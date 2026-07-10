# :sleuth_or_spy: Website Osint Fca43Dba2C0C

> **Original Source:** [Website Osint Fca43Dba2C0C](https://infosecwriteups.com/website-osint-fca43dba2c0c)
> **Platform:** infosecwriteups.com | **Category:** `OSINT`

---

## Taking Off The Training Wheels


### Challenge Description


>

Use the tools and techniques seen so far to gather information about heat[dot]net and answer the questions.


## Get Hacktivities’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in

### Challenge Questions & Answers


>

1. What is the second nameserver listed for the domain?


I started by using [lookup.icann.org](https://lookup.icann.org/lookup) to find WHOIS information for “*heat.net*”. I can see that the second nameserver is “*NS2.HEAT.NET*”.

*WHOIS Nameservers for “heat.net”.*

>

2. What IP address was the domain listed on as of December 2011?


Using [viewdns.info](https://viewdns.info/iphistory/?domain=heat.net) website and searching for the IP history of the domain, I can see that the IP address listed in December 2011 was “*72.52.192.240*”.


*IP address listed in December 2011.*

>

3. Based on domains that share the same IP, what kind of hosting service is the domain owner using?


Since there are other domains hosted on the same IP address, we can safely assume our target uses shared hosting.

>

4. On what date was the site first captured by the internet archive? (MM/DD/YY format)


Using [web.archive.org](https://web.archive.org/web/19970601000000*/heat.net), I can see that the site was first captured by the internet archive on 1st June 1997.


*Date the site was first captured by the internet archive.*

>

5. What is the first sentence of the first body paragraph from the final capture of 2001?


Looking at the final capture of the website in 2001 on June 28, I can see the first sentence of the first body paragraph.

*First sentence of the first body paragraph from the final capture of 2001.*

>

6. Using your search engine skills, what was the name of the company that was responsible for the original version of the site?


I can use Google dorks to find supplemental information Google may have on this page (useful for finding cached pages).


```
info:heat.net
```


Looking at the output from this search, I can see it returns the name of a PC game company called “*SegaSoft*”.

*Google Dork returns name of company.*


Further down in the search results, I can also see multiple articles confirming “*SegaSoft*” was the name of the company that was responsible for the original version of the site.


*Google Dork search results.*

>

7. What does the first header on the site on the last capture of 2010 say?


Using [web.archive.org](http://www.heat.net/), I can see that the last capture of the website in 2010 was on the 30th of December. Looking at the webpage, I can see the first header.


*First header on the site on the last capture of 2010.*

---

*Originally published on [Medium](https://infosecwriteups.com/website-osint-fca43dba2c0c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
