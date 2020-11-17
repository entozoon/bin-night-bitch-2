#include <DS3231.h>
#include <Wire.h>
DS3231 clock;
bool century = false;
bool h12Flag;
bool pmFlag;
int year = 0;
int month = 0;
int day = 0;
int dow = 0; // 1(sun)-7
int hour = 0;
int min = 0;
void readRTC()
{
  Wire.begin();
  year = clock.getYear();
  month = clock.getMonth(century);
  day = clock.getDate();
  dow = clock.getDoW();
  hour = clock.getHour(h12Flag, pmFlag);
  min = clock.getMinute();
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
  result += dowString(dow);
  result += " ";
  result += day;
  result += "/";
  result += month;
  result += "/";
  result += year;
  return result;
}
String getTimeString()
{
  String result = "";
  result += hour < 10 ? "0" : "";
  result += hour;
  result += ":";
  result += min < 10 ? "0" : "";
  result += min;
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
bool isBinTime()
{
  // This needs to be either
  // day before bin day after 4pm
  // day of bin day before 11am
  if (clock.getDoW() == 6)
  {
    return true;
  }
  return false;
}
bool isEvening()
{
  return (clock.getHour(h12Flag, pmFlag) > 12);
}
bool saveRTC()
{
  clock.setClockMode(false); // set to 24h
  clock.setYear(year);
  clock.setMonth(month);
  clock.setDate(day);
  clock.setDoW(dow);
  clock.setHour(hour);
  clock.setMinute(min);
  clock.setSecond(0);
}