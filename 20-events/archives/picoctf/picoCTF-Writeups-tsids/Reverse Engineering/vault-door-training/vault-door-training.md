# [vault-door-training](https://play.picoctf.org/practice/challenge/7)

## Overview

**Points**: 50

**Category**: [Reverse Engineering](../)

## Description

Your mission is to enter Dr. Evil's laboratory and retrieve the blueprints for his Doomsday Project. The laboratory is protected by a series of locked vault doors. Each door is controlled by a computer and requires a password to open. Unfortunately, our undercover agents have not been able to obtain the secret passwords for the vault doors, but one of our junior agents obtained the source code for each vault's computer! You will need to read the source code for each level to figure out what the password is for that vault door. As a warmup, we have created a replica vault in our training facility. The source code for the training vault is here: [VaultDoorTraining.java](./VaultDoorTraining.java)

## Hints

1. The password is revealed in the program's source code.

## Solution

Open the java file, and the flag will be in the `checkPassword()` function at the bottom.

## Flag

`picoCTF{w4rm1ng_Up_w1tH_jAv4_eec0716b713}`