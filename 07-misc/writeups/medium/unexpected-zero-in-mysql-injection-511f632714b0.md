# :game_die: Unexpected Zero in MySQL Injection

---

# Unexpected Zero in MySQL Injection

When conducting a pentest on a client (sorry, I cannot provide real screenshots here), I discovered a SQL injection vulnerability, but there were some limitations that seemed to be implemented as coding filters.

The discovered form looked like this (I have simplified it for easier reading and understanding):

[https://example.com/employee/search/?name={keyword_here}](https://example.com/employee/search/?name=%7Bkeyword_here%7D)

The SQL injection payloads I could obtain were:

- ‘+version()+’

- ‘+database()+’

I concluded that this was a SQL injection vulnerability in MySQL. However, there are a few observations I made:

- Boolean-based exploitation cannot be performed because the output always remains the same.

- If I provide a function outside of MySQL, such as hello(), it will result in a 500 error.

- Attempts to perform enumeration, such as using the substring function, do not provide different output, making enumeration impossible.

- The sleep function has been filtered, so I cannot use it.

- I am unable to use injection comments either — or #.

Then an idea emerged: What if I input 0 into a certain field? But before that, I tried it out using an [online MySQL interface](https://www.w3schools.com/mysql/trymysql.asp?filename=trysql_editor) . Please note that the following query returned 91 records.

Then I tried modifying the query in the CustomerName field as follows:

And the result still displayed all records!

## Get Dimaz Arno’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I tried confirming this on my local MySQL (with a different database and table):

The result was the same! It returned all the data!

Next, I tried it on PostgreSQL:

Interestingly, PostgreSQL gave an error. Does this mean that MySQL doesn’t enforce an error when there’s a data type mismatch? Interesting!

Returning to my pentest, if I want to retrieve all the data using SQL injection using this method, it means I need to provide an integer input. However, it’s important to note that the original query expects a string.

Eventually, I came up with an idea like this:

The injection would be: ‘x’+0+’x’, which would be interpreted as 0 by MySQL, causing a data type difference!

So I can pull all the data without using injection comments, like this:

[https://example.com/employee/search/?name=x'+0+'x](https://example.com/employee/search/?name=x%27+0+%27x)

Thank you for reading!

---
