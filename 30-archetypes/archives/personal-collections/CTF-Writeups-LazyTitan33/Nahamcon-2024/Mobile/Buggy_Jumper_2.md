## Buggy Jumper 2

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

I used [this](https://appetize.io/) website, made an account with a 10 minute mail and ran the app. It's a cute little game with a bug and two options, to play and shop:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The game is fun but not winnable:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We need way too many points to be able to afford the "drip":  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Looking through the network logs, we can see it making some requests to a specific IP with the Godot User Agent:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

When we lose and get 0 points, it saves a null value and uses an authentication header:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

If we try to buy the drip, it again sends an authenticated request with 0 value:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

Knowing now how the application works, we can replicate it in Burp Suite and send some requests ourselves. We start by telling it how big of a score we got:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Now that we have a sufficient amount of points, we purchase the flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`flag{a31e44ba4df9789ed5491dc43fa22de3}`
