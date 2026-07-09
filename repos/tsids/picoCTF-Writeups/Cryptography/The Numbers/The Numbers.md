# [The Numbers](https://play.picoctf.org/practice/challenge/68)

## Overview

**Points**: 50

**Category**: [Cryptography](../)

## Description

The [numbers](./the\_numbers.png)... what do they mean?

## Hints

1. The flag is in the format PICOCTF{}

## Solution

Since the flag is in the format picoCTF{}, we can see that there are 7 numbers before the first `{`. Therefore, each number must correspond to the position of the letter in the alphabet.

Use a [letter to number converter](https://www.boxentriq.com/code-breaking/numbers-to-letters) to get the flag.

## Flag

`picoCTF{thenumbersmason}`