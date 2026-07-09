### Challenge Description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

For this challenge, we get a bunch of Windows EventViewer logs in their standard form of `evtx` files. 

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I like converting them to a human readable format as they are easier to strings and grep through.

```bash
sudo apt install python3-evtx
mkdir converted
for file in ./*.evtx;do evtx_dump.py "$file" > converted/"${file%.evtx}.xml";done
```
I started by looking for powershell scripts being run:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

I opened the Windows Powershell Operational file and looked at the content of the `h.ps1` file and my eyes landed on the `SFRC` which is the Base64 encoded HTB string. I've done a lot of challenges on HTB so I recognize it immediately:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We decode it and get the flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{1ntruS10n_d3t3ct3d_!!!}`

