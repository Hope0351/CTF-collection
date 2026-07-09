# It Has Begun

## Enumeration
The first very easy forensics challenge provides a bash script:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution
Within it, we find the first part of the flag, but reversed:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

No worries, we can reverse it back in the terminal using `rev`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Further down in the script, we see a base64 string so let's decode it:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Now that we have the first and second part of the flag, we put it together and submit it:  
`HTB{w1ll_y0u_St4nd_y0uR_Gr0uNd!!}`
