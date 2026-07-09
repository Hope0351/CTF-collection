# Rock, Paper, Psychic

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
For this challenge, we get a PE executable. When we first run it, regardless of what we choose, we always lose:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The name of the program is interesting. It seems to be a hint for us to patch the program. I've opened it in Ghidra to learn more about what it does and how. At first, we see a function called `determineWinner`   

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We then we also find a function called `printFlag`   

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The `determineWinner` function does a few comparisons and if statements determining winner depending on whether the user chooses rock, paper or scissors. I spent some time trying to mess with those and patch the binary to spit out the flag but I didn't find an easy and elegant solution. Then I got an idea. At the end of all of these, the function returns 0:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

What if we patch that and instead of returning 0, it simply jumps to the `printFlag` function?! So regardless of the if statements, regardless of what the outcome of the `determineWinner` function will be, it will jump where we want to go and print the flag.

We right click on the RET and click on `Patch Instruction`:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We replace the RET with `JMP` and tell it where to jump:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Hit enter and now the RET has been replaced with our JMP:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We highlight this part and click on the icon in Ghidra to Display the Script Manager.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We find our SavePatch.py script and run it. Because we've highlighted our patched instruction, it automatically determines the size and location it needs to patch.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Now we run the binary again and choose anything we want. It beats us but also gives us the flag which we are fine with because we ultimately win:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{35bed450ed9ac9fcb3f5f8d547873be9}

