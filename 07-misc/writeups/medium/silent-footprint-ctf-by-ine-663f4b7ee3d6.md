# :game_die: Silent Footprint CTF by INE. INE’s Network Pentesting CTF · Medium ·…

---

## Flags : step‑by‑step walkthrough

>

*Note: below are the commands and the reasoning I used. Replace *`*192.x.x.`* with the real lab IPs when reproducing.*

## Flag 1 : SMB public share

While enumerating ctf.playground.ine I initially found only three TCP ports open and no web page or other obvious entry points also no UDP ports found.

Initial service scan
Command:

```
nmap -sV ctf.playground.ine
```

Output:

```
Nmap scan report for ctf.playground.ine (192.x.x.4)
Host is up (0.000031s latency).
Not shown: 997 closed tcp ports (reset)
PORT STATE SERVICE VERSION
1234/tcp open hotline?
5678/tcp open rrac?
9101/tcp open jetdirect?
MAC Address: 02:42:C0:F5:71:04 (Unknown)

Service detection performed. Please report any incorrect results
Nmap done: 1 IP address (1 host up) scanned in 6.48 seconds
```

Remembering that CTFs often use port knocking to reveal additional services, I attempted a knock sequence.

### Overview — Port knocking

What it is : *Port knocking is a stealthy method to hide a service behind a closed port by requiring a specific sequence of connection attempts (the “knock”) to predetermined ports. When the correct sequence is observed, a daemon or firewall rule temporarily opens a port (e.g., SSH) for the knocking host.*Why people use it:

- Adds an extra *authentication* factor before a service is even visible.

- Reduces attack surface by keeping services invisible to casual scanners.

- Useful in CTFs and small deployments where convenience beats complexity.

How it works:

- Client sends connection attempts to a sequence of ports (TCP/UDP) in the correct order (or using encoded payloads).

- A listener (knockd, fwknop, or a firewall script) monitors packet logs or raw sockets.

- If the sequence matches, the listener modifies firewall rules (e.g., iptables) to allow the client’s IP to access the protected service for a limited time.

Simple example (user-side):

```
knock -v target.example.com 7000 8000 9000 tcp
```

Example (knockd) config snippet:

```
[options]
UseSyslog

[openSSH]
sequence = 7000,8000,9000
seq_timeout = 5
start_command = /sbin/iptables -A INPUT -s %IP% -p tcp --dport 22 -j ACCEPT
cmd_timeout = 30
stop_command = /sbin/iptables -D INPUT -s %IP% -p tcp --dport 22 -j ACCEPT
```

Common tools:

- `knock` (client)

- `knockd` (daemon)

- `fwknop` (port knocking with single-packet authorization — more secure)

- firewall tools: `iptables`/`nftables` for rule changes

Port knock attempt
Command:

```
knock -v 192.x.x.4 1234 5678 9101 tcp
```

Output:

```
hitting tcp 192.x.x.4:1234
hitting tcp 192.x.x.4:5678
hitting tcp 192.x.x.4:9101
Failed to resolve hostname '192.x.x.4' on port tcp
getaddrinfo: Servname not supported for ai_socktype
```

Note: If you want a detailed write-up on port knocking, including a lab setup and both offensive and defensive perspectives, let me know in the comments. If i get more comments i will prepare a full walkthrough.

- After the knock, I rescanned the target.

Follow-up scan
Command:

```
nmap -sV ctf.playground.ine
```

Output:

```
Nmap scan report for ctf.playground.ine (192.x.x.4)
Host is up (0.000027s latency).
Not shown: 996 closed tcp ports (reset)
PORT STATE SERVICE VERSION
445/tcp open netbios-ssn Samba smbd 4.6.2
1234/tcp open hotline?
5678/tcp open rrac?
9101/tcp open jetdirect?
MAC Address: 02:42:C0:F5:71:04 (Unknown)

Service detection performed. Please report any incorrect results at https:
Nmap done: 1 IP address (1 host up) scanned in 6.36 seconds
```

How I discovered it
The Samba service on port 445/tcp appeared after the port knock, the second Nmap scan showed netbios-ssn (Samba smbd 4.6.2) open on `ctf.playground.ine`

### SMB enumeration

- Enumerating the SMB service

Command:

```
smbclient -L ctf.playground.ine
```

Output:

```
Password for [WORKGROUP\root]:

Sharename Type Comment
--------- ---- -------
public Disk
IPC$ IPC IPC Service (Samba 4.19.5-Ubuntu)
Reconnecting with SMB1 for workgroup listing.
do_connect: Connection to ctf.playground.ine failed (Error NT_STATUS_CONNECTION_REFUSED)
Unable to connect with SMB1 -- no workgroup available
```

>

*Note: *The scan showed a `public` share available. The SMB client attempted an SMB1 fallback for the workgroup listing but failed the share itself is still accessible anonymously.

2. Access the public share (no password required)

Command:

```
smbclient //ctf.playground.ine/public
```

Interactive Session Output:

```
Password for [WORKGROUP\root]:
Try "help" to get a list of possible commands.
smb: \> ls
. D 0 Tue Sep 30 15:54:26 2025
.. D 0 Tue Sep 30 15:54:26 2025
readme.txt N 28 Tue Sep 30 15:54:26 2025
flag.txt N 33 Tue Sep 30 15:54:26 2025
endpoint.txt N 35 Tue Sep 30 15:54:26 2025

1981311780 blocks of size 1024. 67619856 blocks available
smb: \> mget *
Get file readme.txt? y
getting file \readme.txt of size 28 as readme.txt (13.7 KiloBytes/sec) (average 13.7 KiloBytes/sec)
Get file flag.txt? y
getting file \flag.txt of size 33 as flag.txt (32.2 KiloBytes/sec) (average 19.9 KiloBytes/sec)
Get file endpoint.txt? y
getting file \endpoint.txt of size 35 as endpoint.txt (17.1 KiloBytes/sec) (average 18.8 KiloBytes/sec)
smb: \> exit
```

3. Seen `endpoint.txt` on the SMB share, which contained an application endpoint and credentials: `robert:password1` which became crucial for later web access.

```
robert/password1 for /?/ endpoint.
```

The `public` share allowed anonymous access and included `flag.txt`.

Flag 1: `3988bc2138f8c43f62d42bf620fbf5ff`

---
