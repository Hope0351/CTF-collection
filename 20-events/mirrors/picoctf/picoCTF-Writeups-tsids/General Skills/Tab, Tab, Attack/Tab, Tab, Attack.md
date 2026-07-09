# [Tab, Tab, Attack](https://play.picoctf.org/practice/challenge/176)

## Overview

**Points**: 20

**Category**: [General Skills](../)

## Description

Using tabcomplete in the Terminal will add years to your life, esp. when dealing with long rambling directory structures and filenames: [Addadshashanammu.zip](./Addadshashanammu.zip)

## Hints

1. After `unzip`ing, this problem can be solved with 11 button-presses...(mostly Tab)...

## Solution

Unzip the zip file using `unzip Addadshashanammu.zip`, and use the `ls` and `cd` commands to navigate into each folder until you reach the file `fang-of-haynekhtnamet`. (Note: the hint suggests using the Tab key because Tab will autocomplete the `cd` command). Once you find the file, run the command `file fang-of-haynekhtnamet` and you'll see that the file is an executable.

```bash
>>> file fang-of-haynekhtnamet
fang-of-haynekhtnamet: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=5fffe70019957f0a27a70bb886b2cfb9f9b21d6e, not stripped
```

Run the file by typing `./fang-of-haynekhtnamet`, and the flag will appear.

## Flag

`picoCTF{l3v3l_up!_t4k3_4_r35t!_76266e38}`
