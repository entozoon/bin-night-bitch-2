#include <Arduino.h>
#include <rtc.h>
#include <tft.h>
#include <display.h>
void setup(void)
{
  Serial.begin(115200);
  tftSetup();
  displayLogo();
  setupRtc();
  delay(2000);
}
void loop()
{
  tft.fillScreen(ST77XX_BLACK);
  displayBindication();
  displayHeader();
  delay(5000);
}