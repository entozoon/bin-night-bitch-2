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
  tft.setTextSize(2);
  tft.setCursor(35, 226);
  tft.println("MichaelCook.tech");
}