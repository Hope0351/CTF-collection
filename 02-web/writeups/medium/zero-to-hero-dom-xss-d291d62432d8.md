# :globe_with_meridians: Zero To Hero Dom Xss D291D62432D8

---

This is the first blog of my series “Zero to Hero”. I am a beginner bug bounty hunter and have reported many bugs to different organizations. I have a lot of things to share with the infosec community, and hence I thought while I keep hunting I would share my learning through this series of blogs. While writing, I will be focusing more on real-world hunting techniques that I encounter while hunting.

### What is XSS and DOM XSS?

Cross-site scripting or XSS, allows an attacker to compromise the interactions between the victim and the vulnerable server, allowing him to inject malicious executable javascript code, targeting the victim directly. By performing this attack, a malicious actor steals the cookies of the victim and can perform actions on the victim’s behalf.

In DOM XSS, the vulnerable website takes unsafe data (javascript code) from an attacker-controlled source and then passes it to a javascript sink which executes the code, resulting in an XSS attack.

### Types of DOM XSS

Just like the old school XSS, DOM-based XSS is also of two types, depending upon how the vulnerable server responds to the malicious request,

- If the server, reflects the malicious string in the immediate response to an HTTP request and passes it to a sink, it results in Reflected DOM XSS.

- If the server, stores the malicious string and reflects it into a later HTTP response further passing into a sink, it results in Stored DOM XSS.

Both types of DOM XSS are equally dangerous and must be addressed immediately.

### Source? Sink? What the …?DOM: The Document Object Model or DOM is a programming interface for web documents which represents the document as nodes and objects so that programming languages can interact with it and modify the content of the web page according to the code. In the case of javascript as well, it manipulates the nodes and objects of the DOM. If manipulated in an unsafe way, it can result in XSS.

Source: The javascript property which accepts user data in an unsafe way is considered as the source. The most common example of a source is “location.search” which is used with almost every GET parameter.

Sink: The potential javascript function which can execute our script passed into a source is considered as the sink. For example, the eval() function.

Before we hunt in the wild, let us discuss the technique of finding and exploiting DoM XSS in some practice labs.

To solve the lab we have to call an alert() function. To exploit we just need two things,

A source where we enter our malicious javascript code and,

A sink that will execute our malicious js code. It is important to understand that without a sink a source is useless and vice versa.

Now, to find the source and sinks, the best and easiest way is to use the DOM invader. When you suspect that a parameter can be a source leading to a potential sink, just spray it with your canary and load it in the burp browser. Before that, make sure that you turn on the DOM invader extension.

Now, change the value of the parameter to your canary and load the URL.

From this, two things are pretty much clear,

- The parameter “search” is a potential source,

- It is passing the user-controlled data into eval() which is a potential sink.

Now to exploit it, we first have to locate the part of the javascript code where our malicious input is getting injected. You can either search every JS file in your browser’s debugger or Just perform a stack trace in the burp browser to know the exact location.

After locating, you can add a breakpoint by pressing “Ctrl + B” and by reloading you can check that the value is getting passed into our sink i.e. eval().

Now to craft our payload, just follow the basics of XSS exploitation. For example, I will now inject blackburn” to find out that “ is getting escaped by the use of a backslash \.

To solve this, we will also add a backslash before our quotation mark since the backslash is not escaped.

Now the complete exploit will be,

>

search=blackburn\”-alert(1)} //

An arithmetic operator (-) is used to separate the expressions before the alert() is called. And then JSON format is completed by adding a } and // are used to comment out the rest of the code.

To solve the lab we have to call an alert() function. Again, To exploit we just need two things i.e. Source and a potential sink. From the name of the lab, we know that this is going to be a case of stored XSS, So we will only be testing our canary on the parameters storing our data for later responses (comments, username, etc).

## Get Prameya Singh Soni’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

There is functionality to leave comments on any post on the web page. Let’s spray all of those parameters with our canary in DOM invader.

From this, we can confirm that the Name and website fields are working as a potential source and element.innerHTML is our sink. But the escapeHTML will cause an issue. Let’s test our primary payload for XSS,

So, the escapeHTML escaped only the first occurrence of <> tags. It is easy to bypass this and we can craft our final payload as

>

<><img src=1 onerror=alert(1)>

## Real World Exploitation

Now as our basics are clear, Let’s discuss how to hunt this in the wild. For real-world testing, I will be taking my institute’s domain as the target.

People often use automated tools to hunt for XSS, which I do not prefer. But if anyone is interested, they can use my script [Saturn](https://github.com/blackburn27/Saturn) to automate XSS, SQLI, and LFI.

### Step-1: Collecting URLs

For Collecting URLs, we can use tools like [waybackurls](https://github.com/tomnomnom/waybackurls) and [gau](https://github.com/lc/gau). I prefer using waybackurls, and also [uro](https://github.com/s0md3v/uro) to remove all the duplicate URLs. the syntax for the same is,

>

waybackurls rgipt.ac.in | uro | tee urls.txt

We got around 1861 unique (nearly) URLs. Waybackurls greps all URls which are cached on the open source, including cached URLs of sub-domains. So when going for a big target, this can be painful. So what I prefer is, first get all the subdomains using [amass](https://github.com/OWASP/Amass) and [subfinder](https://github.com/projectdiscovery/subfinder), and then while testing a single subdomain for bugs, use waybackurls for it individually. Learn how to setup amass by Hakluke

>

amass enum -d rgipt.ac.in -o subdomains.txt

subfinder -all -d rgipt.ac.in >> subdomains.txt

cat subdomains.txt| sort | uniq | tee subdomains.txt

cat subdomains.txt| httpx -status-code | tee subs_with_codes.txt

The final output will be something like this,

For a big domain, there will a lot of active sub-domains. We can go through all the interesting sub-domains one by one.

Step-2: Sorting URLs with parameters

After getting all the URLs, we will be using [Gxss](https://github.com/KathanP19/Gxss) to sort out reflecting parameters. SetThe value of the flag “-p” same as the canary in your DOM invader.

>

cat urls.txt| Gxss -p blackburn | tee mass_xss.txt

Sometimes, I also use web crawlers (like built-in crawler with sqlmap), paramspider, burp extension (param miner) etc to get more reflecting parameters.

Step-3: Using DOM invader to test for DOM XSS

We can now load these URLs in DOM invader to check for potential sources and sinks. This is a great way to find DOM vulnerabilities, DOM XSS in particular.

I am working on a new project on GitHub which will feature awesome bug bounty tips, tools, blogs etc from around the web. I will share the link soon on my [twitter](https://twitter.com/InfoSecBlack) and [LinkedIn](https://www.linkedin.com/in/prameya-singh-soni-9a38ba1b8/) handle.

Thank you for reading my blog 😀.

Stay tuned for more upcoming security stuff.

References:

---
