# :game_die: Oubliette: A CTF Machine Walkthrough

---

# Oubliette: A CTF Machine Walkthrough

This CTF machine was used by Cyber Secured India for conducting a practical exam for their interns of batch 13th August 2023 to 14th October 2023. We had to find the user flag and root flag.

You can download the machine from the drive link given below:
[https://drive.google.com/file/d/1lRZeesju6PfJ93QvuuGdlEw8tDIXp0NZ/view?usp=drive_link](https://drive.google.com/file/d/1lRZeesju6PfJ93QvuuGdlEw8tDIXp0NZ/view?usp=drive_link)

You can use VirtualBox or VMware to open the .ova file. I suggest using VirtualBox for opening the CTF machine.

So, after downloading the machine and setting it, start the machine.

On starting the machine, you can see the interface like this:

*Obuliette*

So, the first step is to find the IP address of this machine.
We can do this by using [Angry IP Scanner](https://angryip.org/download/#windows).

Click on “Start” to start the scan.

The IP with green color is our machine IP.
Now, start your kali Linux.
Open a terminal and run an Nmap scan on it. The results:

As we can see, there are 4 ports open for this machine.
As the http port(80) is open. Let’s see what we get in it.

Do a gobuster scan on this side by side:
gobuster dir -u http://[YOUR_IP] -w /usr/share/wordlists/dirb/common.txt

As the gobuster scans the webpage to find the directories, let’s see the webpage.
Using the signup page make an account.

After signup, use the credentials to log in. After login, you will get an index.php page:

Nothing useful here.
Now, let’s see the gobuster results:

We have a robots.txt, note, dev and /.htaccess
On accessing the robots.txt:

We get a flag.html, but it’s not an actual flag.
On accessing the /note:

We have a user called Dave now.

On accessing the /.htaccess:

We can see a path-/dev/l33t_lfi.php

Let’s see what we get here.
On accessing this file:

We can see the page has a button “Press Me :)”.On clicking this button, we get:

On the url we have: “?fetch=/var/www/html/dev/index.html”

Now instead of /var/www/html/dev/index.html, let’s try to access “/etc/hosts”.

It seems we have gotten an LFI here.
But on trying to access the /etc/passwd, you will get a message in the webpage:
Alert! LFI attempt detected by firewall, you cannot proceed.Your IP [ip] is being logged.

It seems there is a filter that is being used to block LFI.
On trying to access more such files, I was able to understand the following:
1. You cannot use ‘../’ in the ?fetch= param
2. You cannot view the /etc/passwd or /etc/shadow file.

But, if we type “/etc/passwd-”, we are able to see the contents of it.

It seems the webpage filters the query to make sure it doesn’t include some specific files.

On going through the internet on how to bypass a such a filter, I found this:

## Get Vedant Pillai’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Local File Inclusion (LFI) — Web Application Penetration Testing | by Aptive | Medium

On using this, I got the file “/etc/passwd” in base64 encoded form.
So, I was able to directly get the contents of any file in base64 encoded form. So, I decided to get the code of “l33t_lfi.php”.
Paste this:

http://[MACHINE_IP]/dev/l33t_lfi.php?fetch=php://filter/convert.base64-encode/resource=/var/www/html/dev/l33t_lfi.php

We will get the code of l33t_lfi.php in base64

Copy it and use a base64 decoder to decode the content.
[Base64 Decode and Encode — Online](https://www.base64decode.org/)

On decoding, we get:

So, now we have the PHP code of l33t_lfi.php

As you can see there are files that is blacklisted:
1. /etc/passwd
2. /etc/shadow
3. /var/www/html/dev/phpinfo.php
4. /srv/ftp/…/-
5. /proc/self/environ

On viewing and decoding the /srv/ftp/…/- :

It seems we have got the contents of some id_rsa file.

Copy this id_rsa content and create another id_rsa file in your kali.
Change the permissions of this id_rsa file:

```
chmod 400 id_rsa
```

My guess was that this is of user Dave and it seems I was right.
Access the machine through the ssh:

```
ssh dave@[MACHINE_IP] -i id_rsa
```

Use the ls -la command to list all files and directories

We can see a file called “.fl4g.txt” file which seems to contain the user flag.

*User flag*

We have successfully found the user flag.

Now, we have to find the root flag.

On using “sudo -l”, we are being asked for password. It seems Dave is not allowed to use sudo.

Paste this command:

```
find / -type f -perm /4000
```

This command is used to find all files across the entire filesystem that have the SUID bit set, which is often used for special permissions and can potentially be a security risk if not properly managed.

Output:

On using [GTFO bins](https://gtfobins.github.io/), we get to see something interesting for “gawk”:

It seems we can bypass the local restrictions to read or write a file.

I was stuck here for a lot of time, trying to get the file. I tried to write the sudoers file, but that didn’t work well.

So, I decided to go with names that can be used for the file storing the root flag.

I made quite a lucky guess thinking that the name of user flag and root flag would be the same. I was correct for that guess.

Run this command to read the root flag:

```
LFILE=/root/.fl4g.txt
gawk '//' "$LFILE"
```

Output:

*Root flag*

We have successfully found the root flag as well.

Note: This isn’t the only way to solve this machine. If you look in https://[MACHINE_IP]:8080, you get an OpenEMR Login page. The version of OpenEMR is vulnerable to Remote Code Execution and it’s exploit can be foound in db-exploit.

---
