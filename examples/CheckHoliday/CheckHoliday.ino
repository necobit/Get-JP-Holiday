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
  
  Serial.println("\nFixed Date Holidays:");
  // Check if January 1, 2025 is a holiday (元日)
  checkAndPrintHoliday(2025, 1, 1);
  // Check if February 11, 2025 is a holiday (建国記念の日)
  checkAndPrintHoliday(2025, 2, 11);
  // Check if February 23, 2025 is a holiday (天皇誕生日)
  checkAndPrintHoliday(2025, 2, 23);
  // Check if April 29, 2025 is a holiday (昭和の日)
  checkAndPrintHoliday(2025, 4, 29);
  // Check if May 3, 2025 is a holiday (憲法記念日)
  checkAndPrintHoliday(2025, 5, 3);
  // Check if May 4, 2025 is a holiday (みどりの日)
  checkAndPrintHoliday(2025, 5, 4);
  // Check if May 5, 2025 is a holiday (こどもの日)
  checkAndPrintHoliday(2025, 5, 5);
  // Check if August 11, 2025 is a holiday (山の日)
  checkAndPrintHoliday(2025, 8, 11);
  // Check if November 3, 2025 is a holiday (文化の日)
  checkAndPrintHoliday(2025, 11, 3);
  // Check if November 23, 2025 is a holiday (勤労感謝の日)
  checkAndPrintHoliday(2025, 11, 23);
  
  Serial.println("\nVariable Date Holidays:");
  // Check if January 13, 2025 is a holiday (成人の日 - second Monday of January)
  checkAndPrintHoliday(2025, 1, 13);
  // Check if July 21, 2025 is a holiday (海の日 - third Monday of July)
  checkAndPrintHoliday(2025, 7, 21);
  // Check if September 15, 2025 is a holiday (敬老の日 - third Monday of September)
  checkAndPrintHoliday(2025, 9, 15);
  // Check if October 13, 2025 is a holiday (スポーツの日 - second Monday of October)
  checkAndPrintHoliday(2025, 10, 13);
  
  Serial.println("\nEquinox Holidays:");
  // Check if March 21, 2025 is a holiday (春分の日 - calculated)
  checkAndPrintHoliday(2025, 3, 21);
  // Check if September 23, 2025 is a holiday (秋分の日 - calculated)
  checkAndPrintHoliday(2025, 9, 23);
  
  Serial.println("\nSubstitute Holiday Examples:");
  // February 12, 2024 is a substitute holiday for National Foundation Day (Feb 11, 2024 is Sunday)
  checkAndPrintHoliday(2024, 2, 11); // National Foundation Day (Sunday)
  checkAndPrintHoliday(2024, 2, 12); // Substitute Holiday (Monday)
  
  // May 6, 2024 is a substitute holiday for Children's Day (May 5, 2024 is Sunday)
  checkAndPrintHoliday(2024, 5, 5);  // Children's Day (Sunday)
  checkAndPrintHoliday(2024, 5, 6);  // Substitute Holiday (Monday)
  
  // July 15, 2024 is a substitute holiday for Marine Day (July 14, 2024 is Sunday)
  checkAndPrintHoliday(2024, 7, 14); // Marine Day (Sunday)
  checkAndPrintHoliday(2024, 7, 15); // Substitute Holiday (Monday)
  
  Serial.println("\nNon-Holiday Examples:");
  // Check if January 2, 2025 is a holiday (not a holiday)
  checkAndPrintHoliday(2025, 1, 2);
  // Check if December 25, 2025 is a holiday (not a holiday in Japan)
  checkAndPrintHoliday(2025, 12, 25);
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
