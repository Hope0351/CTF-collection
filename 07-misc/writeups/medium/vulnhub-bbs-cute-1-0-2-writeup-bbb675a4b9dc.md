# :game_die: Vulnhub : BBS (Cute) 1.0.2 Writeup

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
