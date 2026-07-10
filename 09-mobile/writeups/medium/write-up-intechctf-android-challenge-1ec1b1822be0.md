# :mobile_phone: Write up IntechCTF - Android Challenge

---

# Write up IntechCTF — Android Challenge

This year, Politeknik Negeri Bali held an event that had a CTF competition called IntechCTF. Unfortunately, I failed to register because when I know the event from CTFTime, it was too late.

*IntechFest Website*

However, my coworker attends the competition and share the challenge archive after the competition. Some categories are interestingly named “Android”, which all challenges in the category related to Android reverse engineering. I completed all the challenges and it's so much fun and so much to learn.

Here is the list of the challenge and write-up.

· Flag
· JNI
· OAT
· Reflection
· Sign
· Game
· Conclusion

On the challenge game, I would create a new article because this challenge had a few parts and a few flags that must be solved one by one.

All challenges can be downloaded on my GitHub [here](https://github.com/maulvialf/CTF-Challs-Archive/tree/main/intechctf-2022/Android).

## Flag

*Flag challenge description*

The first challenge that I attempt is named “flag”. Based on the description, just load the APK files on the JADX-GUI, and search for the resource, we should find a string that contains “flag”

*Find flag string on the resources*

Search the hash on Crackstation we get hash cracked with string Android. This is supposed to be the flag (perhaps)

*Find hash on the crackstation*

## JNI

*JNI challenge description*

The second challenge that I attempt is called JNI. There are provided APK files and src.cpp files that may be library source files

When the application launches, there are two buttons and one kind of address on the screen

*JNI Challenge Launch*

However, when the user clicks “get flag”, application would force closed. Let's continued with a static analysis on the APK files.

On the Main Activity, there are function get_flag

*On the main activity exist get_flag function*

We try to call this function on Frida to find out the return value. However, if we hook this function, the application would force closed.

*Frida hook get_flag()*

*Frida force closed*

However, if we tried to look in the application logcat, there are interesting outputs.

*logcat of com.intechfest.jni has the flag*

There are flag on the logcat. To understand why this happened, we need to look code on the library (in this scenario, problem setter already provided the library source code)

*src.cpp files*

Function get_flag would execute a function named with the flag that did not exist as class name.

Application also prints the log to the logcat, so the flag would show on the log.

## OAT

*OAT Challenge description*

The third challenge that I tried is a challenge named OAT. On this challenge, we just provided with ELF binary

*Challenge files identified as ELF*

Load binary on the decompiler (in this scenario load this binary to IDA), would show interesting output.

IDA would give suggestions to load the binary as ELF-OAT.

*Load ELF Files to IDA identified as ELF_OAT*

After googling for a while, I know that ELF-OAT is all dex that is cached on the android that saved as ELF files. Continued to load this binary as ELF-OAT would take a few minutes regarding the machine resources.

After code is loaded on the IDA, there are function named java.lang.String com.mxtech.videoplayer.ad.ActivityWelcomeMX.decrypt_flag() and disassembled as smali.

*Smali code of decrypt_flag()*

If we are able to run this smali code, the flag is supposed to be shown on the output. However how to run smali code without APK? After googled it, I found some simple wrappers that are able to run smali code here [https://github.com/JesusFreke/smali/blob/master/examples/HelloWorld/HelloWorld.smali](https://github.com/JesusFreke/smali/blob/master/examples/HelloWorld/HelloWorld.smali). Connect the device with ADB (to make sure we are able to use Dalvik VM), and run the command.

These are the smali files that I converted from IDA pro to HelloWorld.smali.

*Smali code to get flag*

Below is automation to compile smali files to dex, compress dex to zip, push zip to the device and run the zip files with dalvikvm. Luckily our assumption is right and flag is shown on the output.

*script to automate compile, push and run smali on android device*

*flag acquired after run the smali*

## Reflection

The fourth challenge that I attempt is a challenge named “reflection”.

*Reflection Challenge Description*

On this challenge, we provided with APK files and src.cpp files that were supposed to be lib source code. Launch the application did not show any useful information

*Reflection Challenge Launch*

Let's continued with a static analysis of the APK files.

*Reflection Main Activity called get_flag directly*

On the main activity, there is a function get_flag that is called on the main function. However, this function only returns the string “Hmmmm”.

Let's look at src.cpp files that are provided.

*Function get_flag on the binary had a comparison check*

On the source code, there are comparisons that check function would return flag or return “Hmmmmmmmmmmmmmm” string.

Native binary application, called java method getPackageCodePath and getPackageResourcePath. This method must had return value “uwoghhhhhhh cnnuy T_T T_T T_T” to bypass the comparison and print the flag.

After googling the documentation of android, I knew that method getPackageCodePath and getPackageResourcePath exist on the class android.content.ContextWrapper that exist by system default android.

After we know the classes and the methods, lets continued create frida script to hook the method to return “uwoghhhhhhh cnnuy T_T T_T T_T”;

*Frida script to replace getPackageCodePath and getPackageResourcePath*

Run the script and flag would acquired on the screen

*Run frida script then flag acquired on the screen or get_flag return value*

## Sign

Fifth challenge that I attempt is challenge named sign.

*Sign description*

On this challenge provided APK files and src.cpp files that supposed to be library files.

*Sign application launch*

Same with other challenge, launch the application did not show any useful information. Lets as usual continued static analysis on the beloved decompiler Jadx-GUI.

*Main Activity of sign APK*

On the main activity, application had comparison if isAdmin variable true, program would call native function get_flag. Lets hook the onCreate method to modified isAdmin to true.

However this script had return invalid signature.

Lets check the src.cpp code that provided. Below is snippet code of src.cpp

*source code library of sign*

On the native function get_flag, there are such processing and comparison. I would not explain what all the code doing. However we should look on the line 26–28. There are hash digest generation on the code and bytes generated save to digestBytes variable. That variable than extracted to hex and compare with static value SIGNATURE. If we had return digest hex same with the signature, according to the code we should get the flag.

Below is frida code implementation to hook hash signature generation. In general explanation, code would replace the return value of digest bytes with signature from static value that we already set.

*Frida solve of sign*

Executed the script and we would get the flag

*Flag Acquired on the return*

## Game

*Game description*

This part can be read here. This part consists of 2–4 different problems and flags.

## Conclusion

I learn so much when do this challenge. Challenge OAT made me learn write smali code while debugging why IDA parser code cannot be extract it directly. GGWP for the problem setter ([https://github.com/aimardcr](https://github.com/aimardcr) and teams) already provide us with android challenge.

---
