### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This is the first challenge in the Web category and we get the source code.

The first page greets us with a SF looking picture and subject:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We even have a login page on /login:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Going to the source code, from the `database.js` file we can see that the flag is read into the Database:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

From the `entrypoint.sh` file we know it is using a NoSQL database called CouchDB:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Furthermore, the login process doesn't seem to be all that safe either as it is not sanitizing or checking user input.
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In this case, we can intercept the login process using Burpsuite or your proxy of choice and modify it with a standard NoSQL injection, setting the password to `$ne` (not equal) "a" so the statement will be true and we get logged in.
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After we do that, we will get redirected to the /dashboard page where we can see the content of the database:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

That means that somewhere here, we should also see the flag. It's going to be on a random page but if you are like me and are intercepting all pages on Web challenges, then you should see it in the response and can look for HTB:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

HTB{c0rrupt3d_c0uch_b4ll0t}

