# :game_die: First step to an SQL-Injection

---

# First step to an SQL-Injection

*Photo by [Clint Patterson](https://unsplash.com/@cbpsc1?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

In the following article we will try to go from little or no knowledge of SQL to perform a basic SQL injection. To achieve this we will use the DWVA box, hosted by TryHackMe.

### What is an SQL-Injection?

SQL injection is the act of exploiting unfiltered user input in a web app. The input may contain valid SQL commands and will therefore be executed when parsed to the SQL server, which may result in unwanted changes or exposure of data.

## Some basic SQL and SQL-syntax

As you already know, SQL is used to manipulating databases. Before we jump to exploit it, lets just first create a foundation of basic SQL knowledge.

*Figure 1. The users tablein our db.*

Assume that we have a table of data as displayed in figure 1. This table lives inside some database we have access to. Some SQL enabled servers can contain multiple *databases *inside one application. Lets assume that our users table lives inside a database object named *website*. Which database object that is targeted is often handled by some configuration file, therefore we will just skip how to target a database-object for the moment while we discuss some SQL-syntax.

### Hello World with SQL

*Figure 2. The most basic SQL command.*

Lets assume we have the data displayed in figure 1 and we run the SELECT * FROM users; command displayed in figure 2, what would happen? Lets break it down. A keyword can be distinguished by the purple color(it’s the standard highlighting format in atom for .sql files). The SELECT keyword tells the database that we want to retrieve some data. The * (star) say hey why not bring me every thing you can find. And finally, FROM users specifies what table the data will be taken from. So the command in figure 2 would return exactly what is displayed in figure 1(except for the bold- headings ofcourse).

*Figure 3. Some SQL command to insert a new user into our DB.*

So now we know how to return some data, but what if we would like to add a new user? Well, lets just run the command displayed in figure 3. The INSERT INTO users tells the server to add some new data into the users table. (userid, username, password, email) is just for specifying what columns we are targeting and in what order we want to insert the data.

Can we just jump to a new line like that? Yes, we can. Because the SQL server will interpret it as one command as long as there is not a ; somewhere in between. Since we have the ; in the end of our command, the SQL server will interpret everything inside figure 3 as one command. Finally we have VALUES (“5”, “lion”, “theking”, “simba@example.com”) which is just saying that we would like to input these values and the server will map it accordingly in order to our earlier specification (userid, username, password, email).

*Figure 4. The updated table.*

Here in figure 4 the final table is shown. There is a lot more in the SQL language, but for the sake of simplicity I will leave it up to you to do some more research.

## The injection

For this demonstration lets fire up [tryhackme](http://tryhackme.com) and start the box namned [DVWA](https://tryhackme.com/room/dvwa), it can be installed on a locale machine but it is much easier to do it this way(and it is still free). Hard to find the box? [Just click here](https://tryhackme.com/room/dvwa).

If it is your first time using tryhackme, follow some of their guides to get started and connected to their services. Then just come back when you are ready.

*Figure 5. DVWA login page.*

I assume you have now started the DVWA box and can access the website thru the ip displayed on tryhackme. You should see something as displayed in figure 5. Now just login, for username use *admin *and for password use *password. *Viol*á *you are in! There are a lot of stuff here, but first lets turn down the difficulty to something maintainable. Click DVWA Security in the main-menu. Then change the difficulty in the drop down from impossible to low.

## Get Mcry’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Click SQL-injection in the main-menu. Nice, now lets get your hands dirty. Just try to enter some stuff into the text-field. I found that by writing 1 thru 5 each in its separate query returned some user, see figure 6.

*Figure 6. The result after imputing a 1 and clicking submit.*

But what happens if we input a tick i.e the ‘ symbol? Nice, we got a error messages, see figure 7.

*Figure 7. The error message.*

So what happened? Presumably, the backend server ran some SQL script, most likely something like figure 8. The WHERE keyword is used for filtering the result, so all returned records must have its id set to the ?-symbol.

*Figure 8. Possible SQL script on the backend.*

However, the backend before sending the query to the SQL-server changed out the ?-symbol for the input. The final query would now be something like figure 9.

*Figure 9. The final query.*

As you can see, the SQL server can’t make sense of the three ticks and therefore throws an error.

*Figure 10. URL of DVWA after inputing 123 into the text-field.*

After a bit of tinkering I found that the url contained the submitted query. In figure 10 you can see that after id= and before the following & is the input passed to the query, here I just wrote 123 into the text-field and clicked submit. However, the information passed from the input-field to the URL is URL encoded, which for me generated some minor failures. So to avoid this, lets just write the query directly into the URL hereafter.

### Become malicious

A set of two dashes comments out the rest of the SQL on the same row, see figure 11.

*Figure 11. A command and a comment.*

This we can use to escape the SQL query and insert our own SQL commands. Lets edit the URL to be the same as in figure 12.

*Figure 12. An injected SQL command.*

The UNION keyword is used to concatenate two search results together. table_name is a column in the information_schema.tables tablewhich contains all the names of the tables in the database. So lets assume that the server has some SQL template like figure 8. Then the query sent to the SQL server would be something like figure 13.

*Figure 13. Just replaced the ?-symbol in figure 8 for the command in figure 12.*

The automatic highlighting speaks for itself. As you can see by switching out the ?-symbol for the SQL command which we injected into the URL we now created a new valid SQL command which we can edit. As a result of running this command we get the result displayed in figure 14.

*Figure 14. All the tables inside the database.*

One special table I found was the users table. Lets enumerate it a bit further. Just as there exists table_name inside information_schema.tables there exists a column_name inside information_schema.columns, but also lets filter it to the users table. Lets run the same URL as in figure 15.

*Figure 15.*

Just for reference, figure 16 will be the query which will be sent to the SQL server based on figure 15.

*Figure 16. The SQL query which will be sent to the SQL server based on figure 15.*

The result of figure 15 and 16 we can see in figure 17. Here we can see all the column names which the users table contains. I would say the password column is the most interesting one here.

*Figure 17. All the column names inside the users table.*

So lets grab all the passwords. Run the URL in figure 18.

*Figure 18.*

Now we can see all the users and their accompanying password hash, see figure 19. And here the story ends. We have now reach our goal of retrieving all them passwords hashes. Afters this the hashes needs to be cracked with a tool such as hashcat or john the ripper. But I will not cover that in this post.

*Figure 19. Users and their password hashes.*

## How to disclose a SQL injection

This article covers only the absolute basics of SQL injection, so I do not really expect you to go full out bug bounty after reading this. But, would you happen to find yourself a website which is susceptible for a SQL injection I hope you would disclose it with the website owners. Don’t go all the way of breaking in, after you receive an error messages because of a tick, get in contact with the people behind the website and tell them how you generated that error. You do not have to do anything more.

Just one more thing, please don’t brag about your finding before disclosing it properly. After you have disclosed it with the websites owner, sure why not brag a bit!

## Final thought

Thank you for reading the whole text. I hope you found it interesting. SQL and SQL injection is a broad topic and I wish for this article to be nothing more than the snowflake on the top of the iceberg. Wish you all the best of luck in your hacking studies.

---
