 Exploiting Case-Sensitive Security Headers to Capture the Flag

 Challenge Overview

This write-up covers the solution for the CTF challenge “XSS Playground by zseano - Web (Hacker101 CTF)”.

 Description

The challenge involves identifying and exploiting various types of Cross-Site Scripting (XSS) vulnerabilities on a web page. Participants must find and execute different XSS payloads to capture the flag. The challenge is categorized as Moderate difficulty.

 XSS Types to Discover:

- 5 Reflective Cross-Site Scripting (XSS)
- 3 Stored Cross-Site Scripting (XSS)
- 2 DOM-Based Cross-Site Scripting (XSS)
- 1 CSP-Bypass Cross-Site Scripting (XSS)
- 1 Use of XSS to Leak Sensitive Information

 Issue Analysis

During testing, we examined the website's source code and identified an API endpoint in `custom.js` that appeared to handle email retrieval:

```
/api/action.php?act=getemail
```

that required an additional security header:

```
X-SAFEPROTECTION: enNlYW5vb2Zjb3Vyc2U=
```

However, requests sent via Burp Suite and cURL failed due to improper header casing handling in HTTP/2. HTTP/2 enforces lowercase headers for consistency and optimizes transmission by compressing header fields, which can lead to unintended modifications when strict case-sensitive validation is applied on the server-side.

 Why the Request Failed

- Burp Suite Issue: Burp automatically converts headers to Title Case, changing `X-SAFEPROTECTION` to `X-Safeprotection`, which caused the server to reject it.
- cURL Issue: HTTP/2 treats headers as case-insensitive and modifies them, breaking authentication.

 Solution

We resolved this issue by forcing HTTP/1.1, which preserves the exact header case. The correct cURL command is:

```bash
curl -H "X-SAFEPROTECTION: enNlYW5vb2Zjb3Vyc2U=" --http1.1 "https://52b94adfadeff85d1d161f93a34909e8.ctf.hacker101.com/api/action.php?act=getemail"
```

 Breakdown of the Fix:

1. Sending the required security header

   - Ensures the header is sent without modification.
   - Wrapping in quotes prevents syntax errors.

2. Forcing HTTP/1.1

   - Prevents header case normalization by HTTP/2.

3. Proper URL Formatting

   - Wrapping the URL in quotes ensures proper parsing by the shell.

 Flag Retrieval & Final Step

Executing the command successfully returned an email address, which was a crucial piece of information required for capturing the flag. The email either contained the flag directly or led to another step necessary for completing the challenge.

However, the retrieved flag was missing the `FLAG$` suffix. The challenge hint suggested manually appending it:

```
{'email':'zseano@ofcourse.com','flag':'^FLAG^7cf095fe3d1562a95054dedcf6960eb68559619fb3357bdf8d6ddb8b1411e6f4$'}
```

Executing the command successfully returned the flag. However, the flag was missing the `FLAG$` suffix. The challenge hint suggested manually appending it:

```
'flag':'^FLAG^7cf095fe3d1562a95054dedcf6960eb68559619fb3357bdf8d6ddb8b1411e6f4$
```

 Lessons Learned

This challenge highlights common security misconfigurations related to API authentication, particularly how case-sensitive security headers can impact request handling. By understanding these nuances, security professionals can identify potential bypasses and improve API security configurations. Additionally, it reinforces the importance of debugging HTTP request behavior when dealing with strict authentication mechanisms.

- Header case sensitivity matters in some applications, even though HTTP/2 treats headers as case-insensitive.
- Burp Suite automatically adjusts header casing, which can break certain API authentication mechanisms.
- Forcing HTTP/1.1 can help bypass header-related issues in security challenges.
- Debugging with `-v` in cURL can help identify request failures.

 Alternative Debugging Steps

If the request still fails, consider:

- Using `-v` in cURL to check request details:
  ```bash
  curl -v -H "X-SAFEPROTECTION: enNlYW5vb2Zjb3Vyc2U=" --http1.1 "URL"
  ```
- Trying `--http1.0` if HTTP/1.1 still modifies the headers.
- Checking for additional security measures (e.g., `User-Agent` restrictions, cookies).

 Visual Representation

*Below is an image showing the request and response from  terminal output:*

![image](https://github.com/user-attachments/assets/27aa791d-241c-4282-ac2b-f012c79b2a21)


 Conclusion

By identifying and bypassing the header modification issue, we successfully retrieved the flag. This challenge reinforced the importance of understanding HTTP protocol behavior and how security mechanisms can depend on seemingly minor details.

🚀 Happy Hacking!

\
\
During testing, we discovered that the email was hidden within the source code. By inspecting `custom.js`, we identified a function that retrieves the email from the following API endpoint. This was found by searching for keywords like 'email' and 'getemail' within JavaScript files, which led us to locate the endpoint inside `custom.js`.

```
/api/action.php?act=getemail
```

This request requires a specific security header to be included:

```
X-SAFEPROTECTION: enNlYW5vb2Zjb3Vyc2U=
```

This information was crucial for successfully extracting the email as part of the challenge.

