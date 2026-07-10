# :globe_with_meridians: $500 Bounty: DOM-Based XSS in Gatecoin’s Charting Library

---

## Vulnerable Code

Inside the `library.js` file of the charting tool:

```
$.getScript(urlParams.indicatorsFile)
```

No validation or sanitization was performed on the `indicatorsFile` parameter. This is a textbook example of insecure dynamic script injection.

## Impact

This DOM-based XSS vulnerability had the potential to:

- Steal user sessions or API tokens.

- Hijack browser functionality and perform actions on behalf of users.

- Inject fake content or redirect users to phishing pages.

In the context of Gatecoin — a cryptocurrency exchange — such a vulnerability could have devastating financial consequences.

## Get Monika sharma’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Credit: [bobrov](https://hackerone.com/bobrov)

Report ID: [351275](https://hackerone.com/reports/351275)

>

How You Can Find Similar Bugs

Here’s a step-by-step approach to discover DOM XSS vulnerabilities like this:

- Look for Dynamic JavaScript Loading

- Search for usage of `eval()`, `innerHTML`, `document.write()`, `setTimeout()`, `setInterval()`, or jQuery methods like `$.getScript()` in JS files.

2. Check for URL Fragment Parsing

- If the site uses values from `window.location.hash`, `window.location.search`, or `URLSearchParams`, see how they're handled.

3. Use DOM XSS Scanners

- Tools like DOM Invader (Burp Suite) or XSStrike can help detect unsafe sinks and sources.

4. Host Your Own Payload

- If the target loads external scripts, host your payload (e.g., alert + cookie exfiltration) on a server you control and test if it gets executed.

5. Don’t Ignore Widgets or Embeds

- Often, third-party charting libraries, widgets, or embedded tools are less scrutinized — making them a perfect attack surface.

## Conclusion

This $500 DOM XSS vulnerability in Gatecoin’s charting library is a clear reminder of how dangerous dynamic script loading can be when not properly validated. Simple mistakes like blindly trusting URL parameters can expose an entire application to critical attacks.

If you’re into bug hunting, never ignore JavaScript-heavy endpoints, iframe widgets, or anything that uses user-controlled parameters to build DOM elements or load scripts. These can be goldmines for DOM-based attacks that many scanners miss.

>

Found this case study useful? Buy me a coffee ☕[https://buymeacoffee.com/monikaak47](https://buymeacoffee.com/monikaak47)

Happy Hunting.

---
