# 🚀 Start Here — My CTF Collection

Welcome to my personal Capture The Flag (CTF) writeup collection. This is where I document every challenge I solve — the intended path, my actual solve (including the dead ends), and the takeaways I want to remember for next time.

## What's in this directory

| File | Purpose |
|---|---|
| [`learning-path.md`](learning-path.md) | The learning path I'm working through, from foundations up to elite-tier competitions. |
| [`tools-cheatsheet.md`](tools-cheatsheet.md) | My personal cheat sheet of the tools and one-liners I actually use. |

## How this collection is organized

My writeups live in the category folders at the top of the repo, one Markdown file per challenge. Each category folder has its own README explaining the sub-topics I'm tracking.

| Folder | Category |
|---|---|
| [`01-pwn/`](../01-pwn/) | Binary exploitation — stack, heap, kernel, format strings, ROP |
| [`02-web/`](../02-web/) | Web exploitation — SQLi, XSS, SSRF, SSTI, deserialization, prototype pollution |
| [`03-crypto/`](../03-crypto/) | Cryptography — RSA, ECC, lattices, block cipher modes, custom schemes |
| [`04-reverse-engineering/`](../04-reverse-engineering/) | Static/dynamic analysis of native binaries, custom VMs, obfuscation |
| [`05-forensics/`](../05-forensics/) | Disk, memory, network forensics, steganography |
| [`06-osint/`](../06-osint/) | Open-source intelligence — geolocation, social media, breach data |
| [`07-misc/`](../07-misc/) | Programming, game exploitation, esoteric challenges |
| [`08-blockchain-web3/`](../08-blockchain-web3/) | Smart-contract exploitation — reentrancy, oracles, flash loans |
| [`09-mobile/`](../09-mobile/) | Android/iOS reverse engineering and Frida instrumentation |
| [`10-hardware-iot/`](../10-hardware-iot/) | Firmware extraction, JTAG/SWD, side-channel, SDR |
| [`11-ics-scada/`](../11-ics-scada/) | Industrial control systems — Modbus, PLCs, HMI |
| [`12-cloud/`](../12-cloud/) | AWS/Azure/GCP misconfigurations, K8s, container escapes |
| [`13-network-pcap/`](../13-network-pcap/) | Packet capture analysis and protocol reconstruction |

The [`20-events/`](../20-events/) folder holds my writeups grouped by CTF event (picoCTF, HackTheBox, DEF CON, etc.) instead of by category. Use it when I want to review everything I solved at a specific competition.

## My writeup format

Every writeup I publish here follows the same shape:

1. **Challenge metadata** — event, year, category, points, solve count.
2. **The challenge** — what we were given and what the goal was.
3. **Reconnaissance** — what I looked at first and why.
4. **Solve path** — the actual steps, including wrong turns. Wrong turns are the most valuable part because they show what didn't work and why.
5. **Flag** — the flag string, in a code block.
6. **Takeaways** — two or three bullet points I want to remember next time I see a similar challenge.

If a writeup is missing any of these sections, it's a stub I haven't finished yet.

## Why I keep this collection

Writing up a solve forces me to explain the exploit in plain language, which is the fastest way to find the gaps in my own understanding. A challenge I solve but don't write up is a challenge I'll have to re-solve from scratch six months later. This repo is my externalized memory — if I'm stuck on something, the first thing I do is `git grep` my own writeups to see if I've solved something similar before.

The secondary purpose is portfolio: a well-maintained writeup archive is the single most credible credential for an aspiring offensive-security professional. Many CTF players have been hired on the strength of their writeup repositories alone, and I want this repo to be that kind of archive for me.

## Where to start reading

If you're me, six months from now, looking for a specific technique: use `git grep` from the repo root. I tag every writeup with the technique name in the front matter, so `git grep "format string"` or `git grep "tcache poisoning"` will pull up everything I've written on that topic.

If you're someone else browsing this: start with [`learning-path.md`](learning-path.md) to see where I am in the journey, then jump to whichever category folder interests you. The [`tools-cheatsheet.md`](tools-cheatsheet.md) is a condensed reference of the commands and one-liners I use most often.
