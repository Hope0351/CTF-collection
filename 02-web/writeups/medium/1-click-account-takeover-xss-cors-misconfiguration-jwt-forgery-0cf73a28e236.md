# :globe_with_meridians: 1 Click Account Takeover | XSS | CORS Misconfiguration | JWT Forgery

---

## Chaining Vulnerabilities

### Subdomain Takeover

First, I searched for subdomains with subfinder and made sure to include API keys in the config file to find more results.

```
subfinder -d redacted.com -all -recursive | anew subdomains.txt
```

The subdomains were then analyzed by dnsReaper for takeovers.

```
docker run -it — rm -v $(pwd):/etc/dnsreaper punksecurity/dnsreaper file — filename /etc/dnsreaper/subdomains.txt
```

After verifying the results manually, it was determined that none of the takeovers were valid. This is not surprising, as the subdomain takeover vulnerability class is heavily automated.

### Cross Site Scripting

I spent about 2 weeks hunting for XSS. Most of the subdomains were protected by a WAF and difficult to test, so I scanned them with httpx to find the ones that were unprotected.

```
httpx-pd -l subdomains.txt -td -sc -title -fr | grep -viE 'akamai|cloudflare'
```

Analyzing the source code from one of these subdomains led to an interesting discovery.

The url variable was defined but never used, probably because the developers forgot to remove it from a previous commit. This endpoint also failed to sanitize reflected user input from a query parameter, and was therefore vulnerable to XSS.

## Escalating Impact

### JWT Forgery

Most web APIs require inputting the current password to change it, but it is often possible to circumvent this check by editing the current email address, and then calling a reset password endpoint. Unfortunately, [redacted_auth.com/api/v1/profile](https://redacted_auth.com/api/v1/profile) did not allow email modification.

## Get Raymond Van Wart’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

After performing more recon, I found a different API at [redacted_widget.com](https://redacted_widget.com/). Changes made through this endpoint were synced with the main API, but required a UUID and JWT.

The required UUID was included in the JWT shown earlier from the XSS popup and uncrackable because it used version 4. [https://en.wikipedia.org/wiki/Universally_unique_identifier](https://en.wikipedia.org/wiki/Universally_unique_identifier)

The JWT cookie however, possessed a different structure from the one used on the main API.

To validate this token, the application compared its email with the one from the request. Unfortunately, attempting to register users with an existing email would return an error, so it did not seem possible to duplicate tokens.

After some thorough testing, I discovered a mass assignment vulnerability that made it possible to bypass duplicate user checks by setting the region to EU.

Notice, the generated token for the duplicate account does not include a region attribute, so it is identical to the victim’s JWT.

It would now be possible to complete the ATO using the following chain.

---
