# :skull: Binary Brilliance: Unleashing Pwn | CTF Newbies

---

# Binary Brilliance: Unleashing Pwn | CTF Newbies

## Introduction

In the intricate world of cybersecurity, understanding vulnerabilities and exploiting them is both an art and a science. From the humble beginnings of early hackers tinkering with systems to today’s sophisticated penetration testing, the exploration of vulnerabilities remains a critical aspect of securing digital infrastructures. This introduction serves as a gateway into this realm, shedding light on the fundamentals of exploiting vulnerable machines.

## Prerequisites

- Basic Computer Skills: A fundamental understanding of operating systems (e.g., Windows, Linux) and basic command-line usage is essential. This includes familiarity with file systems, processes, and basic system administration tasks.

- Networking Concepts: Knowledge of networking fundamentals such as TCP/IP, DNS, HTTP, and network protocols is crucial. Understanding how data moves across networks and between systems is essential for exploiting vulnerabilities effectively.

- Programming Fundamentals: Proficiency in at least one programming language (e.g., Assembly, Python, C, or Bash scripting) is highly recommended. You should understand variables, data types, loops, conditional statements, and basic algorithms. Additionally, familiarity with debugging techniques is beneficial.

- Web Technologies: Basic knowledge of web technologies such as HTML, CSS, JavaScript, and HTTP protocols is advantageous, especially if you intend to explore web application vulnerabilities like SQL injection, XSS (Cross-Site Scripting), and CSRF (Cross-Site Request Forgery).

- Virtualization: Experience with virtualization platforms like VirtualBox or VMware is recommended. Virtual machines (VMs) provide a safe environment for practicing exploitation techniques without risking damage to real-world systems.

- Security Tools: Familiarity with common security tools such as Wireshark (for network analysis), Nmap (for network scanning), Metasploit (for exploitation), and Burp Suite (for web application testing) is beneficial. Understanding how to use these tools effectively enhances your ability to identify and exploit vulnerabilities.

## Binary Exploitation

Binaries, or executables, are machine code for a computer to execute. For the most part, the binaries that you will face in CTFs are Linux ELF files or the occasional windows executable.

We can solve these type of challenges by identifying these vulnerabilities in the file :-

### 1. Buffer Overflow —

A Buffer Overflow is a vulnerability in which data can be written which exceeds the allocated space, allowing an attacker to overwrite other data.

The simplest and most common buffer overflow is one where the buffer is on the stack.

```
#include <stdio.h>
#include <string.h>

void vulnerable_function(char *input) {
char buffer[10];
strcpy(buffer, input);
printf("Buffer content: %s\n", buffer);
}

int main() {
char input[20];
printf("Enter a string: ");
scanf("%s", input);
vulnerable_function(input);
return 0;
}
```

In this example, `vulnerable_function` is the vulnerable function. It takes a string `input` as a parameter and copies it into a fixed-size buffer `buffer` using the `strcpy` function. The buffer size is 10 bytes, but there is no check on the length of the input string. If the input string is longer than 10 characters, a buffer overflow will occur, overwriting adjacent memory locations on the stack.

Run this program, and provide an input string longer than 10 characters.

```
$ ./buffer_overflow
Enter a string: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
```

This will likely cause a segmentation fault or undefined behavior, as the program tries to write beyond the bounds of the buffer array.

We can use a debugger to see the offsets and the assembly of the program. As you will get this program in a.out only so you can debug and decompile this and can understand the assembly of the program.

### 2. Heap Exploits —

Much like stack buffer overflow, a heap overflow is a vulnerability where more data than can fit in the allocate buffer is read in.

## Get HackTheBox SRMIST’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Example —

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct string {
unsigned length;
char *data;
} string;

int main() {
struct string* s = malloc(sizeof(string));
puts("Length:");
scanf("%u", &s->length);
s->data = malloc(s->length + 1);
memset(s->data, 0, s->length + 1);
puts("Data:");
read(0, s->data, s->length);

free(s->data);
free(s);

char *s2 = malloc(16);
memset(s2, 0, 16);
puts("More data:");
read(0, s2, 15);

// Now using s again, a UAF

puts(s->data);

return 0;
}
```

in this we have a string structure with a length and a pointer to the actual string data. We properly allocate, fill, and then free an instance of this structure. Then we make another allocation,fill it , and then improperly reference the freed string. Due to how glibc’s allocator works, s2 will actually get the same memory as the original s allocation, which in turn gives us the ability to control the s->data pointer. This could be used to leak program data.

## Useful Tools

- PWNTools: This is a Python library that provides a set of utilities and APIs for crafting exploits, interacting with binary programs, and automating various tasks involved in exploitation.

- ROPgadget: Return-oriented programming (ROP) is a technique used in exploitation to bypass certain security mechanisms like DEP (Data Execution Prevention). ROPgadget is a tool used for finding gadgets (small snippets of code ending in a return instruction) in binaries that can be chained together to form an exploit payload.

- anger: This is an open-source binary analysis It combines both static and dynamic symbolic (“consoles”) analysis, providing tools to solve a variety of tasks.

- Immunity Debugger: This is a powerful new way to write exploits, analyze malware, and reverse engineer binary files. It builds on a solid user interface with function graphing, the industry’s first heap analysis tool built specifically for heap creation, and a large and well-supported Python API for easy extensibility.

- peda (Python Exploit Development Assistance): peda is a Python plugin for GDB (GNU Debugger) that provides additional commands and features to assist with exploit development. It simplifies tasks such as searching for gadgets, analyzing memory, and crafting payloads.

- BinDiff: BinDiff is a commercial tool for binary diffing, which compares two binary executables to identify similarities and differences. It’s commonly used for vulnerability analysis, patch diffing, and reverse engineering.

- Frida: Frida is a dynamic instrumentation toolkit that allows for runtime manipulation and analysis of binary executables across various platforms. It can be used for dynamic binary instrumentation, hooking functions, and exploring program behavior during runtime.

## PWN Example

Over here we will be taking a basic example for the PWN Challenge. The example we will be taking is the Stonks question from the picoctf.

Question:

I decided to try something no one else had before. I made a bot to automatically trade stocks for me using AI and machine learning. I wouldn’t believe you if you told me it’s unsecure!

[vuln.c](https://mercury.picoctf.net/static/e4d297ce964e4f54225786fe7b153b4b/vuln.c)

```
nc mercury.picoctf.net 20195
```

Now we see a netcat command over here and we run it to see the following

Now if we have a look at the vuln.c file we see that it scans the API key using a string so using %x it can generate something of interest.

So we select option 1 and we see that it asks for the API Key so we bombard the input with many %x’s.

Now we add this hexadecimal string to decode to find the flag: picoCTF{l_I4_t5m_ll0m_y_y3n5406d06d}

NOTE: You have to remove some elements to get the perfect flag.

## Tools Used In Example

Cyberchef- To decode Hex to String

Any Code Editor- To have a look at the code

## Resources

## Conclusion

In the above article, we have seen how a PWN challenge works and how can we approach a challenge in the PWN or Binary Exploitation. Hope you have understood and will feel at ease in solving the questions.

## Contribution

Devansh Gupta

Dhruv Pridhnani

Abihimanyu V

## Happy Hacking!!

---
