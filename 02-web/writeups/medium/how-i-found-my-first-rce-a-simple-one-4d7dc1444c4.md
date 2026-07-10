# :globe_with_meridians: How I found my first RCE? A simple one…

---

# How I found my first RCE? A simple one…

Hello Everyone,

My name is [Praveen Mali](https://www.linkedin.com/in/praveen-mali/) (PMMALI) and I am a Cyber Security Analyst.

As a cybersecurity enthusiast, I’ve always been fascinated by the concept of vulnerability hunting — the process of actively searching for vulnerabilities in systems and software in order to improve their security.

So I was performing VAPT on a client assignment for my company and I found an easy RCE, that I want to share with all of you.

## Get Praveen Mali (PMMALI)’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I was testing a web application that was an ERP and Assets Management System for ship companies. There was a form for updating company information, and a file upload feature was available for uploading a logo.

The file upload feature trigger me to upload a shell, but it is only allowing JPG and PNG formats. So I downloaded a [web shell](https://github.com/flozz/p0wny-shell/blob/master/shell.php) from GitHub, saved it as .png and uploaded on the web application and while uploading I intercepted the request into the Burp Suite, where I changed the .png to .php.

And web shell was uploaded successfully, when I click on the link of logo, the php file got executed and I got the shell of the server.

And this is how I found I my first RCE. I hope you enjoyed this article and learn something. Although it is very simple RCE.

Thank you so much for reading 🙏

My LinkedIn ID: [https://www.linkedin.com/in/praveen-mali/](https://www.linkedin.com/in/praveen-mali/)

My Twitter ID: [https://twitter.com/pmmali_](https://twitter.com/pmmali_)

---
