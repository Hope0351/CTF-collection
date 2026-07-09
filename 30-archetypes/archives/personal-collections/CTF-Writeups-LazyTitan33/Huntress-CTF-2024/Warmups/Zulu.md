# Zulu



Download: [zulu](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/Huntress-CTF-2024/challenge-files/zulu)

## My Solution

The provided file seems to be a `compress'd data 16 bits`



A quick google search indicates that this should be a `.z` compressed file:  



Within the stackoverflow post, we can see how to decompress such files as well:  



So we rename it accordingly, use `uncompress` command to decompress it and get our flag:  

```bash
mv zulu zulu.z
uncompress zulu.z
cat zulu
```

`flag{74235a9216ee609538022e6689b4de5c}`
