# :globe_with_meridians: Apple Bug bounty writeups XSS(2021)

---

# Apple Bug bounty writeups XSS(2021)

## About me:

[https://hackerone.com/kamikaze?type=user](https://hackerone.com/kamikaze?type=user)

## Enumeration:

Get apple’s reachable host from censys.io

Search query: 17.0.0.0/8 AND 443.https.get.status_code: 200

## Screenshot:

Censys-CLI & Aquatone

Tool for scrape ip: [https://github.com/censys/censys-python](https://github.com/censys/censys-python)

Tool for screenshot: [https://github.com/michenriksen/aquatone](https://github.com/michenriksen/aquatone)

## Terminal command:

- Scrape reachable host from censys CLI

censys search -q “17.0.0.0/8 AND 443.https.get.status_code:\”200\”” -query_type ipv4 — fields ip protocols -max-pages 15 -f json -o apple

2. Grep ip address

grep -o ‘[0–9]\{1,3\}\.[0–9]\{1,3\}\.[0–9]\{1,3\}\.[0–9]\{1,3\}’ apple >> ip-apple

## Get Takashi Suzuki’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

3. Adds “https” for ip address in order to use for Aquatone

sed ‘s/^/https:\/\//’ ip-apple >> http-apple

4. Take screenshots

cat http-apple | ./aquatone -ports 443 -http-timeout 9000 -screenshot-timeout 90000 — out apple

I found a site which is vulnerable to XSS.

## Site:

https://apple.channel.support

## Step to reproduce:

1. Create a ticket

2. Upload SVG image with XSS payload in reply

3. When victim views attacker’s SVG image from mobile device, XSS triggers

## POC

## Timeline:

Reported: 02/16/2021

Fixed & Asked to how to be credited in Hall of Fame page : 31/03/2021

---
