# :globe_with_meridians: Write-up: Forced OAuth profile linking @ PortSwigger Academy

---

## The malicious payload

As my OAuth account is already linked to the account of `wiener`, I wait for the timeout of the lab application to continue.

I initiate the attack by starting to link my OAuth account. I then drop the final request back to the application:

That request was caused by a redirect from the OAuth provider back to the application. I go to the HTTP history, copy the response and paste it as a page on my exploit server.

The important part is the `Location` header that initiates the redirect, so I some of the clutter, especially the cookies:

I send the exploit to the victim and hope that the administrator checks that page.

To find out if I was successful, I log out of the application and login with the OAuth provider.

Luckily, the administrator obeys the lab description and checks all pages. My account page now shows that my social media account is linked to the administrator account on the blog application:

Once I access the admin panel and delete user `carlos`, the lab updates to

---
