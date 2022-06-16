#include "argon_ble_setup.h"
#include <string>


const int PWMA = D8;
const int AI1 = D7;
const int AI2 = D6;
const int BI1 = D5;
const int BI2 = D4;
const int PWMB = D3;

int speed = 100;

void setup() {
    /* === START BLE SETUP === */
    argon_ble_setup();
    /* === END BLE SETUP === */
    Serial.begin(9600);

    pinMode(AI1, OUTPUT);
    pinMode(AI2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(BI1, OUTPUT);
    pinMode(BI2, OUTPUT);
    pinMode(PWMB, OUTPUT);

    digitalWrite(AI1, HIGH);
    digitalWrite(AI2, LOW);
    digitalWrite(BI1, HIGH);
    digitalWrite(BI2, LOW);
    Serial.begin(9600);
}
void loop() {
}

void onDataReceived(const uint8_t* data, size_t len, const BlePeerDevice& peer, void* context) {
   if(data[1] == 'B' && data[2] == '5' && data[3] == '1') {
      //FORWARD
      forwardGear();
      analogWrite(PWMA, speed - map(speed, 0, 255, 0, 10));
      analogWrite(PWMB, speed);
    }else if(data[1] == 'B' && data[2] == '6' && data[3] == '1') {
      reverseGear();
      analogWrite(PWMA, speed);
      analogWrite(PWMB, speed - map(speed, 0, 255, 0, 10));
    }else if(data[1] == 'B' && data[2] == '7' && data[3] == '1') {
      forwardGear();
      analogWrite(PWMA, speed);
      analogWrite(PWMB, speed/2);
    }else if(data[1] == 'B' && data[2] == '8' && data[3] == '1') {
      forwardGear();
      analogWrite(PWMA, speed/2);
      analogWrite(PWMB, speed);
    }else if(data[1] == 'B' && data[2] >= '1' && data[2] <= '4' && data[3] == '1') {
      setSpeed(data[2] - 48);
    }else if(data[1] == 'B' && data[2] >= 5 && data[3] == '0') {
      analogWrite(PWMA, 0);
      analogWrite(PWMB, 0);
    }
}

void forwardGear() {
    digitalWrite(AI1, HIGH);
    digitalWrite(AI2, LOW);
    digitalWrite(BI1, HIGH);
    digitalWrite(BI2, LOW);
}

void reverseGear() {
    digitalWrite(AI1, LOW);
    digitalWrite(AI2, HIGH);
    digitalWrite(BI1, LOW);
    digitalWrite(BI2, HIGH);
}

void setSpeed(int gear) {
  speed = map(gear, 1, 4, 50, 255);
}

