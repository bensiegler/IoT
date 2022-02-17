/*
 * Project ThreeColorLED
 * Description: button controlled LED. double-click to change settings. 
 *  Setting 1 = click once to change color
 *  Setting 2 = auto change every 5 seconds (could also allow user to set this interval themselves)
 *  Setting 3 = rgb fade in fade out
 * Author: Ben Siegler
 * Date: Jan 27th 2022
 */

const int RED_PIN = D2;
const int BLUE_PIN = D4;
const int GREEN_PIN = D3;

const int BUTTON_PIN = D7;

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT);
  setNewColor();
  Serial.begin(9600);
}

int previousButtonState = HIGH;
int currentButtonState = HIGH;

/*
SETTINGS
1 = RANDOM SWITCHING (per 5 second interval)
2 = CLICK TO SWITCH 
3 = SMOOTH ALTERNATE (not implemented yet)
*/
int setting = 1;

// TIMERS
int lastCallTime = Time.now();
int lastClickTime = Time.now();

void loop()
{
  // Serial.println(setting);
  currentButtonState = digitalRead(BUTTON_PIN);

  if (currentButtonState == LOW && previousButtonState == HIGH)
  {
    // button pushed
    if (detectDoubleClick())
    {
      toggleSettings();
    }
    else if (setting == 2)
    {
      setNewColor();
    }

    previousButtonState = LOW;
    lastClickTime = Time.now();
  }
  else if (currentButtonState == HIGH)
  {
    previousButtonState = HIGH;
  }

  if (setting == 1 && timeSinceLastChangeIsGreaterThan(5))
  {
    setNewColor();
  }
}

void toggleSettings()
{
  setting++;

  if (setting > 2)
  {
    setting = 1;
  }
}

bool timeSinceLastChangeIsGreaterThan(int seconds)
{
  int timeSinceLastCall = Time.now() - lastCallTime;

  if (timeSinceLastCall > seconds){
    lastCallTime = Time.now();
    return true;
  }
  else
  {
    return false;
  }
}

void setNewColor()
{
  analogWrite(RED_PIN, random(0, 255));
  analogWrite(BLUE_PIN, random(0, 255));
  analogWrite(GREEN_PIN, random(0, 255));
}

bool detectDoubleClick()
{
  if ((Time.now() - lastClickTime) < 1)
  {
    return true;
  }
  return false;
}
