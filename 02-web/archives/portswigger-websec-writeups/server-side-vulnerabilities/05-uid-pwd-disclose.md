# Lab Writeup: User ID controlled by request parameter with password disclosure

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/access-control-apprentice/access-control/lab-user-id-controlled-by-request-parameter-with-password-disclosure

## Description

This lab has user account page that contains the current user's existing password, prefilled in a masked input.

To solve the lab, retrieve the administrator's password, then use it to delete the user `carlos`.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1. Login using `wiener:peter`
2. Change the id param in the URL to `administrator` here's the full URL:
   `https://0ab9004b04df858d870ea83e00e30086.web-security-academy.net/my-account?id=administrator`
3. Inspect the password value `ybnyydfm0iikizbu8upf`
   ![uid-pwd-disclose](/assets/uid-pwd-disclose.png)
4. Logout and login again with `administrator:ybnyydfm0iikizbu8upf`
5. Go to `/admin`, delete `carlos` and the lab should be solved.
   ![uid-pwd-disclose-1](/assets/uid-pwd-disclose-1.png)
