# :game_die: CTF Write-Up: Shiftpocalypse

> **Original Source:** [CTF Write-Up: Shiftpocalypse](https://infosecwriteups.com/ctf-creation-shiftpocalypse-579cb8d6c050)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# CTF Write-Up: Shiftpocalypse


- CTF challenge available at ctf-mystiko.com.

- Challenge name: Shiftpocalypse

- Category: Cryptography


— — — — —


We are given the following sequence of numbers:


1232 1936 1840 1856 1680 1712 1776 1968 1632 816 1392 1520 1792 816 768 1792 1216 816 1520 1584 1040 1760 1520 576 1664 784 1120 1856 2000


## Get Antonio Lara’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The name of the challenge contains two hints: “shift” and “apocalypse”. Shift indicates that the shift operation has been used, or needs to be used. Apocalypse is related to the number four (four horsemen of Apocalypse). Even if we don’t relate the second hint to the number four, we can think that the shift operation was applied to the flag, and we need to reverse it to recover the plaintext.


The shift operation basically means shifting bits to the left (<<) or to the right (>>). In this way, 1 (001 in binary) becomes 4 (100 in binary) when we do 1<<2 (meaning that we shift the bits of the number 1, which is the first operand by two positions to the left, therefore 001 becomes 010 and then 100). Note that, as we are dealing with binary numbers, the shift to the left operation is the same thing as multiplying by 2, and shifting to the right is equal to dividing by two.


To solve this problem we will create a loop that applies shifts of different amount of positions to the numbers in the sequence, and print the output, hopefully one line of which will be the plaintext flag:


As suggested by the name, four shifts to the right return the numbers corresponding to the char values of the plaintext flag (notice the printf used with the “%c” format, because we need to convert the numbers to chars:


*The plaintext flag is found after shifting 4 positions the numbers and getting the corresponding chars*


One could argue that we could have shifted to the left instead to solve the challenge. Aside from trying both directions and finding the correct one, note that that would imply that the original operation to get the initial sequence of numbers would have consisted in that case of shifts to the right (so that we would undo that with our left shifts). But shifting to the right is dangerous, as it can “push” to the right the lowest significant bits, making them disappear and they wouldn’t be able to be recovered later by shifting to the left. That would of course happen as well if we shifted left a very large number, approaching the limit of its type maximum allowed value, but it’s not to be expected for these small numbers we are given.

---

*Originally published on [Medium](https://infosecwriteups.com/ctf-creation-shiftpocalypse-579cb8d6c050). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
