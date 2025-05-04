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
  
  if (isRegularHoliday(year, month, day)) {
    return true;
  }
  
  if (isSubstituteHoliday(year, month, day)) {
    return true;
  }
  
  return false;
}

bool JpHoliday::isRegularHoliday(int year, int month, int day) {
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
  if (year < 2000 || year > 2030) {
    return "";
  }
  
  if (isSubstituteHoliday(year, month, day)) {
    return "振替休日";
  }
  
  switch (month) {
    case 1:  // January
      if (day == 1) {
        return "元日";  // New Year's Day
      }
      if (isSecondMonday(year, month, day)) {
        return "成人の日";  // Coming of Age Day
      }
      break;
      
    case 2:  // February
      if (day == 11) {
        return "建国記念の日";  // National Foundation Day
      }
      if (day == 23 && year >= 2020) {
        return "天皇誕生日";  // Emperor's Birthday (from 2020)
      }
      break;
      
    case 3:  // March
      if (day == calculateVernalEquinoxDay(year)) {
        return "春分の日";  // Vernal Equinox Day
      }
      break;
      
    case 4:  // April
      if (day == 29) {
        return "昭和の日";  // Showa Day
      }
      break;
      
    case 5:  // May
      if (day == 3) {
        return "憲法記念日";  // Constitution Memorial Day
      }
      if (day == 4) {
        return "みどりの日";  // Greenery Day
      }
      if (day == 5) {
        return "こどもの日";  // Children's Day
      }
      break;
      
    case 7:  // July
      if (year >= 2003) {
        if (isThirdMonday(year, month, day)) {
          return "海の日";  // Marine Day (third Monday from 2003)
        }
      } else if (day == 20) {
        return "海の日";  // Marine Day (July 20 until 2002)
      }
      break;
      
    case 8:  // August
      if (day == 11 && year >= 2016) {
        return "山の日";  // Mountain Day (from 2016)
      }
      break;
      
    case 9:  // September
      if (year >= 2003) {
        if (isThirdMonday(year, month, day)) {
          return "敬老の日";  // Respect for the Aged Day (third Monday from 2003)
        }
      } else if (day == 15) {
        return "敬老の日";  // Respect for the Aged Day (September 15 until 2002)
      }
      
      if (day == calculateAutumnalEquinoxDay(year)) {
        return "秋分の日";  // Autumnal Equinox Day
      }
      break;
      
    case 10:  // October
      if (isSecondMonday(year, month, day) && year >= 2000) {
        if (year >= 2020) {
          return "スポーツの日";  // Sports Day (from 2020)
        } else {
          return "体育の日";  // Health and Sports Day (until 2019)
        }
      }
      break;
      
    case 11:  // November
      if (day == 3) {
        return "文化の日";  // Culture Day
      }
      if (day == 23) {
        return "勤労感謝の日";  // Labor Thanksgiving Day
      }
      break;
      
    case 12:  // December
      if (day == 23 && year < 2019) {
        return "天皇誕生日";  // Emperor's Birthday (until 2018)
      }
      break;
  }
  
  return "";  // Not a holiday
}

bool JpHoliday::isSubstituteHoliday(int year, int month, int day) {
  if (year < 2000 || year > 2030) {
    return false;
  }
  
  int dayOfWeek = getDayOfWeek(year, month, day);
  
  if (dayOfWeek == 0) {
    return false;
  }
  
  if (dayOfWeek == 1) {
    int prevDay = day - 1;
    int prevMonth = month;
    int prevYear = year;
    
    if (prevDay < 1) {
      prevMonth--;
      if (prevMonth < 1) {
        prevMonth = 12;
        prevYear--;
      }
      
      switch (prevMonth) {
        case 2:
          if ((prevYear % 4 == 0 && prevYear % 100 != 0) || (prevYear % 400 == 0)) {
            prevDay = 29;
          } else {
            prevDay = 28;
          }
          break;
        case 4: case 6: case 9: case 11:
          prevDay = 30;
          break;
        default:
          prevDay = 31;
          break;
      }
    }
    
    if (isRegularHoliday(prevYear, prevMonth, prevDay)) {
      return true;
    }
    
    int prevDayOfWeek = getDayOfWeek(prevYear, prevMonth, prevDay);
    if (prevDayOfWeek == 0) {
      int prevPrevDay = prevDay - 1;
      int prevPrevMonth = prevMonth;
      int prevPrevYear = prevYear;
      
      if (prevPrevDay < 1) {
        prevPrevMonth--;
        if (prevPrevMonth < 1) {
          prevPrevMonth = 12;
          prevPrevYear--;
        }
        
        switch (prevPrevMonth) {
          case 2:
            if ((prevPrevYear % 4 == 0 && prevPrevYear % 100 != 0) || (prevPrevYear % 400 == 0)) {
              prevPrevDay = 29;
            } else {
              prevPrevDay = 28;
            }
            break;
          case 4: case 6: case 9: case 11:
            prevPrevDay = 30;
            break;
          default:
            prevPrevDay = 31;
            break;
        }
      }
      
      if (isRegularHoliday(prevPrevYear, prevPrevMonth, prevPrevDay)) {
        return true;
      }
    }
  }
  
  return false;
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
