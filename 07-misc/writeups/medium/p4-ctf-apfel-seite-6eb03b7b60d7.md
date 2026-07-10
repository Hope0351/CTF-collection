# :game_die: P4 Ctf Apfel Seite 6Eb03B7B60D7

> **Original Source:** [P4 Ctf Apfel Seite 6Eb03B7B60D7](https://infosecwriteups.com/p4-ctf-apfel-seite-6eb03b7b60d7)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

There is my write-up for p4 CTF’s apfles seite web exploitation challenge. In this challenge, we need to review an apple store website, looking for any vulnerabilities.


First, we access the URL they give us, and we can see four navigation buttons. We could press any of them to see a page with a path to “description.txt” in the “apfel_selection” parameter.


We can try changing the value to another file to confirm if we have path traversal. To do this, we try to read the file /etc/passwd.


We can see that we can use absolute paths, but if we try with the relative path from our position “../../../../../../../../etc/passwd” we get the following error message.


To see the reason for this message, we can access the server code by reading the index.php of the page through the vulnerability.


Let’s make the code easier to read and analyze in more detail.


We see it filters the inputs with “..” and that’s why it gives this error. But we still have no clue where to locate the flag. After trying the usual methods to get code execution from a traversal path and enumerate all the standard files, I did not make any progress in solving the challenge.


## Get Cybertrinchera’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I decided to take a break and give a new and different approach to the challenge by recapping what we had:


- Apple themed challenge.

- Path Traversal.

- Unknown flag location.


And then I remembered one of my first pentest, where the client was exposing the .DS_Store files, and thanks to that, we discovered a series of files on the server. I did the test, and there was the file:


If we download and parse the file, we see that inside the root, there is only the apfels directory.


Let’s now look at the *.DS_Store* inside the apfels directory.


We could see a large number of directories, entering and downloading the *.DS_Store* of each one seems like a tedious task. So we are going to automate it with the help of BurpSuite, specifically with the Intruder.


Now, we can see that one of them is significantly different from the rest:


We can download the *.DS_Store* and extract the name of the file with the flag.


Finally, we can read the flag file and get those points:


*GG!*

---

*Originally published on [Medium](https://infosecwriteups.com/p4-ctf-apfel-seite-6eb03b7b60d7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
