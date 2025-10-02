# Embedded Architect Mode

This project uses an Embedded Architect mode to ensure all architectural decisions are documented, reviewed, and traceable.

**Key Documents:**
- [CONTRIBUTING.md](CONTRIBUTING.md): Contribution and architectural workflow
- [architecture.md](architecture.md): Firmware architecture overview and summary of decisions
- [ADR template](docs/adr-template.md): Reusable template for Architecture Decision Records (ADRs)
- ADRs directory: `docs/adr/` (contains all ADRs)

**Working Instructions:**
1. Document all significant architectural questions as ADRs using the template.
2. Store ADRs in `docs/adr/` and reference them in `architecture.md`.
3. Follow the workflow in `CONTRIBUTING.md` for reviews and updates.
4. Update `architecture.md` after each accepted ADR for easy reference.

# Development Tools & Frameworks

## Hardware Development

- **KiCAD** (v8.x or latest stable): Schematic capture, PCB layout, BOM generation.
- **Breadboard & ESP32-C6 Dev Board**: For prototyping and initial hardware validation.
- **Basic Electronics Lab Tools**: Multimeter, oscilloscope, soldering station, logic analyzer (optional).
- **Programming Tools**: USB-to-serial adapter, ESP32-C6 programming pins, jumper wires.


## Firmware Development

- **Operating System**: Windows 10/11 with WSL2 (Ubuntu 22.04 LTS recommended)
- **VS Code**: Editor with extensions:
	- GitHub Copilot (AI-assisted development; always review and verify AI-generated code)
	- Espressif IDF Extension
	- C/C++ Extension
	- GitLens
	- Markdown All in One
- **ESP-IDF**: Espressif IoT Development Framework (v5.2 or latest stable)
- **Python 3.8+**: Required for ESP-IDF tools
- **Git**: Version control
- **Unit Testing**: ESP-IDF Unity framework (`idf.py test`)
- **Build & Flash Tools**: ESP-IDF build system (`idf.py build`, `idf.py flash`, `idf.py monitor`)
- **Code Formatters & Linters**: clang-format (formatting), cppcheck (linting), pre-commit hooks recommended

### Code Quality & Development Guidelines
- Run code formatters and linters before submitting code for review.
- Use AI tools for boilerplate and documentation, but always verify correctness, security, and maintainability.
- Attribute AI-generated code in comments or commit messages.
- Update documentation (README, architecture.md, module docs) as part of each increment.
- For minor changes or bug fixes, a streamlined process may be used (e.g., direct commit with clear documentation and code review).

### Firmware Development Environment Setup Instructions

1. **Install WSL2 and Ubuntu 22.04 LTS**
	- Follow Microsoft’s official guide to enable WSL2 and install Ubuntu 22.04 LTS.
	- Verify with: `wsl --list --verbose` (should show Ubuntu running in WSL2 mode).

2. **Update Ubuntu Packages**
	- `sudo apt update && sudo apt upgrade -y`
	- Check: No errors, system up-to-date.

3. **Install Required Packages**
	- `sudo apt install git python3 python3-pip build-essential cmake ninja-build flex bison gperf libssl-dev libffi-dev libusb-1.0-0 libusb-1.0-0-dev python3-setuptools python3-serial python3-click python3-cryptography python3-future python3-pyparsing python3-pyelftools`
	- Check: All packages install without error.

