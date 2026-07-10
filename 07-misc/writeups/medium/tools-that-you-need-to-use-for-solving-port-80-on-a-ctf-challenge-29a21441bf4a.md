# :game_die: Tools you need to use for solving CTF challenges-Port 80.

---

# Tools you need to use for solving CTF challenges-Port 80.

Port 80 is a common service present in the CTF challenges. It is also my favorite one among other services as you would surely find something useful in it. If you encounter port 80 or 433, then here are the basic tools with steps that you should work on.

## Nmap

If you are reading this post, then you would already know about Nmap. Nmap is a Network Scanner tool that finds the hosts and services on a network by sending requests and analyzing the response.

Nmap is the first tool that I use on a CTF challenge. I just use the IP address of the CTF with no options on nmap to see what ports are open. If port 80 is opened, then you should further use nmap with specific options to get more information about it. Here’s what I do,

>

nmap -p80 — script=vuln -sV -A IP

In the above command, the -sV option will give you the version of the service running on port 80 while the — script=vuln option will check for common vulnerabilities on port 80. The -A option will list the OS type along with some other useful information.

To be fair, you will not solve the challenge with the help of this tool only. But it will give you an idea about the software, version number, and more useful information in solving the challenge further down the road.

---
