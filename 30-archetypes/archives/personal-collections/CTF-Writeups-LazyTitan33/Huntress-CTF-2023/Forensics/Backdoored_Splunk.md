# Backdoored Splunk

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
There were a lot of files in this archive but one particular one drew my attention, `nt6-health.ps1`. It didn't take me long to find because I was thinking like an attacker and prioritized looking at the scripts first.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In this script, we can see an Invoke-WebRequest is made with a specific value for a Basic authorization....  We can replicate that using curl:  

```bash
curl -s -H 'Authorization: Basic YmFja2Rvb3I6dXNlX3RoaXNfdG9fYXV0aGVudGljYXRlX3dpdGhfdGhlX2RlcGxveWVkX2h0dHBfc2VydmVyCg==' http://chal.ctf.games:31029
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can go one step further and carve out the flag directly:  

```bash
curl -s -H 'Authorization: Basic YmFja2Rvb3I6dXNlX3RoaXNfdG9fYXV0aGVudGljYXRlX3dpdGhfdGhlX2RlcGxveWVkX2h0dHBfc2VydmVyCg==' http://chal.ctf.games:32337|awk '{print $2}'|base64 -d
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{60bb3bfaf703e0fa36730ab70e115bd7}
