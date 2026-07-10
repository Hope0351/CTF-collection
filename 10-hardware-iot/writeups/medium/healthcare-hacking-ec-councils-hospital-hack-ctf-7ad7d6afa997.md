# :electric_plug: Healthcare Hacking Ec Councils Hospital Hack Ctf 7Ad7D6Afa997

---

## Comprehensive Walkthrough

### 1. Identify Attacking Machine IP

First, confirm the IP of our attacking Kali Linux machine:

```
ip addr
```

Result: IP identified as `10.10.1.2`.

### 2. Network Discovery with ARP Scan

Perform an ARP scan to locate active devices on the network:

```
arp-scan -l
```

Result: Detected two devices with IPs `10.10.1.200` and `10.10.1.201` on the target network `10.10.1.0/24`.

### 3. Service Scan on 10.10.1.200

Run an Nmap scan on `10.10.1.200` to identify open ports and services:

```
nmap -sC -sV -p- -Pn -T4 10.10.1.200
```

Result: Three open ports were found, including HTTP on port 80, running an Apache2 server, and MySQL on port 3306, running version 5.7.31.

### 4. Apache Web Server Identification

Visit `http://10.10.1.200` and confirm an Apache2 server is running.

### 5. Service Scan on 10.10.1.201

Run an Nmap scan on the second target device:

```
nmap -sC -sV -p- -Pn -T4 10.10.1.201
```

Result: Open ports were detected, though the MySQL version was not displayed, emphasizing the importance of scanning all devices for version data. However, we have another Apache Server running on port 80.

## Get Anbu Hack Ops’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

6. Locate OpenEMR Login Interface
Navigate to `http://10.10.1.201`, where the OpenEMR login page was identified.

### 7. Directory Brute-Forcing with Gobuster

Use Gobuster to locate sensitive directories and files:

```
gobuster dir -u http://10.10.1.201/openemr/ -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -x php,html,txt -t 50
```

Result: Found `admin.php`, accessible without authentication.

8. Check OpenEMR Version
Navigate to `/admin.php` to identify OpenEMR version `5.0.2(1)`.

### 9. Vulnerability Research

Research known vulnerabilities for OpenEMR 5.0.2(1) using Searchsploit and CVE databases:

```
searchsploit openemr
```

*OpenEMR v5.0.2(1) RCE exploit found*

---
