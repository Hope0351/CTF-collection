# :game_die: HTB Sherlock ProcNet: Exploring Windows API Call Monitoring with API Monitor

---

# HTB Sherlock ProcNet: Exploring Windows API Call Monitoring with API Monitor

## Hack The Box DFIR Challenge Writeup

*Source : [https://labs.hackthebox.com/storage/challenges/1728efbda81692282ba642aafd57be3a.png](https://labs.hackthebox.com/storage/challenges/1728efbda81692282ba642aafd57be3a.png)*

Malware analysis often involves dissecting the behavior of malicious software in a controlled environment to understand its capabilities and impact. Dynamic analysis, in particular, offers a real-time view of malware execution, allowing analysts to observe its interactions with the system and other processes. One valuable tool in this arsenal is Rohitab Batra’s API Monitor, renowned for its prowess in capturing and analyzing Windows API calls. This article delves into its application within the context of the HTB Sherlock ProcNet challenge, where we were given two hosts that each contained three source data files, including PCAP files, Windows sysmon event logs (evtx), and API Monitor output files (apmx64).

The challenge scenario is as follows :

>

With the rising utilization of open-source C2 frameworks by threat actors, our red team has simulated the functionalities of one such widely employed framework. The objective of this exercise is to aid blue teams in strengthening their defenses against these specific threats. We have been provided with PCAP files and APIs collected during the event, which will serve as valuable resources. Let us now initiate the hunting process.

We’ll be investigating two hosts, identified as :

>

*desktop-r30eamh.Forela.local, ip address -10.0.0.79 (Employee)
DC01.Forela.local, ip address -10.0.0.11 (Domain Controller)*

The goal of this challenge is to find out the behavior of the attackers on both hosts. In addition to the api monitor, we will use several other tools to analyze other artifacts using wireshark, EvtxECmd, and TimelineExplorer. We will utilize the EvtxECmd tool to parse the sysmon evtx into a more readable csv file, and analyze it using TimelineExplorer. As for how to use this tool, 13Cubed explains it well in the following [video](https://www.youtube.com/watch?v=YvMg3p7O6ro) on his YouTube account. Without further ado, let’s analyze each host.

## desktop-r30eamh

*1. To which IP address and port number is the malware attempting to establish a connection ?*

To address this question, we can use either pcap or sysmon event logs, focusing on event ID 3 to detect suspicious network activity. Referring to Microsoft’s official [documentation](https://learn.microsoft.com/en-us/sysinternals/downloads/sysmon) provides insights into sysmon event IDs. Sysmon event ID 3 is useful for examining connections established with hosts. Prioritizing the IP with the most connections, we’ll exclude the domain controller’s IP (10.10.0.11) and focus on IPs 239.255.255.250 and 3.6.165.8 for further investigation.

*TimelineExplorer view*

The process initiating the connection with IP 239.255.255.250 is msedge.exe, confirmed to be a legitimate process.

*msedge.exe executable full path*

On the other hand, the process that initiates the connection with IP 3.6.165.8 is csgo.exe in the download folder with a destination port of 443, which is quite suspicious.

*csgo.exe executable full pathConnection Details*

Analyzing the PCAP file filtered for IP address 3.6.165.8, we observe the host sending an HTTP GET request to that IP on port 8080, querying the directory “/”. With Wireshark’s HTTP stream feature, we examine the response, which contains a list of executables, Notedly Sharpedge. This suggests that the IP serves as the attacker’s command-and-control (C2) server.

*Wireshark TCP stream (GET / )*

Once csgo.exe is downloaded and executed, it encrypts the traffic with TLSv1.3 on port 443 so that the traffic becomes unreadable and can be disguised among legitimate traffic.

*TLS handshake*

>

*Answer: 3.6.165.8:4432. Now that you are aware of the IP address and port number, what is the JA3 fingerprint of the C2 server ?*

JA3 fingerprints serve various purposes like threat intelligence, network monitoring, and security analytics. They aid in distinguishing and classifying SSL/TLS clients, including web browsers and malware. When the host initiates the TLS handshake protocol with a client hello, these fingerprints become visible in the traffic details. Precisely, they are located within the TLS section under HandshakeProtocol, encapsulated within the JA3 field.

*Client hello packet details*

>

*Answer: 19e29534fd49dd27d09234e639c4057e*

3. What is the name of the C2 framework being utilized by the red team ?

To analyze further, extract the csgo.exe file from the traffic in Wireshark. Simply view the TCP stream during the transfer and click “Save As,” ensuring to delete the HTTP request header.

*Wireshark TCP stream (GET /csgo.exe )*

Using [VirusTotal](https://www.virustotal.com/gui/file/896e3ff599f99afb7fa28d7f1d7a21e91d6432806436a7e45a6007aeacee785b/community), it shows csgo.exe tied to “Sliver” C2 framework.

*VirusTotal submission*

>

*Answer: sliver4. Which WIN32 API provided the red team with the current directory information ?*

To find the answer, open the API monitor on the provided apmx64 file and select the csgo.exe process. Alternatively, you can search for the Windows API that retrieves the current directory using google and then utilize the string search feature in the API monitor.

*API monitor csgo.exe*

*Search with the search string feature*

>

*Answer: GetCurrentDirectoryW5. Now that we have identified the C2 framework utilized by the red team, which C2 command is responsible for opening notepad.exe by default and loading the .NET CLR into it ?*

## Get Muhammad Haidar Akita Tresnadi’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

It’s well established that the Common Language Runtime (CLR) furnishes a robust runtime environment, facilitating the execution of managed code across a spectrum of languages supported by the .NET Framework. Through the API monitor, we discern a fascinating aspect of csgo.exe’s functionality: its loading of DLLs via the Windows API LoadLibrary. Notably, clr.dll and mscore.dll are among the DLLs loaded. These particular DLLs play a pivotal role in the in-memory execution of .NET assemblies, employing a technique referred to as *Bring Your Own Land* (BYOL).

*CLRCreateinstance windows API call*

Online findings indicate that Sliver utilizes the “execute-assembly” command to run .NET assemblies.

>

*Answer: execute-assembly6. What is the name of the module (DLL) that was loaded to gain access to Windows Vault ?*

Using LoadLibrary, we find vaultcli.dll related to vault functionality.

*vaultcli.dll loaded using LoadLibraryExW*

>

*Answer: vaultcli.dll7. After loading the mentioned module, there were a series of WIN32 APIs loaded. Which specific Win32 API is responsible for enumerating vaults ?*

Functions exported by vaultcli.dll can be found [here](https://windows10dll.nirsoft.net/vaultcli_dll.html). VaultEnumerateVaults is likely used for vault enumeration and was loaded by the attacker, as shown by the GetProcAddress Windows API call.

*csgo.exe import VaulEnumerateVaultsW function*

>

*Answer: VaultEnumerateVaults8. Which command did the attacker execute to identify domain admins ?*

In the API monitor, csgo.exe spawns a net.exe process, typically used for domain enumeration. The command “net group ‘domain admins’ /dom” identifies the admin domain.

*net.exe api call*

*csgo.exe create new net.exe process*

>

*Answer: net group “domain admins” /dom9. The red team has provided us with a hint that they utilized one of the tools from “ARMORY” for lateral movement to DC01. What is the name of the tool ?*

Analyzing tools executed in memory is challenging. However, by examining the DLLs loaded by csgo.exe, we notice wminets_utils.dll, which is associated with WMI remote execution.

*wminets_utils.dll loaded using LoadLibraryExW*

Furthermore, csgo.exe imports the ExecQueryWmi function, indicating a possible connection to WMI operations.

*csgo.exe import ExecQueryWmi function*

looking for strings related to wmi, we found that the tool used is sharpwmi.

*SharpWMI string allocated*

>

*Answer: sharpwmi*

Prior to moving on to the next question, examining interesting strings used as parameters or arguments from SharpWMI via the API monitor reveals that it executes a VBScript command. This command appears to be responsible for downloading the fifa24.exe file observed earlier on the domain controller acting as the C2 server.

*SharpWMI arguments*

Sysmon event ID 20 on the domain controller confirms the execution of the VBScript command, validating our suspicion. Our analysis can now be narrowed down to fifa24.exe.

*vbscript command*

Here’s a more readable version :

*vbscript command (more readable)*

## DC01

*10. Which command was executed by the red team to extract/dump the contents of NTDS.DIT ?*

With sysmon event ID 1, we observe the attacker executing multiple command lines, including one for extracting content from ntds.dit.

*Command for extracting ntds.dit content*

>

*Answer: cmd /c ntdsutil “ac in ntds” ifm “cr fu %TEMP%\H00i0Z000.dat” q q11. The red team has obtained the aforementioned dump by compressing it into a ZIP file. Which specific Win32 API is responsible for retrieving the full path of the file to be downloaded?*

Using the API monitor, we identify GetFullPathNameW as the Windows API called for obtaining the full path of a file.

*GetFullPathNameW windows API call*

>

*Answer: GetFullPathNameW*

## Closing

In this writeup, I focus on my experience completing this challenge. Apologies for not delving into details on MITRE ATT&CK, the attacker’s cyber kill chain, and mitigation measures. Thank you for reading. Enjoy the investigation :D

## Reference

>

[Bring Your Own Land (BYOL) — A Novel Red Teaming Technique | Mandiant](https://www.mandiant.com/resources/blog/bring-your-own-land-novel-red-teaming-technique) Detecting .NET/C# injection (Execute-Assembly) | by redhead0ntherun | Medium
[Windows 10 DLL File Information — vaultcli.dll (nirsoft.net)](https://windows10dll.nirsoft.net/vaultcli_dll.html)
[Sysmon — Sysinternals | Microsoft Learn](https://learn.microsoft.com/en-us/sysinternals/downloads/sysmon)
[https://www.youtube.com/watch?v=YvMg3p7O6ro](https://www.youtube.com/watch?v=YvMg3p7O6ro)
[API Monitor: Spy on API Calls and COM Interfaces (Freeware 32-bit and 64-bit Versions!) | rohitab.com](http://www.rohitab.com/apimonitor)
[Eric Zimmerman’s tools](https://ericzimmerman.github.io/#!index.md)
[VirusTotal — File — 896e3ff599f99afb7fa28d7f1d7a21e91d6432806436a7e45a6007aeacee785b](https://www.virustotal.com/gui/file/896e3ff599f99afb7fa28d7f1d7a21e91d6432806436a7e45a6007aeacee785b/community)

---
