# :globe_with_meridians: Investigate Web Attacks Challenge (Let’s Defend)

---

*Web Attack Investigated — Earned Badge*

## 1. Which automated scan tool did the attacker use for web reconnaissance?

During the first phase of the attack, I needed to identify which scanning tool the attacker used. To do this, I reviewed the web server logs, paying attention to unusual **User-Agent** strings, which often provide clues about automated tools used.

I scrolled through the logs searching for odd patterns and used the following `grep` command from a Linux console to speed up the search:

```
grep 'Mozilla/5.0' access.log | sort | uniq -c | sort -nr
```

Upon reviewing the logs, at line 30 I found **Nikto** in the User-Agent string, indicating that the attacker used **Nikto**, a popular web vulnerability scanning tool.

**Answer**: Nikto

---
