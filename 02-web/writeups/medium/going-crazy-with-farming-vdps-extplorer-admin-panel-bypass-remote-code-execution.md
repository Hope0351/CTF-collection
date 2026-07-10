# :globe_with_meridians: Going Crazy with Farming VDPs: Extplorer Admin Panel Bypass & Remote Code Execution (RCE)

---

# Going Crazy with Farming VDPs: Extplorer Admin Panel Bypass & Remote Code Execution (RCE)

## Hi Kings & Queens, I’m YoungVanda and in this write-up, I’ll talk about a very simple CVE which led to over +20 high—critical vulnerabilities in a couple of hours and over +500 reputation. Yeah buddy, lightweight baby.

### *In the Name of the One Who Gives Glory*

>

If you only want to read the technical part, please start reading from the Technical Part Header.

## Some Hunting Vibes

Since I was a little boy, I always wanted to be a Gangster. Sorry, I meant a farmer. 🧑🏽‍🌾🧑🏽‍🌾🧑🏽‍🌾🧑🏽‍🌾 😂😂😂

Like World War II soldiers’ dreams, like Western movies.

After all the war and fights, I just wanted a peaceful life. Buying a land on the edge of the world, marrying to the desired one and making babies.

So I said why not!!! f♥♥k yeah. I’m in. Let’s farm some VDPs honey.

I hit up my friend [@TheM@sterOfDisaster](https://x.com/TheMsterDoctor1) , the most dangerous doctor in the world.

*Just kidding 😅😁*

>

Thank God this is where we ended up.

## Technical Part

After some recon, we decided to work on a program with this scope.

>

https://app.redacted.com

I love forcing things, you know 🤔😜. Especially when there is no WAF, that’s when I get violent. So basically the first thing we did was FUZZING.

>

ffuf -u https://app.redacted.com/FUZZ -w wordlsit.txt -c -r

We got a hit with this endpoint /file_manager/ . Then, the first thing we saw was this Admin Panel.

*This is what Extplorer panel looks like. Take a mental screenshot for the next time 😂😂😂*

From old to new resources, from ancient times 😂😂😂, we’ve been told to look for CVES when we face a third-party panel or admin panel. Therefore, nowadays every hunter does the same thing. Right? OK. That’s what we did. 😐😂

## Get YoungVanda’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

We came across this reference from Exploit-DB:

>

[https://www.exploit-db.com/exploits/51067](https://www.exploit-db.com/exploits/51067)

We did a bit of reading, playing around with the target, like Cannibals, and after a couple of minutes, we realised that it’s vulnerable to Authentication Bypass. `eXtplorer<= 2.1.14 - Authentication Bypass`

We put admin:admin and then captured the request, removed the entire password field and finally sent the request.

*Just random admin:admin*

*Original Body RequestEdited one — Removed password filed — &password=admin*

*This is what it looked like*

The Explorer panel allows you to view and manage files in your test directory. The panel shows the directory’s content as a tree of subdirectories, files, and tests. Long story short, we could read the source code and extract unauthenticated endpoints with parameters. Since we had access to the source code we could see what vulnerabilities each endpoint had. You can guess the rest of it. Since they were all unauthenticated endpoints and not same-root/same-cause/anything you say😘, they were all accepted.

### Just being honest and some words

Well, the key to this discovery, for us, was doing structured Wide Recon and I’m sure if I gave that application to any hunter they could find the same discoveries more or less. So, we can conclude that we were the first hunters working on that application.

This is how I see it:

>

Simple Techniques + Good Wide Recon Methodology = Success — Bug

By Simple techniques I mean, it could be a simple fuzzing, running a simple nuclei command, a simple active crawling, a simple Google Dorking, and so on.

### A little Me

I’ve been a bit inactive the last couple of months. But God is with us guys. I hope very soon I can have a strong comeback.

If you somehow liked my write-up, you can like it and follow me on social media.
I don’t know man. It was nice to write something again and share some knowledge.

My Twitter Account: [@young_vanda_](https://twitter.com/young_vanda_)

My Super Dope Friend: [@TheM@sterOfDisaster](https://x.com/TheMsterDoctor1)

Let’s gooo. Yeah buddy, light weight baby. Lightweight baby, light weight.

### Resources

---
