# JpHoliday Test Suite

This directory contains test files for the JpHoliday Arduino library.

## Test Files

- [JpHolidayTest](JpHolidayTest/JpHolidayTest.ino) - Comprehensive test suite for the JpHoliday library

## Running Tests

To run the tests:

1. Open the Arduino IDE
2. Open the JpHolidayTest.ino file
3. Upload the sketch to your Arduino board
4. Open the Serial Monitor (set baud rate to 9600)
5. View the test results in the Serial Monitor

## Test Coverage

The test suite covers:

1. **Fixed Date Holidays** - Tests all fixed date holidays (元日, 建国記念の日, etc.)
2. **Variable Date Holidays** - Tests all variable date holidays (成人の日, 海の日, etc.)
3. **Equinox Holidays** - Tests spring and autumn equinox days for various years
4. **Substitute Holidays** - Tests substitute holiday detection for various scenarios
5. **Holiday Names** - Tests holiday name retrieval for all holidays
6. **Holiday List** - Tests the holiday list retrieval functionality
7. **Edge Cases** - Tests boundary conditions and invalid inputs
8. **Memory Usage** - Tests memory efficiency

## Test Results

The test suite reports:

- Total number of tests run
- Number of tests passed
- Percentage of tests passed
- Detailed results for each test category
- Memory usage statistics

## Adding New Tests

To add new tests:

1. Add test cases to the appropriate test category function
2. Use the assertion helper functions (`assertTrue`, `assertFalse`, `assertEqual`, etc.)
3. Add any new test categories by creating a new test function and calling it from `setup()`
