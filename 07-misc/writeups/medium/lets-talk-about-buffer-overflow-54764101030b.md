# :game_die: Let’s talk about buffer overflow. A buffer overflow, or buffer overrun…

---

# Let’s talk about buffer overflow

A buffer overflow, or buffer overrun, occurs when more extra data is put into a fixed-length buffer than the buffer can manage.

Buffer overflow is possibly the best-known form of software security vulnerability. Most software developers know what a buffer overflow vulnerability is, but buffer overflow attacks corresponding to both legacy and newly-developed applications are still quite obvious. Part of the difficulty is due to the wide category of ways buffer overflows can happen, and part is due to the error-prone procedures often used to prevent them.

In a classic buffer overflow exploit, the attacker transmits data to a program, which it stores in an undersized stack buffer. The result is that data on the call stack is overwritten, including the function’s return pointer. The data sets the value of the return pointer so that when the function returns, it gives control to malicious code contained in the attacker’s data.

Although this type of stack buffer overflow is still prevalent on some policies and in some development communities, there is a mixture of other types of buffer overflow, including heap buffer overflows and off-by-one errors between others.

At the code level, buffer overflow vulnerabilities normally require the destruction of a programmer’s theories. Many memory manipulation functions in C and…

---
