/**
 * JpHolidayTest.ino - Test suite for JpHoliday library
 * 
 * This sketch runs a comprehensive test suite for the JpHoliday library,
 * verifying all functionality including holiday detection, holiday names,
 * and holiday lists.
 */

#include <JpHoliday.h>

JpHoliday holiday;
Holiday holidayList[50]; // Array to store holidays (max 50)

// Test result counters
int totalTests = 0;
int passedTests = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("JpHoliday Library - Test Suite");
  Serial.println("==============================");
  
  // Run all tests
  testFixedDateHolidays();
  testVariableDateHolidays();
  testEquinoxHolidays();
  testSubstituteHolidays();
  testHolidayNames();
  testHolidayList();
  testEdgeCases();
  testMemoryUsage();
  
  // Print test summary
  Serial.println("\n==============================");
  Serial.print("Test Summary: ");
  Serial.print(passedTests);
  Serial.print("/");
  Serial.print(totalTests);
  Serial.print(" tests passed (");
  Serial.print((float)passedTests / totalTests * 100);
  Serial.println("%)");
  
  if (passedTests == totalTests) {
    Serial.println("All tests passed!");
  } else {
    Serial.print("Failed ");
    Serial.print(totalTests - passedTests);
    Serial.println(" tests.");
  }
}

void loop() {
  // Nothing to do here
}

// Test fixed date holidays
void testFixedDateHolidays() {
  Serial.println("\n1. Testing Fixed Date Holidays");
  
  // Test New Year's Day (元日)
  assertIsHoliday(2025, 1, 1, "元日");
  
  // Test National Foundation Day (建国記念の日)
  assertIsHoliday(2025, 2, 11, "建国記念の日");
  
  // Test Emperor's Birthday (天皇誕生日)
  assertIsHoliday(2025, 2, 23, "天皇誕生日");
  assertIsNotHoliday(2019, 2, 23, "Emperor's Birthday should not be on Feb 23 before 2020");
  assertIsHoliday(2018, 12, 23, "天皇誕生日");
  assertIsNotHoliday(2020, 12, 23, "Emperor's Birthday should not be on Dec 23 from 2020");
  
  // Test Showa Day (昭和の日)
  assertIsHoliday(2025, 4, 29, "昭和の日");
  
  // Test Constitution Memorial Day (憲法記念日)
  assertIsHoliday(2025, 5, 3, "憲法記念日");
  
  // Test Greenery Day (みどりの日)
  assertIsHoliday(2025, 5, 4, "みどりの日");
  
  // Test Children's Day (こどもの日)
  assertIsHoliday(2025, 5, 5, "こどもの日");
  
  // Test Mountain Day (山の日)
  assertIsHoliday(2025, 8, 11, "山の日");
  assertIsNotHoliday(2015, 8, 11, "Mountain Day should not exist before 2016");
  
  // Test Culture Day (文化の日)
  assertIsHoliday(2025, 11, 3, "文化の日");
  
  // Test Labor Thanksgiving Day (勤労感謝の日)
  assertIsHoliday(2025, 11, 23, "勤労感謝の日");
}

