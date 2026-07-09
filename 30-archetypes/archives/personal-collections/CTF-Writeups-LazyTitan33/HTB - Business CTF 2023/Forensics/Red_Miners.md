### Challenge description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We get bash script from this challenge:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I didn't look to deep into it, so I don't know what it actually does. My eyes fell directly and some base64 strings in several different parts of the code.

Part 1 on line 761:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
echo cGFydDE9IkhUQnttMW4xbmciCg==|base64 -d
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Part 2 on line 636:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
echo cGFydDI9Il90aDMxcl93NHkiCg==|base64 -d
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Part 3 on line 701:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
echo X3QwX200cnN9Cg==|base64 -d
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

HTB{m1n1ng_th31r_w4y_t0_m4rs}
