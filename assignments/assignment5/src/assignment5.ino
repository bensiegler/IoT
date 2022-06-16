#include <TimerEvent.h>
#include <Flash.h>
#include <list>
using namespace std;

#define RED_PIN D2
#define GREEN_PIN D3
#define BLUE_PIN D4

#define RED_BUTTON_PIN D7
#define BLUE_BUTTON_PIN D8

#define RED_TIMER_LENGTH 7000
#define BLUE_TIMER_LENGTH 11000
#define BLINK_INTERVAL_LENGTH 50
#define PUBLISH_INTERVAL_LENGHT 20000

/*
 * Project assignment5
 * Description: Two timers that can run simultaneously
 * Author: Ben Siegler
 * Date: Feb 14th 2022
 */

bool redCurrentButtonState = HIGH;
bool redPreviousButtonState = HIGH;
bool blueCurrentButtonState = HIGH;
bool bluePreviousButtonState = HIGH;

bool blueTimerActive = false;
bool redTimerActive = false;

int blueAlarmElapsedCount = 0;
int redAlarmElapsedCount = 0;

list<Flash> flashList;

void setup()
{
  Serial.begin(9600);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  pinMode(RED_BUTTON_PIN, INPUT);
  pinMode(BLUE_BUTTON_PIN, INPUT);
}

// publish events
TimerEvent publishRedAlarmCountEvent(0, 20000, "red alarm count publish", &publishRedAlarmCount);
TimerEvent publishBlueAlarmCountEvent(10000, 20000, "blue alarm count publish", &publishBlueAlarmCount);

// these are essentially toggle-able timers with callbacks
TimerEvent flashRedStatus(0, 1000, "red timer status flash added to queue", &addRedFlashToQueue, false);
TimerEvent flashBlueStatus(0, 1000, "blue timer status flash added to queue", &addBlueFlashToQueue, false);

TimerEvent redTimer(0, RED_TIMER_LENGTH, "red timer went off", &handleRedAlarm, false);
TimerEvent blueTimer(0, BLUE_TIMER_LENGTH, "blue timer went off", &handleBlueAlarm, false);
TimerEvent flashQueueProgression(0, 10, "", &flash);

void loop()
{
  redCurrentButtonState = digitalRead(RED_BUTTON_PIN);
  blueCurrentButtonState = digitalRead(BLUE_BUTTON_PIN);

  if (redCurrentButtonState == LOW && redPreviousButtonState == HIGH)
  {
    // Red button pushed
    if (redTimer.getIsActive())
    {
      flashRedStatus.setIsActive(false);
      redTimer.setIsActive(false);
    }
    else
    {
      flashRedStatus.setIsActive(true);
      redTimer.setIsActive(true);
      redTimer.setLastOccuredAtTime(millis());
      redTimer.setShouldHappenEvery(RED_TIMER_LENGTH);
    }
  }
  redPreviousButtonState = redCurrentButtonState;

  if (blueCurrentButtonState == LOW && bluePreviousButtonState == HIGH)
  {
    // Blue button pushed
    if (blueTimer.getIsActive())
    {
      flashBlueStatus.setIsActive(false);
      blueTimer.setIsActive(false);
    }
    else
    {
      flashBlueStatus.setIsActive(true);
      blueTimer.setIsActive(true);
      blueTimer.setLastOccuredAtTime(millis());
      blueTimer.setShouldHappenEvery(BLUE_TIMER_LENGTH);
    }
  }
  bluePreviousButtonState = blueCurrentButtonState;

  flashQueueProgression.update();
  flashBlueStatus.update();
  flashRedStatus.update();
  redTimer.update();
  blueTimer.update();
  publishBlueAlarmCountEvent.update();
  publishRedAlarmCountEvent.update();
}

void writeColor(int red, int green, int blue)
{
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

// TimerEvent behaviors

void publishBlueAlarmCount()
{
  Serial.println("publishing blue");
  Particle.publish("blue timer has elapsed X times", String(blueAlarmElapsedCount));
}

void publishRedAlarmCount()
{
  Serial.println("publishing red");
  Particle.publish("red timer has elapsed X times", String(redAlarmElapsedCount));
}

void flash()
{
  if (flashList.empty())
  {
    writeColor(0, 0, 0);
    // check for changes every 20th of a second
    flashQueueProgression.setShouldHappenEvery(50);
  }
  else
  {
    Flash nextFlash = flashList.front();
    flashList.pop_front();
    writeColor(nextFlash.getRedVal(), nextFlash.getGreenVal(), nextFlash.getBlueVal());
    // set time to wait until next pop
    flashQueueProgression.setShouldHappenEvery(nextFlash.getFlashLengthInMillis());
  }
};

void handleRedAlarm()
{
  redAlarmElapsedCount++;
  redTimer.setIsActive(false);
  flashRedStatus.setIsActive(false);
  flashList.push_back(Flash(255, 0, 0));
  flashList.push_back(Flash());
  flashList.push_back(Flash(255, 0, 0));
  flashList.push_back(Flash());
}

void handleBlueAlarm()
{
  blueAlarmElapsedCount++;
  blueTimer.setIsActive(false);
  flashBlueStatus.setIsActive(false);
  flashList.push_back(Flash(0, 0, 255));
  flashList.push_back(Flash());
  flashList.push_back(Flash(0, 0, 255));
  flashList.push_back(Flash());
}

void addBlueFlashToQueue()
{
  flashList.push_front(Flash(0, 0, 255, BLINK_INTERVAL_LENGTH));
}

void addRedFlashToQueue()
{
  flashList.push_front(Flash(255, 0, 0, BLINK_INTERVAL_LENGTH));
}
