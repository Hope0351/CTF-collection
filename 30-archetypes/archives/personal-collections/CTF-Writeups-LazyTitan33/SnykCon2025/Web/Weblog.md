# Weblog 



Attachment: [challenge.zip](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

I can quickly see a SQL Injection vulnerability in the source code on the `/search` endpoint:  



Using the following syntax, I can get the admin password hash:  

```text
' union select 1,2,3,4, group_concat(username,password) from users#
```



Luckily the hash is crackable and we get the admin password:  



In the source code, I can see that the admin can execute a command, there's an attempt at a filter in the DISALLOWED_CHARS:  



It is, as expected, insuficient to prevent command injection:  



And I have the flag:  



flag{b06fbe98752ab13d0fb8414fb55940f3}
