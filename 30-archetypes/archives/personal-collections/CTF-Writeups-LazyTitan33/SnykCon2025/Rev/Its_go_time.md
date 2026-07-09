# It's Go Time


Attachment: [its-go-time](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

When running this app, it's asking for a 16 byte key:  



When giving it 16 bytes, it shows error "Invalid Key!":  



I spent a long time looking through this app in IDA and Ghidra. I really have a difficult time dealing with GO binaries. After carefully following the flow, I had finally found the JNZ (Jump not equals) conditional jump to the "Invalid key!" error:  



In Ghidra, I went to that address in the binary and patch it by changing the JNZ to JZ (Jump if equals).  The patch works just like I showed in [Rock Paper Psychic](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33) it's just that here I'm changing a JNZ to a JZ instead of changing the function where a JMP would be.



Now the binary will jump in the other direction and give me the flag:  



flag{78b229bed60e12514c94e85126b43ec4}
