# [interencdec](https://play.picoctf.org/practice/challenge/418)

## Overview

**Points**: 50

**Category**: [Cryptography](../)

## Description

Can you get the real meaning from this file.
Download the file [here](https://artifacts.picoctf.net/c_titan/3/enc_flag).


## Hints

1. Engaging in various decoding processes is of utmost importance

## Solution

The text looks like a base64 encoded string. Decode it using the following command:

```bash
$ cat enc_flag | base64 -d
b'd3BqdkpBTXtqaGx6aHlfazNqeTl3YTNrX2kyMDRoa2o2fQ=='
```

The output looks like another base64 encoded string. Decode it again.

```bash
$ echo "d3BqdkpBTXtqaGx6aHlfazNqeTl3YTNrX2kyMDRoa2o2fQ==" | base64 -d
wpjvJAM{jhlzhy_k3jy9wa3k_i204hkj6}
```

We almost have the flag, but it looks like the text is encrypted using a Caesar cipher. Decrypt it using the following [tool](https://www.dcode.fr/caesar-cipher).

Using ROT-19, we get the flag.

## Flag

`picoCTF{caesar_d3cr9pt3d_b204adc6}`
