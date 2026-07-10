# :globe_with_meridians: Blind XXE with OOB Interaction via XML Parameter Entities

> **Original Source:** [Blind XXE with OOB Interaction via XML Parameter Entities](https://infosecwriteups.com/blind-xxe-with-oob-interaction-via-xml-parameter-entities-97244bf2b85e)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## Methodology


Want to give the lab a try yourself and follow along? You can check it out on PortSwigger’s website [here](https://portswigger.net/web-security/xxe/blind/lab-xxe-with-out-of-band-interaction-using-parameter-entities) for free.

## The Recon


Upon opening the application, we’re met with a shop pae that has no ability to login:


We’ll be looking for functionality in the app that will be unauthenticated — something to make note of.


Based on the lab, we’ll be searching for something specifically to do with XML.


Let’s click on a product page. We’re met with two apparent actions:


- Stock Check

- Return to List


It’s likely that Return to List won’t yield anything, so let’s hit the stock check feature to capture the request.


Now, navigate over to the SiteMap in Burp, which we can see already lighting up like a Christmas Tree:


In order to cover all of our basis, kick off an active scan on the root request. This will pick up anything we may have missed.


But, we can already see that Burp is picking up something on the Stock Check, and we can see from a glance there is XML in the request.


## Get Ryan G. Cox’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Let’s go ahead and right click on the request and send it over to the Repeater for some manual testing.

## Testing


Once we get the Request to the Repeater, send a request without changing anything so we can see how the base request functions:


Let’s probe for anything that happens differently with a test payload:


`<!DOCTYPE foo [ <!ENTITY myentity "value" > ]>`


After placing the payload in the *productId* and *storeId*, we can see that both trigger an XML parsing error.


If we take a step back and think about it, we can actually realize this is expected since the lab indicates that we’ll need to trigger an OOB (Out-of-Band) interaction.


So, the lab should not be giving any indication of this being accepted.

## Exploitation


Keeping that OOB interaction in mind, let’s head to Collaborator on our Burp instance and spin it up:


Now, let’s take the following payload, which is designed to trigger an OOB communication to our collaborator link that will be kicked off by the stockCheck DOCTYPE in the XML.


Replace BURP-COLLABORATOR-SUBDOMAIN with the one in your instance by clicking Copy to Clipboard.


Paste the XML payload in place for both the *storeId *and *productId* and see we still get the XML parsing error, but no interaction with our client after clicking Poll Now.


Let’s think about this for a second…


What if we place our payload outsid ethe stockCheck so that our ENTITY can be referenced outside the function?


Still an XML parsing error… but let’s check Collaborator:


We can see we have some interactions with our Collaborator! Lab solved!

## What We’ve Learned


We can see that when testing, we can’t always rely on what we see in the app. In many of these labs, we see direct confirmation in the application to verify to us that a vulnerability is present. However, when searching in the real world, this is most likely not going to happen. Vulnerabilities where there is some form of reflection in the app is going to be considered “low-hanging fruit” and will generally either be found before you can, or be picked up by automated testing. It’s important to understand different techniques to trigger out of band interactions to confirm whether the UI is telling you the truth or not.


—


Remember: The Cybersec Café gets articles first. Subscribe for free [here](https://www.cyberseccafe.com/).


Interested in getting into Cybersecurity? I have a course called the [Security Sip](https://securitysip.cyberseccafe.com/). The curriculum is designed to help you build skills progressively over 12 sections, 85 modules, and 155 exercises. With rapidly evolving threats and technologies widening the skill gap, it’s time to secure your future in cybersecurity. [Available Now](https://securitysip.cyberseccafe.com/#pricing)!


Oh, and if you want even more content and updates, hop over to Ryan G. Cox on [Twitter/X](https://twitter.com/ryangcox_). Can’t wait to keep sharing and learning together!

---

*Originally published on [Medium](https://infosecwriteups.com/blind-xxe-with-oob-interaction-via-xml-parameter-entities-97244bf2b85e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
