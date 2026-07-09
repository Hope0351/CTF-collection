# Traffic

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
After we unzip all of the files, we get down to some logs:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

At first I used `cat` to read each category of logs: capture*, conn*, ssl*. After that, I read the challenge description more carefully and grepped for the word `sketchy`.

```bash
strings *|grep sketchy
```
We can indeed find a sketchy website being accessed more than once:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Accessing the website ourselves, we can find the flag:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can also run this command directly:
```bash
curl -s -L sketchysite.github.io|grep flag
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)


flag{8626fe7dcd8d412a80d0b3f0e36afd4a}
