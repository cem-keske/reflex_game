#include "Buzzer.h"

int Buzzer::_instanceCounter = 0;  // Initialize the static instance counter

Buzzer::Buzzer(int pin) : _pin(pin), _channel(_instanceCounter++) {
    setupPWM();
}

void Buzzer::setupPWM() {
    ledcAttachPin(_pin, _channel);  // Attach the pin to the PWM channel
    ledcSetup(_channel, 2000, 8);   // Set up PWM with 2 kHz frequency and 8-bit resolution
}

void Buzzer::playTone(note_t note, int octave, int duration) {
    ledcWriteNote(_channel, note, octave);  // Play the specified note
    delay(duration);  // Wait for the duration of the note
    stopTone();  // Stop the tone after the duration
}

void Buzzer::playSheet(const Sheet& sheet) {
    int bpm = sheet.getBPM();
    for (const auto& note : sheet.getNotes()) {
        note_t noteValue;
        Octave octave;
        Note_duration duration;
        std::tie(noteValue, octave, duration) = note;

        int msDuration = (60000.0 / bpm) * duration;  // Convert beats to milliseconds
        playTone(noteValue, octave, msDuration);
    }
}

void Buzzer::stopTone() {
    ledcWrite(_channel, 0);  // Stop the tone
}

Sheet operator+(const Sheet& a, const Sheet& b) {
    std::vector<Music_note> combinedNotes = a.getNotes();
    combinedNotes.insert(combinedNotes.end(), b.getNotes().begin(), b.getNotes().end());

    int combinedBpm = a.getBPM();  // You can choose to handle BPM differently if needed

    return Sheet(combinedNotes, combinedBpm);
}
