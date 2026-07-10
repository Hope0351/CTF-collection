# :globe_with_meridians: IW Weekly #13: 1000s of user tokens exposed, pre-auth RCEs in Oracle, AWS Misconfigurations, IDOR, Open redirects, Nmap tutorial, and much more.

---

# IW Weekly #13: 1000s of user tokens exposed, pre-auth RCEs in Oracle, AWS Misconfigurations, IDOR, Open redirects, Nmap tutorial, and much more.

Hey 👋

Welcome to the thirteenth edition of **Infosec Weekly** — the Monday newsletter that brings the best in Infosec straight to your inbox.

The Infosec world is continuously evolving with newer finds and features coming up every single day. Not able to catch up with the changes? Don’t worry. In today’s edition, we’ve curated all the amazing Infosec stuff that needs your attention, in a format of 5 articles, 4 Threads, 3 videos, 2 Github repos and tools, and 1 job alert, to help you maximize the benefit from this newsletter and take a massive jump ahead in your career.

Sounds interesting? Let’s dive in👇

**📝 5 Infosec Articles#1 **[Team Nautilus at Aquasec](https://twitter.com/AquaSecTeam)** found **[tens of thousands of user tokens exposed via the Travis CI API](https://blog.aquasec.com/travis-ci-security)**, which allows anyone to access historical clear-text logs.#2 An article by **[Slowmist](https://slowmist.medium.com/)** describes **how a White hat group, United Global Whitehat Security Team(UGWST) was able to discover the browser extension-only vulnerability** which allowed attackers to deceive users into sending crypto-assets without them realizing it.#3 **[Peterjson](https://peterjson.medium.com/)** & **[Jang](https://testbnull.medium.com/)** ended up with multiple pre-auth RCEs in many products inside Oracle Middleware.**Read more about this cool exploit story here**.#4 **[Dhiyaneshwaran](https://dhiyaneshgeek.github.io/)** shared a **[detailed blog on various scenarios for AWS Misconfigurations starting from basics](https://dhiyaneshgeek.github.io/cloud/security/2022/06/23/aws-misconfigurations/)**.#5 Portswigger has improved the DOM invader tool to make finding C-SPP (client-side prototype pollution) as easy as a couple of clicks.**[Read about it here](https://portswigger.net/blog/finding-client-side-prototype-pollution-with-dom-invader)**.🧵4 Trending Threads#1 **[@LazySaad](https://twitter.com/LazySaad)** explained **[how to find IDORs and how we can use user_id to verify if the IDOR exists or not](https://twitter.com/LazySaad/status/1538664657749266433?s=20&t=FDeNgK3zKzJ4EhiTU8H3Pg)**.#2 **[@tabaahi_](https://twitter.com/tabaahi_)** explains how beginners can look for open redirects, what tools to use, how to go about finding them and where one should report open redirects. **[Check it out here. It’s a great starting point for newbies in Infosec](https://twitter.com/tabaahi_/status/1539159408026218496?t=mF-ote2xiy0kFuvVgHjwTA&s=19)**.#3 A great thread from **[Hossein NafisiAsl](https://twitter.com/MeAsHacker_HNA)** where he explains **[how an HTTP Request smuggling turns into mass account takeover and shares a great GitHub repository where he collected amazing write-ups & tips](https://twitter.com/MeAsHacker_HNA/status/1538862575617814528?t=YitdeDYSt2_fdJTWiK_qmA&s=19)**.#4 **[@hakluke](https://twitter.com/hakluke)**’s “**[Become an Nmap pro in 30 seconds Thread](https://twitter.com/hakluke/status/1539962767901618176?t=2j3vJ9bWBKACz26tUAeLyw&s=19)**” shows an amazing full tutorial for Nmap where he has shared all about the Nmap features you don’t want to miss.📽️ 3 Insightful Videos**

## Get InfoSec Write-ups’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

**#1 **[Rana Khalil](https://www.youtube.com/c/ranakhalil101)**’s next video is out for the 2nd lab of command injection module by the Web Security Academy, **[where she used both manual and automated approach using python to solve the same](https://youtu.be/KbWn4L2dcHU)**.#2 A great video from **[Patrick Collins](https://www.youtube.com/c/patrickcollins)** about auditing smart contracts, where **[he explained the audit process, the basics of how to conduct one, and how to interact with auditors](https://youtu.be/TmZ8gH-toX0)**.#3 **[Laluka](https://twitter.com/TheLaluka)** has gathered lots of RCEs that wander in nature and has decided to present at the conference as a part of the HitchHack produced by Laluka. **[Watch the video here](https://youtu.be/Z9GN6cuggYQ)**.⚒️2 Github repositories & Tools#1 **[Xnl-h4ck3r](https://twitter.com/xnl_h4ck3r)** has **[launched their python tool named xnLinkFinder similar to their Burp extension called GAP](https://github.com/xnl-h4ck3r/xnLinkFinder)**. It helps to discover endpoints for a given target using the Regex. Similar but advanced to a tool named **[LinkFinder](https://github.com/GerbenJavado/LinkFinder)**.#2 A very detailed Ethereum smart contract auditor roadmap shared by **[Razzorsec](https://github.com/razzorsec)** on their github repo. **[Find it here](https://github.com/razzorsec/AuditorsRoadmap)**.💰1 Job alert ⚠️#1 **[A great Internship opportunity by Cybertix](https://www.linkedin.com/posts/cybertix_internshipopportunity-internship-opportunity-activity-6944913323654033408-FuzK?utm_source=linkedin_share&utm_medium=android_app)** for everyone who wants professional experience and wants to upskill themselves.Last date to apply for Internship: 15th July 2022**

That’s all for this week. Hope you enjoyed these incredible finds and learned something new from today’s newsletter.

**Before we say bye…**

If you found this newsletter interesting, and know other people who would too, we’d really appreciate if you could forward it to them 📨

If you have questions, comments, or feedback, just reply to this email or let us know on Twitter [@InfoSecComm](https://twitter.com/InfoSecComm).

See you again next week.

Lots of love

Editorial team,

[Infosec Writeups](https://infosecwriteups.com/)

*This newsletter has been created in collaboration with our amazing ambassadors.*

*Resource contribution by: ***[Nithin R](https://twitter.com/thebinarybot)* (***[thebotsite.me](https://www.thebotsite.me/)*), ***[Ayush Singh](https://twitter.com/AyushSingh1098), **[Vinay Kumar](https://twitter.com/R007_BR34K3R)*, ***[Hardik Singh](https://twitter.com/Kxddah?t=_Ghby7u5rNBfUxzzjEZUUw&s=09)*, ***[Bimal K. Sahoo](https://twitter.com/sr_b1mal)*, ***[Mohit Khemchandani](https://twitter.com/mohitkchandani)* and ***[Pramod Kumar Pradhan](https://twitter.com/NinjaFurry5)*.*

*Newsletter formatting by: ***[Nithin R](https://twitter.com/thebinarybot), **[Bhavya Jain](https://twitter.com/bhavyajain_30), **[Vinay Kumar](https://twitter.com/R007_BR34K3R)* and ***[Siddharth](https://twitter.com/illucist_)*.*

*If you wish to join our Ambassadors channel and contribute to the newsletter, reply to this email with your discord username.*

---
