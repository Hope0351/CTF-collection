# MFAtigue

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
The provided zip file contains a SYSTEM file and ntds.dit which we can extract hashes from using `secretsdump.py`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We feed all those NTLM hashes to hashcat and we have one cracked:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It is the hash for user Jillian Dotson:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

When we try to log in:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We get this error message:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So we need to make sure we use the correct domain as it is indicating to us and then we get logged in:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Or so we think, we are required to approve our sign in request.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After we click on Send Push Notification, we see a little notification in the right corner that says it was sent:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Intercepting with BurpSuite we can see a POST request was made to the /mfa endpoint and a Flask cookie was assigned:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Using `flask-unsign` we can see it is mentioning a counter:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

If we push the button to send a push notification suficient times, 30 to be exact, it will assign this cookie:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we get our flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{9b896a677de35d7dfa715a05c25ef89e}
