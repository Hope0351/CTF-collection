# :globe_with_meridians: SQLi WAF Bypass Techniques Part 1 - Time-Based Attacks

---

# SQLi WAF Bypass Techniques Part 1 — Time-Based Attacks

Web Application Firewall is a good but not perfect solution for protecting websites. It’s the defense framework made by request filtering rules, but those rules could be very simple and easily bypassible. Let’s explore common defenses against SQL injection and how to overcome them!

## Preparation

This time, I will use [testphp.vulnweb.com](http://testphp.vulnweb.com/) website as the example and the CloudFlare firewall in the middle as a proxy:

Now it’s time to go to the terminal and check the offensive side. I have split my terminal in two as I will be using 2 common tools for SQL injection:

One tool is pretty much known by most pentesters — [sqlmap](https://sqlmap.org/). Another is less known but also is pretty good — [ghauri](https://github.com/r0oth3x49/ghauri). Both of those are pretty good for automating SQL injections. Ideally, you want to pass the HTTP request as a file or URL query string to one of these tools. In my experience, the sqlmap is much more aggressive on the network but it’s more faster. The drawback of it is that your IP could be blocked easily if you are not careful.

## Get Ott3rly’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Firstly, let’s try seeing how sqlmap works on our WAF proxy website k1t.uk out of the box:

```
sqlmap -u k1t.uk
```

As you noticed, it immediately gave me a 403 error and identified CloudFlare. This happened because the sqlmap uses its own user-agent out of the box. That’s a pretty annoying feature since you have to specify a –random-agent flag every time. On the other hand, ghauri do not need that!

## Detecting SQLi Without WAF

It’s time to finally hunt for SQL injections! We will first use sqlmap for that but with the –random-agent flag. If you [follow me](https://x.com/ott3rly) on X, you might have seen that I have shared certain sqlmap commands. One command in particular that’s pretty interesting is for crawling websites. That’s right — the sqlmap can also be used as a crawler. Let’s try using sqlmap crawler command on the [original website](http://testphp.vulnweb.com/), which is not under WAF. As it is an intentionally vulnerable site, it should be very easy to find SQL stuff even by using this feature:

```
sqlmap -u testphp.vulnweb.com --random-agent --crawl=3 --forms --hostname --current-db --smart
```

Let’s break down the command mentioned above:

- -u specifies the target URL.

- –random-agent picks a random user agent that looks like a regular user’s browser. This helps to avoid basic CloudFlare user agent blocks.

- –crawl=3 specifies how deep the crawler would go — the link depth.

- –forms will tell sqlmap that this tool could also try putting data into POST, PUT, or any other request found on HTML FORMs. Keep in mind, that this one could be pretty dangerous if you are testing on authenticated flow. I generally use this when I see login forms, and try to bypass them using sqlmap, but with a depth of 1.

- –hostname and –curent-db — I will use those to validate if the SQL injection was successful. It will show me the hostname of the SQL server and the database used for the web application.

- The –smart flag should not be used often, but when I know that there is an intentionally vulnerable app, it will be good enough. It’s only for doing SQL injections if the heuristic checks will tell the tool that there is a high chance of vulnerability.

After running this command, we can see that it has successfully exploited the database:

We can see the current database name and the hostname. Also, we can see the types of SQL injection available for this endpoint:

Let’s copy the vulnerable endpoint identified by the sqlmap since we will be using it throughout this writeup:

Let’s run the sqlmap again, but only for that specific endpoint replaced with WAF proxy URL k1t.uk with added –random-agent flag together with –technique=T to try time-based attacks:

```
sqlmap -u 'http://k1t.uk/listproducts.php?cat=1' --random-agent --technique=T
```

We can see right now that the attack was also successful — the time-based method truly went well. The –random-agent simulated the sqlmap requests as coming from a regular browser.

## Naive WAF Rule Bypass

Let’s imagine a scenario: the cybersecurity team saw requests coming from sqlmap and decided to deploy a simple WAF rule. There were a lot of requests containing the word sleep, someone tried blacklisting it using the following rule:

In this case, it will just check if the URL query — will contain either a lowercase or uppercase string of “sleep”. If we try to run this again from the attack side we will notice, that we will get blocked:

When trying to WAF bypass some basic rules, I suggest listing the tamper scripts for the sqlmap using following command:

```
sqlmap --list-tampers
```

As we know it will just filter out lowercase and uppercase sleep strings, so using the randomcase tamper script might work.

Let’s see it in action:

```
sqlmap -u 'http://k1t.uk/listproducts.php?cat=1' --random-agent --technique=T --tamper=randomcase
```

We can see that this kind of tampering works for pretty basic rules.

## Bit Advanced WAF Rule Bypass

Usually, there will be more smarter rules, like this one right here:

It will convert everything to lowercase and only then compare it to the string. If we deploy this rule, the previous tamper script won’t work in most cases, so the next tampering script that we should try for sleep payloads especially is charencode:

```
sqlmap -u 'http://k1t.uk/listproducts.php?cat=1' --random-agent --technique=T --tamper=charencode
```

This time it has worked!

## Summary

What we learned so far, is to check available tamper scripts, and depending on the situation, and what the tool outputs to us, we need to select a tampering script accordingly. This time we have explored which tampering techniques might work against time-based SQL injections. We saw that the Ghauri tool also works for pretty naive WAF rules. Ideally, you might want to use a mix of both sqlmap and ghauri. For the second part, we will explore other SQL injection WAF bypass techniques for error, boolean, and union-based attacks.

If you find this information useful, please share this article on your social media, I will greatly appreciate it! I am active on [Twitter](https://ott3rly.com/twitter), check out some content I post there daily! If you are interested in video content, check my [YouTube](https://ott3rly.com/youtube). Also, if you want to reach me personally, you can visit my [Discord](https://ott3rly.com/discord) server. Cheers!

---
