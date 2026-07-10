# :globe_with_meridians: XSS Bug Hunting Journey on Paytm Explained

> **Original Source:** [XSS Bug Hunting Journey on Paytm Explained](https://infosecwriteups.com/the-hidden-xss-a-bug-hidden-in-the-mist-907d6cc55322)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# The Hidden XSS: A Bug Hidden in the Mist


[Free Article Link](https://ghostman01.medium.com/907d6cc55322?sk=4937abefb609dd3115a12bb7ac034b1d)👈


Hey fellow Bug Hunters and Security Researchers!
As the title suggests, this is the tale of an XSS vulnerability — hidden in the mist. So, let’s dive right in.


## 🔍 Starting the Hunt


In November 2024, I was testing my most loved payment app website. At that time, I was still a noob (to be honest, I still feel like one 😅). I had no idea where to begin, so I used `subfinder` to collect all the subdomains of target— a classic move.


I opened each subdomain in Firefox, one after another, and many hours later… I realized I was right back where I started. Literally position = 0 😂
Frustrating as hell. All I had done was open hundreds of tabs with nothing to show for it.

## 🕳️ Digging Deeper with WaybackURLs


The next day, I decided to take a different approach. I used `waybackurls` (thanks Tomnomnom 🙌) to collect historical data for target. Within 10 minutes, I had a mountain of URLs — most of them leading to files like `.png`, `.jpg`, `.woff`, etc. Basically, useless for my purpose.


And once again, I was stuck. So many files — but what exactly was I looking for?

## 👻 Building GhostFilter

---

*Originally published on [Medium](https://infosecwriteups.com/the-hidden-xss-a-bug-hidden-in-the-mist-907d6cc55322). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
