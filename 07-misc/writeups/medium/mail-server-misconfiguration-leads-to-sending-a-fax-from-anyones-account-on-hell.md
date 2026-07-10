# :game_die: Mail Server Misconfiguration leads to sending a fax from anyone’s account on HelloFax (Dropbox BBP) for a bounty of $4,913

> **Original Source:** [Mail Server Misconfiguration leads to sending a fax from anyone’s account on HelloFax (Dropbox BBP) for a bounty of $4,913](https://infosecwriteups.com/mail-server-misconfiguration-leads-to-sending-a-fax-from-anyones-account-on-hellofax-dropbox-bbp-aab3d97ab4e7)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Mail Server Misconfiguration leads to sending a fax from anyone’s account on HelloFax (Dropbox BBP) for a bounty of $4,913


Hi Everyone!,


Hope you all are doing well :)


This article is about my recent finding of a mail server misconfiguration among multiple targets that allowed me to perform unauthorized actions on vulnerable web applications, This vulnerability is common among multiple targets and different types of web applications. Dropbox fixed the issue and awarded me a bug bounty of $4,913.

### Description


I was working on the HelloFax application at [Dropbox BBP](https://hackerone.com/dropbox?type=team) and looking for auth issues but the application is well sanitized against authorization issues such as IDOR and Access Control so I thought to look for more interesting functionalities, I found a functionality that allows users to [send a fax using their email](https://faq.hellosign.com/hc/en-us/articles/215338277-How-to-send-a-fax-through-email) without logging into their HelloFax account


So , when a paid user sends an email to *FAXNUMBER@hellofax.com*, the application sends the content of the email as a fax to FAXNUMBER from the user’s HelloFax account, For eg. If I send an email *13456789000@hellofax.com*, then the application sends a fax to +13456789000 from my HelloFax account

### Exploitation


Here the first thing that came to my mind was to send a fake email to *FAXNUMBER@hellofax.com* by putting the victim’s email into FROM field, I quickly went to [http://anonymailer.net/](http://anonymailer.net/) and sent a fake email to *+12345678900@hellofax.com*, Surprisingly it worked well and I received this mail from HelloFax


This email says that our fax has been sent successfully and the mail server at Hellofax did not verify the authenticity of the fake email sent by me and it sent the email from the victim’s account


## Get Sayaan Alam’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Here is how the vulnerability works:-


- Target allows us to perform an action by sending an email to email@target.com

- An attacker sends a fake email to email@target.com by putting the victim’s email in FROM field

- The target server receives the email and does not verify its authenticity and considers it as a legit email sent from a user

- Application processes the email and performs action from the victim’s account and leads to authorization bypass


I reported the bug immediately to Dropbox BBP on Hackerone and it got triaged the next day but the team downgraded the severity to High stating the following reason

*Team Comment on Hackerone*


Though they paid me a bounty of $4913 on High category as per their policy


Other Exploitation Scenarios


- I found the same vulnerability on a bug reporting portal that allowed me to create bug tickets from the victim’s account by sending an email to *bugs@redacted.com*

- This bug could be found on applications that are using their own support panels and we can create tickets there on behalf of the internal team or any other user

- Any other kind of application that performs actions or creates tickets/bugs by sending email to them


The root cause of this vulnerability is that the target server does not verify SPF records, Email clients configured to use SPF and DMARC will automatically reject emails that fail validation and this should be applied to applications to prevent this vulnerability


Timeline


16-Dec-2021 — Reported bug to [Dropbox BBP](https://hackerone.com/dropbox) on Hackerone


17-Dec-2021 — Bug Triaged by Hackerone Triage Team


31-Dec-2021 — $4913 Bounty awarded by Dropbox Team


17-March-2022 — Dropbox Team fixed the issue


02-May-2022 — Report closed as resolved


Thanks for reading this, If you have any queries, feel free to reach me on Twitter at [@ehsayaan](https://twitter.com/ehsayaan) or *ehsayaan@gmail.com*


Special thanks to [Sam Curry](https://twitter.com/samwcyo) for proofreading this writeup


Until next time!


[Sayaan Alam](https://sayn.in)

---

*Originally published on [Medium](https://infosecwriteups.com/mail-server-misconfiguration-leads-to-sending-a-fax-from-anyones-account-on-hellofax-dropbox-bbp-aab3d97ab4e7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
