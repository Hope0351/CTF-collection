# Who is Real?

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
When we access the website we see two faces and we have to decide which one is real:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

If we intercept the request with Burpsuite though, we can see it's setting up a Flask cookie.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Using `flask-unsign` which you can install with `pip install flask-unsign` we can see that it reveals the correct answer:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We just need to hover our mouse over the images and see which one has the specified GUID and then click on it. We can repeat this until we get the streak that we need:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Once we hit the streak of 5/5 we get our flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This was a nice and easy challenge. What would've made it better would've been a longer streak to encourage scripting these steps.

flag{10c0e4ed5fcc3259a1b0229264961590} 

