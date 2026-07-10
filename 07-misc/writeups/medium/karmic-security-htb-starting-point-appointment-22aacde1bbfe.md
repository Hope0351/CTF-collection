# :game_die: HTB Starting Point: Appointment. HTB Starting Point: Appointment

---

# HTB Starting Point: Appointment

Hello and welcome to Starting Point Tier 1! We are officially out of tier zero and are now actually working towards a little bit of actual exploitation! Todays box, Appointment, is going to be covering some of the fundamentals of SQL injection. SQL stands for structured query language and we briefly touched on it during the Mongod box. SQL in it’s normal use is a query language (obviously) that allows us to interact with databases. The thing is these databases are frequently used in conjunction with web applications and if certain input fields on a web page aren’t sanitized properly this can lead to SQL injection (SQLi). This is the vulnerability we will be getting familiar with today. So without further adieu let’s go ahead and spin up our attack boxes of choice as well as the target.

## Task 1 and 2

Well luckily in my little intro monologue I covered both of these. Again, SQL stands for Structured Query Language and the most common SQL vulnerability is SQL injection. Moving right along…

## Task 3

Well let’s find out. Let’s go to OWASP themselves and find out. So if we navigate to [OWASPs top ten](https://owasp.org/Top10/) for 2021 we see this here:

A03:2021-Injection should be our answer and indeed it is.

## Task 4

Alrighty, time to get hands on keyboard and do a little recon. Let’s fire up an nmap scan and get going.

So here I run `sudo nmap 10.129.11.195 -sV -p 80` instead of a full port scan because for the purposes of this box our interest is solely on port 80 and I just did `-p 80` to save some time. We can see though the version of the Apache web server running on our target and that's going to be our answer.

## Task 5

The standard port for HTTPS is 443. In case you aren’t aware HTTPS is the encrypted version of HTTP.

## Get KarmicDragoon92’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

## Task 6 and 7

Folders in the context of web apps are referred to as directories or just directory, same as on Linux. And as you probably already know HTTP Code 404 is the Not Found response. Also, just so we’re all tracking, if you’re reading this on my website you see my domain name {karmicsecurity.com) and after that you should see something like /post/post.html or something like that. /post is the web directory and then the file in that directory post.html which is rendered by your web browser. Anyhow, time to keep moving on.

## Task 8

Alright, back to our shell let’s look at some of the functionality of gobuster.

We see here the `dir` option is what tells gobuster we want to perform directory enumeration rather than sub domain enumeration.

## Task 9

So in SQL syntax, the # character is used to indicate a comment and comment out the rest of the line. There are a lot of characters in SQL that have special values, another one being ‘ a single quote, which will be very important in a moment.

## Task 10 and the Root Flag

We are now going to perform a SQL injection attack to log in as admin without supplying a password. Okay, so open up a web browser and enter `http://[target_IP]`. You should be brought to a web page that looks like this:

In the Username field, we’ll enter admin and then in the password field we are actually going to enter a SQL statement. Specifically:`'or'1'='1`. When this login request is passed to the database, it will see the username as admin and then something interesting. When it goes to compare the password to what it has in the database, the SQL database will evaluate the SQL statement we provided. OR 1=1, which equals True. So, the database compares True to the password value which is already set to True via the expression we provided. So if we enter that SQL statement in the password field we should see...

## Conclusion

That by no means was the best explanation of SQL injections that’s out there, there are multiple really good resources for learning more about SQL injection specifically or web application pentesting in general. Between obviously HTB Academy, TryHackMe and also [Port Swigger Academy](https://portswigger.net/web-security) there’s a ton of good resources where you can learn more. But for now, that’s all I’ve got, thank you for tuning in and see you in the next one!

---
