# :game_die: How I Gained Access to a Multi-Billion Dollar Retailer’s MySQL Databases Using Simple SQL Injection

> **Original Source:** [How I Gained Access to a Multi-Billion Dollar Retailer’s MySQL Databases Using Simple SQL Injection](https://infosecwriteups.com/how-i-got-owned-a-multi-billion-dollar-retailers-mysql-databases-using-simple-sql-injection-30f8b0dfd9ce)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# How I Gained Access to a Multi-Billion Dollar Retailer’s MySQL Databases Using Simple SQL Injection


Hello, thank you for stopping by.


This is my first article on Medium. Usually, I am not fond of writing blogs these days, as I am actively sharing my bug bounty experiences and tips on Twitter whenever I find something interesting. Additionally, I must admit that I am not a skilled writer, so please forgive any typos or grammatical errors you may come across.


*SQL injection (https://www.flickr.com/photos/149561324@N03/34852913554)*

>

If you’re interested, please continue reading the story of one of my most remarkable discoveries to date (at least, I believe so!). However, I understand that the post might be a little lengthy, so feel free to skip the initial part if you prefer to dive straight into the details without the introductory “blah-blahs.”


I have a personal blog at [https://www.nav1n.com](https://www.nav1n.com), where I used to write articles on HackTheBox and TryHackMe machines, as well as solve flags. However, I completely stopped writing on it nearly three years ago due to time constraints. So, this marks my second attempt to restart my blogging journey.


This article tells the story of an SQL injection vulnerability I discovered on a country-specific eStore of a multi-billion dollar retailer and on their user experience enhancement program.


As I delved deeper, I later found the entire group’s websites are vulnerable to this specific issue with one single parameter that lead me try different things and ultimately owning their multiple database servers using simple error-based SQL injection, In one case, I even managed to have a potential RCE on the server.


To find this vulnerability, I didn’t rely on any major tools or techniques. Instead, I used the same methods that every bug bounty hunter employs on a daily basis, utilizing tools such as Burp Suite, ParamSpider, and SQLMap.


*Disclaimer: Below article is for educational purpose only. I’m no way endorse the hacking or unethical ways to hack/test a website unless you have obtained a permission to do so.*

## The Enumeration Phase


I recently came across a YouTube video that discussed a specific reconnaissance process. The presenter mentioned their discovery of remote code execution (RCE) and SQL injection vulnerabilities on a private bug bounty target.


They shared their use of simple Google dorks, such as “site:*.*.xx inurl:bug inurl:bounty site:*.*.xx.xx intext:security report reward site:*.*.xx intext:security report reward,” to find these targets. Although I had known about these dorks for years as a bug hunter, I had never tried them in practice.


Curiosity sparked, I ran some of the dorks and uncovered hundreds of targets. However, most of them turned out to be Vulnerability Disclosure Programs (VDPs) with Hall of Fame acknowledgments but no monetary rewards. Nevertheless, I persisted in my search and stumbled upon a non-English target, which happens to be a major online and in-store retailer present in almost all countries worldwide.


They had a *security.txt* page explicitly stating that the scope covered all web assets within their group of companies, including international ones. In their reward table, I noted they offered up to 3.5K EUR for SQL injection and RCE, and 500 EUR for XSS, IDORs, SSRF among other vulnerabilities.


Encouraged by this, I decided to focus my efforts on this target, hoping to discover some SQL injection, RCE, or CVE-related vulnerabilities.

## Finding an SQL Injection


Knowing that SQL injection vulnerabilities are typically easier to find compared to remote code execution (RCE) vulnerabilities, I decided to prioritize SQL injection attacks as my initial target.

### #1 Subdomain Enumeration:


In order to maximize my subdomain enumeration efforts, especially for larger targets that permit subdomain discovery, I follow a methodology that involves utilizing various tools and resources. My preferred tools for subdomain enumeration include [Netlas](https://app.netlas.io/ref/b0fde95e/), crt.sh and [securitytrails.com](https://securitytrails.com). These platforms allow me to search and gather information on subdomains associated with the target, providing me with a comprehensive list for further investigation.

>

I agree that securitytrails service charge is every expensive if you compare it to a lot of alternatives, but their free tier gives 50 API runs with unlimited subdomain search per month.


#2 Certificate transparency (CT) search:


Initially, I began the process of subdomain enumeration by CT tools such as crt.sh and Netlas.io. By combining the results from both tools, I was able to discover approximately 4961 subdomains associated with the group name.


Netlas:

>

Sample netlas query to find certificates:


```
https://app.netlas.io/certs/?q=certificate.subject.organization%3A%22Microsoft%20Corporation%22&page=1
```


SecurityTrails:


Once I obtained the list of subdomains from certificate transparency, I proceeded to use SecurityTrails. I came across a useful curl command (which I discovered in a Discord server) to find subdomains of their main website.


```
curl -s --request GET --url https://api.securitytrails.com/v1/domain/target.xx.xx/subdomains?apikey=*
| jq '.subdomains[]' | sed 's/\"//g' > target.xx.xx.txt 2> /dev/null
&& sed "s/$/.target.xx.xx/" target.xx.xx.txt | sed 's/ //g'
```


The script successfully returned some 2,000 subdomains. I copied all of them into my Excel spreadsheet and proceeded to filter out any duplicates to ensure a clean and concise list.

>

I still use Excel to remove duplicates from my extensive lists. I firmly believe that it is the best and most efficient method, at least for me. ;)


#3 HTTP Probing:


After filtering out the duplicates, I ended up with 3,154 unique subdomains. I transferred this list to my Kali machine and ran HTTPx against them. As a result, 2,892 URLs that are now available for further investigation and potential attacks.


URL List >> ParamSpider.py:


By far, ParamSpider by @0xAsm0d3us is considered one of the best parameter fuzzer tools or parameter-miners, whichever term you prefer. I also use Arjun by [@s0md3v](https://twitter.com/s0md3v), but to be honest, I feel a bit more comfortable with ParamSpider.


Since my target is extensive and ParamSpider, by default, supports only a single URL (I don’t understand why you do this to us, [@0xAsm0d3us](https://twitter.com/0xAsm0d3us)), I had to find an alternative way to achieve my goal.


I stumbled upon a script that I had previously used with one of my friends. This script takes a list of URLs, sends them through xargs, removes duplicates, and provides a refined list. Although I encountered some errors while running it, I still managed to obtain the desired list.


*Scanning multiple urls/ list of urls using ParamSpider:*


```
cat target.lst | xargs -n 1 -I {} python3 ~/ParamSpider/paramspider.py --domain {} --level high | urldedupe >> all_spiderparamters.txt
```


The results were quite shocking — I now have a whopping 1,796,149 lines in total!


The file size itself is around 96MB. I thought it wouldn’t be wise to run all of them through Burp Suite or SQLMAP, as it would consume a significant amount of resources and potentially crash my Kali host. Therefore, I decided to break the files into smaller sizes of 10MB each and work on them one by one.


I set up my Burp Suite and started scanning the first small list. Initially, I encountered several low-hanging issues such as open redirects, CORS misconfigurations, and even a few instances of XSS. However, I didn’t come across any high or critical vulnerabilities.

>

It’s worth noting that many readers have asked me how it’s possible to scan multiple URLs in Burp Suite. Well, it is indeed possible with the Burp Suite Professional version. For more information, you can refer to this blog post: [https://portswigger.net/blog/launching-scans](https://portswigger.net/blog/launching-scans).


Since I didn’t find any major vulnerabilities in the first file, I let Burp Suite continue its job on the second file and took my wife and kids out for a weekend dinner. When we returned after 3–4 hours, I noticed that Burp Suite was still running, but there was a flashing red exclamatory icon indicating an issue type (SQL Injection).


The Burp Suite finally discovered a boolean-based SQL injection vulnerability for me. I confirmed that the server was running Apache. I sent the vulnerable URL to the Repeater tool and tried various sleep queries like “1'XOR(SELECT(1)FROM(SELECT(SLEEP(8)))a)XOR’Z”, “1' ORDER BY 1 — +”, and “1 or sleep(5)” to test the server’s response.


## Get nav1n👨🏻‍💻⚠️’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Unfortunately, I consistently received a JSON message from the server stating “Success.” It appears that the WAF (Web Application Firewall) or the server itself was sanitizing or blocking known SQL injection payloads, preventing successful exploitation.


## #4 First Breakthrough


I spent an hour trying different methods to provoke an error or execute the `sleep()` function, but unfortunately, none of them worked. The SQL injection attempts through GET requests were unsuccessful.


Determined to find a vulnerability, I decided to switch the request method to POST and sent a simple payload, `1=1'`, as the value for the vulnerable parameter and received the following error response:

>

SQLSTATE[42000]: Syntax error or access violation: 1064 You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near ‘’1=1'’))


This error message indicates that the server is vulnerable to SQL injection, as the payload was not properly sanitized and caused a syntax error in the SQL query execution.


Now that I confirmed the presence of SQL injection vulnerability on the website, I wanted to determine how many endpoints are utilizing this vulnerable parameter. To do this, I extended my search in Kali and used the `grep` command to search for the parameter "xxx" across the 2892 geographically based subdomains. Surprisingly, I found only 4 subdomains that were using this parameter.


Curious to explore further, I opened the links associated with these subdomains, only to be redirected to the homepage. This indicated that these pages were no longer active. To gather more information about these pages, I turned to archive.org and found a cached version that revealed the nature of these pages as user experience enhancement suggestion pages, primarily in an unfamiliar language. After examining the archive.org content, I returned to my Kali VM to continue my investigation.

## #5 SQLMAP or Ghauri here is the Winner


I recently discovered that Ghauri ([https://github.com/r0oth3x49/ghauri](https://github.com/r0oth3x49/ghauri)) has been outperforming SQLMAP in terms of exploit success in some conditions. In multiple instances, when SQLMAP failed to find the exploit, Ghauri was able to successfully identify it within a few minutes.


To leverage Ghauri’s capabilities, I saved the request in a file and ran SQLMAP with minimal options, including the -r request.txt and -p xxx flags, as well as the -random-agent flag. However, despite my attempts, SQLMAP failed to discover the exploit and instead returned various errors such as 500 and 4xx status codes.


In one of my recent tweets, I reached out to the bug bounty community for assistance in a similar situation. While there were several helpful suggestions, none of them proved successful except for the recommendation to use Ghauri.

>

[https://twitter.com/nav1n0x/status/1630627895952527361](https://twitter.com/nav1n0x/status/1630627895952527361)


*[https://twitter.com/nav1n0x/status/1630627895952527361](https://twitter.com/nav1n0x/status/1630627895952527361)*


I submitted the same request to Ghauri, and the results were quite impressive. Ghauri was able to identify the exploit for both time-based blind SQL injection and boolean-based blind SQL injection in just 4 minutes. This is significantly faster compared to SQLMAP, which failed to find the exploit in my previous attempts.


Ghauri’s efficiency and accuracy in detecting vulnerabilities make it a valuable tool in my bug bounty toolkit. It has proven to be a reliable option, especially in cases where SQLMAP falls short.


#6 Retrieving Database Name


Now it’s time to retrieve the database name to validate the exploit. I executed the following command in Ghauri:


```
ghauri -r xxx -p xxx - dbms=mysql - dbs
```


And here I have the nice beautiful xxx* database name, which suggest the db is of a production database.


By running Ghauri on the entire set of endpoints, I was able to discover different databases, including staging and UAT (User Acceptance Testing) endpoints. This expanded the scope of the exploit and provided valuable information about the underlying infrastructure of the target, highlighting potential areas of vulnerability.


#7 Retrieving banner and current-user


```
ghauri -r xxx -p xxx - dbms=mysql -D xxx - current-user -b
```


## #8 Retrieving Admin username and password hash


I proceeded to explore the tables in the main production database and discovered a table named “admin__” that contained the following columns:


As the column p*_*_ is present, I know I can be the new owner of the database :), but I just want the bounty not the database.


I run the following command to retrieve the password hash.


```
ghauri -r xxx -p xxx - dbms=mysql -D xxx -T a_ -C p*_ - dump
```


And..here it is. I now have the admin password hash and the password which would let me own any of their database from 3 major eStore.


I humbly submitted a comprehensive report detailing my findings and analysis, including the discovery of the admin password hash and the corresponding password that could potentially grant me access to any of their three major eStores.


On Monday evening, I received a reply from the organization, expressing their interest in investigating further for additional vulnerabilities. However, despite my efforts, I was unable to identify any additional vulnerabilities.


Later that same night, I received acknowledgement of the acceptance of the reported vulnerabilities. The organization is currently engaged in internal discussions regarding the bounty and the implementation of necessary fixes. In total, I reported four SQL injections, three XSS vulnerabilities, and one open redirect. Considering the severity and impact of these findings, I am anticipating a minimum payout of 4.5K EUR as a bounty reward.


That concludes the summary of my successful findings and ongoing progress.


That’s all.


Takeaways:


- Always go for a larger scoped target.

- Make use of GoSpider, ParamSpider and Arjun.

- The Archive.org has more vulnerable endpoints cached then the live ones.

- If the GET request didn't work, try POST and change the protocol to HTTP1/0 to 2/0 see if it helps.


Thank you for reading. Will comeback soon with another interesting story of multiple Log4Shell findings on a major Sports goods manufacturer’s webapp.

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-got-owned-a-multi-billion-dollar-retailers-mysql-databases-using-simple-sql-injection-30f8b0dfd9ce). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
