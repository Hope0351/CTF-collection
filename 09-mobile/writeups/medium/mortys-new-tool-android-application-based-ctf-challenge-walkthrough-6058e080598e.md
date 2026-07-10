# :mobile_phone: Morty’s New Tool : Android Application Based CTF Challenge Walkthrough

---

# Morty’s New Tool : Android Application Based CTF Challenge Walkthrough

Morty’s new tool is an intermediate level Android application CTF challenge. The basic aim of this CTF challenge is to learn the dynamic transformation in the code at run time, reverse engineering of native libraries and much more.

It will give an atmosphere of real time scenarios which will teach us the working of an application, its process and data flow.

Let’s take a minute to thank [Moksh](https://in.linkedin.com/in/moksh-makhija) for creating this challenge. If someone wants to try and solve the challenge before going through the walkthrough, the link for the CTF can be found [[here](https://github.com/lucideus-repo/cybergym/tree/master/cybergym1/mobile/lab3)] and the application can be downloaded from [[here](https://github.com/lucideus-repo/cybergym/blob/master/cybergym1/mobile/lab3/app/release/com.cybergym.lab3.apk)].

Tools Used :

>

[adb](https://www.xda-developers.com/install-adb-windows-macos-linux/) : a command line tool that lets you communicate with device

[apktool](https://ibotpeaches.github.io/Apktool/) : command line tool for reverse engineering android applications

[jadx-gui](https://github.com/skylot/jadx) : tool for producing Java source code from Android Dex and APK files

[Android Studio](https://developer.android.com/studio/?gclid=EAIaIQobChMIrK6UjcPr6wIVzKuWCh2ViASpEAAYASAAEgJ_qvD_BwE&gclsrc=aw.ds) : official Integrated Development Environment (IDE) for Android app development

[Device](https://www.genymotion.com/) : Android Device/Android Studio Emulator/Genymotion Emulator

[Ghidra](https://ghidra-sre.org/) : Open source reverse engineering tool

[Frida](https://frida.re/docs/android/) : dynamic code instrumentation toolkit for native applications

---
