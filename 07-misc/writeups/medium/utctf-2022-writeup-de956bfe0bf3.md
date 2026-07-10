# :game_die: UTCTF 2022 - Writeup. I did some challenges in the UTCTF so I…

---

I did some challenges in the UTCTF so I would like to share the writeup of those.

- Jump around

This is beginner challenge which is based on the buffer overflow attack.

We have the binary file. To analysis it we can use software like [Ghidra](https://ghidra-sre.org/)or [IDA](https://hex-rays.com/ida-pro/). I used to ghidra and viewed the functions through the decompiler.

We have the main function which is not more informative and looks more straight forward it the input from user.

When I observed the functions available in the binary. I found the ‘get_flag’ function which is suspicious.

So, it basically calls the system function with ‘/bin/sh’. This is the vulnerability which will give us the shell access to server.

---
