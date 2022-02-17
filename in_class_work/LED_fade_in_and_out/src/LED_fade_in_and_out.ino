const int led_pin = D2;

void setup() {
    pinMode(led_pin, OUTPUT);
}
  
int brightnessCounter = 0;
int brightnessChangeRate = 1;

void loop() {
    analogWrite(led_pin, brightnessCounter);
    brightnessCounter = (brightnessChangeRate * (brightnessChangeRate / 2));

    if(brightnessCounter > 255) {
        brightnessCounter = 0;
    }

    // time_t now = time(0);
    // brightnessChangeRate = (millis.count() / 1000) % 60;
    delay(4);
}