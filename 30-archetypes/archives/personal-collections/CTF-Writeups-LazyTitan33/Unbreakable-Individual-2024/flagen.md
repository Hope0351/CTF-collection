# flagen

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

For this challenge, we can use the online emulator [appetize.io](https://appetize.io/) to do some dynamic analysis. I've made an account using a temp email and can now turn on Network Logs:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After adding the generated IP and Port, I hit connect:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Then I make a GET request and can see it in the network logs:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

To make it easier for myself to enumerate this, I've replicated it in Burp Suite, making sure to add the endpoint and the `X-API-KEY` header which seems to be used for authentication:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Considering this is an API, I've decided to fuzz it with an appropriate wordlist:  

```bash
ffuf -c -t 100 -u http://34.107.126.69:31241/FUZZ -w /usr/share/seclists/Discovery/Web-Content/api/api-endpoints.txt
```

And I quickly found that the swagger documentation is exposed on the `/swagger` endpoint:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After we access the swagger documentation we find that there is a second endpoint on `/api/v1/getfl`:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We access that endpoint with the `X-API-KEY` header and we get our flag:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`CTF{21fb574397e3c49950511c5f1a9dd413ffc5986a0a15b36878434e21782877f0}`
