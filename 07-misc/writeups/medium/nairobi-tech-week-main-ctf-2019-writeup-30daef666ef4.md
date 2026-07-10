# :game_die: Nairobi Tech Week Main Ctf 2019 Writeup 30Daef666Ef4

---

Well that makes it easy for us, the POST values are being inserted in the SQL query without any sanitization and the username field is being returned to the page as you will see. So using the basic payload in the username and anything in password field:

```
" OR 1=1 #
```

We get:

Since there is no other page after abusing the login page, we have to leak other information from the table and see if we get the flag. Using UNION SELECT will be perfect for this. The source code already tells us the SELECT returns two fields so we don’t need to test for that and also the username is the second field, so we can use that to extract the data.

Payload:

```
" AND 1=1 UNION SELECT 1,concat(id,' : ',username,' : ',password) FROM users #
```

Flag:

It was fun solving this one, we got first blood on it as well :) . I tried it with sqlmap as well and it didn’t work, manual exploitation ftw!

## Forensics

Just git it

The zip contains a txt file and a .git folder as expected from the challenge name.

Since it’s a git repository we can check commit history using

```
git log
```

Only one commit shows up, I guess we have to dig deeper. In *.git/logs/HEAD *we see:

---
