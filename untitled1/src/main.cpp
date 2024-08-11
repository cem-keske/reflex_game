#ifdef CLION
#include "Arduino.h"
#endif
#include <Push_Button.h>
#include <Standard_Led.h>

Standard_Led red_leds[3] = { Standard_Led(32), Standard_Led(26), Standard_Led(14) };
constexpr size_t no_of_leds = sizeof(red_leds) / sizeof(red_leds[0]);
Standard_Led yellow_leds[2] = { Standard_Led(25), Standard_Led(33) };
Standard_Led green_led(13);
Push_Button buttons[2] = {Push_Button(16, false), Push_Button(17, false)};
bool flag = true;

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
}

void winner_decleration(int winner) {
  yellow_leds[winner].turn_on();
  Serial.println("Winning player:");
  Serial.println(winner);
  delay(3000);
  yellow_leds[winner].turn_off();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
