# How to Connect an ESP32 Device to WSL (Windows Subsystem for Linux)

This guide explains how to access and flash an ESP32 device from your WSL (Ubuntu) environment on Windows.

---

## 1. Plug in the ESP32 Device via USB
Connect your ESP32 development board to your Windows PC using a USB cable.

## 2. Identify the Serial Port in Windows
- Open Device Manager (Win+X → Device Manager).
- Expand "Ports (COM & LPT)" and note the COM port number (e.g., COM5) for your ESP32.

## 3. Enable USB Passthrough to WSL
- Open PowerShell as Administrator and run:
  ```powershell
  wsl --list --verbose
  wsl --shutdown
  ```
- Plug in your ESP32 device.
- For WSL2 on Windows 11, use:
  ```powershell
  wsl --usb
  ```
- Alternatively, use [usbipd-win](https://github.com/dorssel/usbipd-win):
  1. Install usbipd-win from GitHub.
  2. List USB devices:
     ```powershell
     usbipd list
     ```
  3. Attach the ESP32 device to WSL:
     ```powershell
     usbipd attach --busid <busid>
     ```

## 4. Verify Device in WSL
In your Ubuntu terminal, run:
```bash
ls /dev/ttyACM* /dev/ttyUSB*
dmesg | tail
```
You should see a device such as `/dev/ttyACM0` or `/dev/ttyUSB0`.

## 5. Add User to dialout Group (if needed)
To access serial devices, add your user to the `dialout` group:
```bash
sudo usermod -aG dialout $USER
# Log out and back in for changes to take effect
```

## 6. Flash and Monitor ESP32 from WSL
Use ESP-IDF tools as usual:
```bash
idf.py flash
idf.py monitor
```
If you encounter permission errors, check group membership and device path.

---

## Troubleshooting
- If the device does not appear in `/dev/ttyACM*` or `/dev/ttyUSB*`, reattach the USB device using `usbipd` or restart WSL.
- Ensure you are running WSL2 and Windows 11 for best USB support.
- Some USB-to-serial adapters may require additional drivers on Windows.
- If flashing fails, try a different USB cable or port.

## References
- [usbipd-win GitHub](https://github.com/dorssel/usbipd-win)
- [WSL USB device support documentation](https://learn.microsoft.com/en-us/windows/wsl/connect-usb)
- [ESP-IDF Get Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)
