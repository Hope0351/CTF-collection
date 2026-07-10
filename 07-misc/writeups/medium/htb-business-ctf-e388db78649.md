# :game_die: HTB-Business CTF. Payback PWN Challenge

---

## Payback PWN Challenge

Hey there! I know it’s been a long since I wrote any blogs but I am now back with a bang!

I always love pwn challenges in CTF though I am not that good at it. But still, I try to learn them and practice them a lot so as to become great at them someday. And today is one such day where I learned some really cool things and I am excited to share them with you, my buddy!

So let me jump right into the challenge!

For reader’s note, I did not solve this challenge during the CTF as I got stuck at a point and was clueless but I did learn one new thing which helped me solve it after the CTF.

So the challenge is, we are given a binary, source code, loader, libc, and few other things as shown below.

*Challenge files*

As for every challenge, first, understand the binary, and the different protections in place we go for the most used tool for binary exploitation,

>

checksec

Information obtained from this:

The architecture is amd64.

- NX bit is set: This implies we cannot execute shellcode from the stack even though we get a buffer overflow in the binary. But that does not stop us because we are The Most Creative People (but I won’t talk about the method in this post)

- PIE (Position Independent Executable): This is one cool thing that I understood from this challenge. This protection loads your program and its various dependencies in different memory regions each time it is executed. As a result of this, you don’t see the exact memory address of your program in a debugger like gdb instead you see offsets from the start of the elf binary.

I know it’s really boring and dry, so I will show you some cool pics depicting the above.

Since we have the source code, I will compile the program without PIE enabled (Yes it is indeed possible) and show you the difference.

*Compiling source code*

The difference

You could see that the binary without PIE disabled(one on the left) has the exact address of the memory location of each instruction whereas the binary with PIE enabled (one on the right) has offsets from the ELF binary’s base. So when the program is executed the binary gets loaded into a random memory location and the instructions get loaded by adding the offsets to the base.

Though this may not be useful for the challenge I want you to understand this buddy.

4. Full RELRO: This was the one that stopped me and made me clueless about the challenge. This protection when enabled does not allow arbitrary writing on the Global Offset Table during the execution.

The linker will perform all the symbol lookups at link time(before execution starts) and then it will remove the write permissions from the GOT.

Procedure Linkage Table becomes part of Global Offset Table.

If some of the above terms sound scary or make you clueless please do refer to the below video by LiveOverFlow.

5) The final boss is ASLR enabled: This might not be visible directly but most modern systems have this enabled by default. This protection randomizes the location of system executables in the memory for each execution. The system executables include the LIBC which is the library used by C programs for using trivial functions like printf, scanf, and a lot more!!!

If you have ever wondered where these functions are defined and declared now get this right buddy they all are inside LIBC!!!!!

### Now let’s see ASLR in action

We use ldd a tool that prints dynamic dependency ( the files and executables required during runtime for successful execution of the program you execute ) of executables.

Each time libc.so.6 is loaded in a different memory location.

### EXPLOITATION:

Now getting to the source code of the challenge we see basically 3 operations that actually work.

*Dummy ones*

The 5,6,7 just print string in the console and does nothing!

So the interesting ones are Add, Edit, and Delete bot functions.

The bot is a user-defined struct that has id and URL variables in it.

*Bot struct*

After reading the source code we find the culprit which is …………..

## The delete bot function.

The vulnerabilities are:

>

the user input is directly passed onto the printf function causing Format String Vulnerability

the other one which I learned after the CTF is another user input being passed onto the free function without protection. (Abuse the free-hook function pointer)

### Free hook:

What this basically does is give developers a way to define their own functions that get executed whenever free, malloc, or any such functions are called.

## Get Thirukrishnan’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So the exploit development is as follows,

>

a) Use the format string vulnerability to leak some contents from the stack

b) Find a libc address that is at a constant position in the stack on every run of the binary.

c) Find the offset of the libc address you have leaked from the libc base using gdb and find the libc base. (ASLR defeated)

d) Now calculate the address of the free-hook, system libc function, and use format string to overwrite free-hook pointer with the system libc function that gives us a shell.

e) Call delete bot and pass the argument as /bin/sh to free function (which now points to the system)

f) Now see the shell pop open and take a moment to enjoy the feel!!!

### Step 1:

Add a bot with random data and select Delete bot and provide a valid ID which is 0 here and in the reason enter the payload to gather few information.

### Initial Payload:

>

AAAAAAAA| %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p

%p is to print 64-bit memory address in the stack!

### Output:

First, we see 0x4141… which is AAA… the input we have provided. This is intuitive as the input we provide is also in the stack as an argument passed to printf function.

So the 8th position from the stack is out input.

Step 2: Now, we have a few addresses starting with 0x7f which are stack addresses in general. You can see this is gdb and now we need to find which among them is a valid libc address to defeat ASLR.

For this, attach gdb to the running process as shown below and investigate the addresses.

Examining the last address in gdb we see

### Boom!!!

We found a valid libc address great! And this does not change in every run.

Now find the offset of this from libc base address for that follow the steps.

>

In the same gdb window type vmmap.

>

The first address where you see libc.so.6 is its base address.

Calculate offset with Leaked address — base

With this, the entire challenge is almost done. Yeah, it is done believe me!!

Now we need to calculate free-hook and system’s libc address and write them using printf instead of printing the stack.

For further learning on Format String Vulnerabilities see the below link.

Format string attacks are really made easy with pwntools. They are the most versatile and best tools for binary exploitation which makes the job a bit easy!!

You can generate the payload to make this write by

*Calculate libc base from format stringUpdate libc with the calculated value*

You just need to update the libc variable with the libc base you have calculated and use the fmt_str to generate a payload to overwrite.

### So now the next time we call the delete bot function, the function free(botBuf[id].url) will execute system libc function.

So for this, you have to once again Add a bot with URL as /bin/sh .

>

This is because this string is actually passed onto free which now points to the system. Now, this executes system(“/bin/sh”) which pops open a shell.

Now Delete the bot you have created above and see your shell pop open!!!

## Man, you have made it! Kudos!!

This is one good challenge I have ever solved and this made me learn a ton and push my understanding to a good extent. I hope this was useful for you too!

Please do refer to my Github for the challenge file and exploit!

>

[https://github.com/Thirukrishnan/Payback-PWNchallenge](https://github.com/Thirukrishnan/Payback-PWNchallenge)

---
