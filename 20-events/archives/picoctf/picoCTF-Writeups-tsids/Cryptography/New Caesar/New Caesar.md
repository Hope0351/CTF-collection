# [New Caesar](https://play.picoctf.org/practice/challenge/158)

## Overview

**Points**: 60

**Category**: [Cryptography](../)

## Description

We found a brand new type of encryption, can you break the secret code? (Wrap with picoCTF{}) `mlnklfnknljflfjljnjijjmmjkmljnjhmhjgjnjjjmmkjjmijhmkjhjpmkmkmljkjijnjpmhmjjgjj` [new\_caesar.py](./new\_caesar.py)

`new_caesar.py`:

```python
import string

LOWERCASE_OFFSET = ord("a")
ALPHABET = string.ascii_lowercase[:16]

def b16_encode(plain):
	enc = ""
	for c in plain:
		binary = "{0:08b}".format(ord(c))
		enc += ALPHABET[int(binary[:4], 2)]
		enc += ALPHABET[int(binary[4:], 2)]
	return enc

def shift(c, k):
	t1 = ord(c) - LOWERCASE_OFFSET
	t2 = ord(k) - LOWERCASE_OFFSET
	return ALPHABET[(t1 + t2) % len(ALPHABET)]

flag = "redacted"
key = "redacted"
assert all([k in ALPHABET for k in key])
assert len(key) == 1

b16 = b16_encode(flag)
enc = ""
for i, c in enumerate(b16):
	enc += shift(c, key[i % len(key)])
print(enc)
```

## Hints

1. How does the cipher work if the alphabet isn't 26 letters?
2. Even though the letters are split up, the same paradigms still apply

## Solution

The solution script is in [decode.py](./decode.py).

Looking at the code, we can see that the `key` has to be a letter in `ALPHABET` (letters a through p) and the length of key is 1.

```python
assert all([k in ALPHABET for k in key])
assert len(key) == 1
```

To solve it, we should try to reverse the encoding script to decrypt the cipher that is given (`mlnklfnknljflfjljnjijjmmjkmljnjhmhjgjnjjjmmkjjmijhmkjhjpmkmkmljkjijnjpmhmjjgjj`).

Let's analyze what is happening.

The `b16_encode` function takes each letter in the flag, and converts it to binary. Then, it takes the first 4 bits and converts it to a letter in `ALPHABET`, and does the same for the last 4 bits. So it takes in 1 letter, and returns 2 letters. 

For example, if the letter is `r`, then it is converted to `01110010` in binary. Then, the first 4 bits are `0111`, which is `7` in decimal, so it is converted to `h`. The last 4 bits are `0010`, which is `2` in decimal, so it is converted to `c`. So, `r` is converted to `hc`.

 This is essentially a base 16 encoding, which is why the function is called `b16_encode`.

We can reverse the `b16_encode` function by breaking the cipher into pairs of letters, then converting each letter of the pair to a number between 0 to 15 in binary. Then, we can convert the number to a letter in `ALPHABET`. 

For example, if the pair is `hc`, then we can convert `h` to `0111` and `c` to `0010`. Then, we can combine the two binary numbers to get `01110010`, which is `114` in decimal. Then, we can convert `114` to `r`, which is the corresponding letter.

```python
def b16_decode(enc):
	enc = [enc[i:i+2] for i in range(0, len(enc), 2)] # breaks string into pairs of letters
	plain = ""
	for pair in enc:
		n1 = "{0:04b}".format(ALPHABET.index(pair[0]))
		n2 = "{0:04b}".format(ALPHABET.index(pair[1]))
		binary = int(n1 + n2, 2)
		plain += chr(binary)
	return plain
```

After encoding the flag using `b16_encode`, the `shift` function is called on each letter. This function takes the letter and shifts it by the value of the key. The key is a letter in `ALPHABET`, so it is converted to a number from 0 to 15. Then, the letter is shifted by that number. 

For example, if the letter is `a` and the key is `c`, then the letter is shifted by 2, so it becomes `c`. If the letter is `p` and the key is `c`, then the letter is shifted by 2, so it becomes `r`, but since `r` is not in `ALPHABET`, it becomes `b` (the letter at index 1).

We can reverse the shift function by taking each letter in the cipher, and shifting it backwards by the value of the key. 

For example, if the letter is `c` and the key is `c`, then the letter is shifted backwards by 2, so it becomes `a`. If the letter is `b` and the key is `c`, then the letter is shifted backwards by 2, so it becomes `p` (since it wraps around `ALPHABET`). In essence, we just subract instead of add before taking the modulus.

```python
def unshift(c, k):
	t1 = ord(c) - LOWERCASE_OFFSET
	t2 = ord(k) - LOWERCASE_OFFSET
	return ALPHABET[(t1 - t2) % len(ALPHABET)]
```

Finally, remember to reverse the operations of encoding and shifting in the correct order. So, we first unshift the cipher, then we decode the cipher. The script can also be found in [decode.py](./decode.py).

```python
import string

LOWERCASE_OFFSET = ord("a")
ALPHABET = string.ascii_lowercase[:16]

def b16_decode(enc):
	enc = [enc[i:i+2] for i in range(0, len(enc), 2)] # breaks string into pairs of letters
	plain = ""
	for pair in enc:
		n1 = "{0:04b}".format(ALPHABET.index(pair[0]))
		n2 = "{0:04b}".format(ALPHABET.index(pair[1]))
		binary = int(n1 + n2, 2)
		plain += chr(binary)
	return plain

def unshift(c, k):
	t1 = ord(c) - LOWERCASE_OFFSET
	t2 = ord(k) - LOWERCASE_OFFSET
	return ALPHABET[(t1 - t2) % len(ALPHABET)]

cipher = "mlnklfnknljflfjljnjijjmmjkmljnjhmhjgjnjjjmmkjjmijhmkjhjpmkmkmljkjijnjpmhmjjgjj"
for key in ALPHABET:
	assert all([k in ALPHABET for k in key])
	assert len(key) == 1
	decode = ""
	for i, c in enumerate(cipher):
		decode += unshift(c, key[i % len(key)])
	flag = b16_decode(decode)
	print(f"Key: {key}, Flag: {flag}")
```

After going through all the letters in `ALPHABET`, this option seems to best fit the flag.

```console
Key: g, Flag: et_tu?_5723f4e71a0736d3b1d19dde4279ac03
```

## Flag

`picoCTF{et_tu?_5723f4e71a0736d3b1d19dde4279ac03}`