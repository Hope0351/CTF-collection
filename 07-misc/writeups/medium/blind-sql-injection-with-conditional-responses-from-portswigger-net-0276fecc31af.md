# :game_die: Blind SQL injection with conditional responses (From PortSwigger) Lab #11

> **Original Source:** [Blind SQL injection with conditional responses (From PortSwigger) Lab #11](https://infosecwriteups.com/blind-sql-injection-with-conditional-responses-from-portswigger-net-0276fecc31af)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## Confirming the Vulnerability.


```
Cookie: TrackingId=tJ1ux5PVRUX2vGYM ' and 1=1 -
```


When using above payload *Welcome back! *message is displayed.


```
Cookie: TrackingId=tJ1ux5PVRUX2vGYM ' and 1=2 --
```


When using above payload *Welcome back!* is not displayed.


The applications is responding differently depending on the True and false query we sent. Now we can use this response to take out the password from users table. Before that

## Checking if users table exist or not.


```
Cookie: TrackingId=tJ1ux5PVRUX2vGYM ' and (select 'x' from users ) = 'x' --
```


This payload checks if the users table exist or not. Since *Welcome back!* message is displayed , we can confirm users table exist.

## Checking if administrator user exist in users table.


```
Cookie: TrackingId=tJ1ux5PVRUX2vGYM ' and (select username from
users where username = 'administrator') = 'administrator' --
```


This payload return True if user *administrator *exist in users table and return false if *administrator *user does not exit in users table. Since the administrator user exist, query return true and hence *Welcome back!* message is displayed.


Since we know the administrator user exist in the table. We can procced to finding the length of password so that it will be easier to brute force the password later.

## Finding the length of password.


```
Cookie: TrackingId=tJ1ux5PVRUX2vGYM ' and (select length(password)
from users where username = 'administrator')>0 --
```


In above query `(select length(password)
from users where username = ‘administrator’)>0` part return True since password is greater than Zero . And hence *Welcome Back!* message is displayed.


Application will not return *Welcome Back!* message if the query returns false. For example: if the password length 8 and the query is
`(select length(password) from users where username = ‘administrator’)>10` then it would return False and *Welcome back!* message will not be displayed.


## Get dollarboysushil’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


It is tiring to manually change the length digit and view change in application response. So we will be using Intruder feature from BurpSuite.

>

Ctrl + I to send the request to intruder.


- Click on *Clear* Button

- Select the `0`

- Click on *Add*


- Make sure Attack Type is `Sniper`


On `Payloads` section


- Select payload type

- Change From , To & Steps options

- And Start Attack


Here we can see difference in length. In response of length 5437 we can see the *Welcome back! *message.


Here we cannot see difference in length. In response of length 5437 we can see the *Welcome back! *message.


We can clearly see the response length for payload 0–19 is 5473 which contains the *welcome back!* message.
But Response length for payload greater than 20 is 5412 doesnot contains the *welcome back!* message.
Therefore length of password = 20

>

Note: Response length may vary in your case. Focus on the response message for respective response length.


Now its time to get the password.

## Finding Password


In intruder edit the payload as


```
Cookie: TrackingId=tJ1ux5PVRUX2vGYM ' and (select substring(password ,1,1)
from users where username = 'administrator')= 'a' --
```


- Substring in sql works as substring(*string*, *start*, *length*)

- Lets say password is `dollarboysushil` the substring(password,1,1) gives `d`

- `(select substring(password ,1,1) from users where username = ‘administrator’)` will return first character of string , if the character = ‘a’ then the query will be true. thus the response will consist *Welcome back! *message.


In Intruder:


Select starting field of substring function , comparing value and click on add.


Select Attack Type as : Cluster Bomb


In Payloads section
- Payload set 1 (this is the payload for the start field of substring field)
- Payload type : Numbers
- Payload setting , From : 0
- Payload setting , From : 20 (which is the length of password)
- Payload setting , Steps : 1


Now edit the payload Set 2 (this is the payload for the characters we are comparing)
- Select payload type : Brute forcer
- Select min length: 1
- Select Max length: 1

>

Then start the attack


### RESULT


There are two response length. One response contains `Welcome back!` response. In my case 5473 contains the welcome back message. Sort the length and rearrange the password.
In my case Password = `baw6dlog9hpv7tfxus9l`

### Login with the username and password to complete the lab.


My social medial handle
Instagram[dollarboysushil](https://instagram.com/dollarboysushil)
Twitter (X)[dollarboysushil](https://twitter.com/dollarboysushil)
Youtube[dollarboysushil](https://youtube.com/dollarboysushil)


This writeup is purely inspired/helped by . Check her youtube video [here](https://www.youtube.com/watch?v=LBG_n9fr8sM&t=713s).

---

*Originally published on [Medium](https://infosecwriteups.com/blind-sql-injection-with-conditional-responses-from-portswigger-net-0276fecc31af). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
