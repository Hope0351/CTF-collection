# :game_die: Natas2 — Wargames solutions writeup

> **Original Source:** [Natas2 — Wargames solutions writeup](https://infosecwriteups.com/natas2-wargames-solutions-writeup-2b2946358259)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Natas2 — Wargames solutions writeup


Hello guys and welcome back!!, It’s been quite a bit since I have written my last blog in this Natas Wargames solution series. Today, we shall explore the next Natas web security challenge, which is Natas2. As you may have already seen the goal of this challenge is to get the password for the next level which has the username natas3


So, let’s get right in!!


So to open this challenge, you need to visit the URL: [http://natas2.natas.labs.overthewire.org/](http://natas2.natas.labs.overthewire.org/)


And now you would be prompted to authenticate yourself. Please make sure to enter the username as natas2 and password as the one you got from natas1


The homepage of the challenge website (we need to hack) looks like this:


*Homepage of natas2 website*


It says tacitly “There is nothing on this page”. Let us have a look at the source code and see if we get any clues.


*Source code for natas2 homepage*


We can view the source code of any webpage by rightclicking the page on our browser and then clicking the “View Page Source” option.


Ah! we see something new here!! an img tag with src attribute set to files/pixel.png


## Get Adithya M S’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We see a black pixel image on visiting this URL


*Image file hosted at the URL [http://natas2.natas.labs.overthewire.org/files/pixel.png](http://natas2.natas.labs.overthewire.org/files/pixel.png)*


We have also come to know of the existence of a hidden endpoint /files. Let’s try visiting this endpoint now


*The page you see on visiting the endpoint /files of this website*


This website, as you may see from the above image lists all the files and directories (in the directory associated with the files endpoint) when we visit this endpoint /files . In other words, this has a directory listing vulnerability


To be more precise, a directory listing vulnerability at a website endpoint occurs when misconfigured server settings expose the contents of a directory (e.g., files, folders) to users, potentially revealing sensitive data like configuration files or credentials. It allows unauthorized access to browse and retrieve resources that should remain hidden.


Let us now click on and view the users.txt file


The contents are as follows:


*Contents of users.txt file in /files endpoint of the website*


As you can see the password of the user natas3, which is the target of the challenge is revealed to us here!! Hurray, we have solved the challenge 🧨🥳🥳


The password for the user here is blurred to prevent copyright issues, but you may always follow my steps to solve this challenge and get the password for the next level.


Please give me as much claps as you can and follow me so that I can bring the entire Natas challenges solution series for you web security enthusiasts!!


Thank you for reading and happy hacking !!

---

*Originally published on [Medium](https://infosecwriteups.com/natas2-wargames-solutions-writeup-2b2946358259). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
