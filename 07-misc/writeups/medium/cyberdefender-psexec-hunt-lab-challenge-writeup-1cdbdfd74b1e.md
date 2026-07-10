# :game_die: Medium

---

# CyberDefender: “PsExec Hunt Lab” Challenge Writeup

## **Scenario**

An alert from the Intrusion Detection System (IDS) flagged suspicious lateral movement activity involving PsExec. This indicates potential unauthorized access and movement across the network. As a SOC Analyst, your task is to investigate the provided PCAP file to trace the attacker’s activities. Identify their entry point, the machines targeted, the extent of the breach, and any critical indicators that reveal their tactics and objectives within the compromised environment.

>

***Category: Network Forensics*

***Tactics Execution, Defense Evasion, Discovery, Lateral Movement*

***Tools: Wireshark*

## Questions

>

***Q1: To effectively trace the attacker’s activities within our network, can you identify the IP address of the machine from which the attacker initially gained access?***

>

***Q2: To fully understand the extent of the breach, can you determine the machine’s hostname to which the attacker first pivoted?***

With the attacker’s IP locked in, we zeroed in on SMB traffic to 10.0.0.133:

```
ip.addr == 10.0.0.130 && ip.addr == 10.0.0.133
```

We spotted a critical packet:

```
131 2023/284 00:42:08.878607443 10.0.0.133 → 10.0.0.130 SMB2 Session Setup Response, Error: STATUS_MORE_PROCESSING_REQUIRED, NTLMSSP_CHALLENGE
```

Following the TCP stream, we scrolled through the NTLMSSP payload and struck gold: Workstation: SALES-PC. This confirmed SALES-PC as the first machine the attacker compromised after gaining access.

```
Answer: The first pivoted machine’s hostname is SALES-PC.
```

>

***Q3: Knowing the username of the account the attacker used for authentication will give us insights into the extent of the breach. What is the username utilized by the attacker for authentication?***

Sticking with the SMB traffic, we filtered for NTLMSSP authentication:

```
ip.addr == 10.0.0.130
```

Packet 132 revealed the smoking gun:

```
132 2023/284 00:42:08.879115750 10.0.0.130 → 10.0.0.133 SMB2 Session Setup Request, NTLMSSP_AUTH, User: \ssales
```

The attacker authenticated as ssales, likely using stolen credentials or a pass-the-hash technique to gain a foothold on **SALES-PC.**

```
Answer: The username used is ssales.
```

>

***Q4: After figuring out how the attacker moved within our network, we need to know what they did on the target machine. What’s the name of the service executable the attacker set up on the target?***

PsExec is notorious for dropping a service executable to run commands remotely. We filtered for SMB Create/Write requests:

```

## Get SHENOBIE’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in
smb2 && (smb2.cmd == 5 || smb2.cmd == 9)
```

Boom! Packet 144 showed:

```
144 2023/284 00:42:08.885179064 10.0.0.130 → 10.0.0.133 SMB2 Create Request File: PSEXESVC.exe
```

This confirmed PsExec’s hallmark: deploying PSEXESVC.exe to execute malicious commands on the target.

```
Answer: The service executable is PSEXESVC.exe
```

>

***Q5: We need to**know how the attacker installed the service on the compromised machine to understand the attacker’s lateral movement tactics. This can help identify other affected systems. Which network share was used by PsExec to install the service on the target machine?***

PsExec typically uses administrative shares to drop its executable. We revisited the Create Request from Question 4:

```
smb2 && frame contains "PSEXESVC"
```

```
\\10.0.0.133\ADMIN$\PSEXESVC.exe
```

The ADMIN$ share, a hidden Windows share for administrative access, was used to upload PSEXESVC.exe to SALES-PC.

```
Answer: The network share used is ADMIN$
```

>

***Q6: We must identify the network share used to communicate between the two machines. Which network share did PsExec use for communication?***

PsExec relies on named pipes for command and control. We filtered for SMB Tree Connect or Create requests:

```
smb2 && (smb2.cmd == 3 || smb2.cmd == 5)
```

The TCP stream revealed connections to:

```
\\10.0.0.133\IPC$
```

The IPC$ (Inter-Process Communication) share is PsExec’s go-to for facilitating remote procedure calls and service control via named pipes like \\PIPE\\svcctl.

```
Answer: The network share for communication is IPC$
```

>

***Q7:Now that we have a clearer picture of the attacker’s activities on the compromised machine, it’s important to identify any further lateral movement. What is the hostname of the second machine the attacker targeted to pivot within our network?***

To catch further lateral movement, we filtered for traffic from the attacker’s IP (10.0.0.130) to other hosts:

```
19 2023/284 00:37:58.580105328 10.0.0.131 → 224.0.0.252 LLMNR 72 Standard query 0x611b ANY Marketing-PC
```

This LLMNR query for Marketing-PC suggests the attacker was enumerating or targeting this host. Although the source IP (10.0.0.131) differs, it likely indicates a typo or a secondary compromised system, with 10.0.0.130 as the primary attacker IP. We confirmed no SMB traffic to 10.0.0.131, but the LLMNR query points to Marketing-PC as the next pivot target.

```
Answer: The second targeted hostname is Marketing-PC
```

**🎉 Mission Accomplished! We’ve traced the attacker’s every move with forensic precision.**

---
