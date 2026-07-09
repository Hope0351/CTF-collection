# [Easy Peasy](https://play.picoctf.org/practice/challenge/125)

## Overview

**Points**: 40

**Category**: [Cryptography](../)

## Description

A one-time pad is unbreakable, but can you manage to recover the flag? (Wrap with picoCTF{}) `nc mercury.picoctf.net 36449` [otp.py](./otp.py)

## Hints

1. Maybe there's a way to make this a 2x pad.

## Solution

After connecting to the server, we get access to the encrypted flag. We can also send text to be encrypted. The encryption works by taking the flag and XORing it to a key. Normally, the encryption would be unbreakable if it was a one-time pad, but the `encrypt()` method loops the pad around after 50000 characters. We can use this to get back to the same position, and attempt to decrypt the key.

```py
if stop >= KEY_LEN:
    stop = stop % KEY_LEN # pad loops once limit is reached
    key = kf[start:] + kf[:stop]
else:
    key = kf[start:stop]
key_location = stop
```

First of all, we need to figure out the length of the key, so we know how far to loop around. Notice how the output of the encryption is in hex. This is because of the `x` identifier, which converts to hex. See the [documentation](https://docs.python.org/3.4/library/string.html#formatstrings) for more information on how this works.

```py
result = list(map(lambda p, k: "{:02x}".format(ord(p) ^ k), flag, key)) # changes output to hex because of the 'x'
```

Therefore, we need to convert from hex back to binary in order to start cracking the flag. We can do this in python by running 
```py
>>> e = '551257106e1a52095f654f510a6b4954026c1e0304394100043a1c5654505b6b'
>>> bytes.fromhex(e).decode("ASCII")
'U\x12W\x10n\x1aR\t_eOQ\nkIT\x02l\x1e\x03\x049A\x00\x04:\x1cVTP[k'
>>> len(e)
32
```

This also gives us the length of the flag, which is 32, since XORing two binary numbers does not change the length of the output. For example, assume the flag is the character 'a', and the key with which it was encrypted is the character 'b'. Then XORing both of them gives:

```py
>>> '0b{0:08b}'.format(ord('a'), 'b')
'0b01100001' # a in binary
>>> '0b{0:08b}'.format(ord('b'), 'b')
'0b01100010' # b in binary
>>> 0b01100001 ^ 0b01100010 # 'a' XOR 'b'
3
```

To reverse the operation, we can just XOR the output with the key again, to get the original flag in our example.
```py
>>> >>> '0b{0:08b}'.format(3, 'b')
'0b00000011' # 3 in binary
>>> 0b00000011 ^ 0b01100010 # 3 XOR 'b'
97 # gives 'a' in unicode
>>> chr(97)
a
```

Now that we know how much to loop around (which is the length of the key minus the length of the flag: 50000 - 32), and how to undo the XOR operation, we can try to retrieve the flag.

I made this script to automate the process. It starts a connection, and then sends 50000-32 random characters to loop around. Then, it send the unhexed flag to be encrypted and formats the output in the form of a flag.

```py
from pwn import *

io = remote('mercury.picoctf.net', 36449)

encrypted = unhex(io.recvline_startswith('55'))

io.sendlineafter("What data would you like to encrypt?",
                 'p'*(50000-len(encrypted)))
io.sendlineafter(
    "What data would you like to encrypt?", encrypted)
io.recvline()
flag = unhex(io.recvline())
print(f"picoCTF{{{str(flag, 'utf-8')}}}")
io.close()
```

However, the flag is incomplete: `picoCTF{75302b38697a}`. We can check this by trying to encrypt it. Running the following script in the terminal loops the pad around, and then we can paste the flag to encrypt it.

```sh
(python3 -c 'print("p" * (50000-32))';cat) | nc mercury.picoctf.net 36449
******************Welcome to our OTP implementation!******************
This is the encrypted flag!
551257106e1a52095f654f510a6b4954026c1e0304394100043a1c5654505b6b
... # looping around..
What data would you like to encrypt? 75302b38697a
Here ya go!
551257106e1a52095f654f51
```

We got the beginning portion of the flag, but not the whole thing. To get the rest of the flag, I brute forced every letter and number. This script takes the flag and adds each characters in `chars` to the flag. It then checks if the output matches the original encrypted flag, and if it does, it adds that character onto the flag. It does this until the flag matches the whole encrypted flag.

The full script can be found [here](script.py). Technically, the whole flag can be brute forced by modifying the loop.

```py
flag = b'75302b38697a'
chars = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
for i in range(26, 66, 2):
    for c in chars:
        io = remote('mercury.picoctf.net', 36449)
        log.success(f"Current character: {c}")
        e = io.recvline_startswith('55')
        io.sendlineafter("What data would you like to encrypt?",
                         'p'*(50000-len(encrypted)))
        io.sendlineafter(
            "What data would you like to encrypt?", (flag + c.encode()))
        io.recvline()
        new = io.recvline()
        if new[:-1] == e[:i]:
            flag += c.encode()
            break
        io.close()
print(f"picoCTF{{{str(flag, 'utf-8')}}}")
```

## Flag

`picoCTF{75302b38697a8717f0faee9c0fd36a57}`