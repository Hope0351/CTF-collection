# :mobile_phone: Universe Weird C132 : Android Application Based CTF Challenge Walkthrough

> **Original Source:** [Universe Weird C132 : Android Application Based CTF Challenge Walkthrough](https://infosecwriteups.com/universe-weird-c132-android-application-based-ctf-challenge-walkthrough-af834c6c9467)
> **Platform:** infosecwriteups.com | **Category:** `MOBILE`

---

# Universe Weird C132 : Android Application Based CTF Challenge Walkthrough


Universe Weird C132 is a beginner level Android application CTF challenge. It makes you realise that every application is a treasure hunt, more of a treasure and less of a hunt.


The aim of this CTF challenge is to concentrate on the basic flaws which are found while performing security assessment of a mobile application. We will be observing the basic mis-configurations which can lead to huge data loss.


Let’s take a minute to thank [Moksh](https://in.linkedin.com/in/moksh-makhija) for creating this challenge. If someone wants to try and solve the challenge, the link for the CTF can be found [[here](https://github.com/lucideus-repo/cybergym/tree/master/cybergym1/mobile/lab4)] and the application can be downloaded from [[here](https://github.com/lucideus-repo/cybergym/blob/master/cybergym1/mobile/lab4/app/release/com.cybergym.lab4.apk)].


Tools Used :

>

[adb](https://www.xda-developers.com/install-adb-windows-macos-linux/) : a command line tool that lets you communicate with device


[apktool](https://ibotpeaches.github.io/Apktool/) : command line tool for reverse engineering android applications


[jadx-gui](https://github.com/skylot/jadx) : tool for producing Java source code from Android Dex and APK files


[Android Studio](https://developer.android.com/studio/?gclid=EAIaIQobChMIrK6UjcPr6wIVzKuWCh2ViASpEAAYASAAEgJ_qvD_BwE&gclsrc=aw.ds) : official Integrated Development Environment (IDE) for Android app development


[Device](https://www.genymotion.com/) : Android Device/Android Studio Emulator/Genymotion Emulator


Connecting the device with a USB cable and entering command for checking proper connectivity.

---

*Originally published on [Medium](https://infosecwriteups.com/universe-weird-c132-android-application-based-ctf-challenge-walkthrough-af834c6c9467). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of mobile CTF writeups.*
