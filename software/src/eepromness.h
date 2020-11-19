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
  // Serial.print(F("EEPROM.length: "));
  // Serial.println(EEPROM.length());
  Serial.print(F("BinDow: "));
  Serial.println(binDow);
  Serial.print(F("wk1: "));
  Serial.println(wk1);
  Serial.print(F("wk2: "));
  Serial.println(wk2);
  // NOT from EEPROM but handy
  Serial.print(F("year: "));
  Serial.println(_year);
  Serial.print(F("month: "));
  Serial.println(_month);
  Serial.print(F("day: "));
  Serial.println(_day);
  Serial.print(F("hour: "));
  Serial.println(_hour);
  Serial.print(F("min: "));
  Serial.println(_min);
}
void saveEEPROM()
{
  EEPROM.write(eepBinDow, binDow);
  EEPROM.write(eepWk1, wk1);
  EEPROM.write(eepWk2, wk2);
}