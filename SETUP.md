# Development Setup

## First-time setup

### 1. Install tools

- [VS Code](https://code.visualstudio.com/)
- PlatformIO IDE extension (installed from VS Code Extensions panel)
- [GitHub Desktop](https://desktop.github.com/) - includes git
- [PCAN-View or PCAN-Explorer](https://www.peak-system.com/PCAN-View.242.0.html) - CAN bus monitoring

### 2. LOLIN32 Lite USB driver

The LOLIN32 Lite uses either a CH340 or CP210x USB-to-serial chip. Check the small chip next to the USB connector.

- CH340: install driver from [wch.cn](http://www.wch.cn/downloads/CH341SER_EXE.html)
- CP210x: install from [Silicon Labs](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

### 3. Clone this repository

Using GitHub Desktop:
1. File > Clone repository
2. URL tab: paste `https://github.com/MegaLoMonkey/ESP32-EBD-FST150-tyre-temp.git`
3. Local path: choose somewhere OUTSIDE OneDrive, for example `C:\Projects\EbD\`
4. Clone

Do not put this repo inside a OneDrive, Dropbox, or Google Drive synced folder. Git and cloud sync services conflict.

### 4. Open in VS Code

- Open VS Code
- File > Open Folder, select the cloned repository folder
- Wait for PlatformIO to initialise (first time takes a few minutes as it downloads dependencies)

### 5. First build

- Open src/main.cpp
- In the PlatformIO toolbar at the bottom, select environment `env:tyre_node_FL`
- Click Build (checkmark icon)
- If build succeeds, plug in the LOLIN32 Lite
- Click Upload (right arrow icon)
- Open Serial Monitor (plug icon) - should see "Alive" every second

## Working on this project

### Making changes

1. Create a feature branch in GitHub Desktop: Branch > New Branch
2. Make code changes in VS Code
3. Save files
4. GitHub Desktop shows changed files - review the diff
5. Write a commit message and click Commit
6. Push to origin (top right button in GitHub Desktop)
7. Create pull request on GitHub if merging to main

### Building for a specific corner

Each corner has its own build environment:
- `env:tyre_node_FL` - front left
- `env:tyre_node_FR` - front right
- `env:tyre_node_RL` - rear left
- `env:tyre_node_RR` - rear right
- `env:steering_node` - steering column

Select the environment in the PlatformIO toolbar at the bottom of VS Code before building.

### CAN debugging

Use PCAN-View at 500 kbit/s to monitor the bus. Import dbc/fst150_can2.dbc to see decoded signal names and values instead of raw hex.
