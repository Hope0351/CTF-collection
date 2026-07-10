# :globe_with_meridians: SSRF to Internal Port Scanning on Self-Hosted Platform 🚀

> **Original Source:** [SSRF to Internal Port Scanning on Self-Hosted Platform 🚀](https://infosecwriteups.com/ssrf-to-internal-port-scanning-on-self-hosted-platform-05a17a461eed)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# SSRF to Internal Port Scanning on Self-Hosted Platform 🚀


[Free Artices](https://medium.com/@jeetpal2007/ssrf-to-internal-port-scanning-on-self-hosted-platform-05a17a461eed?sk=e2cd54aca1118ebdb7ea5eb4e635f75e)


While exploring a self-hosted platform’s webhook feature, I discovered a Server-Side Request Forgery (SSRF) vulnerability that allowed me to scan internal network ports. This unexpected find opened up a world of network mapping possibilities. Big thanks to my friend who invited me over at [Discord](https://discord.gg/Y467qAFM4X) for making the hunt even more fun and insightful! 🎉

### Discovery Phase 🔍


I started with a pretty simple task: testing out the webhook feature of this self-hosted platform. Typically, webhooks let users forward data to a specified URL, so I entered a `webhook.site` URL to see what kind of response I’d get. The server sent an outbound request as expected, which made me think—*what if I could direct this request internally?* SSRF possibilities started brewing in my mind.

### Testing the Profile for SSRF 🧪


To confirm the vulnerability, I swapped the external URL with an internal IP, like `http://127.0.0.1`, just to see if the server would follow along. It worked! The platform processed my internal IP and even returned a response, confirming that I had access to the internal network through SSRF. With this in place, I decided to dig a little deeper and see if I could go beyond just reaching internal IPs.


---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-to-internal-port-scanning-on-self-hosted-platform-05a17a461eed). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
