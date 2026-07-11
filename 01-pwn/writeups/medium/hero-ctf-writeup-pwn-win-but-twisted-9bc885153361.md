# :skull: Hero CTF Writeup — PWN Win but Twisted

---

# Hero CTF Writeup — PWN Win but Twisted

This Challenge is based on PWN or Binary Exploitation.

**Image Source : Hero CTF**

This is a fairly easy challenge if we know the concept of Stack buffer overflow. We get 2 files for this challenge. One is the binary itself and the other is a C file. Below is the code which was given.

If we analyze the code, we can see the global variable UNLOCKED = 0. The shell function has the system() which gives us access to the machine and we might find the flag there. If we bypass the “if condition” in SHELL Function, which could be done by setting the valued UNLOCKED = 1. This could be done by the function Set_lock().

How do we call these functions?

If you see the main(), we can see the buffer[32]. This takes in 32 characters. The fgets() get the input for buffer and we have 44–32 = 12 spaces left after the buffer array is filled.

This is the place where we can include our function set_lock() and shell()
To do this we need to know the address for the following function, which GDB will help us to get.

Now we can manually insert these functions after filling up the buffer, which is 32 characters. The function has to be inserted in a little-endian format.

**Image Source : Google**

The exploit is as follows

We use python to fill 32 characters and the required functions to be given .

The function address has been given in a little-endian format. AND TADA !! We get the flag for the challenge

Write up by Hariharan Sundar aka Corrupted_Protocol , Team 1nf1n1ty

---
