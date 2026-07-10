# :game_die: HTB Machines: Difficulty Matters

---

# HTB Machines: Difficulty Matters

Hi folks, if you are in cyber security on the red side, you probably hear what Hackthebox is. In basic words, it is a platform that collects vulnerable machines to train hackers to improve their hacking skills.

But there is an important step on these machines. As you know, for solving machines you have to find a vulnerability that the machine creator creates. So that means, usually there is only one way to get in. That’s why the CTF mindset is, so much different than the typical pentest.

If you start there, you will spawn a machine and you will try to hack it without any hint. But, what should you look for? How deep are the holes? For these questions, you have to know HackTheBox policy.

## Get zer0dac’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

As we have talked, Hackthebox collects vulnerable machines, right? How did it come? So, who can submit machines? The Hackthebox team and users of course. Just like open-source things.

According to hackthebox:

>

We encourage experienced users to submit their Machines/Box to Hack The Box, where they will be reviewed by our content delivery team and if deemed appropriate, posted on the HTB Box Submission line-up for everyone to enjoy!

So that means, everyone can create vulnerable machines. But, what rules are required for the machines’ severity?

The difficulty level of the machine changes the enumeration. What do I mean? Let's look together at the difficulty rules for submitting a machine.

*[https://help.hackthebox.com/en/articles/5307061-machine-submission-requirements](https://help.hackthebox.com/en/articles/5307061-machine-submission-requirements)*

Let's explore easy machine rules:

- root and user flag can not be 4–5 steps. So, it shouldn’t be confusing things like finding LFI, then reading source code then finding another bug etc.

- CVE script or Metasploit without modification, means, that if you find a website, you should check versions and look for any vulnerable service that is exploitable. So for the user flag, you will not create a new thing, all you need to do is find that bug that already has an exploit.

- There is no rabbit hole and context will guide you. So the machine hasn't any tricky hints. If you read something like hey George, there was an XSS we didn’t fix, that means there is an XSS that exists.

- Especially for the root part, there is no binary exploration exists. You need to find configuration vulnerability or again version exploit for the root part.

Hope it helps.

---
