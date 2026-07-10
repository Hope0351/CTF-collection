# :game_die: Hack the Box Starting Point: Three

> **Original Source:** [Hack the Box Starting Point: Three](https://infosecwriteups.com/hack-the-box-starting-point-three-f053c830e556)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Hack the Box Starting Point: Three


Hello everyone and welcome back to the HTB Starting Point series I’ve been working on for way too long now. Took a little break for the Thanksgiving weekend, I hope everyone enjoyed themselves. Now however it is time to get back to work and so today we will be working on the next machine here in Tier 1. While we were away it looks like the main HTB platform has undergone some UI changes and so we don’t really get a sneak peak as to what we’ll be doing anymore, which honestly is totally fine, let’s spin up our respective attack machines and get to work!

## Task 1


Well, we all know the drill here.


Very good, just a couple ports open here, we’ll probably check out that web server here in a second.

## Task 2


Again, very straight forward. If we navigate to the targets URL…


It looks like the webpage for a popular band. Sure thing, let’s go to the Contact section and find that email.


And there we have it, so far so good let’s submit the domain of that email as our answer.

## Task 3


Okay so the answer to this question is the /etc/hosts file on our Linux boxes. I believe we messed with this just last box, but as a refresher. When our computers attempt to resolve IPs to URLs they will first reference their own configured hosts file. On Windows this file is found at `C:\Windows\System32\drivers\etc\hosts` and we can hardcode IPs to whatever domains. Because our computers reference these local files first before making any kind of DNS queries we could theoretically set it to whatever. Let's add our newly discovered domain to our /etc/hosts file so that it should look like this.


So now if we navigate to that URL…


Very good.

## Task 4


Alright, let’s do ahead and do some sub-domain enumeration using gobuster… Okay, truthfully this step wasn’t quite as simple as I suspected. If you go ahead and try to use gobusters fuzz command or use ffuf you’re not gonna find anything which I thought was odd. Turns out this domain is using Virtual Hosting, which just means the web server is hosting multiple subdomains. In order to do this we are actually going to use the vhost command in gobuster.


Ah so that’s why this box is called Three. Looks like we have an AWS S3 bucket here. We’ll check that out here in just a second, let’s submit our answer first.

## Task 5


Okay, I actually haven’t messed with AWS stuff at all actually so I’m going to be doing a lot of learning as I go this time. If we visit the s3 subdomain in our browser, we’ll see:


Very cool. Well if we google for a “status running s3 subdomain”…


We see the Amazon S3 Storage Service, which yeah that’s pretty obvious now when you just think about it. In fact so much so that in that other writeup there that’s probably a little better than this one our friend Ch0rum even make a comment. Okay, anyways Amazon S3, right, moving on.

## Task 6


If we just google this question we’ll get our answer.


## Get KarmicDragoon92’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


While all of these are true, the one we’re looking for is awscli. Using this command allows us to interact with the S3 bucket and get up to some shenanigans. If you just type aws into your shell with no arguments gives us some information.


Very nice.

## Task 7


Now what we’re looking for here is `aws configure`, this command sets a bunch of parameters we're going to need in order to actually use awscli.


You see here it asks for a bunch of values, luckily they don’t need to be legit, but they need to be something so this should suffice…


There, now we’re configured and should be ready to interact with the S3 bucket.

## Task 8


So the command we need to use to view the contents of the bucket is going to be `aws --endpoint=http://s3.thetoppers.htb s3 ls s3://thetoppers.htb`.


We see here an image directory as well as a php file. Well knowing that this is a php web server maybe we can do a php rev shell? Oh also, technically the answer to the question is going to be `aws s3 ls` as that's technically the command we ran, we just added a bunch of parameters to it.

## Task 9


… Like I said, php.

## Root Flag


Okay let’s go ahead and try our rev shell theory by using awscli to upload a php file to the web server.


Okay, let’s send this bad boy over to the S3 bucket.


Okay, let’s give this a shot. If we navigate to where our php script should be in our browser and give it an argument…


You see me here referencing the script in the URL and giving cmd a value of id, which runs the id command and voila, there we have it. Okay now for the moment of truth, let’s make ourselves a little Bash reverse shell and have our target server curl it on over.


Paste this into a .sh file and name it something using your desired text editor. Obviously change your IP and desired port number you want netcat to listen on. Okay after that’s done we’re going to…


Run a Python HTTP server on our attacking machine and also


Set up our netcat listener. Okay everything should be in place, let’s go back to our compromised URL and…


Note: For spaces in your URL payload you’re going to want to use %20 instead of a space as the browser won’t like that and %20 is URL encoding for a space so just do that instead and the browser will interpret that correctly. Anywayssssss…..


## Conclusion


Not gonna lie, this one was tougher than I thought it was going to be. I haven’t messed with AWS too much and so I was referencing the official writeup quite a bit. Also that vhosts thing had be stuck for a while I wasn’t sure why ffuf and gobuster weren’t getting any hits even though we added the target domain to our hosts file. Just show how much further we’ve got to go here, thank you all so much for joining me. Again, hope you all had a good Thanksgiving and onto the next one!

---

*Originally published on [Medium](https://infosecwriteups.com/hack-the-box-starting-point-three-f053c830e556). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
