# :globe_with_meridians: Supply Chain Attacks on the risk - Open Source Security

> **Original Source:** [Supply Chain Attacks on the risk - Open Source Security](https://infosecwriteups.com/supply-chain-attacks-on-the-risk-open-source-security-ee7a8cf1ec58)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Supply Chain Attacks on the risk - Open Source Security


## Supply Chain Attack Background — WASP Attack on Python — Polymorphic Malware Shipping WASP Stealer; Infecting Hundreds Of Victims


### TL;DR


Research analysis of [pywale](https://pypi.org/project/pywale/) package linked with a malicious activity (WASP group). The WASP ground approach to impersonate well known package [requests](https://github.com/psf/requests/stargazers) from python aka StarJacking technique. A suspicious file [models.py](http://models.py/)which contained base64 encoded stage1 payload that fetches stage2 payload which is highly obfuscated and performs malicious actions.


Supply chain security in the open source ecosystem has become a large point of focus for the broader open source community — including the many companies and governments that rely on open source software.


As an industry and community, bad actors take over user accounts, corrupt popular open source dependencies, and take advantage of vulnerabilities in some of the biggest open source projects.


It’s no secret that a lot of our modern digital infrastructure runs on open source. The success of open source software (OSS), in part, comes down to the speed at which it’s developed by a global community of developers. But this speed can come at a cost if developers inherit the vulnerabilities in their supply chain.


Observations:


The package is performing starjacking. Its impersonating the famous requests library. The package is pointing to the famous python library i.e., requests to look legitimate.


[https://github.com/psf/requests/stargazers](https://github.com/psf/requests/stargazers)


[https://requests.readthedocs.io/en/latest/](https://requests.readthedocs.io/en/latest/)


Analysis brief:


The package is mentioning a list of requirements that could be downloaded from ‘[https://github.com/psf/requests’](https://github.com/psf/requests%E2%80%99) source.


Supply chain security in the open source ecosystem has become a large point of focus for the broader open source community — including the many companies and governments that rely on open source software.


As an industry and community, bad actors take over user accounts, corrupt popular open source dependencies, and take advantage of vulnerabilities in some of the biggest open source projects.


It’s no secret that a lot of our modern digital infrastructure runs on open source. The success of open source software (OSS), in part, comes down to the speed at which it’s developed by a global community of developers. But this speed can come at a cost if developers inherit the vulnerabilities in their supply chain.


Observations:


The package is performing starjacking. Its impersonating the famous requests library. The package is pointing to the famous python library i.e., requests to look legitimate.


[https://github.com/psf/requests/stargazers](https://github.com/psf/requests/stargazers)


[https://requests.readthedocs.io/en/latest/](https://requests.readthedocs.io/en/latest/)


## Get Dhanesh Dodia - HeyDanny’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Analysis:


The package is mentioning a list of requirements that could be downloaded from ‘[https://github.com/psf/requests’](https://github.com/psf/requests%E2%80%99) source.

*Exhibit 1.1*


While going through the code it can be observed a suspicious file ‘[models.py](http://models.py)’ has a base64 encoded code string found at line number 8, the same can be in referred in exhibit 1.2.

*Exhibit 1.2*


After decoding the encoded code, we observe that the code is fetching some payload from [http://51.103.210.236/inject/8HA7LjxopFuz52AI](http://51.103.210.236/inject/8HA7LjxopFuz52AI)

*Exhibit 1.3*


After looking for IP reputation it was noted that none of them reported it malicious. The same can be noted in Exhibit 1.4 and 1.5.

*Exhibit 1.4Exhibit 1.5*


After navigating on the IP below message was observed.

*Exhibit 1.6*


Going ahead with the base64 decoded code, we further navigated to the mentioned URL from where the payload which is fetched. It appears obfuscated code has been hosted.

*Exhibit 1.7*


Beautifying the python code. It looks like further HEX obfuscation is used in multiple parts of payload. To conclude what exactly the code is trying to do we are required to decode the HEX encoded code.

*Exhibit 1.8*


At this point we were able to notice a test.js file was created and the same was executed but note sure what exactly its trying to do.


Later it was noted that the package was associated with threat actors ‘WASP’ aka WASP Stealer disclosed by [Checkmarkx](https://checkmarx.com/supply-chain-security/)& Checkpoint research team. Shout-out to [Checkmarx](https://checkmarx.com/supply-chain-security/\)for starting such a great area to research. Do check out the blog published by Checkmarx security research team [WASP Attack on Python — Polymorphic Malware Shipping WASP Stealer; Infecting Hundreds Of Victims](https://medium.com/checkmarx-security/wasp-attack-on-python-polymorphic-malware-shipping-wasp-stealer-infecting-hundreds-of-victims-10e92439d192)


Another researcher have also shared a similar analysis of the same, do watch this [YouTube](https://www.youtube.com/watch?v=cW2PHJOuplI&t=121s)video.

---

*Originally published on [Medium](https://infosecwriteups.com/supply-chain-attacks-on-the-risk-open-source-security-ee7a8cf1ec58). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
