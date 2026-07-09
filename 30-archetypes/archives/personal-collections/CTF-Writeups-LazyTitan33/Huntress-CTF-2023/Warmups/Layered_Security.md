# Layered Security

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
As usual, we start by running the file command on the provided file and we see it's a GIMP file:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I searched online for ways to open this without installing GIMP:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The first result in DuckDuckGo was very helpful. I don't recommend searching for these kinds of tools using Google as you get a lot of ads and shady websites.
https://fixthephoto.com/online-gimp-editor.html

Uploading the file in this tool, we can see a bunch of pictures in various layers, thus the name of the challenge. Even in the thumbnail, you can see that Layer #3 isn't just a picture:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In fact, if we click on the small eye icon for the top pictures to hide them, we get to this layer and get the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{9a64bc4a390cb0ce31452820ee562c3f}
