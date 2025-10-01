# Smart Window Sensor System

## Overview
This project aims to develop a smart window sensor system capable of monitoring both the open/closed state of windows and the position of the window handle (open, closed, or tilt/“gekippt”). The system integrates custom firmware, robust mechanical design, and a 3D-printed housing for reliable operation and easy installation.

## Objectives
- Detect and report both the window state (open/closed) and the handle position (open, closed, or tilt/“gekippt”)
- Wireless communication using Wi-Fi (initial version), with future support for Thread/Matter (Zigbee-based)
- Hardware platform: ESP32-C6 microcontroller
- Firmware development using Espressif IDF
- Low power consumption for long battery life
- Easy installation and maintenance
- Durable, attractive printed housing with secure mounting

## Hardware
* ESP32-C6 microcontroller
* Window state detection using a magnetic reed switch
* Handle position detection using three reed sensors: as the window handle is operated, a magnet mounted to the window locking pin (German: Zapfen) moves along the sensors, allowing precise identification of the handle position (closed, open, or tilt/"gekippt"). This design enables the sensor module to be mounted discreetly between the inner and outer window frame, hidden from view and protected from tampering.
* An additional reed sensor detects whether the window sash is actually tilted or opened, enabling the system to distinguish between the handle being in the open/tilt position and the window itself remaining closed.
* Battery power supply (replaceable or rechargeable)
* Status LED for local feedback

## Firmware
- Efficient polling and event-driven state detection
- Power management (sleep modes, battery monitoring)
- Secure wireless communication protocol (Wi-Fi, Thread/Matter in future)
- OTA firmware update capability
- Error handling and diagnostics

## Mechanical & Housing Design
- Compact, robust enclosure suitable for 3D printing (PLA, ABS, PETG)
- Snap-fit or screw-based assembly for easy access to internals
- Mounting features for various window types (adhesive, screws, clips)
- Weather-resistant design for indoor/outdoor use
- Space for sensor, PCB, battery, and status LED

## Deliverables
- Schematics and PCB layout
- Firmware source code and documentation
- 3D CAD files for housing and mechanical parts
- Assembly and installation instructions
- Bill of materials (BOM)

## Milestones
1. Requirements and architecture definition
2. Hardware prototyping and sensor selection
3. Firmware development and initial testing
4. Mechanical design and 3D printing prototypes
5. Integration, field testing, and iteration
6. Final documentation and release

---

For questions or contributions, please contact the project maintainer.
