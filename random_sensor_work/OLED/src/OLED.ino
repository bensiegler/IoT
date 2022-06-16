#include "SparkFunMicroOLED.h"
#include "string.h"
#include "Pixel.h"


const int SNAKE_LENGTH = 20;
const int LEFT_POT = A1;
const int RIGHT_POT = A0;
const int BUTTON_PIN = D2;

MicroOLED oled(MODE_I2C, 9, 1);
const int screenHeightToPotRatio = oled.getLCDHeight() / 4095.0;
const int screenWidthToPotRatio = oled.getLCDWidth() / 4095.0;

void setup()
{
  Serial.begin(9600);
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.clear(PAGE);
  oled.rectFill(0, 0, oled.getLCDWidth(), oled.getLCDHeight());
  oled.display(); // Display what's in the buffer (splashscreen)
  delay(10000);
  oled.clear(PAGE);
  oled.display();

  pinMode(LEFT_POT, INPUT);
  pinMode(RIGHT_POT, INPUT);
  pinMode(BUTTON_PIN, INPUT);
}

int currentX;
int currentY;
Pixel *nullPixel;
//WANT TO USE PIXEL CLASS
int XCoordBuffer[SNAKE_LENGTH];
int YCoordBuffer[SNAKE_LENGTH];
int pixelCounter = 0;

void loop()
{

  currentX = analogRead(LEFT_POT) * screenWidthToPotRatio;
  currentY = analogRead(RIGHT_POT) * screenHeightToPotRatio;

  Serial.println("(" + String(currentX) + " ," + String(currentY) + ")");

  oled.pixel(currentX, currentY);

  // Pixel *p = &pixelBuffer[pixelCounter % 20];

  // if(p != nullPixel) {
  //   oled.pixel(p->getX(), p->getY(), BLACK, NORM);
  // }
  // pixelBuffer[pixelCounter % SNAKE_LENGTH] = Pixel(currentX, currentY);
  // pixelCounter++;

  oled.display();

  if (isButtonPushed())
  {
    Serial.println("CLEARED");
    pixelCounter = 0;
    oled.clear(PAGE);
  }
}

int currentButtonState = HIGH;
int previousButtonState = HIGH;
bool isButtonPushed()
{
  currentButtonState = digitalRead(BUTTON_PIN);

  if (currentButtonState == LOW && previousButtonState == HIGH)
  {
    previousButtonState = currentButtonState;
    return true;
  }

  previousButtonState = currentButtonState;
  return false;
}