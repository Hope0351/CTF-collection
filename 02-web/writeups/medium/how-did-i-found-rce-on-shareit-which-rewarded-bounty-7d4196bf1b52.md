# :globe_with_meridians: How did I found RCE on SHAREit which rewarded $$$ bounty

---

# How did I found RCE on SHAREit which rewarded $$$ bounty

Hello all, hope y’all are doing great. My name is Suprit, Hacker name- s3ctat0r and today we’re going to learn a critical vulnerability. The bug has been fixed now so I’m able to disclose this story publicly.

I believe that recon is the real success for bug hunting. We were hunting on SHAREit’s Vulnerability Disclosure Program i.e. Bug Bounty Program. In recon phase I generally use subfinder and assetfinder to enumerate all the subdomains but this time I thought to add api keys with my favorite weapon subfinder and as expecting there were a greater number of results!!

On the day I was hunting with my friend, mentor , Hacker name — brutlix and we had successfully exploited this critical vulnerability present on the SHAREit’s web server.

Our recon methodology is:

>

Subdomain enumeration > Fuzzing > analyze APIs like shodan, censys, etc > Templating > Manual Testing

During my Reconnaissance phase, while templating we had discovered CVE-2021–44228 which results log4j shell.
In general, CVE refers to Common Vulnerability Exposures which are 0day bugs & may be their way of exploitation is available in the market.

*log4j shell*

>

*What is log4j shell?*

Log4j is a Java-based logging utility that allows developers to output messages from their application to various output targets, such as the console, a file, a database, or a remote server. It provides a flexible and configurable logging framework with fine-grained control over log levels, message formatting, and filtering. Log4j uses a hierarchical structure for organizing loggers, with each logger having a name that reflects its position in the hierarchy. Loggers can be configured to inherit settings from their parent loggers or to override them with their own settings. Log4j also supports various appenders, which are responsible for writing log messages to different output targets. Developers can choose from a wide range of built-in appenders or create their own custom appenders. Log4j has been widely used in the Java community for many years, and it continues to be actively maintained and improved by the Apache Software Foundation. However, in December 2021, a critical vulnerability was discovered in Log4j versions 2.0 to 2.15, which could allow attackers to execute arbitrary code remotely. As a result, users are strongly advised to update to the latest version (2.16.1 as of February 2023) or take other mitigating measures.

## Get Suprit Pandurangi’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Now, after analyzing, manual testing begins on the webserver & we visited the webpage and started to manipulate the network traffic captured in the Burp proxy. After trying harder, we had discovered “accept” parameter to be vulnerable.

Repeater tab is the best friend of all bug hunters. But it displayed 406 status code i.e. Not Acceptable LMAO!!
But still we checked the burp collaborator client since, for this scenario it will act as LDAP server.

*Response from SHAREit server*

BooM !! we got a nice catch here :)
For further confirmation of RCE vulnerability we investigated with DNSLog server as well.

Hahaha, as expected we got the results :)
and we reported this critical vulnerability to SHAREit after a day of reporting the bug has been patched within 24 hours and rewarded three digit bounty :))

Hope you have learnt something new from my experience.
:D Hacking!!

---
