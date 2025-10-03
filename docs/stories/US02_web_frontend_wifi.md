# US02: Web Frontend for WiFi Setup

**As a** device owner
**I want** a web interface in AP mode
**So that** I can enter and save WiFi credentials securely

## Acceptance Criteria
- Given I am connected to the device’s AP,
  When I access the web frontend and enter the device PIN,
  Then I can view and submit WiFi credentials.
- Given I submit valid credentials,
  When the device saves them,
  Then it reboots and attempts to connect to the configured WiFi.
