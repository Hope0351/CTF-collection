# LockTalk

## Enumeration
In this challenge we get a simple looking API:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, trying to get a ticket is blocked by the HAProxy:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This can be observed in the provided source code:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

From the source code, we can also see it using a python_jwt library version 3.3.3:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)  
With a bit of googling we can find that it is vulnerable and we should be able to forge new claims:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

There's even a helpful POC:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we know we need to forge an administrator token from the source code. This is important because usually you would think we need `admin`, but in this case we need `administrator`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution
Before we forge an administrator token we need a guest token. A bit of researching into HAProxy and bypasses, we find a helpful list here:  
eird_proxies/blob/master/Haproxy-and-Nuster.md#vulnerable-configs

With a simple extra slash at the beginning of the URL we bypass the proxy and get a token:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We run the POC we downloaded earlier to forge an administrator JWT token.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We verify and confirm that the administrator claim has been injected:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we get our flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Or not. The weird part of this CVE is how it treats the JSON objects so we actually need to copy the entire thing, including the curly braces and pass that as the JWT:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And now we get our flag. Interesting find for this CVE, very strange behaviour:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{h4Pr0Xy_n3v3r_D1s@pp01n4s}`
