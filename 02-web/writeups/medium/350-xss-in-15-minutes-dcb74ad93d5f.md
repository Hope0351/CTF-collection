# :globe_with_meridians: $350 XSS in 15 minutes

> **Original Source:** [$350 XSS in 15 minutes](https://infosecwriteups.com/350-xss-in-15-minutes-dcb74ad93d5f)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# $350 XSS in 15 minutes


## Bug Bounty Writeup about DOM XSS via JSONP + Parameter pollution


*Photo by [Pepi Stojanovski](https://unsplash.com/@timbatec?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*


Hello 👋


This is my first and last Bug Bounty Writeup this year. 😀


I am sharing with you my latest XSS finding, which I’ve found 2 weeks ago.


This was the fastest and a bit unusual flow that I normally do when I search for XSS.


So let’s dive in…


- Company asked me to retest an old XSS report.

- I’ve checked that XSS and confirmed that it was fixed properly.

- The specific endpoint had `name` a param that was vulnerable to Reflected XSS injection.


```
example.com/profile?name=<img+src=1+onerror=alert(1337)>
```


- I’ve started to search for a bypass and used the Search function in Chrome Developer tools to search this endpoint `/profile` in all JS files to check for another vulnerable param, but found another endpoint:


```
example.com/services
```


- The first idea that came to my mind was to put this URL in the google search engine and see if this endpoint was cached somewhere on the google web space with params.

- After the first try, I found a cached endpoint with params on the first page of the results, the endpoint had ID…

---

*Originally published on [Medium](https://infosecwriteups.com/350-xss-in-15-minutes-dcb74ad93d5f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
