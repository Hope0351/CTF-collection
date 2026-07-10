# :globe_with_meridians: Mastering Blind XSS: Expert Techniques for Seamless Discovery

---

You have probably clicked after the title, in this blog I am going to discuss the unpopular type of XSS that big security researchers don’t pay much attention to and obviously finding it.

### Introduction:

First let’s discuss what actually XSS is, XSS is a short form of Cross Site Scripting.

>

XSS is a type of web application attack in which the attacker compromises the interactions which the users have with a vulnerable application.

### Types of XSS:

There are three major types of XSS, these are:

- Reflected XSS: The most common type of XSS that works when a malicious script is reflected off a web application to the victim’s browser.

*example:* when inserting *<script>alert(1)</script>* into a web application vulnerable to reflected XSS, it will give a pop-up saying (1).

- Stored XSS: A type of XSS that works when an application receives data from an untrusted source and includes that data within its later HTTP responses in an unsafe way.

- Blind XSS: This type of XSS cannot be determined if it is executed or not, in other words you won’t know if your payload is executed or not but we will use some tools to make our work easier.

### Working of Blind XSS:

Blind XSS works when you inject your XSS payload in the target website’s comment boxes, sign-up & login forms, contact forms, email newsletter boxes and etc.

## Get an0nbil’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

When you inject them you have to wait it to be executed. When it is executed the tool you used for blind XSS will send you an email telling that your payload is executed.

### Finding Blind XSS:

First choose a target website, and then use a tool for blind XSS.

I recommend you [bxsshunter](https://bxsshunter.com/) for finding Blind XSS . It is a web based application that makes your blind XSS hunting easier and efficient. Simply Sign-up on [bxsshunter.com](https://bxsshunter.com/).

*bxss hunter sign-up page*

After signing-up go to payloads tab.

*payload tab of bxsshunter*

Copy any payload and enter it on your target website’s comment boxes, search boxes, login and sign-up forms etc.

*entering payloads*

In the above example I entered them in username and password boxes. Now after clicking login I will get a notification in my [bxsshunter.com](https://bxsshunter.com/) XSS fires tab.

*XSS fire*

In XSS fires tab it will show you a notification with the victim’s IP and other details. The best thing about [bxsshunter](https://bxsshunter.com/) is that it auto generates a vulnerability report of your every XSS fire. Simply click on Generate Markdown button.

*Vulnerability report*

After Finding a Blind XSS you can report it to the organization owning the website and if it’s impactful you may get a bounty or a swag.

---
