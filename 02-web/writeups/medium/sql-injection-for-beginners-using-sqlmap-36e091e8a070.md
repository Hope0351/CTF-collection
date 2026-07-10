# :globe_with_meridians: Learn How hackers hack Databases (PART 1)

> **Original Source:** [Learn How hackers hack Databases (PART 1)](https://infosecwriteups.com/sql-injection-for-beginners-using-sqlmap-36e091e8a070)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Learn How hackers hack Databases (PART 1)


Hello Learners, so let’s start with my first blog it is just based on a topic you already knew SQL injection before that let me just introduce myself I am Rajneesh K. Arya student of B.Tech CSE specializing in Cybersecurity
so let us start our blog.


SQL is the structure query language that deals with databases, SQL generated some queries at the backend of the server and grep the data from the database using this query. In SQL Injection we have to just interact with the database with our manipulated query, in other words, we have the power to control the query and we got all information we want.


So, Without going deep into the theory part let me just show you how it works. Today we are using some tools that you can download its free open sources.

>

DISCLAIMER: Do not use these techniques to hack anyone try these in your own lab environment.


We are taking this [http://testphp.vulnweb.com/](http://testphp.vulnweb.com/)a sample vulnerable website for SQL injection you can also try this too.


This is our sample website which is having a login page but the thing is we don’t know what its username and password. So, Lets call our tool here which sqlmap.


You can download this from [github](https://github.com/sqlmapproject/sqlmap).


we have two types of request GET and POST the basic difference is that GET request show the parameter content on the URL but POST don’t.


## Get Rajneesh Kumar Arya’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


As you can see I changed the request method to GET and the content of the parameters are clearly visible on the URL.


In sqlmap also we have two methods based on the request method, first of all, we see how to use sqlmap with the POST request method.
Just intercept the request using burpsuite and copy the all requested content.


*burpsuite copied request*


Now, open your favorite text editor and paste that sucker on it and change the uname parameter value with an asterisk (*) and save it with a .txt extension.


Now, open a terminal or command prompt to start with our main step which is using sqlmap. so type the following command and wait for the result.

>

python3 sqlmap.py -r /home/kairaj5456/Desktop/request.txt — dbs


Here, I use -r for the request file and — dbs for enumerating all the databases, run the command and take some coffee or tea because it takes time.


As you can see I got juicy information about this target which is the name of the databases one is *acuart* and other is a default one *information_schema*. To see what is inside the database we need to just use this command.

>

python3 sqlmap.py -r /home/kairaj5456/Desktop/request.txt -D acuart — tables


We use -D for selecting the name of the database and — tables to enumerate all the tables present in that database and we got 8 tables.


I am gonna selecting the users table because I am interested in that, you can choose as per your interest so now we can see how many users are there in this database and hopefully their passwords also.

>

python3 sqlmap.py -r /home/kairaj5456/Desktop/request.txt -D acuart -T users — dump


I use -T to select the Table name and — dump to dump all the data present in that table. It will ask you whether you want to crack those password or not because in databases the password are store in their cipher text form not in the plain text


and at the end we got a CSV file of all data present in that Table. I am gonna open this CSV file because in terminal the data is not properly sorted.


BOOM! we got all information about the user.


This is how sql injection works and in the next blog I’ll share about the GET method also till then keep learning, keep exploring and do hacking.

---

*Originally published on [Medium](https://infosecwriteups.com/sql-injection-for-beginners-using-sqlmap-36e091e8a070). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
