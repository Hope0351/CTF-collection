# :game_die: Behind The Hack The Mechanics Of Sql Injection Attacks 9D35A34E8371

---

SQL injection arises when user input isn’t properly sanitized before being incorporated into database queries. This allows us to insert our harmful commands.

By exploiting SQL injection flaws, hackers can extract confidential data, alter data, or save files to the host server, potentially gaining full control over it.

## Let’s learn some syntax of SQL

```
-- SELECT statement to retrieve data from a table
SELECT column1, column2, ...
FROM tablename
WHERE condition;

-- INSERT statement to add data to a table
INSERT INTO tablename (column1, column2, ...)
VALUES (value1, value2, ...);

-- UPDATE statement to modify existing data in a table
UPDATE tablename
SET column1 = value1, column2 = value2, ...
WHERE condition;

-- DELETE statement to remove data from a table
DELETE FROM tablename
WHERE condition;

-- CREATE TABLE statement to create a new table
CREATE TABLE tablename (
column1 datatype,
column2 datatype,
...
);

-- DROP TABLE statement to delete a table
DROP TABLE tablename;

-- ALTER TABLE statement to modify a table (e.g., add a column)
ALTER TABLE tablename
ADD columnname datatype;

-- Basic JOIN operation to retrieve data from multiple tables
SELECT column1, column2, ...
FROM table1
JOIN table2
ON table1.column = table2.column
WHERE condition;
```

## Database Enumeration

- Enumerating MySQL Databases

```
select version();
select current_user();
select table_schema from information_schema.tables group by table_schema;
select table_name from information_schema.tables where table_schema = 'app';
select column_name, data_type from information_schema.columns where table_schema = 'app' and table_name = 'menu';
```

- Microsoft SQL Server-Specific Functions and Tables

```
select @@version;
SELECT SYSTEM_USER;
SELECT name FROM sys.databases;
select * from app.information_schema.tables;
select COLUMN_NAME, DATA_TYPE from app.information_schema.columns where TABLE_NAME = 'menu';

GO
```

- PostgreSQL Specific Functions and Tables

```
select version();
select current_user;
select datname from pg_database;
select table_name from app.information_schema.tables where table_schema = 'public';
select column_name, data_type from app.information_schema.columns where table_name = 'menu';
```

---
