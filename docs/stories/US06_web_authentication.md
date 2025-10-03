# US06: Authentication for Web Frontend

**As a** device owner
**I want** access to the WiFi configuration web frontend to be protected by a device PIN
**So that** only authorized users can change network settings

## Acceptance Criteria
- Given I access the web frontend,
  When I enter the correct device PIN,
  Then I am allowed to configure WiFi.
- Given I enter an incorrect PIN,
  Then access is denied.
