 Micro-CMS v1 - Web CTF Walkthrough

 🏆 Challenge Overview
- Challenge Name: Micro-CMS v1  
- Category: Web  
- Difficulty: Easy  
- Flags: 4  

Hey everyone! I'm Divyanshu Kumar, a cybersecurity enthusiast. In this post, I’ll walk you through my experience solving the Micro-CMS v1 CTF challenge. This is part of my series where I explore cybersecurity concepts through CTF (Capture The Flag) walkthroughs.

⚠️ Disclaimer: I’m still learning, and these posts are meant to document and share my knowledge as I grow in the cybersecurity field. Now, let’s dive into the challenge! 🕵️‍♂️

---

 🏁 Flag 1 - Stored XSS via Page Creation 🖊️💥
This CMS allows users to create new pages by specifying a heading and content. I noticed that the heading of the page appears on the homepage without any sanitization.

 🔍 Steps to exploit:
1. Navigate to the Create New Page section.
2. Enter a normal heading and some content.
3. Instead of a normal heading, inject this XSS payload:
   ```html
   Hello <script>alert(1)</script>
   ```
4. Submit the page and return to the homepage.
5. Boom! The JavaScript executes, confirming a Stored XSS vulnerability.
6. 🎉 Flag Captured!

 🔥 Key Takeaways:
- Always sanitize user inputs before rendering them.
- Implement Content Security Policy (CSP) to prevent JavaScript execution.
- Escape special characters to mitigate XSS attacks.


---

 🏁 Flag 2 - IDOR (Insecure Direct Object Reference) 🔢🔓
After creating a page, I noticed my page ID was `10`. However, only three pages were visible on the homepage. This made me wonder: Are there hidden pages?

 🔍 Steps to exploit:
1. Manually modify the page ID in the URL, testing IDs from `1` to `12`.
2. Example URL:
   ```
   http://target-site.com/view?id=7
   ```
3. Boom! At ID `7`, I was granted access to a restricted page, and the flag appeared!
4. 🎉 Flag Captured!

 🔥 Key Takeaways:
- Use proper access controls to restrict unauthorized access to pages.
- Implement UUIDs instead of predictable numeric IDs.
- Always check user authorization before displaying sensitive data.

  


---

 🏁 Flag 3 - SQL Injection in Page Editing 🏗️💀
I found a page edit feature in the CMS. The URL format was:
```
http://target-site.com/edit/1
```
I suspected SQL Injection, so I tried adding a single quote (`'`) after the page ID.

 🔍 Steps to exploit:
1. Navigate to the Edit Page section.
2. Modify the URL:
   ```
   http://target-site.com/edit/1'
   ```
3. Boom! An SQL error appeared, confirming a vulnerability.
4. 🎉 Flag Captured!


 🔥 Key Takeaways:
- Use prepared statements to prevent SQLi.
- Filter user input and escape special characters.
- Restrict direct database queries from URLs.

---

 🏁 Flag 4 - Stored XSS via Button Injection 🎭⚠️
On one of the pages, I noticed a button feature. Since the application didn’t sanitize user input, I inserted an XSS payload inside the button's attributes.

 🔍 Steps to exploit:
1. Locate a page with a button element.
2. Modify the button with this payload:
   ```html
   <button onclick=alert('xss')>Click Me</button>
   ```



   
3. Save the changes and navigate back to the homepage.
4. Boom! The payload executed, confirming another Stored XSS vulnerability.
5. 🎉 Flag Captured!

 🔥 Key Takeaways:
- Always sanitize and escape user inputs.
- Use CSP policies to restrict JavaScript execution.
- Avoid rendering user input directly in the DOM.

---

 🏁 Final Thoughts & Lessons Learned 📚
Through this challenge, I exploited Stored XSS, SQL Injection, and IDOR vulnerabilities, reinforcing the importance of:

✔ Input validation & sanitization – Prevents XSS and SQLi attacks.  
✔ Access control mechanisms – Stops unauthorized access to sensitive pages.  
✔ Using prepared statements – Protects against SQL Injection.

🛡️ Security is all about thinking like an attacker to defend like a pro! Stay curious, stay ethical, and keep hacking! 🚀



