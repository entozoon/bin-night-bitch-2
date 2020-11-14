#include <Arduino.h>
void displayLogo()
{
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(0, 0, 240, 240, 16, ST77XX_ORANGE);
  tft.setTextSize(5);
  tft.setTextColor(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.println("    Bin");
  tft.println("    Night");
  tft.println("    Bitch");
  tft.println("        v2");
}
void displayHeader()
{
  tft.fillRect(0, 0, 240, 9, 0x0000);
  // https://ee-programming-notepad.blogspot.com/2016/10/16-bit-color-generator-picker.html
  tft.setTextColor(0x73AE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.println("WK 1: GREEN  WK 2: GREEN");
  tft.setCursor(140, 0); // should be safe, faux right align
  tft.println(getDateTimeString());
  Serial.println(getDateTimeString());
}
void displayBindication()
{
  if (isBinTime())
  {
    tft.setTextColor(ST77XX_BLACK);
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