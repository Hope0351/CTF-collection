# letters2nums


Attachment: [encflag.txt](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/SnykCon2025/attachments/encflag.txt)  [letters2nums.elf](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

I was doing multiple challenge at the same time at this point and I wasn't very interested in the Rev category so I just copy pasted code from the binary after decompiling it in Ghidra and asked chatGPT what it sees:  



It very nicely gave me working code from the first try:  

```python
with open("encflag.txt", "r") as f:
    encoded_numbers = [int(line.strip()) for line in f.readlines()]

decoded_flag = ""
for num in encoded_numbers:
    char1 = (num >> 8) & 0xFF
    char2 = num & 0xFF
    decoded_flag += chr(char1) + chr(char2)

print("Decoded flag:", decoded_flag)
```

flag{3b050f5a716e51c89e9323baf3a7b73b}
