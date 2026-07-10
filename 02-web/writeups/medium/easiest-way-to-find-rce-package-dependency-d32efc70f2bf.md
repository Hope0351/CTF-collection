# :globe_with_meridians: Easiest way to Find RCE (Package Dependency)

---

# Easiest way to Find RCE (Package Dependency)

Free Article

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
