# Lab Writeup: Basic SSRF against the local server

URL: https://portswigger.net/web-security/learning-paths/ssrf-attacks/ssrf-attacks-common-ssrf-attacks/ssrf/lab-basic-ssrf-against-localhost#

## Description

This lab has a stock check feature which fetches data from an internal system.

To solve the lab, change the stock check URL to access the admin interface at `http://localhost/admin` and delete the user `carlos`.

## Solution

1. Go to one of the products, click on check stock and intercept the request:

   ![basic-local-ssrf](/assets/basic-local-ssrf.png)

2. Send the request to burp repeater, change the `stockApi` to `http://localhost/`, send the request then you'll get the admin privilege:

   ![basic-local-ssrf-1](/assets/basic-local-ssrf-1.png)

3. Change the `stockApi` again to `http://localhost/admin`, you'll get a link to delete `carlos`
4. Change the `stockApi` again to `/admin/delete?username=carlos`, `carlos` should be deleted and the lab is solved:

   ![basic-local-ssrf-2](/assets/basic-local-ssrf-2.png)

   ![basic-local-ssrf-3](/assets/basic-local-ssrf-3.png)
