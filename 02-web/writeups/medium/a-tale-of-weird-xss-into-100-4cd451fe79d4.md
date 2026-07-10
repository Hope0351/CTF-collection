# :globe_with_meridians: A Tale of Weird XSS into $100

---

# A Tale of Weird XSS into $100

Hey Guys , How are you all ? . I hope so your doing good and healthy . So, Lets get started . So , I started searching for bugbounty programme through Google dorking process . I found a program with small scope with app.reducted.com and api.reducted.com . So , I started doing some google dorking as manually as well as in a automated way using a tool called pagodo and using pentest-tools

Above tools are some awesome tools . It gave me some awesome results in my recon process . So , I started playing with login functionality testing that includes I created two accounts and tried session hijacking , Password reset poisoning and similiar to that did every possible ones But unfortunately , Nothing works

I’m so confused , What to do ? . I looked into other functionality that the target has . So , When I looked into settings . We can edit the following such as Bios ,Instagram Handle , Twitter Handle and We can also set the linkedin account . But there is a twist out there we don’t have import the link . we can only import the name of the account only . I can idea of XSS here . But I tried the XSS by simply injecting payloads into Instagram page name field . But Unfortunately It doesn’t works . So , You can ask why can’t we try payloads into fields . But nothing works .

So , I just took break for few hours and I again started working on the target . But this time , I had the idea of why I can’t change by Instagram name to the basic xss payload and Input the payload into the Instagram field ( “><script>alert(document.domain)</script> ) . So , What ? After I entered , The XSS Payload got Triggered

So , I always suggest you to look for the vulnerabilities in every possible way . Hope so , this report looks informative in a way

## Get Nithissh’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Reported On → 14/09/2021

Triaged on → 16/09/2021

Got rewarded $100 → 20/09/2021

---
