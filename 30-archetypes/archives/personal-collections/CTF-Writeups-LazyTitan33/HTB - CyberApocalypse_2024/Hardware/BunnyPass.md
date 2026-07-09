# BunnyPass

## Solution 

As the description mentions, we are given access to a RabbitMQ instance with default credentials:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

As it can easily be found on the internet, the default creds for RabbitMQ are `guest:guest` and `admin:admin`. Both work in this instance but give the same level of access.

This takes a bit of enumeration, figuring out the interface if you are not familiar with it, and eventually we get the flag in one of the messages from the Queues.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

From the `factory_idle` queue, you can read the 6th message and get the flag:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{th3_hunt3d_b3c0m3s_th3_hunt3r}`
