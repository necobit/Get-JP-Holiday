# Get-JP-Holiday

Arduino library for Japanese holiday detection based on "国民の祝日に関する法律（昭和23年法律第178号）".

## Features

- Determine if a specific date is a Japanese national holiday
- Get the name of the holiday for a specific date
- Support for substitute holidays (振替休日)
- Optimized for Arduino's limited memory resources

## Installation

1. Download the ZIP file of this library
2. Open Arduino IDE
3. Go to Sketch > Include Library > Add .ZIP Library...
4. Select the downloaded ZIP file

## Usage

```cpp
#include <JpHoliday.h>

JpHoliday holiday;

void setup() {
  Serial.begin(9600);
  
  // Check if a date is a holiday
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

## Supported Holidays

This library supports all 16 Japanese national holidays defined by law, including:

1. 元日 (New Year's Day) - January 1
2. 成人の日 (Coming of Age Day) - Second Monday of January
3. 建国記念の日 (National Foundation Day) - February 11
4. 天皇誕生日 (Emperor's Birthday) - February 23
5. 春分の日 (Vernal Equinox Day) - Around March 20
6. 昭和の日 (Showa Day) - April 29
7. 憲法記念日 (Constitution Memorial Day) - May 3
8. みどりの日 (Greenery Day) - May 4
9. こどもの日 (Children's Day) - May 5
10. 海の日 (Marine Day) - Third Monday of July
11. 山の日 (Mountain Day) - August 11
12. 敬老の日 (Respect for the Aged Day) - Third Monday of September
13. 秋分の日 (Autumnal Equinox Day) - Around September 23
14. スポーツの日 (Sports Day) - Second Monday of October
15. 文化の日 (Culture Day) - November 3
16. 勤労感謝の日 (Labor Thanksgiving Day) - November 23

It also supports substitute holidays (振替休日) when a national holiday falls on a Sunday.

## License

This library is released under the MIT License.
