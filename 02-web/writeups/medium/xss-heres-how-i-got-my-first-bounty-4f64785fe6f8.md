# :globe_with_meridians: XSS | Here’s How I Got My First Bounty

> **Original Source:** [XSS | Here’s How I Got My First Bounty](https://infosecwriteups.com/xss-heres-how-i-got-my-first-bounty-4f64785fe6f8)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# XSS | Here’s How I Got My First Bounty


Not so long ago, I was reading blogs like this, wondering how to find my first vulnerability in a bug bounty program and probably not thinking that I would get a bounty a little after.


But here we are, having made the decision to revisit a target that seemed initially too big to me as I was only a beginner, I found a reflected XSS vulnerability.


Was it hard to find? Not really. Did I get lucky? Maybe.


My main goal was to find an XSS, so I was searching for user inputs. I started testing the search bar by entering a random string in order to observe the behavior of the web app. Looking at the response in the Browser DevTools, I saw that my double quotes were not filtered, and I found a tag which looked like this :


So, I started trying to bypass it with a double quote in order to close the attribute :


It works, perfect.
Now, let’s exploit this vulnerability to get an XSS. The tag here is a div, so we can use the payload “onpointerover=”alert(‘XSS’)” in a way that the tag looks like this :


Yay, here’s our popup !


I was awarded with a $75 bounty for this one. Not a lot for a medium severity, but it brings motivation especially because it confirms to me that it’s still possible to find XSS vulnerabilities in bug bounty programs with over a hundred vulnerabilities already reported.


That’s it,


I really hope you enjoyed this blog and see you for a next one !

---

*Originally published on [Medium](https://infosecwriteups.com/xss-heres-how-i-got-my-first-bounty-4f64785fe6f8). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
