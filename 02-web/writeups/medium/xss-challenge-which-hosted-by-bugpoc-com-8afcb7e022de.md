# :globe_with_meridians: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/xss-challenge-which-hosted-by-bugpoc-com-8afcb7e022de)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# XSS Challenge which hosted by bugpoc.com


Hello there,


In this article, I will share how did I get alert on my target. It was [http://dogs.buggywebsite.com/](http://dogs.buggywebsite.com/).


I visited the website and I saw a search bar. I thought xss is there!


I tried to search for something, that’s why wrote “A”. It listed dog breeds that starts with “A”. Response:


Something caught my attention. I couldn’t see any parameter on the URL. Interesting! Then I tried to list the subdomains, maybe I can get more information etc. but I saw it have only two subdomains:


I wanted to check request and response when I search a text. I opened Burp Suite and I put “A” to search box. Request & Response:


It was a normal json response (Content-Type: application/json). If I want to get the alert, it must be text/html! I tried to change the Accept header with text/html (It was application/json).


And Content-Type changed as text/html, successfully. Yay! Next step is getting domain name via alert. I tried a simple payload: <script>alert(document.domain)</script>


And boom, P1! Haha :D. Successfully exploited. I created a poc using [https://bugpoc.com/](https://bugpoc.com/).


Here is the poc code: [https://pastebin.com/7nZvm6Cv](https://pastebin.com/7nZvm6Cv)


I hope you had fun reading this. If you want, you can follow me on my social accounts:


## Get Ali TÜTÜNCÜ’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


[https://twitter.com/alicanact60](https://twitter.com/alicanact60)


Also you can follow [https://bugpoc.com](https://bugpoc.com)’s twitter address:


[https://twitter.com/bugpoc_official](https://twitter.com/bugpoc_official)

---

*Originally published on [Medium](https://infosecwriteups.com/xss-challenge-which-hosted-by-bugpoc-com-8afcb7e022de). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
