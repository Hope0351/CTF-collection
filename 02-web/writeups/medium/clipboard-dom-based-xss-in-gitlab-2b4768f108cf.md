# :globe_with_meridians: Clipboard DOM-based XSS in GitLab

> **Original Source:** [Clipboard DOM-based XSS in GitLab](https://infosecwriteups.com/clipboard-dom-based-xss-in-gitlab-2b4768f108cf)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Clipboard DOM-based XSS in GitLab


## Unveiling the Hidden Risks of Unsanitized Markdown Fields and Safeguarding Against JavaScript Exploitation


## Introduction


Cross-site scripting (XSS) vulnerabilities continue to pose significant threats to web applications, with DOM-based XSS presenting a unique challenge due to its reliance on client-side manipulation. A critical vulnerability was identified in GitLab’s Markdown text fields, where a clipboard DOM-based XSS flaw allows attackers to execute arbitrary JavaScript under a user’s credentials. This article provides an in-depth exploration of the vulnerability, its technical underpinnings, reproduction steps, impact, and mitigation strategies, offering valuable insights for developers and security professionals.

## Understanding DOM-based XSS


DOM-based XSS occurs when client-side scripts dynamically manipulate the Document Object Model (DOM) based on unsanitized user input, such as data from the clipboard. Unlike server-side XSS, the attack vector is processed entirely within the browser, making it harder to detect through traditional security measures. In GitLab’s case, the vulnerability leverages the clipboard’s `text/x-gfm-html` MIME type, enabling malicious payloads to be injected into Markdown text fields, particularly in areas like issue descriptions.

## Discovery of the Vulnerability


The flaw was uncovered in the `app/assets/javascripts/behaviors/markdown/copy_as_gfm.js` file, which handles GitHub Flavored Markdown (GFM) data on the clipboard across various GitLab components. The vulnerability arises because the `gfmHtml` variable, sourced directly from the clipboard, is assigned to the `innerHTML` property of a dynamically created `div` element without sanitization. This oversight allows attackers to inject malicious JavaScript when users paste content from a compromised source.

## Technical Analysis


The vulnerable code snippet reveals the issue clearly:


- Clipboard Data Retrieval: The `pasteGFM` function extracts `text/x-gfm-html` data from the clipboard using `clipboardData.getData`.

- Unsanitized Assignment: The `gfmHtml` value is directly set as the `innerHTML` of a `div` element, enabling the execution of embedded scripts.

- Asynchronous Processing: The transformed GFM data is then inserted into the target text field, completing the exploit chain.


This lack of input validation or sanitization creates a pathway for DOM-based XSS, where an attacker-controlled payload can execute under the user’s session context.

## Steps to Reproduce


To replicate the vulnerability, follow these steps on a testing environment:


- Set Up the Environment: Install Docker and create a new GitLab container using the provided Docker command.

- Create a Malicious HTML File: Develop an HTML file with a script that modifies the clipboard data, such as:


```
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Clipboard-XSS</title>
</head>
<body>
<h3>Try out our new clipboard plugin</h3>
<p>Copy <strong>here</strong>, paste it on the editor and see what happens!</p>
<script>
document.oncopy = event => {
event.preventDefault();
event.clipboardData.setData('text/x-gfm-html', 'XSS<img/src/onerror=alert(1)>');
console.log("updated clipboard");
}
</script>
</body>
</html>
```


3. Access the Malicious Page: Open the HTML file in a browser and copy the word “here” to the clipboard.


4. Configure GitLab: Start the GitLab container, set up the root password, and log in as the root user at `http://localhost:8080`.


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


5. Trigger the Exploit: Navigate to the “Issues” section of the “GitLab Instance / Monitoring” project, create a new issue, and paste the clipboard content into the Description textarea. An alert box should appear, confirming the XSS execution.

## Current Bug Behavior


Pasting content with the `text/x-gfm-html` MIME type triggers the execution of arbitrary JavaScript code embedded in the clipboard data. This allows attackers to perform actions within the user’s session, such as accessing sensitive data or manipulating the DOM.

## Expected Correct Behavior


Pasting content should not execute JavaScript. Instead, all clipboard data, especially `text/x-gfm-html`, should be sanitized or escaped before being assigned to `innerHTML` or other executable contexts.

## Impact


This DOM-based XSS vulnerability poses significant risks:


- Credential Harvesting: Attackers can steal session cookies or tokens to impersonate users.

- Unauthorized Actions: Malicious scripts can interact with GitLab’s JavaScript API to create issues, modify repositories, or escalate privileges.

- Data Exposure: Sensitive project data, such as issue details or commit histories, could be exfiltrated.

- Widespread Exploitation: Since the vulnerability affects multiple Markdown text fields, the attack surface is broad, impacting various GitLab functionalities.


Although GitLab’s Content Security Policy (CSP) currently mitigates exploitation on `https://gitlab.com`, the issue remains exploitable in less secure deployments or misconfigured instances.


Report ID: [1196958](https://hackerone.com/reports/1196958)

## Mitigation Strategies


To address this vulnerability, GitLab and similar applications should implement the following measures:


- Input Sanitization: Sanitize clipboard data using libraries like DOMPurify before assigning it to `innerHTML`.

- Escape HTML: Convert special characters (e.g., `<` to `&lt;`) in `gfmHtml` to prevent script execution.

- Strengthen CSP: Enforce a strict CSP to block inline scripts and unauthorized external sources.

- Validate MIME Types: Restrict or validate the `text/x-gfm-html` MIME type to ensure only safe content is processed.

- Update Codebase: Modify the `pasteGFM` function to include sanitization steps before DOM manipulation.

- User Education: Warn users about pasting content from untrusted sources.


Regular security audits and penetration testing can help identify and remediate similar vulnerabilities.

## Conclusion


The clipboard DOM-based XSS vulnerability in GitLab’s Markdown fields highlights the dangers of unsanitized client-side input processing. By exploiting the `copy_as_gfm.js` file’s handling of clipboard data, attackers can execute malicious JavaScript, posing risks to user security and data integrity. Through robust sanitization, enhanced CSP, and proactive security practices, developers can mitigate these threats, ensuring a safer environment for GitLab users and setting a standard for secure web application development.

---

*Originally published on [Medium](https://infosecwriteups.com/clipboard-dom-based-xss-in-gitlab-2b4768f108cf). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
