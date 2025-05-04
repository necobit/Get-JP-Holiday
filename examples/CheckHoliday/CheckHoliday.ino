/**
 * CheckHoliday.ino - Example for JpHoliday library
 * 
 * This example demonstrates how to check if a specific date is a Japanese holiday
 * and how to get the name of the holiday, including substitute holidays.
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
  
  // Check if January 1, 2025 is a holiday (元日)
  checkAndPrintHoliday(2025, 1, 1);
  
  // Check if January 13, 2025 is a holiday (成人の日 - second Monday of January)
  checkAndPrintHoliday(2025, 1, 13);
  
  // Check if March 21, 2025 is a holiday (春分の日 - calculated)
  checkAndPrintHoliday(2025, 3, 21);
  
  // Check if September 23, 2025 is a holiday (秋分の日 - calculated)
  checkAndPrintHoliday(2025, 9, 23);
  
  // Check substitute holiday examples
  
  // February 12, 2024 is a substitute holiday for National Foundation Day (Feb 11, 2024 is Sunday)
  Serial.println("\nSubstitute Holiday Examples:");
  checkAndPrintHoliday(2024, 2, 11); // National Foundation Day (Sunday)
  checkAndPrintHoliday(2024, 2, 12); // Substitute Holiday (Monday)
  
  // May 6, 2024 is a substitute holiday for Children's Day (May 5, 2024 is Sunday)
  checkAndPrintHoliday(2024, 5, 5);  // Children's Day (Sunday)
  checkAndPrintHoliday(2024, 5, 6);  // Substitute Holiday (Monday)
  
  // July 15, 2024 is a substitute holiday for Marine Day (July 14, 2024 is Sunday)
  checkAndPrintHoliday(2024, 7, 14); // Marine Day (Sunday)
  checkAndPrintHoliday(2024, 7, 15); // Substitute Holiday (Monday)
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
