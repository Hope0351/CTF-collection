# 1200 Transmissions



Download: [transmissions.wav](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/Huntress-CTF-2024/challenge-files/transmissions.wav)

## My Solution

A quick google search for similar challenges yealds a promising [result](https://ctftime.org/writeup/23189):  



So we install and run the same tool:  

```bash
sudo apt install minimodem
minimodem -r -f transmissions.wav 1200
```

And we get the flag:  



`flag{f28d133e7174c412c1e39b4a84158fa3}`
