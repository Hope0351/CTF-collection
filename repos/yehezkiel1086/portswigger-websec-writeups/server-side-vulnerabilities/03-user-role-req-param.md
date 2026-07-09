# Lab Writeup: User role controlled by request parameter

## Description

This lab has an admin panel at `/admin`, which identifies administrators using a forgeable cookie.

Solve the lab by accessing the admin panel and using it to delete the user `carlos`.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1. Login using `wiener:peter`
2. Inspect and see the cookies then you'll see `Admin: false`
   ![User Role Req Param](/assets/user-role-req-param.png)
3. Change the value to `true`
4. Go to `/admin`, delete `carlos` and the lab should be solved.
   ![User Role Req Param 1](/assets/user-role-req-param-1.png)
