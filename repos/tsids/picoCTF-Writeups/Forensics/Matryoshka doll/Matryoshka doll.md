# [Matryoshka doll](https://play.picoctf.org/practice/challenge/129)

## Overview

**Points**: 30

**Category**: [Forensics](../)

## Description

Matryoshka dolls are a set of wooden dolls of decreasing size placed one inside another. What's the final one? Image: [this](./dolls.jpg)

## Hints

1. Wait, you can hide files inside files? But how do you find them?
2. Make sure to submit the flag as picoCTF{XXXXX}

## Solution

Use the [binwalk tool](https://github.com/ReFirmLabs/binwalk) to display embedded data in a given file. You can use it by running `binwalk <file>`.

```sh
>>> binwalk dolls.jpg

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             PNG image, 594 x 1104, 8-bit/color RGBA, non-interlaced
3226          0xC9A           TIFF image data, big-endian, offset of first image directory: 8
272492        0x4286C         Zip archive data, at least v2.0 to extract, compressed size: 378955, uncompressed size: 383936, name: base_images/2_c.jpg
651613        0x9F15D         End of Zip archive, footer length: 22

```

Notice that there is an image file stored within the file. Extract it by running `binwalk -e dolls.jpg`. Then, `cd` into the new directory and repeat the process on the next image file. Do this until you see a file named `flag.txt`, and the flag will be in the file.

## Flag

`picoCTF{ac0072c423ee13bfc0b166af72e25b61}`
