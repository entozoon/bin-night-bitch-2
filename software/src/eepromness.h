#include <Arduino.h>
#include <EEPROM.h>
int eepBinDoW = 1;
int eepWk1 = 2;
int eepWk2 = 3;
int eepYear = 4;
int eepMonth = 5;
int eepDay = 6;
int eepHour = 7;
int eepMin = 8;
// defaults during boot
byte binDoW = 1;
byte wk1 = 1;
byte wk2 = 1;
byte year = 79;
byte month = 1;
byte day = 1;
byte hour = 1;
byte min = 1;
// Screw seconds
void readEEPROM()
{
  // Shove some defaults in
  // EEPROM.write(eepBinDoW, 1);
  // EEPROM.write(eepWk1, 2);
  // EEPROM.write(eepWk2, 3);
  // EEPROM.write(eepYear, 4);
  // EEPROM.write(eepMonth, 5);
  // EEPROM.write(eepDay, 6);
  // EEPROM.write(eepHour, 7);
  // EEPROM.write(eepMin, 8);
  binDoW = EEPROM.read(eepBinDoW);
  wk1 = EEPROM.read(eepWk1);
  wk2 = EEPROM.read(eepWk2);
  year = EEPROM.read(eepYear);
  month = EEPROM.read(eepMonth);
  day = EEPROM.read(eepDay);
  hour = EEPROM.read(eepHour);
  min = EEPROM.read(eepMin);
  Serial.print("EEPROM.length: ");
  Serial.println(EEPROM.length());
  Serial.print("BinDoW: ");
  Serial.println(binDoW);
  Serial.print("wk1: ");
  Serial.println(wk1);
  Serial.print("wk2: ");
  Serial.println(wk2);
  Serial.print("year: ");
  Serial.println(year);
  Serial.print("month: ");
  Serial.println(month);
  Serial.print("day: ");
  Serial.println(day);
  Serial.print("hour: ");
  Serial.println(hour);
  Serial.print("min: ");
  Serial.println(min);
}
void saveEEPROM()
{
  EEPROM.write(eepBinDoW, binDoW);
  EEPROM.write(eepWk1, wk1);
  EEPROM.write(eepWk2, wk2);
  EEPROM.write(eepYear, year);
  EEPROM.write(eepMonth, month);
  EEPROM.write(eepDay, day);
  EEPROM.write(eepHour, hour);
  EEPROM.write(eepMin, min);
}