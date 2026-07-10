# :game_die: Ctf Creation Hell Yeah 6D774Aecad8F

> **Original Source:** [Ctf Creation Hell Yeah 6D774Aecad8F](https://infosecwriteups.com/ctf-creation-hell-yeah-6d774aecad8f)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

- CTF challenge available at ctf-mystiko.com.

- Challenge name: Hell yeah!

- Category: Reverse engineering

- Language: C++


— — — — —


## Get Antonio Lara’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Example showing a way to prevent CTF players from getting the flag hidden inside a binary by using the “strings” command. I have found that strings doesn’t print strings shorter than (at least) three characters. So in this case the flag is printed line by line to standard output, without ever being stored in a variable.

*Source code for hellyeah.cpp*


To solve this challenge we need to break out of the “while” loop, which runs forever. To be able to proceed to where the flag is created.


That can be easily done (and without too much thinking) by replacing all the jumps with nops. Using x64 debugger (in this case x32, the 32 bit version, as x64 complains about wrong architecture), to replace an instruction we do: Right click on the instruction> assemble > add nops


We can just pause the program when it gets loaded in the debugger, step over the instructions, and when we reach a jmp, instead of stepping over it, we first replace it with a nop.


*Jumps have been replaced by nops*


At some point we will have patched the jump that returns us to the beginning of the while loop, so we can proceed further and see the flag printed line by line.

*The flag is printed line by line*


In general, when reversing a program, it’s interesting to replace jmps with nops to access parts of the program that fall out of the normal logic, but this can result in unexpected behaviors, and a lot of trial and error may be required.

---

*Originally published on [Medium](https://infosecwriteups.com/ctf-creation-hell-yeah-6d774aecad8f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
