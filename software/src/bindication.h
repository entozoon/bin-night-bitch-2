#include <Arduino.h>
byte isBinTimePrev = 99; // unset
unsigned long headerUpdateLast = millis();
const int binColoursCount = 5;
String binColours[binColoursCount] = {
    "Red",
    "Green",
    "Blue",
    "Brown",
    "Black",
};
uint16_t drawRGB24toRGB565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}
unsigned int binColourCodes[binColoursCount] = {
    drawRGB24toRGB565(168, 0, 35),
    drawRGB24toRGB565(33, 211, 33),
    drawRGB24toRGB565(45, 85, 255),
    drawRGB24toRGB565(172, 107, 14),
    drawRGB24toRGB565(30, 30, 30), // set further down too
};
double darkness = .7;
unsigned int binColourCodesDarker[binColoursCount] = {
    drawRGB24toRGB565(round(168 * darkness), round(0 * darkness), round(35) * darkness),
    drawRGB24toRGB565(round(33 * darkness), round(211 * darkness), round(33) * darkness),
    drawRGB24toRGB565(round(45 * darkness), round(85 * darkness), round(255 * darkness)),
    drawRGB24toRGB565(round(172 * darkness), round(107 * darkness), round(14) * darkness),
    drawRGB24toRGB565(round(30 * darkness), round(30 * darkness), round(30) * darkness),
};
void displayHeader()
{
  tft.fillRect(0, 0, 240, 9, 0x0000);
  // https://ee-programming-notepad.blogspot.com/2016/10/16-bit-color-generator-picker.html
  tft.setTextColor(0xB596);
  tft.setTextSize(1);
  // tft.setCursor(0, 0);
  // tft.println("WK 1: GREEN  WK 2: GREEN");
  tft.setCursor(60, 0); // should be safe, faux right align
  tft.print("WK");
  tft.print(_weekNumber + 1); // 0-1 > 1-2
  tft.print(" - ");
  tft.println(getDateTimeString());
  Serial.println(getDateTimeString());
}
void drawBin(int bg, int bgDarker)
{
  tft.fillRoundRect(0, 9, 240, 240 - 9, 10, bg);
  // edge shading
  // // tft.drawLine(0, 40, 10, 240, 0x528A); // antialias?
  // tft.drawLine(2, 30, 11, 240, bgDarker);
  // tft.drawLine(6, 30, 16, 240, bgDarker);
  // for (float x = 0; x < 3.1415; x += 0.1)
  // {
  //   // y = (cos(x + 3.1415 / 2) + 1) / 2 * 240 * 2
  //   // tft.drawFastVLine(round((cos(x + 3.1415 / 2) + 1) / 2 * 240 * 2), 0, 240, bgDarker);
  //   // y = (cos(x + 3.1415 / 2) + 1) / 2) * 240 * 2
  //   // https://www.google.com/search?sxsrf=ALeKk00Nadc2-My6mtlEPCjP4_L41Ai-PQ%3A1605754528019&ei=oN61X5hdh8SBBs-tssAF&q=y+%3D+%28%28cos%28x+%2B+3.1415+%2F+2%29+%2B+1%29+%2F+2%29+*+240+*+2&oq=y+%3D+%28%28cos%28x+%2B+3.1415+%2F+2%29+%2B+1%29+%2F+2%29+*+240+*+2
  //   tft.drawFastVLine(((cos(x + 3.1415 / 2) + 1) / 2) * 240 * 2, 30, 240, bgDarker);
  // }
  for (float i = 0; i < 3.1415; i += .15)
  {
    float x = round(sin(i) * 30);
    tft.drawFastVLine(30 - x, 30, 240, bgDarker);
    tft.drawFastVLine(210 + x, 30, 240, bgDarker);
  }
  // edge triangle wedges
  tft.fillTriangle(0, 40, 0, 240, 10, 240, 0x0000);
  tft.fillTriangle(240, 40, 240, 240, 230, 240, 0x0000);
  tft.fillTriangle(0, 230, 0, 240, 30, 240, 0x0000);
  tft.fillTriangle(240, 230, 240, 240, 210, 240, 0x0000);
  // lid
  tft.fillRoundRect(0, 15, 240, 15, 5, bg);
  tft.fillRoundRect(0, 30, 240, 5, 5, bgDarker);
  tft.fillRect(0, 14, 240, 1, bgDarker);
}
void displayBindication()
{
  byte binTimeNew = isBinTime(binDow) ? 1 : 0;
  // Only update the display if necessary
  if (isBinTimePrev != binTimeNew || changingScene)
  {
    isBinTimePrev = binTimeNew;
    tft.fillRect(0, 9, 240, 240 - 9, 0x0000);
    //
    // Test colours
    //
    // for (int i = 0; i < binColoursCount; i++)
    // {
    //   int bg = binColourCodes[i];
    //   int bgDarker = binColourCodesDarker[i];
    //   drawBin(bg, bgDarker);
    //   tft.setTextSize(8);
    //   tft.setTextColor(bg == drawRGB24toRGB565(30, 30, 30) ? 0xffff : 0x0000);
    //   tft.setCursor(10, 55);
    //   tft.println("  BIN");
    //   tft.setCursor(10, 140);
    //   tft.println("NIGHT");
    //   delay(5000);
    // }
    if (binTimeNew)
    {
      Serial.println(F("isBinTime baby!"));
      Serial.print(F("binColourRightNow: "));
      Serial.println(binColourRightNowString(wk1, wk2, binColours));
      int bg = binColourCodes[binColourRightNow(wk1, wk2)];
      int bgDarker = binColourCodesDarker[binColourRightNow(wk1, wk2)];
      drawBin(bg, bgDarker);
      tft.setTextSize(8);
      //
      tft.setCursor(13, 58);
      tft.setTextColor(bgDarker);
      tft.println("  BIN");
      //
      tft.setCursor(10, 55);
      tft.setTextColor(bg == drawRGB24toRGB565(30, 30, 30) ? 0xffff : 0x0000);
      tft.println("  BIN");
      if (isEvening())
      {
        Serial.println(F("isEvening"));
        tft.setCursor(13, 143);
        tft.setTextColor(bgDarker);
        tft.println("NIGHT");
        //
        tft.setCursor(10, 140);
        tft.setTextColor(bg == drawRGB24toRGB565(30, 30, 30) ? 0xffff : 0x0000);
        tft.println("NIGHT");
      }
      else
      {
        Serial.println(F("not isEvening"));
        tft.setCursor(13, 143);
        tft.setTextColor(bgDarker);
        tft.println("DAY");
        //
        tft.setCursor(45, 140);
        tft.setTextColor(bg == drawRGB24toRGB565(30, 30, 30) ? 0xffff : 0x0000);
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
void bindicationLoop()
{
  if (millis() - headerUpdateLast > 60000 || changingScene)
  {
    headerUpdateLast = millis();
    readRTC();
    displayHeader();
    displayBindication();
    changingScene = false;
  }
}