# Zimmer down



Download: [NTUSER.DAT](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/Huntress-CTF-2024/challenge-files/NTUSER.DAT)

## My Solution

I have parsed NTUSER.dat files before but also a good hint from John when announcing the challenges leads us to use the kali builtin tool called [regripper](https://www.kali.org/tools/regripper/):  




```bash
regripper -r NTUSER.DAT -a
```

We can see a lot of data:  



But somewhere further down, this string drew my attention as it looked like it was a Base64 string.  



But not quite, the b62 at the end is another clue that this is actually a Base62 encoded string which we can decode using [cyberchef](https://gchq.github.io/CyberChef/#recipe=From_Base62('0-9A-Za-z')&input=VkpHU3VFUmdDb1ZobDZtSmcxeDg3ZmFGT1BJcWFjSTNFYnk0b1A1TXlCWUtReTVwYURG) and get the flag:  



`flag{4b676ccc1070be66b1a15dB601c8d500}`
