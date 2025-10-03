# Implementation Plan: US05 - Compile-Time Configuration of Pins and Defaults

**User Story:** US05 - Compile-Time Configuration of Pins and Defaults  
**Status:** Ready for Implementation  
**ADR Reference:** ADR-012  
**Estimated Effort:** 4-6 hours  
**Priority:** Critical (Foundation for M1)

---

## Overview

Implement compile-time configuration for all hardware pins and default parameters required for Milestone M1 using ESP-IDF Kconfig system. This provides the foundation for all subsequent M1 user stories.

## Acceptance Criteria (from US05)

- ✅ All hardware pin assignments configurable via Kconfig
- ✅ All default parameters configurable via Kconfig
- ✅ Values accessible in code via `sdkconfig.h`
- ✅ Reasonable defaults in `sdkconfig.defaults`
- ✅ Clear documentation in Kconfig help text

---

## Architecture References

### ADR-012: Compile-Time Configuration
- Use ESP-IDF Kconfig for all compile-time configuration
- Define options in `main/Kconfig.projbuild`
- Set defaults in `sdkconfig.defaults`
- Access via `CONFIG_*` macros in code

### Related ADRs
- **ADR-013:** Web server configuration (HTTP port, session timeout)
- **ADR-014:** WiFi state machine timeouts and retry counts
- **ADR-015:** PIN configuration (length, display method)
- **ADR-016:** LED configuration (GPIO, brightness, patterns)
- **ADR-017:** NVS partition size
- **ADR-018:** WiFi error handling timeouts

---

## Configuration Categories

### 1. Hardware Pin Assignments

| Configuration Item | Purpose | Default | Range | User Story |
|-------------------|---------|---------|-------|------------|
| `CONFIG_RGB_LED_GPIO` | RGB LED pin | GPIO 8 | 0-25 | US04 |
| `CONFIG_AP_BUTTON_GPIO` | AP mode button | GPIO 9 | 0-25 | US01 |
| `CONFIG_WINDOW_SENSOR_GPIO` | Window sensor (M2) | GPIO 4 | 0-25 | US10 (M2) |

### 2. WiFi Configuration Parameters

| Configuration Item | Purpose | Default | Range/Options | User Story |
|-------------------|---------|---------|---------------|------------|
| `CONFIG_WIFI_AP_SSID_PREFIX` | AP mode SSID prefix | "WindowSensor" | string (max 20 chars) | US01 |
| `CONFIG_WIFI_AP_PASSWORD` | AP mode password | "configure" | string (8-63 chars) | US01 |
| `CONFIG_WIFI_AP_CHANNEL` | AP WiFi channel | 1 | 1-13 | US01 |
| `CONFIG_WIFI_AP_MAX_CONNECTIONS` | Max AP clients | 4 | 1-10 | US01 |
| `CONFIG_WIFI_CONNECT_TIMEOUT_MS` | Connection timeout | 30000 | 5000-120000 | US01, ADR-018 |
| `CONFIG_WIFI_MAX_RETRY_ATTEMPTS` | Max retry count | 3 | 1-10 | ADR-018 |
| `CONFIG_WIFI_RETRY_BACKOFF_BASE_MS` | Retry backoff base | 10000 | 1000-60000 | ADR-018 |

### 3. Web Server Configuration

| Configuration Item | Purpose | Default | Range/Options | User Story |
|-------------------|---------|---------|---------------|------------|
| `CONFIG_WEB_SERVER_PORT` | HTTP server port | 80 | 1-65535 | US02 |
| `CONFIG_WEB_SERVER_MAX_SESSIONS` | Max concurrent sessions | 4 | 1-10 | US02, US06 |
| `CONFIG_WEB_SESSION_TIMEOUT_SEC` | Session timeout | 300 | 60-3600 | US06 |
| `CONFIG_WEB_MAX_AUTH_ATTEMPTS` | Max PIN attempts | 5 | 1-10 | US06 |
| `CONFIG_WEB_AUTH_LOCKOUT_SEC` | Auth lockout time | 60 | 10-600 | US06 |

### 4. LED Configuration

| Configuration Item | Purpose | Default | Range/Options | User Story |
|-------------------|---------|---------|---------------|------------|
| `CONFIG_LED_BRIGHTNESS` | LED brightness (0-255) | 64 | 0-255 | US04 |
| `CONFIG_LED_BLINK_RATE_SLOW_MS` | Slow blink period | 1000 | 100-5000 | US04 |
| `CONFIG_LED_BLINK_RATE_FAST_MS` | Fast blink period | 250 | 50-1000 | US04 |

### 5. Device Configuration

