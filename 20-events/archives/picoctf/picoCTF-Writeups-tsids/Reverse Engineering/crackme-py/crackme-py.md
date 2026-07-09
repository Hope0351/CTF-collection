# [crackme-py](https://play.picoctf.org/practice/challenge/175)

## Overview

**Points**: 30

**Category**: [Reverse Engineering](../)

## Description

[crackme.py](./crackme.py)

## Hints

None

## Solution

It looks like the flag is kept in the `bezos_cc_secret` variable. There is also a function that can encrypt and decrypt the flag, but its never called.

Add `decode_secret(bezos_cc_secret)` to the bottom of the python file to call the function and pass in the encrypted flag as the argument. Run the file and the decoded flag will show up.

## Flag

`picoCTF{1|\/|_4_p34|\|ut_8c551048}`
