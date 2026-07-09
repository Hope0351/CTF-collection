### Challenge Description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

Pretty good looking Fallout themed website:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We seem to have an interesting endpoint allowing us to update a Firmware.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

When making the POST request we can clearly see it is sending XML data so that screams [XXE](https://book.hacktricks.xyz/pentesting-web/xxe-xee-xml-external-entity) from a mile away:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{b1om3tric_l0cks_4nd_fl1cker1ng_l1ghts_427cf9303c8fd89feaf3582d1f41a8b9}`
