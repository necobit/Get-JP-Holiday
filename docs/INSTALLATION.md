# JpHoliday Installation Guide

This document provides detailed instructions for installing and setting up the JpHoliday Arduino library.

## Installation Methods

### Method 1: Using the Arduino Library Manager (Recommended)

1. Open the Arduino IDE
2. Go to **Sketch > Include Library > Manage Libraries...**
3. In the Library Manager, search for "JpHoliday"
4. Click on the JpHoliday library in the search results
5. Click the "Install" button
6. After installation, restart the Arduino IDE

### Method 2: Manual Installation (ZIP File)

1. Download the ZIP file of this library from the [GitHub repository](https://github.com/necobit/Get-JP-Holiday)
2. Open the Arduino IDE
3. Go to **Sketch > Include Library > Add .ZIP Library...**
4. Select the downloaded ZIP file
5. After installation, restart the Arduino IDE

### Method 3: Manual Installation (Direct)

1. Download or clone the repository from GitHub:
   ```
   git clone https://github.com/necobit/Get-JP-Holiday.git
   ```
2. Copy the entire folder to your Arduino libraries directory:
   - Windows: `Documents\Arduino\libraries\JpHoliday`
   - macOS: `~/Documents/Arduino/libraries/JpHoliday`
   - Linux: `~/Arduino/libraries/JpHoliday`
3. Restart the Arduino IDE

## Verifying Installation

To verify that the library is correctly installed:

1. Open the Arduino IDE
2. Go to **File > Examples**
3. You should see "JpHoliday" in the examples list
4. Select one of the examples (e.g., "CheckHoliday") to open it

## Compatibility

The JpHoliday library is compatible with:

- Arduino IDE 1.5.0 or later
- All Arduino boards (Uno, Mega, Leonardo, etc.)
- ESP8266 and ESP32 boards
- Other Arduino-compatible boards

## Memory Requirements

The library is optimized for Arduino's limited resources:

- Flash Memory Usage: ~2-3 KB
- SRAM Usage: ~100-200 bytes

## Troubleshooting

If you encounter issues during installation:

1. **Library Not Found**: Make sure the library is correctly installed in your Arduino libraries directory.
2. **Compilation Errors**: Ensure you're using a compatible Arduino IDE version (1.5.0 or later).
3. **Memory Issues**: If you're using a board with very limited memory (like Arduino Nano), you might need to optimize your sketch to reduce memory usage.

## Updating the Library

To update to the latest version:

1. Using Library Manager:
   - Go to **Sketch > Include Library > Manage Libraries...**
   - Find "JpHoliday" and click "Update"

2. Manual Update:
   - Remove the existing library folder from your Arduino libraries directory
   - Install the latest version using one of the methods described above
