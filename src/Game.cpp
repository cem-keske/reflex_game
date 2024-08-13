//
// Created by cemke on 12/08/2024.
//

#include "Game.h"
#include "GameParameters.h"
#include <ratio>


Game::Game(const std::vector<Standard_Led>& red_leds, Standard_Led green_led, std::array<Standard_Led, 2> yellow_leds,
    std::array<Push_Button, 2> player_buttons, Buzzer buzzer): red_leds_(red_leds),
                                                                green_led_(green_led),
                                                                yellow_leds_(yellow_leds),
                                                                player_buttons_(player_buttons),
                                                                buzzer_(buzzer){}

Button_state Game::read_buttons() {
    bool first = this->player_buttons_[0].is_pressed();
    bool second = this->player_buttons_[1].is_pressed();

    if (first && second) {
        return Button_state::BOTH_PRESSED;
    } else if (first) {
        return Button_state::PLAYER_1_PRESSED;
    } else if (second) {
        return Button_state::PLAYER_2_PRESSED;
    }
    return Button_state::NONE_PRESSED;
}

void Game::update() {
    buzzer_.update();
    switch (state) {
        case NOT_STARTED:
            start_game();
            break;
        case SEQUENCE_STARTED:
            update_sequence();
            break;
        case LIGHTS_OUT:
            break;
        case GAME_ENDED:
            break;
    }

}


/* sets the game start time
 * turns off all the leds
 * pushes the game start music into the buffer
 * goes to next state
 */

void Game::start_game() {
    this->start_time = millis();

    //Turn off all leds
    for(Standard_Led & led: yellow_leds_) {
        led.turn_off();
    }
    for(Standard_Led & led: red_leds_) {
        led.turn_off();
    }
    green_led_.turn_off();
    buzzer_.play(GAME_START_MUSIC);

    next_state();
}


void Game::update_sequence() {
    // Serial.println(red_leds_.size());
    green_led_.turn_on();
    yellow_leds_[0].turn_on();
    time_t elapsed = millis() - state_change_time;
    // Serial.println(elapsed);
    // Serial.println(elapsed/time_between_leds);
    for(int i(0); i < unsigned(elapsed / time_between_leds); i++) {
        // Serial.println("Here");
        red_leds_[i].turn_on();
    }
}


// uptates the "state_change_time"
//
// changes the state to the next one
void Game::next_state() {
    state_change_time = millis();

    switch (state) {
        case NOT_STARTED:
            state = SEQUENCE_STARTED;
            break;
        case SEQUENCE_STARTED:
            state = LIGHTS_OUT;
            break;
        case LIGHTS_OUT:
            state = GAME_ENDED;
            break;
        case GAME_ENDED:
            state = NOT_STARTED;
            break;
    }
}
