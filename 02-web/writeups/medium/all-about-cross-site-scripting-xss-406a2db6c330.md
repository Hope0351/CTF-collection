# :globe_with_meridians: All about cross-site scripting (XSS)

---

# All about cross-site scripting (XSS)

Hello Amazing Hackers,

Hope you guys Doing well and hunting lots of bugs and Dollars !

Well, let’s start and learn about cross-site scripting attacks and methodologies to find them.

>

What is cross-site scripting (XSS)

Cross-site scripting (XSS) is one of the most popular vulnerabilities in today’s web applications. This vulnerability can be used to execute malicious JavaScript in a user’s web browser. This could then be used to steal users’ tokens, cookies, and some other sensitive information. It happens due to improper sanitization in input fields present on the web applications.

*This could generally be fixed with proper input validation on the client and server sides.*

>

Types of cross-site scripting:-

- Reflected XSS

- Stored XSS

- DOM-based XSS

>

Reflected XSS

Reflected XSS is also popular as non-persistent XSS, which arises when user input is instantly returned by a web application in an error message/search result or the input provided by the user as part of the request and without permanently storing the user-provided data.

*This is the least impactful category of XSS because exploiting the vulnerability involves crafting a request containing embedded JavaScript that is reflected by any user who makes the request.*

>

Stored XSS

stored XSS is also known as persistence XSS, which arise when an application takes user input and stores the input in the back-end database, and then displayed it to other user without proper filtration and sanitization.

## Get Xcheater’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*This is more impactful than reflected XSS because exploiting the vulnerability involves crafting a request containing embedded JavaScript that is reflected to all the user who is visiting the vulnerable web application.*

>

DOM-based XSS

DOM-based XSS (also known as [DOM XSS](https://portswigger.net/web-security/cross-site-scripting/dom-based)) arises when an application contains some client-side JavaScript that processes data from an untrusted source in an unsafe way, usually by writing the data back to the DOM.

>

How to find XSS :-

- To find xss you have to look at each and every client-side input i.e request headers, cookies, forms inputs, POST parameters, GET parameters.

- Give any Input there , if your input reflect back to you.

- Then try to inject any valid payload, By looking response at the HTML sources of the page which will help you to understand how to build an xss payload

well that’s the methodology for finding XSS vulnerabilities but let me introduce you to another type of XSS :-

>

Blind XSS

As the name of the attack suggests, it is when an execution of a stored XSS payload is not visible to the attacker/user, but only visible to an administrator or back-end employee. Although this attack could be very detrimental due to its ability to attack back-end users, it is often missed.

>

How to find Blind Xss :-

This is also similar to reflected xss or stored xss But you Don’t get any reflection, but you get a response on your server.

- Similar methods As given above except try putting payload which can give a callback on your server when executed.

- You can Use [https://xsshunter.com/](https://xsshunter.com/) or Use burp collaborator or ngrok.

- Try it on contact forms or similar functionality.

>

How to prevent XSS attacks :-

- Validate input.

- Validate output.

- Eliminate dangerous insertion points.

References:-

Hope this is useful for you guys

Happy Hacking !

Twitter handle :- [https://twitter.com/Xch_eater](https://twitter.com/Xch_eater)

---
