## Kitty Kitty Bang Bang

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

We can use `jadx` to decompile the provided apk file.  

```bash
jadx -d ~/LAB/CTFs/NahamCon-2024/mobile/decompiled ~/LAB/CTFs/NahamCon-2024/mobile/com.nahamcon2024.kittykittybangbang.apk
```

From the source code we can see that it is outputting the flag into the log when tapping the screen:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

So I used [this](https://appetize.io/) website, made an account with a 10 minute mail, turned ON the ADB Tunnel:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Then locally, on my kali machine I started `adb logcat` grepping for the flag while clicking in the application to have the cat go bang a bunch of time.

```bash
adb logcat | grep -oE 'flag{.*}'
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After a few taps, we've found the flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`flag{f9028245dd46eedbf9b4f8861d73ae0f}`
