# :globe_with_meridians: DVWA Reflected XSS (ALL LEVELS). Low, Medium and High

---

# DVWA Reflected XSS (ALL LEVELS)

### 1. Low

Enter your name into the input field and observe the application’s behavior.

The input is directly reflected in both the URL and the page output beside “Hello”.

View it’s source by selecting “View Source” in the bottom-right corner.

Observe that the application simply echoes back the user-supplied input without any sanitization or encoding.

Inject the following payload into the input field:

```
<script>alert(1)</script>
```

Result: A JavaScript `alert` is successfully executed, confirming the application is vulnerable to reflected XSS at this level.

### 2. Medium

View the source code.

Observe that this time our previous payload won’t work because the application includes a filter that removes `<script>` tags.

## Get Chris Christian’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Since javascript is not a case sensitive language, we can bypass this filter by mixing uppercase and lowercase letters in the tag:

```
<scRipt>alert(1)</Script>
```

Result: The alert executes successfully, demonstrating that the blacklist-based filter is insufficient.

### 3. High

View the source code.

At this level, the application applies a regex-based replacement that strips variations of `<script>` tags, including obfuscated ones (e.g., `<ScRiPt>`, `<sCrXXXipt>`, `<s c r i p t>`).

Since the filter specifically targets `<script>` tags, we must craft a payload that does not rely on them.

Use an alternate injection vector, such as an image element with an error handler:

```
<img src=x onerror=alert(1)>
```

The invalid image source (`x`) triggers an error, which in turn executes the `onerror` JavaScript handler.

Result: The alert is executed successfully, confirming that the application remains vulnerable despite the regex filter.

---
