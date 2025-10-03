# US12: Interoperability Testing

**As a** device owner
**I want** the device to be interoperable with major Matter controllers
**So that** I can use it with Home Assistant, Apple HomeKit, Google Home, and Amazon Alexa

## Acceptance Criteria
- Given the device is commissioned to Home Assistant,
  When I trigger a state change,
  Then Home Assistant receives and displays the event.
- Given the device is commissioned to Apple HomeKit, Google Home, or Amazon Alexa,
  When I trigger a state change,
  Then the respective controller receives and displays the event.

## Dependencies
- US09 (Matter Commissioning Mode)
- US11 (Matter Event Generation)

## Technical Notes
- Test with at least Home Assistant and one other controller (e.g., Apple HomeKit).
- Verify that commissioning and event handling work across platforms.
- Document any platform-specific quirks or limitations.
