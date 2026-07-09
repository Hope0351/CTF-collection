# TimeKORP

## Enumeration

The web application gives us the option to check what time it is, or what date it is:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, from the source code, we can see that it's executing the `date` linux command and using our user input, the `format`, without being sanitized.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

From the Docker file, we can also see where the flag should be:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In this case, we simply need to close the single quote for the date command, add a semicolon, our command, add another semicolon and use another single quote for the stderr redirect.

## Solution
Payload: `';cat /flag;'`  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Nice, we got the flag:  
`HTB{t1m3_f0r_th3_ult1m4t3_pwn4g3}`
