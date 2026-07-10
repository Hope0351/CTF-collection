# :arrows_counterclockwise: How to obfuscate URL/form data parameters to bypass WAF for SQL injections?

---

# How to obfuscate URL/form data parameters to bypass WAF for SQL injections?

*Disclaimer: This information is meant for learning purposes only. We strongly discourage any illegal activities, including unauthorized hacking. We do not endorse or take responsibility for unethical practices. Users should act responsibly and within the law. The content providers are not liable for any consequences resulting from unethical or illegal actions based on this information. Please adhere to ethical standards and legal regulations.*

## Get Trikto’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*Credits: Thanks to kharaone and anshifmonz_ for pointing this out to me.*

## Context

So I was working on the [Glacier CTF 2023](https://play.glacierctf.com) [“Peak” web challenge](https://peak.web.glacierctf.com/) and tried to attempt SQL injections on the register and login page.

But from the challenge description I assumed that they are implying the presence of a WAF here.

>

Beware the silent guards that stand sentinel along the treacherous path, obstructing your ascent.

*login*

*register*

Since there’s a WAF here, I tried to obfuscate the form data parameters sent through the request body.

## Obfuscating the parameters

Send your request to Burp Repeater

Highlight the code you wish to encode and right click it

>

Convert selection -> URL -> URL-encode all characters

Now your message is obfuscated!

But still you have another method left. You can use this [online tool](https://onlinetexttools.com/url-encode-text) too (make sure to check the “Escape All Text Characters” checkbox)

For more information about obfuscation checkout the [Portswigger lab](https://portswigger.net/web-security/essential-skills/obfuscating-attacks-using-encodings).

---
