# :game_die: Crta Exam Writeup Passed Cyberwarfare Lab D55E776C82E7

---

## Phase 6 — Lateral Movement & Network Pivoting

## Discovering the Internal Network

Reading the SSH auth logs revealed connections originating from an internal IP:

```
cat /var/log/auth.log | grep "Accepted"
```

A recurring IP appeared: `10.10.10.20`

## Get Shikhali Jamalzade’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

This machine was on an internal network segment not visible from the exam’s initial VPN range. From the compromised host (`172.26.10.11`), this internal network was reachable.

## Enumerating 10.10.10.20

```
nmap -sV -p- 10.10.10.20 --min-rate 3000
curl http://10.10.10.20/
gobuster dir -u http://10.10.10.20 -w /usr/share/wordlists/dirb/common.txt
```

The `/elfinder` directory was discovered — a file manager interface.

## AD_Resources.txt

Inside the elfinder directory, a file named `AD_Resources.txt` was found containing Active Directory credentials:

```
sync_user@ent.corp / [REDACTED]
```

These credentials belonged to a domain user with replication privileges — the key to DCSync.

## Domain Controller at 10.10.10.100

With domain credentials in hand, targeting the DC:

```
nmap -sV -p 445,88,389,636 10.10.10.100
```

Confirmed: `10.10.10.100` is the Domain Controller for `ent.corp`.

---
