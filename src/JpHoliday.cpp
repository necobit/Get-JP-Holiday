/**
 * JpHoliday.cpp - Arduino library for Japanese holiday detection
 * Created by Devin AI, May 4, 2025
 * Based on "国民の祝日に関する法律（昭和23年法律第178号）"
 */

#include "JpHoliday.h"

const char holiday_none[] PROGMEM = "";
const char holiday_new_year[] PROGMEM = "元日";
const char holiday_coming_of_age[] PROGMEM = "成人の日";
const char holiday_foundation[] PROGMEM = "建国記念の日";
const char holiday_emperor_birthday[] PROGMEM = "天皇誕生日";
const char holiday_vernal_equinox[] PROGMEM = "春分の日";
const char holiday_showa[] PROGMEM = "昭和の日";
const char holiday_constitution[] PROGMEM = "憲法記念日";
const char holiday_greenery[] PROGMEM = "みどりの日";
const char holiday_children[] PROGMEM = "こどもの日";
const char holiday_marine[] PROGMEM = "海の日";
const char holiday_mountain[] PROGMEM = "山の日";
const char holiday_respect_aged[] PROGMEM = "敬老の日";
const char holiday_autumnal_equinox[] PROGMEM = "秋分の日";
const char holiday_sports[] PROGMEM = "スポーツの日";
const char holiday_health_sports[] PROGMEM = "体育の日";
const char holiday_culture[] PROGMEM = "文化の日";
const char holiday_labor_thanksgiving[] PROGMEM = "勤労感謝の日";
const char holiday_substitute[] PROGMEM = "振替休日";

const char* const holiday_names[] PROGMEM = {
  holiday_none,
  holiday_new_year,
  holiday_coming_of_age,
  holiday_foundation,
  holiday_emperor_birthday,
  holiday_vernal_equinox,
  holiday_showa,
  holiday_constitution,
  holiday_greenery,
  holiday_children,
  holiday_marine,
  holiday_mountain,
  holiday_respect_aged,
  holiday_autumnal_equinox,
  holiday_sports,
  holiday_health_sports,
  holiday_culture,
  holiday_labor_thanksgiving,
  holiday_substitute
};

const FixedHoliday fixed_holidays[] PROGMEM = {
  {1, 1, 2000, 2030, HOLIDAY_NEW_YEAR},           // 元日 (New Year's Day)
  {2, 11, 2000, 2030, HOLIDAY_FOUNDATION},        // 建国記念の日 (National Foundation Day)
  {2, 23, 2020, 2030, HOLIDAY_EMPEROR_BIRTHDAY},  // 天皇誕生日 (Emperor's Birthday from 2020)
  {4, 29, 2000, 2030, HOLIDAY_SHOWA},             // 昭和の日 (Showa Day)
  {5, 3, 2000, 2030, HOLIDAY_CONSTITUTION},       // 憲法記念日 (Constitution Memorial Day)
  {5, 4, 2000, 2030, HOLIDAY_GREENERY},           // みどりの日 (Greenery Day)
  {5, 5, 2000, 2030, HOLIDAY_CHILDREN},           // こどもの日 (Children's Day)
  {8, 11, 2016, 2030, HOLIDAY_MOUNTAIN},          // 山の日 (Mountain Day from 2016)
  {11, 3, 2000, 2030, HOLIDAY_CULTURE},           // 文化の日 (Culture Day)
  {11, 23, 2000, 2030, HOLIDAY_LABOR_THANKSGIVING}, // 勤労感謝の日 (Labor Thanksgiving Day)
  {12, 23, 2000, 2018, HOLIDAY_EMPEROR_BIRTHDAY}  // 天皇誕生日 (Emperor's Birthday until 2018)
};

const uint8_t FIXED_HOLIDAY_COUNT = sizeof(fixed_holidays) / sizeof(FixedHoliday);

const uint8_t DAYS_IN_MONTH[] PROGMEM = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

String Holiday::getName() const {
  return JpHoliday::getHolidayNameFromIndex(nameIndex);
}

JpHoliday::JpHoliday() {
}

String JpHoliday::getHolidayNameFromIndex(uint8_t nameIndex) {
  if (nameIndex >= sizeof(holiday_names) / sizeof(char*)) {
    return "";
  }
  
  const char* namePtr;
  memcpy_P(&namePtr, &holiday_names[nameIndex], sizeof(char*));
  
  String result;
  char c;
  while ((c = pgm_read_byte(namePtr++)) != 0) {
    result += c;
  }
  
  return result;
}

