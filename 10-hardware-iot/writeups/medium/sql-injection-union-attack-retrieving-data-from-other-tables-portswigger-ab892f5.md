# :electric_plug: SQL injection UNION attack, retrieving data from other tables - Portswigger

---

# SQL injection UNION attack, retrieving data from other tables — Portswigger

Hi, my fellow hackers. This is Rayofhope. I have over 5 years of experience and am currently working as a consultant with a Big 4 firm.

Day 9 of posting all the PortSwigger labs, not just the solutions. I’ll break down *why* we take each step, because once the ***‘why’ is clear, the ‘how’ becomes easy.*Let’s Start:**

>

***Before you go for this blog, make sure to read the Previous one
Link to Seventh Blog: *

**Video Walkthrough** — You can watch the video or read the blog, totally up to you. But if you ask me, start with the video, then read the blog to connect all the dots.

### **This is what the lab says.**

- This lab contains a SQL injection vulnerability in the product category filter. The results from the query are returned in the application’s response, so you can use a UNION attack to retrieve data from other tables. To construct such an attack, you need to combine some of the techniques you learned in previous labs.

- The database contains a different table called `users`, with columns called `username` and `password`.

- To solve the lab, perform a SQL injection UNION attack that retrieves all usernames and passwords, and use the information to log in as the `administrator` user.

**In this blog, I will jump directly into the practical part. For the theory and concepts, please refer to the Day 7 blog.**

## Get RayofHope’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Here’s what the application looks like.

---
