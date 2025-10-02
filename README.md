# Smart Window Sensor System

## Overview
This project aims to develop a smart window sensor system capable of monitoring both the open/closed state of windows and the position of the window handle (open, closed, or tilt/“gekippt”). The system integrates custom firmware, robust mechanical design, and a 3D-printed housing for reliable operation and easy installation.

## Objectives
- Detect and report both the window state (open/closed) and the handle position (open, closed, or tilt/“gekippt”)
- Wireless communication using Wi-Fi (initial version), with future support for Thread/Matter (Zigbee-based)
- Hardware platform: ESP32-C6 microcontroller
- Firmware development using Espressif IDF
- Low power consumption for long battery life (CR2477 ~ 1000 mAh)
- Easy installation and maintenance
- Durable, attractive printed housing with secure mounting

## Hardware
* ESP32-C6 microcontroller
* During firmware development, an ESP32-C6 development board on a breadboard is used. The necessary circuits will also be placed and wired on the breadboard. In production, a custom-designed and manufactured PCB will be used.
* A network of 74HC... logic ICs is used to debounce the signals from the reed sensors via integrated Schmitt triggers. This is necessary because the mechanical contacts of the reed sensors tend to bounce when they change state, which could lead to false readings if not properly managed. Any change in an input signal also sets a flip-flop, which triggers a wakeup signal. After processing the input signals, the ESP32-C6 resets the flip-flops and returns to sleep mode.
* Window state detection using a magnetic reed switch
* Handle position detection using three reed sensors: as the window handle is operated, a magnet mounted to the window locking pin (German: Zapfen) moves along the sensors, allowing precise identification of the handle position (closed, open, or tilt/"gekippt"). This design enables the sensor module to be mounted discreetly between the inner and outer window frame, hidden from view and protected from tampering.
* An additional reed sensor detects whether the window sash is actually tilted or opened, enabling the system to distinguish between the handle being in the open/tilt position and the window itself remaining closed.
* Battery power supply (replaceable or rechargeable)
* Status LED for local feedback
* Physical setup button for initiating device commissioning and pairing with a Matter/Thread network
* Dedicated programming pins for flashing firmware during development and production (OTA updates are not supported)

## Matter Endpoints and Clusters

The device exposes two Matter endpoints:

| Endpoint                | Matter Device Type | Cluster                | Description                                 |
|-------------------------|-------------------|------------------------|---------------------------------------------|
| Window Frame Sensor     | Contact Sensor    | Contact Sensor Cluster | Reports window open/closed (binary)         |
| Handle Position Sensor  | Window Covering   | Window Covering Cluster| Reports handle position (closed/open/tilt)  |

**Window Frame Sensor Endpoint:**
- Device Type: Contact Sensor (Device Type ID: 0x0016)
- Cluster: Contact Sensor Cluster (reports open/closed)

**Handle Position Endpoint:**
- Device Type: Window Covering (Device Type ID: 0x0013)
- Cluster: Window Covering Cluster (reports handle position: closed, open, tilt/"gekippt")

### Device Commissioning and Setup

To securely add the device to a Matter/Thread network, a physical setup button is provided. Pressing this button puts the device into pairing mode, allowing it to be discovered and commissioned by a Border Router or Thread controller. This is required for secure onboarding and user-friendly setup in Matter ecosystems.

## Firmware
* Efficient polling and event-driven state detection
* Power management (sleep modes, battery monitoring)
* Secure wireless communication protocol (Thread/Matter)
* Device setup code and attestation credentials must be flashed to non-volatile memory during manufacturing or initial programming, as required by Matter standards. Each production device must have a unique setup code and credentials; for development and testing, a shared code may be used.
* Error handling and diagnostics
## Security Requirements (Matter/Thread)

The device must comply with Matter and Thread security standards:

- All communication must be end-to-end encrypted using strong cryptography (AES-CCM, ECC).
- Device attestation: Each device must have unique attestation credentials and certificates to verify authenticity during commissioning.
- Secure commissioning: The onboarding process must use the setup code and cryptographic handshake to prevent unauthorized access.
- Network isolation: Only authenticated devices may join the Thread network.
- Access control: Role-based access control lists (ACLs) must be used to manage permissions for devices and users.

These requirements ensure confidentiality, integrity, and authenticity for all device interactions in a Matter/Thread network.

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
