# US04: RGB LED State Indication

**As a** device owner
**I want** the RGB LED to indicate the device’s WiFi state
**So that** I can easily see if the device is in AP mode, disconnected, or connected

## Acceptance Criteria
- Given the device is in AP mode,
  Then the LED blinks blue.
- Given the device is in disconnected normal mode,
  Then the LED blinks red.
- Given the device is connected to WiFi,
  Then the LED blinks green.
