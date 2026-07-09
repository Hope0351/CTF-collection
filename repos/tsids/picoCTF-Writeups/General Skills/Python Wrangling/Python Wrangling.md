# [Python Wrangling](https://play.picoctf.org/practice/challenge/166)

## Overview

**Points**: 10

**Category**: [General Skills](../)

## Description

Python scripts are invoked kind of like programs in the Terminal... Can you run [this Python script](./ende.py) using [this password](./pw.txt) to get [the flag](./flag.txt.en)?

## Hints

1. Get the Python script accessible in your shell by entering the following command in the Terminal prompt: `$ wget https://mercury.picoctf.net/static/b351a89e0bc6745b00716849105f87c6/ende.py`
2. `$ man python`

## Solution

Run the python script in the terminal using `python3 ende.py` (or `py ende.py` for windows). The file seems to be able to encrypt and decrypt other files. Run the python script with the `-d` flag to decrypt: `python3 ende.py -d flag.txt.en` and input the password when asked, and the flag should appear.

## Flag

`picoCTF{4p0110_1n_7h3_h0us3_67c6cc96}`