bool JpHoliday::isHoliday(uint16_t year, uint8_t month, uint8_t day) {
  if (year < 2000 || year > 2030) {
    return false;
  }
  
  return isRegularHoliday(year, month, day) || isSubstituteHoliday(year, month, day);
}

uint8_t JpHoliday::getHolidayList(uint16_t year, Holiday* holidays, uint8_t maxHolidays) {
  if (year < 2000 || year > 2030 || holidays == NULL || maxHolidays == 0) {
    return 0;
  }
  
  uint8_t count = 0;
  
  for (uint8_t month = 1; month <= 12; month++) {
    uint8_t daysInMonth = getDaysInMonth(year, month);
    
    for (uint8_t day = 1; day <= daysInMonth; day++) {
      uint8_t nameIndex = getHolidayNameIndex(year, month, day);
      if (nameIndex > 0) {
        if (count >= maxHolidays) {
          return count;
        }
        
        holidays[count].year = year;
        holidays[count].month = month;
        holidays[count].day = day;
        holidays[count].nameIndex = nameIndex;
        
        count++;
      }
    }
  }
  
  return count;
}

bool JpHoliday::isRegularHoliday(uint16_t year, uint8_t month, uint8_t day) {
  return isFixedDateHoliday(year, month, day) || 
         isVariableDateHoliday(year, month, day) || 
         isEquinoxHoliday(year, month, day);
}

String JpHoliday::getHolidayName(uint16_t year, uint8_t month, uint8_t day) {
  uint8_t nameIndex = getHolidayNameIndex(year, month, day);
  return getHolidayNameFromIndex(nameIndex);
}

uint8_t JpHoliday::getHolidayNameIndex(uint16_t year, uint8_t month, uint8_t day) {
  if (year < 2000 || year > 2030) {
    return HOLIDAY_NONE;
  }
  
  if (isSubstituteHoliday(year, month, day)) {
    return HOLIDAY_SUBSTITUTE;
  }
  
  for (uint8_t i = 0; i < FIXED_HOLIDAY_COUNT; i++) {
    FixedHoliday holiday;
    memcpy_P(&holiday, &fixed_holidays[i], sizeof(FixedHoliday));
    
    if (month == holiday.month && day == holiday.day && 
        year >= holiday.startYear && year <= holiday.endYear) {
      return holiday.nameIndex;
    }
  }
  
  if (month == 1 && isSecondMonday(year, month, day)) {
    return HOLIDAY_COMING_OF_AGE;
  }
  
  if (month == 7) {
    if (year >= 2003 && isThirdMonday(year, month, day)) {
      return HOLIDAY_MARINE;
    } else if (year < 2003 && day == 20) {
      return HOLIDAY_MARINE;
    }
  }
  
  if (month == 9) {
    if (year >= 2003 && isThirdMonday(year, month, day)) {
      return HOLIDAY_RESPECT_AGED;
    } else if (year < 2003 && day == 15) {
      return HOLIDAY_RESPECT_AGED;
    }
    
    if (day == calculateAutumnalEquinoxDay(year)) {
      return HOLIDAY_AUTUMNAL_EQUINOX;
    }
  }
  
  if (month == 10 && isSecondMonday(year, month, day) && year >= 2000) {
    return (year >= 2020) ? HOLIDAY_SPORTS : HOLIDAY_HEALTH_SPORTS;
  }
  
  if (month == 3 && day == calculateVernalEquinoxDay(year)) {
    return HOLIDAY_VERNAL_EQUINOX;
  }
  
  return HOLIDAY_NONE;
}

