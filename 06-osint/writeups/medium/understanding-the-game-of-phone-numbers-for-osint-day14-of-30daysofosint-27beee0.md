# :sleuth_or_spy: Understanding the game of phone numbers for OSINT | Day14 of 30DaysOfOSINT

---

# Understanding the game of phone numbers for OSINT | Day14 of 30DaysOfOSINT

The main aim of writing this blog is to get you all familiar with basic information about the phone number and their role in OSINT.

Welcome to day 14 of our #30daysofOSINT series, My apologies for taking vacations for a month, now we will be as active as earlier, so stay tuned and subscribe to our website to not miss any upcoming blogs and get new blogs directly in your inbox.

What is a Phone Number?

A phone number is like your very own address in the world of phones. It’s a set of digits that you can dial to connect with someone else’s phone. Just like how your home has an address to find it, a phone number helps others reach you through your phone. As everyone understood this well, let’s not deep dive into it.

What are the main use cases of Phone Numbers?

Calling and voicemail

- Verification — Sometimes, some website uses phone number as a verification to prevent people from creating fake accounts on their website.

- Banking and Payments — Nowadays, by just knowing the phone number of someone, we can transfer money to them via some payment portals like PayTM, Paypal, and others, without sharing any bank-related information.

- Signups — We use phone numbers for signups on popular websites like Instagram and Twitter. Also, some websites just allow signup using phone numbers only like WhatsApp and Telegram.

What’s the first thing that you should do when you are performing OSINT on a phone number?

In my opinion, the first step should be to check if it’s a virtual number or a real telephonic number(whether it’s a VOIP or non-VOIP number).

*VOIP means Voice Over Internet Protocol*
When we take a SIM card from a cellular network provider like MTN, Arizona, Jio, etc. (When we insert a SIM to use a phone number in our mobile device, it’s a non-VOIP number including virtual SIM cards.
When we purchase a phone number online from websites like Google Voice or apps like textnow. In simple words, when you are receiving calls and messages via the internet for a phone number, its a VOIP number.

## How to check if it’s a VOIP or non-VOIP number?

There is not a tool or technique yet which works in every case. Generally, a reverse phone number is a good option for this. It will give you information about the cellular provider if it’s a non-VOIP number. For example, if I do a reverse phone number lookup, it will show you my name, my cellular provider, and some other details if you are lucky.

For Indians, Truecaller is the first tool that we use for reverse lookup because it has a large database of Indian phone numbers. Similarly, there are many other lookup services that you can use depending on your victim and your country.
Also, do a Google search about the phone number using Google Dorks, sometimes it makes the whole process easy.

## Get OSINT Ambition’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*We will deep dive intothis in an upcoming blog.*

Let’s now understand how we can find the real name of the user associated with the phone number.

## Ways to Find Real Name behind a phone number

- Using Banking Apps — This is the most efficient way of getting the real name of a phone number. Banking apps and websites require a strong verification for their usage including KYC in most cases. So, search for the phone number in banking apps like Paytm, and Google Pay, and websites like Paypal.
Search the phone number in all popular payment websites and apps of the target country for better efficiency.

- Using Social Media Apps — This is my second favorite way of finding the real name. Popular social media apps like WhatsApp, and Telegram force users to sign up using their phone number to use their services. So, these are good sources for finding the real name. Try to find out if the phone number is registered on popular social media apps, if yes, check if you can find any information about the victim from that platform.

- Using Reverse lookup — Another way of getting the name is using reverse lookup. Here, in general, we search for the phone number in the available database of that particular reverse lookup, if they have any records of that phone number, it will be shown to you. Popular reverse lookups are Truecaller, Spokeo, NumLooker, WhitePages, and TruthFinder.

- Leaked Databases — Sometimes, we find a lot of information about the target if they have been using any service whose database has been leaked online. For this, we generally rely on popular services like haveibeenpwned, breachdirectory. They will not only give you the real name, but also give other sensitive information like email, and social media profiles depending on the database and that individual.

- Abusing the functionality of websites — Sometimes, we get the real name by abusing the signup, login, and forgot functionality of websites the target uses. It depends on the websites if it’s possible or not.

*Note — Any data can be faked, so always check the information from other sources.*

There are many other ways but those vary on individual cases, we will learn about those in upcoming blogs and the above-listed ones in detail in upcoming blogs.

Now, let me tell you the personal approach that I generally use.
1. Firstly, I always check the prefix of the phone number which tells that the country name of the phone number.

- I then check if it’s a VOIP number or non-VOIP number, if it’s a VOIP number, I usually try to check if it’s a disposable number.
If it’s found to be a disposable number, I just drop the phone number as it will be a waste of time and I generally do osint for fun, so I just end the lead. If it’s a non-disposable number, I try to find out if it has any online activity like if it’s registered on any social media website, instant messaging apps, banking apps, etc.
If it’s a non-VOIP number, I search for it in lookup services and in banking apps.

- Once done with the above steps, I then check the phone number for its online activity. I try to find out the websites the victim uses, by hit and trial and guesses.

- Now, I search if the phone number is registered on WhatsApp and telegram. Telegram is my favorite one as I live in India and Indian people usually forget after signing up, so it works really well in most cases, especially for Indian phone numbers.

- I then search the phone number in database leaks using popular leaked database websites like breachdirectory, haveibeenpwned, etc.

- Now, I try different techniques that hit my mind, including abusing website functionalities like forgot passwords and other things.

That’s it for this blog. Thanks for reading this, subscribe to stay tuned about our upcoming blogs.

Follow our amazing writer [Dheeraj Yadav](http://twitter.com/Dheerajydv19?ref=osintambition.org) on Twitter.
Don’t forget to follow [OSINT Ambition](https://twitter.com/OsintAmbition?ref=osintambition.org) on Twitter to stay ahead and updated in the OSINT community.

---
