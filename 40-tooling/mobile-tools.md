# Mobile Tooling

> Part of **CTF-collection** — see [`40-tooling/README.md`](README.md) for the full tool index.

## Overview

Frida dominates dynamic instrumentation. jadx and apktool handle APK reverse engineering. For iOS, class-dump, Hopper, and Ghidra are standard. objection wraps Frida with higher-level helpers.

## Tools

| # | Tool | Language | Description |
|---:|---|---|---|
| 1 | [Frida](https://frida.re/) | JavaScript | Dynamic instrumentation framework. Dominates mobile RE. Hooks Java methods, native functions, syscalls. |
| 2 | [jadx](https://github.com/skylot/jadx) | Java | APK decompiler. GUI (jadx-gui) and CLI. Best free option for reading Android app source. |
| 3 | [apktool](https://apktool.org/) | Java | APK decompiler/recompiler. Smali editing; resource extraction. |
| 4 | [objection](https://github.com/sensepost/objection) | Python | Frida-based runtime exploration toolkit. Higher-level than raw Frida. |
| 5 | [Android Studio](https://developer.android.com/studio) | Java | Official Android IDE. Useful for emulator and APK profiling. |
| 6 | [Hopper](https://www.hopperapp.com/) | C++ | macOS-native disassembler. Commercial. Good for iOS binary analysis. |
| 7 | [Ghidra](https://ghidra-sre.org/) | Java | Useful for analyzing native libraries (.so files) extracted from APKs. |
| 8 | [dex2jar](https://github.com/pxb1988/dex2jar) | Java | Converts DEX to JAR for analysis in JD-GUI or similar. |
| 9 | [Magisk](https://github.com/topjohnwu/Magisk) | C++ | Android rooting solution. Required for many Frida use-cases on physical devices. |


## Quick Installation

```bash
# Most tools are pip-installable
pip install pwntools angr ropper pyelftools

# Or apt-installable on Debian/Ubuntu
sudo apt install gdb gdb-gef ghidra wireshark tshark binwalk foremost exiftool steghide

# Foundry (blockchain)
curl -L https://foundry.paradigm.xyz | bash
foundryup

# Frida (mobile)
pip install frida-tools
```

## See Also

- [`00-start-here/tools-cheatsheet.md`](../00-start-here/tools-cheatsheet.md) — condensed cheat sheet across all categories
- [`40-tooling/README.md`](README.md) — full tool index
