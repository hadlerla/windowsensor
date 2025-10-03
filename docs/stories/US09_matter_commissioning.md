# US09: Matter Commissioning Mode

**As a** device owner
**I want** to initiate Matter commissioning by pressing the external button
**So that** I can add the device to a Matter fabric using Home Assistant or other controllers

## Acceptance Criteria
- Given the device is powered on and WiFi is configured,
  When I perform a short press (<1 sec, debounced) on the external button,
  Then the device enters Matter commissioning mode.
- Given the device is in commissioning mode,
  When I enter the device PIN in a Matter controller (e.g., Home Assistant),
  Then the device joins the Matter fabric.
- Given the device is already commissioned,
  When I perform a short press on the external button,
  Then the device re-enters commissioning mode for re-pairing.

## Dependencies
- US07 (Button Debouncing for External Input)
- US08 (Matter Stack Integration)

## Technical Notes
- Device PIN is the same as used for WiFi AP authentication (from M1).
- No QR code generation; manual code entry only.
- Support re-commissioning for fabric switching or reset.
