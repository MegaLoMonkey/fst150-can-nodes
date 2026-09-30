# FST-150 Tyre Temperature and Steering Angle Data System

A distributed CAN bus data acquisition system for the Ford Fiesta ST150 race car (FST-150), providing per-corner tyre surface temperature analysis and steering angle logging via ESP32 microcontrollers integrated with an AiM MXS 1.2 dash logger.

## Project overview

This project builds a modular sensor network of five ESP32 nodes:
- Four corner nodes with MLX90640 thermal cameras for tyre surface temperature
- One steering column node with AS5600 magnetic encoder for steering angle

Each node broadcasts sensor data over CAN2 to an AiM MXS 1.2 dash logger, which consolidates the data with existing ECU, GPS, and brake pressure channels for both live display and video overlay on a VBOX HD2 video logger.

## Origin and attribution

This project was inspired by [traviscea/DIY-ESP32-Thermal-Tire-Temperature](https://github.com/traviscea/DIY-ESP32-Thermal-Tire-Temperature) by Travis Way, which demonstrated an ESP-NOW based wireless tyre temperature system using MLX90640 thermal cameras and ESP32 microcontrollers.

This fork diverges significantly:
- Primary architecture is wired CAN bus rather than wireless ESP-NOW
- Designed for integration with AiM MXS 1.2 dash logger via CAN2
- Includes a steering angle node using AS5600 magnetic encoder
- Built for a specific car (Ford Fiesta ST150 race car, "FST-150")
- Adds proper power conditioning and automotive-grade enclosure design
- Wireless variant may be built as a parallel experimental branch for comparison

The original project's contributions remain valuable, particularly the 5-zone tread analysis approach and the browser-based calibration interface concept. Where ideas have been adapted, they are credited inline in the relevant source files.

## Architecture

See `docs/architecture.md` for the full topology, bus diagrams, and design decisions.

Summary:
- 4x tyre nodes: ESP32 + MLX90640-D55 broadcasting on CAN2 IDs 0x320-0x323
- 1x steering node: ESP32 + AS5600 broadcasting on CAN2 ID 0x310
- MXS 1.2 receives CAN2 stream, consolidates with OMEX ECU (RS232), GPS, and brake pressures
- MXS 1.2 broadcasts CAN Output on CAN1 at 500 kbit/s to VBOX HD2 for video overlay

## Data model

Per-corner tyre message (8 bytes, 10 Hz):
- Bytes 0-1: Inner band average temp (uint16, 0.1°C resolution)
- Bytes 2-3: Middle band average temp
- Bytes 4-5: Outer band average temp
- Bytes 6-7: Overall average temp

Steering angle message (4 bytes, 100 Hz):
- Bytes 0-1: Angle (int16, 0.1 degree resolution, positive = right)
- Byte 2: Rolling counter
- Byte 3: Status byte

See `dbc/fst150_can2.dbc` for full DBC definitions.

## Hardware

See `docs/wiring.md` for the wiring specifications and `hardware/` for CAD and schematic files.

Bill of materials tracked separately (see project documentation).

## Firmware

Built with PlatformIO. Common libraries shared across node types.

Build environments:
- `env:tyre_node` - MLX90640 + CAN, deployed to FL, FR, RL, RR corners
- `env:steering_node` - AS5600 + CAN, deployed to steering column

Tyre node ID is set at build time via a build flag.

## Project status

Phase 0: Bench prototype validation (current)
Phase 1: Production wired system for all five nodes
Phase 2: Wireless experimental variant (deferred)
Phase 3: Car installation with enclosures and harness

## Related

- Website: [engineeredbydesign.co.uk](https://engineeredbydesign.co.uk)
- Vehicle: Ford Fiesta ST150 race car
- Series: Modified Fords, CSSC, MSVR

## Licence

MIT Licence. See LICENSE file.

## Author

Gareth Knopp / Engineered by Design
