# Query Code

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
After we download the file, we can find out it is actually a PNG:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We rename the file to give it the .png extension and open it:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Now that we know this is a QR Code, we can use `zbarimg` to scan it and print out the text in it:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{3434cf5dc6a865657ea1ec1cb675ce3b}
