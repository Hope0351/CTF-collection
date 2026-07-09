# [Mod 26](https://play.picoctf.org/practice/challenge/144)

## Overview

**Points**: 10

**Category**: [Cryptography](../)

## Description

Cryptography can be easy, do you know what ROT13 is? `cvpbPGS{arkg_gvzr_V'yy_gel_2_ebhaqf_bs_ebg13_Ncualgvd}`

## Hints

1. This can be solved online if you don't want to do it by hand!

## Solution

The given flag is encrypted in a caesar cipher, where the letters are shifted (or rotated) 13 places, as hinted at in the description. Use [this](https://cryptii.com/pipes/caesar-cipher) site to decrypt the flag.

## Flag

`picoCTF{next_time_I'll_try_2_rounds_of_rot13_Aphnytiq}`