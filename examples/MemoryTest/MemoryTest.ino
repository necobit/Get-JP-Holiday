/**
 * MemoryTest.ino - Example for JpHoliday library memory usage testing
 * 
 * This example demonstrates the memory-optimized JpHoliday library
 * and reports memory usage statistics.
 */

#include <JpHoliday.h>

JpHoliday holiday;
Holiday holidayList[30]; // Array to store holidays (max 30)

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("JpHoliday Library - Memory Optimization Test");
  Serial.println("------------------------------------------");
  
  // Print memory usage information
  Serial.print("Free RAM: ");
  Serial.print(freeRam());
  Serial.println(" bytes");
  
  // Test basic functionality to ensure optimization didn't break anything
  testBasicFunctionality();
  
  // Test holiday list functionality
  testHolidayList();
  
  Serial.println("\nMemory optimization test completed successfully!");
}

void loop() {
  // Nothing to do here
}

// Test basic holiday detection functionality
void testBasicFunctionality() {
  Serial.println("\nTesting basic functionality:");
  
  // Test fixed date holiday
  if (holiday.isHoliday(2025, 1, 1)) {
    Serial.println("✓ Fixed date holiday detection works (元日)");
  } else {
    Serial.println("✗ Fixed date holiday detection failed");
  }
  
  // Test variable date holiday
  if (holiday.isHoliday(2025, 1, 13)) {
    Serial.println("✓ Variable date holiday detection works (成人の日)");
  } else {
    Serial.println("✗ Variable date holiday detection failed");
  }
  
  // Test equinox holiday
  if (holiday.isHoliday(2025, 3, 21)) {
    Serial.println("✓ Equinox holiday detection works (春分の日)");
  } else {
    Serial.println("✗ Equinox holiday detection failed");
  }
  
  // Test substitute holiday
  if (holiday.isHoliday(2024, 2, 12)) {
    Serial.println("✓ Substitute holiday detection works (振替休日)");
  } else {
    Serial.println("✗ Substitute holiday detection failed");
  }
  
  // Test holiday name retrieval
  String name = holiday.getHolidayName(2025, 1, 1);
  if (name == "元日") {
    Serial.println("✓ Holiday name retrieval works");
  } else {
    Serial.println("✗ Holiday name retrieval failed");
  }
}

// Test holiday list functionality
void testHolidayList() {
  Serial.println("\nTesting holiday list functionality:");
  
  int year = 2025;
  int count = holiday.getHolidayList(year, holidayList, 30);
  
  Serial.print("Found ");
  Serial.print(count);
  Serial.print(" holidays in ");
  Serial.println(year);
  
  if (count > 0) {
    Serial.println("✓ Holiday list retrieval works");
    
    // Print first and last holiday to verify
    Serial.print("First holiday: ");
    Serial.print(holidayList[0].year);
    Serial.print("/");
    Serial.print(holidayList[0].month);
    Serial.print("/");
    Serial.print(holidayList[0].day);
    Serial.print(" - ");
    Serial.println(holidayList[0].getName());
    
    Serial.print("Last holiday: ");
    Serial.print(holidayList[count-1].year);
    Serial.print("/");
    Serial.print(holidayList[count-1].month);
    Serial.print("/");
    Serial.print(holidayList[count-1].day);
    Serial.print(" - ");
    Serial.println(holidayList[count-1].getName());
  } else {
    Serial.println("✗ Holiday list retrieval failed");
  }
}

// Function to calculate free RAM
int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
