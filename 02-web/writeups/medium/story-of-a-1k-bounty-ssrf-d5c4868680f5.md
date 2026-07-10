# :globe_with_meridians: Story of a $1k bounty — SSRF to leaking access token and other sensitive information

> **Original Source:** [Story of a $1k bounty — SSRF to leaking access token and other sensitive information](https://infosecwriteups.com/story-of-a-1k-bounty-ssrf-d5c4868680f5)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Story of a $1k bounty — SSRF to leaking access token and other sensitive information


Hello and welcome everyone to my story of how I got my first bounty on HackerOne by exploiting an SSRF that leaked Google cloud access token and other sensitive data, Before moving forward I would like to thank this sweet community that has helped me in my overall journey.


I chose the target from my HackerOne’s private invitation list, therefore I cannot the disclose the target and so I’ll call it redacted.com. I started with recon, I created an automation tool that do my recon process like gathering subdomains, getting live hosts, running nuclei , directory brute forcing, nmap and getting waybackurls etc. After my automation was done i analyzed all the data like waybackurls and others.


The waybackurls seemed interesting so I quickly used gf patterns to get all ssrf endpoints that could be vulnerable


```
cat waybackurl | gf ssrf
```


As the __host field fetches some kind of data from the github, I tried testing ssrf, So I quickly opened my Burpsuite and put the burp collaborator link in the __host field and send the request, I clicked on poll now button and yes I got an HTTP interaction and the burp collaborator response was reflected on the screen.


I tried XSS with it by firing up an Apache server and uploading alert JavaScript payload


But i stopped because XSS won’t be so impactful and started to look for ssrf, In the __host parameter I put 169.254.169.254 and in the url I added */latest/meta-data/iam/security-credentials/*


```
https://redacted.redacted.com/latest/meta-data/iam/security-credentials/?__host=169.254.169.254&__proto=https
```


and sent the request. But it returned 502 BAD Gateway I then changed __proto value to http but it didn’t either worked.


Then I though of why not try other endpoints like google, digital ocean one’s, I took a help of a pdf that has all ssrf endpoints that I will provide down and finally google cloud endpoint gave a response other than 502.


## Get Faique’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The response contained


```
Missing required header: Metadata-Flavour
```


So I quickly added this header and set the value of it to Google(took help from pdf) and send the request and *yesss!! it did work*


I then tried to get access token using


```
GET /computeMetadata/v1/instance/service-accounts/default/token?__host=169.254.169.254&__proto=http
```


I screamed woah!! I got it, SSRF achieved :)


I tried and got other details like scopes, emails, region and id etc.

### Reporting


I reported the vulnerability with all the Pocs and waited until next day, they responded & acknowledged it as a cool finding and rewarded me with $1000 bounty


>

PDF: [SSRF.pdf](https://github.com/faiqu3/ssrf/blob/main/SSRF.pdf)


Thank you for reading till here, I hope you guys learned something new from the write up. If you enjoyed make sure to give a clap and follow me on:

---

*Originally published on [Medium](https://infosecwriteups.com/story-of-a-1k-bounty-ssrf-d5c4868680f5). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