// Test variable date holidays
void testVariableDateHolidays() {
  Serial.println("\n2. Testing Variable Date Holidays");
  
  // Test Coming of Age Day (成人の日) - second Monday of January
  assertIsHoliday(2025, 1, 13, "成人の日"); // 2025-01-13 is the second Monday
  assertIsNotHoliday(2025, 1, 6, "First Monday of January should not be Coming of Age Day");
  assertIsNotHoliday(2025, 1, 20, "Third Monday of January should not be Coming of Age Day");
  
  // Test Marine Day (海の日) - third Monday of July
  assertIsHoliday(2025, 7, 21, "海の日"); // 2025-07-21 is the third Monday
  assertIsNotHoliday(2025, 7, 14, "Second Monday of July should not be Marine Day");
  assertIsNotHoliday(2025, 7, 28, "Fourth Monday of July should not be Marine Day");
  
  // Test Respect for the Aged Day (敬老の日) - third Monday of September
  assertIsHoliday(2025, 9, 15, "敬老の日"); // 2025-09-15 is the third Monday
  assertIsNotHoliday(2025, 9, 8, "Second Monday of September should not be Respect for the Aged Day");
  assertIsNotHoliday(2025, 9, 22, "Fourth Monday of September should not be Respect for the Aged Day");
  
  // Test Sports Day (スポーツの日) - second Monday of October
  assertIsHoliday(2025, 10, 13, "スポーツの日"); // 2025-10-13 is the second Monday
  assertIsNotHoliday(2025, 10, 6, "First Monday of October should not be Sports Day");
  assertIsNotHoliday(2025, 10, 20, "Third Monday of October should not be Sports Day");
  
  // Test pre-2000 fixed date for Coming of Age Day
  assertIsHoliday(1999, 1, 15, "成人の日");
  assertIsNotHoliday(1999, 1, 11, "Second Monday of January 1999 should not be Coming of Age Day");
  
  // Test pre-2003 fixed date for Marine Day
  assertIsHoliday(2002, 7, 20, "海の日");
  assertIsNotHoliday(2002, 7, 15, "Third Monday of July 2002 should not be Marine Day");
  
  // Test pre-2003 fixed date for Respect for the Aged Day
  assertIsHoliday(2002, 9, 15, "敬老の日");
  assertIsNotHoliday(2002, 9, 16, "Third Monday of September 2002 should not be Respect for the Aged Day");
  
  // Test Health and Sports Day (体育の日) before 2020
  assertIsHoliday(2019, 10, 14, "体育の日"); // 2019-10-14 is the second Monday
  assertIsNotHoliday(2019, 10, 7, "First Monday of October 2019 should not be Health and Sports Day");
}

// Test equinox holidays
void testEquinoxHolidays() {
  Serial.println("\n3. Testing Equinox Holidays");
  
  // Test Vernal Equinox Day (春分の日) for various years
  assertIsHoliday(2020, 3, 20, "春分の日");
  assertIsHoliday(2021, 3, 20, "春分の日");
  assertIsHoliday(2022, 3, 21, "春分の日");
  assertIsHoliday(2023, 3, 21, "春分の日");
  assertIsHoliday(2024, 3, 20, "春分の日");
  assertIsHoliday(2025, 3, 20, "春分の日");
  
  // Test Autumnal Equinox Day (秋分の日) for various years
  assertIsHoliday(2020, 9, 22, "秋分の日");
  assertIsHoliday(2021, 9, 23, "秋分の日");
  assertIsHoliday(2022, 9, 23, "秋分の日");
  assertIsHoliday(2023, 9, 23, "秋分の日");
  assertIsHoliday(2024, 9, 22, "秋分の日");
  assertIsHoliday(2025, 9, 23, "秋分の日");
  
  // Test days before and after equinox
  assertIsNotHoliday(2025, 3, 19, "Day before Vernal Equinox should not be a holiday");
  assertIsNotHoliday(2025, 3, 21, "Day after Vernal Equinox should not be a holiday");
  assertIsNotHoliday(2025, 9, 22, "Day before Autumnal Equinox should not be a holiday");
  assertIsNotHoliday(2025, 9, 24, "Day after Autumnal Equinox should not be a holiday");
}

// Test substitute holidays
void testSubstituteHolidays() {
  Serial.println("\n4. Testing Substitute Holidays");
  
  // Test substitute holiday for New Year's Day
  assertIsHoliday(2023, 1, 1, "元日"); // Sunday
  assertIsHoliday(2023, 1, 2, "振替休日"); // Monday
  
  // Test substitute holiday for National Foundation Day
  assertIsHoliday(2024, 2, 11, "建国記念の日"); // Sunday
  assertIsHoliday(2024, 2, 12, "振替休日"); // Monday
  
  // Test substitute holiday for Children's Day
  assertIsHoliday(2024, 5, 5, "こどもの日"); // Sunday
  assertIsHoliday(2024, 5, 6, "振替休日"); // Monday
  
  // Test substitute holiday for Marine Day
  assertIsHoliday(2024, 7, 14, "海の日"); // Sunday (third Monday falls on 15th)
  assertIsHoliday(2024, 7, 15, "振替休日"); // Monday
  
  // Test substitute holiday for Mountain Day
  assertIsHoliday(2030, 8, 11, "山の日"); // Sunday
  assertIsHoliday(2030, 8, 12, "振替休日"); // Monday
  
  // Test substitute holiday for Respect for the Aged Day
  assertIsHoliday(2030, 9, 15, "敬老の日"); // Sunday (third Monday falls on 16th)
  assertIsHoliday(2030, 9, 16, "振替休日"); // Monday
  
  // Test substitute holiday for Culture Day
  assertIsHoliday(2024, 11, 3, "文化の日"); // Sunday
  assertIsHoliday(2024, 11, 4, "振替休日"); // Monday
  
  // Test substitute holiday for Labor Thanksgiving Day
  assertIsHoliday(2024, 11, 23, "勤労感謝の日"); // Saturday
  assertIsNotHoliday(2024, 11, 24, "No substitute holiday for Saturday holidays");
  assertIsNotHoliday(2024, 11, 25, "No substitute holiday for Saturday holidays");
  
  // Test consecutive holidays with substitute holiday
  assertIsHoliday(2025, 5, 3, "憲法記念日"); // Saturday
  assertIsHoliday(2025, 5, 4, "みどりの日"); // Sunday
  assertIsHoliday(2025, 5, 5, "こどもの日"); // Monday
  assertIsHoliday(2025, 5, 6, "振替休日"); // Tuesday (substitute for Sunday)
}

