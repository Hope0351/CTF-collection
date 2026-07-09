# Backdoored Splunk II



Download: [Splunk_TA_windows.zip](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/Huntress-CTF-2024/challenge-files/Splunk_TA_windows.zip)

## My Solution

This is very similar with the [Backdoored Splunk](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33) challenge from last year. This time if we find something suspicious in the `dns-health.ps1` file:  



We see a bunch of bytes being joined together and then passed to IEX. I changed that to pass it to echo instead and reveal a base64 blob:  



When decoding that further, we can see it doing an Invoke-WebRequest with a specific Authorization Basic header and some base64 encoded credentials. We just need to do the same request and replace the port with the one given by the challenge and we get our flag:

```bash
curl -s -u backdoor:this_is_the_http_server_secret http://challenge.ctf.games:32557|awk '{print $2}'|base64 -d|awk '{print $2}'
```



`flag{e15a6c0168ee4de7381f502439014032}`
