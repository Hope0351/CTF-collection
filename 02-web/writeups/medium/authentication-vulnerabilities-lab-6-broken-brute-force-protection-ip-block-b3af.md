# :globe_with_meridians: Authentication Vulnerabilities Lab 6 Broken Brute Force Protection Ip Block B3Af

> **Original Source:** [Authentication Vulnerabilities Lab 6 Broken Brute Force Protection Ip Block B3Af](https://infosecwriteups.com/authentication-vulnerabilities-lab-6-broken-brute-force-protection-ip-block-b3afca0a2ea7)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

How can we create correct attempt after certain incorrect incorrect attempt


The answer is : we can create a macro in burpsuite.
macro will create a correct attempt after certain brute force attempt.


Lets get started


Click on `proxy setting`


Then click on `sessions` and click `add`


Then click on `add` and `Run a macro`


Then select request with status code `302` : because this is the request where the login attempt is correct.


Then click `OK`


Then click `OK`


Then go to scope option


Select `Include all URLs` and click `ok`


## Get dollarboysushil’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Then send the request from repeater to `Intruder` `ctrl + I`


In intruder, set username `carlos` and set payload position on password field
make sure attack type is `sniper`


In payload option.
- set payload option `1`
- payload type `Simple list`
- and `paste` the password list ; password list is provided in lab


Then go to `Resource pool`
- select `create a new resource pool`
- set maximum concurrent requests : `1`


Then `start attack`


And we can see, after multiple tries , the is no brute force blockage


Looking at the status code, we can see we got `302` status code. Which is the required password.


Lets try to login and check if it is correct:


ANd solved.

---

*Originally published on [Medium](https://infosecwriteups.com/authentication-vulnerabilities-lab-6-broken-brute-force-protection-ip-block-b3afca0a2ea7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
