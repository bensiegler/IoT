#include <string.h>
/*
 * Project webhooks
 * Description:
 * Author:
 * Date:
 */

// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  Particle.publish("temperature", String(21));
  delay(1000);
}