# [ARMssembly 0](https://play.picoctf.org/practice/challenge/160)

## Overview

**Points**: 40

**Category**: [Reverse Engineering](../)

## Description

What integer does this program print with arguments `4004594377` and `4110761777`? File: [chall.S](./chall.S) Flag format: picoCTF{XXXXXXXX} -> (hex, lowercase, no 0x, and 32 bits. ex. 5614267 would be picoCTF{0055aabb})

## Hints

1. Simple compare

## Solution

We can solve the challenge by trying to understand what the assembly file does, or compiling it and running it.

`chall.S` is written in ARM assembly, which won't run directly on x86 machines. To run it on our machine, we can follow this guide: https://azeria-labs.com/arm-on-x86-qemu-user/

First install the packages needed to run ARM assembly on x86:

```bash
sudo apt install binutils-aarch64-linux-gnu gcc-aarch64-linux-gnu qemu-user
```

Then compile the assembly file:

```bash
aarch64-linux-gnu-gcc -static -o chall chall.S
```

Finally, run the file with the arguments given in the challenge description:

```bash
> ./chall 4004594377 4110761777
Result: 4110761777
```

Finally, we can take the output and convert it to hex to get the flag.
```bash
> printf "%x\n" 4110761777
f5053f31
```

## Flag

`picoCTF{f5053f31}`