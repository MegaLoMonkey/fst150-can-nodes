# Common library

Shared code used by both tyre nodes and steering nodes.

## Planned modules

- `can_frames.h` / `can_frames.cpp` - CAN message ID definitions and frame packing helpers
- `heartbeat.h` / `heartbeat.cpp` - rolling counter and status byte management
- `config.h` - compile-time configuration constants

## Design principle

Anything that both node types need lives here. Node-specific code goes in `lib/tyre_node/` or `lib/steering_node/`.
