# :globe_with_meridians: Breaking Twitter’s VPN: $20,160 Bounty for a Pre-Auth RCE via Pulse Secure Chain

---

# Breaking Twitter’s VPN: $20,160 Bounty for a Pre-Auth RCE via Pulse Secure Chain

## How Orange Tsai & Meh Chang Combined File Read, Session Hijack, and Admin Injection to Breach Twitter’s Internal Network

### Introduction

In one of the most iconic SSL VPN exploit chains ever demonstrated, legendary researcher Orange Tsai (of DEVCORE) revealed a pre-authentication remote code execution vulnerability on Twitter’s infrastructure through an unpatched Pulse Secure SSL VPN instance. This disclosure earned a bounty of $20,160 and was later showcased at Black Hat USA 2019.

This case study highlights the dangerous impact of leaving VPN appliances unpatched and how multiple CVEs were masterfully chained to pivot from external access to full control over internal systems.

### Vulnerability Chain Overview

CVEs Used:

- CVE-2019–11510 — Pre-auth File Disclosure (CVSS 10.0)

- CVE-2019–11542 — Post-auth Admin RCE (CVSS 8.0)

- Other supporting CVEs: 11508, 11539, 11540, 11538

These vulnerabilities were chained as:

- File read to steal cached plaintext passwords

- Hijack sessions and 2FA bypass using Duo credentials

- Access admin panel and trigger command injection

### Step-by-Step Exploitation

- Exploiting CVE-2019–11510

The attackers started by reading sensitive files directly from the VPN without authentication:

```
/etc/passwd
/etc/hosts
/data/runtime/mtmp/system
/data/runtime/mtmp/lmdb/dataa/data.mdb
```

Crucially, dataa/data.mdb contained plaintext VPN user credentials, as Pulse Secure cached them post-login.

2. Duo 2FA Bypass

With the integration key, secret key, and hostname for Duo.com 2FA stored in mtmp/system, the attackers effectively reconstructed the authentication backend — a massive oversight in credential hygiene.

Treat your secret key like a password, Duo’s docs warn. Twitter hadn’t.

3. Session Hijacking

Because Pulse Secure stored sessions in LMDB and Roaming Session wasn’t enabled, the researchers reused legitimate session tokens to log in as any user.

4. Admin Panel Access & RCE

## Get Monika sharma’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

The cherry on top? The VPN’s internal admin interface was exposed through a web proxy:

```
https://<target>/admin/
```

Using CVE-2019–11542, they gained command injection and arbitrary code execution from the admin context. No need to brute-force hashes; they just waited for the admin to log in and stole the session.

### Impact

The researchers confirmed:

- Access to Twitter’s intranet

- Staff credentials (plaintext)

- LDAP passwords

- Internal services

- Private keys

- Sessions for Okta, Google, Salesforce

- Potential for pivoting to all VPN-connected clients

This level of access is nothing short of total compromise.

### Recommendations

Update your VPN software. Immediately.

Patch management is often overlooked in appliances, but Pulse Secure was publicly known to be vulnerable months earlier.

### Takeaways for Bug Hunters

- Look for unpatched third-party appliances, especially SSL VPNs like Pulse Secure, Fortinet, and Citrix.

- Pre-auth file reads can expose passwords, session tokens, and 2FA secrets.

- Session hijacking remains a critical risk in misconfigured VPNs.

- Chain read ➝ hijack ➝ RCE for maximum impact.

### Credit

- Hunter: orange

- Bounty: $20,160

- Report ID: #591295

### Final Thoughts

This vulnerability wasn’t just a bug — it was a masterclass in chaining subtle flaws into a high-impact breach. It’s no wonder this earned Orange Tsai a $20,160 reward and cemented the exploit as one of the most sophisticated VPN attacks ever reported.

>

Thank you[☕](https://buymeacoffee.com/monikaak47)✨

---
