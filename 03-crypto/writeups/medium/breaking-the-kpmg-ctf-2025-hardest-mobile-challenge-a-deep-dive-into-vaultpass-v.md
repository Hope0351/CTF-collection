# :locked_with_key: Breaking the "KPMG CTF 2025 Hardest Mobile Challenge": A Deep Dive into VaultPass v2

---

# Breaking the "KPMG CTF 2025 Hardest Mobile Challenge": A Deep Dive into VaultPass v2

How I exploited Firebase misconfigurations and hardcoded credentials to solve KPMG CTF’s most challenging mobile security puzzle.

## *The Challenge*

As part of the KPMG CTF 2025 Mobile Challenge, I tackled a task called “VaultPass v2” — a 35MB Android APK named VaultPass.apk. The challenge promised to test advanced mobile security skills, and it certainly delivered on that promise.

Challenge Details:

- Target: VaultPass_v2.apk

- Difficulty: Advanced

- Skills Required: Mobile reverse engineering, cloud security, API exploitation

The goal was simple: find the flag. The path to get there? Not so much.

## Phase 1: APK Reverse Engineering — Peeling Back the Layers

My first step was to reverse engineer the APK using `jadx`, a powerful Java decompiler:

```
jadx -d decompiled_apk VaultPass_v2.apk
```

This extracted 11,030 Java source files, a substantial mobile application with plenty of attack surface to explore.

Now here’s where most people would start reading through MainActivity.java or looking for obvious vulnerabilities. But I’ve learned that the real secrets often hide in the most boring places…

## Get Stalin Prevan Crasta’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Pro Tip: Always check `strings.xml` first. Developers love hiding things there.

```
<string name="firebase_api_key">AIzaSyDlBKScfkI6wjj99mRQG08qZ2BuY2iOMww</string>
<string name="firebase_project_id">demofirebaseapp-58025</string>
<string name="firebase_database_url">https://demofirebaseapp-58025-default-rtdb.asia-southeast1.firebasedatabase.app</string>
```

Bingo! I found Hardcoded API key, these are a critical security vulnerability. This immediately opened up several attack vectors.

## Deep Link Analysis

Further analysis revealed the app implemented a custom deep link handler:

- Deep Link: `vaultpass://getflag`

- Target Activity: `AdminPanelActivity`

- Protection: SharedPreferences validation

## Phase 2: The “Almost Protect” Phenomenon

## Firebase Database Properly Secured… Almost

My initial attempt to access the Firebase database directly failed:

```
curl "https://demofirebaseapp-58025-default-rtdb.asia-southeast1.firebasedatabase.app/.json"
# Result: "Permission denied"
```

The database was properly configured with security rules and no unauthenticated access allowed. This looked like good security practice on the surface.

## External Resource Discovery

However, the hardcoded credentials allowed me to discover the Firebase project’s external resources:

The project existed and was accessible, revealing the infrastructure was live and potentially exploitable.

## Phase 3: The Authentication Bypass

## Firebase Identity Toolkit Discovery

Here’s where the “almost protect” concept came into play. While the database was secured, the Firebase Authentication service had a critical misconfiguration — it allowed anonymous user registration using the leaked API key.

## Exploiting Anonymous Authentication

I crafted a request to create an anonymous user:

```
curl -X POST \
"https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=AIzaSyDlBKScfkI6wjj99mRQG08qZ2BuY2iOMww" \
-H "Content-Type: application/json" \
--data '{"returnSecureToken": true}'
```

Success! The API returned:

- A valid JWT token

- A refresh token

- A local user ID

This legitimate authentication token was the key to bypassing all the database security rules.

## Phase 4: The Final Breakthrough

## Authenticated Database Access

With a valid authentication token in hand, I could now access the protected database:

```
curl -H "Authorization: Bearer [TOKEN]" \
"https://demofirebaseapp-58025-default-rtdb.asia-southeast1.firebasedatabase.app/admin/secrets/flag_payload.json?auth=[TOKEN]"
```

Result:

```
S1BNR19DVEZ7bTBiMWwzX20xNWMwbmYxNl9kMzNwbDFuazVfM3hwMDUzZH0=
```

The response was Base64 encoded. Decoding it revealed the flag:

```
KPMG_CTF{m0b1l3_m15c0nf16_d33pl1nk5_3xp053d}
```

The flag cleverly spelled out “mobile misconfiguration deep links exposed”, a perfect summary of the vulnerability chain I’d just exploited.

---
