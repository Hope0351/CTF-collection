# :game_die: Vulnhub : BBS (Cute) 1.0.2 Writeup

> **Original Source:** [Vulnhub : BBS (Cute) 1.0.2 Writeup](https://infosecwriteups.com/vulnhub-bbs-cute-1-0-2-writeup-bbb675a4b9dc)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Vulnhub : BBS (Cute) 1.0.2 Writeup


## A beginner-friendly box with some exploit modding needed


## Reconnaissance


Get the machine ip:


```
sudo netdiscover
```


On this version of netdiscover Virtualbox VMs have *TP-LINK TECHNOLOGIES* as the name, which is the name of the WiFi NIC on my home computer.


The Cute 1.0.2 ip is 192.168.1.12:


It’s a machine on the local home network, so we can launch an aggressive nmap scan against all ports:


```
sudo nmap -T5 -A -sS -p- 192.168.1.12
```


On port 80 we have the usual Apache2 Default page:


On port 88 a 404 not found page is returned:


Then we have the usuall ssh service on port 22 and some email server related services on ports 110…

---

*Originally published on [Medium](https://infosecwriteups.com/vulnhub-bbs-cute-1-0-2-writeup-bbb675a4b9dc). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
