# :arrows_counterclockwise: Reverse Engineering Injection Series Part 4 Blue Team Labs 8Efe326049Dc

> **Original Source:** [Reverse Engineering Injection Series Part 4 Blue Team Labs 8Efe326049Dc](https://infosecwriteups.com/reverse-engineering-injection-series-part-4-blue-team-labs-8efe326049dc)
> **Platform:** infosecwriteups.com | **Category:** `REVERSE ENGINEERING`

---

>

Scenario: Reverse Engineer the given file and understand the behavior. You can use any disassembler you like to complete this challenge.


You can access the challenge using above link and try along with me. I am going to use IDA Pro to disassemble the given file and to find the answers of the questions.

### Question 1) What is the process that would be first spawned by the sample? And what is the API used? (Format: Format: process, API Call) (1 Point)


The question asks to find out the first spawning process by a malware file and API used to spawn the process. You guessed it right, CreateProcessA API might be used to spawn the process, but this is not the only API can be used to spawn the process. Let’s open the binary in IDA Pro and take a look what is happening under the hood.


## Get Jay Vadhaiya’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Let’s first take a look at strings, what do the strings are saying ?


*IDA Pro Strings*


As we can see, the notepad.exe is being opened. Let’s double check it with assembly view. Click on start function from function window and scroll up to the top of the screen.


*IDA Pro Assembly View*


Perfect, We got our answer of our first question. Note that, the instructions of the binary is stored in .text header of the binary. Even if you find entry function or start function, don’t forget to start from the top of the .text header block.

### Question 2) The value 4 has been pushed as a parameter to this API, what does that denote? (Format: FLAG) *(1 points)*


When any function or API is called, before calling the function or API all the required parameters are being pushed to stack in reverse order. Because stack operates on LIFO order, the last pushed value will be popped out first.


*IDA Pro Assembly View*


IDA Pro has already showed us the argument name or what argument it is. `dwCreationFlags` is a parameter used in the `CreateProcessA` function, which is part of the Windows API. This parameter specifies various creation options for the new process when it is created by the `CreateProcessA` function.


*Learn Microsoft*


*Learn Microsoft*


As per Microsoft documentation, the `value 4 (0x00000004)` represents the `CREATE_SUSPENDED` flag, which is used to load process in suspended mode and the process will not run until the `ResumeThread` function will be called. This solves our question and gives the answer.

### Question 3) What is the domain that the malware tries to connect? (Format: domain.tld) *(1 points)*


If you have observed strings in one of the previous questions, you must encountered a PowerShell script being executed on the system. Let’s have a look at it and see what does it contains.


*IDA Pro Strings*


Right click on it and copy to any text editor to analyse it. You will notice that the PowerShell is executing a base64 encoded strings with hidden window mode. Looking suspicious right? Decode the base64 strings with your fav decoder.


*CyberChef Base64 Decode*


Copy the output to any text editor and you will get the exact command executed by the PowerShell. This solves our question and gives us the answer.


*Decoded Base64 String*

### Question 4) What is the cmdlet used to download the file and what is the path of the file stored? (Format: CMDLET, path) *(1 points)*


Hmm, the previous findings are pretty enough to solve this question right away. There is nothing to find more in this question.

*Tenor.com*

### Question 5) Just after the file download instructions, a function from ntdll has been loaded and invoked by the sample. What is the function name? (Format: Function) *(2 points)*


Now the functions invoked from `NTDLL.dll` are always starts with `Nt` prefix. Let’s get back to IDA Pro Assembly view and see where ntdll is imported and used.


*IDA Pro Assembly View*


Very simple and easy to find it out. This solves our question and gives us the answer.

### Question 6) After the allocation of memory and writing the date into the allocated memory. What are the 2 APIs used to update the entry point and resume the thread? (Format: API, API) *(2 points)*


`VirtualAllocEx` and `WriteProcessMemory` are API function which are used to allocate memory and write data to the memory respectively. After allocating the memory and writing data to the memory, the suspended notepad.exe should be executed to run the malicious software.


*IDA Pro*


These are the two API function being called after writing data to the allocated memory. Yes, you are right. This solves our question and gives us an answer.

### Question 7) What is the MITRE ID for this technique implemented in this sample? (Format: TXXXX.XXX)


If you have observed while analysis, you might have noticed that malware first executes a process in suspended mode and then allocates some memory and write data into it. After that it resumes the process thread, which allows malware to do malicious activities without being detected by antivirus programs. This method of doing malicious activities are known as process injection or process hallowing.


*MITRE ATT&CK*

---

*Originally published on [Medium](https://infosecwriteups.com/reverse-engineering-injection-series-part-4-blue-team-labs-8efe326049dc). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
