# :globe_with_meridians: Finding SSRF BY Full Automation

---

# Finding SSRF BY Full Automation

Hi, everyone

My name is Santosh Kumar Sha, I’m a security researcher from India(Assam). In this article, I will be describing how I was able to Find SSRF vulnerability by by automating it and leak private information amazon metadata, ec2 and cloud services.

>

I am now offering 1:1 sessions to share my knowledge and expertise:[topmate.io/santosh_kumar_sha](https://topmate.io/santosh_kumar_sha)

## TIP For looking for SSRF bug with automation:

Tools Requried:

- gf (tomnomnom) — [https://github.com/tomnomnom/gf](https://github.com/tomnomnom/gf)

- qsreplace(tomnomnom) — [https://github.com/tomnomnom/qsreplace](https://github.com/tomnomnom/qsreplace)

- ffuf — [https://github.com/ffuf/ffuf](https://github.com/ffuf/ffuf)

- gau(Corben) — [https://github.com/lc/gau](https://github.com/lc/gau)

- waybackurls(tomnomnom) — [https://github.com/tomnomnom/waybackurls](https://github.com/tomnomnom/waybackurls)

## Case#1 — — Accessing SSRF metadata with automation by just using curl and bash

Here get access to internal metadata by ssrf we will collect all URL from way-back machine and look for access the internal data by ssrf

Suppose the the target is targetme.com

Now here process the process for find the ssrf to access internal metadata

Command for getting the URL:

waybackurl targetme.com >> blindssrftesturl.txt

---
