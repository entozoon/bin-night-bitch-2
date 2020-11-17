#include <Arduino.h>
#include <EEPROM.h>
int eepBinDow = 1; // 1(sun)-7
int eepWk1 = 2;
int eepWk2 = 3;
// defaults during boot
byte binDow = 1;
byte wk1 = 1;
byte wk2 = 1;
// Screw seconds
void readEEPROM()
{
  // Shove some defaults in
  // EEPROM.write(eepBinDow, 1);
  // EEPROM.write(eepWk1, 2);
  // EEPROM.write(eepWk2, 3);
  binDow = EEPROM.read(eepBinDow);
  wk1 = EEPROM.read(eepWk1);
  wk2 = EEPROM.read(eepWk2);
  Serial.print("EEPROM.length: ");
  Serial.println(EEPROM.length());
  Serial.print("BinDow: ");
  Serial.println(binDow);
  Serial.print("wk1: ");
  Serial.println(wk1);
  Serial.print("wk2: ");
  Serial.println(wk2);
  // NOT from EEPROM but handy
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
  EEPROM.write(eepBinDow, binDow);
  EEPROM.write(eepWk1, wk1);
  EEPROM.write(eepWk2, wk2);
}