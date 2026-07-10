# :game_die: Htb Academy Writeup Bdbd39D2F364

---

This was an easy difficulty box, and it involved multiple steps to fully gain root access on the box. Good learning path for:

- Access Control Bypass on Register Function on Webapp

- Laravel Token Unserialize RCE

- Linux Audit

- Composer Privilege Escalation

## Initial Recon

### Nmap

```
$ nmap -Pn --open -p- -T4 -sV -sC 10.10.10.215PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 8.2p1 Ubuntu 4ubuntu0.1 (Ubuntu Linux; protocol 2.0)
80/tcp open http Apache httpd 2.4.41 ((Ubuntu))
|_http-server-header: Apache/2.4.41 (Ubuntu)
|_http-title: Did not follow redirect to [http://academy.htb/](http://academy.htb/)
33060/tcp open mysqlx?
| fingerprint-strings:
| DNSStatusRequestTCP, LDAPSearchReq, NotesRPC, SSLSessionReq, TLSSessionReq, X11Probe, afp:
| Invalid message"
|_ HY000
```

- HTTP (80/TCP) — From the Nmap result, port 80 will be redirected to [http://academy.htb/](http://academy.htb/) . Once I updated my /etc/hosts file, I could hit the following HTB Academy website:

### Web Directory Enumeration (Dirsearch)

---
