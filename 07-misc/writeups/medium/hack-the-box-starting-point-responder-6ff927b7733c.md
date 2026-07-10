# :game_die: Hack the Box Starting Point: Responder

---

# Hack the Box Starting Point: Responder

Hello and welcome back to the little Starting Point series I’ve been doing on the HacktheBox main platform. Today we’re going to be looking at the Responder box which definitely looks interesting. Just peaking at the questions ahead of us we’re going to be dealing with some stuff that I haven’t touched too much. Yeah we have some web stuff, but it looks like it may be hosted on a Windows server? It also looks like (per the name) we may be using responder to do some nefarious things.

## What is Responder?

Responder is another security tool that we’ll be using in this engagement and it’s main purpose is to capture credentials on the local network. It does this by impersonating legitimate network services and then responding to clients before the real network service can and therefore getting in the middle of all of those communications. I apologize if that’s not the best explanation, feel free to refer to [this post here](https://hunt.io/malware-families/responder) if you’d like a little more info. With that all being said though, let’s go ahead and fire up our attacking machine of choice and get after it.

## Task 1

Well, seems like an easy enough first task, let’s fire up our web browser and check it out.

Hmmm, so after just entering the IP address of the target in our browser we get brought to the page above. Now, it appears the site is having trouble rendering for some reason, but we see we’ve been redirected to `[http://unika.htb/](http://unika.htb/.)`[.](http://unika.htb/.)

## Task 2

Now, we all probably have a feeling we know what the answer here is, but let’s do our due diligence. We see that the web page is struggling in the browser, let’s see if we can get a little more information from the command line.

In the HTTP response under the Server header we see a lot of info actually. The target web server is running Apache, is a Windows 64 bit system and is using the PHP scripting language. Now, we had a feeling about this, but it’s always important to verify.

## Task 3

Alright, well now we’re going to need to fix the connection issue when we’re trying to vaigate to the website. Just for curiositites sake let’s try adding the targets IP to our /etc/hosts file and see if that maybe fixes it.

Here you can see that at the bottom of the file I’ve added the IP and domain name of the host we want to be able to navigate to. Do remember /etc/hosts needs root priviliges to edit. Now that we’ve added that, let’s go ahead and try going to the target URL again.

Awesome, there we go. Now time to actually answer the question. There’s not a parameter currently in the URL that looks like we can modify, but it can’t help but notice on that menu bar there it looks like we can change our language. We can hover over it and select between French and German, I’m going to select German.

And there in the URL we see `index.php?page=german.html` so the page parameter is what sets the language.

## Task 4 and 5

So for these two tasks we’re not exploiting anything yet, just understanding the difference between Local and Remote File Inclusion Vulnerabilities. The idea behind both is the same though, by abusing poorly configured web applications we are able to call other files via different parameters on the target. The only difference is for Local you are abusing some kind of path traversal bug in order to read local files where as Remote you are suppling the URI of a remote file from somewhere else. So going to our first question here. `french.html` and `mimikatz.exe.` are just two files the only one that has any directory traversal even in it is the file path ending with /etc/hosts so... For the second question, you can just tell it's a Remote File Inclusion (RFI) as we can see that there is a path to a remote host and that will be our answer this time. If you want to read up more on RFI and LFI I would maybe take a peak [here](https://www.geeksforgeeks.org/computer-networks/difference-between-rfi-and-lfi/).

## Task 6

NTLM stands for `New Technology LAN Manager` and is an authentication protocol used in Widnows Environments. There's a post from [CrowdStrike](https://www.crowdstrike.com/en-us/cybersecurity-101/identity-protection/windows-ntlm/) if you want to read more about it. For our purposes though, it's important to know that NTLM uses a client-server model that performs a kind of three way handshake challenge with the client. This is what Responder is going to be looking for when we use it here in just a moment.

## Task 7

Alright, time to start getting some hands on with responder let’s check it’s help utility to see how it works. Running `responder -h` gives us the help we're looking for.

## Get KarmicDragoon92’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So the`-I` flag is what we'll use to specify the interface we want to run Responder on.

## Task 8

The hash cracking tool being referenced here is John the Ripper, a very popular password cracking tool that you should definitely be aware of if you’re not already. Now we’re starting to see how this attack is going to work a little bit. NTLM passes password hashes over the network, not jusst plaintext. So we need to use responder to capture that hash and then crack it with John the Ripper. How do we go about actually forcing the target to try to authenticate to our NTLM server?

## Task 9

Okay, so full transparency, I referenced the official writeup here as I was note exactly sure how to leverage the RFI vulnerability to cause the web server to initiate NTLM authentication. But to be honest this is pretty cool. First things first though, we are going to want to start Responder on out tun0 interface (the interface connected to the HTB lab).

Okay awesome, we have responder set up. Now here’s the cool part, Responder is running opened a few different ports so it can listen for a dew different kinds of authentication and one service it’s spoofing right now is SMB. SMB being a network file share, allows us to abuse the RFI vulnerability to make the web server request a file from our machine using SMB which uses? NTLM to authenticate that’s right so…

So we inject our RFI payload into the vulnerable URL parameter and after hitting enter…

We see that the web server throws an error about not having permissions to access our placeholder file, so it tried to authenticate… So if we look at our running Responder.

Beautiful. Okay awesome, we have our file hash, time to use John the Ripper. First things first is we’re going to want to save that hash to a file.

Awesome. Now John can brute force things, but most of the time we’re going to want to use a word list like so.

And we see the password is `badminton`. Awesome, we have our creds, but where are we logging into?

## Task 10

Well we should all know what to do here.

We see a service running on 5985, Microsoft HTTPAPI or more commonly referred to as WinRM or Windows Remote Management. As the name implies it’s another method of remotely administering Windows systems. Let’s try logging into there with our stolen credentials. To interact with that service we will be using a tool called evil-winrm.

## Root Flag and Conclusion

Uh oh…

And under the user mike’s Desktop directory we see our flag.

This box was great, I learned a lot and it’s really cool to start to see some of these different exploit techniques be used together now instead of us just finding an open port and finding a flag. Hope you all enjoyed and I’ll see you next time!

---
