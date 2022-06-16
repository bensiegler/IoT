#include <iostream>
#include <string>
/*
 * Project blinking_led
 * Description: 
 * Author:
 * Date:
 */

const int led_pin = D2;

void setup() {
    pinMode(led_pin, OUTPUT);
    Serial.begin(9600);
}
  
int brightnessCounter = 0;

void loop() {
    analogWrite(led_pin, brightnessCounter);
    // Serial.begin("brightness (0 - 255) set to " + String(brightnessCounter));

    brightnessCounter++;

    if(brightnessCounter > 255) {
        brightnessCounter = 0;
    }
    delay(4);
}