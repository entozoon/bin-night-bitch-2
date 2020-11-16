#include <Arduino.h>
int pinA = 12;
int pinB = A0;
bool pressedA = false;
bool pressedB = false;
void setupButtons()
{
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
}
void checkButtons()
{
  // I mean, I know there are smarter ways to do this.. state arrays and whatnot but it's literally just two buttons, so why keep the compiled code flat and exhaustive (like your mom)
  if (pressedA == false && digitalRead(pinA) == 0)
  {
    Serial.println("pinA");
    pressedA = true;
  }
  else if (pressedA == true && digitalRead(pinA) == 1)
  {
    pressedA = false;
  }
  if (pressedB == false && digitalRead(pinB) == 0)
  {
    Serial.println("pinB");
    pressedB = true;
  }
  else if (pressedB == true && digitalRead(pinB) == 1)
  {
    pressedB = false;
  }
}