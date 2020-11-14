#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <nokia-myke.h>
#define CS 9  // D9    (unused)
#define DC 7  // D8
#define RST 8 // D7
// #define SDA A4 // (built-in)
// #define SCK A5 // (built-in SCL)
Adafruit_ST7789 tft = Adafruit_ST7789(CS, DC, RST); // hardware SPI
void tftSetup()
{
  tft.init(240, 240, SPI_MODE2);
  tft.setRotation(1);
  tft.setTextWrap(true);
  tft.setFont(&__nokiafc224pt7b);
}