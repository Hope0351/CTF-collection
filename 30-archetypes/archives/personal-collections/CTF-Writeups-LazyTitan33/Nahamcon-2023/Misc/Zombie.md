# Zombie

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This challenge allows us to SSH into a box and we see a script that we can read to better understand what is going on:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It seems the user runs tail on the flag and then deletes it. However, the process is still running in the background:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Which means we should be able to read its file descriptor by going to `/proc/<pid>/fd`.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And indeed, we get the flag:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{6387e800943b0b468c2622ff858bf744}
