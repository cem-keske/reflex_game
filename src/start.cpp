#include <Arduino.h>
#include "start.h"
#include "Push_Button.h"
#include "Standard_Led.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Buzzer.h"

Buzzer buzzer(15);  // Set buzzer pin to digital pin 2

Sheet coffin1({
    {NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},{NOTE_A, 4, 2.0},{NOTE_B, 4, 2.0},},120);  // 120 BPM

constexpr auto SCREEN_WIDTH  = 128; // OLED display width, in pixels
constexpr auto SCREEN_HEIGHT = 64; // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
constexpr auto OLED_RESET   =  -1; // Reset pin
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Standard_Led red_leds[3] = { Standard_Led(32), Standard_Led(26), Standard_Led(14) };
constexpr size_t no_of_leds = sizeof(red_leds) / sizeof(red_leds[0]);
Standard_Led yellow_leds[2] = { Standard_Led(25), Standard_Led(33) };
Standard_Led green_led(13);
Push_Button buttons[2] = {Push_Button(16, false), Push_Button(17, false)};
bool flag = true;
unsigned long reflex_time;



void startGame(){
  for(auto & red_led : red_leds) {
    red_led.turn_off();
  }
  green_led.turn_off();
  for(auto & yellow_led : yellow_leds) {
    yellow_led.turn_off();
  }

  for(int i=0; i<no_of_leds;++i) {
    red_leds[i].turn_on();
    if (i != no_of_leds-1){
      delay(1500);
    }
  }

  flag=true;
}

void compete(){
  for(auto & red_led : red_leds) {
    red_led.turn_off();
  }
  green_led.turn_on();
  reflex_time = millis();

}

void winner_decleration(int winner) {
  display.clearDisplay();
  display.setCursor(0,2);
  display.println(millis()-reflex_time);
  yellow_leds[winner].turn_on();
  display.println("Winning player:");
  display.println(winner);
  display.display();
  delay(3000);
  yellow_leds[winner].turn_off();

  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Sheet twinkle({
      {NOTE_C, 4, 1.0}, {NOTE_E, 4, 1.0}, {NOTE_G, 4, 1.0}}, 500);  // 120 BPM

  // Play the melody
  buzzer.playSheet(twinkle);
  delay(1000);
  buzzer.playSheet(twinkle);
  delay(1000);
  buzzer.playSheet(twinkle);
  delay(1000);
  buzzer.playSheet(twinkle);
  delay(1000);
  buzzer.playSheet(twinkle);
  delay(1000);
  buzzer.playSheet(twinkle);
  delay(1000);

  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();

  display.setTextSize(1,2);
  display.setTextColor(WHITE);
  display.setCursor(0,32);
  display.println("Hello world!");
  display.display();
  delay(10000);
}

void loop() {
  Serial.println("START");
  startGame();
  int winner = -1;

  unsigned delaytime = random(100,6000);
  for(unsigned t = 0; t<delaytime & flag;++t ) {
    for (int i=0; i<2; ++i) {
      if (buttons[i].is_pressed()) {
        winner = !bool(i);
        flag = false;
      }
    }
    delay(1);
  }

  compete();
  while (flag){
    for (int i=0; i<2; ++i){
      if (buttons[i].is_pressed()) {
        winner = i;
        flag = false;
      }
    }
  }
  winner_decleration(winner);

}
