# :globe_with_meridians: How this team accidentally found a SSRF in Slack exposing AWS credentials! A $4000 bug bounty

> **Original Source:** [How this team accidentally found a SSRF in Slack exposing AWS credentials! A $4000 bug bounty](https://infosecwriteups.com/how-this-team-accidentally-found-a-ssrf-in-slack-exposing-aws-credentials-a-4000-bug-bounty-513be19286e)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How this team accidentally found a SSRF in Slack exposing AWS credentials! A $4000 bug bounty


## Complex libraries lead to hidden attack vectors


This is an inspiring story for all bug bounty hunters of how a SSRF vulnerability was discovered in Slack, along with potentially many other web applications, by [Brett Buerhaus](https://twitter.com/bbuerhaus), [Cody Brocious](https://twitter.com/daeken), [Sam Erb](https://twitter.com/erbbysam), and [Olivier Beg](https://twitter.com/smiegles)’s. I will be detailing a more user-friendly version of their detailed “[A Tale of Exploitation in Spreadsheet File Conversions](https://buer.haus/2019/10/18/a-tale-of-exploitation-in-spreadsheet-file-conversions/),” and all the material I’m presenting is sourced from Brett’s writing. I highly encourage the read for the more technical details.


I will also include the message from Slack regarding the vulnerability for transparency

>

Slack would like to thank the researchers for their work to increase the security of the open source tool LibreOffice and their responsible disclosure to Slack. The security of file sharing is critically important to Slack and its users, and we worked with the research team to quickly implement a fix within 24 hours of receiving the report. Slack has confirmed that no customer data was accessed using this bug. (source: [A Tale of Exploitation in Spreadsheet File Conversions](https://buer.haus/2019/10/18/a-tale-of-exploitation-in-spreadsheet-file-conversions/) by Brett Buerhaus and co.)


*AI-generated art of “slack with sad face next to it illustration” by craiyon.com*

## Reconnaissance: Spreadsheet fingerprinting

---

*Originally published on [Medium](https://infosecwriteups.com/how-this-team-accidentally-found-a-ssrf-in-slack-exposing-aws-credentials-a-4000-bug-bounty-513be19286e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
