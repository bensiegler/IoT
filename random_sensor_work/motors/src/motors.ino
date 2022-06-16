/*
 * Project motors
 * Description:
 * Author:
 * Date:
 */

const int AIN1 = D3;
const int AIN2 = D4;
const int PWMA = D5;

const int SERVO_PIN = D2;
const int POT_PIN = A0;

Servo servo;

// setup() runs once, when the device is first turned on.
void setup()
{
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(POT_PIN, INPUT);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  Serial.begin(9600);

  servo.attach(SERVO_PIN);
}

int i = 15;
// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  int potValue = analogRead(POT_PIN);
  Serial.println(potValue);
  int digitalPotValue = map(potValue, 0, 4095, 0, 255);
  analogWrite(PWMA, digitalPotValue);

  i++;
  if(i > 165) {
    i = 15;
  }
  servo.write(i);
  delay(100);
}