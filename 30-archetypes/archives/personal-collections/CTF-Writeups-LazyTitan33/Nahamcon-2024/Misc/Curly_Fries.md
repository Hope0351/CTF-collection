## Curly Fries

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

After we SSH into the box, we find that the user is allowed to run a very specific curl command as user `fry`:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, while enumerating we also find that he is allowed to enter the `fry` user home directory and read the `.bash_history` in which we find a password:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```text
iLoveCurlyFriesYumYumInMyTumTum
```

We can use this to switch to `fry` and can see that he also is allowed to run curl but as root and with a wildcard at the end. This is the important part:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

Abusing the wildcard we can read files as root:  

```bash
sudo curl 127.0.0.1:8000/health-check file:///etc/shadow
```
We don't even need a valid localhost on port 8000 to curl to. While trying to crack the root hash in the background. We can save this shadow file to a file called `health-check`. However, we've modified it so that the root hash is known to us. I simply copied fry's hash over to root so we can reuse his password.

In a different shell, we use python to host the file on port 8000 and then use the curl command below to grab it and overwrite the /etc/shadow file:  

```bash
sudo curl 127.0.0.1:8000/health-check -o /etc/shadow
```

Now we can switch to root and get the flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`flag{36fa4a94c4c3806b19c496a31859eff0}`
