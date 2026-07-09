# wifibasic

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

Looking through the provided wireshark capture, we can find an [EAPOL handshake](https://networklessons.com/cisco/ccnp-encor-350-401/wpa-and-wpa2-4-way-handshake)

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can use [aircrack-ng](https://www.aircrack-ng.org/) to try and crack this to get the WiFi password. We try each destination BSSID until we find one where the full handshake was capture and we can crack the password for.

```bash
aircrack-ng -w /usr/share/wordlists/rockyou.txt -b '02:00:00:00:04:00' wifibasic.cap
```

We've successfully found the password so we have the values they are looking for. We've found the BSSID and the PSK:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The `ESSID` was a bit confusing but it's just an interchangeable term for `SSID`, meaning, the name of the WiFi network. We can filter base don the BSSID/MAC address and find it:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```python3
from hashlib import sha256

BSSID = "02:00:00:00:04:00"
ESSID = "TargetHiddenSSID"
PSK = "tinkerbell"

def calculate_sha256(bssid, essid, psk):
    input_string = bssid + essid + psk
    hash_result = sha256(input_string.encode()).hexdigest()
    return hash_result
    
sha256_sum = calculate_sha256(BSSID, ESSID, PSK)
print('CTF{'+sha256_sum+'}')
```
Now that we have the values of all the variables, we can complete the script the organizers provided and get the flag:  
`CTF{73841584e4c011c940e91c76bf1c12a7a4850e4b3df0a27ba8a35388c316d468}`
