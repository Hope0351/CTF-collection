# :globe_with_meridians: SQLi: Next Level. When not even SQLMap’ --eval can help…

> **Original Source:** [SQLi: Next Level. When not even SQLMap’ --eval can help…](https://infosecwriteups.com/sqli-next-level-5b1145b83c79)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## Get Rend’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Part Two: Reverse Engineering JS Code
I searched for the encrypted value in the server’s previous response and didn’t find any instance of that value, so I could be pretty sure the encryption happens client-side in the js code.
alright, how to find the js code in charge of encrypting the query?
the first clue can be the request itself:


```
{
"param1": "<Search Filter='GIBBERISH HERE' Order='DESC' Sort='priority'/>",
"param2": "something..",
...
}
```


I searched for the name of the parameter containing the gibberish data and found the code which built the XML data.
nice, a good starting point. now it’s time to analyze the code.
how? using the best js debugging tool ever: chrome devtools 😏


PRO TIP
read this document entirely:
[https://developer.chrome.com/docs/devtools/javascript/](https://developer.chrome.com/docs/devtools/javascript/)


long story short, by use of `devtools` and setting some breakpoints I found out the workflow behind that obfuscated value:


1. based-on the dropdown option user selects, an SQL query would be selected:


```
function SelectFilter(selectedFilter) {
switch (selectedFilter) {
case "unread messages":
filter = "mailType = 1"
break; case "high priority":
filter = "mailType = 1"
break; case "having attachment":
filter = "mailType = 1"
break;
}
return filter;
}
```


2. then encryption of the query happens:


```
function encrypt(Filter){
// grep session token

// mix the query with session token

// base64 encode the result of previous step // obfouscate the result of previous step

// base64 encode again return Filter;
}
```


3. after that js query builds the XML data
4. and at the end, puts the XML in JSON and sends the request


At this moment I was pretty sure that if I find a way to encrypt my SQL payload the way the js code does and send it to the server, there would be an injection in the backend code. why?
Simple,
because when the developer has tried this hard to hide the query being transmitted and has done all of this client-side, he thinks his shield is impenetrable and… there is no protection server-side 😏


ok, now we know the workflow. how to use this knowledge to inject our own query? writing a script to do the same encryption ??
no, much simpler than that…


use `devtools`…
put a breakpoint on the first line of the encryption function,
change the value of function’s argument to your own query,
hit the resume button and let code does its job, but in a malicious way 😉
*I told you to read the *`*devtools*`* documentation, didn’t I?* :)


I used a simple boolean-based injection to confirm the vulnerability. and after that using the string concatenation technique I found out that the backend DBMS was `SQL Server`.
you can find this technique at the beginning of portswigger’s `SQL Injection cheat sheet`:
[https://portswigger.net/web-security/sql-injection/cheat-sheet](https://portswigger.net/web-security/sql-injection/cheat-sheet)


after executing a couple of queries I realise that the injection was boolean-based.


As you remember the job of the vulnerable query was returning the received mails data, right?
then if it returns data, why the injection is blind?
read this article to learn how to turn your blind injections to union-based ones: ✌️
[https://medium.com/@Rend_/healing-blind-injections-df30b9e0e06f](https://medium.com/@Rend_/healing-blind-injections-df30b9e0e06f)


ok, at this stage I needed to use `SQLMap` for automation.
but how to use `SQLMap` when the vulnerable parameter is being this hard obfuscated… ?

---

*Originally published on [Medium](https://infosecwriteups.com/sqli-next-level-5b1145b83c79). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
