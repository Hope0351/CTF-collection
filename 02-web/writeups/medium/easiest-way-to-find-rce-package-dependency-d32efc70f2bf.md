# :globe_with_meridians: Easiest way to Find RCE (Package Dependency)

> **Original Source:** [Easiest way to Find RCE (Package Dependency)](https://infosecwriteups.com/easiest-way-to-find-rce-package-dependency-d32efc70f2bf)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Easiest way to Find RCE (Package Dependency)


[Free Article](https://medium.com/@jeetpal2007/easiest-way-to-find-rce-package-dependency-d32efc70f2bf?sk=49407366f7d1616155408794a169672d)


Hello


Today I will show you the easiest way to find RCE via Package Dependency Confusion


Let’s Start


Requirements


> First let try this on a target name “target” and try 2 ways to find it


Way №1


First We need to find subdomains using subfinder


```
subfinder -d target.com -v -o target_subdomains.txt
```


Commands


- -d : Define the domain

- -v : verbose result

- -o : Output file name


Now use httpx


```
cat target_subdomains.txt | httpx-toolkit > Out_put_File_of_httpx.txt
```


Now use nuclei


```
nuclei -l Out_put_File_of_httpx.txt -t nuclei-templates/http/exposures/configs/package-json.yaml -o packages.txt -v
```


Commands


- -l : Define file name where subdomains are stored

- -t : Template name

- -o : Define output For it

---

*Originally published on [Medium](https://infosecwriteups.com/easiest-way-to-find-rce-package-dependency-d32efc70f2bf). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