| Configuration Item | Purpose | Default | Range/Options | User Story |
|-------------------|---------|---------|---------------|------------|
| `CONFIG_DEVICE_PIN_LENGTH` | PIN length | 8 | 4-12 | US06, ADR-015 |
| `CONFIG_AP_BUTTON_HOLD_TIME_MS` | Button hold for AP mode | 5000 | 1000-10000 | US01 |
| `CONFIG_DEBOUNCE_DELAY_MS` | Button debounce time | 50 | 10-200 | US07 (M2) |

### 6. NVS Configuration

| Configuration Item | Purpose | Default | Range/Options | User Story |
|-------------------|---------|---------|---------------|------------|
| `CONFIG_NVS_PARTITION_SIZE` | NVS partition size (KB) | 24 | 12-256 | US03, ADR-017 |

---

## Implementation Steps

### Phase 1: Kconfig Structure Setup (1 hour)

**Task 1.1:** Update `main/Kconfig.projbuild` structure
- Remove old/duplicate configuration items
- Organize into logical menus using ESP-IDF menu structure
- Add clear menu titles and descriptions

**Task 1.2:** Create configuration menu hierarchy
```kconfig
menu "Window Sensor Configuration"
    menu "Hardware Pin Assignments"
        # Pin configurations
    endmenu
    
    menu "WiFi Configuration"
        # WiFi parameters
    endmenu
    
    menu "Web Server Configuration"
        # Web server parameters
    endmenu
    
    menu "LED Configuration"
        # LED parameters
    endmenu
    
    menu "Device Configuration"
        # Device parameters
    endmenu
    
    menu "Storage Configuration"
        # NVS parameters
    endmenu
endmenu
```

### Phase 2: Define Configuration Options (2 hours)

**Task 2.1:** Hardware Pin Assignments
```kconfig
config RGB_LED_GPIO
    int "RGB LED GPIO number"
    range 0 25
    default 8
    help
        GPIO number for the WS2812 RGB LED (ESP32-C6 built-in).
        Default: GPIO 8 (built-in RGB LED on ESP32-C6-WROOM-1).
        Avoid: GPIO 12-17 (flash), GPIO 24-25 (USB).

config AP_BUTTON_GPIO
    int "AP Mode Button GPIO number"
    range 0 25
    default 9
    help
        GPIO number for the AP mode activation button.
        Press and hold this button to enter AP configuration mode.
        Default: GPIO 9 (BOOT button on ESP32-C6-DevKitC-1).
        The pin is configured with internal pull-up.

config WINDOW_SENSOR_GPIO
    int "Window Sensor GPIO number"
    range 0 25
    default 4
    help
        GPIO number for the window sensor input (M2 feature).
        Connect a reed switch or magnetic sensor to this pin.
        Default: GPIO 4. The pin will use internal pull-up resistor.
```

**Task 2.2:** WiFi Configuration Parameters
```kconfig
config WIFI_AP_SSID_PREFIX
    string "WiFi AP SSID prefix"
    default "WindowSensor"
    help
        SSID prefix for AP mode. The full SSID will be:
        <prefix>-<last 4 chars of MAC>
        Example: WindowSensor-A1B2

config WIFI_AP_PASSWORD
    string "WiFi AP default password"
    default "configure"
    help
        Default password for AP mode WiFi network.
        Must be 8-63 characters. Use strong password for production.
        This is only used when device has no stored credentials.

config WIFI_CONNECT_TIMEOUT_MS
    int "WiFi connection timeout (ms)"
    range 5000 120000
    default 30000
    help
        Maximum time to wait for WiFi connection before timeout.
        Default: 30 seconds. Increase for slow networks.

config WIFI_MAX_RETRY_ATTEMPTS
    int "WiFi maximum retry attempts"
    range 1 10
    default 3
    help
        Number of connection retry attempts before returning to AP mode.
        See ADR-018 for retry strategy details.
```

**Task 2.3:** Web Server Configuration
```kconfig
config WEB_SERVER_PORT
    int "Web server HTTP port"
    range 1 65535
    default 80
    help
        TCP port for the web configuration server.
        Default: 80 (standard HTTP). Change if port conflict occurs.

config WEB_SESSION_TIMEOUT_SEC
    int "Web session timeout (seconds)"
    range 60 3600
    default 300
    help
        Session timeout after successful PIN authentication.
        Default: 5 minutes. Sessions expire after this time of inactivity.

config WEB_MAX_AUTH_ATTEMPTS
    int "Maximum authentication attempts"
    range 1 10
    default 5
    help
        Maximum PIN entry attempts before lockout.
        Implements brute-force protection (ADR-015).
```

