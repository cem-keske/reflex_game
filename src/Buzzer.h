#ifndef BUZZER_H
#define BUZZER_H

#include "Arduino.h"
#include <vector>
#include <tuple>
#include "esp32-hal-ledc.h"  // Include ESP32 LEDC library

typedef float Note_duration;
typedef int Octave;
typedef std::tuple<note_t, Octave, Note_duration> Music_note;

class Sheet {
public:
    Sheet(std::vector<Music_note> notes, int bpm) : notes(notes), bpm(bpm) {}
    int getBPM() const { return bpm; }
    const std::vector<Music_note>& getNotes() const { return notes; }

    friend Sheet operator+(const Sheet& a, const Sheet& b);

private:
    std::vector<Music_note> notes;
    int bpm;
};

class Buzzer {
public:
    Buzzer(int pin);
    void playTone(note_t note, int octave, int duration);  // in ms Updated to use note_t and octave
    void playSheet(const Sheet& sheet);
    void stopTone();

private:
    int _pin;
    int _channel;
    static int _instanceCounter;  // Static member to track instance count
    void setupPWM();  // Set up PWM settings
};

#endif
