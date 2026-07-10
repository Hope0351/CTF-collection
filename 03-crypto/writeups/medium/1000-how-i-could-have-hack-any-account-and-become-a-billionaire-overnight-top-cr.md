# :locked_with_key: $1000: How I could have Hack any account and become a billionaire overnight👑Top Crypto-Trading Platform

---

After several emails with the security team [ which also includes depression & demotivation] and the HITCON team, the company rewarded me with a bounty of $1000 which is usually higher than the bounty mentioned on their Bug-Bounty page.

* Introduction *

Hello Infosec people, This is Gowtham, 17y/o Security Researcher from India who loves to dive deep into technologies all the time😁😅. and also from my blogs, you also knew that I am not being consistent in writing blogs🙃 But let me tell you😙This blog make you stick until the end.

Talking about the platform, It is a Top Crypto-trading platform where we can buy, sell or transfer cryptocurrencies. According to the non-disclosure policy, I cannot leak any private information so, let’s say the domain name is “Redacted.com”.

>

*This grabs my attention as usual😅*

If you read my previous blogs, I usually look into Login/Signup Functionalities and I did the same thing here. I turned on my BurpSuite to capture all the requests & responses and signed up on the website and went through every functionality. After spending a some good amount of time understanding the platform, I wore my hackersuit [Just Kidding🙃]. I started looking into IDOR Vulnerabilities but had no luck :(, tried XSS on Username fields but still the same result And Now, I actually started looking into my favourite spot.

>

Bookmarks will help you, Believe Me:

I logged out of my account and started looking into Forgot-Password End-point. I had my eyes on JS files which can reveal some important information sometimes but there is nothing interesting at this point in time. So I entered my registered email on the Forgot-Password field and click on send, And guess what? It asks for 6-digit OTP😙.

And the First thing that comes into my mind is “Bruteforce, Bruteforce, Bruteforce…….😂”. And I entered a Wrong OTP in the browser and captured that request in Burp, Looking into the response, it says “4 More Attempts Left”😶. I am like ~

And then I sent the request to Repeater and sent it multiple times and got eventually ended with the response saying, “Your Account is blocked, Wait for 2hours”.

Here, I tried multiple methods like X-Forwarded-For: <IP> and many more but nothing works out!. Then I remember from my Bookmarks on my browser, Someone bypassed Rate-Limiting by changing the IP Address. And I turned on my free VPN service, so-called “ProtonVPN”😙 and connected to the free server and I sent the request and got ended with a response saying, “4 More Attempts Left”. Next Moment,

I thought of reporting it here but I stopped😶. What’s the impact though? Just bypassing the rate limit is not a great thing and in order to get correct OTP, we need to have 2,00,000 IPs which costs some good amount of money😂 so I gave up on this.

>

Google it, Until you find it🔥

While I am in college, I got to remember “Race-Condition” vulnerability during my Math class😅 so immediately after reaching home, I revisited the program and tested the request with the “modified race.py” script [ default script from Turbo-Intruder within Burp ].

What is Race-Condition though? “*A race condition is a flaw that produces an unexpected result when the timing of actions impacts other actions. An example may be seen on a multi-threaded application where actions are being performed on the same data.” In simple terms, sending multiple requests in a fraction of time to trick the server.*

Now, After looking into all the responses from Turbo-Intruder, I was the happiest person at the moment and excited at the same moment. I was able to send almost 200 requests without hitting the rate limit🔥.

>

Report Writing pays off

By Using this vulnerability, An Attacker can able to brute-force any 6 digit OTP by having 5000 IPs [which costs around $150-$250 ] and can get into any user account, and can able to transfer the funds into his own wallet address. This is a severe rated-vulnerability and some top companies like Instagram and Microsoft paid $30000 and $50000 respectively.

## Get Gowtham_Naidu’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

[ Note ]: The Full POC is not possible as it needs a lot of computing resources and IPs in order to show the actual vulnerability and that’s the only reason why the severity changes from Severe to High.

I immediately recorded the POC[Proof-Of-Concept] and started writing down the report. It took me one hour to write a detailed report with supporting evidence. And then the story continues in the timeline:

- Report Sent: 11th March, 2022

- First Response: 16th March, 2022 [Their Support Team said, Security team is verifying the Vulnerability I reported.]

- Second Response: 23rd March, 2022 [Still said the same thing but they are so trustworthy.]

- Triage: 29th March, 2022 [Team validated the vulnerability and awarded me with an bounty of $50 😶 I was literally in shock, I was expecting more.]

- Discussions with Security and HITCON Team: 29th March, 2022–31st March, 2022 [They are very responsive and explained the root causes along with impacts. ]

- Third Response: 31st March, 2022 [ I got awarded a Bounty of $1000 which is higher than the bounty stated on their Bug-Bounty page, and got an appreciation for my efforts and patience.]

- Fixed the Vulnerability and Resting: 1st April, 2022 [ I confirmed that the vulnerability doesn’t exist anymore and gave some security measures aka tips.]

- Received Bounty: 6th April, 2022 [ I received the bounty via LTC, I was so happy to get second crypto bounty😁😭.]

Detailed Reply about the vulnerability from security team

>

It’s all about how you END! aka Gratitude 🙂

I know, this program took more days to fix the vulnerability and pay the bounty but I still love their support and security team for being in touch all the time. I really appreciate their efforts and quick fixes from their security team and special thanks to higher officials who were involved in this.

That’s all for my third blog😁, I hope you enjoyed it and still looking for your suggestions on improving my writing skills. Feedback is always accepted🥰

Follow me on: [These are my Official Accounts ]

Twitter: [https://twitter.com/gowtham_ponnana](https://twitter.com/gowtham_ponnana)

LinkedIn: [https://www.linkedin.com/in/gowtham-ponnana/](https://www.linkedin.com/in/gowtham-ponnana/)

Instagram: [https://www.instagram.com/gowtham_ponnana/](https://www.instagram.com/gowtham_ponnana/)

Discord: MountXLover#3269

Mail: gowtham.official45@gmail.com

---
