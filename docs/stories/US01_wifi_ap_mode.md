# US01: WiFi Configuration via AP Mode

**As a** device owner
**I want** the device to enter AP mode when no WiFi configuration is present or when I press the AP activation button
**So that** I can connect and configure WiFi credentials using a web interface

## Acceptance Criteria
- Given the device has no WiFi configuration,
  When it powers up,
  Then it starts in AP mode and broadcasts a WiFi network.
- Given the device is in normal or Zigbee mode,
  When I press the AP activation button for the configured duration,
  Then it enters AP mode and broadcasts a WiFi network.
