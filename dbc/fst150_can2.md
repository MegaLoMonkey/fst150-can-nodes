# FST-150 CAN2 Bus DBC Documentation

Human-readable description of the DBC file for the FST-150 CAN2 bus.

## Bus configuration

- Bit rate: 500 kbit/s
- Byte order: Motorola / big-endian throughout
- Format: standard 11-bit identifiers

## Message summary

| CAN ID | Name | Length | Rate | Sender | Description |
|--------|------|--------|------|--------|-------------|
| 0x310 | STEERING_ANGLE | 4 | 100 Hz | steering_node | Steering column angle |
| 0x320 | TYRE_TEMP_FL | 8 | 10 Hz | tyre_node_FL | Front left tyre temperature summary |
| 0x321 | TYRE_TEMP_FR | 8 | 10 Hz | tyre_node_FR | Front right tyre temperature summary |
| 0x322 | TYRE_TEMP_RL | 8 | 10 Hz | tyre_node_RL | Rear left tyre temperature summary |
| 0x323 | TYRE_TEMP_RR | 8 | 10 Hz | tyre_node_RR | Rear right tyre temperature summary |

## STEERING_ANGLE (0x310)

100 Hz update rate. Transmitted by steering_node.

| Signal | Start bit | Length | Type | Factor | Offset | Unit | Range |
|--------|-----------|--------|------|--------|--------|------|-------|
| angle | 0 | 16 | int16 | 0.1 | 0 | degrees | -450 to +450 |
| counter | 16 | 8 | uint8 | 1 | 0 | count | 0 to 255 |
| status | 24 | 8 | uint8 | 1 | 0 | bitfield | see below |

Positive angle indicates right turn. Rolling counter increments on every transmission to detect stale data at the receiver.

Status byte bits:
- 0: sensor_ok
- 1: calibration_valid
- 2: magnet_detected
- 3-7: reserved (must be 0)

## TYRE_TEMP_xx (0x320-0x323)

10 Hz update rate. One message per corner.

| Signal | Start bit | Length | Type | Factor | Offset | Unit | Range |
|--------|-----------|--------|------|--------|--------|------|-------|
| inner_avg | 0 | 16 | uint16 | 0.1 | 0 | degC | -40 to +300 |
| middle_avg | 16 | 16 | uint16 | 0.1 | 0 | degC | -40 to +300 |
| outer_avg | 32 | 16 | uint16 | 0.1 | 0 | degC | -40 to +300 |
| overall_avg | 48 | 16 | uint16 | 0.1 | 0 | degC | -40 to +300 |

Band definitions:
- Inner: 4 columns of pixels closest to inside edge of tyre (cabin side)
- Outer: 4 columns closest to outside edge (kerb side)
- Middle: remaining 24 columns in the centre of the tread
- Overall: average across all pixels identified as tyre surface

Right-side corners (0x321 FR, 0x323 RR) do NOT need software mirroring at the sensor node. The DBC signal names remain relative to the tyre (inner is always cabin-side), so the receiver applies interpretation consistently.

## Future messages (reserved)

- 0x340-0x343: Full thermal map per corner, multi-frame at 1 Hz
- 0x300-0x30F: Chassis sensors (yaw rate, acceleration, etc)
- 0x330-0x33F: Expansion

## Change log

- 2026-09-30: Initial version, draft
