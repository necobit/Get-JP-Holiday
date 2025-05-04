# JpHoliday Examples

This document provides examples of how to use the JpHoliday Arduino library.

## Basic Holiday Detection

This example demonstrates how to check if a specific date is a holiday and get its name.

```cpp
#include <JpHoliday.h>

JpHoliday holiday;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  // Check if January 1, 2025 is a holiday
  if (holiday.isHoliday(2025, 1, 1)) {
    Serial.print("2025/1/1 is ");
    Serial.print(holiday.getHolidayName(2025, 1, 1));
    Serial.println(" (holiday)");
  } else {
    Serial.println("2025/1/1 is not a holiday");
  }
}

void loop() {
  // Nothing to do here
}
```

## Checking Multiple Holidays

This example demonstrates how to check multiple holidays.

```cpp
#include <JpHoliday.h>

JpHoliday holiday;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  Serial.println("Fixed Date Holidays:");
  checkAndPrintHoliday(2025, 1, 1);   // 元日 (New Year's Day)
  checkAndPrintHoliday(2025, 2, 11);  // 建国記念の日 (National Foundation Day)
  checkAndPrintHoliday(2025, 2, 23);  // 天皇誕生日 (Emperor's Birthday)
  
  Serial.println("\nVariable Date Holidays:");
  checkAndPrintHoliday(2025, 1, 13);  // 成人の日 (Coming of Age Day)
  checkAndPrintHoliday(2025, 7, 21);  // 海の日 (Marine Day)
  
  Serial.println("\nEquinox Holidays:");
  checkAndPrintHoliday(2025, 3, 21);  // 春分の日 (Vernal Equinox Day)
  checkAndPrintHoliday(2025, 9, 23);  // 秋分の日 (Autumnal Equinox Day)
  
  Serial.println("\nSubstitute Holiday Example:");
  checkAndPrintHoliday(2024, 2, 11);  // 建国記念の日 (Sunday)
  checkAndPrintHoliday(2024, 2, 12);  // 振替休日 (Substitute Holiday)
}

void loop() {
  // Nothing to do here
}

// Helper function to check and print holiday information
void checkAndPrintHoliday(int year, int month, int day) {
  if (holiday.isHoliday(year, month, day)) {
    String name = holiday.getHolidayName(year, month, day);
    Serial.print(year);
    Serial.print("/");
    Serial.print(month);
    Serial.print("/");
    Serial.print(day);
    Serial.print(" is ");
    Serial.print(name);
    Serial.println(" (holiday)");
  } else {
    Serial.print(year);
    Serial.print("/");
    Serial.print(month);
    Serial.print("/");
    Serial.print(day);
    Serial.println(" is not a holiday");
  }
}
```

## Getting a List of Holidays

This example demonstrates how to get a list of all holidays for a specific year.

```cpp
#include <JpHoliday.h>

JpHoliday holiday;
Holiday holidayList[30]; // Array to store holidays (max 30)

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  // Get the list of holidays for 2025
  int year = 2025;
  int count = holiday.getHolidayList(year, holidayList, 30);
  
  Serial.print("Found ");
  Serial.print(count);
  Serial.print(" holidays in ");
  Serial.print(year);
  Serial.println(":");
  
  // Print all holidays
  for (int i = 0; i < count; i++) {
    Serial.print(holidayList[i].year);
    Serial.print("/");
    Serial.print(holidayList[i].month);
    Serial.print("/");
    Serial.print(holidayList[i].day);
    Serial.print(" - ");
    Serial.println(holidayList[i].getName());
  }
}

void loop() {
  // Nothing to do here
}
```

## Memory Optimization Example

This example demonstrates how to use the library with memory optimization in mind.

```cpp
#include <JpHoliday.h>

JpHoliday holiday;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  // Use uint8_t and uint16_t types for memory efficiency
  uint16_t year = 2025;
  uint8_t month = 1;
  uint8_t day = 1;
  
  // Check if the date is a holiday
  if (holiday.isHoliday(year, month, day)) {
    // Get the holiday name only when needed
    String name = holiday.getHolidayName(year, month, day);
    Serial.print(year);
    Serial.print("/");
    Serial.print(month);
    Serial.print("/");
    Serial.print(day);
    Serial.print(" is ");
    Serial.print(name);
    Serial.println(" (holiday)");
  }
  
  // Process holidays for a specific month only
  processHolidaysForMonth(2025, 5); // May 2025
}

void loop() {
  // Nothing to do here
}

// Process holidays for a specific month to save memory
void processHolidaysForMonth(uint16_t year, uint8_t month) {
  Serial.print("Holidays in ");
  Serial.print(year);
  Serial.print("/");
  Serial.print(month);
  Serial.println(":");
  
  // Get days in month
  uint8_t daysInMonth = 31; // Simplified for example
  if (month == 2) {
    daysInMonth = 28;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
      daysInMonth = 29; // Leap year
    }
  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
    daysInMonth = 30;
  }
  
  // Check each day in the month
  for (uint8_t day = 1; day <= daysInMonth; day++) {
    if (holiday.isHoliday(year, month, day)) {
      Serial.print("  ");
      Serial.print(day);
      Serial.print(": ");
      Serial.println(holiday.getHolidayName(year, month, day));
    }
  }
}
```
