# Project Roadmap

## Milestone M1: WiFi Configuration Enablement

**Goal:** Enable secure, flexible WiFi configuration for the window sensor device, with persistent storage of credentials and clear user feedback via RGB LED. All hardware pin assignments and default parameters are managed at compile time using ESP-IDF Kconfig.

### User Stories (Proposed Development Order)

| ID   | Title                                      | Status      | Story File                                 |
|------|---------------------------------------------|-------------|---------------------------------------------|
| US05 | Compile-Time Configuration of Pins/Defaults | not-started | docs/stories/US05_compile_time_config.md    |
| US01 | WiFi Configuration via AP Mode              | ready       | docs/stories/US01_wifi_ap_mode.md           |
| US03 | Secure Storage of WiFi Credentials          | ready       | docs/stories/US03_secure_wifi_storage.md    |
| US04 | RGB LED State Indication                    | ready       | docs/stories/US04_rgb_led_state.md          |
| US02 | Web Frontend for WiFi Setup                 | ready       | docs/stories/US02_web_frontend_wifi.md      |
| US06 | Authentication for Web Frontend             | ready       | docs/stories/US06_web_authentication.md     |

---

## Milestone M2: Matter Connectivity

**Goal:** Enable Matter fabric connectivity for the window sensor device, supporting commissioning via Home Assistant and other Matter controllers. External button simulates window sensor state and triggers Matter events. Device uses the same PIN for authentication as in M1.

### User Stories (Proposed Development Order)

| ID   | Title                                      | Status      | Story File                                 |
|------|---------------------------------------------|-------------|---------------------------------------------|
| US07 | Button Debouncing for External Input        | not-started | docs/stories/US07_button_debouncing.md      |
| US08 | Matter Stack Integration                    | ready       | docs/stories/US08_matter_stack.md           |
| US09 | Matter Commissioning Mode                   | ready       | docs/stories/US09_matter_commissioning.md   |
| US10 | Window Sensor State Simulation              | ready       | docs/stories/US10_sensor_simulation.md      |
| US11 | Matter Event Generation                     | ready       | docs/stories/US11_matter_events.md          |
| US12 | Interoperability Testing                    | ready       | docs/stories/US12_interoperability.md       |

---

## Milestone Status
- M1: not-started
- M2: not-started

## References
- See individual user story files in `docs/stories/`
- Architecture decisions in `architecture.md` and ADRs
