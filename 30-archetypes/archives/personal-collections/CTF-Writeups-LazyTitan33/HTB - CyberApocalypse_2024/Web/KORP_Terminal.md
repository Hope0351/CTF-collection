# KORP Terminal

## Enumeration

The web application shows a very nice old school login prompt:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

If we try a single quote we get a very helpful SQL error indicating a possible SQL Injection vulnerability:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution
In this case SQLMap goes brrr. We don't need to conserve our time for the harder challenges ahead.
```bash
sqlmap -r req.txt -p username --dbms=mysql --ignore-code 401 --dump
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Easy crack with rockyou since it's one of the first passwords in the wordlist:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After we log in, we get our flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{t3rm1n4l_cr4ck1ng_sh3n4nig4n5}`
