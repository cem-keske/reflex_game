//
// Created by cemke on 04/08/2024.
//

#include "Push_Button.h"
#include <Arduino.h>
#ifdef CLION
#include <esp32-hal-gpio.h>
#endif

Push_Button::Push_Button(int pin, bool is_pull_up) {
    this->pin = pin;
    this->is_pull_up = is_pull_up;
    pinMode(this->pin, INPUT);
}

bool Push_Button::is_pressed() const {
    bool status = digitalRead(this->pin);
    if (this->is_pull_up) {
        return !status;
    }
    return status;
}

// bool Push_Button::is_pressed() {
//     return  this->is_pull_up xor digitalRead(this->pin);
// }