4. **Install VS Code (Windows host)**
	- Download and install from [code.visualstudio.com](https://code.visualstudio.com/).
	- Install recommended extensions (see above).
	- Check: VS Code launches, extensions installed.

5. **Install ESP-IDF (v5.2 or latest stable)**
	- Follow Espressif’s official [Get Started guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html):
	  - Clone ESP-IDF: `git clone --recursive https://github.com/espressif/esp-idf.git`
	  - Checkout latest stable: `cd esp-idf && git checkout v5.2`
	  - Run install script: `./install.sh`
	  - Set up environment: `source export.sh`
	- Check: `idf.py --version` returns v5.2 or latest stable.

6. **Verify Python Environment**
	- `python3 --version` (should be >= 3.8)
	- `pip3 --version`
	- Check: No errors, correct versions.

7. **Clone Project Repository**
	- `git clone <repo-url>`
	- `cd firmware-fenstersensor`
	- Check: Repository cloned, files present.

8. **Build Example Project**
	- `idf.py build`
	- Check: Build completes without errors, `build/` directory created.

9. **Flash Firmware to ESP32-C6**
	- Connect dev board via USB.
	- `idf.py flash`
	- Check: Flash completes, device boots.

10. **Monitor Serial Output**
	 - `idf.py monitor`
	 - Check: Serial output visible, device running.

11. **Run Unit Tests**
	 - `idf.py test`
	 - Check: All tests pass, Unity test results shown.

12. **Git Version Control**
	 - `git status`, `git log`, `git push/pull`
	 - Check: No errors, repository syncs with remote.

**Checkpoint Summary:**
- WSL2 and Ubuntu installed and updated
- VS Code and extensions installed
- ESP-IDF installed and verified
- Python and dependencies installed
- Project cloned and builds successfully
- Firmware flashes and runs on hardware
- Unit tests pass
- Git workflow operational

## Mechanical Engineering

- **FreeCAD** (v0.22 or latest stable): 3D modeling, mechanical part design, export to STL/STEP for printing/manufacturing.
- **3D Printer**: For prototyping enclosures (PLA, ABS, PETG recommended).
- **CAD File Management**: Use Git for versioning CAD files and documentation.

---

# Product Iterations

### Iteration 1: Matter over Wi-Fi
- Device operates using Matter protocol over Wi-Fi.
- Wi-Fi configuration via temporary access point and secure web interface (see Wi-Fi Configuration section).
- Simplified commissioning and setup for development and initial deployment.

### Iteration 2: Matter over Thread (Zigbee-based) with Wi-Fi Fallback
- Device operates using Matter protocol over Thread (Zigbee-based) for mesh networking and low power.
- Wi-Fi fallback supported for environments without Thread.
- Commissioning and setup process supports both Thread and Wi-Fi, using the same device PIN for authentication.

## Device Mode Configuration and Fallback (Best Practices)

- Both Matter over Wi-Fi and Matter over Thread operate on the same hardware (ESP32-C6).
- On boot, the device automatically attempts to join a Thread network; if unavailable, it falls back to Wi-Fi.
- Users can select the preferred network mode (Thread or Wi-Fi) via the configuration web interface or a mobile app.
- The status LED indicates the current network mode (e.g., different colors or blink patterns).
- The last successful network mode is saved in non-volatile storage, so the device remembers its configuration after reboot.
- Pressing and holding the setup button resets the network mode and triggers reconfiguration.
- Documentation and user guides should clearly explain fallback logic and manual mode switching.

## Wi-Fi Configuration

- On first boot or after a Wi-Fi reset, the device starts in configuration mode and creates a temporary Wi-Fi access point (AP).
- The AP SSID is unique to each device (e.g., `WindowSensor-<last6MAC>`).
- The user connects to the AP using a smartphone or computer.
- After connecting, the user accesses a simple web interface (e.g., at `192.168.4.1`) to enter their home Wi-Fi credentials (SSID and password).
- The configuration webpage requires the device PIN (the same PIN used for Matter/Thread commissioning) as the login secret to access the setup form.
- The device saves the credentials securely in non-volatile storage and reboots to join the configured Wi-Fi network.
- If Wi-Fi connection fails, the device automatically returns to configuration mode and re-enables the AP.
- Pressing and holding the setup button for 5 seconds resets the Wi-Fi credentials and restarts the configuration process.

**Security Considerations:**
- The configuration web page uses the device PIN for authentication, ensuring only authorized users can configure the device. This PIN is the same as used for Matter/Thread onboarding.
- Wi-Fi credentials are stored securely using ESP-IDF’s NVS (non-volatile storage) with encryption enabled.
## Wi-Fi Configuration (Iteration 1: Matter over Wi-Fi)

- On first boot or after a Wi-Fi reset, the device starts in configuration mode and creates a temporary Wi-Fi access point (AP).
- The AP SSID is unique to each device (e.g., `WindowSensor-<last6MAC>`).
- The user connects to the AP using a smartphone or computer.
- After connecting, the user accesses a simple web interface (e.g., at `192.168.4.1`) to enter their home Wi-Fi credentials (SSID and password).
- The configuration webpage requires the device PIN (the same PIN used for Matter/Thread commissioning) as the login secret to access the setup form.
- The device saves the credentials securely in non-volatile storage and reboots to join the configured Wi-Fi network.
- If Wi-Fi connection fails, the device automatically returns to configuration mode and re-enables the AP.
- Pressing and holding the setup button for 5 seconds resets the Wi-Fi credentials and restarts the configuration process.

**Security Considerations:**
- The configuration web page uses the device PIN for authentication, ensuring only authorized users can configure the device. This PIN is the same as used for Matter/Thread onboarding.
- Wi-Fi credentials are stored securely using ESP-IDF’s NVS (non-volatile storage) with encryption enabled.
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
* Firmware development is based on the Espressif IoT Development Framework (IDF)
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
