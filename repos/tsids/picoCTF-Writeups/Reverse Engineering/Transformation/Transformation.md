# [Transformation](https://play.picoctf.org/practice/challenge/104)

## Overview

**Points**: 20

**Category**: [Reverse Engineering](../)

## Description

I wonder what this really is... [enc](./enc) `''.join([chr((ord(flag[i]) << 8) + ord(flag[i + 1])) for i in range(0, len(flag), 2)])`

## Hints

1. You may find some decoders online

## Solution

When running `cat enc`, we get a bunch of symbols: `灩捯䍔䙻ㄶ形楴獟楮獴㌴摟潦弸弰摤捤㤷慽`. This doesn't translate to anything, so it must be coded. We could use the python code given to try to figure out how they were encoded.

The code shifts each character of the flag left by 8 bits (or 1 byte), then it adds the unicode value of the next letter to the shifted letter. Basically, it takes two letters from the original flag and merges them together into 1 letter represented by a byte.

Recall that `ord` takes a character and returns its unicode value (`ord('A') = 65`). Since the first character of each pair is moved over by 8 bits, it leaves room for new bits to come in. For example, take the letter 'p'. In binary p is

```py
>>> bin(ord('p'))
'0b1110000'
```

When we shift p over by 8 bits, we get

```py
>>> bin(ord('p') << 8)
'0b111000000000000'
```

There is now more room for a new letter to be added.

```py
>>> bin(ord('i'))
'0b1101001'
>>> bin((ord('p') << 8) + ord('i'))
'0b111000001101001'
```

If we shift the new binary 8 bits to the right, we get `p` again.

```py
>>> bin(0b111000001101001 >> 8)
'0b1110000'
>>> chr(0b111000001101001 >> 8)
'p'
```

Using this trick, we can shift each letter of the flag right by 8 bits to get the first letter of the pair.

```py
>>> for letter in flag:
...     print(chr(ord(letter) >> 8), end='')
... 
pcCF1_isis3do__dc9a
```

The original code shifts the first letter to the left and then adds the unicode value of the second letter. Therefore, we can use the first letter to find the value of the second letter.

Since shifting the letter right 8 bits gives us the first letter of the pair, we can shift it 8 bits to the left again to get the original value before the second letter was added.

```py
>>> bin((ord('p') << 8) + ord('i'))
'0b111000001101001'
>>> bin(0b111000001101001 >> 8)
'0b1110000'
>>> bin(0b1110000 << 8)
'0b111000000000000' # We get the shifted value of 'p' before 'i' was added
```

Subtracting this new value from the original `ord` value gets us the unicode value of the second letter of the pair, and we can convert it using `chr` to figure out the letter.

```py
>>> for letter in flag:
...     print(chr(ord(letter) - ((ord(letter) >> 8) << 8)), end='')
... 
ioT{6bt_nt4_f80dd7}
```
Putting it altogether, we have

```py
>>> for letter in flag:
...     print(chr(ord(letter) >> 8), end='')
...     print(chr(ord(letter) - ((ord(letter) >> 8) << 8)), end='')
... 
picoCTF{16_bits_inst34d_of_8_0ddcd97a}
```

You can also find a list comprehension version of the code in [script.py](script.py).

## Flag

`picoCTF{16_bits_inst34d_of_8_0ddcd97a}`
