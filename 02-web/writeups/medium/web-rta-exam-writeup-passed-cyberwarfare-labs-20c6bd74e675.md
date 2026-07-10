# :globe_with_meridians: Web-RTA Exam Writeup - Passed | CyberWarFare Labs

---

## WebApp 01

## Reconnaissance

Starting with the provided IP, the first step is directory enumeration:

bash

```
feroxbuster -u http://<WEBAPP01_IP>:<PORT> -w /usr/share/wordlists/dirb/common.txt
```

The root page redirects to a login page. Note the URL structure — the `/dashboard` endpoint will matter shortly.

## Flag 5 — Anonymous User Role

Navigating to the login page, there’s a CAPTCHA + username/password form. Skip trying to brute force it for now.

Instead, go directly to `/dashboard` without logging in. The application loads and reveals your current role in the UI:

- Flag 5: The role allocated to unauthenticated users → `anonymous`

- Flag 6: The endpoint where events are available → `/dashboard`

## JWT Token Manipulation

While on the dashboard as an anonymous user, open Burp Suite and inspect the cookies. There’s an `access_token_cookie` - paste it into jwt.io.

The decoded payload reveals:

json

```
{
"role": "anonymous",
"username": "anonymous"
}
```

The token uses `algorithm: none` - meaning there's no signature verification. This is a classic JWT vulnerability.

Modify the payload:

json

```
{
"role": "user",
"username": "user"
}
```

Remove the signature entirely (keep the trailing dot), update the cookie in your browser (Storage tab in DevTools or via Burp), and reload the page.

You’re now authenticated as a user-role account. The dashboard now shows an event:

## Flag 7 — Event Name

The event visible to authenticated users:

## Flag 8 — Admin Username Discovery

The event details show it was created by a specific user. That username is:

- Flag 8: `notatypicalsysadmin`

## SQL Injection — Admin Login Bypass

Log out and return to the login page. Enter `notatypicalsysadmin` as the username. Leave the password empty for now - but fill in the CAPTCHA correctly first.

Key insight: The application validates the CAPTCHA before checking credentials. If the CAPTCHA is correct, the response will confirm whether the username exists. This is an information disclosure vulnerability that lets you enumerate valid usernames.

Once you’ve confirmed the username is valid, exploit the SQL injection:

- Flag 10: The value of the flag in WebApp 01 → `flag` (the username found in `/etc/passwd`)

## Flags 11, 12 & 13 — SSRF via Check Outage

Click Check Outage → Check Our Status. The application makes an internal request and returns service health data. Observing the response, it’s hitting:

Now scroll down to the Fetch Status section. There’s a “Service URL” input field and a Fetch Secret button — a classic SSRF endpoint.

Step 1: Enter `http://127.0.0.1:8000` and submit. The server returns a `418` status code (I'm a teapot) - the service is alive but rejects plain requests.

Step 2: URL-encode the target URL and resubmit:

```
http%3A%2F%2F127.0.0.1%3A8000
```

This time the server returns an encoded response with the label “hidden in layers”.

- Flag 12: The encoded data returned → a hex-encoded Base64 string

Step 3: Decode it — it’s hex that, when decoded, gives Base64. Decode the Base64:

bash

```
echo "<hex_string>" | xxd -r -p | base64 -d
```

The final decoded output contains credentials: a username and password.

- Flag 13: The plaintext version of “hidden in layers” → the decoded credentials (username:password pair)

---
