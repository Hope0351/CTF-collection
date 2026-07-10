# :arrows_counterclockwise: Write Up Reverse Engineering— LINE CTF 2023— Fishing and Jumpit

---

# Write Up Reverse Engineering— LINE CTF 2023— Fishing and Jumpit

## Introduction

*LINE CTF banner*

A week ago, I participated in LINE CTF as part of team TCP1P, with the username mahoushoujo. I managed to solve two reverse engineering challenges named Fishing and Jumpit, and our team secured 16th place out of 477 teams.

Today, I want to share a write-up for these two challenges.

All files can be downloaded [here](https://github.com/maulvialf/CTF-Challs-Archive/tree/main/2023/line-ctf-2023)

## Table of Content

· Introduction
· Table of Content
· Fishing
· Jumpit
· Epilogue

## Fishing

*Challenge description*

In this challenge, there is a binary called fishing.exe. Running the binary prompts the user to input the correct flag.

*When running the program, the input prompt appears*

Now, let’s view the program in the decompiler

In the decompiler, there are a few strings defined that are printed on the prompt.

*String list*

However, if we look at the references, these strings are not used from any address.

*String not referenced by any function*

If we examine the function code, we can see that the program fails at the decompiled code. This can be proven by some of the code below.

*Program has anti-decompiler instructions— 1*

*Program has anti-decompiler instructions— 2*

This occurs because the program has anti-decompiler instructions that break the analysis. Now we need to investigate how the anti-decompiler works in this program.

For this analysis, I used the function sub_140001DDB.

*Sample code to analyze anti-decompiler*

If we look at the disassembly view, we can see the program jumps to location 140001E15+1.

*Analysis of anti-decompiler instruction*

Now, let’s view the code at 140001E16 by undefining the code at 140001E15 and defining the code again at 140001E16.

*Undefine code to ensure we are able to define another address as codeDefine +1 address as code.*

After doing this, we should see the following instruction

*The anti-decompiler instruction uses inc eax and dec eax to normalize the eax*

The program increases and decreases the eax value, which does not affect the execution flow.

Now we know that the bytecode EB FF XX, with XX as any byte, serves as an anti-decompiler. To patch this, I created a Python script to find this pattern in the binary and replace it with a nop instruction.

Running the program and reopening the new file fishing-patch.exe in the decompiler.

*After patch, string already referenced*

After patching, the string is already referenced, and the program should now decompile successfully.

*startAddress now able to decompiled*

Before inspecting the main code, we should check for any anti-debugger code within the program.

If we examine the program’s functions, we can see the code below:

*Anti debugger 1Anti debugger 2*

This function would disrupt the program’s execution when attached to a debugger. To fix this, the function needs to be patched.

After patching, we should see the program prompting for input.

*Run program on the debugger now should ask input*

Now, let’s analyze the program. Below is the main function that has been renamed based on its functionality:

In the startAddress function, the program encrypts our input using a combination of XOR and subtraction processes. The program also performs XOR and addition processes on our key. After modifying the key and input, the program executes a custom RC4 encryption and compares the results using memcmp with the encryptedFlag variable that has already been set.

However, this function is straightforward; I discovered strange behavior during the analysis.

Below is the value of the key when the program is being debugged:

*RC4 key as argument is not printable*

The program should run fine, performing the encryption XOR and using the key below:

*RC4 key as argument is not printable*

However, when my team debugged the program in Frida, we observed a different result. When executing this in Frida, my team found that the key used in the custom RC4 is “m4g1KaRp_ON_7H3_Hook”

*key variable had printable string when hooked in frida*

This strange behavior also exists in the input variable.

Below is another behavior of the program modifying the input:

*Input value somehow changed before enter sub34*

I tried inputting BBBBBBB into the program. The program correctly displayed the result as 63 63 63 63 in hex. But before entering sub34, the variable changed to 1b 1b 1b 1b in hex.

If we examine the code, the program does not perform any other processes between these functions.

*Another operation inserted between xor21 and sub34*

This behavior also exists in the key encryption. Before entering xor11, the key is not processed with any function.

*On the code key did not modified before entered xor11*

This code applies normally to the debugger.

*Behavior on the debugger runs normally, matching the code*

However, this behavior changes when entering xor11, as the key has already been altered to a different value, indicating that there is another process before entering the xor11 function.

*Key somehow modified before performing xor11*

This can happen because the program calls this function.

*Cause of anomaly: there are threading modifications*

In this function, the program sets up some kind of thread modification, causing the process in the debugger and the real-time process to exhibit different behavior.

I tried to analyze this process and attempted to duplicate the code in C, but still failed

However, I had another approach to solve this. If we look at the code, the program compares encryptedFlag with outputRc4 in the function. We can obtain the value of this argument using Frida.

*Program compared encryptedFlag and outputRc4*

The outputRc4 encryption used by the program also has a linear encryption, meaning if we modify the first byte input, only the first byte output is modified. Why not use Frida to brute force?

*This two parameter can be acquired to side channel attack*

After coming up with this idea, I tried to create a Frida script to hook the function address after input, replace our fake input with our brute-force input, and then hook the memcmp function to get the value of encryptedFlag and outputRc4.

I combined this Frida script with a Python script to wrap the automation, and we should be able to automate hooking in Windows (with a hacky script, I guess hehe).

Below is the Python script that I used to automate this process:

Below is frida script that I used to implement my ideas

Before running the script, don’t forget to create a tmp folder as a directory to store temporary thread outputs

`mkdir tmp`

Run the script and wait for a while until all flags can be guessed

`python2 mt3.py`

*Flag acquired after a while*

Notes:
Another intended solution that analysis threading handler can be viewed here: [https://blog.snwo.kr/posts/(ctf)-line-ctf-2023/](https://blog.snwo.kr/posts/(ctf)-line-ctf-2023/)

## Jumpit

*Challenge description*

In this challenge, a folder containing the Android distribution folder is provided.

*Challenge file folder*

However, only this folder is provided, without an APK build.

I checked the program in the native library and found libil2cpp.so and libunity.so, indicating that this project was built on the Unity framework.

*Library on the program*

In the program, I also found global-metadata files for Unity.

*There is global-metadata that can be used to dump IL2CPP data*

If metadata files exist, we should be able to view the program logic and discover the structure of libil2cpp.so using [Ill2cppDumper](https://github.com/Perfare/Il2CppDumper)

Run IL2CPPDumper and provide global-metadata.dat and libil2cpp.so.

After IL2CPPDumper is completed, these files will be generated:

*Files generated after running IL2CPPDumper on the library:*

This file can be used to resolve the structure and literal strings in the library. Now, using Ghidra (you can use IDA too for doing this), load the libil2cpp.so.

After the file is loaded, open the Window tab and open Script Manager.

*Script Manager in Ghidra to run Python script:*

Now, create a new script.

*Create new script button*

Choose Python and select a script name.

*Create new script for python*

Now, open the file ghidra_with_struct.py in the IL2CPPDumper directory and copy all the code to the new script that we just created.

*In the libil2cppDumper, there is a Python script that can be used to resolve IL2CPP binaries.*

After copying the code content, click Run.

*Running the script will prompt the user to input script.json, which has already been generated by IL2CPPDumper*

The program will ask for the script.json file that was generated by the IL2CPPDumper executable.

*Provide required files*

Now, we should be able to view the Unity logic in the library.

*Now function can be resolved and logic code can be analyzed*

Now, the function can be resolved, and the logic code can be analyzed. Below is the code for getFlag:

*The program performs decrypting ECB on getFlag*

In the getFlag method, the program executes DecryptECB with several parameters. Parameter _StringLiteral_2608 has a base64 value:

cWGTmeDlFsYEFI9E5mH/eCnQ1SNlWJlXj+klPLbWS/c/1vI7UPrO4dp41u2tTGM2

*StringLiteral 2608 contains the encrypted string*

This value is an encrypted string that will be decrypted by AES ECB.

Another parameter, *(param_1 + 0x50), points to another value.

*Pointer to AES ECB key*

If we look at the GameManager$$ScoreUp method, this pointer is used and concatenated with another StringLiteral when the score reaches a certain point.

Below is the logic code for GameManager$$ScoreUp:

*For every score that reaches specific points, parts of the key will concatenate to the AES key pointer.*

If we combine all score comparisons from the lowest to the highest and concatenate all StringLiterals for every score, the pointer will have the string value “Cia!fo2MPXZQvaVA39iuiokE6cvZUkqx”.

I then created a Python script to decrypt “cWGTmeDlFsYEFI9E5mH/eCnQ1SNlWJlXj+klPLbWS/c/1vI7UPrO4dp41u2tTGM2” using the key “Cia!fo2MPXZQvaVA39iuiokE6cvZUkqx”, and the flag was acquired in the output.

*Flag acquired after decryption*

## Epilogue

I learned a lot while doing this CTF. Automating debugging and brute-forcing on Windows is always challenging because the environment is not as robust as GDB scripts running on Linux. Unity reverse engineering is also something rare that I’ve encountered in CTFs.

I hope this write-up helps people learn about Unity reverse engineering and Windows brute-forcing.

---
