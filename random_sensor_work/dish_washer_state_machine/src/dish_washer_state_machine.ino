#include "WasherStates.h"
#include "Cycle.h"
#include "Trigger.h"

/*
 * Project dish_washer_state_machine
 * Description: Practice creating state machines by creating one that represents a dishwasher
 * Author: Ben Siegler
 * Date: Feb 26th 2022
 */

const int RED_PIN = D5;
const int GREEN_PIN = D4;
const int BLUE_PIN = D3;
const int SWITCH_PIN = D6;
const int POT_PIN = A0;

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
}

Cycle economy(
    WasherStates::COLD_WASH,
    WasherStates::REGULAR_DRY,
    2000,
    2000);
Cycle deluxe(
    WasherStates::HOT_WASH,
    WasherStates::REGULAR_DRY,
    2000,
    2000);
Cycle super_deluxe(
    WasherStates::HOT_WASH,
    WasherStates::EXTRA_DRY,
    4000,
    4000);

//these variables help to keep track of the current state of the machine
WasherStates currentWasherState = WasherStates::IDLE;
Cycle currentCycle = economy;
int potValue;
bool doorOpenedAfterCompletedCycle = true;

//these are the timers used to trigger state changes
Trigger startDryingTrigger(0, 0, "washing completed", &startDrying);
Trigger finishCycleTrigger(0, 0, "drying completed", &completeCycle);

void loop()
{
  if (currentWasherState == WasherStates::IDLE)
  {
    setCycleType();
    if(!doorClosed()) {   //protect from re-runs
      doorOpenedAfterCompletedCycle = true;
    }
    if (doorClosed() && doorOpenedAfterCompletedCycle)
    {
      Serial.println("starting wash");
      currentWasherState = currentCycle.getWashType();
      startDryingTrigger.setLastOccuredAtTime(millis());
      startDryingTrigger.setShouldHappenEvery(currentCycle.getWashTime());
    }
  }
  else
  {
    if (currentWasherState != WasherStates::REGULAR_DRY && currentWasherState != WasherStates::EXTRA_DRY)
    {
      startDryingTrigger.check();
    }
    else
    {
      finishCycleTrigger.check();
    }
  }
  updateStatusLight();
}

void updateStatusLight() {
  switch (currentWasherState)
  {
  case WasherStates::IDLE:
    Serial.println("IDLE");
    writeToLight(255, 250, 240);   //white
    break;
  case WasherStates::COLD_WASH:
    Serial.println("COLD WASH");
    writeToLight(0, 0, 255);     //blue
    break;
  case WasherStates::HOT_WASH:
    Serial.println("HOT WASH");
    writeToLight(255, 0, 0);     //red
    break;
  case WasherStates::REGULAR_DRY:
    Serial.println("REGULAR DRY");
    writeToLight(255, 128, 0);     //orange
    break;
  case WasherStates::EXTRA_DRY:
    Serial.println("EXTRA DRY");
    writeToLight(255, 255, 51);    //yellow
    break;
  }
}

void writeToLight(int red, int green, int blue) {
    digitalWrite(RED_PIN, red);
    digitalWrite(GREEN_PIN, green);
    digitalWrite(BLUE_PIN, blue);
}

bool doorClosed()
{
  if (digitalRead(SWITCH_PIN) == 0)
  {
    return true;
  }
  return false;
}

void setCycleType()
{
  potValue = analogRead(POT_PIN);
  if (potValue < 1365)
  {
    currentCycle = economy;
  }
  else if (potValue > 2730)
  {
    currentCycle = super_deluxe;
  }
  else
  {
    currentCycle = deluxe;
  }
}

void completeCycle()
{
  currentWasherState = WasherStates::IDLE;

}

void startDrying(){
  currentWasherState = currentCycle.getDryType();
  finishCycleTrigger.setLastOccuredAtTime(millis());
  finishCycleTrigger.setShouldHappenEvery(currentCycle.getDryTime());
}