# :globe_with_meridians: $2000 Bounty: Stored XSS in GitLab

---

### Proof of Concept

The payload uploaded in the OpenAPI YAML file was an <a> tag with special attributes designed to trigger script loading

```
<a
data-remote="true"
data-method="get"
data-type="script"
href="/wbowling/wiki/raw/master/test.js"
class='atwho-view select2-drop-mask pika-select'>
</a>
```

Here’s how the exploit worked

- User visits the malicious OpenAPI YAML file inside GitLab’s repository file viewer.

- Clicks anywhere on the page.

- GitLab’s JavaScript event handlers process the crafted <a> tag triggering loading of an external JavaScript (test.js).

- The injected script runs in the context of GitLab.com.

### Step-by-Step Reproduction

- Go to the malicious file in a repository

2. Click anywhere on the page.

You should see an alert box pop up, proving JavaScript execution in GitLab’s context.

## Get Monika sharma’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Alternatively it could be triggered by chaining url parameters like

Same process click anywhere XSS triggers.

### What’s the impact?

This vulnerability was stored XSS

- Payload persisted in the repository file

- Any user viewing the malicious OpenAPI file could be exploited

Attackers could

- Steal the user’s CSRF token

- Render a phishing login form inside GitLab’s UI

- Perform actions on behalf of the user (account takeover)

- Escalate the attack to organization-wide compromise in shared repositories

Even though the XSS required a click, it was high impact because

- Stored on GitLab’s domain

- Any authenticated user could be affected

- Could exploit trust in GitLab’s interface

>

The root cause

- GitLab used an old version of Swagger UI

- That Swagger UI version relied on an outdated DOMPurify

- DOMPurify failed to sanitize certain HTML attributes

- CSP policy blocked direct <script> tags, but allowed indirect loading via data-* attributes

Upgrading Swagger UI & DOMPurify resolved the issue by closing the sanitization gap.

### The bounty & credit

For responsibly discovering and reporting this vulnerability, kannthu was awarded a $2000 bounty by GitLab under report ID #1072868.

This finding not only secured GitLab.com but also highlighted risks of embedding outdated third party libraries in production environments.

>

Lessons Learned

Keep third party dependencies up to date.Outdated libraries = inherited vulnerabilities. Test how CSP & JavaScript interact.Even with CSP attackers can find creative ways to execute scripts indirectly. Sanitize user controlled input at multiple layers.Don’t rely solely on frontend libraries also validate server side where possible.Don’t overlook non obvious input vectors.Swagger UI/OpenAPI files are often overlooked for XSS but they process user content!

### Final Thoughts

This vulnerability is a great example of how even secure platforms can be exposed through third party components and nuanced interactions between HTML, JavaScript, and CSP.

Huge kudos to kannthu for their excellent work uncovering and responsibly disclosing this issue! Their finding makes GitLab a safer platform for developers everywhere.

>

Thanks for reading! If you found this interesting *buying me a coffee!☕*

Monika ✨☕

---
