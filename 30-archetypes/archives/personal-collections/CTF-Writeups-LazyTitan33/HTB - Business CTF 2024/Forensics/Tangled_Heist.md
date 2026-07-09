### Challenge Description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

For this challenge we get a wireshark capture that we have to sift through and answer questions. In this situation, the wireshark capture contains LDAP traffic.  

#### Question 1:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Since LDAPS wasn't used, the traffic is in plaintext and we can see a first LDAP bind request on packet 10 by user `copper`:   
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I lost many hours and even opened a ticket to support for this one because for the longest time, I was typing `cooper`. Don't be like me, take plenty of breaks and don't neglect sleep.

#### Question 2:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can use the search for strings in Wireshark for this one and simply search for `Domain Controllers`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 3:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We know the answer for this one from the Distinguished Name.

#### Question 4:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Again, we can use the search function to find Ranger and then have a look at the [badPwdCount](https://learn.microsoft.com/en-us/windows/win32/adschema/a-badpwdcount) value to get the answer.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)
#### Question 5:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Going through the wireshark capture, we can easily see the list of groups. We look for the `searchRequest` packet right before it and then look at the `Filter` value:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 6:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The non-standard groups are at the end of the list of standard groups so we just count them:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 7:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Doing a bit of quick research to refresh our memory, we know that disabled users will show up in LDAP with the `UserAccountControl` attribute set to `514`:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Going through the users, we find that `radiation` is the only user with 514.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 8:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Towards the end, after the attacker did his enumeration, we can see, in packet 669, the modification he made.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 9:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In the same 669 packet, we can also see what the modification was:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 10:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In packet 671 we can see another user which is not following the same naming convention as the other ones so we can safely assume this is the user created for persistence.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In packet 675 we can also see the group this user is in:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)
#### Question 11:
Lastly, but weirdly this was the first step I actually did. I loaded the capture into [NetworkMiner](https://www.netresec.com/?page=NetworkMiner) and saw the asreproasted hash:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Passed it to hashcat and it quickly cracked it:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we have the final answer and our flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{1nf0rm4t10n_g4th3r3d_2ff9f09034376d273b889164b91dbf15}`
