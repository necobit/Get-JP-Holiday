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
  // Private methods will be added during implementation
};

#endif // JP_HOLIDAY_H
