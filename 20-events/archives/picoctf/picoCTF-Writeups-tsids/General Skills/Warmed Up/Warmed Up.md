# [Warmed Up](https://play.picoctf.org/practice/challenge/58)

## Overview

**Points**: 50

**Category**: [General Skills](../)

## Description

What is 0x3D (base 16) in decimal (base 10)?

## Hints

1. Submit your answer in our flag format. For example, if your answer was '22', you would submit 'picoCTF{22}' as the flag.

## Solution

Convert 0x3D to decimal.

```bash
> printf "%d\n" 0x3D
61
```

## Flag

`picoCTF{61}`