# :globe_with_meridians: Writeup: Path mapping for web cache deception @ PortSwigger Academy

> **Original Source:** [Writeup: Path mapping for web cache deception @ PortSwigger Academy](https://infosecwriteups.com/writeup-path-mapping-for-web-cache-deception-portswigger-academy-184ae04ca4c7)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Writeup: Path mapping for web cache deception @ PortSwigger Academy


*APPRENTICE-LAB*


Before starting, configure FoxyProxy to intercept requests through Burp Suite. Ensure that ‘Intercept’ is turned off in Burp Suite while FoxyProxy is active, so that all requests are logged in the HTTP history. Then, log in to the application using the credentials **wiener:peter**.


Please note that the response will include your API key.


*Login*


Go to Burpuite **Proxy > HTTP history**, right-click the GET /my-account request and select **Send to Repeater**.


*HTTP history*


Navigate to the Repeater tab. Modify the base path by adding an arbitrary segment; for example, change the path to `/my-account/hanzala`. Send the request and observe that you still receive a response containing your API key. This indicates that the origin server abstracts the URL path to `/my-account`. Additionally, ensure that you receive a 200 response and verify that the request is not cached


*Repeater Tab*


Add a static extension to the URL path, such as `/my-account/hanzala.js`, and send the request.


## Get Hanzala Ghayas Abbasi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Observe the response headers for `X-Cache: miss` and `Cache-Control: max-age=30`. For example:


- **X-Cache**: `miss` – This indicates that the response was not served from the cache.

- **Cache-Control**: `max-age=30` – This specifies that if the response were cached, it should be stored for 30 seconds.


*extension cache*


Resend the request within 30 seconds. You should notice that the `X-Cache` header changes to `hit`, indicating that the response was served from the cache. This suggests that the cache interprets the URL path with the `.js` extension and has a caching rule for it.


*cache hit*


So Now we Know that our request is cache lets create the exploit.


- In browser, click **Go to exploit server**.

- In the **Body** section, craft an exploit that navigates the victim user carlos to the malicious URL that you crafted earlier. Make sure to change the arbitrary path segment you added, so the victim doesn’t receive your previously cached response.

- Click **Deliver exploit to victim**. When the victim views the exploit, the response they receive is stored in the cache.


```
<script>document.location="https://YOUR-LAB-ID.web-security-academy.net/my-account/hanzalaa.js"</script>
```


*exploit*


Now in Burp Suite, change the path to `/my-account/hanzalaa.js`. Since Carlos's response is stored in the server cache, this request will return the same response. Send the request to retrieve Carlos's API key. Copy it.


*Carlos API*


Click **Submit solution**, then submit the API key for carlos to solve the lab.


*Solved*

---

*Originally published on [Medium](https://infosecwriteups.com/writeup-path-mapping-for-web-cache-deception-portswigger-academy-184ae04ca4c7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
