#include <Arduino.h>
bool menuIsOpen = false;
int menuActive = 0;
int menuItemsCount = 0;
int menuSelectionsCount = 0;
void menuOpen()
{
  menuIsOpen = true;
  menuActive = 0;
  changingScene = true;
}
void menuClose()
{
  menuIsOpen = false;
  changingScene = true;
}
void drawMenuHeader()
{
  tft.fillRoundRect(0, 0, 240, 16, 5, 0xFF8C);
  tft.setTextSize(2);
  tft.setCursor(90, 1);
  tft.setTextColor(0x700C);
  tft.println("Menu");
}
void drawItem(String text)
{
  tft.setCursor(5, 30 + menuItemsCount * 20);
  tft.setTextColor(0xE37D);
  tft.println(text);
  menuItemsCount++;
}
void drawItems()
{
  menuItemsCount = 0;
  tft.fillRect(0, 17, 130, 240 - 17, 0x700C);
  drawItem("Bin day:");
  drawItem("WK1 colour:");
  drawItem("WK2 colour:");
  drawItem("Year:");
  drawItem("Month:");
  drawItem("Day:");
  drawItem("Weekday:");
  drawItem("Hour (24h):");
  drawItem("Min:");
}
void drawSelection(String text)
{
  tft.setCursor(130, 30 + menuSelectionsCount * 20);
  tft.setTextColor(menuActive == menuSelectionsCount ? 0xFF8C : 0xE37D);
  tft.println(text);
  menuSelectionsCount++;
}
void drawSelections()
{
  menuSelectionsCount = 0;
  tft.fillRect(130, 17, 240 - 130, 240 - 17, 0x700C);
  tft.setTextSize(2);
  drawSelection(dowString(binDow));
  drawSelection(binColours[wk1]);
  drawSelection(binColours[wk2]);
  drawSelection((String)year);
  drawSelection((String)month);
  drawSelection((String)day);
  drawSelection(dowString(dow));
  drawSelection((String)hour);
  drawSelection((String)min);
  drawSelection("SAVE");
}
void pressSelection(int index)
{
  switch (index)
  {
  case 0:
    binDow = (binDow < 7) ? binDow + 1 : 1;
    break;
  case 1:
    wk1 = (wk1 < binColoursCount - 1) ? wk1 + 1 : 0;
    break;
  case 2:
    wk2 = (wk2 < binColoursCount - 1) ? wk2 + 1 : 0;
    break;
  case 3:
    year = (year < 99) ? year + 1 : 20;
    break;
  case 4:
    month = (month < 12) ? month + 1 : 1;
    break;
  case 5:
    day = (day < 31) ? day + 1 : 1;
    break;
  case 6:
    dow = (dow < 7) ? dow + 1 : 1;
    break;
  case 7:
    hour = (hour < 23) ? hour + 1 : 0;
    break;
  case 8:
    min = (min < 59) ? min + 1 : 0;
    break;
  case 9:
    saveEEPROM();
    saveRTC();
    menuClose();
    break;
  default:
    break;
  }
}
void menuLoop()
{
  if (pressedA)
  {
    if (menuIsOpen)
    {
      // menuActive = (menuActive >= menuSelectionsCount - 1) ? 0 : menuActive + 1;
      menuActive = menuActive < menuSelectionsCount - 1 ? menuActive + 1 : 0;
      drawSelections();
    }
    else
    {
      Serial.println("Opening");
      menuOpen();
      drawMenuHeader();
      drawItems();
      drawSelections();
      changingScene = false;
    }
  }
  else if (pressedB && menuIsOpen)
  {
    pressSelection(menuActive);
    drawSelections();
  }
}