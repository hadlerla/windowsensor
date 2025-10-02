# Window Sensor Firmware - First Blink Example

This is the first working example of the Window Sensor firmware that demonstrates the basic LED blinking functionality using the same hardware configuration as the working blink example.

## What This Example Does

- Blinks the built-in RGB LED on GPIO 8 of the ESP32-C6
- Uses addressable LED strip functionality (WS2812-style RGB LED)
- Provides a foundation for the window sensor architecture while maintaining immediate functionality
- Demonstrates proper hardware abstraction concepts

## Hardware Configuration

- **LED**: GPIO 8 (ESP32-C6 built-in RGB LED)
- **LED Type**: Addressable LED strip (single pixel)
- **Backend**: RMT peripheral (10MHz resolution)
- **Blink Period**: 1 second (configurable)

## Configuration

The project is configured through menuconfig in the "Window Sensor Configuration" section:

- `CONFIG_BLINK_GPIO=8` - GPIO pin for the LED
- `CONFIG_BLINK_LED_STRIP=y` - Use addressable LED strip
- `CONFIG_BLINK_LED_STRIP_BACKEND_RMT=y` - Use RMT backend
- `CONFIG_BLINK_PERIOD=1000` - Blink period in milliseconds

## Building and Running

1. Build the project:
   ```bash
   idf.py build
   ```

2. Flash to the device:
   ```bash
   idf.py flash
   ```

3. Monitor the output:
   ```bash
   idf.py monitor
   ```

## Expected Behavior

- The built-in RGB LED will blink white (RGB: 16,16,16) every second
- Console output will show status messages about LED state changes
- The firmware identifies itself as "Window Sensor Firmware" in the logs

## Architecture Notes

This example maintains the architectural vision while providing immediate functionality:

- **Hardware Configuration**: Centralized at the top of main.c (foundation for future HAL)
- **Modular Design**: Separate functions for LED configuration and control
- **Configurable**: All hardware parameters are configurable via Kconfig
- **Future Ready**: Code structure supports evolution into the full window sensor system

## Next Steps

This foundation enables the following architectural evolution:

1. **Hardware Abstraction Layer (HAL)**: Move hardware configuration into separate modules
2. **Sensor Integration**: Add window sensor GPIO reading and debouncing
3. **State Management**: Implement event-driven state management for window status
4. **Communication**: Add Thread/Wi-Fi connectivity
5. **Power Management**: Implement sleep/wake functionality

## File Structure

```
main/
├── main.c                  # Main application with LED blinking
├── CMakeLists.txt         # Build configuration with led_strip dependency
├── Kconfig.projbuild      # Configuration options for window sensor
└── idf_component.yml      # Component dependencies (led_strip)
```

This example successfully demonstrates that the window sensor firmware can use the same hardware and functionality as the simple blink example while maintaining proper architectural foundations.