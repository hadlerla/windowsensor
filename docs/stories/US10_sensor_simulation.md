# US10: Window Sensor State Simulation

**As a** device owner
**I want** the external button to simulate window sensor state (open/closed)
**So that** I can test the device functionality without a physical sensor

## Acceptance Criteria
- Given the device is operational,
  When I press the external button (short press),
  Then the device toggles the simulated window state (open ↔ closed).
- Given the window state changes,
  Then the device logs the state change.

## Dependencies
- US07 (Button Debouncing for External Input)

## Technical Notes
- Use a digital input to represent window state (1 = closed, 0 = open).
- State is toggled on each short press.
- No physical sensor integration in M2; this is simulation only.
