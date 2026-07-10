# :game_die: Hack The Box Keeper A81B5D959C23

> **Original Source:** [Hack The Box Keeper A81B5D959C23](https://infosecwriteups.com/hack-the-box-keeper-a81b5d959c23)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Author — [Satyam Pathania](https://www.linkedin.com/in/satyam-pathania/)


Hello cybersecurity enthusiast! This machine could be easy for many but not for all so Let’s Begin!


for non-medium partners check the free article here : [click me](https://medium.com/bugbountywriteup/hack-the-box-keeper-a81b5d959c23?sk=14c6c59ed89d5427b5c21a2dc56036f0)

## Enumeration


Given a target host IP, let’s perform port scanning with one of the most powerful tools, Nmap.


```
nmap -sV -sC -vv 10.10.11.227
```


As we found after scanning, On port 80 (HTTP) and port 20 (TCP), we are immediately pointed to two domain names:


- keeper.htb

- tickets.keeper.htb


Let’s add it in the /etc/hosts file system


Now, We were unable to locate any credentials within the page’s source code. Therefore, we can attempt a couple of default login credentials or explore the internet for the default credentials associated with Request Tracker.


## Get Satyam Pathania’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


It appears that the default login credentials for this tool are ‘*root:password*,’ so we can attempt using those and check if we can gain entry to the portal.

## Initial Access to Request Tracker Dashboard


After some exploration, discovered a ‘Users’ tab within the ‘Admin’ section. Within this tab, we noticed the presence of another user named lnorgaard. Since we have root-level access to the portal


What captures our attention the most is the comment section, where we can readily observe the plain-text password for this user. With this matching set of username and password in our possession, we can attempt to utilize them for the purpose of acquiring SSH access to the machine.


If you enjoyed this guide or have any questions, feel free to reach out. Keep hacking, and see you on the next machine!


— [Satyam Pathania](https://www.linkedin.com/in/satyam-pathania/)

---

*Originally published on [Medium](https://infosecwriteups.com/hack-the-box-keeper-a81b5d959c23). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
