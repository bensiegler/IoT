#include "rgb-controls/rgb-controls.h"
using namespace RGBControls;

/*
 * Project light_sensor_practice
 * Description:
 * Author:
 * Date:
 */

const int PHOTORESISTOR_PIN = A3;

const int led_pins[3] = {D2, D3, D4};

void setup()
{
  Serial.begin(9600);
  pinMode(PHOTORESISTOR_PIN, INPUT);
  
  for(int i: led_pins) {
    pinMode(i, OUTPUT);
  }
}



int color[3] = {255, 255, 0};
void loop()
{
  int photoInput = analogRead(PHOTORESISTOR_PIN);
  int averageBrightness = map(photoInput, 100, 3500, 0, 255);
  Serial.println(averageBrightness);
  
  analogWrite(D3, averageBrightness);
  analogWrite(D4, averageBrightness);
}