# :globe_with_meridians: $300 Bounty: SSRF to Cloud Metadata

---

# $300 Bounty: SSRF to Cloud Metadata

>

One Internal Request All Your Secrets: The Phabricator SSRF Story

In 2015 a cleverly exploited Server-Side Request Forgery (SSRF) vulnerability in Phabricator earned bug hunter agarri_fr a modest yet significant $300 bounty. This flaw shed light on the hidden dangers of SSRF particularly its ability to access sensitive cloud metadata services from within a server. The incident not only highlighted a critical security oversight but also set a precedent for how cloud-hosted applications should handle internal network vulnerabilities. Let’s explore the full story its technical underpinnings its far reaching impact and actionable lessons for bug hunters and developers alike.

### The Vulnerability at a Glance

- Bug Type: SSRF (Server-Side Request Forgery)

- Target: Phabricator meme generation feature

- Impact: Access to internal services including EC2 / OpenStack metadata

- Bounty: $300

- Reported By: agarri_fr

The vulnerability originated in a seemingly innocuous feature of Phabricator, an open source software suite for collaborative coding and project management. This feature allowed users to upload or specify external image URLs to create memes. However, the lack of robust input validation or restriction on these URLs created a gateway for exploitation. Attackers could manipulate the input to point to internal IP addresses bypassing typical security controls and exposing sensitive data.

As a result an attacker could supply internal IP addresses instead of public URLs.

But here’s where it gets interesting

>

Why Local IP Addresses Are Dangerous

Cloud platforms like Amazon EC2 and OpenStack expose a special internal web server at:

```
http://169.254.169.254/
```

This server is only accessible from inside the machine, and it provides sensitive metadata about the instance, such as:

- Hostname

- Internal and external IPs

- IAM roles and credentials

- User data (sometimes containing scripts, passwords, private keys)

For example:

```
http://169.254.169.254/latest/meta-data/hostname
http://169.254.169.254/latest/user-data
```

By abusing SSRF, an attacker could trick Phabricator into sending HTTP requests to this metadata server exposing sensitive internal data.

### The Impact

With access to /latest/user-data, an attacker could retrieve

- Startup scripts

- Hardcoded secrets

- Private SSH keys

- API tokens

- Custom configuration

In some cloud environments this could enable lateral movement privilege escalation or even full environment compromise.

### The Fix

Initially a previous SSRF report was closed as Won’t Fix underestimating the impact of internal only requests.

## Get Monika sharma’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

But once the attacker demonstrated the risk of targeting link-local/private IPs the assessment changed.

>

Phabricator patched the vulnerability by

- Blocking requests to 169.254.169.254

- Adding a blacklist for private IP ranges

- Improving granularity and visibility of outbound request behavior

### Key Takeaways for Bug Hunters

- Always test SSRF for internal IPs (127.0.0.1, 10.x.x.x, 192.168.x.x, 169.254.x.x)

- Target metadata endpoints in cloud environments

- SSRF isn’t just about accessing websites it’s about pivoting into internal services

- Even if earlier reports were marked won’t fix a stronger impact story can change triage

### Final Thoughts

The Phabricator SSRF vulnerability is a classic case study of how a seemingly minor bug can evolve into a critical cloud security issue. Its $300 bounty underscores the value of identifying and reporting such flaws, even in less obvious contexts. As cloud adoption grows, metadata services remain a lucrative target for attackers, making vigilance essential.

Have you tested your SSRF targets for metadata access recently? If not now’s the perfect time to start. Share your findings or questions in the comments I’d love to hear from you!

If you enjoyed this deep dive consider following for more bug bounty breakdowns security insights and technical tutorials. Support my work by buying me a coffee to fuel my next investigation. Let’s keep hunting and learning together!

Monika ✨

---
