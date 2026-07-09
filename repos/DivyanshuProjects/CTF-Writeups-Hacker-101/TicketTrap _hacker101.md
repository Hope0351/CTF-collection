 🎯 CTF Challenge: TicketTrap

Category: Web  
Difficulty: Moderate  
Instance: Live Demo (Containerized)

---

 🧾 Description

TicketTrap is a support portal built for internal ticket handling at a tech startup. It allows users to submit tickets, while admins review and manage them from a private dashboard.

But there's more to this app than meets the eye. 🤔

Explore the endpoints, understand how users are managed, and see how the system handles (or mishandles) ticket data.

---

 🎯 Objectives

There are two flags hidden within the application. You must:

- 🏁 Flag 0: Gain unauthorized access by exploiting the ticket system's behavior and leveraging how users interact with links.
- 🏁 Flag 1: Use SQL injection to extract sensitive database details and retrieve the admin password.

---

 🧩 Flag 0 – User Creation via CSRF

 🔍 Goal:
Exploit the interaction between ticket content and admin behavior to create a new user account.

 🔧 Steps:
1. Attempt to access `/addUser` – returns 404:
   ```
   http://localhost:1337/addUser
   http://localhost:1337/addUser?username=test&password=test&password2=test
   ```
2. Go to the ticket submission page.
3. Craft a malicious payload in the body:
   ```html
   <a href="http://localhost:1337/newUser?username=test&password=test&password2=test">Click me</a>
   ```
4. Submit the ticket.
5. Wait a few seconds – if an admin views the ticket and clicks the link, your account is created.
6. Log in at `/admin` using `test:test`

 ✅ Outcome:
Access granted to admin dashboard as newly created user.


![image](https://github.com/user-attachments/assets/b697a473-0c6d-4af1-a71c-462951e46dd4)


---

 🧩 Flag 1 – SQL Injection via Ticket Endpoint (Using Burp Suite and SQLMap)

 🔍 Goal:
Exploit SQLi vulnerability to retrieve sensitive data, including the admin password.

 🔧 Steps:
(Method used by Divyanshu 🚀)

1. Open Burp Suite and intercept the request when accessing:
   ```
   http://localhost:1337/ticket?id=6
   ```
2. Capture the request and save it as `data.txt` from Burp Suite.
3. Run SQLMap with the saved request:
   ```bash
   sqlmap -r data.txt --dump --batch --banner
   ```
4. Wait around 5 minutes ⏳ while SQLMap automatically:
   - Extracts the database banner
   - Lists the tables (`tickets`, `users`)
   - Dumps data from the `users` table
5. In the dumped data, find the `admin` username and its associated password. 🎯

 ✅ Outcome:
Successfully retrieved the admin password quickly and efficiently without manually guessing the database structure.


![image](https://github.com/user-attachments/assets/b04702fb-1fa4-4d7c-acfa-2b2ea3955254)


---

 🧠 Learned Concepts
- Web interactions through ticket content (CSRF-style exploitation).
- Enumeration of database schema using SQL injection.
- Using Burp Suite to capture requests for offline analysis.
- Automating SQLi attacks using SQLMap.
- Efficient data extraction without manual payload crafting.
- Understanding error-based exploitation with real-world tools.

---
