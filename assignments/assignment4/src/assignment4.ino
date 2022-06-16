#include <string.h>

/*
 * Project assignment4
 * Description: A random number generator (1 - 6) that displays the generated value using 9 LEDs
 * in a dice pattern.
 * Author: Ben Siegler
 * Date: Feb 8th 2022
 */

const int BUTTON_PIN = A0;
const int LED_PINS[3][3] = {
    {D2, 0, D5},
    {D3, D4, 0},
    {D5, 0, D2}}; //could optimize here. row irrelevant -> lights dependent on above 2 rows.
const int lightPatterns[6][3][3] = {
    {// pattern #1
     {0, 0, 0},
     {0, 1, 0},
     {0, 0, 0}}, //could get rid of this row and the 5 others below. but code more opaque if I do
    {// pattern #2
     {1, 0, 0},
     {0, 0, 0},
     {0, 0, 1}},
    {// pattern #3
     {1, 0, 0},
     {0, 1, 0},
     {0, 0, 1}},
    {// pattern #4
     {1, 0, 1},
     {0, 0, 0},
     {1, 0, 1}},
    {// pattern #5
     {1, 0, 1},
     {0, 1, 0},
     {1, 0, 1}},
    {// pattern #6
     {1, 0, 1},
     {1, 0, 1},
     {1, 0, 1}}};

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);

  // set all light pins (stored in LED_PINS) to output
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      pinMode(LED_PINS[i][j], OUTPUT);
    }
  }
}

void loop()
{
  if (buttonPush()) {
    int random = (int) (rand() % 6);
    Particle.publish("generated value", String(random + 1));
    setNewLightPattern(random);
  }
}

void setNewLightPattern(int patternNumber)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (lightPatterns[patternNumber][i][j] == 1)
      {
        digitalWrite(LED_PINS[i][j], HIGH);
      }
      else
      {
        digitalWrite(LED_PINS[i][j], LOW);
      }
    }
  }
}

int currentButtonState = HIGH;
int previousButtonState = HIGH;

bool buttonPush()
{
  currentButtonState = digitalRead(BUTTON_PIN);
  // LATCH FOR FALLING EDGE
  if (currentButtonState == LOW && previousButtonState == HIGH)
  {
    previousButtonState = currentButtonState;
    return true;
  }

  previousButtonState = currentButtonState;
  return false;
}