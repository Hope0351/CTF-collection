# CTF Communities and Event Listings

This file consolidates the community and event-listing references from my
learning path. Instead of linking out, I keep the descriptions here so
the collection stays self-contained.

---

## CTFtime

**What it is.** The central hub of the CTF community. It lists upcoming
CTF events, archives past events with writeup links, ranks teams
globally and per-country, and hosts a calendar of the competitive CTF
season.

**How I use it.**
- **Event list** — browse upcoming CTFs, filter by format (Jeopardy,
  Attack-Defense), weight (rating), and location.
- **Team page** — track my team's rating and the events we've played.
- **Writeup archive** — after a CTF ends, teams post writeup links to
  the event's CTFtime page. This is the canonical place to find other
  teams' solutions for comparison.
- **Calendar** — subscribe to the CTFtime calendar so I never miss a
  major event.

**Notes.**
- A CTF's "weight" on CTFtime reflects how much it counts toward the
  global ranking. Higher-weight CTFs are more prestigious.
- The writeup archive is community-moderated. Quality varies; the
  top-placing teams' writeups are usually the best.

---

## LiveOverflow Discord

**What it is.** The official Discord server of LiveOverflow, a
popular security education YouTuber. The server is one of the more
active CTF-focused communities on Discord and is a good place to ask
questions, find teammates, and hear about upcoming events.

**How I use it.**
- Browse the `#ctf` channel for announcements of small/medium CTFs.
- Use the `#help` channels for specific technical questions — but
  search first, as common questions have been answered.
- The community is generally beginner-friendly; don't be afraid to ask.

**Notes.**
- Discord invites rotate; if the official invite expires, check
  LiveOverflow's latest YouTube video description for a fresh link.
- Many other CTF communities exist on Discord (dicegang, corCTF, picoCTF
  etc.). Join the ones for CTFs I play regularly.

---

## OWASP Top 10

**What it is.** The Open Worldwide Application Security Project's
standard awareness document for developers and web-application security.
It lists the ten most critical web-application security risks, updated
every few years based on industry data. The current version is OWASP
Top 10:2021.

**The 2021 list (in order).**
1. **Broken Access Control**
2. **Cryptographic Failures** (formerly "Sensitive Data Exposure")
3. **Injection** (now includes XSS; XSS was split out into its own
   category in 2013 but was re-merged in 2021)
4. **Insecure Design**
5. **Security Misconfiguration**
6. **Vulnerable and Outdated Components**
7. **Identification and Authentication Failures**
8. **Software and Data Integrity Failures**
9. **Security Logging and Monitoring Failures**
10. **Server-Side Request Forgery (SSRF)**

**How I use it.**
- When I encounter a web challenge, mentally walk the Top 10 to ensure
  I'm not missing an obvious vulnerability class.
- Each entry on the OWASP site has example scenarios and prevention
  guidance — useful when writing up a challenge and explaining *why* the
  vulnerability exists.

**Notes.**
- The Top 10 is an awareness list, not a comprehensive vulnerability
  taxonomy. CTFs will often test vulnerabilities outside the Top 10
  (e.g., prototype pollution, SSTI, deserialization).
- Read the full document at least once. The prevention guidance is as
  valuable as the attack descriptions.

---

## Source attribution

The descriptions above were written in my own words based on the
official landing pages of each community/resource, downloaded on
2026-07-11 for reference. The communities themselves are not reproduced
here — only my notes about them.
