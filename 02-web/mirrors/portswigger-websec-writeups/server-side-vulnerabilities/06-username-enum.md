# Lab Writeup: Username enumeration via different responses

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/authentication-apprentice/authentication/password-based/lab-username-enumeration-via-different-responses#

## Description

This lab is vulnerable to username enumeration and password brute-force attacks. It has an account with a predictable username and password, which can be found in the following wordlists:

- Candidate usernames
- Candidate passwords

To solve the lab, enumerate a valid username, brute-force this user's password, then access their account page.

## Solution

1. Go to `/login` and try logging in once with random username and password while intercepting the `POST` request using Burp
2. Send the intercepted request to burp intruder and add the sign to username body value

   ![username-enum](/assets/username-enum.png)

3. Paste the provided username lists as payload

   ![username-enum-1](/assets/username-enum-1.png)

4. Start the attack. We see that the only different response is from user with the username `agent` meaning the username is valid

   ![username-enum-2](/assets/username-enum-2.png)

5. Go back to the intruder but now change the value of username with `agent` and add the sign to password as such:

   ![username-enum-3](/assets/username-enum-3.png)

6. Clear the payload and change it with the provided password payloads

   ![username-enum-4](/assets/username-enum-4.png)

7. Start the attack and see the responses.

   ![username-enum-5](/assets/username-enum-5.png)

   From the above image, we could see that the response is different for the password `michael` from the rest (302 response)

   ![username-enum-6](/assets/username-enum-6.png)

8. Try logging in using `agent:michael`. We can see that we successfully and the lab is solved

   ![username-enum-7](/assets/username-enum-7.png)
