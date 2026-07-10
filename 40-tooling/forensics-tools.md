# Forensics Tooling

> Part of **CTF-collection** — see [`40-tooling/README.md`](README.md) for the full tool index.

## Overview

Volatility dominates memory forensics. Autopsy and The Sleuth Kit handle disk forensics. Wireshark and tshark handle packet captures. Aperi'Solve is the dominant online stego solver; binwalk extracts embedded files; foremost carves deleted files.

## Tools

| # | Tool | Language | Description |
|---:|---|---|---|
| 1 | [Volatility](https://www.volatilityfoundation.org/) | Python | The dominant memory forensics framework. Supports Windows, Linux, macOS memory dumps. Vol3 is the current major version. |
| 2 | [Autopsy](https://www.autopsy.com/) | Java | GUI frontend for The Sleuth Kit. Disk image forensics. |
| 3 | [The Sleuth Kit](https://www.sleuthkit.org/) | C++ | CLI disk forensics tools. Underlies Autopsy. |
| 4 | [Wireshark](https://www.wireshark.org/) | C++ | The dominant packet-capture analysis tool. Display filters are the key skill. |
| 5 | [tshark](https://www.wireshark.org/docs/man-pages/tshark.html) | C++ | CLI version of Wireshark. Scriptable; useful for batch processing. |
| 6 | [binwalk](../40-tooling/archives/forensics-tools/binwalk) | Python | Firmware analysis. Identifies and extracts embedded files. |
| 7 | [foremost](http://foremost.sourceforge.net/) | C | File carver. Recovers deleted files from disk images. |
| 8 | [Aperi'Solve](https://www.aperisolve.com/) | Web | Online stego solver. Runs multiple tools (zsteg, stegsolve, steghide, etc.) automatically. |
| 9 | [zsteg](../40-tooling/archives/forensics-tools/zsteg) | Ruby | PNG/BMP stego detector. Detects LSB steganography. |
| 10 | [stegsolve](http://www.caesum.com/handbook/Stegsolve.jar) | Java | Visual stego analysis. Bit-plane viewing, alpha-channel analysis. |
| 11 | [exiftool](https://exiftool.org/) | Perl | Metadata reader/writer. Essential for image forensics. |
| 12 | [steghide](https://steghide.sourceforge.net/) | C++ | Embeds/extracts data in JPEG, BMP, WAV, AU. Password-protected. |

## Quick Installation

```bash
# Volatility (memory forensics)
pip install volatility3

# binwalk (firmware/file analysis)
pip install binwalk

# foremost (file carving)
sudo apt install foremost

# exiftool (metadata extraction)
sudo apt install libimage-exiftool-perl

# zsteg (PNG steganography)
gem install zsteg

# steghide (JPEG steganography)
sudo apt install steghide

# Wireshark/tshark (network analysis)
sudo apt install wireshark tshark
```

## See Also

- [`00-start-here/tools-cheatsheet.md`](../00-start-here/tools-cheatsheet.md) — condensed cheat sheet across all categories
- [`40-tooling/README.md`](README.md) — full tool index
