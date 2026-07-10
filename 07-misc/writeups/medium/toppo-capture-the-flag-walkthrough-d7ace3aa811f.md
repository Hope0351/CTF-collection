# :game_die: Vulnhub Machine-Toppo Writeup/Walkthrough | By Md Amiruddin

---

# Vulnhub Machine-Toppo Writeup/Walkthrough | By Md Amiruddin

Difficulty : Easy

Flags: There is one flag

DHCP : Enabled
IP Address : Automatically assigned

For this Toppo machine, I used Virtual Box to run the target machine. Kali Linux is the attacker machine for solving this CTF.

The Toppo OVA file can be downloaded [here](https://www.vulnhub.com/entry/toppo-1,245/).

Footprinting

As you can see the Toppo machine is powered on ad it shows it’s ip as 10.0.2.12. Now before we begin use ifconfig to find the IP address of your attack machine (kali) .

My target has an IP address of 10.0.2.12 and my Kali has an IP address of 10.0.2.5. These addresses to apply to me and my network, yours will probably differ.

We will use the command > netdiscover -i eth0 to discover the Toppo ip address.

We next need to find out what ports and services are available. For this purpose we can do a Nmap scan.

Command used > nmap 192.168.0.31 -p-sV

The scan shows that the target has 4 open ports.

As we can see port 80 is available so, we will open the browser and in the address bar we will type the IP Address and it will show the homepage of the website .

Since Webpage is not showing any useful information. Now it’s Time to break out with Dirb. Dirb will help us to find the directories of the website. DIRB is a Web Content Scanner. It looks for existing (and/or hidden) Web Objects. It basically works by launching a dictionary based attack against a web server and analyzing the responses.

## Get Md Amiruddin’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Command used > dirb [http://10.0.2.12](http://10.0.2.12)

After some time, dirb will show some useful directories and from the results we have got an admin directory which would be our first choice of where to start looking. Just need to copy the URL and place it in the address bar of our browser.

We have found some important notes.txt file in the admin directory. After opening that notes.txt file we found one password {12345ted123} so, we will try to use that password to login with ssh which is running on port 22.

Since we already have a password with a name in it and the target is running SSH and a possible username and password combination will be as follows ssh [[email protected]](https://cyberintelligencesolution.com/cdn-cgi/l/email-protection)

Command used > ssh [[email protected]](https://cyberintelligencesolution.com/cdn-cgi/l/email-protection)

As you can see we got logged in so we will dive deeper to find the required Flag.

Now it’s time to exploit and to root. Let’s see if the OS version is vulnerable.

> *cat /etc/issue*

I have already checked that our target OS Debian 3.16.51–3 is not vulnerable so we try something different to find our root flag.

By using the following command, we can enumerate all binaries having SUID permission.

SUID is a special file permission for executable files which enables other users to run the file with effective permissions of the file owner. Instead of the normal x which represents execute permissions, you will see an s (to indicate SUID) special permission for the user.

Command used > find / -perm -u=s -type f 2>/dev/null

We have found python2.7 binaries so, we are going to exploit it.

By using Python 2.7, we can gain root access and we will find the root flag using the following commands:

Command used > python2.7 -c ‘import pty;pty.spawn(“/bin/sh”)’

As you can see we have found our root flag in the root directory.This CTF is of beginner level or easy but it is fun doing it.

---
