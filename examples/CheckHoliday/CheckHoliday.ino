/**
 * CheckHoliday.ino - Example for JpHoliday library
 * 
 * This example demonstrates how to check if a specific date is a Japanese holiday
 * and how to get the name of the holiday.
 */

#include <JpHoliday.h>

JpHoliday holiday;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("JpHoliday Library Example");
  Serial.println("------------------------");
  
  // Check if January 1, 2025 is a holiday
  if (holiday.isHoliday(2025, 1, 1)) {
    Serial.print("2025/1/1 is ");
    Serial.println(holiday.getHolidayName(2025, 1, 1));
  } else {
    Serial.println("2025/1/1 is not a holiday");
  }
  
  // Check if February 12, 2024 is a holiday (substitute holiday for National Foundation Day)
  if (holiday.isHoliday(2024, 2, 12)) {
    Serial.print("2024/2/12 is ");
    Serial.println(holiday.getHolidayName(2024, 2, 12));
  } else {
    Serial.println("2024/2/12 is not a holiday");
  }
  
  // Check if May 6, 2024 is a holiday (substitute holiday for Children's Day)
  if (holiday.isHoliday(2024, 5, 6)) {
    Serial.print("2024/5/6 is ");
    Serial.println(holiday.getHolidayName(2024, 5, 6));
  } else {
    Serial.println("2024/5/6 is not a holiday");
  }
}

void loop() {
  // Nothing to do here
}
