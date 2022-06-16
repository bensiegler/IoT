#include "PietteTech_DHT.h"
#include "timers/RepeatableTrigger.h"
#include "SparkFunMicroOLED.h"
#include "string.h"
/*
 * Project assignment6
 * Description:
 * Author:
 * Date:
 */

using namespace Timing;

enum DisplayStates
{
  CURRENT,
  MAXMIN,
  ERROR
};
#define BUTTON_PIN D3
#define DHTPIN D2
#define DHTTYPE DHT11 // specific DHT model we have
#define DATA_UPDATE_DELAY 2500
#define OLED_UPDATE_DELAY 2500
#define DHT_TIMEOUT 1000
#define DATA_UPLOAD_DELAY 10000
#define ERROR_CLEAR_DELAY 10000

// peripherals
PietteTech_DHT dht(DHTPIN, DHTTYPE); // DHT software object
MicroOLED oled(MODE_I2C, 9, 1);

RepeatableTrigger dataReadTrigger(DATA_UPDATE_DELAY, &readData, "read data");
RepeatableTrigger oledRefreshTrigger(OLED_UPDATE_DELAY, &refreshOLED, "OLED refresh");
RepeatableTrigger dataUploadTrigger(DATA_UPLOAD_DELAY, &uploadData, "update data");
Trigger clearErrorTrigger(ERROR_CLEAR_DELAY, &clearError, "clear data");

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  dht.begin();

  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.clear(PAGE);
  oled.rectFill(0, 0, oled.getLCDWidth(), oled.getLCDHeight());
  oled.display(); // Display what's in the buffer (splashscreen)
  delay(2000);
  oled.clear(PAGE);
  oled.display();
  oled.setFontType(0);
}

bool previousButtonState = 1;
bool currentButtonState = 1;
DisplayStates displayState = CURRENT;

float maxTemp = 1;
float minTemp = 0;
float currentTemp = 0;
float maxHumidity = 1;
float minHumidity = 0;
float currentHumidity = 0;

void loop()
{
  currentButtonState = digitalRead(BUTTON_PIN);

  if (currentButtonState == 0 && previousButtonState == 1)
  {
    previousButtonState = 0;
    if (displayState == CURRENT)
    {
      displayState = MAXMIN;
    }
    else if (displayState == MAXMIN)
    {
      displayState = CURRENT;
    }
  }
  previousButtonState = currentButtonState;

  dataReadTrigger.check();
  oledRefreshTrigger.check();
  dataUploadTrigger.check();
}

void readData()
{
  int result = dht.acquireAndWait(DHT_TIMEOUT);
  if (result == DHTLIB_OK)
  {
    currentTemp = dht.getCelsius();
    currentHumidity = dht.getHumidity();
    if (currentTemp > maxTemp)
    {
      maxTemp = currentTemp;
    }
    else if (currentTemp < minTemp)
    {
      minTemp = currentTemp;
    }
    if (currentHumidity > maxHumidity)
    {
      maxHumidity = currentHumidity;
    }
    else if (currentHumidity < minHumidity)
    {
      minHumidity = currentHumidity;
    }
  }
};

void clearError()
{
  displayState = MAXMIN;
};

void refreshOLED()
{
  oled.clear(PAGE);
  if (displayState == CURRENT)
  {
    oled.println("Temp:");
    oled.println(String(currentTemp, 1) + " F");
    oled.println();
    oled.println("Hum");
    oled.println(String(currentHumidity, 1) + " %");
  }
  else if (displayState == MAXMIN)
  {
    oled.println("Temp:");
    oled.println("H: " + String(maxTemp, 1) + " F");
    oled.println("L: " + String(minTemp, 1) + " F");
    oled.println("Hum");
    oled.println("H: " + String(maxHumidity, 1) + " %");
    oled.println("L: " + String(minHumidity, 1) + " %");
  }
  else
  {
    oled.println("DHT Error");
  }
  oled.display();
};

void uploadData()
{
  String json = "{\"temperature\":\"" + String(currentTemp, 1) + "\"," +
                "\"humidity\":\"" + String(currentHumidity, 1) + "\"," +
                "}";

  Particle.publish("environment_data_publish", json, PRIVATE);
};
