# [Lets Warm Up](https://play.picoctf.org/practice/challenge/22)

## Overview

**Points**: 50

**Category**: [General Skills](../)

## Description

If I told you a word started with 0x70 in hexadecimal, what would it start with in ASCII? 

## Hints

1. Submit your answer in our flag format. For example, if your answer was 'hello', you would submit 'picoCTF{hello}' as the flag.

## Solution

Open [CyberChef](https://gchq.github.io/CyberChef/#recipe=From_Hex('Auto')&input=MHg3MA) and paste 0x70 into the input. Since we want to convert from hex to ASCII, use the `From Hex` tool. You'll find that 0x70 is 'p' in ASCII. Wrap picoCTF{} around the answer and submit the flag.

## Flag

`picoCTF{p}`