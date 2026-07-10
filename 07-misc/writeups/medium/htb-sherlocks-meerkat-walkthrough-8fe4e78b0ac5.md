# :game_die: [HTB](https://hacktheboxltd.sjv.io/19ZM06) Sherlocks: Meerkat Walkthrough

---

# [HTB](https://hacktheboxltd.sjv.io/19ZM06) Sherlocks: Meerkat Walkthrough

## [HackTheBox](https://hacktheboxltd.sjv.io/19ZM06) Sherlocks: Meerkat Walkthrough

Hello everyone and welcome to my first Sherlock writeup! I’ve done a few other [HTB](https://hacktheboxltd.sjv.io/19ZM06) writeups before, but we’re going to start doing a few more of their Sherlock challenges. With the Holmes CTF fast approaching I figured this was a good time for all of us to brush up on our blue teams skills and start doing some investigating.

## What Are Sherlocks?

Sherlocks are a [HacktheBox](https://hacktheboxltd.sjv.io/19ZM06) ([HTB](https://hacktheboxltd.sjv.io/19ZM06)) challenge type that more so revolve around digital forensics, network traffic analysis, malware analysis and so on. These are CTF’s that more so challenge your blue team skillset than your ability to root a box. With the majority of jobs in cyber security being blue team I think doing these are a worth while investment to showcase and develop your skills. Now with that being said, let’s get right into it.

## Starting the Challenge

So to actually start the Sherlock, all you need to do is log into [HTB](https://hacktheboxltd.sjv.io/19ZM06) Labs and on the left side of the page there’s that main menu there with a tab called Sherlocks.

After clicking into that you can see all of the Sherlocks currently available, either retired or active. As we’re doing Meerkats today, we are just gonna type Meerkats in the search bar and start working on that.

After clicking into Meerkats and scrolling down we see a few different important things.

In the top write here we see the official writeup (in case you don’t like mine), we also have the scenario for this Sherlock which has a being the new security provider for this company. It also says they want us to analyze some PCAP and log data to determine if a security breach has occurred. Then at the bottom there we see the first question we need to answer. Well, no time to waste, let’s download and unzip the provided file and let’s get to it!

## Task 1

Alrighty so after downloading that zip file and running `unzip` on it we get two files, `meerkat-alerts.json` and `meerkat.pcap`. Side note, you will need a password to unzip the file, the key icon on the Sherlock menu page will give you said password. I think the first thing we're gonna do who is crack open the pcap file with Wireshark and start drilling into that. Assuming you have Wireshark installed go ahead and fire that up and open up our pcap.

Okay, after scrolling down just a hair we see something pretty suspicious almost immediately.

This to me almost certainly looks like we got some port scanning going on. If you click on each SYN request you can see the port number change to common ports each time and these requests are all coming from the same source so this is already pretty nefarious I’d say. Now after scrolling down past all of the SYN, RST behavior we finally start to see some different traffic and one of the first things we see is an HTTP GET request to the following endpoint.

It looks like Bonita is the service they are running here on port 8080, but that doesn’t look like the answer that HTB is looking for. Now maybe if we search the log file and look for the string Bonita we’ll find something that could help us. Now full disclosure, there is surely a better way to do this than what I did, but I put the .json file into Vim ( `vim meerkat-alerts.json`) and once in Vim typed `/Bonita` to match that string. This is what I found.

Here we see the name of the software is actually Bonitasoft and also the CVE used to exploit the vulnerability. The string Bonitasoft does look like that could be right so let’s see…

Awesome, one down and a bit of a ways to go still, but we got this.

## Task 2

Alright so this task is asking us to determine what subsect of brute forcing the attacker(s) were using in order to try and compromise an account. Now right off the bat the two options that come to mind here are Credential Stuffing vs Credential Spraying.

### Credential Stuffing vs Credential Spraying

While they are both forms of account brute forcing they are not quite the same thing. For Credential Spraying think of it as going for the low hanging fruit as this technique involves trying a few different common passwords across a lot of different accounts. So in our pcap if we see a lot of different login attempts with different users, but with a lot of repeating simple passwords (password, abc123, passw0rd, etc. I think you get it) then we can be pretty confident about it being Credential Spraying. Credential Stuffing on the other hand involves credentials typically stolen or acquired in a data breach and trying to use those on user accounts. So it’s very possible in Credential Stuffing we will see lots of login attempts, yes, but with maybe slightly more unique passwords as the attacker is trying to use credentials acquired from somewhere else and trying to login with those.

### Back to Task 2

Now that we know the difference, let’s find some login attempts in Wireshark and see if we can determine the difference.

Okay see here we can see a few of these HTTP POST requests to this /bonita/loginservice endpoint which is where this brute forcing attack is occurring. In Wireshark let’s go ahead and click on one and drill down into what’s going on here.

Now at the bottom left of your Wireshark you should see something like the above. Under this HTML form section we can see the credentials used in the login attempt and I gotta be honest that password looks pretty unique, which as we discussed earlier is more indicate of a Stuffing attack than a Spraying one. Now as a quick note, the reason we can see these credentials is because the web server running this application is not using HTTPS so all the network traffic is unencrypted. This allows us to see pretty much everything going on in this conversation which ends up working out for us in this case, but is obviously a very big security vulnerability in it of itself. Any how, let’s see if our hunch is right.

Hooray! We’re moving right along now, let’s keep it up.

## Task 3

Huh, wait a minute… Didn’t we see something about a CVE when we were looking at something else earlier?

Oh my goodness that’s right, our meerkat-alerts.json file had that in there. Well hopefully this was an easy one?

## Get KarmicDragoon92’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Woo, easy one, very nice.

## Task 4

Interesting, so an API endpoint was exploited with some authentication bypass technique. Well, we’re definitely going to be looking through our pcap to find evidence of that, but for the sake of curiosity let’s just google this CVE and learn a little more about this exploit.

Yep that looks like it to me.

Welp, there it is. Like there it is, that’s the answer. Now, with the being said and all we still need to do our due diligence so let’s go actually find evidence of this being exploited in our pcap file.

SO if we scroll down in Wireshark a little bit, passed all the brute forcing behavior we’ll eventually see some nasty looking API abuse. So first and foremost yeah, right at the top there we see that string being used to bypass auth into privileged API access so we know for sure now that’s what’s going on here. To explore it a little more though, we can even see the specific commands being run by the attacker in that GET request there. If you right click that GET request and then Follow -> HTTP Stream and then scroll down towards the bottom we see…

Ruh roh. Okay, that’s enough for now, let’s submit our answer.

## Task 5

Alright, this one is fairly straight forward. Just how many authentications attempts occurred during the Credential Stuffing attack? To make this fairly simple we can go back to of the POST requests to the login endpoint, right click one of them and Apply as Filter like so:

Now after applying that POST request as our filter we should only be seeing POST requests to our login endpoint. There should be 118 results displayed to you right now, but that is not our answer. If you’ve been following along a click around you may have found a few different occurrences of the login install:install. As we are trying to find out the amount if legitimate login credentials we want to filter these out. So similarly to how we filtered *for* our POST request we can filter out this login. So find a request with install as the login parameters and then go down to the bottom left of Wireshark.

This time when hovering over Apply as filter though we need to select `and not selected` in order to keep our original query parameter and filter out the install login. Doing that should leave you with 59 results, definitely the answer right? Nope not quite yet, we're also looking for unique logins so no repeats. I am kind though, I won't make you click through every entry, at the bottom there are three logins with the same credentials:

Bringing our grand total to…

Now you would think it would be 57 as I one occurrence of this login should count as a unique entry, but ssshhh it’s fine, don’t think about it too hard.

## Task 6

Probably the repeating one yeah? In all seriousness, yeah definitely, but to do our analysis still if we right click on the first login with these credentials and follow the HTTP stream again we see that these credentials were used and then immediately the API bypass exploit was used so it definitely seems like this is our culprit.

Bam, too easy.

## Task 7

Mmm interesting, well this could be a little tricky. What text sharing site did they use? Well we could be digging around this pcap a while-

Oh well how about that. In all seriousness what we do see almost half way down the pcap is a few more logins with our compromised account and then continued exploitation of the API endpoint. One of which is a wget command which causes a DNS lookup to pastes.io which seems like our culprit.

Bingo. Hang in with me we’re almost there!

## Task 8 (and 9)

Ah, so the attacker sets up SSH key persistence somewhere huh? Okay so this one seems trickier than it is. So staying where we’re at in Wireshark we still see the DNS requests following the wget command run via the RCE exploit. Now if you want you can scroll down till you see the exploit get run again to execute this command `bash bx5gcr0et8`. Which if you end up following that HTTP stream you see it downloads something and then after that if you keep scrolling everything becomes SSH traffic making it much harder to tell what's going on. Now it's pretty obvious that bx5gcr0et8 is a bash script, but where did it come from. Well, to be honest, I spent a little too long trying to find that out considering wget is most commonly used to? That's right download things from websites, oh my lord ding ding gind. Sorry, this one stumped me longer than it should have. As a matter of fact, if we ourselves navigate to the URL that wget requested we see this.

Which not only gives us the files created for persistence, but also stores it in the authorized_keys file, which happens to also Task 9 which is `What file is Modified` (more or less) so...

ONE MORE, we’re almost there, let’s finish strong!!

## Task 10 (Final)

Well this shouldn’t be too bad. We know the technique the attacker used was establishing persistence with SSH public keys by modifying the authorized_keys file via a BASH script downloaded from somewhere else. Well let’s head over to [MITRE ATT&CK](https://attack.mitre.org/) and see if there’s an entry that sounds like what we’re dealing with.

So under the Persistence section -> Account Manipulation we see T1098.004, SSH Authorized Keys.

BOOM and just like that, you’ve solved your first [HTB Sherlock challenge](https://hacktheboxltd.sjv.io/19ZM06), let’ssss goooooooo!!

---
