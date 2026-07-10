# :globe_with_meridians: Akamai Bypass! Advanced XSS.. In the name of God

> **Original Source:** [Akamai Bypass! Advanced XSS.. In the name of God](https://infosecwriteups.com/akamai-bypass-advanced-xss-68634f082859)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Akamai Bypass! Advanced XSS.


In the name of God


In this write-up, we will embark on a journey to explore the intricate art of bypassing security measures by WAF in this case we will fight against Akamai. By the end of this tutorial, you will not only gain a profound understanding of the security mechanisms in place but also acquire the knowledge and skills necessary to craft your own custom payloads. As we delve into the realm of security and vulnerabilities, we will unravel the layers of protection that safeguard web applications, enabling you to grasp the underlying logic and master the techniques required to navigate this fascinating domain. Prepare to embark on a learning adventure that will empower you to think like a security professional and strengthen your bypassing skills.

## Story


Every WAF (Web Application Firewall) bypassing adventure begins with the quest to find the elusive injection point — the proverbial crack in the fortress’s armor. And so, my journey began when I stumbled upon an endpoint where the presence of the infamous parameter “returnUrl” was unmistakably shining like a beacon in the night.


Try again button is where our payload is injected


As a pentester whenever we approach this situation automatically we insert our *javascript:alert(1)* payload but what I got in response was


Now onto the analysis phase — I removed everything after “javascript:” to check if I had access to the JavaScript protocol, and fortunately, I did:


With the discovery that “alert” after “javascript:” was blocked, my investigation proceeded to assess the blocking of other common JavaScript functions. I tested “javascript:prompt(),” “javascript:console.log(),” and “javascript:eval(),” but all attempts ended in failure. It became evident that the web application’s security measures were thorough and effectively thwarted my initial attempts.


Undeterred, I decided to explore more advanced JavaScript functions to determine if any could bypass the security defenses. I tested “javascript:atob()” and “String.fromCharCode(),” among others, but each endeavor met the same outcome — failure


After exhaustive testing, I found that `decodeURI()` remained unblocked, providing a potential path to exploit the vulnerability.


According to [Mozilla](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/decodeURI):

>

*The *`*decodeURI()*`* function decodes a Uniform Resource Identifier (URI) previously created by *`[encodeURI()](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/encodeURI)`* or a similar routine.*


The way it works is as follows: Essentially, when we use a function such as `javascript:decodeURI("<h1>vita</h1>")`, and then click on the "Try Again" button, we can see the result of the decoded URI, which will be displayed as shown below:


Result after clicking on Try again button


## Get hosein vita’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Now it was time to dig deeper and insert a payload like `<img src=x onerror=alert(1)>` inside the `decodeURI` function to achieve XSS, but what I got was:


Even without `onerror=alert(1)`, I was still encountering the same error, indicating that the WAF was effectively filtering out malicious tags.


I went through all the tags all of them were blocked except one tag `<button>` is working!


So I gave my first try there <*button autofocus onfocus=alert(1)>test</button> *and yes! I was blocked again:


The WAF continued to inspect the event handlers, but I didn’t waste any time. I swiftly initiated a brute force attempt on all of the event handlers to identify which one triggered a response:


Within the array of event handlers, only “*onbeforetoggle” *managed to evade the blocking mechanism.


Afterward, I visited PortSwigger and compiled a list of payloads involving the `<button>` tag and the 'onbeforetoggle' event handler, discovering that these were the only two available options:


I attempted both options, but neither of them proved successful, primarily because the WAF was effectively blocking the `alert(1)`.


But how did I manage to overcome this issue? Essentially, after ‘javascript:’, you have the ability to declare variables. So, I employed a bit of creativity and divided the `alert()` function into three separate variables, something like this: `javascript: var a = 'ale'; var b = 'rt'; var c = '()'`. Then, I concatenated these variables within the string inside the `decodeURI` function, resulting in my final payload, which looked like:


```
javascript:var a="ale";var b="rt";var c="()";decodeURI("<button popovertarget=x>Click me</button><hvita onbeforetoggle="+a+b+c+" popover id=x>Hvita</hvita>")
```


And the result:


I hope you enjoyed reading this write up:)

## Conclusion


In conclusion, I’d like to highlight that as a result of my communication with Akamai, it has been clarified that this issue has been promptly addressed and fixed. Consequently, the payload is no longer exploitable, underscoring the importance of responsible disclosure and timely resolution in ensuring the security of web applications.

## Contact me


[Tiwtter](https://twitter.com/hoseinvita)

---

*Originally published on [Medium](https://infosecwriteups.com/akamai-bypass-advanced-xss-68634f082859). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
