#include <Arduino.h>
//
//
// //
// // BLINK
// //
// void setup()
// {
//   pinMode(LED_BUILTIN, OUTPUT);
// }
// void loop()
// {
//   digitalWrite(LED_BUILTIN, HIGH);
//   delay(1000);
//   digitalWrite(LED_BUILTIN, LOW);
//   delay(1000);
// }
//
// //
// // PIN TEST
// //
// void setup()
// {
//   Serial.begin(115200);
//   delay(4000);
//   pinMode(7, OUTPUT); // 7 = D7
//   pinMode(8, OUTPUT);
//   pinMode(A0, INPUT_PULLUP);
//   pinMode(A1, INPUT_PULLUP);
// }
// void loop()
// {
//   digitalWrite(7, 1);
//   digitalWrite(8, 1);
//   digitalWrite(9, 1);
//   delay(1000);
//   digitalWrite(7, 0);
//   digitalWrite(8, 0);
//   digitalWrite(9, 0);
//   delay(1000);
//   Serial.println(digitalRead(A0));
//   Serial.println(digitalRead(A1));
//   Serial.println("");
// }
//
//
// LCD Test
//
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library#include <Adafruit_GFX.h>    // Core graphics library
#define CS 9                 // D9    (unused)
#define DC 7                 // D8
#define RST 8                // D7
// #define SDA A4 // (built-in)
// #define SCK A5 // (built-in SCL)
Adafruit_ST7789 tft = Adafruit_ST7789(CS, DC, RST); // hardware SPI
// Adafruit_ST7789 tft = Adafruit_ST7789(CS, DC, SDA, SCK, RST); // software SPI
float p = 3.1415926;
float time = 0;
void testlines(uint16_t color)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(0, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(0, 0, tft.width() - 1, y, color);
    delay(0);
  }
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(tft.width() - 1, 0, 0, y, color);
    delay(0);
  }
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(0, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
    delay(0);
  }
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
    delay(0);
  }
}
void testdrawtext(char *text, uint16_t color)
{
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
void testfastlines(uint16_t color1, uint16_t color2)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y = 0; y < tft.height(); y += 5)
  {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x = 0; x < tft.width(); x += 5)
  {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}
