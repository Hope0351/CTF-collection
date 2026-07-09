# Baking

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
Accessing the web page we see we can bake some cookies. The Magic Cookies however seem to take 7200 minutes which is forever... not someting we have time for:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We also see that a cookie is set when baking the cookie:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
echo 'eyJyZWNpcGUiOiAiTWFnaWMgQ29va2llcyIsICJ0aW1lIjogIjEwLzE0LzIwMjMsIDE1OjUzOjUwIn0='|base64 -d
```
Decoding this cookie, we can see it's a JSON object which includes the time for when the cookie would be done.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
echo -n '{"recipe": "Magic Cookies", "time": "10/14/2022, 15:53:50"}'|base64 -w0
```

We changed the year to put it in the past:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Now that we have a new cookie, we replace it in the browser and refresh to get the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{c36fb6ebdbc2c44e6198bf4154d94ed4} 
