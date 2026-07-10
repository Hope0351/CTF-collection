# :globe_with_meridians: EG-CERT CTF 2025 Web Challenges Writeup

> **Original Source:** [EG-CERT CTF 2025 Web Challenges Writeup](https://gem0x00.medium.com/eg-cert-ctf-2025-web-challenges-writeup-28647607c094)
> **Platform:** gem0x00.medium.com | **Category:** `WEB` | **Year:** 2025

---

# EG-CERT CTF 2025 Web Challenges Writeup


## By Mohamed Gamal (gem0x00)


بسم الله خير ما يفتتح به الأديب كتابه، والخطيب خطابه


Hello This is Mohamed Gamal gem0x00 and through this writeup I will walkthrough the challenges I’ve Solved in the EG-CERT CTF 2025 Web challenges let’s begin.


First challenged I’ve solved called Internal


when I opened I found this page …


When I clicked source …


When I clicked flag


From the code we saw we deduct that the `src `parameter gets you the source code of the page requested and there is a `url `parameter this `url` parameter must start with http or https and after this it should contain the `egcert` then it will execute a curl command this means that there is a SSRF Vulnerability with a weak protection the developer when he tried to protect his website from SSRF did a very bad protection so I tried to do this :


[http://64.227.76.217:8080/?url=http://egcert.localhost](http://64.227.76.217:8080/?url=http%3A%2F%2Fegcert.localhost)


and got this :


If you notice that the page called again and there is 1 this 1 is indicator for that the `url `you entered is accepted so I did this :


[http://64.227.76.217:8080/?url=http://egcert.localhost/flag.php](http://64.227.76.217:8080/?url=http%3A%2F%2Fegcert.localhost%2Fflag.php)


and got the flag:


Let’s go to the 2nd challenge I’ve solved :


[Out of Order](https://ctf2025.egcert.eg/challenges#Out%20of%20Order-7)


At first I tried to understand the application and the application sends the feedback to the admin I Read this and said this application may be vulnerable to SSTI (Server Side Template Injection)


did this and see that result tried to see the type of the template that the server use Asked AI and after many and many attempts I knew it is djanjo :
{% include “secretflag” %}


Only remove the double quotes :


Let’s see the Revenge of this Challenge 😂


[Out of Order — Revenge](https://ctf2025.egcert.eg/challenges#Out%20of%20Order%20--%20Revenge-30)


It is the same and when you input the same payload you get this


Honestly I asked the AI to tell me what can I do It tells me that payload


{% include secretflag|b64 %}


I told my self why not do it in another way :


{% include secretflag|urlencode %}


This is what happens when you team up human intuition with AI — solved in minutes flat. Proof that brains + bots make an unstoppable CTF duo.


Thanks for reading …


[LinkedIn](https://www.linkedin.com/in/mohamad-gamal-abdelmegeed-ab903a236/)


[Github](https://github.com/M0hmedGamal)

---

*Originally published on [Medium](https://gem0x00.medium.com/eg-cert-ctf-2025-web-challenges-writeup-28647607c094). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
