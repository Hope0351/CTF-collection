# :globe_with_meridians: Reflected XSS in Facebook’s mirror websites

> **Original Source:** [Reflected XSS in Facebook’s mirror websites](https://infosecwriteups.com/reflected-xss-in-facebooks-mirror-websites-4384b4eb3e11)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Reflected XSS in Facebook’s mirror websites


Heyyy Everyoneee,


I hope everyone is doing good , it’s been a while since I haven’t shared any writeup of my finding’s.


This blog post is going to be about a reflected xss bug affecting Facebook mirror websites. I will be explaining the whole process how I found the vulnerable endpoint.


Well many people ask me how do I look for xss bugs so in this same blog I will also share my method of finding xss.


And here we go…..


I was collecting subdomains of *thefacebook.com* domain, as I have seen many writeups regarding bugs found in *thefacebook.com* subdomain only. I wanted to find something there too :)


Started with collecting the subdomains. I basically use tools like [Findomain](https://github.com/Edu4rdSHL/findomain), [Subfinder](https://github.com/projectdiscovery/subfinder),[Assetfinder](https://github.com/tomnomnom/assetfinder),etc to find subdomains of my target. After I collected the subdomains I used another tool called [httprobe](https://github.com/tomnomnom/httprobe)


After the subdomain enumeration part is completed. I have a habit of doing directory bruteforcing(using [ffuf](https://github.com/ffuf/ffuf)) on all the collected hosts from httprobe, then going through them to see if I can find some easy wins. Look at the below code that’s how I do it

*python3 dir.py httprobe.txt*


While I was looking at the [https://mirror-ext.glbx.thefacebook.com](https://mirror-ext.glbx.thefacebook.com) ffuf result:


Only one directory was there,I decided to look what might be there. [http://mirror-ext.glbx.thefacebook.com/help/](http://mirror-ext.glbx.thefacebook.com/help/)


It was normal help page with the support email address, didn’t seem interesting to me at first but looking at the page source I could see something ineteresting.


Look at the second line, I tried accessing that endpoint [http://mirror-ext.glbx.thefacebook.com/.layout/mirror.php](http://mirror-ext.glbx.thefacebook.com/.layout/mirror.php) and it was just a blank page :(


This time there was nothing in the page source code too that I can look further into, then I decided to find more php endpoints under the /.layout directory.


These were the files which I was able to find using different wordlists. They were all same as the earlier one mirror.php blank page, only one was different header.php


*[http://mirror-ext.glbx.thefacebook.com/.layout/header.php](http://mirror-ext.glbx.thefacebook.com/.layout/header.php)*


Looking at the page source code I found that the endpoint was getting reflected inside anchor tag href value, it might be vulnerable to xss so I started testing for it.


Adding characters like “>< at the end of the url gave *not found page*.


I didn’t wanted to give up so easily as I can smell xss there. I started bruteforcing for parameters but didn’t find any.


Upon adding a slash and then another directory name didn’t gave me the *not found error* like last time.I tried this because of @[brutelogic](https://twitter.com/brutelogic/) blog which I read in the past


*[http://mirror-ext.glbx.thefacebook.com/.layout/header.php/shirley](http://mirror-ext.glbx.thefacebook.com/.layout/header.php/shirley)*


Trying again with “>< and I found that they are getting url encoded.


Later I realised that the href value is inside single quotes. So trying with single quote this time.


I tried this at first when I saw that my input was getting reflected inside href, href=’/javascript:alert()’, but this wasn’t working because there is a slash before our input. I started looking on google for a way to include two href in a single anchor tag , found a solution on [https://stackoverflow.com/questions/13965753/how-can-i-open-multiple-links-using-a-single-anchor-tag](https://stackoverflow.com/questions/13965753/how-can-i-open-multiple-links-using-a-single-anchor-tag)


Based upon the solution , the final payload was:


I was like holy sh*t!! I just found a xss on a Facebook domain.


## Get Sudhanshu Rajbhar’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Well I knew about some more Facebook mirror domains so tried to see if I can replicate the same xss on there also. Result was:


*mirror.facebook.net*


One more subdomain was vulnerable [http://mirror.t.tfbnw.net/](http://mirror.t.tfbnw.net/) but I don’t have any screenshot of it.


That’s the end of the story.


Regarding the fix, now the single quote(‘) is converted to &.


I was rewarded with a $500 bounty for this xss.


Video POC:


## Now moving on to the second part,


How do I look for xss bugs?


I am using this awesome burp plugin called [reflector](https://github.com/elkokc/reflector)


It basically checks the parameter whose value is getting reflected in the source page and then tries to see which symbols are also getting reflected in the source page like “,>,<,{,},’,etc


You just need to browse the web application , visit every page there, fill all the input fields. Then look at the burp issue tab to see if it has find anything.


*[https://github.com/elkokc/reflector/blob/master/screenshot/symbols_analyse.png](https://github.com/elkokc/reflector/blob/master/screenshot/symbols_analyse.png)*

### Talking about some automation work:


Use tools like paramspider , gau ,etc to collect endpoints which have parameter in them then you can use kxss, dalfox (choice is yours, use whatever tool which works for you, they both are very good.) on them to see if you can find some xss. Below you can see the dalfox tool in action


[https://twitter.com/0xAsm0d3us](https://twitter.com/0xAsm0d3us)


[https://twitter.com/hacker_](https://twitter.com/hacker_)


[https://twitter.com/TomNomNom](https://twitter.com/TomNomNom)


[https://twitter.com/hahwul](https://twitter.com/hahwul)

### Beginner Guide


If you are a beginner and want to learn about xss, start by reading blogs there are many great people writing blogs about xss like [@brutelogic](https://twitter.com/brutelogic) (He is very kind and helpful. If you are having a hard time bypassing a xss waf or something , he is always ready to help you there. )


[https://twitter.com/soaj1664ashar](https://twitter.com/soaj1664ashar)


[https://twitter.com/s0md3v](https://twitter.com/s0md3v)


There are many more just search them on google yourself.


Want to practise xss somewhere goto : Portswigger Web Security Academy


Do ctf challenges related to xss, watch poc videos/writeups they will give you an idea where you should look for xss, which fields are more prone to be vulnerable to xss eg. search fields, submit forms, etc .


That’s all, thankyou very much for reading it till the last. Hope you would have enjoyed it.


Sya everyonee

---

*Originally published on [Medium](https://infosecwriteups.com/reflected-xss-in-facebooks-mirror-websites-4384b4eb3e11). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
