# :game_die: Day 14: Blind SQL injection with time delays - Zero to Hero Time-Based Blind SQL Injection - Portswigger

---

Note:

- *Time-based SQL Injection is a subtype of blind SQL injection where the attacker determines the presence of a vulnerability based on the time the database takes to respond. Based on the response time, the attacker can determine whether a condition is true or false and exploit the vulnerability.*

>

Each database management system (DBMS) has its own built-in function to pause execution, so the payload used in time-based SQLi varies depending on the backend.

- MySQL: select sleep(10)
MSSQL: waitfor delay ‘0:0:10’
PostgreSQL: select pg_sleep(10)
Oracle: dUbms_pipe.receive_message((‘a’),10)Lab Questions: This lab contains a blind SQL injection vulnerability. The application uses a tracking cookie for analytics and performs a SQL query containing the value of the submitted cookie. The results of the SQL query are not returned, and the application does not respond any differently based on whether the query returns any rows or causes an error. However, since the query is executed synchronously, it is possible to trigger conditional time delays to infer information.

## Get RayofHope’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

To solve the lab, exploit the SQL injection vulnerability to cause a 10-second delay.

>

Objective:
What is the database
What kind of payload will be used for that database?
Delayed response time by 10 seconds.

*This is how the lab looks — let’s intercept the data.*

---
