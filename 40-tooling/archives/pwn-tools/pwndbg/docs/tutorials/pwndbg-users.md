# Pwndbg in the wild

Here is a non-exhaustive list of Pwndbg mentions found in the wild. Feel free to open a PR to add more if you find them!

## Talks
+ [EuroPython 2025 - Pwndbg: Low level debugging and exploit development with Python](https://ep2025.europython.eu/session/pwndbg-low-level-debugging-and-exploit-development-with-python) ([slides](https://docs.google.com/presentation/d/1m9yYOeHxkKznseTakYeKixOUcCEjk7e-goirNE93ISs/), [video](https://www.youtube.com/watch?v=hRvjre7AH-o&t=7100s))
+ [OffensiveCon24 - How to Fuzz Your Way to Android Universal Root: Attacking Android Binder - by Eugene Rodionov, Zi Fan Tan and Gulshan Singh](https://www.youtube.com/watch?v=U-xSM159YLI&t=1859s)

## Blog posts
+ [Oops Safari, I think You Spilled Something! @ Exodus Intelligence](https://blog.exodusintel.com/2025/08/04/oops-safari-i-think-you-spilled-something/)
+ [“Unstripping” binaries: Restoring debugging information in GDB with Pwndbg by Jason An @ Trail of Bits](https://blog.trailofbits.com/2024/09/06/unstripping-binaries-restoring-debugging-information-in-gdb-with-pwndbg/)
+ [A Winter’s Tale: Improving messages and types in GDB’s Python API by Matheus Branco Borella @ Trail of Bits](https://blog.trailofbits.com/2023/04/18/a-winters-tale-improving-types-and-messages-in-gdbs-python-api/)
+ [Patch-gapping Google Chrome @ Exodus Intelligence](https://blog.exodusintel.com/2019/09/09/patch-gapping-chrome/)
+ [Inspecting rdtsc with pwndbg by John Shaughnessy](https://www.johnshaughnessy.com/blog/posts/rdtsc_and_pwndbg)

## Videos
+ [Intro to pwndbg - CTF Cookbook by SloppyJoePirates CTF Writeups](https://www.youtube.com/watch?v=5judobmDBKI)
+ [Intro to Binary Exploitation (Pwn) by CryptoCat](https://youtu.be/wa3sMSdLyHw?list=PLHUKi1UlEgOIc07Rfk2Jgb5fZbxDPec94&t=730)
+ [Bug A Day #8 - pwndbg #2 by Bug-A-Day](https://www.youtube.com/watch?v=mmkewHlDv9I)

## Scripts
+ CVE-2022-24834 exploit by ptr-yudai

## Magazine articles
+ ["Programista" polish programming magazine - Low level debugging with Pwndbg (in polish)](https://programistamag.pl/programista-42023-109-wrzesienpazdziernik-2023-debugowanie-niskopoziomowe-z-pwndbg/)

## Software
+ ghidra2dwarf shows Pwndbg in its README.md example
+ decomp2dbg implements a Pwndbg client (though we implement our own integration now :) )
+ An (outdated :( ) pwndbg plugin for scudo exploitation
+ gdb-peda-pwndbg-gef - A script that installs those tools
+ splitmind - Better organization of Pwndbg contexts via tmux splits
+ hyperpwn - Similar as splitmind, but for the hypr terminal
+ epictreasure - A [vagrant](https://developer.hashicorp.com/vagrant) box that includes Pwndbg
+ pwn-init-env - A pwn environment that includes Pwndbg
+ gdbw - A scriptable CLI debugger for windows inspired by Pwndbg
+ pwndbg-gui - A Pwndbg GUI wrapper
+ pwnmux - A Pwndbg configuration to use tmux panes
+ GEP - A GDB plugin that allows fuzzy searching the GDB history, compatible with Pwndbg
+ 217gdb - Modifies the Pwndbg UI for better usage
+ And [many more](https://github.com/search?q=pwndbg&type=repositories)
