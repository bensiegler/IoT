/*
 * Project button controlled LED
 * Description: button to toggle LED on and off using latch
 * Author: Ben Siegler
 * Date: Jan 27th 2022
 */

// setup() runs once, when the device is first turned on.
const int LED_PIN = D2;
const int BUTTON_PIN = D3;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

bool isOn = true;
int previousButtonStatus = HIGH;
int buttonVal;

void loop() {
  buttonVal = digitalRead(BUTTON_PIN);
  
  if(buttonVal == LOW && previousButtonStatus == HIGH) {
    Serial.println("Pressed!");
    previousButtonStatus = LOW;
    toggle();
  }else if(buttonVal == HIGH) {
    previousButtonStatus = HIGH;
    Serial.println("Not Pressed");
  }
  delay(100);
}

void toggle() {
  if(isOn) {
    digitalWrite(LED_PIN, LOW);
    isOn = false;
  }else{
    digitalWrite(LED_PIN, HIGH);
    isOn = true;
  }
}