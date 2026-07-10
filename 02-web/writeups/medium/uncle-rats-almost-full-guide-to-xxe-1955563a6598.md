# :globe_with_meridians: Uncle Rat’s (Almost) Full Guide To XXE

> **Original Source:** [Uncle Rat’s (Almost) Full Guide To XXE](https://infosecwriteups.com/uncle-rats-almost-full-guide-to-xxe-1955563a6598)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Uncle Rat’s (Almost) Full Guide To XXE


## Introduction


XXE is one of my favourite attack types because it’s usually hidden below a surface level concealment. We all know that almost nobody uses XML files anymore these days as JSON has taken over and even YAML. Yet the fact XXE appears in the OWASP top 10 of 2017 does say something about this vulnerability type.


Today we are going to look at all the possible attack vectors that we can think of, both from the perspective of a pentester and of a bug bounty hunter. Defending your application against XXE attacks is not simple either so i hope this will give anyone building a web application some ideas as to how to protect their application better.

## Blind XXE


Before we start talking about XXE, we need to talk about the blind aspect of XXE attacks. Whether you are a pentester, bug bounty hunter or ethical hacker in general, it’s always a good idea to look for blind XXE over normal XXE. This will ensure that you will not miss any entry points as sometimes we might be testing for XXE and think an endpoint is not vulnerable because we do not see any data being returned while in all actuallity the endpoint might be vulnerable to blind XXE.


Blind XXE means that you are performing a succesfull attack but that you are not seeing any output from the server. This means that in order to confirm whether or not our attack was successful, we need to make a request to an external server. I usually use the burp collaborator to test for this…

---

*Originally published on [Medium](https://infosecwriteups.com/uncle-rats-almost-full-guide-to-xxe-1955563a6598). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
