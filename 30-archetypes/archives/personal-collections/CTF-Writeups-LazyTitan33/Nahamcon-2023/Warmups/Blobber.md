# Blobber

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The file we get is a SQLite database file:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Opening it in the DB Browser, we notice a lot of entries with random looking names. 

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It was all garbage. I spend some time trying to find the needle in the haystack but then I remembered it's a SQL database so we can simply use queries. All the `name` columns contained junk, and all the `data` columns were empty. But that is something we can double check using the SQL query below to list everything that doesn't have a NULL data column entry:

```sql
select * from blobber where data != 'NULL';
```
It turns out we have a blob in one of the entries:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Good thing I learned to leave assumptions at the door when doing CTFs. Now I used some short python scripting to pull out the blob and write it to a file since I didn't know exactly what it was.

```python3
import sqlite3

conn = sqlite3.connect('blobber')
cursor = conn.cursor()

cursor.execute("select data from blobber where data != 'NULL';")

result = cursor.fetchone()
blob_content = result[0]

with open('output.bin', 'wb') as file:
    file.write(blob_content)
    
conn.close()
```

We can use the file command on it and find out it's a `bzip2` archive.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can use `bzip2 -d` to decompress it:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And the resulting file is a picture:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

That contains our flag:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{b93a6292f3491c8e2f6cdb3addb5f588}
