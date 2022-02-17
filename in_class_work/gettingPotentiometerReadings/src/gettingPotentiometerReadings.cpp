/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/bensiegler/Documents/CodingShit/Learning/argon/gettingPotentiometerReadings/src/gettingPotentiometerReadings.ino"
// const int pinPotentiometer = A1;
// const int pinLED = D2;
// setup() runs once, when the device is first turned on.
void setup();
void loop();
int convertAnalogReadToDigitalValue(int analogValue);
#line 4 "/Users/bensiegler/Documents/CodingShit/Learning/argon/gettingPotentiometerReadings/src/gettingPotentiometerReadings.ino"
void setup() {
  Serial.begin(9600);
  pinMode(pinLED, OUTPUT);
  // pinMode(pinPotentiometer, INPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // int digitalRead = convertAnalogReadToDigitalValue(analogRead(pinPotentiometer));
  // Serial.println("Digital value of potentiometer = " + digitalRead);
  digitalWrite(pinLED, 255);
}

int convertAnalogReadToDigitalValue(int analogValue) {
    int maxAnalog = 4095;
    int maxDigital = 255;
    double ratio = maxDigital / maxAnalog;
    return analogValue * ratio;
}