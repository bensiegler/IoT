/*
 * Project: Assignment 7
 * Description: Blynk App tea brewer
 * Author: Ben Siegler
 * Date: March 26th 2022
 */

#include <blynk.h>
#include "pitches.h"

#define BLYNK_TEMPLATE_ID "TMPLYx2vjVI5"
#define BLYNK_DEVICE_NAME "teaBrewing"
#define BLYNK_AUTH_TOKEN "getGzTysUVpyQ30n4zUauNizS_bZuzr2"
#define BLYNK_PRINT Serial
#define BLYNK_IP \
  IPAddress(64, 225, 16, 22) // https://ny3.blynk.cloud/ – New York

#define SLIDER_TEA_TYPE_VPIN V0
#define TEXT_TEA_TYPE_VPIN V1
#define TEXT_CUP_STATUS_VPIN V2
#define BUTTON_START_VPIN V3
#define BREW_STATE_VPIN V4
#define SOUND_BUTTON_VPIN V5
#define TIME_LEFT_VPIN V7

#define MAGNETIC_SWITCH_PIN D2
#define SPEAKER_PIN D3

const int notes[16] = {NOTE_B0, NOTE_GS2, NOTE_C3, NOTE_FS3, NOTE_GS3, NOTE_GS4, NOTE_GS2, NOTE_E1, NOTE_GS1, NOTE_B1, NOTE_A2, NOTE_C3, NOTE_DS2, NOTE_C2, NOTE_D4, NOTE_DS5};

unsigned long lastSwitchedStateAt;
int timeLeft;
bool soundOn;

enum BREWING_STATE
{
  IDLE,
  HEAT,
  STEEP,
  HOLD,
  POUR
};
enum TEA_TYPE
{
  GREEN = 2,
  BLACK = 3,
  HERBAL = 4
};

BREWING_STATE currBrewingState;
TEA_TYPE selectedTeaType = GREEN;

void setup()
{

  currBrewingState = IDLE;
  selectedTeaType = GREEN;

  pinMode(MAGNETIC_SWITCH_PIN, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, BLYNK_IP);
  Blynk.virtualWrite(BUTTON_START_VPIN, 0);
  Serial.begin(9600);
}

BLYNK_WRITE(BUTTON_START_VPIN)
{
  bool buttonVal = param.asInt();

  if (buttonVal)
  {
    timeLeft = 10 + selectedTeaType;
    currBrewingState = HEAT;
    lastSwitchedStateAt = millis();
  }
  else
  {
    currBrewingState = IDLE;
  }
}

BLYNK_WRITE(SOUND_BUTTON_VPIN)
{
  soundOn = param.asInt();
}

BLYNK_WRITE(SLIDER_TEA_TYPE_VPIN)
{
  int sliderVal = param.asInt();
  if (currBrewingState == IDLE)
  {
    switch (sliderVal)
    {
    case 0:
      selectedTeaType = GREEN;
      Blynk.virtualWrite(TEXT_TEA_TYPE_VPIN, "GREEN");
      break;
    case 1:
      selectedTeaType = BLACK;
      Blynk.virtualWrite(TEXT_TEA_TYPE_VPIN, "BLACK");
      break;
    case 2:
      selectedTeaType = HERBAL;
      Blynk.virtualWrite(TEXT_TEA_TYPE_VPIN, "HERBAL");
    }
  }
}

void loop()
{
  Blynk.run();
  updateLocalState();
  sendNewDataToBlynk();
}

void sendNewDataToBlynk()
{
  switch (currBrewingState)
  {
  case IDLE:
    Blynk.virtualWrite(BREW_STATE_VPIN, "IDLE");
    break;
  case HEAT:
    Blynk.virtualWrite(BREW_STATE_VPIN, "HEATING");
    break;
  case STEEP:
    Blynk.virtualWrite(BREW_STATE_VPIN, "STEEPING");
    break;
  case HOLD:
    Blynk.virtualWrite(BREW_STATE_VPIN, "HOLDING");
    break;
  case POUR:
    Blynk.virtualWrite(BREW_STATE_VPIN, "POURING");
    break;
  }
  Blynk.virtualWrite(TIME_LEFT_VPIN, timeLeft);
  Blynk.virtualWrite(TEXT_CUP_STATUS_VPIN, digitalRead(MAGNETIC_SWITCH_PIN));
}

void updateLocalState()
{
  switch (currBrewingState)
  {
  case HEAT:
    timeLeft = 6 - (millis() - lastSwitchedStateAt) / 1000;
    if (millis() >= lastSwitchedStateAt + 6000)
    {
      currBrewingState = STEEP;
      lastSwitchedStateAt = millis();
    }
    break;
  case STEEP:
    timeLeft = selectedTeaType - (millis() - lastSwitchedStateAt) / 1000;
    if (millis() >= lastSwitchedStateAt + (selectedTeaType * 1000))
    {
      lastSwitchedStateAt = millis();
      if (digitalRead(MAGNETIC_SWITCH_PIN) == LOW)
      {
        currBrewingState = POUR;
      }
      else
      {
        currBrewingState = HOLD;
      }
    }
    break;
  case HOLD:
    if (digitalRead(MAGNETIC_SWITCH_PIN) == LOW)
    {
      currBrewingState = POUR;
    }
    lastSwitchedStateAt = millis();
    break;
  case POUR:
    timeLeft = 4 - ((millis() - lastSwitchedStateAt) / 1000);
    if (millis() >= lastSwitchedStateAt + 4000)
    {
      currBrewingState = IDLE;
      Blynk.virtualWrite(BUTTON_START_VPIN, 0);
      if (soundOn)
      {
        playTune();
      }
    }
    break;
  }
}

void playTune()
{
  for (unsigned int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++)
  {
    if (i % 2 == 0)
    {
      tone(SPEAKER_PIN, notes[i], 200);
    }
    else
    {
      tone(SPEAKER_PIN, notes[i], 500);
    }
  }
}