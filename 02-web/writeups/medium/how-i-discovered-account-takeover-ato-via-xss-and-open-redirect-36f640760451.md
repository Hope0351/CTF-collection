# :globe_with_meridians: How I Discovered Account Takeover (ATO) via XSS and Open redirect

---

# How I Discovered Account Takeover (ATO) via XSS and Open redirect

Hello Everyone,

Today, I want to share my experience of discovering an account takeover (ATO) vulnerability through XSS and Open redirect. Let’s dive right in!

So, hunting starts with a random program selection let call it `example.xyz.`It is a crypto platform.

I started hunting with enumerating subdomain and checking if there is any possible subdomain takeover but there is nothing found.

## Get JEETPAL’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I use my Wayback URLs to grab previous URL’s from the `example.xyz`and started hunting manually. I visited the signup page and started the registration process while registering on the site I notice a parameter called `callbackUrl`

```
https://example.xyz/sign-in?callbackUrl=
```

I decided to test this parameter with an open redirect payload.

```
https://example.xyz/sign-in?callbackUrl=https://example.xyz@evil.com
```

and this Open redirect works. After the signin. I was redirected to the evil.com. but this wasn’t sufficient for higher impact the max could go up to P3 /P4 so I decide to test for a xss. I use many payloads but the tags `<>`were filter out from the payload. So, I decided to use different payload i.e

```
javascript:alert(document.cookie)
```

and this one worked successfully I was able to pop-up an alert with session cookies. from here we can get those cookies into our server and use them.

![img_1.png](images/how-i-discovered-account-takeover-ato-via-xss-and-open-redirect-36f640760451/img_1.png)




After this I prepared a report to submit to the program. and after few days I got a reply from the program manager.

![img_2.png](images/how-i-discovered-account-takeover-ato-via-xss-and-open-redirect-36f640760451/img_2.png)




The report considers as duplicate of a 2024 report submitted by someone else on the platform.

Thank you for reading if you enjoy it clap 50 times

New articles Dropping soon

Connect with meLinkedin: [https://www.linkedin.com/in/jeet-pal-22601a290/](https://www.linkedin.com/in/jeet-pal-22601a290/)
Instagram: [https://www.instagram.com/jeetpal.2007/](https://www.instagram.com/jeetpal.2007/)
X/Twitter: [https://x.com/Mr_mars_hacker](https://x.com/Mr_mars_hacker)

---
