# :game_die: Plan Ristriction Bypass for Slack Integration: 500$ Improper Validation Check Bug

> **Original Source:** [Plan Ristriction Bypass for Slack Integration: 500$ Improper Validation Check Bug](https://infosecwriteups.com/plan-ristriction-bypass-for-slack-integration-500-improper-validation-check-bug-0c1acf6f01d3)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Plan Ristriction Bypass for Slack Integration: 500$ Improper Validation Check BugHello Readers, I’m thrilled to share details about a recent discovery I made concerning entry.io’s integration functionality. I’ve identified a vulnerability that allows users with free plan accounts to bypass subscription restrictions and integrate Slack, typically reserved for higher subscription tiers. For this report, Xentry.io acknowledged the issue and awarded me a bounty of $500.


>

Understanding Target


Xentry.io is a prominent platform used for error tracking and monitoring in software development. However, a flaw in its integration setup process enables users to circumvent plan restrictions and utilize Slack integrations without the required subscription level.

>

The Vulnerability:


This vulnerability arises from improper validation in Xentry.io’s integration setup flow, particularly when transitioning from GitHub to Slack integrations. Users on free plan accounts can exploit this flaw by modifying intercepted HTTP requests, allowing them to add Slack integrations instead of the restricted GitHub integrations.

### Steps to Reproduce:


Create a Free Plan Account:


- Sign up for a free plan account on Xentry.io.

- Go to the integrations section and select GitHub integration(which is free for all the users) .

- Use tools like Burp Suite to intercept the HTTP request for adding GitHub integration. `(GET /organizations/dd-0n/integrations/github/setup/? HTTP/2)`

- Replace “github” with “slack” in the intercepted request URL.

- Forward the modified request and follow the steps on the new page to connect your Slack account with Xentry.

>


## Get Abhi Sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Impact


- Users on free plan accounts can access Slack integrations, potentially exposing sensitive information and configuring alerts within Slack channels.

- It undermines Xentry.io’s subscription model by allowing users to utilize premium features reserved for higher subscription tiers, impacting operational integrity and service delivery.

>

Response and Resolution


Upon discovering this vulnerability, I promptly reported it to Xentry.io’s security team. They acknowledged the issue and took immediate steps to address the flaw, ensuring that proper validation mechanisms are in place to enforce plan restrictions effectively. As a token of appreciation for responsible disclosure, I received a bounty of $500.


>

Connect and Engage


If you found this article informative, please share your feedback and insights in the comments section. Follow me for more updates on cybersecurity insights and responsible disclosure stories.

>

Connect on Twitter: [@a13h1_](https://twitter.com/a13h1_)


### Thank you for your continued support. Keep clapping, commenting, and sharing your thoughts!

---

*Originally published on [Medium](https://infosecwriteups.com/plan-ristriction-bypass-for-slack-integration-500-improper-validation-check-bug-0c1acf6f01d3). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
