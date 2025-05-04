/**
 * JpHoliday.h - Arduino library for Japanese holiday detection
 * Created by Devin AI, May 4, 2025
 * Based on "国民の祝日に関する法律（昭和23年法律第178号）"
 */

#ifndef JP_HOLIDAY_H
#define JP_HOLIDAY_H

#include <Arduino.h>

// Cross-platform PROGMEM compatibility
#if defined(ESP8266) || defined(ESP32)
  #include <pgmspace.h>
#else
  #include <avr/pgmspace.h>
#endif

// Holiday name indices for memory optimization
enum HolidayNameIndex {
  HOLIDAY_NONE = 0,
  HOLIDAY_NEW_YEAR = 1,
  HOLIDAY_COMING_OF_AGE = 2,
  HOLIDAY_FOUNDATION = 3,
  HOLIDAY_EMPEROR_BIRTHDAY = 4,
  HOLIDAY_VERNAL_EQUINOX = 5,
  HOLIDAY_SHOWA = 6,
  HOLIDAY_CONSTITUTION = 7,
  HOLIDAY_GREENERY = 8,
  HOLIDAY_CHILDREN = 9,
  HOLIDAY_MARINE = 10,
  HOLIDAY_MOUNTAIN = 11,
  HOLIDAY_RESPECT_AGED = 12,
  HOLIDAY_AUTUMNAL_EQUINOX = 13,
  HOLIDAY_SPORTS = 14,
  HOLIDAY_HEALTH_SPORTS = 15,
  HOLIDAY_CULTURE = 16,
  HOLIDAY_LABOR_THANKSGIVING = 17,
  HOLIDAY_SUBSTITUTE = 18
};

// Fixed date holiday structure (for lookup table)
typedef struct {
  uint8_t month;
  uint8_t day;
  uint16_t startYear;
  uint16_t endYear;
  uint8_t nameIndex;
} FixedHoliday;

// Holiday structure to store date and name index
struct Holiday {
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t nameIndex;
  
  // Helper method to get the holiday name
  String getName() const;
};

class JpHoliday {
public:
  // Constructor
  JpHoliday();
  
  // Check if the specified date is a holiday (including substitute holidays)
  bool isHoliday(uint16_t year, uint8_t month, uint8_t day);
  
  // Get the name of the holiday (returns empty string if not a holiday)
  // Returns "振替休日" for substitute holidays
  String getHolidayName(uint16_t year, uint8_t month, uint8_t day);
  
  // Get the name index of the holiday (returns 0 if not a holiday)
  uint8_t getHolidayNameIndex(uint16_t year, uint8_t month, uint8_t day);
  
  // Get the list of holidays for the specified year
  // Returns the number of holidays found
  uint8_t getHolidayList(uint16_t year, Holiday* holidays, uint8_t maxHolidays);
  
  // Get holiday name from index (static method)
  static String getHolidayNameFromIndex(uint8_t nameIndex);

private:
  // Check if the date is a fixed date holiday
  bool isFixedDateHoliday(uint16_t year, uint8_t month, uint8_t day);
  
  // Check if the date is a variable date holiday
  bool isVariableDateHoliday(uint16_t year, uint8_t month, uint8_t day);
  
  // Check if the date is an equinox holiday
  bool isEquinoxHoliday(uint16_t year, uint8_t month, uint8_t day);
  
  // Check if the date is a substitute holiday
  bool isSubstituteHoliday(uint16_t year, uint8_t month, uint8_t day);
  
  // Calculate the day of the Vernal Equinox
  uint8_t calculateVernalEquinoxDay(uint16_t year);
  
  // Calculate the day of the Autumnal Equinox
  uint8_t calculateAutumnalEquinoxDay(uint16_t year);
  
  // Check if the date is the second Monday of the month
  bool isSecondMonday(uint16_t year, uint8_t month, uint8_t day);
  
  // Check if the date is the third Monday of the month
  bool isThirdMonday(uint16_t year, uint8_t month, uint8_t day);
  
  // Get the day of the week (0=Sunday, 1=Monday, ..., 6=Saturday)
  uint8_t getDayOfWeek(uint16_t year, uint8_t month, uint8_t day);
  
  // Check if the specified date is a regular holiday (not including substitute holidays)
  bool isRegularHoliday(uint16_t year, uint8_t month, uint8_t day);
  
  // Helper method to get days in month
  uint8_t getDaysInMonth(uint16_t year, uint8_t month);
  
  // Helper method to check if year is leap year
  bool isLeapYear(uint16_t year);
};

#endif // JP_HOLIDAY_H
