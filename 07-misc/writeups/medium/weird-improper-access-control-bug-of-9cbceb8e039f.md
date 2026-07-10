# :game_die: Weird Improper Access Control Bug of $$$

> **Original Source:** [Weird Improper Access Control Bug of $$$](https://infosecwriteups.com/weird-improper-access-control-bug-of-9cbceb8e039f)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Weird Improper Access Control Bug of $$$


Hello , So I am back with another write up . This one is about an Improper access control issue which I have found in a famous website which is used to create projects and collaborate with different users . Let’s see this in detail .


### **Description**


I am testing a website that contains three user roles: owner, admin and normal user (which can only read and write). Let’s refer to the company as ‘Private’ (as the report has not yet been disclosed).


I have created a project for myself with my email: email1, so I am the owner of the project. Now, I invited my second email: email2, with admin privileges. I tried to remove the owner, become the owner, etc. from my admin’s account but all attempts failed.


Finally, I thought to check for similar issues through a normal user perspective . I invited my third email: email3 from admin’s account . I checked whether the owner can see that I invited someone or not, and it turns out the owner can see that I invited another user into the project, and the owner can also delete the invite.


## Get Ankit Joshi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Also I checked every other basic issues like becoming owner/admin , removing admin , etc but not able to find anything useful.


After spending nearly 3–4 hours, I was not able to find anything interesting . Finally I thought , what if I invite someone whose account does not exist ? So I invited my other email address into the project i.e email4, and the account of email4 does not exist. To my surprise, the owner is not able to see that I invited email4 into the project. If the email4 user creates an account and accept the invite, then only the owner can see that user.


Now I can invite any other user as an admin without the owner seeing it.


But now you may think that what is the benefit of inviting another user if you are already an admin ? Let me explain this in more detail.


**Impact**


So as this is a project sharing website , it contains confidential information which should not be seen by any outsider . Now if owner removes admin (attacker) from the project due to any reason , then admin can rejoin the project by using the older invite link which is sent to email4 (which is non-expirable) . Similarly again attacker can invite new emails and keeps on joining every time and there is no way to stop this, except for deleting the project .


Due to this issue, confidential information can get leaked .


This bug was accepted as medium severity as it requires higher privileges to initiate this attack . After 2–3 weeks, I received $$$ for submitting this bug .


I hope you can learn something new with this . Thank you for your time!!

---

*Originally published on [Medium](https://infosecwriteups.com/weird-improper-access-control-bug-of-9cbceb8e039f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