// Test holiday names
void testHolidayNames() {
  Serial.println("\n5. Testing Holiday Names");
  
  // Test fixed date holiday names
  assertEqual(holiday.getHolidayName(2025, 1, 1), "元日", "New Year's Day name");
  assertEqual(holiday.getHolidayName(2025, 2, 11), "建国記念の日", "National Foundation Day name");
  assertEqual(holiday.getHolidayName(2025, 2, 23), "天皇誕生日", "Emperor's Birthday name");
  assertEqual(holiday.getHolidayName(2025, 4, 29), "昭和の日", "Showa Day name");
  assertEqual(holiday.getHolidayName(2025, 5, 3), "憲法記念日", "Constitution Memorial Day name");
  assertEqual(holiday.getHolidayName(2025, 5, 4), "みどりの日", "Greenery Day name");
  assertEqual(holiday.getHolidayName(2025, 5, 5), "こどもの日", "Children's Day name");
  assertEqual(holiday.getHolidayName(2025, 8, 11), "山の日", "Mountain Day name");
  assertEqual(holiday.getHolidayName(2025, 11, 3), "文化の日", "Culture Day name");
  assertEqual(holiday.getHolidayName(2025, 11, 23), "勤労感謝の日", "Labor Thanksgiving Day name");
  
  // Test variable date holiday names
  assertEqual(holiday.getHolidayName(2025, 1, 13), "成人の日", "Coming of Age Day name");
  assertEqual(holiday.getHolidayName(2025, 7, 21), "海の日", "Marine Day name");
  assertEqual(holiday.getHolidayName(2025, 9, 15), "敬老の日", "Respect for the Aged Day name");
  assertEqual(holiday.getHolidayName(2025, 10, 13), "スポーツの日", "Sports Day name");
  
  // Test equinox holiday names
  assertEqual(holiday.getHolidayName(2025, 3, 20), "春分の日", "Vernal Equinox Day name");
  assertEqual(holiday.getHolidayName(2025, 9, 23), "秋分の日", "Autumnal Equinox Day name");
  
  // Test substitute holiday name
  assertEqual(holiday.getHolidayName(2024, 2, 12), "振替休日", "Substitute Holiday name");
  
  // Test non-holiday
  assertEqual(holiday.getHolidayName(2025, 1, 2), "", "Non-holiday should return empty string");
  
  // Test Health and Sports Day vs Sports Day name change
  assertEqual(holiday.getHolidayName(2019, 10, 14), "体育の日", "Health and Sports Day name (before 2020)");
  assertEqual(holiday.getHolidayName(2020, 10, 12), "スポーツの日", "Sports Day name (from 2020)");
}

