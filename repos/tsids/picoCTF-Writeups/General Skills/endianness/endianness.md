# [endianness](https://play.picoctf.org/practice/challenge/414)

## Overview

**Category**: [General Skills](../)

**Difficulty**: Easy

**Event**: picoCTF 2024

## Description

Know of little and big endian?
[Source](https://artifacts.picoctf.net/c_titan/79/flag.c)

## Hints

1. You might want to check the ASCII table to first find the hexadecimal representation of characters before finding the endianness.
2. Read more about how endianness  [here](https://levelup.gitconnected.com/little-endian-and-big-endian-74ab6441b2a7)

## Solution

Endianness is the order of bytes in a multi-byte data type. In little-endian, the least significant byte is stored first, and in big-endian, the most significant byte is stored first.

First, we need to convert the word to hex. For example, the word `hello` is `68 65 6c 6c 6f` in hex.

To convert the word to big-endian, we need to remove the spaces from the original hex. So, `hello` in big-endian is `68656c6c6f`.

To convert the word to little-endian, we need to reverse the order of the bytes and remove the spaces. So, `hello` in little-endian is `6f 6c 6c 65 68`, which becomes `6f6c6c6568`.

> [!WARNING]
> For little-endian, simply reversing the hex string doesn't work. You need to reverse the order of the bytes.

```python
word = "hello"
hex_word = " ".join([hex(ord(c))[2:] for c in word])
'68 65 6c 6c 6f'
big_endian = hex_word.replace(" ", "")
'68656c6c6f'
little_endian = "".join(reversed(hex_word.split(" ")))
'6f6c6c6568'
```

The solution script is in [solve.py](./solve.py).

## Flag

`picoCTF{3ndi4n_sw4p_su33ess_d58517b6}`
