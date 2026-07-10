# :game_die: I Found an SQL Injection in an Internal API (Behind Cloudflare) — A Full Story from Discovery to Data Dump

---

# I Found an SQL Injection in an Internal API (Behind Cloudflare) — A Full Story from Discovery to Data Dump

*Image by Pixabay*Hello Medium family! I’m back — and I’m writing this blog with happiness and excitement.
As a penetration tester, few things are more thrilling than finding a real, exploitable vulnerability — especially during internal security assessments, where your discoveries lead to real impact, better defenses, and improved trust in systems.

This post is a deep dive into how I discovered and exploited an SQL Injection vulnerability in one of our internal APIs, despite it being behind Cloudflare WAF and using a PostgreSQL backend. I’ll walk you through the story from the first scan in Burp Suite to bypassing defenses and dumping sensitive data with SQLMap.

By the end of this post, you’ll learn:

- How to find SQLi using Burp Suite

- How to verify injections manually

- SQLMap commands with real examples

- WAF evasion tricks

- Responsible testing practices

Let’s dive in.

### Setting the Stage: Internal Penetration Testing

As part of a scheduled internal assessment, I was asked to test the security of our…

---
