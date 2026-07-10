# :globe_with_meridians: $256 Bounty : XSS via Web Cache Poisoning in Discourse

---

>

Step-by-Step Breakdown: How the Bug Was Found

- Target Discourse-based Sites

Bobrov tested live instances of Discourse such as:

- meta.discourse.org

- discourse.mozilla.org

- forum.glasswire.com

- help.nextcloud.com

2. Analyze Template Rendering

The template at _special_font_face.html.erb rendered external user-controlled input (from the host header) directly into HTML.

3. Inject a Malicious Header

- Using tools like Burp Suite or cURL:

```
GET /?xx HTTP/1.1
Host: meta.discourse.org
X-Forwarded-Host: cacheattack'"><script>alert(document.domain)</script>
```

4. Observe the Rendered Output

The script ended up inside the href and src attributes of font preload links and it got parsed by the browser.

5. Bonus Exploitation: Cache Poisoning

Discourse cached this response for 60 seconds. That means other users who request the page with the same headers would receive the already poisoned response functioning like a temporary Stored XSS.

### POC

### Impact

- Cross-Site Scripting (XSS): Exploited via header injection.

- Web Cache Deception: Payload persisted for up to 60 seconds.

- Affects Multiple Live Instances: Even major platforms like Mozilla.

- Stored-like Behavior: Feels like Stored XSS despite being injected via request headers.

### How You Can Find Similar Bugs

Want to hunt down Web Cache Deception or header-based XSS? Follow this guide:

- Target Popular Frameworks

Look at apps built with:

- Discourse

- Django

- Ruby on Rails

- Express.js

These often rely on reverse proxies and are prone to unsafe use of X-Forwarded-headers.

## Get Monika sharma’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

2. Check for Improper Output Encoding

- Look at templates and rendered output.

- Focus on font preloading, meta tags, image sources these are often dynamically rendered.

3. Inject Headers

Use tools like:

```
curl -H "X-Forwarded-Host: evil.com'><script>alert(1)</script>" https://target.site/
```

Or configure Burp Suite’s Repeater to automate different payloads.

4. Test Cache Behavior

- Vary your Accept and Accept-Encoding headers.

- See if poisoned responses persist across requests.

- Use Cache Deception techniques to store malicious output for other users.

5. Monitor CDN URLs

CDNs like CloudFront or Fastly sometimes cache HTML pages based on header combinations a perfect opportunity to exploit Web Cache Deception.

### Lessons for Developers

- NEVER trust headers like X-Forwarded-Host without sanitizing or allowlisting.

- Avoid using .html_safe unless you are 100% sure the input is clean.

- Use content encoding libraries (like sanitize() in Ruby or Django’s escape()).

- Audit CDN and cache behavior: Make sure dynamic content is never cached without checking headers.

- Test template outputs: Especially URLs, fonts, preload links etc.

### Final Thoughts

This bug is a powerful reminder that even headers can carry dangerous payloads and when combined with cache behavior the impact multiplies.

Thanks to responsible disclosure by bobrov the issue was patched across Discourse instances. A simple XSS turned into a multi instance stored like vulnerability because of careless header handling and template rendering.

- Hunter: bobrov

- Report ID: #394016

- Bounty Earned: $256

>

Happy Hunting!Monika☕

---
