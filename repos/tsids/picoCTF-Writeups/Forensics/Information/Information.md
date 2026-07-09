# [Information](https://play.picoctf.org/practice/challenge/186)

## Overview

**Points**: 10

**Category**: [Forensics](../)

## Description
Files can always be changed in a secret way. Can you find the flag? [cat.jpg](./cat.jpg)

## Hints

1. Look at the details of the file
2. Make sure to submit the flag as picoCTF{XXXXX}

## Solution

First try to see if there's anything in the exif data of the file. This can be done through [this](https://29a.ch/photo-forensics/#strings) site or by running `exiftool cat.jpg` in the terminal.

The license looks unusual, and upon further analysis, it seems that `cGljb0NURnt0aGVfbTN0YWRhdGFfMXNfbW9kaWZpZWR9` is a base64 code. Decode it using [this](https://www.base64decode.org/) site or run `echo cGljb0NURnt0aGVfbTN0YWRhdGFfMXNfbW9kaWZpZWR9 | base64 --decode` in the terminal.

## Flag

`picoCTF{the_m3tadata_1s_modified}`
