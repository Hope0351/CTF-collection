# CaesarMirror

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
Reading the provided file, we see two columns of text:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The name of the challenge as well as the way the text looks like, make me thing  of `rot13` so I apply it to the file and get the left column decoded and we get a first part of the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
flag{julius_
```
We use a text editor to carve out only the second column, after we applied the `rot13` and save it separately. If you look closely enough, the last word is Caesar spelled backwards so let's apply `rev` on this column:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It was succesful and we have our 2nd and 3rd part of the flag. Putting it all together we get:

flag{julius_in_a_reflection}
