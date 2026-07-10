# :game_die: Host & Network Penetration Testing: System-Host Based Attacks CTF 1 - eJPT (INE)

---

## Q. User ‘bob’ might not have chosen a strong password. Try common passwords. (`target1.ine.local`)

As usual, I started with an Nmap scan to identify the running services.

```
nmap -sV -sC -T5 target1.ine.local
```

*Nmap scan results*

The scan showed that port 80 was open running Microsoft IIS 10.0, but it returned a 401 Unauthorized — meaning it was protected by HTTP Basic Authentication. Ports 135, 139, 445 (SMB), and 3389 (RDP) were also open.

I navigated to `http://target1.ine.local` in the browser and it immediately asked for credentials.

*The site was asking for authentication.*

Since the question already hinted that Bob might have a weak password, I decided to brute-force his password using Hydra and a common password list.

```
hydra -l bob -P /usr/share/metasploit-framework/data/wordlists/unix_passwords.txt target1.ine.local http-get /
```

*Hydra Result*

Hydra successfully identified Bob’s password.

Now I had valid credentials. I logged in, I didn’t find anything useful on the homepage, so I moved on to directory enumeration with DIRB.

```
dirb http://target1.ine.local -u bob:<password>
```

*DIRB Result*

DIRB found two directories — `/aspnet_client/` and `/webdav/`. The WebDAV directory was listable, so I navigated straight to it: `[http://target1.ine.local/webdav/](http://target1.ine.local/webdav/)`

And there it was — `flag1.txt` sitting right in the directory listing.

---
