# Lab Writeup: User ID controlled by request parameter, with unpredictable user IDs

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/access-control-apprentice/access-control/lab-user-id-controlled-by-request-parameter-with-unpredictable-user-ids

## Description

This lab has a horizontal privilege escalation vulnerability on the user account page, but identifies users with GUIDs.

To solve the lab, find the GUID for `carlos`, then submit his API key as the solution.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1. Login with `wiener:peter`
2. Go to a blog where the writer is `carlos` while already in the blog, click the username and you'll see the UID in the URL `https://0a5300d60317685c806a6292009600dc.web-security-academy.net/blogs?userId=d19f2737-7aeb-40f4-8507-a8264d7ecdf0`
   ![uid-predictable-req-param](/assets/uid-predictable-req-param.png)
3. Go to `/my-account` and replace the UID param with Carlos's `d19f2737-7aeb-40f4-8507-a8264d7ecdf0` here's the full version `https://0a5300d60317685c806a6292009600dc.web-security-academy.net/my-account?id=d19f2737-7aeb-40f4-8507-a8264d7ecdf0`. refresh and you should get Carlos's API key`mYKRkTGUNILHgWZ0LVLgSXr2U9aL2Jcs`
4. Submit the API key and the lab should be solved

   ![uid-predictable-req-param-1](/assets/uid-predictable-req-param-1.png)
