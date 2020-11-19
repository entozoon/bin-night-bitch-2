#include <Arduino.h>
#include <rtc.h>
#include <tft.h>
#include <logo.h>
#include <eepromness.h>
#include <buttons.h>
// Big juicy global variables. Why? Because I'm bad at C!
bool changingScene = true;
#include <bindication.h>
#include <menu.h>
void setup(void)
{
  Serial.begin(115200);
  tftSetup();
  displayLogo();
  setupButtons();
  // readRTC(); // no need here, runs within bindication
  readEEPROM(); // do infrequently; has a lifespan
  delay(1000);
}
void loop()
{
  checkButtons();
  menuLoop();
  if (!menuIsOpen)
  {
    bindicationLoop();
  }
  delay(150); // at least debounce the buttons slightly
}