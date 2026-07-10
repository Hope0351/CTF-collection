# :globe_with_meridians: [Write-up] Stored XSS into Onclick Event with Angle Brackets and Double Quotes HTML-encoded and Single Quotes and Backlash Escaped | Bashoverflow

> **Original Source:** [[Write-up] Stored XSS into Onclick Event with Angle Brackets and Double Quotes HTML-encoded and Single Quotes and Backlash Escaped | Bashoverflow](https://infosecwriteups.com/stored-xss-into-onclick-event-bypassing-angle-brackets-double-quotes-and-escaped-characters-ee347b9e19d9)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## Steps to Reproduce & Proof of Concept (POC)


1. Open the XSS lab and select one of the example articles.


2. Fill out the comment section, including a payload in the input field.


3. Go back to Burp Suite’s HTTP History and examine the server’s response, which shows the sanitization applied to your payload.


4. Notice that the `onclick` event reflects the URL input from the comment section.


## Get Bash Overflow’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


5. Attempt to inject the second payload in the URL form:


`/?&apos;&quot;&gt;&lt;img src=x onerror=alert(1)&gt;//`


```
/?&apos;&quot;&gt;&lt;img src=x onerror=alert(1)&gt;//
```


6. Check the browser’s response using Developer Tools (press F12).


7. Observe that certain HTML characters `&apos;` is converted back to `‘`(single quote)


8. Inject the next payload:


```
/?&apos;-top[`alert`](1)-&apos;
```


9. Return to the comment section and click on the username.


10. The payload executes successfully, triggering a pop-up with `alert(1)`.


11. The lab is now solved


---

*Originally published on [Medium](https://infosecwriteups.com/stored-xss-into-onclick-event-bypassing-angle-brackets-double-quotes-and-escaped-characters-ee347b9e19d9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
