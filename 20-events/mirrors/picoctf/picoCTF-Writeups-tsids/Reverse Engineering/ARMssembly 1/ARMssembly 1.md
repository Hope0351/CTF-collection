# [ARMssembly 1](https://play.picoctf.org/practice/challenge/111)

## Overview

**Points**: 70

**Category**: [Reverse Engineering](../)

## Description

For what argument does this program print `win` with variables `83`, `0` and `3`? File: [chall\_1.S](./chall\_1.S) Flag format: picoCTF{XXXXXXXX} -> (hex, lowercase, no 0x, and 32 bits. ex. 5614267 would be picoCTF{0055aabb})

## Hints

1. Shifts

## Solution

> Look at this [aarch64 assembly cheat sheet](https://www.cs.swarthmore.edu/~kwebb/cs31/resources/ARM64_Cheat_Sheet.pdf) if you're unfamiliar with ARM assembly.

In order to solve this challenge, we need to try to get "You win!" to print, which is stored in the function `.LC0`.

```asm
.LC0:
	.string	"You win!"
	.align	3

main:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	w0, [x29, 28]
	str	x1, [x29, 16]
	ldr	x0, [x29, 16]
	add	x0, x0, 8
	ldr	x0, [x0]
	bl	atoi
	str	w0, [x29, 44]
	ldr	w0, [x29, 44]
	bl	func
	cmp	w0, 0
	bne	.L4
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
```

The program compares `w0` to `0`. If they're not equal, then it jumps to `.L4`, otherwise it continues to `.LC0`. However, before comparing values, it jumps to `func`.

The value of `w0` before going into `func` is the user input, since the value is loaded into `w0` from the stack, and converted into an integer using `atoi`.

```asm
func:
	sub	sp, sp, #32
	str	w0, [sp, 12]
	mov	w0, 83
	str	w0, [sp, 16]
	str	wzr, [sp, 20]
	mov	w0, 3
	str	w0, [sp, 24]
	ldr	w0, [sp, 20]
	ldr	w1, [sp, 16]
	lsl	w0, w1, w0
	str	w0, [sp, 28]
	ldr	w1, [sp, 28]
	ldr	w0, [sp, 24]
	sdiv	w0, w1, w0
	str	w0, [sp, 28]
	ldr	w1, [sp, 28]
	ldr	w0, [sp, 12]
	sub	w0, w1, w0
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	add	sp, sp, 32
	ret
```
`sp` refers to the stack pointer, and `wzr` is the zero register. \
Storing an item at `[sp, 12]` is equivalent to storing it at `sp + 12`.

Here's a quick review of the commands:
- `mov a, b` => `b = a`.
- `str a, [sp, c]` => `sp[c] = a`. (Store at sp + c)
- `ldr a, [sp, c]` => `a = sp[c]`. (Load from sp + c)
- `sub a, b, c` => `a = b - c`.
- `lsl a, b, c` => `a = b << c`.
- `sdiv a, b, c` => `a = b / c`.

The function `func` does the following:
1. Stores `w0` into `[sp, 12]`.
2. Moves `83` into `w0` and stores it into `[sp, 16]`.
3. Stores `0` into `[sp, 20]` from `wzr` (the zero register).
4. Moves `3` into `w0` and stores it into `[sp, 24]`.
5. Loads `0` into `w0` from `[sp, 20]` and `83` into `w1` from `[sp, 16]`.
6. Shifts `83` left by `0` and stores it into `w0`.
   - `w0 = 83 << 0 = 83`.
7. Stores `83` into `[sp, 28]`.
8. Loads `83` into `w1` from `[sp, 28]` and `3` into `w0` from `[sp, 24]`.
9. Divides `83` by `3` and stores it into `w0`.
   - `w0 = 83 / 3 = 27`.
10. Stores `27` into `[sp, 28]`.
11. Loads `27` into `w1` from `[sp, 28]` and `w0` into `w0` from `[sp, 12]`.
12. Subtracts `w0` from `27` and stores it into `w0`.
    - `w0 = 27 - w0`.
13. Returns the function. 

We can see that `w0` stores the result of `27 - w0`. Since `w0` is the user input, we can set `w0` to `27`. So, we have `w0 = 27 - 27 = 0`. This means that the program will not jump to `.L4` but will continue to `.LC0`, allowing us to get the program to print "You win!". 

Therefore, the answer is 27, which is `0000001b` in hex.

Lets compile the code and run it to see that our answer is correct. 
```bash
sudo apt install binutils-aarch64-linux-gnu gcc-aarch64-linux-gnu qemu-user
aarch64-linux-gnu-gcc -static -o chall chall_1.S
./chall 27
You win!
python3 -c "print(f'{27:08x}')" # format into hex
0000001b
```

## Flag

`picoCTF{0000001b}`
