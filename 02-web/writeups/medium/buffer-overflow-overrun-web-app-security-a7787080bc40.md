# :globe_with_meridians: Buffer Overflow/Overrun: Web App Security

---

# Buffer Overflow/Overrun: Web App Security

Let’s start with basics…

What is Buffer?

Buffers are the memory storage regions that temporarily holds the data while it is being transferred from one place to another.

What is Buffer Overflow/Overrun?

>

Buffer overflow is a security issue, which occurs when the volume of data exceeds the storage capacity of memory buffer and the exceed data could corrupts nearby space in memory or alter other data.

Example:

The buffer for username is designed to except input of 15 bytes, but if input is of 18 bytes, the application may writes the extra 3 bytes of data past the buffer boundary or program might fail to allocate enough space for buffer which can cause the program to behave unpredictably and generate incorrect results, memory access errors, or crashes.

Few products which were affected by buffer overflow:Types:

- Stack buffer overflow: The data on the stack is stored and retrieved as ‘last in first out’, the stack allocation is managed by the operating system, and access to the stack is fast. It is more common and leverage stack memory that only exists during the execution time of a function.

- Heap buffer overflow: The amount of memory that needs to be reserved is decided at runtime and it is managed by the program, not the operating system. It is harder to carry out and involves flooding the memory space allocated for a program beyond memory used for current runtime operations.

Languages which are more likely to be vulnerable:

## Get Hemant Birdi’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

C and C++ are two languages that are highly susceptible to buffer overflow attacks. These are low-level languages that rely on the developer to allocate memory and they don’t have built-in safeguards against overwriting or accessing data in their memory. Mac OSX, Windows, and Linux all use code written in C and C++.

Languages such as PERL, Java, JavaScript, and C# use built-in safety mechanisms that minimize the likelihood of buffer overflow. However, they are not completely safe. Some of them allow direct memory manipulation and they often use core functions that are written in C/C++.

Prevention:

- Do not trust user input.

- Check input length before using any functions.

- Static code scanning.

- Avoiding unsafe functions.

- Using Buffer overflow protection mechanisms like [ASLR](https://en.wikipedia.org/wiki/Address_space_layout_randomization).

- Use latest versions of components.

Reference:

---
