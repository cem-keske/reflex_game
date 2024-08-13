#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include <memory>
#include <queue>
#include <vector>
#include <tuple>
#include <esp32-hal-ledc.h>

typedef float Note_duration;
typedef int Octave;
typedef std::tuple<note_t, Octave, Note_duration> Music_note;

class Sheet {
public:
    Sheet(std::vector<Music_note> notes, float bpm = 120.0)
        : _notes(notes), _bpm(bpm) {}

    const std::vector<Music_note>& getNotes() const {
        return _notes;
    }

    float getBPM() const {
        return _bpm;
    }

    uint32_t getNoteDuration(Note_duration duration) const {
        return (60000 / _bpm) * duration;
    }

    Sheet operator+(const Sheet& other) const {
        std::vector<Music_note> combinedNotes = _notes;
        combinedNotes.insert(combinedNotes.end(), other._notes.begin(), other._notes.end());
        return Sheet(combinedNotes, _bpm);
    }

private:
    std::vector<Music_note> _notes;
    float _bpm;
};

class Buzzer {
public:
    Buzzer(uint8_t pin)
        : _pin(pin), _channel(nextChannel()), _isPlaying(false), _noteIndex(0), _lastUpdate(0) {
        ledcAttachPin(pin, _channel);
    }

    // Overloaded play method that takes a Sheet directly
    void play(const Sheet& sheet) {
        play(std::make_shared<Sheet>(sheet));
    }

    // Start playing a sheet, using shared_ptr to manage the Sheet's memory
    void play(std::shared_ptr<Sheet> sheet) {
        _sheetQueue.push(sheet);
        if (!_isPlaying) {
            startNextSheet();
        }
    }

    void stop() {
        _isPlaying = false;
        ledcWriteTone(_channel, 0);  // Turn off the buzzer
        while (!_sheetQueue.empty()) {
            _sheetQueue.pop();  // Clear the queue
        }
    }

    bool isPlaying() const {
        return _isPlaying;
    }

    void update() {
        if (_isPlaying && millis() - _lastUpdate >= _noteDuration) {
            playNextNote();
        }
    }

private:
    void startNextSheet() {
        if (!_sheetQueue.empty()) {
            _currentSheet = _sheetQueue.front();
            _sheetQueue.pop();
            _noteIndex = 0;
            _isPlaying = true;
            _lastUpdate = millis();
            playNextNote();
        } else {
            stop();  // No more sheets to play, stop playback
        }
    }

    void playNextNote() {
        if (_currentSheet && _noteIndex < _currentSheet->getNotes().size()) {
            Music_note note = _currentSheet->getNotes()[_noteIndex];
            playNote(std::get<0>(note), std::get<1>(note), std::get<2>(note));
            _lastUpdate = millis();
            _noteIndex++;
        } else {
            _isPlaying = false;
            startNextSheet();  // Start the next sheet if available
        }
    }

    void playNote(note_t note, Octave octave, Note_duration duration) {
        if (octave == -1 || note == NOTE_MAX) {
            ledcWriteTone(_channel, 0);  // Stop playing if note is invalid or rest
        } else {
            ledcWriteNote(_channel, note, octave);
        }
        _noteDuration = _currentSheet->getNoteDuration(duration);
    }

    static uint8_t nextChannel() {
        static uint8_t currentChannel = 0;
        return currentChannel++;
    }

    uint8_t _pin;
    uint8_t _channel;
    bool _isPlaying;
    uint32_t _lastUpdate;
    uint32_t _noteDuration;
    size_t _noteIndex;
    std::shared_ptr<Sheet> _currentSheet;  // Shared pointer to manage Sheet's memory
    std::queue<std::shared_ptr<Sheet>> _sheetQueue;  // Queue of sheets to be played
};

#endif