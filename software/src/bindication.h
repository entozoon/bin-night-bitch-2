#include <Arduino.h>
byte isBinTimePrev = 99; // unset
unsigned long headerUpdateLast = millis();
void displayHeader()
{
  tft.fillRect(0, 0, 240, 9, 0x0000);
  // https://ee-programming-notepad.blogspot.com/2016/10/16-bit-color-generator-picker.html
  tft.setTextColor(0x73AE);
  tft.setTextSize(1);
  // tft.setCursor(0, 0);
  // tft.println("WK 1: GREEN  WK 2: GREEN");
  tft.setCursor(140, 0); // should be safe, faux right align
  tft.println(getDateTimeString());
  Serial.println(getDateTimeString());
}
void displayBindication()
{
  byte binTimeNew = isBinTime() ? 1 : 0;
  if (isBinTimePrev != binTimeNew || changingScene)
  {
    isBinTimePrev = binTimeNew;
    tft.fillRect(0, 9, 240, 240 - 9, 0x0000);
    if (isBinTime())
    {
      tft.setTextColor(0x0000);
      tft.setTextSize(8);
      tft.setCursor(10, 50);
      tft.println("  BIN");
      if (isEvening())
      {
        tft.setCursor(8, 140);
        tft.println("NIGHT");
      }
      else
      {
        tft.setCursor(45, 140);
        tft.println("DAY");
      }
    }
    else
    {
      tft.setTextColor(0x0020);
      tft.setTextSize(5);
      tft.setCursor(40, 100);
      tft.println(" Relax");
    }
  }
}
String binColours[] = {
    "Red",
    "Green",
    "Blue",
    "Black",
};
void bindicationLoop()
{
  if (millis() - headerUpdateLast > 30000 || changingScene)
  {
    headerUpdateLast = millis();
    displayHeader();
  }
  displayBindication();
  changingScene = false;
}