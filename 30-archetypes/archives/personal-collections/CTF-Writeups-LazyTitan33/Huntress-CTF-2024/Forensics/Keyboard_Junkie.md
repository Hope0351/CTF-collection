# Keyboard Junkie



Download: [keyboard_junkie](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/Huntress-CTF-2024/challenge-files/keyboard_junkie)


## My Solution

When opening the provided file in Wireshark, I could see USB traffic. I've done these kinds of challenges in the past but couldn't remember the tool so I googled it:  



Using this tool allows us to decode keyboard traffic, but first we need to extract the traffic:  

```bash
tshark -r keyboard_junkie -Y 'usb.capdata && usb.data_len == 8' -T fields -e usb.capdata  | sed 's/../:&/g2' >usbPcapData
```

Here we are using tshark to extract just the USB packets that have a length of 8 and are placing : every two characters to get a format recognized by the tool.

We then use the ctf-usb-keyboard-parser and get the flag:  



Another easier method would be to use this other parser which allows us to pass the wireshark capture directly and it will grab the traffic on its own:  



`flag{f7733e0093b7d281dd0a30fcf34a9634}`
