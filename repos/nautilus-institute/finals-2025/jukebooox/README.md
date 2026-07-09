# Jukebooox - DEF CON 25 CTF Finals Challenge

## Game Description

```
Shall we play a... sooong?

All hardware is fixed, only filters.txt can be changed.
```

## Overview
Jukebooox is an attack-defense CTF challenge for DEF CON 25 CTF Finals. Players interact with a virtual jukebox system where they can select and upload songs. The jukebox emits sound waves that travel to various listening devices in a virtual room.

This was released during the game as three different challenges:

- `jukebooox-echooo`
- `jukebooox-laptooop`
- `jukebooox-prooodigi`

All challenges could only be patched by changing the `filters.txt` file, which allowed the teams to use biquad filters to modify the audio file before it reached the device. 

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

## Testing
To run the unit tests:
```bash
cd src
make test
```

This will compile and run the test suite, which includes tests for the WAV parsing functionality.

## Devices

### Echooo

This is a device that mimics a voice controlled assistant such as Siri, Alexa, etc. The central jukebooox plays a sound file, and this sound file is stored by the echooo and sent to whisper-cli (from whisper.cpp) for text extraction. Then, if the user sends the phrase "hey hacker" the rest of the text is sent to system. 

However, only the admin should have access to this functionality, so before the jukebooox plays the song it passes it to an echooo filter, which passes it to whisper-cli for text extraction and then checks for any "hey" or "hacker", and if those exists refuses to play it. 

#### Vulnerability

The core vulnerability inspiration here is from [Dolphin Attacks](https://arxiv.org/abs/1708.09537): ultrasonic frequencies are demodulated due to the nonlinearity of the microphone _into_ audible frequencies, which is in [echooo.c:94](./src/echooo.c#L94). 

The microphone processing in `echooo` was designed to mimic a real microphone, and the design of the challenge also led to several interesting bypasses: adding either low frequency or high frequency audio to the "hey hacker" wake word [echooo.c:98](./src/echooo.c#98-101). 

My exploit: [x.py:388](./src/tests/x.py#L388).

### Laptooop

This is a device that mimics a laptop recording audio sounds. We also simulate a spinning hard disk drive (HDD) with an actuator arm and shock sensors, each with different resonance frequencies. 

#### Vulnerability 

The inspiration of this challenge is [CVE-2022-38392](https://nvd.nist.gov/vuln/detail/CVE-2022-38392), and further studied in [Blue Note, an Oakland 2018 paper](https://ieeexplore.ieee.org/document/8418653), which studied resonance's role in triggering a HDD failure. 

- When clearing data the hard drive doesn't reset the number of bytes written, which allows information leak of heap and binary [laptooop.c:580](./src/laptooop.c#L580).
- When there's too many write errors of the HDD, the laptooop frees the hdd causing a UAF [laptooop.c:380](./src/laptooop.c#380).

#### Post-game Notes

Before launching I was worried about patches that just reduced the Db of the audio file so much it could never trigger, so I significantly increased [the amp wattage](./src/main.c#L279) of speakers so this couldn't happen. Unfortunately I didn't test enough to realize that this made the resonance very easy to trigger. 

### Prooodigi

This is a device that is essentially a shellcoding challenge: create shellcode that is in a specific musical key and the delta between the audio samples is below a threshold. 

