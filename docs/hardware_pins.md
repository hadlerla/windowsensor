# ESP32-C6 GPIO Pin Reference for Window Sensor

This document provides detailed GPIO pin information for the ESP32-C6 microcontroller, specifically for the window sensor firmware project.

**Target:** ESP32-C6-WROOM-1 Module  
**Last Updated:** 2025-10-03  
**Reference:** ESP32-C6 Datasheet v1.4

---

## Table of Contents

1. [Pin Overview](#pin-overview)
2. [Pin Categories](#pin-categories)
3. [Safe GPIO Pins](#safe-gpio-pins)
4. [Restricted Pins](#restricted-pins)
5. [Default Pin Assignments](#default-pin-assignments)
6. [Pin Multiplexing](#pin-multiplexing)
7. [Electrical Characteristics](#electrical-characteristics)
8. [Best Practices](#best-practices)

---

## Pin Overview

The ESP32-C6 has **26 GPIO pins** (GPIO0-GPIO25) with various capabilities and restrictions.

### Quick Reference Table

| GPIO | Safe for Use? | Default Function | Notes |
|------|---------------|------------------|-------|
| 0 | ✅ Yes | GPIO | Boot mode select (pull-up recommended) |
| 1 | ✅ Yes | GPIO | ADC1_CH0 |
| 2 | ✅ Yes | GPIO | ADC1_CH1, FSPIQ (flash in quad mode) |
| 3 | ✅ Yes | GPIO | ADC1_CH2 |
| 4 | ✅ Yes | GPIO | ADC1_CH3, FSPIHD (flash in quad mode) |
| 5 | ✅ Yes | GPIO | ADC1_CH4, FSPIWP (flash in quad mode) |
| 6 | ✅ Yes | GPIO | FSPICLK (flash clock) |
| 7 | ✅ Yes | GPIO | FSPID (flash data) |
| 8 | ✅ Yes | GPIO | **RGB LED (built-in on WROOM-1)** |
| 9 | ✅ Yes | GPIO | **BOOT button (on DevKitC-1)** |
| 10 | ✅ Yes | GPIO | FSPICS0 (flash chip select) |
| 11 | ✅ Yes | GPIO | VDD_SPI power |
| 12 | ⚠️ Caution | SPIHD | **Flash in QPI mode** |
| 13 | ⚠️ Caution | SPIWP | **Flash in QPI mode** |
| 14 | ⚠️ Caution | SPICS0 | **Flash chip select** |
| 15 | ⚠️ Caution | SPICLK | **Flash clock** |
| 16 | ⚠️ Caution | SPID | **Flash data** |
| 17 | ⚠️ Caution | SPIQ | **Flash in QPI mode** |
| 18 | ✅ Yes | GPIO | USB D- |
| 19 | ✅ Yes | GPIO | USB D+ |
| 20 | ✅ Yes | GPIO | UART0 RX (console) |
| 21 | ✅ Yes | GPIO | UART0 TX (console) |
| 22 | ✅ Yes | GPIO | |
| 23 | ✅ Yes | GPIO | |
| 24 | ❌ No | USB D- | **Reserved for USB** |
| 25 | ❌ No | USB D+ | **Reserved for USB** |

---

## Pin Categories

### Category 1: General Purpose GPIO (Recommended)

These pins are safe for general use without special considerations:

**GPIO: 0, 1, 3, 8, 9, 22, 23**

- No hardware restrictions
- Can be used for digital I/O, PWM, interrupts
- Suitable for buttons, LEDs, sensors

### Category 2: ADC-Capable GPIO

These pins can be used for analog input (in addition to digital):

**GPIO: 1, 2, 3, 4, 5**

- ADC1 channels 0-4
- 12-bit resolution (0-4095)
- Useful for analog sensors (temperature, light, etc.)

### Category 3: Boot and Strapping Pins

These pins affect boot behavior if held at specific levels:

**GPIO 0:** Boot mode selection
- Float or HIGH: Normal boot
- LOW: Download mode (firmware flashing)
- Recommendation: Use with external pull-up if connecting input

**GPIO 9:** Boot button (on dev boards)
- Pull-up by default
- Safe for button input with internal pull-up

### Category 4: Communication Peripherals

**UART0 (Console):**
- GPIO 20: RX
- GPIO 21: TX
- Used for serial console by default
- Can be remapped if needed

**USB:**
- GPIO 18: USB D- (can be GPIO if USB disabled)
- GPIO 19: USB D+ (can be GPIO if USB disabled)
- GPIO 24, 25: Hardware USB (cannot be GPIO)

---

## Safe GPIO Pins

### Highly Recommended (No Conflicts)

| GPIO | Use Case | Window Sensor Assignment |
|------|----------|-------------------------|
| 8 | RGB LED | ✅ Status LED (built-in WS2812) |
| 9 | Button Input | ✅ AP Mode Button (BOOT) |
| 4 | Digital Input | ✅ Window Sensor (M2) |
| 22, 23 | General I/O | Available for expansion |
| 1, 3 | ADC/GPIO | Available for analog sensors |

### Usable with Caution

| GPIO | Caution | Recommended Use |
|------|---------|----------------|
| 0 | Boot strapping | Avoid unless necessary |
| 2, 5, 6, 7, 10, 11 | Flash interface (dual/quad SPI) | Safe in dual SPI mode |
| 20, 21 | UART console | Avoid if serial debug needed |
| 18, 19 | USB | Avoid if USB needed |

---

## Restricted Pins

### Never Use (Hardware Reserved)

**GPIO 12-17:** Flash memory interface (QPI mode)
- These pins are connected to the flash chip
- Cannot be used as GPIO
- Firmware will fail if these are configured as GPIO

**GPIO 24-25:** USB hardware
- Hardwired to USB D- and D+
- Cannot be reconfigured
- Only accessible via USB peripheral

---

## Default Pin Assignments

### Window Sensor M1 Configuration

```
┌─────────────────────────────────────┐
│     ESP32-C6-WROOM-1 Module         │
├─────────────────────────────────────┤
│ GPIO 8  → RGB LED (WS2812 built-in) │ ← Status indication
│ GPIO 9  → BOOT Button               │ ← AP mode trigger
│ GPIO 4  → Window Sensor (M2)        │ ← Reed switch input
│ GPIO 20 → UART RX (console)         │ ← Serial debug
│ GPIO 21 → UART TX (console)         │ ← Serial debug
├─────────────────────────────────────┤
│ Available: GPIO 1, 3, 22, 23        │ ← Future expansion
└─────────────────────────────────────┘
```

### Pin Function Summary

| Function | GPIO | Direction | Pull | Notes |
|----------|------|-----------|------|-------|
| RGB LED | 8 | Output | - | WS2812 addressable LED |
| AP Button | 9 | Input | Pull-up | Internal pull-up enabled |
| Window Sensor | 4 | Input | Pull-up | Reed switch (M2) |
| Console RX | 20 | Input | - | Serial debugging |
| Console TX | 21 | Output | - | Serial debugging |

---

## Pin Multiplexing

### Peripheral Multiplexing Examples

Most ESP32-C6 peripherals can be mapped to any GPIO via the IO MUX:

**I2C:**
```c
i2c_config_t conf = {
    .sda_io_num = 22,  // Any safe GPIO
    .scl_io_num = 23,  // Any safe GPIO
    // ...
};
```

**SPI:**
```c
spi_bus_config_t buscfg = {
    .mosi_io_num = 22,  // Any safe GPIO
    .miso_io_num = 23,  // Any safe GPIO
    .sclk_io_num = 3,   // Any safe GPIO
    // ...
};
```

**PWM (LEDC):**
```c
ledc_channel_config_t ledc_channel = {
    .gpio_num = 22,  // Any safe GPIO
    // ...
};
```

---

## Electrical Characteristics

### GPIO Specifications

| Parameter | Min | Typ | Max | Unit |
|-----------|-----|-----|-----|------|
| Input HIGH voltage | 2.0 | - | 3.6 | V |
| Input LOW voltage | -0.3 | - | 0.8 | V |
| Output HIGH voltage | 2.4 | 3.3 | - | V |
| Output LOW voltage | - | 0 | 0.4 | V |
| Source current (per pin) | - | - | 40 | mA |
| Sink current (per pin) | - | - | 28 | mA |
| Input leakage current | - | - | 1 | μA |

**Important:**
- Total source current (all pins): 200mA max
- Total sink current (all pins): 200mA max
- Use external transistors for loads >20mA

### Pull-up/Pull-down Resistors

| Type | Resistance | Notes |
|------|------------|-------|
| Pull-up | 45 kΩ | Configurable in software |
| Pull-down | 45 kΩ | Configurable in software |

---

## Best Practices

### 1. Pin Selection Guidelines

✅ **DO:**
- Use GPIO 0-11, 18-23 for general I/O
- Use GPIO 1-5 for ADC applications
- Enable internal pull-ups for button inputs
- Check dev board schematics for pre-connected pins

❌ **DON'T:**
- Use GPIO 12-17 (flash interface)
- Use GPIO 24-25 (USB hardware)
- Exceed 40mA per pin or 200mA total
- Connect 5V signals directly (use level shifter)

### 2. Button Input Example

```c
// GPIO 9 as button input with pull-up
gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << 9),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_NEGEDGE,
};
gpio_config(&io_conf);
```

### 3. LED Output Example

```c
// GPIO 8 as LED output (for WS2812)
led_strip_config_t strip_config = {
    .strip_gpio_num = 8,
    .max_leds = 1,
};
led_strip_rmt_config_t rmt_config = {
    .resolution_hz = 10 * 1000 * 1000,  // 10MHz
};
led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip);
```

### 4. Protection Recommendations

For external connections:
- Add series resistor (220-470Ω) for LEDs
- Use Schottky diode for inductive loads
- Add TVS diode for ESD protection on exposed pins
- Use optocoupler for isolation if needed

---

## Troubleshooting GPIO Issues

### Symptom: GPIO not working as expected

**Possible Causes:**
1. Pin is reserved (12-17, 24-25)
2. Pin has boot strapping conflict (GPIO 0)
3. Pin is used by another peripheral
4. Electrical overload (>40mA)

**Solution:**
1. Check pin restrictions in this document
2. Use logic analyzer to verify signal
3. Check ESP-IDF peripheral configuration
4. Add external driver if current exceeds limits

### Symptom: Boot issues after GPIO configuration

**Possible Causes:**
1. GPIO 0 held LOW at boot (enters download mode)
2. GPIO 9 held LOW at boot (may affect boot)

**Solution:**
1. Ensure GPIO 0 is not pulled LOW externally
2. Add delay before configuring boot-related pins

### Symptom: Intermittent GPIO behavior

**Possible Causes:**
1. Insufficient pull-up/pull-down
2. Electrical noise on long wires
3. ESD damage

**Solution:**
1. Enable stronger internal pull-ups or add external (1-10kΩ)
2. Use twisted pair or shielded cable
3. Add capacitor (0.1μF) near pin for filtering

---

## Pin Change Summary (from Development to Production)

If you need to change pin assignments between hardware revisions:

1. Update Kconfig in `main/Kconfig.projbuild`
2. Update defaults in `sdkconfig.defaults`
3. Rebuild firmware: `idf.py fullclean && idf.py build`
4. Update this documentation
5. Test all affected peripherals

---

## References

- [ESP32-C6 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-c6_datasheet_en.pdf)
- [ESP32-C6 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32-c6_technical_reference_manual_en.pdf)
- [ESP-IDF GPIO Driver Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c6/api-reference/peripherals/gpio.html)
- [ESP32-C6-DevKitC-1 Schematic](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c6/esp32-c6-devkitc-1/index.html)

---

## Revision History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | 2025-10-03 | Initial pin reference for M1 |

---

**Always verify pin assignments with actual hardware schematics before deployment.**
