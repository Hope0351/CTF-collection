# An unusual Sighting

## Enumeration
For this challenge, we receive two files. A bash history and the sshd log file.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution
We start the challenge by connecting to the provided IP and port:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This answer can be found by looking through the sshd log file:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Second question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The answer to this can also be found in the sshd log file by looking for the first instances of `accepted password` and `starting session`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Third question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I was puzzled by this one for a minute because nothing was defining what "unusual" means. But after looking carefully at the sshd log, I noticed a pattern in the login hours. Of course, it made sense, most of them were between normal business working hours, except one which was at 4AM:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I initially missed it because I used to work OnCall as a systems admin so weird hours for login wasn't that weird to me. Moving on.

Fourth question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)  
This can be found in the screenshot for the third question.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Fifth question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)  
Now we need to move our attention to the bash history. Since we already know the time when the intruder first logged in, we can easily tell the answer is "whoami".. plus, it's a classic ;)  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Last question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can find the answer within the same log file:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{B3sT_0f_luck_1n_th3_Fr4y!!}`
