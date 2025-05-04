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
  
  // Check if January 1, 2025 is a holiday (元日)
  if (holiday.isHoliday(2025, 1, 1)) {
    Serial.println("2025/1/1 is a holiday (元日)");
  } else {
    Serial.println("2025/1/1 is not a holiday");
  }
  
  // Check if January 13, 2025 is a holiday (成人の日 - second Monday of January)
  if (holiday.isHoliday(2025, 1, 13)) {
    Serial.println("2025/1/13 is a holiday (成人の日)");
  } else {
    Serial.println("2025/1/13 is not a holiday");
  }
  
  // Check if March 21, 2025 is a holiday (春分の日 - calculated)
  if (holiday.isHoliday(2025, 3, 21)) {
    Serial.println("2025/3/21 is a holiday (春分の日)");
  } else {
    Serial.println("2025/3/21 is not a holiday");
  }
  
  // Check if September 23, 2025 is a holiday (秋分の日 - calculated)
  if (holiday.isHoliday(2025, 9, 23)) {
    Serial.println("2025/9/23 is a holiday (秋分の日)");
  } else {
    Serial.println("2025/9/23 is not a holiday");
  }
}

void loop() {
  // Nothing to do here
}
