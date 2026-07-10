# :mag: ProtoVault Breach Forensics Challenge Offsec CTF Week 1

---

# ProtoVault Breach Forensics Challenge Offsec CTF Week 1

*Source : [https://www.offsec.com/events/the-gauntlet/](https://www.offsec.com/events/the-gauntlet/)*

M*averick is back again with a fresh article this time I dug into ProtoVault Breach, the Week 1 forensics challenge from the Offsec CTF. Unlike a typical pentest-style box, this one lived squarely in the forensic mindset: examining artifacts, piecing together timelines, and extracting the story hidden in data.I cleared the challenge in just a few minutes a neat reminder that a disciplined, methodical approach pays off. That said, “quick” didn’t mean trivial for everyone. Several parts of the challenge were deceptively subtle, and I can see how they’d slow down players who skipped careful enumeration or jumped straight to assumptions.This write-up keeps things practical and human: I’ll show the exact steps I took to recover and interpret the evidence, point out the little gotchas that can trip you up, and share takeaways that will help you sharpen your forensic workflow for future CTFs or real incident investigations.Ready to rewind the timeline and follow the breadcrumbs? Let’s get into the artifacts and analysis.*

### 1- Investigate if the leak originated from the application. Inspect the database connection string for security flaws and submit the full string as your answer

---
