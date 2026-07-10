# :game_die: HTB Academy: Windows CMD and PowerShell

> **Original Source:** [HTB Academy: Windows CMD and PowerShell](https://infosecwriteups.com/htb-academy-windows-cmd-and-powershell-4abfd13d6a1e)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Academy: Windows CMD and PowerShell


I did say that I needed to work on my Windows sys admin skills and also my PowerShell-fu and so here I am. As per the usual when it comes to my Academy content, I will just be covering the skill assessment part of the module. It was a good module though, covered a lot of content as you get some hands on with both CMD and PowerShell and both are important. I came into this module with a bit of CMD know how, but PowerShell not as much, although lots of cmdlets are aliased to Bash commands so that makes it a lot easier to pick up. Now with that being said, let’s go ahead and actually get into the skill assessment here.

## Scenario


Well it looks like for each task we have for this assessment we will be sshing into the Windows host as a different user and conducting various different tasks. Alright, well let’s get this show on the road then.

## Question 1


Okay so just ssh into the Windows box and we get a freebie flag, sure thing.


Well what string here looks like a flag? Yes, it’s the one you think it is.

## Question 2


No problem, let’s quick login as user1 with the previous flag as our password (not literally “previous flag). One important note is that when you land on the Windows host you’ll be dropped into a CMD shell. If you want to switch to PowerShell type that into the console and hit enter and you’ll switch to a PowerShell terminal. That’s what I’m going to do just to demonstrate.


You can see my shell prompt change to indicate I am now running in PowerShell. Okay any who let’s go read that file.


Okay so here you see me run a few cmdlets (PowerShell speak for commands) that we see in orange text. That first one functions like `ls` on Linux and just lists our current directories contents. We see that we're in the Users home directory and the file we want is on their desktop. I use Set-Location (equivalent to `cd`) to change my current directory to Desktop and then Get-Content prints out flag.txt's content to our terminal. Like the flag says, nice and easy right? Also, do remember there are lots of aliases created in PowerShell for our Bash commands. I literally could have run `ls`, `cd` and `cat flag.txt` and achieved the same goal. However, this is a PowerShell skill assessment, not a Bash one so I will be sticking with using cmdlets exclusively.

## Question 3


So fun fact for everyone, it’s not explicitly stated, but all passwords for each user are the flags for the previous question. I probably should have been able to figure that out, but I did need to search around a bit to find that out. Anyhow, now landing on our Windows host, we are actually going to stay in CMD to answer this one.


Our flag here is just going to be the value in the Host Name field. This is the output from the `systeminfo` command which gives is a lot of information about the host we're currently logged into.

## Question 4


Well this shouldn’t be too bad.


So after logging in a user3 and moving into a PowerShell terminal I moved to user3’s desktop and ran `Get-ChildItem -Attributes Hidden`. For some reason Academy's terminal here hides anything you type after the - character for some reason, but it's still there. Now I did only clip a portion of the output here, but at the bottom...


we see there’s 99 .txt files. However, we also have the .ini and .lnk files which are also hidden, giving us a total of 101 files.

## Question 5


You know the drill by this point.


In user4’s Documents folder we see lots of directories here and yes they each have a fair amount of files in them. Let’s list out all of these branching paths and try to see maybe where our flag is hiding.


So this is actually just a snippet of the output, but yeah no each of these subdirectories has their own flag.txt. So which one is it? Well, here’s the interesting thing.


All of these txt files don’t actually have any content. So. presumably, the flag file we want would be the one with our flag inside of it. How can we search all of these files to see which one has something in it?


## Get KarmicDragoon92’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


`findstr` is what we can use on Windows to search for strings in files. `\S` makes our search recursive and `"."` actually is the wild card character for this command so keep that in mind. This command searches all of the flag.txt's for any string in them and we see that only one has any content in there.

## Question 6


Well this one seems relatively straight forward, let’s use PowerShell to list all of the users.


So not counting the Default and Utility accounts we are looking at 14 user accounts.

## Question 7


Once again the `systeminfo` command is what we're going to want to use here.


We see here that the registered owner of the system is `htb-student`.

## Question 8


Gotcha, so first we’re going to need to ssh into our target box and then use PowerShell to ssh into the domain controller.


After sshing into the DC (Domain Controller) I ran systeminfo again just to see some of the differences between our normal target box. Now to list all of the available PowerShell modules here on the DC we’re going to run `Get-Module -ListAvailable`.


Huh…


## Question 9


No problem, let’s run `Get-ADUser -Filter * -Properties Surname` which is going to give us the output of all the users on the system, but if we comb through the output...


And the answer is the GivenName of this user.

## Question 10


This task literally tells us the command to run, we just need to figure out a way to sort the output…


Oh yeah, pretty intuitive. Answer should be the first process with vm at the front.

## Question 11


Finally our last question. Let’s go ahead and get back into the DC the same way we did for a previous task and then we’ll get going. I’m not going to lie, this one ended up being more difficult that you would first think. First and foremost here is the command that I ran.


```
Get-WinEvent -FilterHashTable @{LogName='Security'; ID=4625} | Group-Object -Property @{Expression = {$_.Properties[5].Value}} | Sort-Object Count -Descending |
```


I found this command from another [writeup](https://medium.com/@clh0011/introduction-to-windows-command-line-skills-assessment-walkthrough-32c1d76d52c0) and yeah no it’s a lot. However…


We see here the name of the user.

## Conclusion


PowerShell and CMD are very powerful tools and we as security professionals, system admins and all kinds of IT folk need to be comfortable with these tools. We don’t all need to be wizards, but we got to be comfortable, especially if you are doing an actual red team engagement. You have to be able to live off the land a little and use what you’re given and a lot of the time these will be tools that you will definitely have access to. As always, thank you for checking out this post and I will see you in the next one!

---

*Originally published on [Medium](https://infosecwriteups.com/htb-academy-windows-cmd-and-powershell-4abfd13d6a1e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
