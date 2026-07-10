# :globe_with_meridians: Swagger XSS Mass Hunting. Hi guys, in this write-up, I’m gonna…

> **Original Source:** [Swagger XSS Mass Hunting. Hi guys, in this write-up, I’m gonna…](https://infosecwriteups.com/swagger-xss-mass-hunting-b7a19e23cfd9)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

*In the name of Allah*


## Get YoungVanda’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Hi guys, I’m YoungVanda and in this write-up, I’m gonna explain my own approach towards Swagger XSS and why I don’t use the Nuclei template ( swagger-api.yaml) ;d


### The Entire Flow


```
1. Find as many subdomains as possible
2. cat all_subs.txt | dnsx | tee -a resolved_ones.txt
3. cat resolved_ones.txt | httpx | tee -a alive_ones.txt
4. ffuf -w /root/wordlist/api/swagger_xss.txt:FUZZ -w alive_ones.txt:URL -u URLFUZZ -mc 200 -o ffuf-result.txt
5. cat ffuf-result.txt | jq -r .results[].url | tee -a feed_me_to_httpx.txt
6. cat feed_me_to_httpx.txt | httpx -silent -title | tee -a title.txt
7. cat title.txt | grep "Swagger UI"
```


### First Step


Find as many subdomains as possible you can get help from Chaos.

### Second Step


Now it’s time to resolve subdomains. If you get false positive, use ShuffleDNS with -d and -l options.

### Third Step


After resolving them, we need to find alive subdomains. You can add
User-Agent, Time Delay and etc

### Fourth Step


Now we are ready to fuzz for Swagger UI endpoints.


```
ffuf -w /root/wordlist/api/swagger_xss.txt:FUZZ -w alive_ones.txt:URL -u URLFUZZ -mc 200 -o ffuf-result.txt
```


### Fifth Step


Extracting found URLs from ffuf result.


```
cat ffuf-result.txt | jq -r .results[].url | tee -a feed_me_to_httpx.txt
```


### Sixth Step


Now, we use httpx with -title to get the title of fuzzed and possible endpoints for Swagger UI.


```
cat feed_me_to_httpx.txt | httpx -silent -title | tee -a title.txt
```


### Seventh Step


```
cat title.txt | grep "Swagger UI"
```


### Why Not Nuclei (swagger-api.yaml) ?


- In this methodology wordlist is so important and what I realised is that the wordlists inside this template is not enogh.

- We’re looking for Swagger UI not API paths. We should be aware of our wordlist so this way you can reduce the extra traffics. I mean you should remove endpoints like this:
* /swagger-ui.js
* /swagger-ui.yaml
* /swagger-ui.json
Because you looking for Swagger UI, which under a certain version is vulnerable to XSS, not API path. But if you’re looking for API path that’s a different thing.

### Best Approach


I think the best approach would be fixing above-mentioned problems and code your own private nuclei template. Even though, my methodology worked fine so far, I was able to find multiple VDP bugs, and you can use it if you’re not into coding templates, but it takes lots of time and energy, also you have to send lots of requests. Therefore, I tried to explain my previous methodology and the reason why I don’t use default Nuclei template in this regard so you guys can think and get the idea or maybe you can come up with a better methodology.

### Update


Check out this post. I talked about my recent RDP finding and some more useful tips:
[https://twitter.com/young_vanda_/status/1700590035282587861](https://twitter.com/young_vanda_/status/1700590035282587861)


My Twitter Account: [@young_vanda_](https://twitter.com/young_vanda_)

---

*Originally published on [Medium](https://infosecwriteups.com/swagger-xss-mass-hunting-b7a19e23cfd9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
