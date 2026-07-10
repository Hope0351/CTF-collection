# :game_die: Lacerating Through Sql Injections 806F62Cc2Fe1

---

### A simple SQL Injection

An SQL injection attack can be used to obtain admin privileges to wing the attacker to quickly access sensitive data. However, this type of attack relies on the website conditions and how user ID and other admin-related content is stored. Despite its simplicity, this type of attack can lead to more complex security breaches.

Generally, most operating systems and secure websites, use hashes to store passwords, to prevent attacks like SQL injections. In this case, websites store passwords beside their usernames like an Excel sheet, and write code to make sure that both username AND password are right, then only will the user be able to enter the site. The code may look like this:

```
SELECT * FROM users WHERE username ='admin' AND password='password123'
```

In the code shown above, the site only lets us in, if both the username and password match the ones given in the code. (Generally, there will be a huge list from which the code scans through to identify if the password and username match).

A small loophole is when through the username and password bar, we can access and add on to this code. For example, in this case, we can either comment out the rest of the code after the username mentioned or we can add a bit of code to overrun the existing code like so:

```
SELECT * FROM users WHERE username ='admin' OR '1'='1' AND password='password123'
```

In the username bar, it would look like:

username: *admin’ OR ‘1’=’1*OR

```
SELECT * FROM users WHERE username ='admin' --AND password='password123'
```

In this case, the entire code after the username is ignored. The username would be typed as:

username: *admin’ — —*

---
