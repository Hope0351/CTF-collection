# :game_die: Medium

---

>

**1.3 — What’s the CVE you’re using against the application?**

Now we need to take a better look at the application.

As we can see in the nmap scan results, the port 80 is open with http service running what makes us think in a web application.

So let’s check what the browser shows us!

**Step 1: Paste the IP target in the browser.**

That’s what we got:

The default page of server apache running in this site.

It doesn’t have a lot of useful information, but maybe there is some hidden directory that we can find.

**Step 2: Do a directory brute-force to find hidden directories.**

You can use any tool you prefer.

I’ll be using gobuster with the wordlist below:

[https://github.com/danielmiessler/SecLists/blob/master/Discovery/Web-Content/directory-list-2.3-small.txt](https://github.com/danielmiessler/SecLists/blob/master/Discovery/Web-Content/directory-list-2.3-small.txt)

>

gobuster -u http://10.10.179.177 -w directory-list-2.3-small.txt dir

We found a directory named **simple/** so let’s take a look.

**Step 3: Take a look at simple directory:**

>

http://”Target IP”/simple/

And we found what seems to be a home page of the application.

Let’s explore this page and see if we can find something interesting.

At the bottom of the page there is a useful information.

The site tells us that it is powered by CMS Made Simple, that seems to be a Open Source Content Management System, still tells us the version 2.2.8.

Knowing that, we can search for exploits for this version of CMS Made Simples.

**Step 4: Search for CVE’s to CMS Made Simple version 2.2.8.**

Searching on [https://cve.mitre.org/](https://cve.mitre.org/), we find that it is vulnerable to sql injection attacks.

>

**Answer: CVE-2019–9053**

---
