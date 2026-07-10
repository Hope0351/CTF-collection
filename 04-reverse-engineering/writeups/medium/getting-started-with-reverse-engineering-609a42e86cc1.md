# :arrows_counterclockwise: Getting Started with Reverse Engineering

> **Original Source:** [Getting Started with Reverse Engineering](https://infosecwriteups.com/getting-started-with-reverse-engineering-609a42e86cc1)
> **Platform:** infosecwriteups.com | **Category:** `REVERSE ENGINEERING`

---

# Getting Started with Reverse Engineering


Reverse engineering is the process of understanding the particular aspects of the program, which are listed below to identify the components of the system and the interrelationship between the components. And enhance the components of the system and improve the performance and scalability of the system (or) subsystem. Software reverse engineering is a technique that converts a machine code of a program (string 0’s and 1’s usually sent to the logic processor) back into the programmable language statements which are called source code. Software reverse engineering is done to get the source code of the program because to know how the particular parts of the program perform particular operations to improve the program functionality or to fix the bugs in the program or to find the malicious block of statements in the software if any.


Generally, this reverse engineering will take place in older industries on machines. But now it is frequently used on computer hardware and software. The important contents like data formats, algorithms that the programmer used to implement the software, and ideas of the programmer (or) company will be revealed to the 3rd person by violating the security and privacy issues using reverse engineering technique.


Reverse engineering in and of itself doesn’t mean changing the subsystem or developing the new system based on the existing. Reverse engineering involves a very broad range of aspects such as starting from the existing implementation, recreating or recapturing the design ideas, and extracts the actual requirements of the existing system. Design recovery is the most vital subset of reverse engineering because in which knowledge of the domain, external (or) outer side information, and deduction or fuzzy reasoning are added to the investigated (or) subjected system to find the high level abstract of the system, normally which is not obtained by directly observing the system.

### What do we need for reverse engineering?


To start reverse engineering software, you need:
knowledge in the field where you want to apply reverse engineering
tools that will allow you to apply your knowledge while trying to disassemble the software.
Let’s consider a generic example that isn’t connected to the software. Let’s say you have a watch and you want to find out if it’s mechanical, quartz, or automatic.
Knowing the field means you should know that there are three types of watches. Additionally, you should know that if there’s a battery, it’s located inside the watch, and you can see it if you open it up. You should also have basic knowledge of a watch’s internal structure, what the battery looks like, and what tools you need to open a watch case. Having the tools to apply your knowledge means that you need to have a screwdriver or other dedicated tool that will give you the chance to open the watch.
Just like reverse engineering a watch requires a specific skill set and tools, reverse engineering software requires its field-specific knowledge and tools.


### Useful tools for reverse engineering Windows software


We’ve already described several reverse engineering tools, including ProcessMonitor and ProcessExplorer, in our application architecture research. These tools are indispensable for reverse engineering.
In this section, we’ll review the most popular disassemblers and a few more tools that we use for our reverse engineering projects.
You can get more details and usage examples in our article on the best software reverse engineering tools.


Disassemblers:
A disassembler is a program that translates an executable file to assembly language. The most popular one is IDA Pro


IDA Pro


IDA Pro is a convenient and powerful tool for disassembly. It has a huge number of instruments that allow you to quickly disassemble a piece of software. It can show the function call tree, parse import and export of the executable, and show information about them. It can even show the code in C. Also, it supports multiple CPU architectures, so it’s possible to use IDA Pro to reverse engineer code for ARM, AVR, M68k, and many other architectures.


## Get ZeusCybersec’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Radare
The Radare disassembler is an alternative to IDA. It has all the IDA features without being as robust and stable. But it’s free and open source. Radare itself is a console tool, but it has a Cutter frontend, which makes it a true alternative to IDA.


Windows Sysinternals
Windows Sysinternals utilities are generally used for management, diagnostics, troubleshooting, and monitoring of the Microsoft Windows environment. But they’re also suitable for reverse engineering Windows software.


TCPView is a network sniffer that shows all information about TCP/UDP packets from all processes. This tool is useful for reversing network protocols.
PortMon is a physical system port monitor. It monitors serial and parallel ports and all traffic that goes through them.
WinObj shows all global objects in the system in a hierarchical structure. This tool can be useful when reversing an application that works with synchronization primitives such as mutexes and semaphores and also when reverse engineering kernel-mode drivers.
Network monitoring tools


Wireshark
Wireshark is one of the most powerful network sniffers. It not only allows you to capture network traffic but also contains parsers for various network protocols, starting from really low-level like Ethernet, TCP, and IP to application-specific protocols like WebSockets and XMPP.


Fiddler
Fiddler is a web proxy that records traffic from browsers and allows you to analyze HTTP/HTTPS requests. Unlike Wireshark, it shows HTTP sessions instead of separate network packets. Fiddler also allows you to analyze compressed data sent over HTTP and analyze JSON and XML data when monitoring SOAP, REST, and AJAX requests.


API Monitor
API Monitor is a useful tool for discovering which APIs are called by an application and what behavior the application expects from those APIs. This tool has a powerful database and lets you see calls to a huge number of API functions of not only kernel32 and ntdll but also COM, managed environment, and others. Also, API Monitor provides convenient filtering mechanisms.
Debuggers
A debugger is invaluable for any developer to see what a program is doing right now. You get the same benefit from debugging when reversing applications as you get from debugging live applications.
The most popular debuggers are OllyDbg, WinDbg, and Windbg Preview.


*Reversing in OllyDBG*OllyDBG
OllyDbg (and its successor x64dbg) is probably the best debugger when it comes to software reverse engineering. It was specifically developed for the needs of reversing, and has all the tools needed for that purpose:
a built-in disassembler with the ability to analyze and identify key data structures
an import and export analysis feature
a built-in assembling and patching engine
The ability to parse API functions and their parameters makes it easy to reverse interactions with a system. The stack view provides a lot of information about the call stack. One more important advantage is that you may use OllyDbg with debug-protected applications when usual debuggers just can’t do anything.


Windbg
Despite its simple interface, WinDbg has powerful tools for debugging. It has a built-in disassembler, various commands that allow you to know almost everything about the process/system you’re debugging, and the ability to do kernel-mode debugging, which is probably the most valuable feature. It’s a big advantage for reversing drivers, kernel-mode drivers in particular.


Windbg Preview
Windbg Preview is a new version of Windbg developed by Microsoft. It’s distributed via the Windows Store only. It has all the features of the classic Windbg coupled with a new UI and several new features. One of these new features is Time Travel Debugging, which allows you to record some period of program execution and then replay it as many times as you need. This way, you can execute the interesting parts of the code by stepping, without being afraid to run some code accidentally and lose the context or all the data.


I would like to thank Hackers Arcade for sharing this article([https://hackersarcade.tech/blog/](https://hackersarcade.tech/blog/))


Make sure to follow me on this Platform to stay updated with more such informative articles on Hacking - Zeus


### 🔵 For Cybersecurity Business/Product Promotion contact — sparshjazz@gmail.com

---

*Originally published on [Medium](https://infosecwriteups.com/getting-started-with-reverse-engineering-609a42e86cc1). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
