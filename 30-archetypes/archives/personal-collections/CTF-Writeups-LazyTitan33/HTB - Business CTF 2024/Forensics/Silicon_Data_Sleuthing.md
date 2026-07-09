### Challenge Description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

The challenge provides a .bin file that linux can't identify, it just says it's data:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

But the challenge description does say it's a firmware dump so we are not starting blindly. A good resource as always is [Hacktricks](https://book.hacktricks.xyz/hardware-physical-access/firmware-analysis#analyzing-firmware).

Running `binwalk` on it, we find the `squashfs` filesystem and its `offset`. 

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can use it to carve out the image from the firmware:  

```bash
dd if=chal_router_dump.bin bs=1 skip=4375240 of=dir.squashfs
```

Or you can just let binwalk do it as well:

```bash
binwalk -ve chal_router_dump.bin
```

Using binwalk is definitely the easier method as it gives you all the content you need and the squashfs filesystem is neatly placed in a folder:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 1: 
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The answer to this one can be found within the squashfs filesystem in `etc/openwrt_release`.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 2:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)  
There are many ways to find this answer, a quick one is using strings and grep:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 3:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Sadly this hash can't be found where you would normally expect it to be, in /etc/shadow in the squashfs filesystem. It is actually in the `jffs2` filesystem that was also extracted by binwalk earlier and a folder already created with the content we need:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In the `upper` directory we can find an archive:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

When decompressed we can see it also has shadow file:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This is where we find our answer:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 4+5:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The answers can be found in the same folder where we decompressed the archive, in the `etc/config/network` file.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 6+7:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Both answers can be found in `etc/config/wireless`.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

#### Question 8:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The last information can be found in `etc/config/firewall`:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{Y0u'v3_m4st3r3d_0p3nWRT_d4t4_3xtr4ct10n!!_af640eb12f2108e34ea9f6cc49a018fb}`