**Task 2.4:** LED Configuration
```kconfig
config LED_BRIGHTNESS
    int "LED brightness (0-255)"
    range 0 255
    default 64
    help
        Brightness level for RGB LED (0=off, 255=max).
        Lower values save power. Default: 64 (25% brightness).

config LED_BLINK_RATE_SLOW_MS
    int "LED slow blink period (ms)"
    range 100 5000
    default 1000
    help
        Period for slow blink pattern (1 Hz = 1000ms).
        Used for normal status indication (AP mode, connected, etc).
```

**Task 2.5:** Device Configuration
```kconfig
config DEVICE_PIN_LENGTH
    int "Device PIN length (digits)"
    range 4 12
    default 8
    help
        Number of digits in device PIN for web authentication.
        Default: 8 digits. See ADR-015 for PIN generation details.

config AP_BUTTON_HOLD_TIME_MS
    int "AP mode button hold time (ms)"
    range 1000 10000
    default 5000
    help
        Duration to hold AP button to trigger AP mode entry.
        Default: 5 seconds. Prevents accidental activation.
```

**Task 2.6:** NVS Configuration
```kconfig
config NVS_PARTITION_SIZE_KB
    int "NVS partition size (KB)"
    range 12 256
    default 24
    help
        Size of NVS partition for persistent storage.
        Must match partition table. Default: 24KB.
        See ADR-017 for namespace layout.
```

### Phase 3: Update sdkconfig.defaults (30 minutes)

**Task 3.1:** Update `sdkconfig.defaults` with M1 defaults
```plaintext
# Hardware Pin Assignments
CONFIG_RGB_LED_GPIO=8
CONFIG_AP_BUTTON_GPIO=9
CONFIG_WINDOW_SENSOR_GPIO=4

# WiFi Configuration
CONFIG_WIFI_AP_SSID_PREFIX="WindowSensor"
CONFIG_WIFI_AP_PASSWORD="configure"
CONFIG_WIFI_AP_CHANNEL=1
CONFIG_WIFI_AP_MAX_CONNECTIONS=4
CONFIG_WIFI_CONNECT_TIMEOUT_MS=30000
CONFIG_WIFI_MAX_RETRY_ATTEMPTS=3
CONFIG_WIFI_RETRY_BACKOFF_BASE_MS=10000

# Web Server Configuration
CONFIG_WEB_SERVER_PORT=80
CONFIG_WEB_SERVER_MAX_SESSIONS=4
CONFIG_WEB_SESSION_TIMEOUT_SEC=300
CONFIG_WEB_MAX_AUTH_ATTEMPTS=5
CONFIG_WEB_AUTH_LOCKOUT_SEC=60

# LED Configuration
CONFIG_LED_BRIGHTNESS=64
CONFIG_LED_BLINK_RATE_SLOW_MS=1000
CONFIG_LED_BLINK_RATE_FAST_MS=250

# Device Configuration
CONFIG_DEVICE_PIN_LENGTH=8
CONFIG_AP_BUTTON_HOLD_TIME_MS=5000
CONFIG_DEBOUNCE_DELAY_MS=50

# Storage Configuration
CONFIG_NVS_PARTITION_SIZE_KB=24
```

### Phase 4: Create Configuration Documentation (1 hour)

**Task 4.1:** Create `docs/configuration.md`
- Document all configuration options
- Explain purpose and impact of each option
- Provide examples for different hardware variants
- Document safe GPIO pin choices for ESP32-C6
- Include troubleshooting tips

**Task 4.2:** Add configuration examples
- Development configuration
- Production configuration
- Low-power configuration
- Different hardware variants

### Phase 5: Testing & Validation (1 hour)

**Task 5.1:** Build verification
```bash
# Clean build with defaults
idf.py fullclean
idf.py build

# Verify sdkconfig.h contains expected macros
grep "CONFIG_RGB_LED_GPIO" build/config/sdkconfig.h
grep "CONFIG_WIFI_AP_SSID_PREFIX" build/config/sdkconfig.h
```

**Task 5.2:** Configuration menu testing
```bash
# Test menuconfig interface
idf.py menuconfig
# Navigate to "Window Sensor Configuration"
# Verify all options are present and organized
# Test changing values and saving
```

**Task 5.3:** Create test code
- Create simple test in `main.c` to print all configuration values at boot
- Verify values match Kconfig settings

**Task 5.4:** Documentation validation
- Verify all Kconfig help text is clear and accurate
- Check for typos and formatting issues
- Ensure GPIO pin warnings are correct for ESP32-C6

---

## File Changes

