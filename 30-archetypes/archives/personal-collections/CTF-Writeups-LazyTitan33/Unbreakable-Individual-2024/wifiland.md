# wifiland

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

The wireshark capture contains an [EAPOL handshake](https://networklessons.com/cisco/ccnp-encor-350-401/wpa-and-wpa2-4-way-handshake) so we can try to crack the password using [aircrack-ng](https://www.aircrack-ng.org/):  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
aircrack-ng -w /usr/share/wordlists/rockyou.txt -b '02:00:00:00:05:00' wifiland.cap
```

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can now use this password to decrypt the traffic by going in Wireshark in `Edit` -> `Preferences` -> `Protocols` -> `IEEE - 802.11` -> `Edit` on Decryption Keys and set the password for `wpa-pwd`:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Scrolling through the decrypted traffic we can eventually see an ARP broadcast request giving us the Client and Target IPs.  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we can now generate the flag:  

```python3
from hashlib import sha256

ip_client = "10.0.3.19"
ip_target = "93.184.216.34"

def calculate_sha256(ip_client, ip_target):

    input_string = ip_client + ip_target
    
    hash_result = sha256(input_string.encode()).hexdigest()
    
    return hash_result

sha256_sum = calculate_sha256(ip_client, ip_target)

print('CTF{'+sha256_sum+'}')
```

`CTF{b67842d03eadce036c5506f2b7b7bd25aaab4d1f0ec4b4f490f0cb19ccd45c70}`
