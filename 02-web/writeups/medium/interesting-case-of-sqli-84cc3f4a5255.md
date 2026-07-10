# :globe_with_meridians: Interesting Case Of Sqli 84Cc3F4A5255

> **Original Source:** [Interesting Case Of Sqli 84Cc3F4A5255](https://infosecwriteups.com/interesting-case-of-sqli-84cc3f4a5255)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

Hey everyone, didn’t get time this year to blog about my findings. But this one, I found around 2–3 months back, it was an interesting case and since it's fixed now, I am going to write about it a bit.


I got an interesting case of SQLi on one of Synack program.


Since only unauthenticated testing was allowed, I started with directories and files brute-force, but the applications keep redirecting me to a login page on each directory and file brute and login page redirecting me to portal page, hence creating a loop.


I tried to change the method to see if any a particular method is restricted. But the same result.


Well, next I notice that application is using a third-party solution. I googled it and found its a hosted e-invoicing solution. From here, I thought, let's retrieve the application paths and try brute-forcing again with those.


I checked it to see if I can get a copy of it. No, you can’t, because a demo will be available on request


I didn’t want to waste my time in requesting for a demo version and it’s a tedious process too(fill the form, talking to the sales guy, giving requirements and bla bla). I searched on GitHub etc to see if any demo version of the application is available with credentials, nothing found. I just had a youtube video of application demo on their channel and nothing else. From the video, i was only able to disclose Invoice details of all of their clients and few rxss but my motive was SQLi. From here, i also got to know that redirection only happen in directories under /portal/ which looks like a core part of the application.


## Get Nikhil (niks)’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I decided to check the subdomains of the application to see if I can get any demo version hosted on one of their subdomain itself. I mostly use sub-finder for discovering subdomains, so I run a quick scan of it.


Cool, I got plenty of subdomains that have demo instance running. The good thing is they weren’t even password-protected lol. But that’s a bit strange too because all demo instance doesn’t have authentication and other subdomains which belong to a client was having the same behaviour as I was getting (redirect loop on login). I started wondering, what if there is no authentication at all? and from their demo video on youtube, client’s don’t need to login into the app, some very specific links were generated and sent to their email, by clicking it, they can view all information related to invoicing or even can pay directly for it.


So, I changed my plan, instead of application path, I captured all post requests from demo instances and replaced the domain to in-scope application domain and then replayed it. To my surprise, it worked without a redirect loop.


Cool, next I checked the SQLi on a parameter and as expected it was vulnerable too. I quickly run sqlmap and got access to all data


I reported it and it was accepted within a couple of hours. Synack has a max payout of $3k for SQLi (FYI) if blitz isn’t involved.


Stay Home, Stay Safe, Stay Curious!

---

*Originally published on [Medium](https://infosecwriteups.com/interesting-case-of-sqli-84cc3f4a5255). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
