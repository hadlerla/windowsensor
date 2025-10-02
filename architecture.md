# Firmware Architecture Overview

This document provides an overview of the firmware architecture and summarizes all major architectural decisions for the project. Each decision is documented in a dedicated Architecture Decision Record (ADR) and referenced here for easy access.

## Architectural Process
- All significant architectural questions are documented as ADRs in `docs/adr/`.
- ADRs follow the template in `docs/adr-template.md`.
- This overview is updated whenever a new ADR is accepted.

## Summary of Architectural Decisions

| Decision | Summary | ADR Reference |
|----------|---------|--------------|
| (Example) Firmware update strategy | OTA updates not supported; flashing via programming pins only | [ADR-001](docs/adr/ADR-001.md) |
| (Example) Sensor debouncing | Hardware debouncing using 74HC logic ICs | [ADR-002](docs/adr/ADR-002.md) |

*Add new decisions as ADRs are created and accepted.*

## How to Contribute
- See `CONTRIBUTING.md` for the Embedded Architect mode workflow.
- Use the ADR template in `docs/adr-template.md` for all new decisions.
- Update this overview after each accepted ADR.

## References
- ADR template: `docs/adr-template.md`
- ADRs directory: `docs/adr/`
- Contribution guidelines: `CONTRIBUTING.md`
