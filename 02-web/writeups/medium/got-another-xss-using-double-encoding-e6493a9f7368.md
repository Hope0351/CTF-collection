# :globe_with_meridians: Reflected XSS using Double Encoding

> **Original Source:** [Reflected XSS using Double Encoding](https://infosecwriteups.com/got-another-xss-using-double-encoding-e6493a9f7368)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

and checked the source code.


*source code*


Then I added a single quote but it filtered the input and replaced it with *hello1&amp;* in some places and with ‘&’ in our target fields.


I tried URL encoding there, Then also got the same output which means it decodes the input.


So I used [Double Encoding](https://owasp.org/www-community/Double_Encoding).
By using double encoding it’s possible to bypass security filters that only decode user input once. The second decoding process is executed by the backend platform or modules that properly handle encoded data, but don’t have the corresponding security checks in place.


It works.


Then our basic payload ‘><script>alert(1)</script> with double encoding tried.

>

%2527%253E%253Cscript%253Ealert%25281%2529%253C%252Fscript%253E


But it created an error


I searched for attributes of input tag to exploit using it.
[onfocus](https://www.w3schools.com/jsref/event_onfocus.asp) : The onfocus event occurs when an element gets focus.


## Get ag3n7’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


‘ onfocus=’alert(1)’

>

%2527%2520onfocus%253D%2527alert%25281%2529%2527%2520


I clicked on the search bar, and the popup alert appeared.


But I thought of modifying it a little bit with autofocus which makes the text field automatically get focused upon page load and creates the popup alert while visiting the page itself.


‘ onfocus=’alert(1)’ autofocus=’

>

%2527%2520onfocus%253D%2527alert%25281%2529%2527%2520autofocus%253D%2527

---

*Originally published on [Medium](https://infosecwriteups.com/got-another-xss-using-double-encoding-e6493a9f7368). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
