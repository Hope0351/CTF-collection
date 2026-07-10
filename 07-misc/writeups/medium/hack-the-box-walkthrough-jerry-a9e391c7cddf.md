# :game_die: Hack the Box Walkthrough: Jerry. And here we are back to the Intro to…

> **Original Source:** [Hack the Box Walkthrough: Jerry. And here we are back to the Intro to…](https://infosecwriteups.com/hack-the-box-walkthrough-jerry-a9e391c7cddf)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Hack the Box Walkthrough: Jerry


And here we are back to the Intro to Red Team track here on Hack the Box. Today we’ve got an easy Windows box. We’re going to be trying from here on out to do as much in adventure mode as we can, only really switching to guided if we’re really stuck. So without anymore yapping from me, let’s get into todays box.

## NMAP scan results


Looks like we have an Apache Tomcat running on probably Windows Server 2012? Let’s go ahead and navigate to the URL.

## Checking the URL


Here we see what looks like a fresh install of Tomcat 7.0.88. Let’s go ahead and maybe do some quick googling to see what exploits may or may not be available to us.

## CVE-2019–0232?


After a little bit of googling we get a few interesting CVE’s.


[CVE Details](https://www.cvedetails.com/vulnerability-list/vendor_id-45/product_id-887/version_id-786653/year-2019/opec-1/Apache-Tomcat-7.0.88.html)


[NIST vulnerability Database](https://nvd.nist.gov/vuln/detail/cve-2019-0232)


Looks like a potential attack vector, RCE when running on Windows?


Okay so after doing a little bit of [reading](https://wwws.nightwatchcybersecurity.com/2019/04/30/remote-code-execution-rce-in-cgi-servlet-apache-tomcat-on-windows-cve-2019-0232/) this CVE requires that the /cgi-bin is one accessible and two has some .bat files in it. Due to how some Windows API things read arguments we can get RCE, but long story short /cgi-bin is not accessible here and we obviously don’t have access to reconfigure anything there or even view it. Speaking of viewing what can we view. Maybe we should focus on continuing to explore the application rather than immediately trying to find an exploit.

## Back to Exploring the Web Page


On the landing page there’s the Manager App can we get into there?


Crap, uh, admin admin?


Damn. And this is one of those things where you gotta close the browser to try a different logon so this is annoying. Tried tomcat tomcat, apache apache, admin password, apache tomcat. Huh what could it be? You don’t think maybe the web server admins just used the example creds?


## WAR Files


We have this file upload utility here that accepts a WAR file type? Not quite sure what that is… After doing a little bit of looking around I found this [article.](https://medium.com/@mingihongkim/exploiting-java-portlets-with-a-malicious-war-file-to-gain-a-reverse-shell-2504909f71c1) Essentially a WAR file is a Web ARchive file that has some Java type objects inside, some html/css and a web.xml file (typically). So, we should be able to craft our own malicious WAR file, upload it and then get a reverse shell from that, at least in theory. Below is the code from the article that should work?


## Get KarmicDragoon92’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Let’s craft our WAR package. Specific instructions are in the article mentioned above.


So when trying to compile the java it seems like we don’t have that right packages installed? We could go through and try to get this working, but I feel like there’s an easier answer. And after doing a little bit more digging I found that we can just do all of this with [MSFvenom.](https://www.linkedin.com/pulse/exploit-elevate-reverse-shells-action-msfvenom-jason-passarelli-uscof)


If you’re not familiar, MSFvenom is a payload generator developed by the same people who made/own Metasploit? One or the other, but I use this a lot when developing shellcode exploits for any binary exploitation I get up to, so with that being said.


Let’s try it


Hit deploy


Now that we got that uploaded, what we’re going to want to do is set up our netcat listener and then navigate to the URL our malicious WAR file is located and after we do all that…


## System Exploration


And there we have it. Alright time to start poking around the file system, what’s going on inside our current directory?


Long story short, there’s nothing here of interest. Note to myself you gotta be able to dig into every where in order to find what you’re looking for. And by everywhere I mean the most probable place which is in the \Users directory and checking any users home directories or the Admin home directory, which in this case we can and we see this wonderful file.


Which conveniently has both of our flags in there.


## Conclusion


This was a very simple box as long as you just kinda observe what you have in front of you and don’t think about it too hard. That’s kinda what I took away from this one, instead of immediately trying to look for CVE’s and getting sent down those rabbit holes, sometimes it’s simpler than you think. And with that being said, thank you so much for joining me for this one and I will see you next time.

---

*Originally published on [Medium](https://infosecwriteups.com/hack-the-box-walkthrough-jerry-a9e391c7cddf). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
