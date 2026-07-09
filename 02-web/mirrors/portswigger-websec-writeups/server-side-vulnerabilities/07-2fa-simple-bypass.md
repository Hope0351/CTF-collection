# Lab Writeup: 2FA simple bypass

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/authentication-apprentice/authentication/multi-factor/lab-2fa-simple-bypass#

## Description

This lab's two-factor authentication can be bypassed. You have already obtained a valid username and password, but do not have access to the user's 2FA verification code. To solve the lab, access Carlos's account page.

- Your credentials: `wiener:peter`
- Victim's credentials `carlos:montoya`

## Solution

1. Login using `wiener:peter`
2. See the client email
3. Enter the security code and save the loggedin path which is `/my-account`
   ![2fa-simple-bypass](/assets/2fa-simple-bypass.png)
4. Logout and login using `carlos:montoya` then go straight to `/my-account` and the lab should be solved
   ![2fa-simple-bypass-1](/assets/2fa-simple-bypass-1.png)
