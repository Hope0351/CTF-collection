# :game_die: Vulnhub : Backdoored Writeup

> **Original Source:** [Vulnhub : Backdoored Writeup](https://infosecwriteups.com/vulnhub-backdoored-writeup-032475f760dc)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Vulnhub : Backdoored Writeup


## One of the easiest Vulnhub machines


If the machine has issues with getting an IP follow this guide I made to solve it: How To Solve Vulnhub VM Network Interface IP Issues.

### Reconnaissance


Find the machine IP in your local network with `netdiscover`:


```
sudo netdiscover
```


*TP-LINK TECHNOLOGIES* is my WiFi NIC adapter on my Windows machine in another room, where also the Backdoored VM is installed. The ip is 192.168.1.6.


Let’s launch nmap, we’re in a home local network, let’s blast the machine with an aggressive scan:


```
sudo nmap -T5 -A -sS -p- 192.168.1.6
```


It found a web server on port 1337.


Visit the web page at http://192.168.1.6:1337 and we’re presented with a welcome web page:


We see just some details on the box. Let’s dirbust the web server and see what we can find, I’m using dirbuster…

---

*Originally published on [Medium](https://infosecwriteups.com/vulnhub-backdoored-writeup-032475f760dc). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
