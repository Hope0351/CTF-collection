# safe-password

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

This one gives us a leaked.txt file containing 150 passwords:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I couldn't think of an easier way so I manually started looking up passwords from this list in the [Have I Been Pwned](https://haveibeenpwned.com/Passwords) password database. I started with the lower half which seems to contain easier to write passwords:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

As per the challenge description, we are looking for a password that has been leaked at least 80 times before. We find that to be `Bubblegum123!`:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we have our flag: `CTF{fdc852bc63a266c8c38db64bef90d62d53ddeef00aa85df7b941ac780b3d75d8}`