// Test holiday list
void testHolidayList() {
  Serial.println("\n6. Testing Holiday List");
  
  // Test holiday list for 2025
  int count = holiday.getHolidayList(2025, holidayList, 50);
  
  // Check if we got the expected number of holidays
  // 2025 should have 16 regular holidays plus possibly some substitute holidays
  assertTrue(count >= 16, "2025 should have at least 16 holidays");
  
  // Check if the first holiday is New Year's Day
  assertEqual(holidayList[0].year, 2025, "First holiday year");
  assertEqual(holidayList[0].month, 1, "First holiday month");
  assertEqual(holidayList[0].day, 1, "First holiday day");
  assertEqual(holidayList[0].getName(), "元日", "First holiday name");
  
  // Check if the list contains all expected holidays
  bool hasNewYear = false;
  bool hasComingOfAge = false;
  bool hasFoundation = false;
  bool hasEmperorBirthday = false;
  bool hasVernalEquinox = false;
  bool hasShowa = false;
  bool hasConstitution = false;
  bool hasGreenery = false;
  bool hasChildren = false;
  bool hasMarine = false;
  bool hasMountain = false;
  bool hasRespectAged = false;
  bool hasAutumnalEquinox = false;
  bool hasSports = false;
  bool hasCulture = false;
  bool hasLaborThanksgiving = false;
  
  for (int i = 0; i < count; i++) {
    String name = holidayList[i].getName();
    if (name == "元日") hasNewYear = true;
    else if (name == "成人の日") hasComingOfAge = true;
    else if (name == "建国記念の日") hasFoundation = true;
    else if (name == "天皇誕生日") hasEmperorBirthday = true;
    else if (name == "春分の日") hasVernalEquinox = true;
    else if (name == "昭和の日") hasShowa = true;
    else if (name == "憲法記念日") hasConstitution = true;
    else if (name == "みどりの日") hasGreenery = true;
    else if (name == "こどもの日") hasChildren = true;
    else if (name == "海の日") hasMarine = true;
    else if (name == "山の日") hasMountain = true;
    else if (name == "敬老の日") hasRespectAged = true;
    else if (name == "秋分の日") hasAutumnalEquinox = true;
    else if (name == "スポーツの日") hasSports = true;
    else if (name == "文化の日") hasCulture = true;
    else if (name == "勤労感謝の日") hasLaborThanksgiving = true;
  }
  
  assertTrue(hasNewYear, "Holiday list should contain New Year's Day");
  assertTrue(hasComingOfAge, "Holiday list should contain Coming of Age Day");
  assertTrue(hasFoundation, "Holiday list should contain National Foundation Day");
  assertTrue(hasEmperorBirthday, "Holiday list should contain Emperor's Birthday");
  assertTrue(hasVernalEquinox, "Holiday list should contain Vernal Equinox Day");
  assertTrue(hasShowa, "Holiday list should contain Showa Day");
  assertTrue(hasConstitution, "Holiday list should contain Constitution Memorial Day");
  assertTrue(hasGreenery, "Holiday list should contain Greenery Day");
  assertTrue(hasChildren, "Holiday list should contain Children's Day");
  assertTrue(hasMarine, "Holiday list should contain Marine Day");
  assertTrue(hasMountain, "Holiday list should contain Mountain Day");
  assertTrue(hasRespectAged, "Holiday list should contain Respect for the Aged Day");
  assertTrue(hasAutumnalEquinox, "Holiday list should contain Autumnal Equinox Day");
  assertTrue(hasSports, "Holiday list should contain Sports Day");
  assertTrue(hasCulture, "Holiday list should contain Culture Day");
  assertTrue(hasLaborThanksgiving, "Holiday list should contain Labor Thanksgiving Day");
  
  // Test with limited buffer size
  Holiday smallList[5];
  int smallCount = holiday.getHolidayList(2025, smallList, 5);
  assertEqual(smallCount, 5, "Should return max 5 holidays when buffer is limited");
  
  // Test with invalid year
  int invalidCount = holiday.getHolidayList(1999, holidayList, 50);
  assertEqual(invalidCount, 0, "Should return 0 holidays for year before 2000");
  
  invalidCount = holiday.getHolidayList(2031, holidayList, 50);
  assertEqual(invalidCount, 0, "Should return 0 holidays for year after 2030");
}

