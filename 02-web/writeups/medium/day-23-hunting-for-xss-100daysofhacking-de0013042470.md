# :globe_with_meridians: Day 23 Cross-Site Scripting - Part 2#100DaysofHacking

> **Original Source:** [Day 23 Cross-Site Scripting - Part 2#100DaysofHacking](https://infosecwriteups.com/day-23-hunting-for-xss-100daysofhacking-de0013042470)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Day 23 Cross-Site Scripting - Part 2#100DaysofHacking


Get all the writeups from Day 1 to 21,[Click Here](https://github.com/ayush098-hub/100DaysofHacking)Or [Click Here](https://3xabyt3.medium.com/list/100daysofhacking-challenge-3db6061da4b1).


Hello folks, in our previous blog we talked about the basics of XSS, what are the types of XSS, now in this blog we’ll talk about how we can hunt for XSS, So let’s start.


Before starting hunting for any vulnerability, we should keep our burp open in the background.

### Step 1:


Now the very first step of finding XSS is to lookup for an input field where the user can input something, such as the name field while signup or comment field. We should check our input whether it’s reflected or not somewhere in the response or in page source.


Suppose there is not any input field, and we are not able to input our XSS payload then in that case suppose there are drop-down menus then also we can perform by intercepting the request and then inserting our payload in burp and then forward the request.

### Step 2:


After identifying input fields in an application, we can start entering a test XSS payload at the discovered input points.


Most basic payload as we all know:


```
<script>alert('xss')</script>
```


We can first insert this one to check whether pop comes or not.

---

*Originally published on [Medium](https://infosecwriteups.com/day-23-hunting-for-xss-100daysofhacking-de0013042470). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
