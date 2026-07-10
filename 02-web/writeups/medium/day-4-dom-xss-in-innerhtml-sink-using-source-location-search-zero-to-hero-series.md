# :globe_with_meridians: Day 4 Dom Xss In Innerhtml Sink Using Source Location Search Zero To Hero Series

---

Let's understand in this way:
`*<span id="searchMessage"></span>*`* creates an empty *`*<span>*`* element in the DOM with the ID *`*searchMessage*`*. This ID allows JavaScript to target and modify the element’s content. However, if user-controlled input is inserted into this element without proper sanitisation, especially using *`*innerHTML*`*It can lead to Cross-Site Scripting (XSS) vulnerabilities. An attacker could exploit this to inject and execute malicious scripts in the browser. Therefore, it's important to handle dynamic content securely by using *`*textContent*`* or properly sanitising input before injecting it into the DOM.function doSearchQuery(query) { document.getElementById(‘searchMessage’).innerHTML = query;
} Here, this function takes a string query as an argument. It then finds the <span> element in the DOM with the ID searchMessage using document.getElementById(…), and sets its innerHTML to the value of query. The issue here is that innerHTML treats the input as actual HTML, not plain text. If a query contains any HTML tags or JavaScript code (e.g., <script>), the browser will parse and execute it. This makes the function vulnerable to Cross-Site Scripting (XSS) attacks if the input is not properly sanitised.*Mitigation:
*To prevent this, use *`*textContent*`* instead, which treats the input as plain text and avoids executing any embedded HTML or scripts (document.getElementById(‘searchMessage’).textContent = query)*

---
