# Window Sensor Firmware Configuration Guide

This document provides comprehensive information about configuring the window sensor firmware using ESP-IDF's Kconfig system.

**Last Updated:** 2025-10-03  
**Firmware Version:** M1 (WiFi Configuration Enablement)  
**Target Hardware:** ESP32-C6-WROOM-1

---

## Table of Contents

1. [Overview](#overview)
2. [Configuration Methods](#configuration-methods)
3. [Hardware Pin Assignments](#hardware-pin-assignments)
4. [WiFi Configuration](#wifi-configuration)
5. [Web Server Configuration](#web-server-configuration)
6. [LED Configuration](#led-configuration)
7. [Device Configuration](#device-configuration)
8. [Storage Configuration](#storage-configuration)
9. [Configuration Examples](#configuration-examples)
10. [Troubleshooting](#troubleshooting)

---

## Overview

The window sensor firmware uses ESP-IDF's Kconfig system for compile-time configuration. This approach provides:

- **Type-safe configuration:** Values are checked at compile time
- **Range validation:** Prevents invalid values
- **Clear documentation:** Help text in menuconfig
- **Version control:** Configuration tracked with code
- **Hardware flexibility:** Easy adaptation for different boards

### Architecture Reference

See **ADR-012** for the architectural decision behind compile-time configuration.

---

## Configuration Methods

### Method 1: Using menuconfig (Interactive)

```bash
cd /path/to/firmware-fenstersensor
idf.py menuconfig
```

Navigate to: `Window Sensor Configuration`

- Use arrow keys to navigate
- Press Enter to select/modify
- Press Space to toggle boolean options
- Press 'S' to save, 'Q' to quit

### Method 2: Editing sdkconfig.defaults (Batch)

Edit `sdkconfig.defaults` file directly:

```bash
vim sdkconfig.defaults
```

Then rebuild:

```bash
idf.py fullclean
idf.py build
```

### Method 3: Command Line Override

```bash
idf.py -DCONFIG_RGB_LED_GPIO=21 build
```

**Note:** Command line overrides are temporary and not saved to sdkconfig.

---

## Hardware Pin Assignments

### RGB LED GPIO (`CONFIG_RGB_LED_GPIO`)

**Purpose:** GPIO pin for WS2812 RGB LED status indicator  
**Default:** 8 (ESP32-C6-WROOM-1 built-in RGB LED)  
**Range:** 0-25  
**User Stories:** US04 (LED State Indication)

**Hardware Notes:**
- GPIO 8 is the built-in RGB LED on ESP32-C6-WROOM-1
- For external LED, use GPIO 21 or other safe pin
- Avoid GPIO 12-17 (flash), GPIO 24-25 (USB)

**Example:**
```kconfig
CONFIG_RGB_LED_GPIO=8
```

### AP Mode Button GPIO (`CONFIG_AP_BUTTON_GPIO`)

**Purpose:** Button to trigger WiFi AP configuration mode  
**Default:** 9 (BOOT button on ESP32-C6-DevKitC-1)  
**Range:** 0-25  
**User Stories:** US01 (WiFi AP Mode)

**Hardware Notes:**
- GPIO 9 is the BOOT button on most ESP32-C6 dev boards
- Pin is configured with internal pull-up
- Press and hold for `CONFIG_AP_BUTTON_HOLD_TIME_MS` to activate

**Example:**
```kconfig
CONFIG_AP_BUTTON_GPIO=9
```

### Window Sensor GPIO (`CONFIG_WINDOW_SENSOR_GPIO`)

**Purpose:** Input for window open/close sensor (M2 feature)  
**Default:** 4  
**Range:** 0-25  
**User Stories:** US10 (Sensor Simulation, M2)

**Hardware Notes:**
- Connect reed switch or magnetic sensor
- Internal pull-up resistor enabled
- Safe pins: GPIO 2, 3, 4, 5, 6, 7, 10, 11, 18, 19, 20, 21

**Example:**
```kconfig
CONFIG_WINDOW_SENSOR_GPIO=4
```

---

## WiFi Configuration

### AP SSID Prefix (`CONFIG_WIFI_AP_SSID_PREFIX`)

**Purpose:** Prefix for AP mode SSID  
**Default:** "WindowSensor"  
**Type:** String (max 20 characters)  
**User Stories:** US01

**Details:**
- Full SSID format: `<prefix>-<MAC_last_4_chars>`
- Example: `WindowSensor-A1B2`
- Keep prefix short to allow MAC suffix

**Example:**
```kconfig
CONFIG_WIFI_AP_SSID_PREFIX="WindowSensor"
```

### AP Password (`CONFIG_WIFI_AP_PASSWORD`)

**Purpose:** Default password for AP mode  
**Default:** "configure"  
**Type:** String (8-63 characters)  
**User Stories:** US01

**Security Warning:**
⚠️ Change this for production deployments! The default is intentionally weak for development.

**Example:**
```kconfig
CONFIG_WIFI_AP_PASSWORD="MySecurePassword123"
```

### AP Channel (`CONFIG_WIFI_AP_CHANNEL`)

**Purpose:** WiFi channel for AP mode  
**Default:** 1  
**Range:** 1-13  
**User Stories:** US01

**Recommendations:**
- Use channels 1, 6, or 11 to avoid overlap
- Survey local WiFi networks to choose least congested channel

**Example:**
```kconfig
CONFIG_WIFI_AP_CHANNEL=6
```

### AP Max Connections (`CONFIG_WIFI_AP_MAX_CONNECTIONS`)

**Purpose:** Maximum simultaneous AP clients  
**Default:** 4  
**Range:** 1-10  
**User Stories:** US01

**Performance Note:**
- Each connection consumes ~10KB RAM
- Default of 4 is sufficient for configuration use case

**Example:**
```kconfig
CONFIG_WIFI_AP_MAX_CONNECTIONS=4
```

### Connection Timeout (`CONFIG_WIFI_CONNECT_TIMEOUT_MS`)

**Purpose:** Maximum time to wait for WiFi connection  
**Default:** 30000 ms (30 seconds)  
**Range:** 5000-120000 ms  
**User Stories:** US01, ADR-018

**Tuning:**
- Increase for slow/congested networks
- Decrease for faster failure detection

**Example:**
```kconfig
CONFIG_WIFI_CONNECT_TIMEOUT_MS=30000
```

### Max Retry Attempts (`CONFIG_WIFI_MAX_RETRY_ATTEMPTS`)

**Purpose:** Number of connection retries before AP fallback  
**Default:** 3  
**Range:** 1-10  
**User Stories:** ADR-018 (Error Handling)

**Strategy:**
- Uses exponential backoff between retries
- After max retries, device returns to AP mode

**Example:**
```kconfig
CONFIG_WIFI_MAX_RETRY_ATTEMPTS=3
```

### Retry Backoff Base (`CONFIG_WIFI_RETRY_BACKOFF_BASE_MS`)

**Purpose:** Base delay for exponential backoff  
**Default:** 10000 ms (10 seconds)  
**Range:** 1000-60000 ms  
**User Stories:** ADR-018

**Formula:**
```
actual_delay = base * (2 ^ retry_attempt)
```

**Example:**
- Attempt 1: 10 seconds
- Attempt 2: 20 seconds
- Attempt 3: 40 seconds

**Example:**
```kconfig
CONFIG_WIFI_RETRY_BACKOFF_BASE_MS=10000
```

---

## Web Server Configuration

### Server Port (`CONFIG_WEB_SERVER_PORT`)

**Purpose:** HTTP server port for web interface  
**Default:** 80  
**Range:** 1-65535  
**User Stories:** US02 (Web Frontend)

**Notes:**
- Port 80 is standard HTTP
- Change if port conflict occurs
- Ports >1024 don't require root privileges

**Example:**
```kconfig
CONFIG_WEB_SERVER_PORT=80
```

### Max Sessions (`CONFIG_WEB_SERVER_MAX_SESSIONS`)

**Purpose:** Maximum concurrent web sessions  
**Default:** 4  
**Range:** 1-10  
**User Stories:** US02, US06

**Memory Impact:**
- Each session: ~2KB RAM
- 4 sessions: ~8KB RAM total

**Example:**
```kconfig
CONFIG_WEB_SERVER_MAX_SESSIONS=4
```

### Session Timeout (`CONFIG_WEB_SESSION_TIMEOUT_SEC`)

**Purpose:** Session expiration time after authentication  
**Default:** 300 seconds (5 minutes)  
**Range:** 60-3600 seconds  
**User Stories:** US06 (Authentication)

**Security Note:**
- Shorter timeout = more secure, less convenient
- Longer timeout = more convenient, less secure

**Example:**
```kconfig
CONFIG_WEB_SESSION_TIMEOUT_SEC=300
```

### Max Auth Attempts (`CONFIG_WEB_MAX_AUTH_ATTEMPTS`)

**Purpose:** Maximum PIN entry attempts before lockout  
**Default:** 5  
**Range:** 1-10  
**User Stories:** US06, ADR-015

**Brute-Force Protection:**
- After max attempts, account locked for `CONFIG_WEB_AUTH_LOCKOUT_SEC`

**Example:**
```kconfig
CONFIG_WEB_MAX_AUTH_ATTEMPTS=5
```

### Auth Lockout Time (`CONFIG_WEB_AUTH_LOCKOUT_SEC`)

**Purpose:** Lockout duration after failed auth attempts  
**Default:** 60 seconds  
**Range:** 10-600 seconds  
**User Stories:** US06, ADR-015

**Example:**
```kconfig
CONFIG_WEB_AUTH_LOCKOUT_SEC=60
```

---

## LED Configuration

### LED Brightness (`CONFIG_LED_BRIGHTNESS`)

**Purpose:** RGB LED brightness level  
**Default:** 64 (25% brightness)  
**Range:** 0-255 (0=off, 255=max)  
**User Stories:** US04

**Power Consumption:**
- Brightness 64: ~15mA
- Brightness 128: ~30mA
- Brightness 255: ~60mA per color channel

**Example:**
```kconfig
CONFIG_LED_BRIGHTNESS=64
```

### Slow Blink Rate (`CONFIG_LED_BLINK_RATE_SLOW_MS`)

**Purpose:** Period for slow blink pattern  
**Default:** 1000 ms (1 Hz)  
**Range:** 100-5000 ms  
**User Stories:** US04, ADR-016

**Usage:**
- Normal status indication (AP mode, connected, disconnected)

**Example:**
```kconfig
CONFIG_LED_BLINK_RATE_SLOW_MS=1000
```

### Fast Blink Rate (`CONFIG_LED_BLINK_RATE_FAST_MS`)

**Purpose:** Period for fast blink pattern  
**Default:** 250 ms (4 Hz)  
**Range:** 50-1000 ms  
**User Stories:** US04, ADR-016

**Usage:**
- Error indication
- Urgent status alerts

**Example:**
```kconfig
CONFIG_LED_BLINK_RATE_FAST_MS=250
```

---

## Device Configuration

### PIN Length (`CONFIG_DEVICE_PIN_LENGTH`)

**Purpose:** Number of digits in device PIN  
**Default:** 8  
**Range:** 4-12  
**User Stories:** US06, ADR-015

**Security Considerations:**
- 4 digits: 10,000 combinations (weak)
- 6 digits: 1,000,000 combinations (adequate)
- 8 digits: 100,000,000 combinations (strong)

**Example:**
```kconfig
CONFIG_DEVICE_PIN_LENGTH=8
```

### AP Button Hold Time (`CONFIG_AP_BUTTON_HOLD_TIME_MS`)

**Purpose:** Duration to hold button for AP mode  
**Default:** 5000 ms (5 seconds)  
**Range:** 1000-10000 ms  
**User Stories:** US01

**User Experience:**
- Shorter time: Easier to activate, risk of accidents
- Longer time: Harder to activate, prevents accidents

**Example:**
```kconfig
CONFIG_AP_BUTTON_HOLD_TIME_MS=5000
```

### Debounce Delay (`CONFIG_DEBOUNCE_DELAY_MS`)

**Purpose:** Button debounce time (M2 feature)  
**Default:** 50 ms  
**Range:** 10-200 ms  
**User Stories:** US07 (M2)

**Tuning:**
- Increase if false button triggers occur
- Decrease for more responsive buttons

**Example:**
```kconfig
CONFIG_DEBOUNCE_DELAY_MS=50
```

---

## Storage Configuration

### NVS Partition Size (`CONFIG_NVS_PARTITION_SIZE_KB`)

**Purpose:** Non-volatile storage partition size  
**Default:** 24 KB  
**Range:** 12-256 KB  
**User Stories:** US03, ADR-017

**Storage Requirements:**
- M1 (WiFi config): ~4KB
- M2 (Matter/Thread): ~12KB
- Headroom: ~8KB
- Total: 24KB

**Important:** Must match partition table definition.

**Example:**
```kconfig
CONFIG_NVS_PARTITION_SIZE_KB=24
```

---

## Configuration Examples

### Example 1: Development Configuration

```kconfig
# Development-friendly settings
CONFIG_RGB_LED_GPIO=8
CONFIG_AP_BUTTON_GPIO=9
CONFIG_WIFI_AP_PASSWORD="devmode123"
CONFIG_LED_BRIGHTNESS=128  # Brighter for visibility
CONFIG_DEVICE_PIN_LENGTH=4  # Shorter PIN for quick testing
CONFIG_WEB_SESSION_TIMEOUT_SEC=3600  # 1 hour timeout
CONFIG_LOG_DEFAULT_LEVEL_DEBUG=y
```

### Example 2: Production Configuration

```kconfig
# Production-secure settings
CONFIG_RGB_LED_GPIO=8
CONFIG_AP_BUTTON_GPIO=9
CONFIG_WIFI_AP_PASSWORD="SecureP@ssw0rd2025!"
CONFIG_LED_BRIGHTNESS=32  # Lower for power saving
CONFIG_DEVICE_PIN_LENGTH=8  # Strong security
CONFIG_WEB_SESSION_TIMEOUT_SEC=180  # 3 minute timeout
CONFIG_WEB_MAX_AUTH_ATTEMPTS=3  # Stricter auth
CONFIG_WEB_AUTH_LOCKOUT_SEC=300  # 5 minute lockout
CONFIG_LOG_DEFAULT_LEVEL_INFO=y
```

### Example 3: Low-Power Configuration

```kconfig
# Optimized for battery operation
CONFIG_LED_BRIGHTNESS=16  # Minimal brightness
CONFIG_LED_BLINK_RATE_SLOW_MS=2000  # Slower = less power
CONFIG_WIFI_CONNECT_TIMEOUT_MS=15000  # Faster timeout
CONFIG_WIFI_MAX_RETRY_ATTEMPTS=2  # Fewer retries
CONFIG_COMPILER_OPTIMIZATION_SIZE=y
```

### Example 4: Custom Hardware Variant

```kconfig
# External components on different pins
CONFIG_RGB_LED_GPIO=21  # External LED
CONFIG_AP_BUTTON_GPIO=5  # Different button location
CONFIG_WINDOW_SENSOR_GPIO=6  # Different sensor pin
```

---

## Troubleshooting

### Issue: Configuration changes not taking effect

**Solution:**
```bash
idf.py fullclean
idf.py build
idf.py flash
```

### Issue: GPIO conflicts or hardware not working

**Check:**
1. Verify GPIO pin is not used by flash (12-17) or USB (24-25)
2. Check pin multiplexing in ESP32-C6 datasheet
3. Use logic analyzer to verify signal output
4. See [hardware_pins.md](hardware_pins.md) for safe pins

### Issue: menuconfig shows wrong values

**Solution:**
```bash
rm sdkconfig
idf.py reconfigure
```

### Issue: Build fails with Kconfig errors

**Check:**
1. Kconfig syntax in `main/Kconfig.projbuild`
2. Range violations in `sdkconfig.defaults`
3. Missing dependencies between options

### Issue: WiFi not working with custom channel

**Solution:**
- Use channels 1-11 for wider compatibility
- Some regions restrict certain channels
- Check local regulations

### Issue: LED too bright/dim

**Solution:**
- Adjust `CONFIG_LED_BRIGHTNESS` (0-255)
- Consider ambient light conditions
- Full brightness draws significant power

---

## References

- **ADR-012:** Compile-Time Configuration Architecture
- **ADR-013:** Web Server Architecture
- **ADR-014:** WiFi State Machine
- **ADR-015:** Authentication & PIN Management
- **ADR-016:** LED Control Architecture
- **ADR-017:** NVS Partition Layout
- **ADR-018:** WiFi Error Handling
- [ESP-IDF Kconfig Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/kconfig.html)
- [ESP32-C6 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-c6_datasheet_en.pdf)
- [Hardware Pin Reference](hardware_pins.md)

---

## Change Log

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | 2025-10-03 | Initial M1 configuration documentation |

---

**For questions or issues, please refer to the project repository or contact the development team.**
