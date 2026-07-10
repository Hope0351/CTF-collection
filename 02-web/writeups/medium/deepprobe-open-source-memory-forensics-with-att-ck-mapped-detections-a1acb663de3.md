# :globe_with_meridians: DeepProbe: Open-Source Memory Forensics with ATT&CK-Mapped Detections

> **Original Source:** [DeepProbe: Open-Source Memory Forensics with ATT&CK-Mapped Detections](https://infosecwriteups.com/deepprobe-open-source-memory-forensics-with-att-ck-mapped-detections-a1acb663de39)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# DeepProbe: Open-Source Memory Forensics with ATT&CK-Mapped Detections


When attackers breach a system, logs lie, binaries mutate, but memory doesn’t forget. From hidden rootkits to credential theft, the evidence is there, if you can find it.


But manual memory forensics is slow and noisy. Volatility is powerful, but plugin-by-plugin hunting burns precious hours in an incident.


That’s why we built DeepProbe: an open-source framework that automates Volatility analysis, codifies expert detection logic, and correlates signals into actionable findings.


Repo: [https://github.com/purplesectools/DeepProbe](https://github.com/purplesectools/DeepProbe?utm_source=chatgpt.com)


The Core Idea


At its heart, DeepProbe is simple:


- Run the right plugins across Windows, Linux, macOS memory dumps

- Apply detection logic written in YAML (detections.yaml)

- Respect a baseline of known-good processes, services, IPs (baseline.yaml)

- Correlate anomalies into higher-confidence findings


This means analysts don’t drown in raw output, instead, they get ready-to-use forensic artifacts that point to the attack path.


### Individual Detections (With Artifacts)


DeepProbe breaks down detections into categories that mirror attacker tradecraft. Each detection comes with direct artifacts you can pivot on.


Evasion & Hiding


Attackers conceal themselves by unlinking or tampering with OS structures. DeepProbe flags:


- Hidden Processes (psxview): artifacts → process name, PID, thread count

- Unlinked DLLs (ldrmodules): artifacts → DLL path, load count, suspicious temp dirs

- Hidden Drivers (modules vs modscan): artifacts → driver name, memory base address

- Orphaned Registry Hives (hivelist vs hivescan): artifacts → hive offsets, root keys


Why it’s useful: These anomalies usually mean stealth malware or rootkits.


Persistence


How attackers survive a reboot:


- Run/RunOnce Keys: artifacts → suspicious executables/scripts set to autostart

- Scheduled Tasks: artifacts → task name, command line, execution time

- Suspicious Services: artifacts → service name, binary path in writable/temp directories


Why it’s useful: These reveal *how* the attacker plans to come back.


Network Activity


Memory exposes live or recent C2 connections:


- Malicious IPs (via AbuseIPDB): artifacts → remote IP, port, reputation score

- Suspicious Geolocations (RU, CN, IR, etc.): artifacts → IP → country

- Non-whitelisted Connections: artifacts → full socket tuple (local/remote IP:port)

- Suspicious Ports: artifacts → 31337, 4444, etc.


Why it’s useful: Outbound traffic often points directly to C2 infrastructure.


Code Injection & Execution


## Get Purple Security’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


DeepProbe catches how malware runs in memory:


- Malfind Injection: artifacts → process, suspicious memory region, strings found (Mimikatz, Meterpreter)

- LSASS Handle Access: artifacts → process holding dangerous rights to lsass.exe

- Hollowed Processes: artifacts → parent process, injected payload, mismatch between on-disk vs in-memory image


Why it’s useful: These are the execution points where attackers gain creds or run payloads.

### Correlated Detections


This is where DeepProbe moves beyond checklists. It links weak signals into strong findings.


- Persistence + Execution: If a suspicious scheduled task exists *and* the binary it launches is actively running, that’s not just noise — it’s an active backdoor.

- Credential Access + Injection: LSASS access *and* malfind injection in the same process = clear credential theft.

- Evasion + Network Activity: A hidden process (not in pslist) that also has a suspicious outbound connection = active C2 with stealth.

- Kernel Anomalies Cluster: Multiple discrepancies in kernel modules and SSDT hooks point strongly to a rootkit.


Why it’s useful: Correlation mirrors an analyst’s reasoning, cutting false positives and raising confidence.

### Artifacts: Readily Available


Every detection DeepProbe surfaces is tied to real, pivot-ready artifacts:


- Process names, PIDs, parent processes

- Module/DLL paths

- Registry keys and hive offsets

- Service names and ImagePaths

- Scheduled task details

- Network sockets with remote IP/ports

- Enriched IP reputation & geolocation

- Suspicious memory regions (addresses + extracted strings)


No vague alerts, you get investigative leads right away.


### Baselining: Removing Noise


No two environments are the same. That’s why DeepProbe ships with baseline.yaml:


- Define known-good processes (chrome.exe, explorer.exe, AV tools)

- Whitelist expected IP ranges and ports

- Allow trusted services and DLLs


The effect: detections focus on true anomalies, not false positives from normal activity.


Analysts can tune the baseline once, then reuse it across investigations for consistency.

### MITRE ATT&CK Mapping


DeepProbe’s categories align with MITRE ATT&CK tactics, helping analysts contextualize findings:


- Evasion & Hiding → Defense Evasion (TA0005)

- Persistence → Persistence (TA0003)

- Code Injection & Hollowing → Execution (TA0002), Defense Evasion (TA0005)

- LSASS Access → Credential Access (TA0006)

- Suspicious Network → Command & Control (TA0011)

- Correlated Kernel Anomalies → Privilege Escalation (TA0004)


This makes detections not just anomalies, but mapped attacker behaviors, ready for reporting and threat-intel integration.

### Call for Collaboration


We built DeepProbe to accelerate memory forensics, but this is just the beginning.


We need the community’s help:


- Expand detection rules → contribute new TTPs in YAML

- Improve ATT&CK mapping → link each detection to specific techniques (T1055, T1053, etc.)

- Refine baselining → share whitelists for common enterprise environments

- Suggest enrichments → domain reputation, YARA hits, hash lookups


Whether you’re a DFIR pro, threat hunter, or red teamer, your input can sharpen DeepProbe further.


Try it, break it, extend it, and open issues/PRs on [GitHub](https://github.com/purplesectools/DeepProbe?utm_source=chatgpt.com).


Memory forensics doesn’t have to be slow, noisy, and overwhelming.


DeepProbe gives analysts codified detection logic, forensic artifacts, correlation, baselining, and MITRE context — all in one workflow.


The goal isn’t just automation. It’s turning raw memory into actionable intelligence.

---

*Originally published on [Medium](https://infosecwriteups.com/deepprobe-open-source-memory-forensics-with-att-ck-mapped-detections-a1acb663de39). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
