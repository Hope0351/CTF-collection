# :game_die: Phoenix Challenges - Stack Zero. An explanation of Exploit Education’s…

> **Original Source:** [Phoenix Challenges - Stack Zero. An explanation of Exploit Education’s…](https://infosecwriteups.com/phoenix-challenges-stack-zero-f8743cc871ed)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Phoenix Challenges — Stack Zero


## The Challenge


The challenge’s description and source code are located [here](https://exploit.education/phoenix/stack-zero/). It and all other Phoenix binaries are located in the /opt/phoenix/amd64 directory. A [previous post](https://secnate.medium.com/phoenix-challenges-getting-set-up-a2783e0616c6) describes how to set up the Virtual Machine for *Exploit Education’s Phoenix *challenges, if that hasn’t been done already.

## Objective


Looking at *Stack Zero’s* C code, we see the *changeme* variable stored in the *locals* struct initialized to 0. The goal is to tamper with its value and make it non-zero to print the desired statement.

## Related Concept


Executed programs look like this inside computer memory:


The stack and the heap are the two main memory structures. To keep it short:


- The Stack is used for storing information regarding called functions and their local variables. When a new function is called, the machine expands the stack’s size downwards with more room for storing its local variables and information regarding this function call. Conversely, the machine frees up stack memory and decreases its size upwards when a function is exited. Stack memory management is automatically performed during execution.

- The Heap is used by programs to allocate memory on the fly during execution. This is especially useful if the amount of memory needed is *unpredictable*. For example, a browser receiving messages of variable lengths may grab chunks of Heap memory into which incoming messages are to be placed for processing.


The Heap’s memory is managed explicitly by programmers during low-level languages’ execution. The malloc(), calloc(), free(), and realloc() functions are used in C and the new and delete operators are used in C++. Higher-level and memory-safe languages such as Python and Java use memory managers to handle the heap securely out of sight.


Those desiring further clarification regarding how the Stack and Heap work may find [this explanation](https://courses.engr.illinois.edu/cs225/sp2022/resources/stack-heap/) helpful.

## The Bug


All of Stack Zero’s data is stored on the stack, with the *locals* struct’s *buffer* and *changeme* variables being adjacent neighbors. Excess data rammed into the *buffer* will spill over into the *changeme* variable and affect its value. This spillover is caused by gets() function for writing console-entered input into the *locals.buffer* not performing any bounds-checking.

## The Exploit


The *locals.buffer* into which the input is written has space for 64 characters. Since the *locals.changeme* variable was 0 originally, the exploit needs to tamper with its memory location to make it have a non-zero value. This is done by feeding in an input string of 65 characters, with the last directly spilling over into the *locals.changeme* variable’s memory and making it non-zero.


## Get Nathan Pavlovsky’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The exploit was scripted with *pwntools*, a Python framework for exploit development. The code has extensive explanatory comments since it is the first of this series. It can be found in my [Github repository](https://github.com/secnate/Exploit-Education-CTFs) for Phoenix challenge solutions.


The result?


```
nathan@nathan-VirtualBox:~/Desktop/Exploit-Education- CTFs/Phoenix/stack-zero$ ./stack-zero-exploit.py
Launching The Phoenix Stack Zero Exploit!
[!] Could not find executable 'stack-zero' in $PATH, using '/opt/phoenix/amd64/stack-zero' instead
[+] Starting local process '/opt/phoenix/amd64/stack-zero': pid 12739
[*] Switching to interactive mode
[*] Process '/opt/phoenix/amd64/stack-zero' stopped with exit code 0 (pid 12739)
Welcome to phoenix/stack-zero, brought to you by https://exploit.education
Well done, the 'changeme' variable has been changed!
[*] Got EOF while reading in interactive
$
```


## Remediation


To prevent such a memory corruption bug, I would encourage developers to not write in C and to transition to memory-secure languages such as Python or Rust.


If there is no choice but to use C, I would caution against using the [gets()](https://www.tutorialspoint.com/c_standard_library/c_function_gets.htm) function to extract inputs from the command line. As just seen, it reads input until the newline or end-of-file characters are reached, regardless of the destination buffer’s size.


The [fgets()](https://cplusplus.com/reference/cstdio/fgets/) function should be used instead. It parses command-line input and places it into the destination buffer while performing the appropriate bounds checks. The source code’s `gets(locals.buffer);` line would thus be`fgets(locals.buffer, 64, stdin);`


An additional bonus of using fgets is that it automatically terminates the buffer with the terminating *null* character (“\0”). Programmers may forget to insert such a character manually. So in the case of this challenge, it is only 63 characters that would read from the command line into the buffer, with the 64th being “\0”.


Terminating a buffer with a null character is critical for preventing buffer over-read vulnerabilities. These involve leaks of data as a function reading a buffer does not meet a terminating character and continues past the buffers’ end into adjacent memory.


The most notorious example of such that comes to mind is the [2014 OpenSSL Heartbleed bug.](https://owasp.org/www-community/vulnerabilities/Heartbleed_Bug) For those unfamiliar, OpenSSL is a widely-used open-source implementation of SSL and TLS cryptographic protocols used by websites and systems to establish secure and verified connections. Bruce Schneier, a security expert who has historically been very conservative when talking about the effects of security issues, [called it catastrophic](https://www.schneier.com/blog/archives/2014/04/heartbleed.html):

>

*On the scale of 1 to 10, this is an 11.*


That’s all for this round. Stay tuned for the *Stack One* challenge, an extension of *Stack Zero* — with a twist!

---

*Originally published on [Medium](https://infosecwriteups.com/phoenix-challenges-stack-zero-f8743cc871ed). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
