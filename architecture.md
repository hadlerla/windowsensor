# Firmware Architecture Overview

This document provides an overview of the firmware architecture and summarizes all major architectural decisions for the project. Each decision is documented in a dedicated Architecture Decision Record (ADR) and referenced here for easy access.

## Architectural Process
- All significant architectural questions are documented as ADRs in `docs/adr/`.
- ADRs follow the template in `docs/adr-template.md`.
- This overview is updated whenever a new ADR is accepted.

## Summary of Architectural Decisions

| Decision | Summary | ADR Reference |
|----------|---------|--------------|
| System architecture | Modular component-based, FreeRTOS tasks, event-driven state management | [ADR-001](docs/adr/ADR-001.md) |
| Hardware abstraction | HAL for sensor and peripheral access, debouncing logic | [ADR-002](docs/adr/ADR-002.md) |
| Protocol stack integration | Dual protocol (Thread/Wi-Fi) with automatic fallback | [ADR-003](docs/adr/ADR-003.md) |
| Power management | Event-driven sleep/wake, battery monitoring via ADC | [ADR-004](docs/adr/ADR-004.md) |
| Security architecture | NVS encryption, secure boot, role-based access control | [ADR-005](docs/adr/ADR-005.md) |
| Error handling & diagnostics | Structured logging, self-test, watchdog, persistent error logs | [ADR-006](docs/adr/ADR-006.md) |
| Update & config management | Physical flashing, encrypted NVS, reset via setup button | [ADR-007](docs/adr/ADR-007.md) |
| Testing & QA | ESP-IDF Unity, automated unit/integration tests, hardware-in-the-loop | [ADR-008](docs/adr/ADR-008.md) |
| Documentation & code standards | Doxygen-style comments, markdown docs, review checklists | [ADR-009](docs/adr/ADR-009.md) |
| Performance optimization | Targeted profiling, event handling, hardware features | [ADR-010](docs/adr/ADR-010.md) |
| Code quality & AI usage | clang-format, cppcheck, pre-commit hooks, AI-assisted development with review and attribution | [ADR-011](docs/adr/ADR-011.md) |
| Compile-time configuration | ESP-IDF Kconfig for hardware pins and default parameters | [ADR-012](docs/adr/ADR-012.md) |
| Web server architecture | ESP-IDF HTTP server with embedded files, HTTPS, session management | [ADR-013](docs/adr/ADR-013.md) |
| WiFi state machine | Event-driven state machine with explicit states and transitions | [ADR-014](docs/adr/ADR-014.md) |
| Authentication & PIN management | Random PIN at first boot, encrypted NVS storage, brute-force protection | [ADR-015](docs/adr/ADR-015.md) |
| RGB LED control | Dedicated LED task with pattern queue and priority handling | [ADR-016](docs/adr/ADR-016.md) |
| NVS partition layout | Multiple namespaces by function, consistent key naming convention | [ADR-017](docs/adr/ADR-017.md) |
| WiFi error handling | Automatic retry with exponential backoff, error classification, graceful fallback | [ADR-018](docs/adr/ADR-018.md) |

*Add new decisions as ADRs are created and accepted.*

## How to Contribute
- See `CONTRIBUTING.md` for the Embedded Architect mode workflow.
- Use the ADR template in `docs/adr-template.md` for all new decisions.
- Update this overview after each accepted ADR.

## References
- ADR template: `docs/adr-template.md`
- ADRs directory: `docs/adr/`
- Contribution guidelines: `CONTRIBUTING.md`
