# :game_die: Ctflearn Dont Bump Your Head Er Walkthrough Bad20C66B96C

> **Original Source:** [Ctflearn Dont Bump Your Head Er Walkthrough Bad20C66B96C](https://infosecwriteups.com/ctflearn-dont-bump-your-head-er-walkthrough-bad20c66b96c)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Launched Burp Suite and captured the request through my proxy, send it to repeater and edit the user agent header to Sup3rS3cr3tAg3nt. Forwarded the request and this was the response.


The message “Sorry it seems as if you did not come from this site awesomesauce.com” suggests that the website is using Referrer Validation to make sure the request is coming from the expected domain. This is likely a referrer header check.

>

this link will help you learn more about http headers: [https://curl.se/docs/httpscripting.html](https://curl.se/docs/httpscripting.html)


Let’s add the referrer header manually and set the value to “awesomesauce.com”.


Done. Hope this was helpful, Thank you!


[My Linkedin](http://www.linkedin.com/in/qaishammad)

---

*Originally published on [Medium](https://infosecwriteups.com/ctflearn-dont-bump-your-head-er-walkthrough-bad20c66b96c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
