# :globe_with_meridians: Salesforce bug hunting to Critical bug

---

# Salesforce bug hunting to Critical bug

## Or how I learned that some bugs are truly rare

Ah, yes, third party is 9 out of 10 times out of scope. But sometimes it's not. Sometimes it's very much in scope. Unlike Zendesk , Salesforce can be misconfigured by its clients or left in a default state which allows for access to interesting/not-meant-to-be-publicly-accessible data.

The Bug

It's really simple (for more complicated and indepth analysis check this article.

*Low vs Critical*

First you have to find a subdomain that is on Salesforce/aura, which is usually help.target.com, support.target.com or community.target.com, but it can also be some random thing like state.target.com etc. In case of widescope program it's best to use nuclei with Salesforce aura module to automate the process, but sometimes manual approach may be necessary.

Second, after finding Salesforce/aura site, using burp or even Firefox/chrome network inspector find any POST request to aura endpoint. You'll know what you're looking for when there's message parameter in the body:

Final step, this is where you learn if the target is vulnerable or not, edit the message parameter by replacing the value with this (you don't even have to encode it):

---
