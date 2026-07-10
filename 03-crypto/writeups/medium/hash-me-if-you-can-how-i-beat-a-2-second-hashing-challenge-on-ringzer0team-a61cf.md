# :locked_with_key: Hash Me If You Can - How I Beat a 2-Second Hashing Challenge on RingZer0Team

> **Original Source:** [Hash Me If You Can - How I Beat a 2-Second Hashing Challenge on RingZer0Team](https://infosecwriteups.com/hash-me-if-you-can-how-i-beat-a-2-second-hashing-challenge-on-ringzer0team-a61cf0a87291)
> **Platform:** infosecwriteups.com | **Category:** `CRYPTO`

---

# *Hash Me If You Can* — How I Beat a 2-Second Hashing Challenge on RingZer0Team


## You have 2 seconds to hash this message using the SHA512 algorithm.


Two seconds?
I leaned back in my chair, staring at the screen. The clock was ticking — literally.


>

Hash Me If You Can


The name alone sounded like a dare.
I clicked it — and instantly understood why.


The challenge page displayed a wall of random characters between two neat banners:


```
----- BEGIN MESSAGE -----
wpIkf9n3I4NnnN9ZHGoCTOvLWL7ptuQwBaINST2avSi6uXtz0ZeEDG2tHnxNz0n15EZrUN9l0sgiWQKznq0JpXFmOwnSjVXzWvPhwox9E5vA2Ki9pqv6iqOEA1zEYr4JvZ5grJvSvdp9NYmVse5qn9gAHfQmkW5NWcNR1Fm06Yu3KknHAtI1kVnjsxCjjLXV24OmYuYnHJghVvSKNd1xRzRVga4Gghi3N3QPHkt47vvuLu2rYmcZ43L3ig8zTH2W9B0qF00zL2F5c3O5dsKG99yUfjnQOFmdJfpZisSQScIB1hXf6JrLwW8X47waAREsskQbRsw0ek0uv4s2uObT3yT8TZFhgajXV3s08O6oWEVVtVgGSP2Abn2W9fkciukwZ12soKDkQr2X11uYGDM85YZkeyK9fcXgVlKXReAwgLF9qi5ggDWynqVXxKOZlP8tjVmRszmN4sPVHNS0KYJT5bO9Ikm98ulXSjBb3LQWLrxu4fl3Eoj274CCrLJnoIEsbHlqYT8peEKeZ2uqG16HQX9CdMrDelm3shQztq6RElsP5UOL2Z3hAcpNbeQ9lCMmDQqeVIicCl9nqXO5HOGw0EE6akvhTb3s4Vqni65R9O1yhGc8p62oEZvKDullLFjtrr4Vf0UvKArjqKQ5WkC67fnsIk0PEeUR4Uanz4vxEJu3G99I5QbDxwIJ4XjpB3oa0jyQld1ASbOBD0fNCWx18M4fceDozuBo8toItiskZlaTqOw8rhN00SlsyGUxaF3GhEtUvl4bC7OjHGL8jYsl0NENimY64oE710NcR6gAfaandjcoFjAZo04ETnxPUxKEeWQb93d6v1rZVBhmyWiNNEfCH7NERXtV3T6JhKGUNNRuqcAFNJoNvrfeXYLic9mmw44gzafxtNv1ZCg5rFoth24IUcPFQhoalJDRdwfdnRMphkcvm14H4goSHPFyMQQe9fBXi1PPnutiIZAbZo1H95VKs5We49AjzuE3BW4W2M9wmJ9tnigPFK5JkXxwkrEb
----- END MESSAGE -----
```


Below it was a single line that set the tone for the next hour of my life:

>

*“You have 2 seconds to hash this message using the SHA512 algorithm and send the answer back.”*


Two seconds. That wasn’t just a task — that was a challenge to my reaction time.

>

*At first, I laughed. “Easy,” I thought.
Copy the message, run a quick *`*sha512sum*`*, paste the hash back, done.*


Except… the moment I reloaded the page, the message changed.
Every time — a new string.


That’s when I realized what was really going on. This wasn’t about computing a hash. It was about automation and precision under pressure.


Manual work was impossible. The only way to win this race was with a script.


So, I opened VS Code and began typing. A simple Python script using `requests`, `re`, and `hashlib` — nothing fancy, just something to fetch the message, strip the tags, compute the SHA-512 digest, and send it back.


```
import requests, re, hashlib

url = "http://challenges.ringzer0team.com:10013/"
r = requests.get(url)
m = re.search(r"----- BEGIN MESSAGE -----(.*?)----- END MESSAGE -----", r.text, re.S)
msg = m.group(1).replace("<br />", "").strip()
h = hashlib.sha512(msg.encode()).hexdigest()
print(h)
```


I ran it, expecting fireworks.
Instead, I got an error that every programmer dreads:


```
AttributeError: 'NoneType' object has no attribute 'group'
```


My beautiful regex couldn’t even find the message. I checked the source HTML, and there it was — the culprit — hundreds of `<br />` tags and broken line spacing. The message wasn’t one solid block of text; it was a fragmented mess.


## Get SHENOBIE’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Fine. Regex could adapt. I rewrote the extraction to handle any combination of `<br>` and whitespace.


```
pattern = r"----- BEGIN MESSAGE -----\s*<br\s*/?>\s*(.*?)\s*<br\s*/?>\s*----- END MESSAGE -----"
```


Now the DNS resolver decided to join the challenge.


The problem wasn’t just in the code anymore — it was in the network stack itself. The server couldn’t be reached, and I only had two seconds to respond once it did.


I took a deep breath, sipped what was left of my coffee, and decided to go full-engineer mode.
If the DNS wanted to play games, I’d play smarter.


I built a resilient, no-nonsense Python script that could handle everything: messy HTML, DNS resolution, timeouts — even fallback to direct IP communication. It would retry intelligently and report exactly what was going on.


Here’s the final form — the one that finally conquered the challenge:

>

*The Final Script: *`*script_fixed.py*`


Save this as `script_fixed.py`, make it executable (`chmod +x script_fixed.py`) and run `python3 script_fixed.py`


```
#!/usr/bin/env python3
"""
script_fixed.py
Robust client for RingZer0 "Hash me if you can" challenge.

- Extracts the dynamic message from the page
- Computes SHA-512 (exact bytes of the extracted message)
- Submits ?r=<sha512>
- Handles DNS failures and attempts IP+Host fallback
- Prints flag or helpful diagnostics on failure
"""
import requests
import re
import hashlib
import socket
import subprocess
import sys
import html
import time

from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry

URL = "http://challenges.ringzer0team.com:10013/"
HOSTNAME = "challenges.ringzer0team.com"

def make_session():
s = requests.Session()
retries = Retry(total=3, backoff_factor=0.2, status_forcelist=(500,502,503,504))
s.mount("http://", HTTPAdapter(max_retries=retries))
return s

def http_get(session, url, headers=None, timeout=3):
return session.get(url, headers=headers, timeout=timeout)

def extract_message(html_text):
# Try a few flexible patterns; handle <br>, <br/> and raw text
patterns = [
r"----- BEGIN MESSAGE -----\s*(?:<br\s*/?>\s*)*(.*?)\s*(?:<br\s*/?>\s*)*----- END MESSAGE -----",
r"----- BEGIN MESSAGE -----\s*(.*?)\s*----- END MESSAGE -----",
]
for p in patterns:
m = re.search(p, html_text, re.S | re.I)
if m:
raw = m.group(1)
# remove <br> tags and any other html tags
raw = re.sub(r'<br\s*/?>', '', raw, flags=re.I)
raw = re.sub(r'<[^>]+>', '', raw)
raw = html.unescape(raw)
return raw.strip()
return None

def resolve_with_socket(host):
try:
infos = socket.getaddrinfo(host, None)
ips = []
for info in infos:
ip = info[4][0]
if ip not in ips:
ips.append(ip)
return ips if ips else None
except socket.gaierror:
return None

def resolve_with_commands(host):
# Try dig, nslookup, getent if available
cmds = [
["dig", "+short", host],
["nslookup", host],
["getent", "hosts", host],
]
for cmd in cmds:
try:
out = subprocess.check_output(cmd, stderr=subprocess.DEVNULL, text=True)
lines = [l.strip() for l in out.splitlines() if l.strip()]
ips = []
for l in lines:
# lines can be "x.x.x.x" or "x.x.x.x hostname"
parts = l.split()
for p in parts:
if re.match(r'^\d+\.\d+\.\d+\.\d+$', p):
if p not in ips:
ips.append(p)
if ips:
return ips
except (FileNotFoundError, subprocess.CalledProcessError):
continue
return None

def print_dns_help():
print("\nDNS seems broken on this machine. Quick checks / fixes:")
print(" - Can you ping a public IP? ping -c3 1.1.1.1")
print(" - Try resolving from a public DNS server:")
print(" dig +short {0} @1.1.1.1".format(HOSTNAME))
print(" - If you can get the server IP from another machine, add it temporarily:")
print(" sudo sh -c 'echo \"<IP> {0}\" >> /etc/hosts'".format(HOSTNAME))
print(" - Or set a working resolver (temporary):")
print(" sudo sh -c 'echo \"nameserver 1.1.1.1\" > /etc/resolv.conf'")
print(" - If you're behind a restrictive network, try a VPN or different network.\n")
try:
print("--- /etc/resolv.conf ---")
with open("/etc/resolv.conf") as f:
print(f.read())
except Exception as e:
print("Could not read /etc/resolv.conf:", e)

def find_flag_in_html(html_text):
# common patterns
m = re.search(r'FLAG\{.*?\}', html_text)
if m:
return m.group(0)
m = re.search(r'FLAG[-_\w\d]{8,}', html_text)
if m:
return m.group(0)
m = re.search(r'<div class="alert alert-info">(.*?)</div>', html_text, re.S|re.I)
if m:
return m.group(1).strip()
return None

def main():
session = make_session()

print("Fetching challenge page...")
try:
resp = http_get(session, URL, timeout=3)
except requests.exceptions.RequestException as e:
errstr = str(e)
print("Initial request failed:", errstr)
# Detect name resolution failure patterns
cause = getattr(e, "__cause__", None)
is_dns_error = ("NameResolutionError" in errstr) or ("Temporary failure in name resolution" in errstr) \
or isinstance(cause, socket.gaierror) or ("Failed to resolve" in errstr)
if is_dns_error:
print("DNS resolution failed. Attempting alternate resolution methods...")
ips = resolve_with_socket(HOSTNAME)
if not ips:
ips = resolve_with_commands(HOSTNAME)
if ips:
print("Resolved IP(s):", ips)
# attempt to contact each IP using Host: header
for ip in ips:
ip_url = f"http://{ip}:10013/"
print("Trying", ip_url, "with Host header", HOSTNAME)
try:
r = http_get(session, ip_url, headers={"Host": HOSTNAME}, timeout=4)
if r.status_code == 200:
resp = r
print("Success using IP", ip)
break
else:
print("Got HTTP", r.status_code, "from", ip)
except requests.exceptions.RequestException as e2:
print("Failed to connect to", ip, ":", e2)
if 'resp' not in locals():
print("Tried resolved IPs but could not fetch page.")
print_dns_help()
sys.exit(1)
else:
print("Could not resolve host via socket or system tools.")
print_dns_help()
sys.exit(1)
else:
print("Network error (not DNS). Full exception:")
print(repr(e))
sys.exit(1)

# At this point 'resp' should be a requests.Response
html_text = resp.text
message = extract_message(html_text)
if not message:
print("Couldn't find the message block in the page. Dumping first 1000 chars for inspection:")
print(html_text[:1000])
sys.exit(1)

print("Extracted message (len={}):".format(len(message)))
# Uncomment below to print message for debugging:
# print(message)

# Compute SHA-512
digest = hashlib.sha512(message.encode("utf-8")).hexdigest()
print("SHA-512:", digest)

# Submit answer
submit_url = URL + "?r=" + digest
print("Submitting to:", submit_url)
try:
r2 = http_get(session, submit_url, timeout=4)
except requests.exceptions.RequestException as e:
# If submission failed due to DNS and we have an IP fallback from earlier, try IP fallback
print("Submission request failed:", e)
# attempt IP fallback again
ips = resolve_with_socket(HOSTNAME) or resolve_with_commands(HOSTNAME)
if ips:
for ip in ips:
try:
r2 = http_get(session, f"http://{ip}:10013/?r={digest}", headers={"Host": HOSTNAME}, timeout=4)
break
except Exception:
r2 = None
if not r2:
print("Submission failed and IP fallback didn't work. See DNS/network hints above.")
sys.exit(1)

# Parse response
flag = find_flag_in_html(r2.text)
if flag:
print("\n=== FLAG ===\n", flag)
else:
# print small helpful snippet from page
if "Wrong answer" in r2.text or "too slow" in r2.text:
print("\nServer responded: Wrong answer or too slow.")
else:
print("\nServer response (truncated):\n", r2.text[:1000])

if __name__ == "__main__":
main()
```


It wasn’t pretty, but it was powerful. It could resolve hosts manually, retry connections, and hash the message instantly. I ran it with a sense of anticipation that only CTF players understand — the moment before code meets challenge.


```
└─$ python3 script_fixed.py
Fetching challenge page...
Extracted message (len=1024):
SHA-512: a23dca1da70398ac723e4f1a73fe7f81478716b4dfe6969faf44a61dd655adcf8e4e549a089606e992d3b4618d624fcb83ac72c7f8171182315ae6a27e7d6a27
Submitting to: http://challenges.ringzer0team.com:10013/?r=a23dca1da70398ac723e4f1a73fe7f81478716b4dfe6969faf44a61dd655adcf8e4e549a089606e992d3b4618d624fcb83ac72c7f8171182315ae6a27e7d6a27
```


The output paused for half a second. Then, on the screen, in the glow of my terminal:

---

*Originally published on [Medium](https://infosecwriteups.com/hash-me-if-you-can-how-i-beat-a-2-second-hashing-challenge-on-ringzer0team-a61cf0a87291). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
