/**
 * JpHoliday.cpp - Arduino library for Japanese holiday detection
 * Created by Devin AI, May 4, 2025
 * Based on "国民の祝日に関する法律（昭和23年法律第178号）"
 */

#include "JpHoliday.h"

JpHoliday::JpHoliday() {
}

bool JpHoliday::isHoliday(int year, int month, int day) {
  if (year < 2000 || year > 2030) {
    return false;
  }
  
  if (isFixedDateHoliday(year, month, day)) {
    return true;
  }
  
  if (isVariableDateHoliday(year, month, day)) {
    return true;
  }
  
  if (isEquinoxHoliday(year, month, day)) {
    return true;
  }
  
  return false;
}

String JpHoliday::getHolidayName(int year, int month, int day) {
  return "";
}


bool JpHoliday::isFixedDateHoliday(int year, int month, int day) {
  if (month == 1 && day == 1) {
    return true;
  }
  
  if (month == 2 && day == 11) {
    return true;
  }
  
  if (month == 2 && day == 23 && year >= 2020) {
    return true;
  }
  if (month == 12 && day == 23 && year < 2019) {
    return true;
  }
  
  if (month == 4 && day == 29) {
    return true;
  }
  
  if (month == 5 && day == 3) {
    return true;
  }
  
  if (month == 5 && day == 4) {
    return true;
  }
  
  if (month == 5 && day == 5) {
    return true;
  }
  
  if (month == 8 && day == 11 && year >= 2016) {
    return true;
  }
  
  if (month == 11 && day == 3) {
    return true;
  }
  
  if (month == 11 && day == 23) {
    return true;
  }
  
  return false;
}

bool JpHoliday::isVariableDateHoliday(int year, int month, int day) {
  if (month == 1 && isSecondMonday(year, month, day)) {
    return true;
  }
  
  if (month == 7) {
    if (year >= 2003 && isThirdMonday(year, month, day)) {
      return true;
    } else if (year < 2003 && day == 20) {
      return true;
    }
  }
  
  if (month == 9) {
    if (year >= 2003 && isThirdMonday(year, month, day)) {
      return true;
    } else if (year < 2003 && day == 15) {
      return true;
    }
  }
  
  if (month == 10 && isSecondMonday(year, month, day) && year >= 2000) {
    return true;
  }
  
  
  return false;
}

bool JpHoliday::isEquinoxHoliday(int year, int month, int day) {
  if (month == 3 && day == calculateVernalEquinoxDay(year)) {
    return true;
  }
  
  if (month == 9 && day == calculateAutumnalEquinoxDay(year)) {
    return true;
  }
  
  return false;
}

int JpHoliday::calculateVernalEquinoxDay(int year) {
  if (year >= 2000 && year <= 2030) {
    if (year >= 2000 && year <= 2099) {
      return static_cast<int>(20.8431 + 0.242194 * (year - 1980) - static_cast<int>((year - 1980) / 4));
    }
  }
  return 0; // Return 0 for unsupported years
}

int JpHoliday::calculateAutumnalEquinoxDay(int year) {
  if (year >= 2000 && year <= 2030) {
    if (year >= 2000 && year <= 2099) {
      return static_cast<int>(23.2488 + 0.242194 * (year - 1980) - static_cast<int>((year - 1980) / 4));
    }
  }
  return 0; // Return 0 for unsupported years
}

bool JpHoliday::isSecondMonday(int year, int month, int day) {
  return (day - 1) / 7 == 1 && getDayOfWeek(year, month, day) == 1;
}

bool JpHoliday::isThirdMonday(int year, int month, int day) {
  return (day - 1) / 7 == 2 && getDayOfWeek(year, month, day) == 1;
}

int JpHoliday::getDayOfWeek(int year, int month, int day) {
  if (month == 1 || month == 2) {
    month += 12;
    year--;
  }
  
  int h = (day + 13 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
  
  return (h + 6) % 7;
}
