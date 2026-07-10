# :game_die: Code Breaker Challenge 2025 Task 1: Getting Started

> **Original Source:** [Code Breaker Challenge 2025 Task 1: Getting Started](https://infosecwriteups.com/code-breaker-challenge-2025-task-1-getting-started-19f6d3d3a83c)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2025

---

# Code Breaker Challenge 2025 Task 1: Getting Started


Hello everyone and welcome to NSA’s Code Breaker Challenge for 2025! NSA CBC is a yearly event put on by the NSA that is for all intents and purposes a CTF. Challenge topics vary from forensics to reverse engineering and they’re always pretty fun and challenging. Starting off this year it looks like we’re given a disk image that we’ve gotta comb through for something suspicious. So, without further adieu, let’s dive into Code Breaker Challenge 2025.


So to start off here, we’re given a little scenario to get us in the mindset for these challenges as well as a zip file that is has a ext2 disk image inside. Well, seems fairly straight forward so far, let’s go ahead download and mount this image and start looking through it.


Right off the bat we can see that in this directory structure there are a few directories that aren’t default Linux directories. The culprits being /app and /backup, let’s see what’s there.


Nothing huh? Alright, well let’s just start combing through some of these directories and seeing what we can find.


Here you see me running ls -la on pretty much every subdirectory in root here and honestly this file system is not very big. We only have files in /bin /dev /etc /lib /media /root /run /usr and /var. That may sound like a lot, but it could be a lot worse and also a lot of this stuff looks pretty regular. Also a couple other interesting notes.


We have this alpine-release file here, which tells us the is an Alpine Linux box. Another little interesting tidbit.


All of our normal binaries are now linked to busybox. Why are these two things significant? Alpine Linux utilizes Busybox (which is basically a bundle core Linux binaries bundled together) because it is frequently used as the OS for embedded systems. Alpine is super lightweight, and efficient which makes it ideal for use in systems that need to be extremely efficient and don’t have a ton of resources. So this image could be of some kind of IoT device or home router or something. Does that mean anything for us here? Maybe, maybe not we’ll have to keep looking and see.


Anything interesting here in /etc? This would be a good place to drop a malicious file, maybe they placed something in cron for persistence?


Hmmm, /etc/periodic? What’s that?


So [Periodic](https://freebsdfoundation.org/blog/an-introduction-to-freebsds-periodic-system/) is like a FreeBSD implementation of cron huh? Well let’s see what’s in /etc/periodic.


What the heck is that?


Now this looks kinda janky, let’s see if this is the suspicious file.


Bam and that’s Task 1 of CBC 2025!

---

*Originally published on [Medium](https://infosecwriteups.com/code-breaker-challenge-2025-task-1-getting-started-19f6d3d3a83c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
