#include <Event.h>

/*
 * Project timing
 * Description: 
 * Author: 
 * Date: 
 */

const int GREEN_LED = D2;
const int RED_LED = D3;
const int BUTTON_PIN = D4;

Event publishButtonPushes(0, 5000);
Event toggleGreenLight(0, 2000, "toggled green light on/off");
int numButtonPresses = 0;
bool greenLightIsOn = false;

// setup() runs once, when the device is first turned on.
void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
}

bool currentButtonState = HIGH;
bool previousButtonState = HIGH;
bool lightTwoIsOn = false;

void loop() {
    currentButtonState = digitalRead(BUTTON_PIN);

    if(currentButtonState == HIGH && previousButtonState == LOW) {
      numButtonPresses++;
      if(lightTwoIsOn) {
        digitalWrite(RED_LED, LOW);
        lightTwoIsOn = false;
      }else{
        digitalWrite(RED_LED, HIGH);
        lightTwoIsOn = true;
      }
    }

    previousButtonState = currentButtonState;

    if(publishButtonPushes.isDueToOccur()) {
      Particle.publish("number of button pushes", String(numButtonPresses));
      publishButtonPushes.occured();
    }

    if(toggleGreenLight.isDueToOccur()) {
      if(greenLightIsOn) {
        greenLightIsOn = false;
      }else{
        greenLightIsOn = true;
      }
      digitalWrite(GREEN_LED, greenLightIsOn);
      toggleGreenLight.occured();
    }
}