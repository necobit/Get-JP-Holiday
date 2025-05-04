/**
 * HolidayList.ino - Example for JpHoliday library
 * 
 * This example demonstrates how to retrieve a list of all Japanese holidays
 * for a specified year using the getHolidayList method.
 */

#include <JpHoliday.h>

JpHoliday holiday;
Holiday holidayList[50]; // Array to store holidays (max 50)

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("JpHoliday Library - Holiday List Example");
  Serial.println("---------------------------------------");
  
  // Get the list of holidays for 2025
  int year = 2025;
  int count = holiday.getHolidayList(year, holidayList, 50);
  
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
    Serial.println(holidayList[i].name);
  }
  
  Serial.println("\nHolidays by Month:");
  printHolidaysByMonth(year, holidayList, count);
  
  // Example for another year with substitute holidays
  Serial.println("\n\nHolidays in 2024 (with substitute holidays):");
  year = 2024;
  count = holiday.getHolidayList(year, holidayList, 50);
  
  for (int i = 0; i < count; i++) {
    Serial.print(holidayList[i].year);
    Serial.print("/");
    Serial.print(holidayList[i].month);
    Serial.print("/");
    Serial.print(holidayList[i].day);
    Serial.print(" - ");
    Serial.println(holidayList[i].name);
  }
}

void loop() {
  // Nothing to do here
}

// Helper function to print holidays grouped by month
void printHolidaysByMonth(int year, Holiday* holidays, int count) {
  for (int month = 1; month <= 12; month++) {
    bool hasHoliday = false;
    
    // Check if there are any holidays in this month
    for (int i = 0; i < count; i++) {
      if (holidays[i].month == month) {
        if (!hasHoliday) {
          // Print month header
          Serial.print("\nMonth ");
          Serial.print(month);
          Serial.println(":");
          hasHoliday = true;
        }
        
        // Print holiday
        Serial.print("  ");
        Serial.print(holidays[i].day);
        Serial.print(" - ");
        Serial.println(holidays[i].name);
      }
    }
  }
}
