# :globe_with_meridians: Stored xss using PDF 👾 a bug?

> **Original Source:** [Stored xss using PDF 👾 a bug?](https://infosecwriteups.com/stored-xss-using-pdf-a-bug-0690125015bb)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Stored xss using PDF 👾 a bug?


Hello Hackers, Today in this writeup I am going to discuss a bug which is not that high level but sometimes this bug will give you HOF. It totally depends on the company to company. In my case I reported 2 bugs and got HOF for both of them. Let’s get started.


>

You can find the malicious pdf from this repo of coffinxp: [https://github.com/coffinxp/pdFExploits](https://github.com/coffinxp/pdFExploits)


In this bug, When you upload a malicious PDF which has a payload to triggered the xss. And when you click on that uploaded pdf it simply opens the pdf and our xss payload was executed successfully and boom we find stored xss 🥳. Is it really true? NO…!


Using this you cannot triaged *document.cookie, document.domain, windows.location*, etc.. commands. I am not sure why but I tried my best to understand this things but still I don’t know how this things works so I cannot say to you but you can do more research on this. Why pdf files was not executing js commands?


How I got 2 HOF?


- Whatfix HOF:


During testing all the functionality I find out a functionality of uploading a pdf files which was accessible to all the workspace members. Now I simply upload a malicious PDF file which has having a very simple payload alert(‘xss poc’).


After successfully uploading PDF, any member on the workspace can see, and download the malicious pdf!


Why I report?


- The company stores the pdf into their main domain. which looks like


```
https://whatfix.com/a/c/f/d/adsfjr2eawr32.pdf
```


2. After visiting this url the pop up triggers and it shows this:


So, Now we know that if the attacker some how upload the malicious files then the main website was affected so this was not the best practice. The company should use a sandbox domain to store and interact with the pdf thus this will not directly affect the main website.


## Get cryptoshant🇮🇳’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Sadly, the bug was already known to them but still they decide to give me HOF.


2. Lenovo HOF:


Sorry I can't exactly disclose everything as the bug was still in unresolved state but the process was same. But in this case the different scenerio.


Where I found?


I found the bug in contact us page and after submitting the query they assign the ticket and it was shown to us in our profile. Now when you visit that particular ticket and click on the malicious pdf it was executing perfectly. But when you give that url to someone else person then this wasn’t executing. Thus Is this self? Umm, yes but I show them impact in different way.


How I show Impact & got HOF?Bugcrowd team: This was self and this will not affect any user.


Me: But this will affect the employee of the company. The malicious pdf was accessible with employees & hacker. And the hacker will add the pdf exploits and try to hijack employees computers and thus this will affect your company.


After sending the above message, bugcrowd team create a blocker on the company and asked them to check on their side whether the pdf was executed on their side or not?


After couple of days, they confirmed that the pdf file was also executed on the company side and they marked my report as P3 severity as a Stored xss And awarded me HOF.


Why I report?


- This is also storing the pdf on their main site and it looks like this:


```
https://xyz.subdomain_from_in_scope.com/a/b/c/asfdfsa.pdf
```


2. It was same as above the company was not using any sandbox domain to store and interact with the pdf or any uploaded files. And they accept.


Still I don’t know what can I achieve using this bug 🤔. If you know you can tell me the other things the attacker can do. it would really helpful. But yes if you are beginner and wanted to get your first hof you can go with this bug the company will probably accepts this bug and awarded you your first HOF. I am not sure this will help you to get your first bounty or not.


That’s it for this writeup, I will see you in next amazing one. bye 👋

---

*Originally published on [Medium](https://infosecwriteups.com/stored-xss-using-pdf-a-bug-0690125015bb). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
