//
// Created by cemke on 12/08/2024.
//

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <array>
#include "Standard_Led.h"
#include "Push_Button.h"
#include "Buzzer.h"
#include "GameParameters.h"

enum Game_state { NOT_STARTED = 0, SEQUENCE_STARTED = 1, LIGHTS_OUT = 2, GAME_ENDED = 3 };
enum Button_state { PLAYER_1_PRESSED, PLAYER_2_PRESSED, NONE_PRESSED, BOTH_PRESSED };

class Game {
public:

    Game(redLedArray                   red_leds,
        Standard_Led                   green_led,
        yellowLedArray                 yellow_leds,
        pushButtonArray                player_buttons,
        Buzzer                         buzzer
        );
    /* Reads the state of the player buttons and returns
    */
    Button_state read_buttons();

    void update();
    Game_state get_state(){return state;};

private:
    redLedArray                    red_leds_;
    Standard_Led                   green_led_;
    yellowLedArray                 yellow_leds_;
    pushButtonArray                player_buttons_;
    Buzzer buzzer_;
    Game_state state = Game_state::NOT_STARTED;
    time_t start_time;
    time_t state_change_time;
    time_t time_between_leds = 2000;//ms
    int winner = -1;


    void next_state();
    void start_game();
    void update_sequence();
    void lights_out();
    void declare_winner();
};



#endif //GAME_H
