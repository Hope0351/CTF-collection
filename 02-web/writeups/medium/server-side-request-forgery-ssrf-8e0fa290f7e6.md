# :globe_with_meridians: Server-Side Request Forgery (SSRF)

---

# Server-Side Request Forgery (SSRF)

## Broken Access Control (BAC) > Server-Side Request Forgery (SSRF)

*Photo by [Justaf Abduh](https://unsplash.com/@jabacule?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

### What is SSRF?!

Server-Side Request Forgery (SSRF) is an exploit use to attack internal systems behind firewalls that are not accessible from external networks. SSRF is to access internally running services like SSH, Local-Host, FTP, and others. An SSRF scenario would be to force the server to make a connection to internal-only services within the organization’s infrastructure.

### Intro:

Testing TripAdvisor for vulnerabilities and bugs, I found that it was vulnerable to SSRF. I found this vulnerability using the Burp Suite feature Collaborator. *What is Burp Collaborator*? Burp Collaborator is a network service that Burp Suite uses to help discover many kinds of vulnerabilities. For example, Some injection-based vulnerabilities can be detected using payloads that trigger an interaction with an external system when successful injection occurs.

### This Is How I Did It:

- Open Burp Suite>Burp menu>Burp Collaborator client and select “Burp Collaborator client”

- Click where it says “Copy to clipboard” this will copy the payload needed to exploit the web app ex: `jhggfwo94wu094ctrtrstwrvterwt0tvwg.burpcollaborator.net`

---
