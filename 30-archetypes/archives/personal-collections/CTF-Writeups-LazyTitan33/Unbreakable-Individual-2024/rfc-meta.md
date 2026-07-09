# rfc-meta

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

When accessing the generated web service we just get an OK on a /home page:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After proxying all the traffic through Burp Suite, we can see it is actually doing several redirects until it lands on `/home`:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A closer look in the response and we can see some hex data.

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Instead of manually going through all 15 redirects in order and copy the hex data we can script it to get the flag:  

```python3
import requests

response = requests.get('http://35.234.88.19:31765')

if response.history:
    for resp in response.history:
        hex_flag = resp.reason.replace('MOVED PERMANENTLY','')
        flag = bytes.fromhex(hex_flag).decode().strip()
        print(flag, end='')
else:
    print("No redirects occurred.")
```

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`CTF{5ba73b7f830badc3e9d32e85bcdcc172bc417afbabc92ea7a343bc3b79fd722e4c44c}`

Note: This was a nice and easy challenge relying on attention to detail and not relying strictly on the web browser which, in my opinion, you shouldn't do when web hacking anyway.