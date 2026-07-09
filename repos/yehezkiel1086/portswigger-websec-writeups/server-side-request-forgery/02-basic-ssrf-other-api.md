# Lab Writeup: Basic SSRF against another back-end system

URL: https://portswigger.net/web-security/learning-paths/ssrf-attacks/ssrf-attacks-common-ssrf-attacks/ssrf/lab-basic-ssrf-against-backend-system#

## Description

This lab has a stock check feature which fetches data from an internal system.

To solve the lab, use the stock check functionality to scan the internal `192.168.0.X` range for an admin interface on port `8080`, then use it to delete the user `carlos`.

## Solution

1. Go to one of the products, click on check stock and intercept the request:

   ![basic-ssrf-other-api](/assets/basic-ssrf-other-api.png)

2. Send to intruder, change the `stockApi` value to `http://192.168.0.§x§:8080/`:

   ![basic-ssrf-other-api-1](/assets/basic-ssrf-other-api-1.png)

3. Set the intruder payload as numbers ranging from 1 to 255:

   ![basic-ssrf-other-api-2](/assets/basic-ssrf-other-api-2.png)

4. Start the attack:

   ![basic-ssrf-other-api-3](/assets/basic-ssrf-other-api-3.png)

   From the above we could see that the ip `http://192.168.0.202:8080/` is possibly the valid backend API

5. Try changing the `stockApi` again to `http://192.168.0.202:8080/admin`:

   ![basic-ssrf-other-api-4](/assets/basic-ssrf-other-api-4.png)

   We see that we now are able to access the website with admin privilege

6. Change the `stockApi` again to `http://192.168.0.202:8080/admin/delete?username=carlos`:

   ![basic-ssrf-other-api-5](/assets/basic-ssrf-other-api-5.png)

   User `carlos` should be deleted and the challenge should be solved:

   ![basic-ssrf-other-api-6](/assets/basic-ssrf-other-api-6.png)
