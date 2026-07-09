# Lab Writeup: SSRF with filter bypass via open redirection vulnerability

URL: https://portswigger.net/web-security/learning-paths/ssrf-attacks/ssrf-attacks-circumventing-defenses/ssrf/lab-ssrf-filter-bypass-via-open-redirection

## Description

This lab has a stock check feature which fetches data from an internal system.

To solve the lab, change the stock check URL to access the admin interface at `http://192.168.0.12:8080/admin` and delete the user `carlos`.

The stock checker has been restricted to only access the local application, so you will need to find an open redirect affecting the application first.

## Solution

1. Go to one of the products, click on "Next product" then intercept the request:

   ![ssrf-open-redirection](/assets/ssrf-open-redirection.png)

   From the above we can see that there's a potential openApi redirection vulnerability `/product/nextProduct?currentProductId=2&path=/product?productId=3` which is in the `path` parameter

2. Go to one of the products, click on "Check Stock":

   ![ssrf-open-redirection-1](/assets/ssrf-open-redirection-1.png)

   then you can see that there is a possibility of SSRF in `stockApi` body, send the request to repeater

3. Change the `stockApi` value with `/product/nextProduct?path=http://192.168.0.12:8080/admin`:

   ![ssrf-open-redirection-2](/assets/ssrf-open-redirection-2.png)

   From the above we could see that we are able to access (redirected) to `/admin` page

4. Change the `stockApi` value with `/product/nextProduct?path=http://192.168.0.12:8080/admin/delete?username=carlos`:

   ![ssrf-open-redirection-3](/assets/ssrf-open-redirection-3.png)

   User `carlos` should be deleted and the lab should be solved.

   ![ssrf-open-redirection-4](/assets/ssrf-open-redirection-4.png)
