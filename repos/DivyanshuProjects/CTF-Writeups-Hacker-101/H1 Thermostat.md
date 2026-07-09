 🔐 H1 Thermostat CTF Writeup — Digging Through Android APKs for Flags!

Hi! I'm Divyanshu, and I’m passionate about cybersecurity, reverse engineering, and exploring the internals of mobile apps. Whether it's breaking down Android APKs or diving into CTFs, I love the thrill of solving complex puzzles and uncovering hidden secrets. In this blog, I’ll walk you through my detailed approach to solving the H1 Thermostat Android CTF, where I reversed an APK to uncover a hidden flag. 

This isn’t just a technical breakdown — it’s a story of digital forensics, code archaeology, and that unbeatable rush when you finally find what’s been buried deep inside an app.

---

🕵️ Exploring an APK File & Reverse Engineering It to Uncover Hidden Secrets (Just Like Hunting Malware!)

🔐 CTF Challenge: H1 Thermostat  
📱 Platform: Android  
🎯 Objective: Reverse an APK to extract the hidden flag  
🛠️ Tools Used: Kali Linux • `unzip` • JADX-GUI

We were handed a file: `thermostat.apk`. At first glance, it's just another Android application. But hidden deep inside its codebase is a flag — and it’s our job to find it.

---

 ✅ Step 1: Unzipping the APK — Getting to the Core
I fired up Kali Linux, the go-to OS for penetration testers, and used the terminal to unzip the APK using:
```bash
unzip thermostat.apk
```
This simple command exposed the internal architecture of the app — `.dex` files (compiled bytecode for Android), `AndroidManifest.xml` (the app's blueprint), and various resource directories.

These files are goldmines for any reverse engineer. If you know where to look, they can tell you everything from how the app functions to what secrets it might be hiding.

---

 👁️ Step 2: Static Code Analysis with JADX-GUI
Next, I loaded the APK into JADX-GUI, a powerful decompiler that converts `.dex` files into readable Java code. Unlike Android Studio (which is great for app development), JADX is built for speed and clarity — perfect for static analysis.

As the app loaded in JADX, I began browsing through the decompiled packages, looking for anything suspicious, unusual, or just plain interesting.

---

 🔎 Step 3: Hunting the Payload — Deep Dive into Code
After scanning through some auto-generated boilerplate code, I arrived at a curious directory: `com.hacker101`. The name itself hinted at the CTF roots, so I focused my energy there.

Inside this package, I discovered a file named `PayloadRequest.java`. That name screamed "flag carrier" — and I wasn't wrong. After reading through the class logic, I noticed a hardcoded string embedded directly in one of the functions.

```java
public String getFlag() {
    return "FLAG{reverse_engineering_ftw}";
}
```
And there it was — the flag hidden in plain sight!

---

 🚀 Step 4: Mission Accomplished — Lessons Learned
Finding the flag is exciting, but the real reward is what you learn in the process:

- 🔍 Static analysis is often enough. You don’t always need to run the app or hook into processes.
- 🛠️ JADX-GUI gives incredible visibility into app logic. If you're into Android security, it's a must-have.
- 🧠 Think like a developer: If you were hiding a flag, where would you put it?

---

 💡 Key Takeaways
- Reverse engineering isn't just about breaking stuff — it's about understanding design, spotting patterns, and peeling back layers of abstraction.
- Tools like JADX-GUI, paired with basic Linux commands, are incredibly powerful when used effectively.
- CTFs are more than just games. They're hands-on simulations of real-world bug bounty and malware analysis scenarios.

---

 📝 Final Thoughts
The H1 Thermostat CTF was a short, sweet, and deeply satisfying exercise in Android app analysis. It reminded me how valuable it is to keep practicing, stay curious, and dig deeper — even when things seem simple on the surface.

If you're new to reverse engineering or CTFs, don't hesitate. Start with APK challenges. Explore, break, learn, repeat.

Stay curious, stay persistent, and happy hacking!  
— Divyanshu

