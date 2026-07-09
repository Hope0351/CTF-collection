# Fetch

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

For this challenge we get a file I haven't seen before. A Windows imaging image:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After some research with Google, we find that there are tools we can use to parse these in Linux and in Windows. Initially I install `wimtools`.

```bash
sudo apt-get install wimtools
```
After that I mounted it to a folder and found a bunch of prefetch files:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I read some articles trying to find some easy ways of parsing the information in these files as there were quite a few, a real "needle in a haystack" situation.

https://www.hackingarticles.in/forensic-investigation-prefetch-file/

Eventually I found this Windows tool as it was easier for me to have a GUI in this instance:
https://www.nirsoft.net/utils/win_prefetch_view.html

My aim was to look into the prefetch files of stuff that had user input like, notepad, cmd, powershell and eventually I found wordpad:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I used cyberchef to quickly convert it to lowercase:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{97f33c9783c21df85d79d613b0b258bd}
