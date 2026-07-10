# :game_die: Medium

---

**The lab states that it is not an Oracle database, which means it could be either MySQL, MSSQL, or PostgreSQL.**

- In this case, it turns out to be a **PostgreSQL database**, and you’ll see why by the end of this blog.

- Since it’s a PostgreSQL database, there are a few important details we need to keep in mind.

N**ote:**

When you’re unsure about the core database, it’s a good idea to test payloads from different database types; one of them might trigger a response.

>

***Microsoft SQL Server: SELECT @@version*

***PostgreSQL: SELECT version()*

***MySQL: SELECT @@version*

In PostgreSQL, "`***information_schema.tables"***` is commonly used to enumerate available tables within the database.

## Get RayofHope’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

P***ostgreSQL, ***`***information_schema.tables***`*** includes:***

- `***table_catalog***` (Name of the database containing the table (always the current database)

- `***table_schema***` (Name of the schema containing the table, like `public`, `pg_catalog`, etc.)

- `***table_name ***`(Name of the Table)

- `***table_type***` (e.g., `'BASE TABLE'`, `'VIEW'`)

- `***column_name***`(Name of the column)

Here’s what the application looks like.

---
