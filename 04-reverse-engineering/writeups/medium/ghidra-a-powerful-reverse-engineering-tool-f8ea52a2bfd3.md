# :arrows_counterclockwise: Ghidra — A powerful Reverse Engineering Tool

> **Original Source:** [Ghidra — A powerful Reverse Engineering Tool](https://infosecwriteups.com/ghidra-a-powerful-reverse-engineering-tool-f8ea52a2bfd3)
> **Platform:** infosecwriteups.com | **Category:** `REVERSE ENGINEERING`

---

# Ghidra — A powerful Reverse Engineering Tool


Hello everyone, I recently started exploring Ghidra, an open-source reverse engineering tool. Through reverse engineering, hackers can analyze a program’s components and functionalities in order to identify any vulnerabilities. By analyzing the code or binary of the program, one can recover the original software design for more effective hacking. Reverse engineering can also help malware analysts to identify malicious software by analyzing the source code.


Follow up to this post: [Detecting DLL injection in Windows](https://medium.com/@suprajabaskaran8/detecting-dll-injection-in-windows-804e065f5eb7).

## About Ghidra


Ghidra is one of the most powerful and popular reverse engineering frameworks used extensively today, which was developed by the NSA (National Security Agency) of the USA. It offers a user-friendly interface which permits users to reverse engineer binaries, debug code, and analyze code in many languages. It also includes several advanced features, such as code decompilation, scripting capabilities, and collaboration tools that allow multiple analysts to work together on the same project.


To demonstrate the features of Ghidra, I have taken a sample binary from the following github link —[https://github.com/Maijin/radare2-workshop-2015/tree/master/IOLI-crackme/bin-win32](https://github.com/Maijin/radare2-workshop-2015/tree/master/IOLI-crackme/bin-win32)


Ghidra Installation and Setup:


*Pre-requisites:*


- VM — Windows or any Linux-based OS


2. Ghidra download link — [https://github.com/NationalSecurityAgency/ghidra/releases](https://github.com/NationalSecurityAgency/ghidra/releases)


3. JAVA — JDK 17 or Java 17


*Can be installed from -*

>

*$sudo apt-cache search java18$ sudo apt install openjdk-17-jdkInstallation steps:*


## Get Suprajabaskaran’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Extract the zip file using the command -

>

*$ unzip *[ghidra_10.2.3_PUBLIC_20230208.zip](https://github.com/NationalSecurityAgency/ghidra/releases/download/Ghidra_10.2.3_build/ghidra_10.2.3_PUBLIC_20230208.zip)


Navigate to the directory and run this executable file -

>

*$./ghidraRun*


## Features of Ghidra:


To import a binary file into Ghidra, we can follow these steps — navigate to the Ghidra window, select “Import file,” and choose the desired binary file. Once imported, Ghidra will display some initial information about the file. Ghidra will then prompt the user to choose whether to analyze the file automatically, with various options available.

*Initial Information on the Crackme BinaryGhidra auto analyzer module*


The Program Trees menu in Ghidra Code Browser shows various program views of the current program, such as the Names tree, Functions tree, Data Types tree, and much more, as shown in the figure. It lists all the headers, text, data bss segments of the stack. These views display a hierarchical representation of the program’s components, allowing users to navigate through the program more easily and quickly. This menu provides a convenient way to switch between different program views and perform various analyses and debugging tasks in Ghidra. We can use the modularize by dominance option which will list all the segments which Ghidra thinks important to check first and we find the main function as shown in the figure.

*Ghidra Code Browser — Program Tree*


The Symbol Trees lists all the imports, exports, functions, classes and labels. Imports display all the libraries imported by the binary and export contain functions written by malware authors. We can find the program entry point in exports.

*Ghidra Code Browser — Symbol Tree*


Data Type Manager provides us with the data that have been used within the malware. For example, we can identify the usage of strings in the binary. The following window is the Listings window where the assembly code resides. We can customize how the window would display the assembly code. From the Script Manager, we can add external scripts as per our need for analysis. The list of scripts can be found within the Script Manager.

*Ghidra Code Browser — Data Type ManagerGhidra Code Browser — Listings windowGhidra Code Browser — Script Manager Window*


The Decompiler is the most important feature. It presents the binary as a human-readable C language code, as shown in the figure. Its navigation is integrated with the listing window (assembly code).

*Ghidra Code Browser — Decompiler Window*


Different operations can be performed in the Listings window.

*Operations by Ghidra Code Browser Listings*


Any function can be chosen to view the control flow in a graphical representation. In addition, bytecode of a malware can also be viewed.

*Graphical representation of the function’s control flow — Ghidra Code BrowserGhidra Code Browser — Malware Bytecode representation*

## Conclusion


Applying reverse engineering to evaluate programs can be an effective approach to discovering any weak points. Ghidra is an excellent tool, to begin with if you are looking to get into reverse engineering. This is just an introduction to how to start with the Ghidra Code Browser and some ideas on a few of its features. But, there is a lot more to Ghidra apart from what is mentioned in this post.


In the following post, I will show a straightforward add-on to the Ghidra framework, which I and my friend have developed to identify DLL injection in the binaries.


Edit: Please check outmy post on [Detecting DLL injection in Windows](https://medium.com/@suprajabaskaran8/detecting-dll-injection-in-windows-804e065f5eb7) too :)


I hope you find success during your venture with Ghidra. I thank you for your time spent reading. Did I forget to mention anything? Please do not hesitate to inform me :)

*Buy me a coffee — [https://www.buymeacoffee.com/suprajabask](https://www.buymeacoffee.com/suprajabask)*

---

*Originally published on [Medium](https://infosecwriteups.com/ghidra-a-powerful-reverse-engineering-tool-f8ea52a2bfd3). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
