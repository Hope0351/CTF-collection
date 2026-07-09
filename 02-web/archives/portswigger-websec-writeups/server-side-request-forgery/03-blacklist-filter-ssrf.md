# Lab Writeup: SSRF with blacklist-based input filter

URL: https://portswigger.net/web-security/learning-paths/ssrf-attacks/ssrf-attacks-circumventing-defenses/ssrf/lab-ssrf-with-blacklist-filter#

## Description

This lab has a stock check feature which fetches data from an internal system.

To solve the lab, change the stock check URL to access the admin interface at `http://localhost/admin` and delete the user `carlos`.

The developer has deployed two weak anti-SSRF defenses that you will need to bypass.

## Solution

1. Go to one of the products, click on check stock and intercept the request:

   ![blacklist-filter-ssrf](/assets/blacklist-filter-ssrf.png)

2. Send to repeater, change the `stockApi` value to `http://127.0.0.1`:

   ![blacklist-filter-ssrf-1](/assets/blacklist-filter-ssrf-1.png)

   From the above image we'll know that `http://127.0.0.1` is blocked, so we have to circumvent around it

3. Try using `http://127.1/`:

   ![blacklist-filter-ssrf-2](/assets/blacklist-filter-ssrf-2.png)

   We can see that it's bypassed

4. Try changing the `stockApi` again to `http://127.1/admin`:

   ![blacklist-filter-ssrf-3](/assets/blacklist-filter-ssrf-3.png)

   We can see that it's blocked again

5. Try encoding the first character "a" so it becomes `http://127.1/%2561dmin`:

   ![blacklist-filter-ssrf-4](/assets/blacklist-filter-ssrf-4.png)

   We can see that we could finally access the admin page

6. Try changing the `stockApi` again to `http://127.1/%2561/delete?username=carlos`:

   ![blacklist-filter-ssrf-5](/assets/blacklist-filter-ssrf-5.png)

   We can see that `carlos` is now deleted and the lab should be solved:

   ![blacklist-filter-ssrf-6](/assets/blacklist-filter-ssrf-6.png)
