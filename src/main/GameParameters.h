//
// Created by cemke on 12/08/2024.
//

#ifndef GAMEPARAMETERS_H
#define GAMEPARAMETERS_H
#include <array>
#include "Buzzer.h"


const Sheet DIRIRIM({{NOTE_C, 4, 0.1}, {NOTE_D, 4, 0.1},
                        {NOTE_C, 4, 0.1}, {NOTE_D, 4, 0.1},
                        {NOTE_C, 4, 0.1}, {NOTE_D, 4, 0.1},
                        {NOTE_C, 4, 0.1}, {NOTE_D, 4, 0.1},
                        {NOTE_C, 4, 0.1}, {NOTE_D, 4, 0.1},
                        {NOTE_C, 4, 0.1}, {NOTE_D, 4, 0.1}}, 500);

const Sheet DEVELOP({
                           {NOTE_C, 4, 1.0}, {NOTE_D, 4, 1.0},
                           {NOTE_C, 4, 0.8}, {NOTE_D, 4, 0.8},
                           {NOTE_C, 4, 0.7}, {NOTE_D, 4, 0.7},
                           {NOTE_C, 4, 0.6}, {NOTE_D, 4, 0.6},
                           {NOTE_C, 4, 0.5}, {NOTE_D, 4, 0.5},
                           {NOTE_C, 4, 0.4}, {NOTE_D, 4, 0.4},
                           {NOTE_C, 4, 0.3}, {NOTE_D, 4, 0.3},
                           {NOTE_C, 4, 0.2}, {NOTE_D, 4, 0.2},
                           {NOTE_C, 4, 0.1}, {NOTE_D, 4, 0.1},
                       }, 240.0);

const Sheet GAME_START_MUSIC = DEVELOP + DIRIRIM;

typedef std::array<Standard_Led, 3> redLedArray;
typedef std::array<Standard_Led, 2> yellowLedArray;
typedef std::array<Push_Button, 2> pushButtonArray;

#endif //GAMEPARAMETERS_H
