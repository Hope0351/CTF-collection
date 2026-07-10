# :globe_with_meridians: Understanding & Identifying Insecure Deserialization Vulnerabilities

---

# Understanding & Identifying Insecure Deserialization Vulnerabilities

This post explains the nitty-gritty of Insecure Deserialization Vulnerabilities. We will be covering basic understanding and identification., Insecure Deserialization- Vulnerability lies on the 8th spot in OWASP Top 10 Vulnerabilities-2017. It is said to be the most difficult to understand Vulnerability in OWASP Top 10.

Insecure Deserialization also was the common question that I came across frequently, in my Interviews, for InfoSec Profiles. There’s definitely a hype for this Vulnerability & if you are appearing for an interview in InfoSec, keep this in your must-to-know-list. So, now let’s get started.

### What’s the root cause behind the Vulnerability?

>

Simple Words: The application deserializes untrusted data without sufficiently verifying that the resulting data will be valid.

When developers place no restrictions on “gadget chains,” or series of instances and method invocations that can self-execute during the deserialization process (i.e., before the object is returned to the caller), it is sometimes possible for attackers to leverage them to perform unauthorized actions, like generating a shell.

### What is Serialization?

---
