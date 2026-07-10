# :globe_with_meridians: Blind SSRF in Skype (Microsoft)

> **Original Source:** [Blind SSRF in Skype (Microsoft)](https://infosecwriteups.com/blind-ssrf-in-skype-microsoft-6639f4961052)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Blind SSRF in Skype (Microsoft)


Server Side Request Forgery is a vulnerability that allows attacker to make server request to attacker controlled network location/path.


While analyzing requests in Burp for Skype for Web, found a endpoint at *.*.skype.com/path?url=https://example.com , As the url param appeared interesting tried to change the url with my ngrok instance & got a hit !


Confirmed that it’s Skype which hit the url by looking at the ngrok inspect web console by verifying received User-Agent header(Skype)and IP address in who.is.


Although I was able to make the server hit arbitrary webpage, I couldn’t get full response. I could only get status code, content-type, content-length(size) of response and text content from few selected HTML tags. That’s, it’s not full SSRF as expected, but is a blind/partial SSRF.


Tried to access below paths —


- localhost/internal ip address -> Failed

- Tried to bypass localhost/internal ip address using url redirect/url shortner methods -> Failed

- External ip address/webpage -> Success

- Common Azure/AWS/DigitalOcean Meta data IP addresses -> Failed

- Not so commonly used, Azure related IP address (168.63.129.16) -> Success -> This IP can be used to determine VM’s health by using [http://168.63.129.16/metadata/v1/maintenance](http://168.63.129.16/metadata/v1/maintenance) endpoint, which should return OK (200 Status Code) if VM is functioning. (Refer [this](https://learn.microsoft.com/en-us/azure/virtual-network/what-is-ip-address-168-63-129-16?WT.mc_id=docs-azuredevtips-azureappsdev) for more information)


Tried changing url param value to [http://168.63.129.16/metadata/v1/maintenance](http://168.63.129.16/metadata/v1/maintenance) , got 200 Ok response, with size of response as 2 bytes which confirms that response text probably contains OK in response.


## Get Jayateertha Guruprasad’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Made a nice report mentioning all the details and sat back waiting for Microsoft to reproduce and fix the report.


Fortunately this was in scope for bounty under the M365 Bounty Program and got a nice $$$$ bounty !


*Party Hard!*


Report Timeline:


- Reported — Sep 23, 2022

- Additional Details Updated — Oct 3, 2022

- Bounty Rewarded — Oct 8, 2022

- Fixed — Oct 12, 2022

## Liked my article ? Follow me on twitter ([@jayateerthaG](https://twitter.com/jayateerthaG)) and medium for more content about bugbounty, Infosec, cybersecurity and hacking.

---

*Originally published on [Medium](https://infosecwriteups.com/blind-ssrf-in-skype-microsoft-6639f4961052). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
