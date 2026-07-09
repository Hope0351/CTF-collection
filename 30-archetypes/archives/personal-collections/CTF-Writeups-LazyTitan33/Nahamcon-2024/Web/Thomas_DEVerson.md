## Thomas DEVerson
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

At first glance we just get a website with very few options:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Typing anything in the Username box get's us this message:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

On the /status endpoint we get an incredible uptime for the webserver:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The source code seems to be hiding another endpoint:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

If we access it, we get only the first 10 lines of the source code. But it is enough to show us a few valid users and the Flask application secret key used to sign the session cookie:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

If we try to log in using one of the valid users, we still can't log in because they are protected:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

When trying to log in, we also get a session cookie assigned that looks like this:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So let's try to forge a cookie ourselves. As per the source code, part of the secret key is the epoch time from when the server started, which we know based on the /status endpoint. After a while, I learned the hard way that we also need to keep in mind the timezone. 

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

After we access the /status endpoint one more time, we fill out this script to do some quick math:  

```python
from datetime import datetime, timedelta, timezone

# Current time in GMT
c = datetime.now(timezone.utc)

uptime = timedelta(days=82817, hours=2, minutes=29)
uptime_datetime = c - uptime

f = uptime_datetime.strftime("%Y%m%d%H%M")

print(f)
```

With the correct epoch time, we can use flask-unsign to sign our cookie:  

```bash
flask-unsign -s --secret 'THE_REYNOLDS_PAMPHLET-179708250845' -c '{"name":"Jefferson"}'
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

With it set in our browser, we access login and get the flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`flag{f69f2c087b291b9da9c9fe9219ee130f}`
