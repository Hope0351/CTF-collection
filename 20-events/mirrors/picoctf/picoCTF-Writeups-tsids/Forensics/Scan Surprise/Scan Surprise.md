# [Scan Surprise](https://play.picoctf.org/practice/challenge/444)

## Overview

**Points**: 50

**Category**: [Forensics](../)

## Description

I've gotten bored of handing out flags as text. Wouldn't it be cool if they were an image instead?
You can download the challenge files here:
- [challenge.zip](https://artifacts.picoctf.net/c_atlas/15/challenge.zip)

The same files are accessible via SSH here:
`ssh -p <port> ctf-player@atlas.picoctf.net`
Using the password `1db87a14`. Accept the fingerprint with `yes`, and `ls` once connected to begin. Remember, in a shell, passwords are hidden!

## Hints

1. QR codes are a way of encoding data. While they're most known for storing URLs, they can store other things too.
2. Mobile phones have included native QR code scanners in their cameras since version 8 (Oreo) and iOS 11
3. If you don't have access to a phone, you can also use zbar-tools to convert an image to text

## Solution

SSH into the server. The zip file contains an image named `flag.png`. The image is a QR code. Use a QR code scanner to scan the image and get the flag.

## Flag

`picoCTF{p33k_@_b00_19eccd10}`
