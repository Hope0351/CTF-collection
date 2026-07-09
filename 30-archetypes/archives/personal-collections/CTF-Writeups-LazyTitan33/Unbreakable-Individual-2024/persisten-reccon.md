# persistent-reccon

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

With this challenge, we only get a generic looking login page:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, this challenge had an `OSINT` tag associated with it so we screenshot the login and do a Google reverse image search:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The first result mentions a `Westermo` product, clicking on it we can see a Lynx series switch:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can google for the default credentials:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`admin:westermo`

We try and use that and we get the flag:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`CTF{7e33e33a06c53d77330b9621a62fd4f1915e6e695f3188aba62c6800695ee30e}`
