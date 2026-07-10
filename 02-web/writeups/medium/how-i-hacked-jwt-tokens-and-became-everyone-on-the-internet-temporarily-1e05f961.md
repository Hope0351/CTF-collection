# :globe_with_meridians: How I Hacked JWT Tokens and Became Everyone on the Internet (Temporarily) 😈

> **Original Source:** [How I Hacked JWT Tokens and Became Everyone on the Internet (Temporarily) 😈](https://infosecwriteups.com/how-i-hacked-jwt-tokens-and-became-everyone-on-the-internet-temporarily-1e05f961048d)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How I Hacked JWT Tokens and Became Everyone on the Internet (Temporarily) 😈


Hey there!😁


Free [Link](https://medium.com/@iski/how-i-hacked-jwt-tokens-and-became-everyone-on-the-internet-temporarily-1e05f961048d?sk=858472fdb5a352604ed70ed49741f426)🎈


*Image by AI*


You know that moment when you find a spare key under someone’s doormat and think “Wow, people actually do this?” Well, I found the digital equivalent last week. Except instead of a physical key, it was JSON Web Tokens, and instead of one house, it was every user’s account on the entire platform. All because someone left the key to the kingdom under a virtual doormat labeled “security.” 🗝️


It all started when I was testing “SocialFlow,” a new social media platform that was getting hype for its “military-grade security.” I had a basic user account and was ready to poke around. Little did I know I was about to become the master of keys…

## Act 1: The Accidental Discovery — Token Troubles 🔍


After my standard recon (I should really make a keyboard shortcut for `subfinder | httpx | gau` by now), I found SocialFlow's API. I created two test accounts and started capturing traffic in Burp.

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-hacked-jwt-tokens-and-became-everyone-on-the-internet-temporarily-1e05f961048d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
