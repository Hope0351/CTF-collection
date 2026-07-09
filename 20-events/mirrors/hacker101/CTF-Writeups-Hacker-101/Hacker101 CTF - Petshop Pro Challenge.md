 Hacker101 CTF - Petshop Pro Challenge

 🏆 Challenge Overview
- Platform: Hacker101
- Challenge Name: Petshop Pro
- Flags: 3

This challenge requires exploiting vulnerabilities in a pet shop web application to uncover three hidden flags. Through client-side manipulation, brute-force techniques, and stored XSS, I was able to retrieve all three flags. Let's dive into the details!



 🏁 Flag 1 - Price Manipulation Attack 🛒💰
The first vulnerability exists in the Add to Cart and Payment functionality. While inspecting the checkout process, I noticed that the application relies on client-side pricing, meaning the user can modify it before the final purchase is processed.

 🔍 Steps to exploit:
1. Add an item to the cart and proceed to checkout.
2. Intercept the payment request using Burp Suite.
3. Locate the `price` field in the intercepted request and modify it (e.g., change `$100` to `$1`).
4. The response from the server was encoded, so I decoded it first.
5. Created a new encoded request with the manipulated price and sent it back to the server.
6. The server accepted the manipulated price, and the purchase was completed at a fraudulently reduced cost.
7. 🎉 Flag Captured!

 🔥 Key Takeaways:
- Never trust client-side inputs, especially for critical data like pricing.
- Always enforce server-side validation to prevent such exploits.
- Implement hash-based verification or digital signatures to detect price tampering.


![Screenshot (7)](https://github.com/user-attachments/assets/f9a623a6-d98d-4b8a-ae74-dd35d75990e4)

---

 🏁 Flag 2 - Brute Force Login Attack 🔑🚪
During my reconnaissance, I performed directory enumeration using tools like `dirb` and `gobuster`, which led me to an unprotected login page (`/admin/login`).

I initially attempted an SQL Injection (SQLi), but it was well-secured against direct attacks. Instead, I opted for a brute-force attack using Burp Suite Intruder and Hydra, leveraging a common credential wordlist.

 🔍 Steps to exploit:
1. Use `dirb` or `gobuster` to discover the login endpoint.
2. Try SQL Injection, but it's blocked.
3. Initiate a brute-force attack using Hydra:
   ```bash
   hydra -L usernames.txt -P rockyou.txt target_ip http-post-form "/admin/login:username=^USER^&password=^PASS^:Invalid login"
   ```
4. Eventually, I successfully retrieved the admin credentials.
5. 🎉 Flag Captured!

🔍 Spoiler Alert: Instead of brute-forcing, you can directly bypass authentication using:
```
your_IP/edit?id=0 or 1
```

![Screenshot 2025-02-21 104113](https://github.com/user-attachments/assets/2df22ff6-ab8d-499d-b3b4-da1ad5662413)

This simple trick provides direct access to internal admin functionalities without requiring login credentials!

 🔥 Key Takeaways:
- Implement account lockouts after multiple failed attempts.
- Enforce CAPTCHA to prevent automated brute-force attacks.
- Hide admin login pages using obfuscation techniques (e.g., security through obscurity).

---

 🏁 Flag 3 - Stored XSS Exploit 🎭⚠️
After logging in (via brute force or bypass), I discovered an edit pet details feature, which lacked input sanitization. This allowed me to inject Stored XSS (Cross-Site Scripting) payloads.

 🔍 Steps to exploit:
1. Navigate to the pet details editing section.
2. Modify the pet’s name field with an XSS payload:
   ```html
   <img src=x onload=alert(1)>
   ```
3. Save the changes.
4. Return to the homepage.
5. Click Add to Cart, triggering the stored XSS.
6. Boom! The flag appears! 🎉

 🔥 Key Takeaways:
- Always sanitize user inputs before storing them in a database.
- Use Content Security Policy (CSP) to mitigate XSS attacks.
- Employ escaping mechanisms (e.g., encoding HTML special characters).

---

 🛡️ Final Thoughts & Lessons Learned 📚
🔹 Never trust client-side data – Always enforce validation server-side to prevent price manipulation attacks.  
🔹 Protect login endpoints – Use rate limiting, multi-factor authentication (MFA), and CAPTCHA to prevent brute-force attacks.  
🔹 Sanitize all user inputs – Implement secure coding practices to prevent stored XSS and enhance overall application security.

🚀 Security is all about thinking like an attacker to defend like a pro! Stay curious, stay ethical, and keep hacking! 🛡️

