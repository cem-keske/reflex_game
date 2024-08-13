//
// Created by cemke on 04/08/2024.
//

#include "Standard_Led.h"
#include <Arduino.h>


Standard_Led::Standard_Led(int pin, bool is_on) {
    this->pin_ = pin;
    this-> status_ = is_on;
    pinMode(this->pin_, OUTPUT);
    if(is_on) {
        this->turn_on();
    }
}

void Standard_Led::toggle() {
    if(this->status_ == false) {
        this->turn_on();
    } else {
        this->turn_off();
    }
}

void Standard_Led::turn_on() {
    // Serial.println("Led will turn on.");
    // Serial.println(this->pin_);
    digitalWrite(this->pin_, HIGH);
    this->status_ = true;
}

void Standard_Led::turn_off() {
    digitalWrite(this->pin_, LOW);
    this->status_ = false;
}
