# [speeds and feeds](https://play.picoctf.org/practice/challenge/116)

## Overview

**Points**: 50

**Category**: [Reverse Engineering](../)

## Description

There is something on my shop network running at `nc mercury.picoctf.net 28067`, but I can't tell what it is. Can you?

## Hints

1. What language does a CNC machine use?

## Solution

After googling, we find that a CNC machine uses G-code. We can save the G-code in a [text file](./cnc.txt).

```bash
nc mercury.picoctf.net 28067 > cnc.txt
```

Then, we can copy the G-code and paste it into a [G-code interpreter](https://ncviewer.com/) to get the flag.

## Flag

`picoCTF{num3r1cal_c0ntr0l_84d2d117}`
