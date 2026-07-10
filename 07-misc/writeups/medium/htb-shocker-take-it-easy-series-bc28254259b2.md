# :game_die: HTB- Shocker ( Take It Easy Series)

> **Original Source:** [HTB- Shocker ( Take It Easy Series)](https://infosecwriteups.com/htb-shocker-take-it-easy-series-bc28254259b2)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB- Shocker ( Take It Easy Series)


In the month of July, Hack the Box ( HTB) came up with a concept of making 10 retired machines available for all the users to pwn and build their skills. Please find the announcement from HTB.


As part of this series, I have started trying one of the retired boxes i.e., Shocker. These machines are available for free in retired machines


Let’s access the box and gain root access.


Basically, this is a Linux machine. We will run a Nmap scan to identify open ports and services.


*Nmap Scan*


The output shows that it’s an Ubuntu machine running SSH on 2222 and an HTTP Apache server on Port 80. So without any delay, open the browser and access the webpage.


Nothing in Webpage. Let’s take a look at the page source.


Nothing on the Source page too.


Now, use go buster to identify the hidden directories for a sensitive approach. Our main focus is on the directory showing status codes 200,403.


We can able to see the regular Index, Server status directories. Wait, along with that we got one more directory with the name CGI-bin.


When I tried googling to understand it, I got the below information that it is a type of folder to host scripts. Since it gave a 403 status code, let's do the directory enumeration in that dir to see if there are any scripts with which we can play.


```
A CGI-bin is a folder used to house scripts that will interact with a Web browser to provide functionality for a Web page or website. Common Gateway Interface (CGI) is a resource for accommodating the use of scripts in Web design. As scripts are sent from a server to a Web browser, the CGI-bin is often referenced in a url.
```


We got a hit. There is one shell script file named “user” in the CGI-bin directory. Surprisingly, Instead of executing in the browser, it gave a prompt to download.


When I run the script, it just shows the uptime of the server.


Now it’s time to exploit the machine. Based on the machine name and as it has CGI-bin, we can co-relate that it may be vulnerable to Shellshock vulnerability (CVE-2014–6271)detected in 2014.


## Get Adithya Thatipalli’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


There are two ways to exploit it.
1. Metasploit
2. Publicly available exploits( Command Injections)

## Root Access using Metasploit


Security researchers are not new to Metasploit. There are many exploits that can complete this task. Let’s run msfconsole and start exploring.


*MSF exploit with updated details( RHOST, RPORT TARGETURI)*


We got the meterpreter access. Now search for the flags and gain the root shell. Let’s see who all users we have in this machine.


There is one user in this machine called shelly who gave us the first flag.
Using Perl I have gained access to a bash shell and now I am root. Using root
I have access to 2nd flag.

## Root access using Public Exploits


We have multiple exploits available with working POC to exploit this vulnerability. Below is one of them which I am going to use here.


This is a python script to exploit and create a reverse shell. This requires the inputs like RHOST, RPORT, URL, LHOST, LPORT.


Once I feed the inputs, we can able to gain shell access. To gain root shell access, we use the Perl shell command. Once you are root, navigate to the folder and grab the flag.

---

*Originally published on [Medium](https://infosecwriteups.com/htb-shocker-take-it-easy-series-bc28254259b2). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