### Files to Modify
1. `main/Kconfig.projbuild` - Complete restructure with new options
2. `sdkconfig.defaults` - Update with M1 defaults
3. `main/main.c` - Add configuration validation/debug output

### Files to Create
1. `docs/configuration.md` - Configuration documentation
2. `docs/hardware_pins.md` - ESP32-C6 GPIO pin reference

### Files to Update (Future)
These files will be created in subsequent user stories but will reference these configs:
- `components/wifi_manager/wifi_manager.c` (US01)
- `components/led_controller/led_controller.c` (US04)
- `components/web_server/web_server.c` (US02)

---

## Testing Checklist

- [ ] Build succeeds with default configuration
- [ ] All CONFIG_* macros accessible in code
- [ ] menuconfig displays organized menu structure
- [ ] Help text is clear and accurate
- [ ] Changing values in menuconfig works correctly
- [ ] sdkconfig.defaults provides working defaults
- [ ] GPIO pin ranges prevent invalid selections
- [ ] String lengths are validated
- [ ] Numeric ranges are enforced
- [ ] Documentation is complete and accurate

---

## Code Example: Using Configuration in Code

```c
// In wifi_manager.c
#include "sdkconfig.h"

void wifi_manager_init(void) {
    // Access compile-time configuration
    const char *ap_ssid_prefix = CONFIG_WIFI_AP_SSID_PREFIX;
    uint32_t timeout_ms = CONFIG_WIFI_CONNECT_TIMEOUT_MS;
    uint8_t max_retries = CONFIG_WIFI_MAX_RETRY_ATTEMPTS;
    
    ESP_LOGI(TAG, "WiFi Manager Config:");
    ESP_LOGI(TAG, "  AP SSID Prefix: %s", ap_ssid_prefix);
    ESP_LOGI(TAG, "  Connect Timeout: %lu ms", timeout_ms);
    ESP_LOGI(TAG, "  Max Retries: %u", max_retries);
    
    // Use configuration values...
}
```

```c
// In led_controller.c
#include "sdkconfig.h"

#define LED_GPIO CONFIG_RGB_LED_GPIO
#define LED_BRIGHTNESS CONFIG_LED_BRIGHTNESS
#define BLINK_PERIOD_MS CONFIG_LED_BLINK_RATE_SLOW_MS

void led_controller_init(void) {
    ESP_LOGI(TAG, "LED Controller Config:");
    ESP_LOGI(TAG, "  GPIO: %d", LED_GPIO);
    ESP_LOGI(TAG, "  Brightness: %d", LED_BRIGHTNESS);
    
    // Configure LED with compile-time settings...
}
```

---

## Dependencies

### Required Before Starting
- ✅ ADR-012 reviewed and accepted
- ✅ Development environment set up (ESP-IDF v5.5)
- ✅ ESP32-C6 target configured

### Blocks These User Stories
- US01 (WiFi AP Mode) - needs WiFi configuration
- US02 (Web Frontend) - needs web server configuration
- US03 (Secure Storage) - needs NVS configuration
- US04 (LED State) - needs LED configuration
- US06 (Authentication) - needs PIN configuration

---

## Success Criteria

1. ✅ All M1 hardware pins configurable via Kconfig
2. ✅ All M1 parameters configurable via Kconfig
3. ✅ Values accessible via CONFIG_* macros in sdkconfig.h
4. ✅ Defaults in sdkconfig.defaults work for ESP32-C6-WROOM-1
5. ✅ Configuration menu is organized and user-friendly
6. ✅ Help text is clear and comprehensive
7. ✅ GPIO ranges prevent invalid pin assignments
8. ✅ Documentation complete in docs/configuration.md
9. ✅ Build succeeds with default configuration
10. ✅ Configuration values logged at boot for verification

---

## References

- **ADR-012:** Compile-Time Configuration via ESP-IDF Kconfig
- **US05:** Compile-Time Configuration of Pins and Defaults
- [ESP-IDF Kconfig Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/kconfig.html)
- [ESP32-C6 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-c6_datasheet_en.pdf)
- [ESP32-C6 Pin Layout](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c6/hw-reference/index.html)

---

## Notes

- This is a foundational user story; thorough implementation is critical
- Configuration choices affect all subsequent M1 user stories
- Consider future M2 requirements when designing structure
- Use consistent naming conventions across all CONFIG_* items
- Document any ESP32-C6-specific constraints or limitations
- Consider hardware variant support for future products

---

**Implementation Status:** ✅ Completed  
**Completed Date:** 2025-10-03  
**Build Status:** ✅ Successful  
**Next User Story:** US01 - WiFi Configuration via AP Mode
