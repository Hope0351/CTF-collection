# :mobile_phone: BackDoor 1: Walkthrough of NET-SQUARE Hacking Warm-Up Mobile Application Challenge

> **Original Source:** [BackDoor 1: Walkthrough of NET-SQUARE Hacking Warm-Up Mobile Application Challenge](https://infosecwriteups.com/backdoor-1-walkthrough-of-net-square-hacking-warm-up-mobile-application-challenge-7433b8e1a482)
> **Platform:** infosecwriteups.com | **Category:** `MOBILE`

---

# BackDoor 1: Walkthrough of NET-SQUARE Hacking Warm-Up Mobile Application Challenge


Recently got an opportunity to participate in a CTF (Capture-The-Flag) event which was organized by NET-SQUARE. They had their different set of challenges with respect to Mobile, Web, Network, Source Code, and Thick/Thin Client. So, there were few quite interesting mobile application challenges and here we will be discussing one of them.

>

*Note: Those who want to explore and want to try the challenges on their own before reading the walkthrough can access the applications from the *[GitHub](https://github.com/jain6196/NET-SQUARE-Mobile-Application-Challenges)* repository. The application can be downloaded from [*[here](https://github.com/jain6196/NET-SQUARE-Mobile-Application-Challenges/blob/main/Backdoor1/backdoor1.apk)*]. Kindly share your experience with me in the comment box.*Challenge Description: The application hides username and password inside the application and we need to find the credentials using various tools and techniques to log in.


Tools Used :

>

[adb](https://www.xda-developers.com/install-adb-windows-macos-linux/)* : command line tool that lets you communicate with device*[apktool](https://ibotpeaches.github.io/Apktool/)* : command line tool for reverse engineering android applications*[jadx-gui](https://github.com/skylot/jadx)* : tool for producing Java source code from Android Dex and APK files*[Android Studio](https://developer.android.com/studio/?gclid=EAIaIQobChMIrK6UjcPr6wIVzKuWCh2ViASpEAAYASAAEgJ_qvD_BwE&gclsrc=aw.ds)* : official Integrated Development Environment (IDE) for Android app development*[Device](https://www.genymotion.com/)* : Android Device/Android Studio*…

---

*Originally published on [Medium](https://infosecwriteups.com/backdoor-1-walkthrough-of-net-square-hacking-warm-up-mobile-application-challenge-7433b8e1a482). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of mobile CTF writeups.*
