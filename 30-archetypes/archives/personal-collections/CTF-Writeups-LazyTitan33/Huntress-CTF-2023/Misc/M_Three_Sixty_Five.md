# M Three Sixty Five

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
We first follow the instructions in the description and SSH into the box:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Before anything, we do a little recon because we are curios. We list the running processes. In the screenshot below, you can see that I first redirected the output to a file and then read the file. This was easier for me to be able to read the entire content that was flowing outside the screen since we didn't have access to the less command which I would normally use.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We found some credentials so we put that aside for now:

```
user: HackMe@4rhdc6.onmicrosoft.com
pass: HackHuntWin!
```
For the rest of the enumeration I used the AADInternals documentation to figure out what commands I can run:
https://aadinternals.com/aadinternals/#read-aadintconfiguration

#### 1st Flag:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
Get-AADIntTenantDetails |grep street
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{dd7bf230fde8d4836917806aff6a6b27}

#### 2nd Flag: 
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
Get-AADIntConditionalAccessPolicies |grep flag
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{d02fd5f79caa273ea535a526562fd5f7}

#### 3rd Flag:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
Get-AADIntTeamsMessages | Format-Table id,content,deletiontime,*type*,DisplayName
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{f17cf5c1e2e94ddb62b98af0fbbd46e1}

#### 4th Flag:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
Get-AAIntUsers |grep flag
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{1e674f0dd1434f2bb3fe5d645b0f9cc3}