void testdrawrects(uint16_t color)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color);
  }
}
void testfillrects(uint16_t color1, uint16_t color2)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = tft.width() - 1; x > 6; x -= 6)
  {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color2);
  }
}
void testfillcircles(uint8_t radius, uint16_t color)
{
  for (int16_t x = radius; x < tft.width(); x += radius * 2)
  {
    for (int16_t y = radius; y < tft.height(); y += radius * 2)
    {
      tft.fillCircle(x, y, radius, color);
    }
  }
}
void testdrawcircles(uint8_t radius, uint16_t color)
{
  for (int16_t x = 0; x < tft.width() + radius; x += radius * 2)
  {
    for (int16_t y = 0; y < tft.height() + radius; y += radius * 2)
    {
      tft.drawCircle(x, y, radius, color);
    }
  }
}
void testtriangles()
{
  tft.fillScreen(ST77XX_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width() / 2;
  int x = tft.height() - 1;
  int y = 0;
  int z = tft.width();
  for (t = 0; t <= 15; t++)
  {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}
void testroundrects()
{
  tft.fillScreen(ST77XX_BLACK);
  int color = 100;
  int i;
  int t;
  for (t = 0; t <= 4; t += 1)
  {
    int x = 0;
    int y = 0;
    int w = tft.width() - 2;
    int h = tft.height() - 2;
    for (i = 0; i <= 16; i += 1)
    {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}
void tftPrintTest()
{
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}
void mediabuttons()
{
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}
void setup(void)
{
  Serial.begin(115200);
  delay(1000);
  Serial.print(F("Right.."));
  Serial.print(F("Hello! ST77xx TFT Test"));
  // if the display has CS pin try with SPI_MODE0
  tft.init(240, 240, SPI_MODE2); // Init ST7789 display 240x240 pixel SPI_MODE0 SPI_MODE1 SPI_MODE2 SPI_MODE3
  // if the screen is flipped, remove this command
  // tft.setRotation(2);
  Serial.println(F("Initialized"));
  // uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;
  Serial.println(time, DEC);
  delay(500);
  // large block of text
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST77XX_WHITE);
  delay(1000);
  // tft print function!
  tftPrintTest();
  delay(4000);
  // a single pixel
  tft.drawPixel(tft.width() / 2, tft.height() / 2, ST77XX_GREEN);
  delay(500);
  // line draw test
  testlines(ST77XX_YELLOW);
  delay(500);
  // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);
  testdrawrects(ST77XX_GREEN);
  delay(500);
  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);
  tft.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);
  testroundrects();
  delay(500);
  testtriangles();
  delay(500);
  mediabuttons();
  delay(500);
  Serial.println("done");
  delay(1000);
}
void loop()
{
  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
}
//
// //
// // RTC SET (using serial monitor input)
// //
// #include <DS3231.h>
// #include <Wire.h>
// DS3231 clock;
// byte year;
// byte month;
// byte date;
// byte dow;
// byte hour;
// byte minute;
// byte second;
// bool century = false;
// bool h12Flag;
// bool pmFlag;
// void inputDateFromSerial()
// {
//   boolean isStrComplete = false;
//   char inputChar;
//   byte temp1, temp2;
//   char inputStr[20];
//   uint8_t currentPos = 0;
//   while (!isStrComplete)
//   {
//     if (Serial.available())
//     {
//       inputChar = Serial.read();
//       inputStr[currentPos] = inputChar;
//       currentPos += 1;
//       // Check if string complete (end with "x")
//       if (inputChar == 'x')
//       {
//         isStrComplete = true;
//       }
//     }
//   }
//   Serial.println(inputStr);
//   // Find the end of char "x"
//   int posX = -1;
//   for (uint8_t i = 0; i < 20; i++)
//   {
//     if (inputStr[i] == 'x')
//     {
//       posX = i;
//       break;
//     }
//   }
//   // Consider 0 character in ASCII
//   uint8_t zeroAscii = '0';
//   // Read Year first
//   temp1 = (byte)inputStr[posX - 13] - zeroAscii;
//   temp2 = (byte)inputStr[posX - 12] - zeroAscii;
//   year = temp1 * 10 + temp2;
//   // now month
//   temp1 = (byte)inputStr[posX - 11] - zeroAscii;
//   temp2 = (byte)inputStr[posX - 10] - zeroAscii;
//   month = temp1 * 10 + temp2;
//   // now date
//   temp1 = (byte)inputStr[posX - 9] - zeroAscii;
//   temp2 = (byte)inputStr[posX - 8] - zeroAscii;
//   date = temp1 * 10 + temp2;
//   // now Day of Week
//   dow = (byte)inputStr[posX - 7] - zeroAscii;
//   // now Hour
//   temp1 = (byte)inputStr[posX - 6] - zeroAscii;
//   temp2 = (byte)inputStr[posX - 5] - zeroAscii;
//   hour = temp1 * 10 + temp2;
//   // now Minute
//   temp1 = (byte)inputStr[posX - 4] - zeroAscii;
//   temp2 = (byte)inputStr[posX - 3] - zeroAscii;
//   minute = temp1 * 10 + temp2;
//   // now Second
//   temp1 = (byte)inputStr[posX - 2] - zeroAscii;
//   temp2 = (byte)inputStr[posX - 1] - zeroAscii;
//   second = temp1 * 10 + temp2;
// }
// void setup()
// {
//   // Start the serial port
//   Serial.begin(115200);
//   // Start the I2C interface
//   Wire.begin();
//   // Request the time correction on the Serial
//   delay(4000);
//   Serial.println("Format YYMMDDwhhmmssx");
//   Serial.println("Where YY = Year (ex. 20 for 2020)");
//   Serial.println("      MM = Month (ex. 04 for April)");
//   Serial.println("      DD = Day of month (ex. 09 for 9th)");
//   Serial.println("      w  = Day of week from 1 to 7, 1 = Sunday (ex. 5 for Thursday)");
//   Serial.println("      hh = hours in 24h format (ex. 09 for 9AM or 21 for 9PM)");
//   Serial.println("      mm = minutes (ex. 02)");
//   Serial.println("      ss = seconds (ex. 42)");
//   Serial.println("Example for input : 2004095090242x");
//   Serial.println("-----------------------------------------------------------------------------");
//   Serial.println("Please enter the current time to set on DS3231 ended by 'x':");
// }
// void loop()
// {
//   if (Serial.available())
//   {
//     inputDateFromSerial();
//     clock.setClockMode(false); // set to 24h
//     clock.setYear(year);
//     clock.setMonth(month);
//     clock.setDate(date);
//     clock.setDoW(dow);
//     clock.setHour(hour);
//     clock.setMinute(minute);
//     clock.setSecond(second);
//     // Give time at next five seconds
//     for (uint8_t i = 0; i < 5; i++)
//     {
//       delay(1000);
//       Serial.print(clock.getYear(), DEC);
//       Serial.print("-");
//       Serial.print(clock.getMonth(century), DEC);
//       Serial.print("-");
//       Serial.print(clock.getDate(), DEC);
//       Serial.print(" ");
//       Serial.print(clock.getHour(h12Flag, pmFlag), DEC); //24-hr
//       Serial.print(":");
//       Serial.print(clock.getMinute(), DEC);
//       Serial.print(":");
//       Serial.println(clock.getSecond(), DEC);
//     }
//     // Notify that we are ready for the next input
//     Serial.println("Please enter the current time to set on DS3231 ended by 'x':");
//   }
//   delay(1000);
// }
//
// //
// // RTC READ
// //
// #include <DS3231.h>
// #include <Wire.h>
// DS3231 clock;
// bool century = false;
// bool h12Flag;
// bool pmFlag;
// void setup()
// {
//   // Start the serial port
//   Serial.begin(115200);
//   delay(4000);
//   // Start the I2C interface
//   Wire.begin();
// }
// void loop()
// {
//   delay(1000);
//   Serial.print("20");
//   Serial.print(clock.getYear(), DEC);
//   Serial.print("-");
//   Serial.print(clock.getMonth(century), DEC);
//   Serial.print("-");
//   Serial.print(clock.getDate(), DEC);
//   Serial.print(" ");
//   Serial.print(clock.getHour(h12Flag, pmFlag), DEC); //24-hr
//   Serial.print(":");
//   Serial.print(clock.getMinute(), DEC);
//   Serial.print(":");
//   Serial.println(clock.getSecond(), DEC);
// }