# :globe_with_meridians: Medium

---

# How I got RCE In The World Largest Russian Company

*Photo by [Christian Wiediger](https://unsplash.com/@christianw?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

Hello Security Researchers & Hackers

In this writeup I will explain how I was able to find RCE in Mail.ru which is considered the world largest internet company,
Before starting to hack I was wondering on how I should approach the target and what most people would miss in the program, they have a huge scope which means it should be something out there sitting for me to find XD

I started looking with the Favicon using [This](https://gist.github.com/yehgdotnet/b9dfc618108d2f05845c4d8e28c5fc6a) Where I replace the link with the Mail.ru favicon, once generate I go to shodan.io and search for it

Now we search this hash on shodan.io with the **http.favicon.hash** syntax

Now I went to see page by page and look for something suspicious with an unusual port number so I kept going till I found a host with port 8080
That has a **Welcome to Nginx page**
Once found I wanted to dig further on what’s going on, so I started to FUZZ directories and I…

---
