# Glasses

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

When checking the source code of this web application, I noticed a large blob in the HTTP response in BurpSuite:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Scrolling all the way down, we can see it's actually javascript. I tried multiple ways to run it, in the browser console, beautifying it and running it in online parsers but the output was too large and I couldn't get all of it.

So I resorted to saving it locally in a file and changing it a bit to print the code:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Then I used node to run the javascript and redirect the output to a file. Again, there was a lot of content (garbage) but doing a simple CTRL+F helps us find the flag:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{8084e4530cf649814456f2a291eb81e9}
