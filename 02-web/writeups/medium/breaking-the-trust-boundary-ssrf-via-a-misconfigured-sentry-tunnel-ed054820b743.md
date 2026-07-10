# :globe_with_meridians: Breaking the Trust Boundary: SSRF via a Misconfigured Sentry Tunnel

---

# Breaking the Trust Boundary: SSRF via a Misconfigured Sentry Tunnel

Free Article Link: Click for free!

Hello readers,
Sometimes the most interesting vulnerabilities are not hiding in login forms, password reset flows, or API endpoints — they hide in the background. This story started with a feature that most testers completely ignore: an error logging endpoint.
While testing target.com, I noticed a request being sent to an endpoint called:

```
POST /tunnel/
```

At first glance, it looked harmless. Just telemetry. Just logging. Just Sentry doing its thing. But security testing has taught me one important rule:
If the server makes a request based on something I control — I look closer. And that’s exactly what happened here.

*For more real-world SaaS security research and application security testing insights, explore:
*[https://thehiddenfinds.com/blog/](https://thehiddenfinds.com/blog/)

## Before We Dive In — What Is SSRF?

Server-Side Request Forgery (SSRF) happens when an application allows user-controlled input to influence a server-side HTTP request.

In simple terms:

Instead of sending requests directly to a system, I trick the server into…

---
