/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/bensiegler/Documents/CodingShit/Learning/argon/LED_fade_in_and_out/src/LED_fade_in_and_out.ino"
/*
 * Project LED_fade_in_and_out
 * Description:
 * Author:
 * Date:
 */

void setup();
void loop();
#line 8 "/Users/bensiegler/Documents/CodingShit/Learning/argon/LED_fade_in_and_out/src/LED_fade_in_and_out.ino"
const int led_pin = D2;

void setup() {
    pinMode(led_pin, OUTPUT);
}
  
int brightnessCounter = 0;

void loop() {
    analogWrite(led_pin, brightnessCounter);
    brightnessCounter++;

    if(brightnessCounter > 255) {
        brightnessCounter = 0;
    }
    delay(4);
}