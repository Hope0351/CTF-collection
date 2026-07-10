# :globe_with_meridians: NoSQL Injection in Express: Stop Trusting req.body

> **Original Source:** [NoSQL Injection in Express: Stop Trusting req.body](https://infosecwriteups.com/stop-trusting-req-body-how-i-broke-an-express-mongodb-app-with-nosql-injection-ba92208ebe53)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Stop Trusting req.body: How I Broke an Express + MongoDB App with NoSQL Injection


In Express applications using MongoDB, a common mistake is passing `req.body` directly into database queries.


This mistake is not tied to login systems, authentication logic, or password handling. It can exist in any route that accepts user input and builds a MongoDB query without sanitization.


The problem is not what the endpoint does.
The problem is allowing user-controlled objects to influence MongoDB query operators.

>

Not a Medium member? Read the complete story [here](https://medium.com/@sardarsubhodip857/stop-trusting-req-body-how-i-broke-an-express-mongodb-app-with-nosql-injection-ba92208ebe53?sk=a7389945f2408ba1dbab639f9657796e)


This post walks through a small Express + MongoDB setup, a working NoSQL injection proof-of-concept, and the underlying reason this class of bugs appears across beginner and tutorial-based projects.


To demonstrate the issue clearly, this article uses a simple login endpoint. The endpoint is intentionally minimal so the behavior of the query is easy to observe. The vulnerability shown here would behave the same way in any other view or model that blindly trusts user input.

## Assumptions


This post assumes you already understand:


- Basic Express routing

- MongoDB / Mongoose queries

---

*Originally published on [Medium](https://infosecwriteups.com/stop-trusting-req-body-how-i-broke-an-express-mongodb-app-with-nosql-injection-ba92208ebe53). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
