# US07: Button Debouncing for External Input

**As a** developer
**I want** software-based debouncing for the external button
**So that** button press events are reliable and do not trigger false positives

## Acceptance Criteria
- Given the external button is pressed,
  When the button state changes,
  Then the software debounces the input and only registers valid press events.
- Given a short press (<1 sec) is detected,
  Then the device triggers Matter commissioning mode.
- Given a long press (2 sec for WiFi mode, 5 sec for Zigbee mode) is detected,
  Then the device triggers AP mode.

## Dependencies
- US05 (Compile-Time Configuration of Pins/Defaults)

## Technical Notes
- Implement debouncing logic with configurable thresholds (compile-time via Kconfig).
- Support press duration detection for short vs. long press differentiation.
