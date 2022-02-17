
/*
 * Project Scanning Light (itp348_a3_ben_siegler)
 * Description: Scanning or blinking series of lights with potentiometer 
 * adjusted brightness and rate. 
 * Author: Benjamin Siegler
 * Date: Feb 1st 2022
 */

const int POTENTIOMETER_PIN = A0;
const int led_pins[6] = {D2, D3, D4, D5, D6, D7};

void setup()
{
  Serial.begin(9600);
  pinMode(POTENTIOMETER_PIN, INPUT);

  for (int i : led_pins)
  {
    pinMode(i, OUTPUT);
  }
}

int brightness;
int changeRateInMillis;
int potValue;
int lastLightChangeTime = 0;
int currentLightNum = 0;

void loop()
{
  potValue = analogRead(POTENTIOMETER_PIN);

  brightness = 255 - analogToDigital(potValue);
  //override. minimum brightness is 10 of 255
  if(brightness < 10) {
    brightness = 10;
  }

  //min of 1 millisecond differences or max ~4 seconds
  changeRateInMillis = potValue;

  if (moreThanXMillisPassedSinceLightChange(changeRateInMillis))
  {
    switchLight();
    lastLightChangeTime = millis();
  }
  //adjust brightness in between light changes
  analogWrite(led_pins[currentLightNum], brightness);
}

bool increment = true;
void switchLight()
{
  // turn off current light
  analogWrite(led_pins[currentLightNum], LOW);

  //back and forth sweeping logic
  if(currentLightNum > 4) {
    increment = false;
  }
  if(currentLightNum < 1) {
    increment = true;
  }

  if(increment) {
    currentLightNum++;
  }else{
    currentLightNum--;
  }

  // turn on next light
  analogWrite(led_pins[currentLightNum], brightness);
}

double conversionRate = 255.0 / 4095.0;
int analogToDigital(int analogInput) {
  return conversionRate * analogInput;
}

bool moreThanXMillisPassedSinceLightChange(int numMillis)
{
  if ((millis() - lastLightChangeTime) > numMillis)
  {
    return true;
  }
  return false;
}
