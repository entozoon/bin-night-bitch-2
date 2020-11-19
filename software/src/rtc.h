#include <DS3231.h>
#include <Wire.h>
#include <TimeLib.h>
DS3231 clock;
bool century = false;
bool h12Flag;
bool pmFlag;
// 'year' and whatnot are fuckin nabbed by Time.h
int _year = 0;
int _month = 0;
int _day = 0;
int _dow = 0; // 1(sun)-7
int _hour = 0;
int _min = 0;
int _weekNumber = 0;
time_t secondsSince9thNov2020(int yearr, int monthh, int dayy, int hourr, int minn)
{
  // 9th nov makes christmas week as week1, might not be accurate but.. it's a gift
  tmElements_t input9thNov2020;
  // Actually, during calc we're gonna whip off 2000 years for var size
  input9thNov2020.Year = 2020 - 2000;
  input9thNov2020.Month = 11;
  input9thNov2020.Day = 9;
  input9thNov2020.Hour = 0;
  input9thNov2020.Minute = 0;
  input9thNov2020.Second = 0;
  // 0000/1/1 0:0:0 = 0 seconds
  time_t time9thNov2020 = makeTime(input9thNov2020);
  tmElements_t inputNow;
  inputNow.Year = yearr - 2000;
  inputNow.Month = monthh;
  inputNow.Day = dayy;
  inputNow.Hour = hourr;
  inputNow.Minute = minn;
  inputNow.Second = 0;
  return makeTime(inputNow) - time9thNov2020;
}
// returns 0 or 1 with 9 if on the given week, 1 next week, 0, etc
int weekNumberSince(time_t secondss)
{
  // Serial.print("now: ");
  // Serial.println(now);
  // Serial.print("seconds since: ");
  // Serial.println(now - time9thNov2020);
  int daysSince = floor(secondss / 60 / 60 / 24);
  // Serial.print("daysSince: ");
  // Serial.println(daysSince);
  int weeksSince = floor(daysSince / 7);
  // Serial.print("weeksSince: ");
  // Serial.println(weeksSince);
  int weekNumber = weeksSince % 2 == 0 ? 0 : 1;
  // Serial.print("weekNumber: ");
  // Serial.println(weekNumber);
  // Serial.println("");
  return weekNumber;
}
void readRTC()
{
  Wire.begin();
  _year = clock.getYear();
  _month = clock.getMonth(century);
  _day = clock.getDate();
  _dow = clock.getDoW();
  _hour = clock.getHour(h12Flag, pmFlag);
  _min = clock.getMinute();
  // Serial.print("2021, 1, 18: ");
  // Serial.println(weekNumberSince(secondsSince9thNov2020(2021, 1, 18, random(0, 24), random(0, 59))));
  _weekNumber = weekNumberSince(secondsSince9thNov2020(_year + 2000, _month, _day, _hour, _min));
  Serial.print("weekNumber (0 or 1): ");
  Serial.println(_weekNumber);
}
String days[] = {"n/a",
                 "Sun",
                 "Mon",
                 "Tue",
                 "Wed",
                 "Thu",
                 "Fri",
                 "Sat"};
String dowString(int index)
{
  return days[index];
}
String getDateString()
{
  String result = "";
  result += dowString(_dow);
  result += " ";
  result += _day;
  result += "/";
  result += _month;
  result += "/";
  result += _year;
  return result;
}
String getTimeString()
{
  String result = "";
  result += _hour < 10 ? "0" : "";
  result += _hour;
  result += ":";
  result += _min < 10 ? "0" : "";
  result += _min;
  // result += ":";
  // result += clock.getSecond();
  return result;
}
String getDateTimeString()
{
  String result = "";
  result += getDateString();
  result += " ";
  result += getTimeString();
  return result;
}
// don't check RTC too often.. slows the clock down potentially
// https://forum.arduino.cc/index.php?topic=343194.msg2389434#msg2389434
// although next dude says that's bullshit
bool isBinTime(byte binDow)
{
  // needs readRTC() to have been run
  return (
      // Day before bin day after 4pm
      _dow == (binDow - 1 && clock.getHour(h12Flag, pmFlag) > 16) ||
      // Day of bin day before 11am
      _dow == (binDow && clock.getHour(h12Flag, pmFlag) < 11));
}
bool isEvening()
{
  return (clock.getHour(h12Flag, pmFlag) > 12);
}
int binColourRightNow(byte wk1, byte wk2)
{
  // _weekNumber calculcated during readRTC
  return _weekNumber == 1 ? wk2 : wk1;
}
String binColourRightNowString(byte wk1, byte wk2, String binColours[])
{
  return binColours[binColourRightNow(wk1, wk2)];
}
void saveRTC()
{
  clock.setClockMode(false); // set to 24h
  clock.setYear(_year);
  clock.setMonth(_month);
  clock.setDate(_day);
  clock.setDoW(_dow);
  clock.setHour(_hour);
  clock.setMinute(_min);
  clock.setSecond(0);
}