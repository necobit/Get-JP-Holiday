/**
 * JpHoliday.h - Arduino library for Japanese holiday detection
 * Created by Devin AI, May 4, 2025
 * Based on "国民の祝日に関する法律（昭和23年法律第178号）"
 */

#ifndef JP_HOLIDAY_H
#define JP_HOLIDAY_H

#include <Arduino.h>

class JpHoliday {
public:
  // Constructor
  JpHoliday();
  
  // Check if the specified date is a holiday (including substitute holidays)
  bool isHoliday(int year, int month, int day);
  
  // Get the name of the holiday (returns empty string if not a holiday)
  // Returns "振替休日" for substitute holidays
  String getHolidayName(int year, int month, int day);
  
  // Get the list of holidays for the specified year
  // This will be implemented in a future version
  // void getHolidayList(int year, /* output parameters */);

private:
  // Check if the date is a fixed date holiday
  bool isFixedDateHoliday(int year, int month, int day);
  
  // Check if the date is a variable date holiday
  bool isVariableDateHoliday(int year, int month, int day);
  
  // Check if the date is an equinox holiday
  bool isEquinoxHoliday(int year, int month, int day);
  
  // Check if the date is a substitute holiday
  bool isSubstituteHoliday(int year, int month, int day);
  
  // Calculate the day of the Vernal Equinox
  int calculateVernalEquinoxDay(int year);
  
  // Calculate the day of the Autumnal Equinox
  int calculateAutumnalEquinoxDay(int year);
  
  // Check if the date is the second Monday of the month
  bool isSecondMonday(int year, int month, int day);
  
  // Check if the date is the third Monday of the month
  bool isThirdMonday(int year, int month, int day);
  
  // Get the day of the week (0=Sunday, 1=Monday, ..., 6=Saturday)
  int getDayOfWeek(int year, int month, int day);
  
  // Check if the specified date is a regular holiday (not including substitute holidays)
  bool isRegularHoliday(int year, int month, int day);
};

#endif // JP_HOLIDAY_H
