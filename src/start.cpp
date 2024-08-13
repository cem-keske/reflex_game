#include <Arduino.h>
#include "start.h"
#include "Push_Button.h"
#include "Standard_Led.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Buzzer.h"
#include "Game.h"



Buzzer buzzer1(15);  // Set buzzer pin to digital pin 2


Sheet winning_sound({
        {NOTE_C, 4, 0.5}, {NOTE_E, 4, 0.5}, {NOTE_G, 4, 0.5}, {NOTE_C, 5, 0.5},
        {NOTE_A, -1, 0.5}, {NOTE_E, 4, 0.5}, {NOTE_C, 5, 1}
        // ... more notes
    }, 240.0);

Sheet ode_to_joy({
  {NOTE_E, 4, 1.0}, {NOTE_E, 4, 1.0}, {NOTE_Fs, 4, 1.0}, {NOTE_G, 4, 1.0},
  {NOTE_G, 4, 1.0}, {NOTE_Fs, 4, 1.0}, {NOTE_E, 4, 1.0}, {NOTE_E, 4, 1.0},
  {NOTE_E, 5, 2.0}, {NOTE_D, 5, 1.0}, {NOTE_D, 5, 1.0}, {NOTE_E, 5, 1.0},
  {NOTE_E, 5, 1.0}, {NOTE_E, 4, 2.0}, {NOTE_E, 4, 2.0}, {NOTE_E, 4, 1.0},
  {NOTE_E, 4, 1.0}, {NOTE_E, 4, 1.0}, {NOTE_Fs, 4, 1.0}, {NOTE_G, 4, 1.0},
  {NOTE_G, 4, 1.0}, {NOTE_Fs, 4, 1.0}, {NOTE_E, 4, 1.0}, {NOTE_E, 4, 1.0},
  {NOTE_E, 5, 2.0}, {NOTE_D, 5, 1.0}, {NOTE_D, 5, 1.0}, {NOTE_E, 5, 1.0},
  {NOTE_E, 5, 1.0}, {NOTE_E, 4, 2.0}, {NOTE_E, 4, 2.0}, {NOTE_E, 4, 1.0},
},240);

constexpr auto SCREEN_WIDTH  = 128; // OLED display width, in pixels
constexpr auto SCREEN_HEIGHT = 64; // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
constexpr auto OLED_RESET   =  -1; // Reset pin
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
std::vector<Standard_Led> red_leds = { Standard_Led(32), Standard_Led(26), Standard_Led(14) };
std::array<Standard_Led,2> yellow_leds = { Standard_Led(25), Standard_Led(33) };
Standard_Led green_led(13);
std::array<Push_Button,2> buttons= {Push_Button(16, false), Push_Button(17, false)};

Game game(red_leds, green_led, yellow_leds, buttons, buzzer1);


// void winner_decleration(int winner) {
//   display.clearDisplay();
//   display.setCursor(0,2);
//   display.println(millis()-reflex_time);
//   yellow_leds[winner].turn_on();
//   display.println("Winning player:");
//   display.println(winner);
//   display.display();
//   delay(3000);
//   yellow_leds[winner].turn_off();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // Serial.println("red_leds.size()");
  // Serial.println(red_leds.size());
  game.update();

}
#include "Buzzer.h"

