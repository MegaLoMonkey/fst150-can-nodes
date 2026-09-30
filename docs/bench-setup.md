# Phase 0 Bench Setup

Steps to build the first bench prototype for validating one tyre node end-to-end before scaling to four corners plus steering.

## Bill of materials

- 1x LOLIN32 Lite ESP32 dev board (existing)
- 1x Waveshare MLX90640-D55 thermal camera
- 1x Waveshare SN65HVD230 CAN transceiver breakout
- 2x 120 ohm resistors for CAN bus termination
- Breadboard and jumper wires
- USB cable (Micro-USB for LOLIN32 Lite)
- 12V bench power supply (optional, USB power works for bench)

## Software

- Windows 11 with VS Code
- PlatformIO IDE extension
- Git and GitHub Desktop
- Race Studio 3 (for MXS configuration testing)
- PCAN-View or PCAN-Explorer (for CAN bus monitoring)
- PEAK PCAN-USB FD hardware interface

## Wiring

### MLX90640 to ESP32 (I2C)

| MLX90640 | ESP32 GPIO | Notes |
|----------|------------|-------|
| VIN | 3.3V | do NOT use 5V from USB |
| GND | GND | common ground |
| SDA | GPIO 23 | I2C data |
| SCL | GPIO 19 | I2C clock |

### SN65HVD230 to ESP32 (TWAI/CAN)

| SN65HVD230 | ESP32 GPIO | Notes |
|------------|------------|-------|
| 3.3V | 3.3V | must be 3.3V not 5V |
| GND | GND | common ground |
| CAN RX | GPIO 4 | ESP32 receives here |
| CAN TX | GPIO 5 | ESP32 transmits here |
| CANH | to PCAN-USB CAN H | bus wire |
| CANL | to PCAN-USB CAN L | bus wire |

Bus needs 120 ohm termination at both ends. The Waveshare SN65HVD230 board has an onboard 120 ohm resistor already (marked 121 on the PCB). The PCAN-USB FD has switchable termination. Enable both for bench test.

## Validation steps

Run each step and confirm it works before moving to the next.

### 1. ESP32 alive test

Flash the minimal main.cpp from src/. Open serial monitor at 115200 baud.

Expected output: "Alive" every second, with node identity printed at boot.

If this doesn't work: USB driver missing, wrong board selected in platformio.ini, or dead board.

### 2. MLX90640 read test

Wire the camera. Flash a stock SparkFun MLX90640 example that prints pixel values.

Expected output: 768 pixel values (32x24 array) with reasonable room temperature readings around 20-25 degC.

Test with a heat source (hairdryer or hand) - pixels should track the heat.

If this doesn't work: I2C wiring, wrong SDA/SCL pins, library not installed.

### 3. CAN transmit test

Wire the transceiver. Flash a stock ESP32-TWAI-CAN transmit example.

Set PCAN-View to 500 kbit/s. Connect the SN65HVD230 CANH/CANL to the PCAN-USB.

Expected: CAN frames appear in PCAN-View at the configured rate.

If this doesn't work: transceiver wiring, wrong GPIO pins, bus not terminated, PCAN-USB not configured.

### 4. Combined test

Merge the MLX90640 read and CAN transmit into one sketch. Every 100 ms:
- Read 768 pixels from MLX90640
- Compute overall average temperature
- Pack into 8-byte CAN frame with ID 0x320
- Transmit

Expected: 10 Hz CAN frames with plausible temperature values decoded in PCAN-View.

### 5. Band averaging

Add the 3-band average calculation (inner, middle, outer). Send full 8-byte payload matching the DBC.

Test with a targeted heat source aimed at one band - only that band's average should rise.

### 6. DBC integration

Import the DBC into PCAN-View. Confirm decoded values appear with correct scale and units.

## Common issues

- Windows may not recognize the LOLIN32 Lite as a serial device. Install the CH340 or CP210x driver depending on which USB-to-serial chip is on the board.
- I2C pull-up resistors: some MLX90640 breakouts include them, some don't. If I2C reads fail, add 4.7k pull-ups on SDA and SCL.
- CAN bus with no termination or wrong termination will not work. Verify with an oscilloscope if possible.
- ESP32 TWAI shares pins with other peripherals. If GPIO 4 or 5 don't work, check the LOLIN32 Lite pinout for conflicts.
