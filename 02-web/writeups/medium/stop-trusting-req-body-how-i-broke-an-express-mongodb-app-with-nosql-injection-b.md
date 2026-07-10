# :globe_with_meridians: NoSQL Injection in Express: Stop Trusting req.body

---

# Stop Trusting req.body: How I Broke an Express + MongoDB App with NoSQL Injection

In Express applications using MongoDB, a common mistake is passing `req.body` directly into database queries.

This mistake is not tied to login systems, authentication logic, or password handling. It can exist in any route that accepts user input and builds a MongoDB query without sanitization.

The problem is not what the endpoint does.
The problem is allowing user-controlled objects to influence MongoDB query operators.

>

Not a Medium member? Read the complete story here

This post walks through a small Express + MongoDB setup, a working NoSQL injection proof-of-concept, and the underlying reason this class of bugs appears across beginner and tutorial-based projects.

To demonstrate the issue clearly, this article uses a simple login endpoint. The endpoint is intentionally minimal so the behavior of the query is easy to observe. The vulnerability shown here would behave the same way in any other view or model that blindly trusts user input.

## Assumptions

This post assumes you already understand:

- Basic Express routing

- MongoDB / Mongoose queries

---