bool JpHoliday::isSubstituteHoliday(uint16_t year, uint8_t month, uint8_t day) {
  if (year < 2000 || year > 2030) {
    return false;
  }
  
  uint8_t dayOfWeek = getDayOfWeek(year, month, day);
  
  if (dayOfWeek != 1) {
    return false;
  }
  
  // Check if the previous day was a holiday
  uint16_t prevYear = year;
  uint8_t prevMonth = month;
  uint8_t prevDay = day - 1;
  
  if (prevDay == 0) {
    prevMonth--;
    if (prevMonth == 0) {
      prevMonth = 12;
      prevYear--;
    }
    prevDay = getDaysInMonth(prevYear, prevMonth);
  }
  
  if (isRegularHoliday(prevYear, prevMonth, prevDay)) {
    return true;
  }
  
  if (getDayOfWeek(prevYear, prevMonth, prevDay) == 0) {
    uint16_t prevPrevYear = prevYear;
    uint8_t prevPrevMonth = prevMonth;
    uint8_t prevPrevDay = prevDay - 1;
    
    if (prevPrevDay == 0) {
      prevPrevMonth--;
      if (prevPrevMonth == 0) {
        prevPrevMonth = 12;
        prevPrevYear--;
      }
      prevPrevDay = getDaysInMonth(prevPrevYear, prevPrevMonth);
    }
    
    if (isRegularHoliday(prevPrevYear, prevPrevMonth, prevPrevDay)) {
      return true;
    }
  }
  
  return false;
}

bool JpHoliday::isFixedDateHoliday(uint16_t year, uint8_t month, uint8_t day) {
  for (uint8_t i = 0; i < FIXED_HOLIDAY_COUNT; i++) {
    FixedHoliday holiday;
    memcpy_P(&holiday, &fixed_holidays[i], sizeof(FixedHoliday));
    
    if (month == holiday.month && day == holiday.day && 
        year >= holiday.startYear && year <= holiday.endYear) {
      return true;
    }
  }
  
  return false;
}

bool JpHoliday::isVariableDateHoliday(uint16_t year, uint8_t month, uint8_t day) {
  if (month == 1 && isSecondMonday(year, month, day)) {
    return true;
  }
  
  if (month == 7) {
    if (year >= 2003 && isThirdMonday(year, month, day)) {
      return true;  // Third Monday of July from 2003
    } else if (year < 2003 && day == 20) {
      return true;  // July 20 until 2002
    }
  }
  
  if (month == 9) {
    if (year >= 2003 && isThirdMonday(year, month, day)) {
      return true;  // Third Monday of September from 2003
    } else if (year < 2003 && day == 15) {
      return true;  // September 15 until 2002
    }
  }
  
  if (month == 10 && isSecondMonday(year, month, day) && year >= 2000) {
    return true;
  }
  
  return false;
}

bool JpHoliday::isEquinoxHoliday(uint16_t year, uint8_t month, uint8_t day) {
  if (month == 3 && day == calculateVernalEquinoxDay(year)) {
    return true;
  }
  
  if (month == 9 && day == calculateAutumnalEquinoxDay(year)) {
    return true;
  }
  
  return false;
}

uint8_t JpHoliday::calculateVernalEquinoxDay(uint16_t year) {
  if (year < 2000 || year > 2030) {
    return 0;
  }
  
  return (uint8_t)(20.8431 + 0.242194 * (year - 1980) - ((year - 1980) >> 2));
}

uint8_t JpHoliday::calculateAutumnalEquinoxDay(uint16_t year) {
  if (year < 2000 || year > 2030) {
    return 0;
  }
  
  return (uint8_t)(23.2488 + 0.242194 * (year - 1980) - ((year - 1980) >> 2));
}

bool JpHoliday::isSecondMonday(uint16_t year, uint8_t month, uint8_t day) {
  return ((day - 1) >> 3) == 1 && getDayOfWeek(year, month, day) == 1;
}

bool JpHoliday::isThirdMonday(uint16_t year, uint8_t month, uint8_t day) {
  return ((day - 1) >> 3) == 2 && getDayOfWeek(year, month, day) == 1;
}

uint8_t JpHoliday::getDayOfWeek(uint16_t year, uint8_t month, uint8_t day) {
  if (month < 3) {
    month += 12;
    year--;
  }
  
  uint16_t y = year % 100;
  uint16_t c = year / 100;
  
  uint8_t w = (day + ((month + 1) * 26) / 10 + y + (y >> 2) + (c >> 2) + (c * 5)) % 7;
  
  return (w + 6) % 7;  // Adjust to make Sunday = 0
}

uint8_t JpHoliday::getDaysInMonth(uint16_t year, uint8_t month) {
  uint8_t days = pgm_read_byte(&DAYS_IN_MONTH[month]);
  
  if (month == 2 && isLeapYear(year)) {
    return 29;
  }
  
  return days;
}

bool JpHoliday::isLeapYear(uint16_t year) {
  return ((year & 3) == 0 && year % 100 != 0) || (year % 400 == 0);
}
