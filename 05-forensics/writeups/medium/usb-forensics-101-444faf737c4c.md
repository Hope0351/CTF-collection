# :mag: USB Forensics 101. Ever wondered what the digital…

---

Welcome to my USB Forensics 101 guide.

Inspired by a Pluralsight course I completed on USB Forensics fundamentals, I decided to have a crack at explaining the basics myself. Being quite goal-oriented I knew that deciding on a blogpost will help me see through the learning and help with organising the new knowledge in my head — you know what they say, one doesn’t fully understand a topic until they are able to explain it to a five year old. While this might be a bit heavy for a five year old (although it probably would prove an efficient bedtime lullaby), it should convey what I learnt from only knowing of USB existence to understanding how it works under the hood.

## Basics

First of all, let’s find out what the host machine sees about its USB without any USB devices being plugged in. For this we will need the `lsusb` utility. Let’s try it out – make sure there’s nothing plugged into your USB ports.

`lsusb` comes preinstalled on Linux. If you’re using macOS like myself, you need to install it first with `brew install lsusb`. Run the `lsusb -t` command to have the output presented as a tree. Other useful syntax can be `lsusb | sort -k 2` which sorts the output by the bus number, or `lsusb -v`, the verbose flag outputs more detailed information about the listed devices.

```
Kingas-MacBook-Pro:~ kingakieczkowska$ lsusb -t
...
0.Dev 000: iBridge Bus,
/: Bus 000.Dev 001: USB 3.1 Bus,
/: Bus 128.Dev 000: Apple T2 Controller,
/: Bus 128.Dev 000: FaceTime HD Camera (Built-in),
/: Bus 128.Dev…
```

---
