/*
 * Project blynk_test
 * Description:
 * Author:
 * Date:
 */

#include <blynk.h>

#define BLYNK_TEMPLATE_ID "TMPLI2u4ppQt"
#define BLYNK_DEVICE_NAME "Test Template"
#define BLYNK_AUTH_TOKEN "X"
#define BLYNK_PRINT Serial
#define BLYNK_IP \
    IPAddress(64, 225, 16, 22)  // https://ny3.blynk.cloud/ – New York

BLYNK_WRITE(V5) {
    // this function will get called when v5 has new data
    // the app will also send data so we should retrieve it
    int buttonVal = param.asInt();

    // at this point....pretend that buttonVal represents a physical button
    // on your argon
    digitalWrite(D2, buttonVal);
}

// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  pinMode(D2, OUTPUT);
  delay(5000);

  Blynk.begin(BLYNK_AUTH_TOKEN, BLYNK_IP);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  Blynk.run();
}