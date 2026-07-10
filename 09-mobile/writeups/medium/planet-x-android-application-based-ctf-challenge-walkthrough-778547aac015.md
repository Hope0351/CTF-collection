# :mobile_phone: Planet X : Android Application Based CTF Challenge Walkthrough

---

# Planet X : Android Application Based CTF Challenge Walkthrough

Planet-X is an intermediate level Android application CTF challenge. The aim of this CTF challenge is to learn and concentrate on the basic flaws which are found while performing security assessment of a mobile application.

We will be observing the basic misconfigurations which will lead our path and help us to find the flag.

Let’s take a minute to thank [Moksh](https://in.linkedin.com/in/moksh-makhija) for creating this challenge. If someone wants to try and solve the challenge before going through the walkthrough, the link for the CTF can be found [[here](https://github.com/lucideus-repo/cybergym/tree/master/cybergym1/mobile/lab1)] and the application can be downloaded from [[here](https://github.com/lucideus-repo/cybergym/tree/master/cybergym1/mobile/lab1/app/release)].

So, before beginning the walkthrough, highlighting the fact that the challenge can be solved in two different ways. Both the ways teach us something unique and make us aware about the security flaws.

Just stay connected till the end….

First Approach is basically the intended way how the challenge was designed to be solved.

Tools Used :

>

[adb](https://www.xda-developers.com/install-adb-windows-macos-linux/) : command line tool that lets you communicate with device

[apktool](https://ibotpeaches.github.io/Apktool/) : command line tool for reverse engineering android applications

[jadx-gui](https://github.com/skylot/jadx) : tool for producing Java source code from Android Dex and APK files

---
