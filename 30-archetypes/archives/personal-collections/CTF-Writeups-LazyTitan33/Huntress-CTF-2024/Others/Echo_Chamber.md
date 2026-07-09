# Echo Chamber



Download: [echo_chamber.pcap](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/Huntress-CTF-2024/challenge-files/echo_chamber.pcap)

## My Solution

The provided pcap file contains ICMP traffic:  



Using tshark I exfiltrated only the requests (type 8):  

```bash
tshark -r echo_chamber.pcap -Y "icmp.type == 8" -T fields -e data
```

And saw repeating values:  



So I decided to take just the first 2 characters which look like hex and decode them:  

```bash
tshark -r echo_chamber.pcap -Y "icmp.type == 8" -T fields -e data 2>/dev/null|sed 's/^\(.\{2\}\).*/\1/'|xxd -r -p
```
The result was a PNG file based on the header:  



And we have our flag:  



`flag{6b38aa917a754d8bf384dc73fde633ad}`
