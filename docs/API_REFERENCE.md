# JpHoliday API Reference

This document provides detailed information about the JpHoliday Arduino library API.

## Class: JpHoliday

The main class for Japanese holiday detection.

### Constructor

```cpp
JpHoliday()
```

Creates a new instance of the JpHoliday class.

### Methods

#### isHoliday

```cpp
bool isHoliday(uint16_t year, uint8_t month, uint8_t day)
```

Checks if the specified date is a Japanese holiday (including substitute holidays).

**Parameters:**
- `year`: Year (2000-2030)
- `month`: Month (1-12)
- `day`: Day (1-31)

**Returns:**
- `true` if the date is a holiday
- `false` if the date is not a holiday

**Example:**
```cpp
JpHoliday holiday;
if (holiday.isHoliday(2025, 1, 1)) {
  // January 1, 2025 is a holiday (New Year's Day)
}
```

#### getHolidayName

```cpp
String getHolidayName(uint16_t year, uint8_t month, uint8_t day)
```

Gets the name of the holiday for the specified date.

**Parameters:**
- `year`: Year (2000-2030)
- `month`: Month (1-12)
- `day`: Day (1-31)

**Returns:**
- The name of the holiday (in Japanese)
- Empty string if the date is not a holiday

**Example:**
```cpp
JpHoliday holiday;
String name = holiday.getHolidayName(2025, 1, 1);
// name will be "元日" (New Year's Day)
```

#### getHolidayList

```cpp
uint8_t getHolidayList(uint16_t year, Holiday* holidays, uint8_t maxHolidays)
```

Gets a list of all holidays for the specified year.

**Parameters:**
- `year`: Year (2000-2030)
- `holidays`: Pointer to an array of Holiday structures to store the results
- `maxHolidays`: Maximum number of holidays to retrieve (size of the holidays array)

**Returns:**
- The number of holidays found

**Example:**
```cpp
JpHoliday holiday;
Holiday holidayList[30];
int count = holiday.getHolidayList(2025, holidayList, 30);
for (int i = 0; i < count; i++) {
  Serial.print(holidayList[i].year);
  Serial.print("/");
  Serial.print(holidayList[i].month);
  Serial.print("/");
  Serial.print(holidayList[i].day);
  Serial.print(" - ");
  Serial.println(holidayList[i].getName());
}
```

### Helper Methods

The following methods are used internally but may be useful for advanced users:

#### isRegularHoliday

```cpp
bool isRegularHoliday(uint16_t year, uint8_t month, uint8_t day)
```

Checks if the specified date is a regular holiday (not including substitute holidays).

#### isSubstituteHoliday

```cpp
bool isSubstituteHoliday(uint16_t year, uint8_t month, uint8_t day)
```

Checks if the specified date is a substitute holiday.

#### getDayOfWeek

```cpp
uint8_t getDayOfWeek(uint16_t year, uint8_t month, uint8_t day)
```

Gets the day of the week for the specified date (0=Sunday, 1=Monday, ..., 6=Saturday).

## Struct: Holiday

Structure to store holiday information.

### Properties

- `year`: Year of the holiday (uint16_t)
- `month`: Month of the holiday (uint8_t)
- `day`: Day of the holiday (uint8_t)
- `nameIndex`: Index of the holiday name (uint8_t)

### Methods

#### getName

```cpp
String getName() const
```

Gets the name of the holiday.

**Returns:**
- The name of the holiday (in Japanese)
