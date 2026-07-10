# :globe_with_meridians: Blue Team Bootcamp Series (P3): How to Detect Cross-Site Scripting (XSS) Attacks

---

# Blue Team Bootcamp Series (P3): How to Detect Cross-Site Scripting (XSS) Attacks

Hello Friend :)

In this part, we’re going to cover the common WEB Attack known as XSS (Cross-Site Scripting)

Prerequisite: Basic knowledge about How Attackers Exploit XSS vulnerability is preferred.

But first, let’s understand:

## What is an XSS vulnerability?

Cross-Site Scripting (XSS), is classified as an injection attack where malicious JavaScript gets injected into a web application to be executed by other users.

## Get Ali AK’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

If you can get JavaScript to run on a victim’s computer, there are numerous things you can achieve. This can range from stealing the victim’s cookies to take over their session, running a keylogger that will log every key the user presses on their keyboard while visiting the website, redirecting the user to a different website altogether, or performing some kind of action on the website such as placing an order or resetting their password, etc.

## Types of XSS

- DOM
DOM (Document Object Model) is a programming interface for HTML and XML documents. It represents the page so that programs can change the document structure, style, and content. A web page is a document, and this document can be either displayed in the browser window or as the HTML source.

- Reflected (Non-Persistent)
Reflected XSS happens when user-supplied data in an HTTP request is included in the webpage source without any validation.
An example of this could be an error message which is in a query string of a URL that is reflected on the webpage. The URL could look something like the following:
[https://website.xyz/login?error=Username%20Is%20Incorrect](https://website.xyz/login?error=Username+Is+Incorrect)
The error message could be replaced with JavaScript code which gets executed when a user visits the page.

- Stored (Persistent)
XSS payload is stored on the web application (in a database, for example) and then gets run when other users visit the site or web page. This type of XSS can be particularly damaging due to the number of victims that may be affected.
An example of this could be a blog that allows visitors to leave comments. If a visitor’s message is not properly validated and checked for XSS payloads, then every subsequent visit to the blog page would run the malicious JavaScript code.

- Blind
Blind XSS is similar to a stored XSS in that your payload gets stored on the website for another user to view, but in this instance, you can’t see the payload working or be able to test it against yourself first.
An example of this could be a contact form. In the contact form, your message could contain an XSS payload, which when a member of staff views the message gets executed.

## Detecting XSS Attacks

- Look for keywords: The easiest way to catch XSS attacks is to look for keywords such as “alert” and “script” which are commonly used in XSS payloads.

- Familiarize yourself with frequently used XSS payloads: Attackers primarily use the same payloads to look for vulnerabilities before they exploit an XSS vulnerability. This is why familiarizing yourself with frequently used XSS payloads would make it easier for you to detect XSS vulnerabilities.

- Check if any special characters have been used: Check data coming from a user to see if any special characters that are frequently used in XSS payloads like greater than (>) or lesser than (<) are present.

## XSS Detection (Reflected) Example

- We can see on 1 March at 8:53:20 that the attacker with IP (192.168.31.183) first sends an XSS payload to test if XSS vulnerability exists before that normal/expected input is given such as john etc.

2. The attacker found out that it’s vulnerable (the “name” parameter is passing without any sanitization).
we can confirm this by looking at the request XSS payload send-in parameter & also response size returned from the server is large (4266–4298) means the attacker successfully executed the XSS payloads.

>

*Note: if a response is returned with a smaller size that means the server returned an error message so the XSS payload isn’t executing in that case*

## Investigation Report

- What date did the exploitation phase of the XSS Attack start?
01/Mar/2022 8:53:20

- What is the IP address of the attacker who performed the SQL Injection attack?
192.168.31.183

- What method does the attacker use is it automated (tool) or manual?
Manual because the request rate difference between each payload is 1 to 2.5 minutes & also user-agent is legit,

- What was the parameter vulnerable to XSS Attack?
name

- Was the XSS attack successful?
Yes, the attacker can execute or inject any malicious javascript code in a website here he injects JS code that redirects the other user to his malicious website.

- What is the type of XSS attack?
Reflected

## How to Prevent XSS

- Sanitize data coming from a user: Never trust data coming from a user. If user data needs to be processed and saved it should be encoded with html encoding using special characters and only then should it be saved.

- Use a framework: Most frameworks come with preventive measures against XSS attacks.

- Use the framework correctly: Almost all frameworks used to develop web applications come with a sanitation feature but if this is not used properly there still is a chance for XSS vulnerabilities to occur.

- Keep your framework up to date: Frameworks are developed by humans so they too may contain XSS vulnerabilities. However, these kinds of vulnerabilities are usually patched by security updates. So you should make sure that you have completed your framework’s security updates.

---
