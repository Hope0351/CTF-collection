# :game_die: QRadar Threat Hunting: Blue Team CTF Challenge

> **Original Source:** [QRadar Threat Hunting: Blue Team CTF Challenge](https://infosecwriteups.com/qradar-threat-hunting-blue-team-ctf-challenge-389a87f4a126)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## Cyber Defenders Questions & Answers


*Q1: How many log sources are available?*


Looking through the [IBM QRadar Documentation](https://www.ibm.com/docs/en/sdi/7.2.0.3?topic=connector-setting-up-qradar-log-source), we can identify the number of log sources by following these steps:


- Log on to the QRadar SIEM and select the Admin tab on the navigation bar.

- Under Data Sources, in the Events section, click Log Sources.

- This provides a list of log sources in QRadar.

*Log sources available in QRadar.Q2: What is the IDS software used to monitor the network?*


Referring to the available logs sources above, the IDS software being used is Suricata.


*Q3: What is the domain name used in the network?*


The question is asking for the domain name used by the company in their network. A network domain, in relation to a domain controller, is a logical grouping of computers and devices managed by a domain controller, enabling centralized authentication, authorization, and administration within a network.


It is probably worth briefly discussing how to perform searches in QRadar, as I will be performing lots of them throughout this challenge. Click the Log Activity tab, then Select the “Search” dropdown to create a custom search.

*Edit Search under Log Activity*


Next, we need to set the specific interval to search for events across the timeframe, based on the log sources seen when answering Q1. The events appeared to take place between the months of October 2020 and November 2020, so I set the specific interval to encompass this time frame.

*Set search time frame.*


Then, under column definition, we can group by different fields, such as Log Source. If the field is already included as a column, then it will need to be removed first from the “columns” and then added under “group by” by selecting the field and using the directional arrows.


*Group by fields and add columns to search results.*


This specific search filter returns events grouped by their respective log source. The log source titled “DC” most likely contains windows events from the companies domain controller(s). We can double click this log source to see the events.

*Events grouped by the Log Source Field.*


If we select one of the events and observe the raw windows event log under Payload Information, we can see that the network domain name being used is “hackdefend.local”.

*Network Domain.*


This is the process I mostly followed to perform searches during the rest of the investigation.


*Q4: Multiple IPs were communicating with the malicious server. One of them ends with “20”. Provide the full IP.*


To determine what IP’s were communicating with the malicious server, we can select the “SO-Suricata” log source as seen earlier with the “DC” log source. Once the events are returned, I also edited the search to group by source IP addresses as seen earlier above.

*Suricata IDS Alerts for “DC”.*


The results show multiple NIDS alerts for the IP address 192.168.20.20 “DC”.


*Q5: What is the SID of the most frequent alert rule in the dataset?*


I can simply apply a filter for the log source “SO-Suricata” and group by the field “Rule SID”. I can see that the top Rule SID is 2027865 and by drilling down into the grouped events, I can see that this Rule SID is for DNS related activity.


*Q6: What is the attacker’s IP address?*


Continuing to work with the Suricata logs, we can remove any pre-existing grouping and include the column titled “Rule Name” in our search results, which was seen earlier when searching for the Rule SID. Looking through the events from oldest to newest, we can see lots of alerts for DNS related activity but there is one rule that fired for a potential “Metapsloit Payload” that stands out.


*Suricata Alert for Metasploit.*


There looks to be some suspicious activity involving a Metasploit payload between 192.20.80.25 and 192.168.10.15 IP addresses. Applying a filter for where either the source or destination IP is “192.20.80.25”, we can see additional rule alerts being fired by Suricata that are indicative of this IP address being the attacker’s IP.


*Suricata Alerts for “192.20.80.25” IP Address.Q7: The attacker was searching for data belonging to one of the company’s projects, can you find the name of the project?*


The attacker was able to compromise 192.168.10.15 with a Metasploit reverse shell. It is common for attackers to start enumerating the compromised host, attempt to escalate their privileges and then move laterally through the network. We can apply new filters to the search for the IP address 192.168.10.15 as either the destination or source IP address and apply a filter to check event payloads for the keyword “project”. This search returns events for the log source “HD-FIN-03”.


*Events that contain the keyword “project”.*


Looking at these events, we can see the attacker attempting to retrieve an excel file called “project48-transactions.xlsx”.


*Company Project Name.Q8: What is the IP address of the first infected machine?*


Looking at the Suricata alerts in question 6, we can see that the attacker initially exploited the host 192.168.10.15 with a Metasploit exploit and then started to look for confidential company data.


*Q9: What is the username of the infected employee using 192.168.10.15?*


Looking at the Suricata alerts in question 6, we can see the username is “nour”.


*Q10: Hackers do not like logging, what logging was the attacker checking to see if enabled?*


In question 7, we saw the attacker using PowerShell to retrieve the project data. We can apply a new filter for the log source “HD-FIN-03”, source or destination IP 192.168.10.15, and the username “nour”. The results show the attacker launching two PowerShell Console sessions.

*PowerShell Console Sessions.*


The PowerShell logs appear to be truncated, since it does not contain the full PowerShell command being executed but I can see that the attacker is attempting to test for additional hosts within the 192.168.20.0/24 subnet, after they have found the company project data.


```
CommandInvocation(ForEach-Object): "ForEach-Object" ParameterBinding(ForEach-Object): name="Process"; value=""192.168.20.$($_): $(Test-Connection -count 1 -comp 192.168.20.$($_) -quiet)"" ParameterBinding(ForEach-Object): name="InputObject"; value="1" ParameterBinding(ForEach-Object): name="InputObject"; value="2" ParameterBinding(ForEach-Object): name="InputObject"; value="3" ParameterBinding(ForEach-Object): name="InputObject"; value="4" ParameterBinding(ForEach-Object): name="InputObject"; value="5" ParameterBinding(ForEach-Object): name="InputObject
```


Performing a new search where the source IP is 192.168.10.15 and the destination IP is the 192.168.20.0/24 network subnet, we can see all the connection records made as part of the internal reconnaissance performed via the PowerShell command seen above.


*Connection records related to internal reconnaissance scan.*


Next, I applied a filter for log source “HD-FIN-03”, source or destination IP 192.168.10.15 and [Sysmon event ID 1](https://learn.microsoft.com/en-us/sysinternals/downloads/sysmon#event-id-1-process-creation), which is for process creation and logs command line arguments. Reviewing the command line arguments did not show any indicators of logging being disabled.


## Get Hacktivities’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Next, I applied the same filter and changed the log source to “DC”, where I can see that the attacker is checking if PowerShell logging is enabled.


```
cmd.exe /Q /c reg query HKLM\Software\Policies\Microsoft\Windows\PowerShell\ScriptBlockLogging 1> \\127.0.0.1\ADMIN$\__1604913874.5822518 2>&1
```


*Attacker Checking if PowerShell Logging is enabled.*


The command above queries the specified registry key related to PowerShell ScriptBlockLogging and saves the output, including any errors, to a file located at the specified UNC path.


*Q11: Name of the second system the attacker targeted to cover up the employee?*


In the offenses tab, under all offenses, I can see that an offense was generated for 192.168.11.13 around 20 minutes after the offense generated for 192.168.10.15 IP address.


*Offenses for 192.168.11.13 IP Address.*


Looking at the available log sources, I can see that the IP address belongs to “MGNT-01”. I applied a filter for log source “MGNT-01”, Sysmon event ID 1 and included a column for “Process ComamndLine” which is for process creation and logs command line arguments. Looking at the output, I can see multiple events that contain process command line activity related to the ADMIN share, including the removal and deletion of an excel file titled “sami.xlsx” in the Desktop folder.

*Removal and deletion of excel file titled “sami.xlsx”.Q12: When was the first malicious connection to the domain controller (log start time — hh:mm:ss)?*


So far, we know that the first compromised host was “HD-FIN-03” and that it might be a good place to start checking for any malicious connections. I applied a filter for the log source “HD-FIN-03” and for [Sysmon event ID 3](https://learn.microsoft.com/en-us/sysinternals/downloads/sysmon#event-id-3-network-connection) (“Network Connection Detected”). Looking back at the earliest events, I can see that at “11:14:10 PM”, the file notepad.exe starts making network connections, which is very suspicious.

*Notepad.exe making network connections.*


Looking at the event payload, I can see that a network connection was made to the DC via the LDAP protocol.


*Network connection to DC at “11:14:10 PM”.Q13: What is the md5 hash of the malicious file?*


Still working with Sysmon events, I applied a filter for “[Event ID 15: FileCreateStreamHash](https://learn.microsoft.com/en-us/sysinternals/downloads/sysmon#event-id-15-filecreatestreamhash)” and the log source “HD-FIN-03”. Looking at the events, I can see the MD5 hash for the malicious file titled “important_instructions.docx”.


*Malicious File MD5 Hash.Q14: What is the MITRE persistence technique ID used by the attacker?*


Performing a quick search on google reveals that one of the most common techniques for establishing persistence by malware and threat actors is the usage of registry Run keys & Start up folders in a windows system. I applied a filter for [Sysmon Event ID 13: RegistryEvent (Value Set)](https://learn.microsoft.com/en-us/sysinternals/downloads/sysmon#event-id-13-registryevent-value-set) and added a column for “Target Object”. Looking through the events, I can see that a suspicious program is set to run on the Domain Controller every time the user logs in, by using the registry “Run” key.


*Registry “Run” Key.*


Reviewing the event log payload, we can see that the attacker used PowerShell (i.e. Image) to rename the registry key and value, the complete path of the renamed registry key (i.e. “TargetObject”) and the details added to the registry key (i.e. Details), which in this case is to run the VBS script “C:\Windows\TEMP\PjvQTe.vbs” every time the user logs in.


*VBS Script runs every time user logs on.*


This activity matches the MITRE persistence technique ID [T1547.001](https://attack.mitre.org/techniques/T1547/001/)


*Q15: What protocol is used to perform host discovery?*


In Question 10, we found the attacker using the PowerShell script used below to enumerate the 192.168.20.0/24 subnet.


```
CommandInvocation(ForEach-Object): "ForEach-Object" ParameterBinding(ForEach-Object): name="Process"; value=""192.168.20.$($_): $(Test-Connection -count 1 -comp 192.168.20.$($_) -quiet)"" ParameterBinding(ForEach-Object): name="InputObject"; value="1" ParameterBinding(ForEach-Object): name="InputObject"; value="2" ParameterBinding(ForEach-Object): name="InputObject"; value="3" ParameterBinding(ForEach-Object): name="InputObject"; value="4" ParameterBinding(ForEach-Object): name="InputObject"; value="5" ParameterBinding(ForEach-Object): name="InputObject
```


I applied a filter for the source IP 192.168.10.15, the destination IP 192.168.20.0/24 network subnet and added a column for the Protocol field. We can see all the connection records made as part of the internal reconnaissance performed via the PowerShell command seen above and the protocol used.

*Host Discovery with ICMP.Q16: What is the email service used by the company?(one word)*


To answer this question, we can apply a filter on the log source “Zeek_conn”, destination port 53, exclude destination IP 8.8.8.8 and exclude destination IP 192.168.20.0/24 subnet.

*DNS Connections.*


If we use VirusTotal, we can see that the IP addresses listed above resolve to Microsoft cloud services.

*VirusTotal.*


If we search online, we can see that Microsoft offers the cloud service Office 365, which provides email services.


*Q17: What is the name of the malicious file used for the initial infection?*


Name of the file was identified in Q13.


*Q18 — What is the name of the new account added by the attacker?*


To find new accounts added, we can filter on event ID 4720 (A user account was created). When a user account is created in Active Directory, event ID 4720 is logged. Looking at the event returned, we can see the name of the account added by the attacker.


*Windows Event ID 4720.*


Filtering on event 1 ID, we can also see the attacker adding the “rambo” user to domain admins group.


*User “rambo” added to domain admins group.Q19: What is the PID of the process that performed injection?*


We can filter for [Sysmon Event ID 8: CreateRemoteThread](https://learn.microsoft.com/en-us/sysinternals/downloads/sysmon#event-id-8-createremotethread), which detects when a process creates a thread in another process. This technique is used by malware to inject code and hide in other processes. I applied a filter for event ID 8 and the infected host “HD-FIN-03”. I can see that FSETPBEUsIek.exe performed process injection on notepad.exe, as well as the source process ID.


*Process Injection.Q20: What is the name of the tool used for lateral movement?*


Needed to use the hints to find the answer since nothing conclusive was appearing in the logs.


Answer: wmiexec.py


*Q21: Attacker exfiltrated one file, what is the name of the tool used for exfiltration?*


Filtering on suricata alerts and the attackers IP address 192.20.80.25 as the destination IP address, we can see that an alert occurred for the usage of “curl”.

*Suricata Alert for cURL.*


If I apply a filter for the log source HD-FIN-02 and 192.20.80.25 as the destination IP address, I can see the command line used to exfiltrate the excel file.

*Data exfiltration with cURL.Q22: Who is the other legitimate domain admin other than the administrator?*


To find the other domain admin, I applied a filter for event ID 4672: Special privileges assigned to new logon and grouped by usernames.

*Domain Admins.Q23: The attacker used the host discovery technique to know how many hosts available in a certain network, what is the network the hacker scanned from the host IP 1 to 30?*


Network range was identified in Q10.


Answer: 192.168.20.0


*Q24: What is the name of the employee who hired the attacker?*


The attacker exfiltrated the file sami.xlsx and was seen trying to cover it up by then deleting the same excel file from the desktop, which indicates the name of the employee who hired the attacker was “sami”.

## Closing Remarks


I really enjoyed working through this challenge and getting the opportunity to learn more about investigating incidents using IBM’s QRadar. The challenge provides opportunities to learn about different log sources (e.g. Sysmon, Windows Events, Suricata, etc.), different adversary techniques and threat hunting with QRadar. Thank you for reading till the end and keep hacking 😄!

---

*Originally published on [Medium](https://infosecwriteups.com/qradar-threat-hunting-blue-team-ctf-challenge-389a87f4a126). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
