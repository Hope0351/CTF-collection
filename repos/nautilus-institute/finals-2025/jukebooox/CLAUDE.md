# Jukebooox - DEF CON 25 CTF Finals Challenge

## Overview
Jukebooox is an attack-defense CTF challenge for DEF CON 25 CTF Finals. Players interact with a virtual jukebox system where they can select and upload songs. The jukebox emits sound waves that travel to various listening devices in a virtual room.

## Theme
- Interactive jukebox system (jukebooox - with "ooo" as homage to Order of the Overflow)
- Users can select songs from a catalog or upload custom songs
- Sound waves propagate through the room to listening devices
- Audio simulation includes volume decreasing with distance

## Technical Requirements
- Language: C2X
- Build system: Makefile (builds to src/build/)
- I/O: All via stdin/stdout
- Heavy use of structs for data structures

## Security Model
**IMPORTANT**: Vulnerabilities should ONLY exist in the listening devices (echooo, microphone), NOT in the main jukebox or audio engine.

### Safe Components
- main.c - User interface and jukebox control
- audio.c/h - Audio emulation engine

### Vulnerable Components (for CTF exploitation)
- echooo.c/h - First listening device (must contain vulnerability)
- microphone.c/h - Second listening device (must contain vulnerability)  
- laptooop.c/h - Third listening device simulating laptop with HDD (Blue Note attack target)

## Architecture

### Components
1. **Main Program (main.c)**
   - User interface for jukebox interaction
   - Song selection and upload functionality
   - Device management

2. **Audio Engine (audio.c/h)**
   - Sound wave propagation simulation
   - Distance-based volume calculations
   - Audio routing to devices

3. **Listening Devices**
   - echooo - First vulnerable device
   - microphone - Second vulnerable device
   - laptooop - Third vulnerable device (laptop with spinning HDD simulation)

### Key Data Structures
- Song information (title, duration, audio data)
- Audio wave packets
- Device states and positions
- Room layout for distance calculations
- HDD simulation (actuator arm, shock sensors, platter mechanics)

## Blue Note Attack Simulation (laptooop device)
The laptooop device simulates a laptop with a spinning hard disk drive vulnerable to the "Blue Note" attack. This attack demonstrates how intentional acoustic interference can damage HDD availability and integrity by triggering resonance in:

1. **Actuator Arm**: Controls read/write head positioning. Resonant frequencies can cause positioning errors and data corruption.
2. **Shock Sensors**: Designed to protect against physical shock. Acoustic resonance can trigger false positives, causing unnecessary head parking and performance degradation.

The simulation includes:
- Multi-platter HDD mechanics with configurable RPM
- Actuator arm with resonance frequency response
- Shock sensor with acoustic sensitivity thresholds
- Realistic failure modes and error responses

## Build Instructions
```bash
cd src
make            # Build debug version
make release    # Build release version
make clean      # Clean build artifacts
```

## Running
```bash
./build/jukebooox
```

## Development Notes
- Ensure all non-device code is secure (no vulnerabilities)
- Make structs interesting for reverse engineering
- Consider implementing realistic audio physics (volume decay, etc.)
- All output must be to stdout, all input from stdin
