# US05: Compile-Time Configuration of Pins and Defaults

**As a** developer
**I want** all hardware pins and default WiFi parameters to be configurable at compile time via Kconfig
**So that** the firmware can be adapted for different hardware versions

## Acceptance Criteria
- Given the project is built,
  When I set pin assignments and default parameters in Kconfig,
  Then the firmware uses these values and they are accessible in code via `sdkconfig.h`.
