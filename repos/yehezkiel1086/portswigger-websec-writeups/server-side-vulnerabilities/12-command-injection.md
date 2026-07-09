# Lab Writeup: OS command injection, simple case

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/os-command-injection-apprentice/os-command-injection/lab-simple#

## Description

This lab contains an OS command injection vulnerability in the product stock checker.

The application executes a shell command containing user-supplied product and store IDs, and returns the raw output from the command in its response.

To solve the lab, execute the `whoami` command to determine the name of the current user.

## Solution

1. Go to one of the products
2. Check stock and intercept with burp
   ![command-injection](/assets/command-injection.png)

   We can see the parameters being passed `productId` and `storeId`

3. Change the `productId` param with `& whoami &` then encode it with URL encoding

   ![command-injection-1](/assets/command-injection-1.png)

   ![command-injection-2](/assets/command-injection-2.png)

4. Send and the lab should be solved.

   ![command-injection-3](/assets/command-injection-3.png)