// Test edge cases
void testEdgeCases() {
  Serial.println("\n7. Testing Edge Cases");
  
  // Test year boundaries
  assertIsNotHoliday(1999, 1, 1, "Year before 2000 should not be supported");
  assertIsHoliday(2000, 1, 1, "Year 2000 should be supported");
  assertIsHoliday(2030, 1, 1, "Year 2030 should be supported");
  assertIsNotHoliday(2031, 1, 1, "Year after 2030 should not be supported");
  
  // Test invalid dates
  assertIsNotHoliday(2025, 2, 29, "Invalid date (February 29 in non-leap year)");
  assertIsNotHoliday(2025, 4, 31, "Invalid date (April 31)");
  
  // Test leap year
  assertIsNotHoliday(2024, 2, 29, "February 29 in leap year should not be a holiday");
  
  // Test month boundaries
  assertIsNotHoliday(2025, 0, 1, "Month 0 should not be valid");
  assertIsNotHoliday(2025, 13, 1, "Month 13 should not be valid");
  
  // Test day boundaries
  assertIsNotHoliday(2025, 1, 0, "Day 0 should not be valid");
  assertIsNotHoliday(2025, 1, 32, "Day 32 should not be valid");
  
  // Test non-holidays
  assertIsNotHoliday(2025, 12, 25, "Christmas is not a holiday in Japan");
  assertIsNotHoliday(2025, 2, 14, "Valentine's Day is not a holiday in Japan");
  assertIsNotHoliday(2025, 3, 17, "St. Patrick's Day is not a holiday in Japan");
  
  // Test consecutive holidays
  assertIsHoliday(2025, 5, 3, "憲法記念日"); // Constitution Memorial Day
  assertIsHoliday(2025, 5, 4, "みどりの日"); // Greenery Day
  assertIsHoliday(2025, 5, 5, "こどもの日"); // Children's Day
}

// Test memory usage
void testMemoryUsage() {
  Serial.println("\n8. Testing Memory Usage");
  
  // Report free memory
  Serial.print("Free memory: ");
  Serial.print(freeRam());
  Serial.println(" bytes");
  
  // Test memory usage with multiple operations
  for (int i = 0; i < 100; i++) {
    holiday.isHoliday(2025, 1, 1);
    holiday.getHolidayName(2025, 1, 1);
  }
  
  Serial.print("Free memory after operations: ");
  Serial.print(freeRam());
  Serial.println(" bytes");
  
  // No specific assertions here, just reporting memory usage
  // This helps to identify memory leaks or excessive memory usage
  
  // Mark test as passed
  totalTests++;
  passedTests++;
}

// Helper function to calculate free RAM
int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

// Helper functions for assertions
void assertTrue(bool condition, const char* message) {
  totalTests++;
  
  if (condition) {
    passedTests++;
    Serial.print("✓ ");
  } else {
    Serial.print("✗ ");
  }
  
  Serial.println(message);
}

void assertFalse(bool condition, const char* message) {
  assertTrue(!condition, message);
}

void assertEqual(String actual, String expected, const char* message) {
  totalTests++;
  
  if (actual == expected) {
    passedTests++;
    Serial.print("✓ ");
  } else {
    Serial.print("✗ ");
    Serial.print(message);
    Serial.print(" (Expected: '");
    Serial.print(expected);
    Serial.print("', Actual: '");
    Serial.print(actual);
    Serial.print("')");
  }
  
  Serial.println(message);
}

void assertEqual(int actual, int expected, const char* message) {
  totalTests++;
  
  if (actual == expected) {
    passedTests++;
    Serial.print("✓ ");
  } else {
    Serial.print("✗ ");
    Serial.print(message);
    Serial.print(" (Expected: ");
    Serial.print(expected);
    Serial.print(", Actual: ");
    Serial.print(actual);
    Serial.print(")");
  }
  
  Serial.println(message);
}

void assertIsHoliday(int year, int month, int day, const char* holidayName) {
  String message = String(year) + "/" + month + "/" + day + " should be " + holidayName;
  assertTrue(holiday.isHoliday(year, month, day), message.c_str());
  
  String name = holiday.getHolidayName(year, month, day);
  message = String(year) + "/" + month + "/" + day + " should be named " + holidayName;
  assertEqual(name, holidayName, message.c_str());
}

void assertIsNotHoliday(int year, int month, int day, const char* message) {
  String fullMessage = String(year) + "/" + month + "/" + day + " " + message;
  assertFalse(holiday.isHoliday(year, month, day), fullMessage.c_str());
  
  String name = holiday.getHolidayName(year, month, day);
  fullMessage = String(year) + "/" + month + "/" + day + " should return empty name";
  assertEqual(name, "", fullMessage.c_str());
}
