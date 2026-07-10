# :arrows_counterclockwise: CTF Writeup | RanDom BUG | Reverse Engineering

> **Original Source:** [CTF Writeup | RanDom BUG | Reverse Engineering](https://me-ankeet.medium.com/ctf-writeup-random-bug-reverse-engineering-f17ebba1c5b3)
> **Platform:** me-ankeet.medium.com | **Category:** `REVERSE ENGINEERING`

---

# CTF Writeup | RanDom BUG | Reverse Engineering


In this article, I will do a walk through of a CTF challenge which was a part of TyroCTF 2024 under the Reverse Engineering category.


We have been given an executable named a.out. You can download the executable from [here](https://github.com/CSecIITB/TyroCTF_2024/blob/main/Reversing/ranDom_BUG_medium/a.out). Let’s see what it does.


So, as you can see, it asks us to input a random number. If we guess the random number incorrectly, then it prints the troll message. On opening [binaryninja](https://binary.ninja/) and looking around, we understand that this executable works like this.


- It generates a random number dynamically each time it is run.

- It prompts you for a number.

- It checks whether number you have entered is equal to the random number it generated this time.

- If check does not pass it prints the troll message.

- If check passes it calls a function win().


Now the function win() is quite obfuscated and would be a real pain to reverse it. But with its name (win()) it is pretty safe to assume that this function generates and prints out the flag. (Coz it does have a print statement at the end)


So now we have two options.


- Go through the pain of reversing the win() function using any decompiler of your choice.

- Use GDB (more elegant)


In this writeup, I will use GDB.


This would require some prior knowledge of gdb and assembly language. Resources for the same are provided [here](https://www.geeksforgeeks.org/gdb-step-by-step-introduction/) and [here](https://www.youtube.com/playlist?list=PLmxT2pVYo5LB5EzTPZGfFN0c2GDiSXgQe).


So let’s move forward now and open the executable using gdb.


Note that I am using a different flavor of gdb so mine might look a bit different from yours.


So as you can see in the highlighted portion, we just had a call to the function that generates the random number. Now the return value of any function is by convention, stored in eax. So if we set a breakpoint at the this address, and check the value of eax, then we will know what the random number is.


So the commands I used to reach till this point are:


- break *main+155

- run

- p $eax


So as you can see, the random number generated in this case is `39015676`


Now, I `continue` in gdb and enter this number as my input.


And voila! We have our flag.


Flag:


`tyroCTF{0h_5h1t_1_f0rg0t_4b0ut_gdb}`

---

*Originally published on [Medium](https://me-ankeet.medium.com/ctf-writeup-random-bug-reverse-engineering-f17ebba1c5b3). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
