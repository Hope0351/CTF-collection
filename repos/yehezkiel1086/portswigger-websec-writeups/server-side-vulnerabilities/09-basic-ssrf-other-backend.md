# Lab Writeup: Basic SSRF against another back-end system

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/ssrf-apprentice/ssrf/lab-basic-ssrf-against-backend-system#

## Description

This lab has a stock check feature which fetches data from an internal system.

To solve the lab, use the stock check functionality to scan the internal `192.168.0.X` range for an admin interface on port `8080`, then use it to delete the user `carlos`.

## Solution

1. Go to one of the products and click "Check stock" while intercepting the request using Burp
2. Send the intercepted request to intruder and change the `stockApi` value to `http://192.168.0.X:8080/` add the sign to `x`

   ![basic-ssrf-other-backend](/assets/basic-ssrf-other-backend.png)

3. Set the payload as numbers in the range of 1 - 255 then start the attack

   ![basic-ssrf-other-backend-1](/assets/basic-ssrf-other-backend-1.png)

4. From the intruder, we could see that the one that returns a different response is `http://192.168.0.154:8080/`

   ![basic-ssrf-other-backend-2](/assets/basic-ssrf-other-backend-2.png)

5. We can now try to request to `http://192.168.0.154:8080/admin`

![basic-ssrf-other-backend-3](/assets/basic-ssrf-other-backend-3.png)

We can see that we are now able to access the admin page to delete carlos

6. Send the following request payload `stockApi=http://192.168.0.154:8080/admin/delete?username=carlos`, carlos should be deleted and the challenge should be solved.

   ![basic-ssrf-other-backend-4](/assets/basic-ssrf-other-backend-4.png)
