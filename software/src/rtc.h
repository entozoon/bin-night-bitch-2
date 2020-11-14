#include <DS3231.h>
#include <Wire.h>
DS3231 clock;
bool century = false;
bool h12Flag;
bool pmFlag;
void setupRtc()
{
  Wire.begin();
}
String getDoWString()
{
  String days[] = {"Sun",
                   "Mon",
                   "Tue",
                   "Wed",
                   "Thu",
                   "Fri",
                   "Sat"};
  return days[clock.getDoW()];
}
String getDateString()
{
  String result = "";
  result += getDoWString();
  result += " ";
  result += clock.getDate();
  result += "/";
  result += clock.getMonth(century);
  result += "/";
  result += clock.getYear();
  return result;
}
String getTimeString()
{
  String result = "";
  result += clock.getHour(h12Flag, pmFlag);
  result += ":";
  result += clock.getMinute();
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