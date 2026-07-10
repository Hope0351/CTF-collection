# :globe_with_meridians: Bypassing XSS Filters: Techniques and Solutions

---

# Bypassing XSS Filters: Techniques and Solutions

In the ever-evolving landscape of web security, Cross-Site Scripting (XSS) stands as one of the most pernicious vulnerabilities. XSS allows attackers to inject malicious scripts into web pages which then run on another user’s browser. These injected scripts can lead to a variety of malicious actions, such as stealing session cookies or defacing web pages. To counteract these vulnerabilities, developers deploy multiple techniques. But as developers fortify defenses, attackers refine their techniques to bypass these security measures. This article will explore some techniques used to bypass XSS filters and how developers can stay vigilant.

## Techniques to Bypass XSS Filters

## 1. Set length limit

Technique: Attackers set a limit on the payload’s length, hoping the filter doesn’t recognize lengthy malicious scripts.

```
def filter_input(data):
if len(data) > 50: # Assuming filter has a set length limit of 50 characters
return "Data too long"
# ... further processing

# Attackers payload
payload = "<img src=x onerror=alert('XSS')>"
filter_input(payload)
```

Output: If the length of the payload is under the limit, it could bypass the filter.

## 2. Block all event handlers

Technique: Filters block all event handlers to prevent malicious scripts using them.

```
def filter_input(data):
event_handlers = ["onerror", "onload", "onclick"]
for handler in event_handlers:
if handler in data:
return "Suspicious event handler detected"
# ... further processing

# Attackers payload
payload = "<img src=x onerror=alert('XSS')>"
filter_input(payload)
```

Output: If the payload uses an event handler not in the filter’s list, it might bypass the filter.

## 3. Block some tags

Technique: Filters block certain HTML tags like `<script>` and `<iframe>`.

```
def filter_input(data):
disallowed_tags = ["<script>", "<iframe>"]
for tag in disallowed_tags:
if tag in data:
return "Blocked tag detected"
# ... further processing

# Attackers payload
payload = "<script>alert('XSS')</script>"
filter_input(payload)
```

Output: The payload will be blocked by the filter. However, if attackers use an alternative method not covered by the filter, it could bypass.

## 4. Block popup functions

Technique: Filters block popup functions like `alert()` to detect common XSS demonstrations.

```
def filter_input(data):
if "alert(" in data or "confirm(" in data:
return "Popup function detected"
# ... further processing

# Attackers payload
payload = "alert('XSS')"
filter_input(payload)
```

Output: The filter will block the payload. But innovative methods might bypass it.

## 5. Block `<`

Technique: By blocking the `<` character, filters try to stop creation of HTML tags used in payloads.

```
def filter_input(data):
if "<" in data:
return "Blocked character detected"
# ... further processing

# Attackers payload
payload = "<img src=x>"
filter_input(payload)
```

Output: The payload gets blocked. However, encoding techniques can bypass such filters.

## 6. Block `()`

Technique: Filters block parentheses, preventing function calls in JavaScript.

```
def filter_input(data):
if "(" in data and ")" in data:
return "Blocked characters detected"
# ... further processing

# Attackers payload
payload = "alert('XSS')"
filter_input(payload)
```

Output: The payload will be blocked, but alternative scripts might not be detected.

## Advanced Bypass: Base href attribute

Another sneaky method mentioned is using a payload with a base href attribute. This can result in an unexpected XSS popup, illustrating the complexity of creating foolproof XSS filters.

## Get Security Lit Limited’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Protecting against XSS attacks requires constant vigilance. Understanding how attackers might bypass filters helps developers design more robust defenses. Regularly updating security measures and being aware of the latest techniques is essential in safeguarding against these threats.

## Further Reading

- OWASP Cross-Site Scripting (XSS)

- Content Security Policies (CSP)

The information in this blog is intended for educational purposes. Security professionals should conduct thorough testing and follow best practices to ensure comprehensive protection.

---
