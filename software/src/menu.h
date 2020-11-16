#include <Arduino.h>
bool menuIsOpen = false;
int menuActive = 0;
int menuItemsCount = 4;
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
void drawItem(int index, String text)
{
  tft.setCursor(5, 30 + index * 18);
  tft.setTextColor(0xE37D);
  tft.println(text);
}
void drawItems()
{
  tft.fillRect(0, 17, 130, 240 - 17, 0x700C);
  drawItem(0, "     Bin day:");
  drawItem(1, "WK1 colour:");
  drawItem(2, "WK2 colour:");
}
void drawSelection(int index, bool active, String text)
{
  tft.setCursor(130, 30 + index * 18);
  tft.setTextColor(active ? 0xFF8C : 0xE37D);
  tft.println(text);
}
void drawSelections()
{
  tft.fillRect(130, 17, 240 - 130, 240 - 17, 0x700C);
  tft.setTextSize(2);
  drawSelection(0, menuActive == 0, DoWString(binDoW));
  drawSelection(1, menuActive == 1, binColours[wk1]);
  drawSelection(2, menuActive == 2, binColours[wk2]);
  drawSelection(3, menuActive == 3, "SAVE");
}
void pressSelection(int index)
{
  if (index == 0)
  {
    binDoW = (binDoW < 7 - 1) ? binDoW + 1 : 0;
  }
  else if (index == 1)
  {
    wk1 = (wk1 < 4 - 1) ? wk1 + 1 : 0;
  }
  else if (index == 2)
  {
    wk2 = (wk2 < 4 - 1) ? wk2 + 1 : 0;
  }
  else if (index == 3)
  {
    saveEEPROM();
    menuClose();
  }
}
void menuLoop()
{
  if (pressedA)
  {
    if (menuIsOpen)
    {
      menuActive = (menuActive >= menuItemsCount - 1) ? 0 : menuActive + 1;
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