# :globe_with_meridians: $2,500 Bounty: DOM-Based XSS via postMessage on Upserve’s Login Page

> **Original Source:** [$2,500 Bounty: DOM-Based XSS via postMessage on Upserve’s Login Page](https://infosecwriteups.com/2-500-bounty-dom-based-xss-via-postmessage-on-upserves-login-page-dc899778ed31)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# $2,500 Bounty: DOM-Based XSS via postMessage on Upserve’s Login Page


## How a Loose Origin Check Opened the Door to Credential Theft on a Production Login Page


### Overview


Security researcher gamer7112 uncovered a DOM-Based XSS vulnerability on Upserve’s login page ([https://inventory.upserve.com/login/](https://inventory.upserve.com/login/)) by exploiting a misconfigured postMessage handler. The bug originated from weak origin validation logic, leading to the execution of attacker controlled JavaScript via eval() — ultimately earning a $2,500 bounty.


This report highlights the importance of strict origin checks when using postMessage especially on pages handling sensitive operations like user authentication.

### Vulnerability Details


Vulnerable Endpoint:


```
https://inventory.upserve.com/login/
```


Vulnerable JavaScript Logic:


```
window.addEventListener("message", function(e) {
if (~e.origin.indexOf("https://hq.upserve.com")) {
if (e.data && typeof e.data == "object") {
try {
if (e.data["exec"]) {
eval(e.data["exec"]);
}
} catch (err) {
console.log(err);
}
} else {
console.log("Non-object passed");
}
} else {
console.log("Incorrect origin: " + e.origin.toString());
return;
}
});
```


The Issue:


The if (~e.origin.indexOf(“[https://hq.upserve.com](https://hq.upserve.com)")) condition is not strict. It will accept any domain that contains [https://hq.upserve.com](https://hq.upserve.com) — including attacker-controlled subdomains like:


```
https://hq.upserve.com.attacker.com
```


This allowed a malicious site to send a postMessage to the login page and trick it into executing arbitrary JavaScript using eval().

### Proof of Concept (PoC)


- The attacker hosts a malicious HTML file at:


```
https://hq.upserve.com.attacker.com/upserve_xss.html
```


2. The HTML file sends a crafted postMessage to the login page with malicious JavaScript in the exec field.


3. When a victim visits this page and clicks a link or performs an action, the payload is sent and the login page executes arbitrary JS using eval().


4. Result: alert(1) or credential stealing scripts can run on the login page.

### Impact


- Session hijacking or credential theft on a sensitive login endpoint.

- Account takeover potential if paired with social engineering.

- Exploitable in production with high trust from users.

>

How You Can Find Similar Vulnerabilities


- Search for postMessage Listeners


Use tools like grep, Burp Suite or DevTools to search JavaScript files for:


```
window.addEventListener("message", ...)
```


2. Check Origin Validation Logic


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Look for improper origin checks like:


- indexOf(…) >= 0

- includes(…)

- includes(…)

- Regex patterns not using ^ (start of string)


These can be bypassed with attacker-controlled subdomains:


```
https://trusted.com.evil.com
```


3. Inspect Message Handling


If the handler directly uses:


- eval()

- document.write()

- innerHTML

- location.href


Then test for injection possibilities.


4. Craft a Payload


From your malicious domain (or localhost) try:


```
window.frames[0].postMessage({
exec: 'alert("XSS")'
}, '*');
```


Adjust message structure to match what the handler expects.


5. Test on Sensitive Pages


Target login pages, dashboards and admin panels. XSS in these places has high impact and higher bounty potential.

### Bounty Info


- Hunter: gamer7112

- Bounty Awarded: $2,500

- Report ID: #603764

### Final Thoughts


This case is a textbook example of how a seemingly small oversight — a loose origin check — can lead to high-impact vulnerabilities on sensitive endpoints. Always validate the origin strictly using equality comparison (===) or trusted origin lists.


For bug hunters, this is a great reminder: don’t just look for broken CSP or reflected payloads — DOM-based vulnerabilities, especially via postMessage, are lurking behind the scenes and can be incredibly rewarding.

>

Thanks for reading!


Happy hunting and stay curious. 🤑✨

---

*Originally published on [Medium](https://infosecwriteups.com/2-500-bounty-dom-based-xss-via-postmessage-on-upserves-login-page-dc899778ed31). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
