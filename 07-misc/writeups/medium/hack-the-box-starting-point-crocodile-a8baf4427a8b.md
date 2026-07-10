# :game_die: Hack the Box Starting Point: Crocodile

---

# Hack the Box Starting Point: Crocodile

Time for our next Tier 1 box, Crocodile looks like it will be covering a few of the different tools we’ve been getting familiar with rather than introducing any new ones. Scrolling through the questions I see some FTP, gobuster, nmap, php, you know, fun stuff. Anyhow of you’re not familiar with any of this I implore you to go back and look through some of my other posts, otherwise fire up your attack environments and let’s go huntin for gators.

## Task 1

We actually briefly touched on this in the last post, but to reiterate it here again. Nmap has some very powerful scripting utilities that are definitely beyond the scope of what I’m going to cover here. For our purposes here the`-sC` flag tells nmap to utilize the default scripts when we run our scan. Nmap has a ton of scripts built into it natively and you can also make your own. If there's a specific script you'd like nmap to use you can specify that with`--script=[script_name]`, but for us the defaults will suffice. For more info on nmap scripting feel free to refer to this article [here](https://www.geeksforgeeks.org/linux-unix/how-to-use-nmap-script-engine-nse-scripts-in-linux/).

## Task 2

Now normally I’d have us run a classic service scan on this bad boy, but we’ll actually be utilizing that default script scan I was just talking about. So my nmap scan today actually looks like this:

## Get KarmicDragoon92’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

which has that -sC flag we discussed to enable the default scripts, but also this `-T5` flag. If you haven't see that before all that is, is actaully nmaps "throttle" so to speak. It just tell nmap how fast I want it to scan. 5 being the highest value and 0 being the lowest, there are legitimate use cases for each one, but I'm not going to get into that now. I just wanted this scan to move a little faster because the scripts can take a while to execute. Looking at our output though...

We see a lot of interesting stuff. FTP is running on the default port of 21 and some of the nmap scripts did a little bit of enumeration for us. We can towards toe bottom that anonymous login is allowed and also we got a few files listed “allowed.userlist” and “allowed.userlist.passwd”. Well how about that. However, we need to answer our task question and so just above the line where it says anonymous login allowed is our version number. Go ahead and plug that in and then we’ll move right on along.

## Task 3

If we actually look back at our nmap output we should see…

So there we go, perfect.

## Task 4

I believe to login anonymously to FTP the username is just ‘anonymous’. Let’s give it a try.

Nice, we’ve logged into the FTP service with the username ‘anonymous’. Let’s quick answer our question and then move onto the next task.

## Task 5

From the FTP CLI we can run help with no arguments which gives us a list of useful commands.

The output shown is clipped (by a lot), but it has the command we want. In the bottom left we see `get` which is the command we can use to download files from the FTP server back to our client. Let's grab both files of interest we saw from our nmap scan.

Perfect, with our files of interest pillaged let’s go ahead and exit out of FTP here (just type exit).

## Task 6

Let’s go ahead now and examine the contents of our files. After running `get` on the FTP server, the files should just be saved to your current working directory. Let's go ahead and cat both of them out here and take a look.

Well, I don’t know about you, but admin sounds like a pretty high privilege user and we also have their password it looks like. Let’s answer our question and keep moving along.

## Task 7

Well I hope you still have your nmap output. That is my bad to be fair, we should be saving out namp results to a file by this point, we’ll start doing that as best practice going forward here (you should absolutely be doing that for real engagements btw). If we go back and look though…

oh that’s actually not what I was expecting. Our default script scan didn’t actually give us much back. Alright well, let’s go ahead and run a service scan on port 80 **and** save it to a file.

So besides our normal service scan flags there is also the`-oA` flag which tells nmap to save the scan results to three different file types that you can see listed by the ls command after the scan runs. You can specify the file type(s) you want with other flags, but I just did all three. I would suggest catting them all out and seeing how they each look. The nmap scan itself though lists the version number we're looking for so let's plug that in and move onto the next task.

## Task 8

We answered this on another box recently, but I’m having a hard time remembering…

Ah yes that’s right`-x`. You see me use gobusters help command on the dir subcommand and then I pipe that to grep with the -i flag for case insensitivity. I show me using help commands, one because I forget things all the time, but two because you will too and it's important that we know how to answer our own questions sometimes. Anyhow`-x` is the flag we're going to want.

## Task 9

Let’s fire up gobuster and point it at the target now.

Here you see me run

```
gobuster dir -w /opt/useful/seclists/Discovery/Web-Content/common.txt -x .php -u http://10.129.1.15
```

which uses the common.txt wordlist, searchers for php files at the target URL. Looking at the output we a few interesting endpoints:

The one we’re probably most interested in is login.php.

## Root Flag and Conclusion

Open up your web browser and navigate to the target IP /login.php like so.

Using the admin credentials we pillaged from the FTP server, let’s go ahead and login.

Oof, you really hate to see it happen.

Honestly, this was a pretty fun box. Tested a lot of the things we’ve been learning up till this point and it’s always important to review things every now and then. Thank you for checking out this post and as always stay tuned for the next one. Thank you so much and adios for now.

---
