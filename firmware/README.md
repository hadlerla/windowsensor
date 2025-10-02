# Fenstersensor Firmware

This directory contains the ESP32 firmware for the fenstersensor project.

## Structure
- `main/` - Main application source
- `components/` - Custom ESP-IDF components
- `test/` - Unit and integration tests
- `docs/` - Firmware-specific documentation

## Build Instructions
1. Install ESP-IDF and set up environment variables.
2. Run `idf.py build` in this directory.
3. Flash with `idf.py -p <PORT> flash`.

## Contribution
Follow the incremental development and ADR workflow described in the project root `CONTRIBUTING.md`.
