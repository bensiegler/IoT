
/*
 * Project assignment2
 * Description: light sculpture. fade in and out red and blue LEDs
 * Author: Ben Siegler
 * Date: Jan 24th 2022
 */

const int blue1 = A1;
const int blue2 = A2;

const int red1 = A3;
const int red2 = A4;
const int red3 = A5;

// setup() runs once, when the device is first turned on.
void setup()
{
  Serial.begin(9600);
  pinMode(blue1, OUTPUT);
  pinMode(blue2, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(red3, OUTPUT);
}

int redBrightness = 0;
int redFadeRate = 10;
bool isRedIncreasing = true;

int blueBrightness = 255;
int blueFadeRate = 10;
bool isBlueIncreasing = false;

void loop()
{
  if (redBrightness <= 0)
  {
    isRedIncreasing = true;
    redFadeRate = rand() % 5;
  }
  else if (redBrightness >= 255)
  {
    isRedIncreasing = false;
  }

  if (blueBrightness <= 0)
  {
    isBlueIncreasing = true;
    blueFadeRate = rand() % 5;
  }
  else if (blueBrightness >= 255)
  {
    isBlueIncreasing = false;
  }

  blueBrightness = calculateNewBrightness(isBlueIncreasing, blueBrightness, blueFadeRate);
  redBrightness = calculateNewBrightness(isRedIncreasing, redBrightness, redFadeRate);

  Serial.println("red brightness: " + redBrightness);
  analogWrite(red1, redBrightness);
  analogWrite(red2, redBrightness);
  analogWrite(red3, redBrightness);

  Serial.println("blue brightness: " + blueBrightness);
  analogWrite(blue1, blueBrightness);
  analogWrite(blue2, blueBrightness);

  delay(50);
}

int calculateNewBrightness(bool isIncreasing, int currentBrightness, int fadeRate)
{
  if (isIncreasing)
  {
    return currentBrightness + fadeRate;
  }
  else
  {
    return currentBrightness - fadeRate;
  }
}