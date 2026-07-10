# :game_die: How I Found 7 Logical Bugs In The Com Olho Ctf Feature 7Adc4C88615D

> **Original Source:** [How I Found 7 Logical Bugs In The Com Olho Ctf Feature 7Adc4C88615D](https://infosecwriteups.com/how-i-found-7-logical-bugs-in-the-com-olho-ctf-feature-7adc4c88615d)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Let’s talk about the website in sort. The platform has a CTF program where you can submit flags and earn some points according to level of CTF. You can also create your own CTF and earn points if it’s good enough, they will upload it to their program.

## 1. Unlimited Points Farming via Replayed Flag Submission — P2


So when we submit a correct flag, we get points and the submit flag option is removed. The bug is that only the input is removed — there is no server-side validation.


- While submitting a correct flag, I capture the request:
`POST /api/ctf/submit_answer/128` using Burp.

- Send this request to Repeater. Now I can submit the same flag infinite times, and each time it will give me points.

## 2. Race Condition Allows User To Collect Extra Points From Single — P4


*I know you might be thinking why this is separated from point 1 — it’s because I found this later.*


- Follow the same process until the request is in Repeater, then right-click and choose extension, and select Turbo Intruder.

- Choose any script and launch the attack — the points get added multiple times.


Please read this blog first for better understanding of how creating and submitting your own CTF works because all the below bugs are related this.

## 4. Unlimited Points Earned By Re-submitting CTF Using Draft Manipulation — P2


When you submit your own CTF for review, you normally cannot revert it back to draft — you can only edit the CTF.


- Open Burp Suite and intercept the request while submitting a CTF:
`POST /ctf/123/`

- Send this request to Repeater and then let the intercepted request go forward (note: this is not the same as the first bug). The CTF is submitted successfully, and I get points for submitting it.

- Now i come back to the Repeater tab and modify the request by adding:
`save_as_draft = true`

- Send the request. The CTF reverts back to draft. I repeated this process again and again, and each time I received points.

>

*How did I know *`*save_as_draft*`* was a parameter? Because when I originally submitted the CTF as a draft, this parameter was present in the request.*


*Real request*

## 5. Race Condition Allows Submitting More Than 5 CTF per Months — P3


Because of the huge number of CTF submissions, they decided to limit it to only 5 CTFs per month.


- I created more than 5 CTFs and saved all of them as drafts.

- Open Burp Suite, click on Edit CTF, and in the request i get the CTF ID. Don’t change anything — just save it as a draft.

- Do the same for all other CTFs to collect their CTF IDs.

- Now submit a CTF and send this request to Repeater multiple times (5+).

- After that, change the CTF IDs in the requests (the ones obtained in step 2).

- Create a group in Repeater and send all the requests in parallel.

## 6. Points Awarded For Rejecting CTF via Manipulation request — (don’t remember)


So I submitted a CTF and it wasn’t good, so it got rejected. Basically, if a CTF is rejected, all actions should be blocked. But because of this bug, I was still able to submit a flag and get points.


- I submitted a flag to any CTF just to get the request format and sent it to Repeater.

- In that request, I changed the CTF ID to my rejected CTF ID (I explained above how to get the ID).

- I then changed the flag to the correct one — I knew the flag because I created that CTF.

- Done. I got points for the rejected CTF.

>

*Note: If your CTF is approved, others can solve it and submit flags, but you cannot solve your own CTF. And if the CTF is rejected, you should not be able to do anything at all.*


## 7. Allow editing of approved / publicly available CTFs. — P2


Once a CTF is approved, we are not allowed to edit it, but there is no server-side validation in place. This is the most dangerous bug in this blog, because once a CTF is approved, it becomes publicly available and other users can interact with it.


## Get StrangeRwhite’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I was able to edit an approved CTF. I could upload a virus, add phishing links, or redirect users anywhere. Users would think it’s just a normal CTF and run it to solve, without knowing what’s really inside. I submitted this as P1, but they changed it to P2.


- I opened Burp Suite and edited any old CTF, captured the request, and sent it to Repeater.

- Then I changed the CTF ID to an approved CTF ID.

- I could change anything I wanted, and all those changes became publicly available


Done! This blog is a bit different from my other blogs, and it may not be as clear, because I don’t remember everything perfectly and I had to put all the bugs into one post. I also didn’t want to make it too long. So if you don’t understand anything, just mail me and I’ll share the original POC.

>

*Got questions? Email me: strangerwhite9@gmail.com or reach out on Twitter: *[@StrangeRwhite9](https://x.com/StrangeRwhite9?t=xdbpVbjrkxEW1TQSfK94jQ&s=09)

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-found-7-logical-bugs-in-the-com-olho-ctf-feature-7adc4c88615d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
