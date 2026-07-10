# :globe_with_meridians: Broken Brute Force Protection How To Bypass Rate Limiting In A Single Request Au

> **Original Source:** [Broken Brute Force Protection How To Bypass Rate Limiting In A Single Request Au](https://infosecwriteups.com/broken-brute-force-protection-how-to-bypass-rate-limiting-in-a-single-request-authentication-a4a761fc0b5a)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## Steps to Reproduce & Proof of Concept (POC)


1. Access the PortSwigger Authentication Vulnerability lab


2. Enter `carlos` as the username, since the password is unknown, enter a random value


3. In Burp Suite, go to HTTP History, right-click on the login request and send it to Repeater


4. Prepare for Brute-Force Attack Using Burp Intruder


5. Right-click on the request and send it to Intruder


6. Identify the password parameter and replace its value with `$$`


7. Perform Password Spraying with Burp Intruder


## Get Bash Overflow’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


8. Paste the candidate passwords provided in the lab. Click Start Attack and observe the responses


9. Notice that the server is implementing rate limiting to prevent traditional brute-force attacks


10. Instead of using Burp Intruder, perform password spraying using the following Python script:


```
import sys

def read_passwords(file_path):
try:
with open(file_path, 'r') as file:
passwords = [line.strip() for line in file.readlines() if line.strip()]
return passwords
except FileNotFoundError:
print(f"File {file_path} not found.")
sys.exit(1)

def main():
if len(sys.argv) != 2:
print("Usage: python3 gen_pass.py <passwordlists>")
sys.exit(1)

file_path = sys.argv[1]
passwords = read_passwords(file_path)

print('[')
for i, pwd in enumerate(passwords):
if i == len(passwords) - 1:
print(f' "{pwd}"')
else:
print(f' "{pwd}",')
print(']')

if __name__ == "__main__":
main()
```


11. Save the script as `gen_pass.py`


12. Save the password list as `passlist.txt`


13. Paste the generated passwords into Burp Repeater. Click Send and observe the server response


14. If the server responds with HTTP 302, it indicates a successful bypass of rate limiting


15. However, the exact password used for login remains unknown


16. Copy the session cookie from the successful request


17. Use the Cookie Editor extension for Firefox or Chrome


18. Modify the session cookie value and save the changes


19. Navigate to `https://<your-lab-id>.web-security-academy.net/my-account`


20. If successful, you have solved the lab


## Impact


- Compromise sensitive user data, such as personal information and account settings

- Bypass brute-force protection by exploiting a flaw in how login attempts are counted

## Mitigation


- Ensuring that brute-force protection applies even when multiple credentials are sent in a single request

- Adding an extra layer of security to prevent unauthorized access

---

*Originally published on [Medium](https://infosecwriteups.com/broken-brute-force-protection-how-to-bypass-rate-limiting-in-a-single-request-authentication-a4a761fc0b5a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
