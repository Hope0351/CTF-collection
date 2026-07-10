# :globe_with_meridians: HOW I FOUND MY FIRST XSS BUG. Introduction:

> **Original Source:** [HOW I FOUND MY FIRST XSS BUG. Introduction:](https://infosecwriteups.com/how-i-found-my-first-xss-bug-553225548d29)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# HOW I FOUND MY FIRST XSS BUG


## Introduction:


Let’s start with how I found my first love… oh wait, Zero, snap out of it — you’re daydreaming again! Right, back to reality. Sorry, I meant to say, how I found my first XSS! Fellow hackers, buckle up because this is a story packed with curiosity, chaos, and that unforgettable adrenaline rush when a simple pop-up alert feels like winning a boss fight. If you’re just starting your hacking journey, don’t sweat it — XSS is a beginner-friendly challenge, and I’m here to walk you through how I tackled mine. Let’s dive in!

## How I Found It


It all started with a classic Google Dork:

>

site:radicated.com


After scrolling through a few pages, I thought, *let’s refine this a bit*. So, I switched it up:

>

site:radicated.*


Still not quite there, I decided to get clever and filter out unnecessary subdomains:

>

site:radicated.* -www -blog


This nifty trick removes the www and blog subdomain pages, making the search results much cleaner. That’s when I stumbled upon a webpage with a comment functionality.


## Get jirosec’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Immediately, the thought of XSS popped into my head like a lightbulb in a cartoon.


I grabbed a simple payload and threw it into the comment box:

>

“><img src=x onerror=alert(‘xss’)>


To my surprise, the XSS was stored, and it worked! I couldn’t believe my luck. I was just testing, thinking the input would be sanitized. But nope — no sanitization. *Boom*, it worked like a charm.


For a brief moment, I felt like the king of the world. But then, reality hit me, and I remembered all the cautionary tales of irresponsible hacking. My soaring confidence quickly came back down to earth. I decided to do the right thing — I wrote up a detailed report and submitted it to the company.


## Connect With Me:


If you enjoyed this write-up and want to stay connected, feel free to follow me on [LinkedIn](https://www.linkedin.com/in/ranjan-yadav-82b28b249/)and [X (formerly Twitter)](https://x.com/ig_ftw). Let’s grow and learn together — happy hacking! 🎯

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-found-my-first-xss-bug-553225548d29). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
