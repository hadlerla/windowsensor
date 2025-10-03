# US11: Matter Event Generation

**As a** device owner
**I want** the device to send Matter events when the window state changes
**So that** controllers like Home Assistant can react to state changes

## Acceptance Criteria
- Given the device is commissioned to a Matter fabric,
  When the simulated window state changes (via button press),
  Then the device sends a Matter event to the fabric.
- Given a Matter controller is listening,
  When the event is sent,
  Then the controller receives and logs the state change.

## Dependencies
- US08 (Matter Stack Integration)
- US09 (Matter Commissioning Mode)
- US10 (Window Sensor State Simulation)

## Technical Notes
- Use Matter's contact sensor cluster or equivalent for state reporting.
- Event should include timestamp and state (open/closed).
