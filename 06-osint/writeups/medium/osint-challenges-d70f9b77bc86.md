# :sleuth_or_spy: OSINT Challenges. Learning to find the Treasure Trove of…

---

# OSINT Challenges

## Learning to find the Treasure Trove of Information

*In my previous *article* I mentioned few OSINT tools that can be used for passive reconnaissance. In this article I’ll be attempting some HTB OSINT challenges. OSINT is also one of the key skills essential during the Reconnaissance phase of the Red Team assessment.*

*Photo by [Roman Kraft](https://unsplash.com/@romankraft?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

## Scenario 1 - Understand SPF, DKIM and DMARC

Customers of secure-startup.com have been recieving some very convincing phishing emails, can you figure out why?1st Flag

2nd Flag

There is a clue in the first half flag. SPF.

What is SPF?

Sender Policy Framework is a technique for email authentication techniques which has been superseded by DKIM (Domain Keys Identified Mail) followed by DMARC.

What is DMARC??

[DMARC](https://dmarc.org) - Domain-based Message Authentication and Reporting Conformance is an email authentication policy build on SPF and DKIM protocols to determine the authenticity of an email.

---
