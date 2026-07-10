# :globe_with_meridians: Part 1 Of Abusing Envoy Kubernetes Staging Servers Verb Tampering To Achieve Xss

> **Original Source:** [Part 1 Of Abusing Envoy Kubernetes Staging Servers Verb Tampering To Achieve Xss](https://infosecwriteups.com/part-1-of-abusing-envoy-kubernetes-staging-servers-verb-tampering-to-achieve-xss-idors-and-8f4620c035b2)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

- Fuzz subdomain VHOSTS via`FFUF`

- `PureDNS` for direct DNS enumeration.

- I also went through passive collection of subdomains by using tools such as `subfinder` and google dorking (`site:Sister-REDACTED.com` ).

- Looked for related sister sites via:


- `FOFA`

- `SHODAN` (Via Favicon hash search)

- Fuzzing `TLD` via PureDNS (ex: REDACTED`.FUZZ` )


5. Scanning ports via `Masscan` & `RustScan`


- I stopped over-relying on one tool and lowered the maximum packet rate as it typically leads to inconsistent results.


6. Scrape endpoints from `GAU` , `WayBackURLS` , `Dorking`


- When dorking I use the [URL Extractor](https://chromewebstore.google.com/detail/ggiihlkbikggfknjgbocmogobagckdpc?utm_source=item-share-cb) extension to parse all the URLs from google searches as I dork.


7. Exposed secrets by searching target-specific keywords on `Github` , `PostMan` , etc.

### Subdomain Analysis


After cleaning up and collecting the list I realized there weren’t many subdomains this company offered. However there were two that stuck out to me the most:


- `staging.Sister-REDACTED.com`

- `testing-ignore.Sister-REDACTED.com`


The `testing-ignore` subdomain was inaccessible and had no digital footprint as to what its purpose was or how the website looked (was not archived in the Wayback Machine).


I shifted my focus to the staging server, I realized account takeover (ATO) may be possible if I registered an account using an email address that existed in production but not in staging. This would only work if both servers were using the same JWT signing keys. This is a common technique explained more in-depth here: [https://sandh0t.medium.com/the-bad-twin-a-peculiar-case-of-jwt-exploitation-scenario-1efa03e891c0](https://sandh0t.medium.com/the-bad-twin-a-peculiar-case-of-jwt-exploitation-scenario-1efa03e891c0).

### Black Box Reverse Engineering


Unfortunately, when registering a new account there’s an email verification sent-I could not bypass this. But then I caught myself falling into autopilot. I was just following the same checklist everyone runs through.


Why was I even trying to register with someone else’s email on staging in the first place?


Well, I told myself my goal was to obtain a JWT from staging and replay it against production. But I was getting ahead of myself, I didn’t even examine the decoded JWT, what if there wasn’t even an email field at all?


## Get Alimuhammadsecured’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I decoded a JWT from an authenticated login on staging and it looked like this:


*I used the token.dev website when decoding the JWT*

>

Side Note: If you’re a penetration tester make sure to NEVER put a JWT into a public website, regardless of what their claims are.


All decoding or tedious tasks should be done on your own machine, you can use self-hosted services such as [CyberChef](https://github.com/gchq/CyberChef).


Okay… so the JWT does have the email field, but what if the server isn’t even using it. If you look closely you’ll notice the `id` field, what if the server is relying on this over the email field?


I confirmed this by registering multiple accounts on production and noticed it go from `50,612`to `50,613`, `50,614`, etc. For further verification, I logged in, changed my email and noticed my JWT still had my old email address in it even though my account settings displayed my new updated email address.


Okay-that confirms my suspicions, the server isn’t even querying the email claim in the JWT anyway, it’s querying the id claim.


Furthermore, when I did attempt to use the staging JWT on prod it was denied complaining about an invalid signature. Looks like prod and staging used separate signing keys for their JWT tokens.

### Poor Isolation Breakthrough


Before I gave up I clicked around on the staging domain and everything pretty much looked the same-until I went to profile settings and realized it displayed someone else’s email !


So we have ATO? Not quite. If I sent a password reset request I would see my account details and the reset would be done on my own account (within staging).


I decided to poke at the tech stack being used by this company, some common techniques use the [Wappalyzer](https://chromewebstore.google.com/detail/gppongmhjkpfnbhagpmjfkannfbllamg?utm_source=item-share-cb) chrome extension, reading response headers sent back from the web server, and skimming any specific keywords in the JavaScript files.


Turns out this website’s tech stack was using `Kubernetes`, `Nginx`, and `Envoy` proxies!


Why is this important you may be asking...? Well Kubernetes can get very complex and if you’re not careful, especially when isolating the workflows for prod and staging can lead to mixups.


So to understand what may have caused this vulnerability we need to see a simple example of how user requests are handled.


Envoy runs as a config alongside each pod, meaning every request in and out of the cluster passes through it first. It reads the routing rules defined in its sidecar profile and decides where to send the traffic such as to the staging or prod clusters. It’s great for service mesh control, but one bad route and you’re now leaking traffic across environments.

---

*Originally published on [Medium](https://infosecwriteups.com/part-1-of-abusing-envoy-kubernetes-staging-servers-verb-tampering-to-achieve-xss-idors-and-8f4620c035b2). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
