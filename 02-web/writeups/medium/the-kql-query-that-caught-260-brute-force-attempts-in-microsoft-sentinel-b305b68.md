# :globe_with_meridians: The KQL Query That Caught 260 Brute Force Attempts in Microsoft Sentinel

> **Original Source:** [The KQL Query That Caught 260 Brute Force Attempts in Microsoft Sentinel](https://infosecwriteups.com/the-kql-query-that-caught-260-brute-force-attempts-in-microsoft-sentinel-b305b68afb69)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## The attack


I’m building a Microsoft Sentinel enterprise lab — two endpoints (Windows 11 and Ubuntu 22.04) connected to Sentinel via Azure Arc, with a Kali Linux VM acting as the attacker. For this simulation I ran Hydra against the Ubuntu server’s SSH service — the same tool real attackers use against any Linux server exposed to the internet.

>

The numbers: 260 failed attempts across 3 attack waves over 28 minutes. 0 successful logins.


Each failed attempt produced a Syslog entry like this:


*What a single brute force attempt looks like in raw Syslog*


```
Facility: authpriv
SyslogMessage: Failed password for ronak from 10.0.0.100 port 54321 ssh2
Computer: ronak
TimeGenerated: 2026-04-22T05:05:14Z
```


One of these is noise. 260 in 28 minutes from the same IP is an attack. The challenge is making Sentinel tell the difference automatically.


*260 failed SSH authentication attempts from Kali Linux (10.0.0.100) flowing into Sentinel in real time — all captured in the Syslog table.*

## The KQL detection rule — every line explained


*SSH Brute Force Detection — Full Analytics Rule*


```

Syslog
| where Facility == "authpriv"
| where SyslogMessage contains "Failed password"
or SyslogMessage contains "authentication failure"
| where Computer == "ronak"
| summarize FailedAttempts = count()
by Computer, HostName, bin(TimeGenerated, 5m)
| where FailedAttempts > 10
```


`Syslog`


Start with the Syslog table — this is where all Linux authentication events land after the Azure Monitor Agent ingests them from the Ubuntu endpoint.


`| where Facility == "authpriv"`


Filter to authentication events only. The `authpriv` facility captures SSH, sudo, and PAM authentication. This cuts all the noise — cron jobs, kernel messages, service logs — in one line.


`| where SyslogMessage contains "Failed password" or "authentication failure"`


Two conditions because SSH produces two different failure messages. “Failed password” fires when the user exists but the password is wrong. “Authentication failure” fires for invalid usernames. A real attacker generates both — you need to catch both.


`| summarize FailedAttempts = count() by Computer, HostName, bin(TimeGenerated, 5m)`


This is the most important line. `bin(TimeGenerated, 5m)` groups events into 5-minute buckets and counts them. Without this, you alert on every single failure — 260 individual alerts that create noise and hide the pattern. With it, you get one number per time window that immediately shows the rate of attack. This is what makes it a rate-based detection instead of a per-event alert.


## Get Ronak Mishra’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


`| where FailedAttempts > 10`


The threshold. A legitimate user mistyping their password fails once or twice. 10 failures in 5 minutes from the same source is automated tooling, not a human. In my lab, the attacker hit 48 in the first wave alone — this fired almost immediately.


*The analytics rule in Sentinel — High severity, MITRE T1110.001, runs every 5 minutes. Query results confirm detection logic works against real attack data.*

>

T1110.001Brute Force: Password Guessing — mapped directly in the analytics rule. Every time this fires, Sentinel auto-generates a High severity incident.


## What Sentinel generated automatically


Within 90 minutes of the attack starting, the rule fired and Sentinel created Incident ID 1 — SSH Brute Force Attack Detected — High severity — Active. No manual trigger. No human needed to notice the pattern.


*Sentinel auto-generated Incident ID 1 — SSH Brute Force Attack Detected — High severity. This is the end-to-end detection pipeline working as intended.*

## The investigation — two more KQL queries


Once the incident fired, two hunting queries confirmed everything I needed to know:


*Identify the attacker IP and targeted account*


```
Syslog
| where SyslogMessage contains "Failed password"
| where TimeGenerated > ago(7d)
| parse SyslogMessage with * "from " AttackerIP " port" *
| parse SyslogMessage with * "for " TargetUser " from" *
| summarize TotalAttempts = count() by AttackerIP, TargetUser, HostName
| order by TotalAttempts desc
```


*Confirm no successful logins*


```
Syslog
| where SyslogMessage contains "Accepted password"
or SyslogMessage contains "Accepted publickey"
| where TimeGenerated > ago(7d)
| project TimeGenerated, HostName, SyslogMessage
```


Result: 10.0.0.100–260 attempts. Zero successful authentications anywhere in the logs. The attacker ran for 28 minutes and never got in.


*KQL forensics confirmed attacker IP, targeted username, and 260 total attempts. Zero successful logins — attack failed completely.*


*Attack timeline showing 3 distinct waves — 48, 120, and 88 attempts. Multi-wave pattern is characteristic of Hydra brute force tool behavior.*

## The one thing that makes this query actually work


Everything in this rule comes down to one decision: rate-based detection vs per-event alerting.


If I had alerted on every single failed login, I’d have had 260 alerts to triage. Each one would be identical. None of them would tell me anything the others didn’t. That’s alert fatigue — the thing that burns out SOC analysts in real environments.


By aggregating with `bin(TimeGenerated, 5m)`, I got one incident that showed the complete picture: 260 attempts, 3 waves, 28 minutes, one attacker IP, zero successful logins. Everything a SOC analyst needs to investigate and contain in a single incident.


That’s the shift from writing a query to writing a detection rule.

>

This is one piece of a 7-day Microsoft Sentinel enterprise lab I built from scratch — SSH and RDP brute force detection, post-exploitation recon detection, KQL threat hunting, SOAR automation, and a full SOC dashboard. Full lab on GitHub at github.com/ronakmishra28. More writeups coming.


If you’re building your own Sentinel lab or studying for SC-200 — feel free to connect on LinkedIn. Always good to compare notes with people doing the actual work.


#microsoftsentinel #kql #soc #cybersecurity #blueteam #siem #sc200 #azure #infosec #detectionengineering #homelab

---

*Originally published on [Medium](https://infosecwriteups.com/the-kql-query-that-caught-260-brute-force-attempts-in-microsoft-sentinel-b305b68afb69). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
