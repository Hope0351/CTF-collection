# [Nice netcat...](https://play.picoctf.org/practice/challenge/156)

## Overview

**Points**: 15

**Category**: [General Skills](../)

## Description

There is a nice program that you can talk to by using this command in a shell: `$ nc mercury.picoctf.net 35652`, but it doesn't speak English...

## Hints

1. You can practice using netcat with this picoGym problem: [what's a netcat?](https://play.picoctf.org/practice/challenge/34)
2. You can practice reading and writing ASCII with this picoGym problem: [Let's Warm Up](https://play.picoctf.org/practice/challenge/22)

## Solution

After running the command, the numbers seem to be the unicode values of some ascii letters. Copy and paste the numbers into [CyberChef](https://gchq.github.io/CyberChef/), then use the `From Decimal` tool to convert from the unicode values to the corresponding letters.

## Flag

`picoCTF{g00d_k1tty!_n1c3_k1tty!_9b3b7392}`