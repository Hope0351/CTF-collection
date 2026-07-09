# Wordle Bash

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

As the challenge description informs us, we connect with SSH to the box and then check to see what permissions we have. It seems we can run a script as root.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The script is basically Wordle but implemented in bash. We need to enter a date and it has to match with the one the script randomly chooses. Which is impossible so that's not the solution.

After carefully reading the script, I noticed that `date` is also run as root and it's taking user input.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

As we know, `date` is a [GTFObin](https://gtfobins.github.io/gtfobins/date/#sudo) that allows us to read files. At first we need to go through the motions of selecting a date:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, when it asks us if it is correct, we need to say no:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This is where the user input comes in. After we say no, we can enter arbitrary content so we just pass the `-f` argument and the file we want to read. If we try to read the flag, we get this message:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This means we were able to read the flag.txt however it doesn't actually contain the flag. We need to escalate our privileges to get code execution as root. A logical step is to see if there is an RSA private key:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Confirm it:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we get the key:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We clean it up and use it to SSH as root, we find a binary that we can run and it gives us the flag:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{2b9576d1a7a631b8ce12595f80f3aba5}
