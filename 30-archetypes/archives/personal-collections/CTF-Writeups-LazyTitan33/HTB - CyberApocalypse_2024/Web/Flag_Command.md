# Flag Command

## Enumeration

The web application provided starts as an old school game with prompts and we have to choose from some options:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We see it making a GET request to an API for some options:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Which shows us the possible commands:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution
At the bottom we see a secret command. I wonder what that does if we input that instead of the expected commands:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Nice, we got the flag:  
`HTB{D3v3l0p3r_t00l5_4r3_b35t_wh4t_y0u_Th1nk??!}`
