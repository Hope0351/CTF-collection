# :game_die: HTB Academy: Windows Fundamentals

> **Original Source:** [HTB Academy: Windows Fundamentals](https://infosecwriteups.com/htb-academy-windows-fundamentals-eefae02ee49c)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Academy: Windows Fundamentals


Now in the past, I’ve gone on the record saying that I don’t like covering Academy content and that’s still true. I will do it however if one of two conditions are met, I think it’s hard and there’s not a lot of resources on the topic. Or if I personally suck at it and this one is definitely the latter as my Windows sysadmin skills are not great. With that being said, feel free to join me as I quick work on the Skills Assessment portion of the HTB Academy Windows Fundamentals module.


Here we’re given a little scenario to mentally prepare us for the daunting tasks ahead. So what are these tasks?


Oh no, creating folders? Users? Managing permissions? This is getting serious. I joke, but I honestly am not 100% certain how to do all this on Windows, which is why I am in fact making a post about it. Now we have these tasks, but we also have questions at the bottom that we need to answer as we go. So, let’s take a look at the first question and get started on these tasks.

## Question 1


Well, in order to answer that, we are going to need to complete task 1. The first step in this process is RDPing into the target Windows box using `xfreerdp`. After running


```
xfreerdp /u:htb-student /p:Academy_WinFun! /w:1920 /h:1080 /v:10.129.188.92
```


we are dropped into our remote Windows machine. After landing on the desktop I am going to right click on the desktop and hover over New and then Folder.


Be sure to name the folder Company Data. Now in order to share this folder, we are going to need to right click the folder and select Properties.


Now after navigating to the Sharing tab we see…


Well simple enough, let’s hit share.


Here we see a drop down menu where we can select who has access to this folder. For our purposes we will select Everyone and then click Share (shield icon means admin privileges required).


So this is an interesting question. I am going to select no as I only want to share this folder on my local network. I could be misunderstanding the prompt, but I don’t think I’d ever want to publicly share it.


Bam, easy. Click done. Now to answer the first question we got, let’s click on the Security tab of the Properties menu.


Here we see a few users/groups listed. By default I am pretty sure SYSTEM is the default group in question here. Actually nope, we’re in the wrong place. My bad, we’re going back to the Sharing tab and then click on Advanced Sharing.


Check Share this folder and then click on Permissions.


Ah, let’s try that. That is the answer by the way, but in the Beta for the new Academy GUI there’s no cool effect for getting it right so just take my word for it. Go ahead and click OK on all these menus so we can move to our next task. Which is quick creating another Folder called HR which needs to go in the Company Data Folder. Go ahead and create it the same way we did earlier and then drag it into the Company Data folder. After I did that, I clicked on the Company Data folder to open File Explorer and see what’s inside.


Cool looks good. Okay, moving onto Question #2.

## Question 2


Oh we got this one easy. You see, earlier in the Security tab that I thought was managing the Share permissions was actually managing the local permissions. As the default file system type for Windows is NTFS `Security` should be our answer. Yep, got it.

## Question 3


Alright, I think it’s PowerShell time.


Okay, I’m going to take some time to explain this quick. Yes, running Get-Service displays all of the services on the host. Now, as we’re looking for something to do with Windows Update I wanted to filter the output hence the -DisplayName flag. We see a few services still, but only one with Windows Update: `wuauserv`. BAM For more on the [Get-Services](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.management/get-service?view=powershell-7.5) command if you'd like.

## Question 4


Well in order to do that, we’re finally going to need to make our Jim user finally. Now, we could do it through the Windows GUI, but as I’m trying to use PowerShell I’m going to stick with that. After a quick google search I found this.


[New-LocalUser](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.localaccounts/new-localuser?view=powershell-5.1) appears to be the command we want, let’s create Jim.


Ah, right. Needs admin, obviously. Open a new PowerShell prompt with admin privileges by right clicking and Run as Admin.


There we go. We can then find his SID with `get-localuser | Select name,sid`.


Perfect

## Question 5


Alright, this will be the last PowerShell task we’ll do and then we’ll mess with Company Data’s permissions. Once again referring to Microsoft’s documentation it looks like our command will be [New-LocalGroup](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.localaccounts/new-localgroup?view=powershell-5.1).


Awesome, let’s run this bad boy.


You see here we created the HR group and also spit out it’s SID. So that SID is the answer to our last question (woo), but we still have those tasks we need to do. It’s important to practice our sys admin skills. Quick speed run of me doing the last few tasks. Such as adding Jim to HR.


Here you see me add Jim to HR and verify it with the last command, that middle one was me trying and failing.


Here you see me once again go into Properties, Security, I click Edit and then Add. In the box I just typed HR and clicked OK.


There we go. Now we need to change the Share permissions to add HR and also remove everyone.


Modifying the permissions for the Share is very similar to modifying the local permissions. To disable Inheritance…


Under Security, we go into Advanced and click Disable Inheritance (which is where Enable is here, I just disabled it already).

---

*Originally published on [Medium](https://infosecwriteups.com/htb-academy-windows-fundamentals-eefae02ee49c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
