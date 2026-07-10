# :game_die: HTB Starting Point: Synced

> **Original Source:** [HTB Starting Point: Synced](https://infosecwriteups.com/htb-starting-point-synced-c24e53638573)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Starting Point: Synced


## Rsync is a Pretty Important Tool


Hey there and welcome to the final box under HTB’s Starting Point Tier 01 Yayyyy (this took me way too long). Anyhow, todays box is going to be going over the usage of a tool called `rsync` which is another file transfer tool, but a very powerful one. Frequently used by sys admins and what not to perform system backups and things of that nature. You should know the drill at this point, if not, that's okay feel free to check out some of my other Start Point writeups and come back when you're ready. Otherwise, after connecting to the box either with a VPN client or the Pwnbox let's get rolling.

## Task 1


So yes, rsync is a command, but it is also a service and as such has a default port. We could google this quick or we can take a peak at the rsync man page using `man rsync` and see what we can find.


Scrolling down through the man page here, a little ways down, we see that the rsync daemon typically uses port 873 so there we go. It is important to get comfortable reading man pages as in some engagements you may not always have internet access. I relied heavily on them during my RHCSA exam and I think it’s something all IT professionals should be familiar with. Anyways, moving right on along.

## Task 2


Welp, we all know what to do by this point. Let’s fire off a service scan on all ports with nmap shall we?


Here we see rsync running on it’s expected port as well as the version number. There are no other services running on this machine so it’s just the one.

## Task 3


We actually saw this is our nmap scans output, so where it says protocol version go ahead and enter the number next to that.

## Task 4


Well I kinda spoiled this already, but again, rsync is both a service and a command. You interact with the rsync daemon via the rsync command-line utility. Everyone clear on that? Awesome, moving on.


## Get KarmicDragoon92’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in

## Task 5


You know what actually that’s a really good question. Let’s go consult the man page again and see if we can find an answer.


So after perusing the rsync man page we only can find one occurrence of the word anonymous (you can search for strings in man pages with /(STRING). Maybe the answer is that we don’t need to supply any credentials at all for an anonymous transfer? And `none` is indeed the answer, okay cool let's keep moving.

## Task 6


You know where we’re going for this by now.


Here we see this parameter as being what we want to pass to rsync to just list files. For your answer, be sure to leave out the leading -.

## Root Flag


Well we probably need to interact with the rsync daemon on the remote host. Let’s just fire off `rsync` at it and see what it does.


Oh, interesting, it looks like some file shares are visible? Let’s check out the public share.


Oh? Can we maybe transfer the flag file to our local host?


Perfect, let’s cat it out and submit it.


## Conclusion


Again, rsync is a very powerful file transfer tool and you should be familiar with it, obviously HTB thinks so. More importantly we have officially done all the Tier 0 boxes yayyyyyyyy. We are still infants in this vast world of cyber security, but we’re starting to be able to do some stuff. The fundamentals are so important, that’s why it’s worth doing things like Starting Point. I did my RHCSA and CCNA and now my Linux and networking skills feel much better and allow me to understand more advanced concepts later on. I appreciate you sticking around and hope to see you for Tier 1!

---

*Originally published on [Medium](https://infosecwriteups.com/htb-starting-point-synced-c24e53638573). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
