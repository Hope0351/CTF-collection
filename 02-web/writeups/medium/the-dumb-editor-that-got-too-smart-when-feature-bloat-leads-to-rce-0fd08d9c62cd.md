# :globe_with_meridians: The Dumb Editor That Got Too Smart When Feature Bloat Leads To Rce 0Fd08D9C62Cd

> **Original Source:** [The Dumb Editor That Got Too Smart When Feature Bloat Leads To Rce 0Fd08D9C62Cd](https://infosecwriteups.com/the-dumb-editor-that-got-too-smart-when-feature-bloat-leads-to-rce-0fd08d9c62cd)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## The Context: Why Does Notepad Even Have Vulnerabilities?


To understand the bug, we have to understand the history. For decades, Windows had two text tools:


- Notepad: For plain text.

- WordPad: For Rich Text Format (RTF).


Microsoft recently deprecated and removed WordPad. To fill the void for developers and power users, they began injecting new features into the modern (Microsoft Store) version of Notepad. The biggest addition? Markdown support.

## What is Markdown?


Markdown is a lightweight markup language that allows you to represent formatted text using unformatted text. For example, if you type # Hello in a Markdown editor, it renders as a large Hello header. It allows you to transport “Word-like” documents without the file size bloat of Word documents.


Crucially, Markdown supports hyperlinks. And this is where the trouble begins.

## The Vulnerability: CVE-2026–20841


The vulnerability lies in how the modern Notepad application parses and handles Uniform Resource Identifiers (URIs) within Markdown (.md) files.


When Notepad transformed from a raw text viewer to a Markdown renderer, it had to decide how to handle links. A standard link looks like this: [Google](https://google.com).


However, the researchers found that Notepad failed to properly sanitize the file:// URI scheme.

## The Mechanism


An attacker can create a malicious Markdown file containing a link that points not to a website, but to a local executable or a network resource.


*The raw content of the Markdown file, showing the unsanitized file:// URI scheme pointing to cmd.exe.*


As seen in the Proof of Concept (PoC) above, the attacker formats a link that points directly to cmd.exe.


When a user opens this .md file in Notepad, the application renders the text “POC” as a clickable link. If the user clicks it, Notepad passes that URI to the system. Because of the lack of sanitization, instead of opening a web browser, the system obeys the file:// protocol and executes the binary.


*The malicious file opened in Notepad. The Markdown renders the “POC” link as harmless clickable text.*


If an attacker uses a network path (e.g., pointing to an SMB share), they could potentially trick the user into downloading a payload or leaking NTLM hashes just by clicking the link.

## The Reality Check: Is It Really That Bad?


There is a lot of Fear, Uncertainty, and Doubt (FUD) circulating on Twitter and Reddit regarding this bug. Let’s look at the nuance.


Is this a critical “zero-click” exploit? No.


## Get Sohan Kanna’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


For this exploit to work, a specific chain of events must occur:


- The user must download a malicious .md file.

- The user must open it in Notepad (not VS Code or other default editors).

- The user must hold Ctrl and click the link.

- The Security Warning.


Contrary to some early reports claiming “silent execution,” modern Windows protections *do* trigger.


*The security warning triggered by the exploit. While it prompts the user, “warning fatigue” often leads users to click “Yes” regardless.*


As shown above, Windows attempts to warn the user that file://C:/windows/system32/cmd.exe might be unsafe. However, we all know that “Warning Fatigue” is real. Users are conditioned to click “Yes” to get to the content they want.


If the user clicks “Yes,” the command executes with the privileges of the current user.


*Successful exploitation. The cmd.exe shell is spawned directly from the Notepad process after the link is clicked*

## The Real Risk


While it requires user interaction, the risk is that this breaks the mental model of Notepad. Users treat text files as harmless. If an HR employee receives a Candidate_Notes.md file, they don’t expect it to be capable of launching a reverse shell.

## The Philosophy: The Feature Bloat Pipeline


This vulnerability highlights a massive problem in modern software development: Feature Bloat.


As mentioned in the analysis of this bug, we have reached the logical conclusion of adding features to things that didn’t need them.


- Old Notepad: A dumb window. Secure by design because it did nothing.

- New Notepad: Renders Markdown, has tabs, integrates with Copilot AI, and connects to the internet.


By adding a Markdown parser, Microsoft increased the attack surface of the application. By integrating Copilot and AI features, they normalized the behavior of notepad.exe making network connections.


From a Blue Team/Defender perspective, this is a nightmare. Five years ago, if notepad.exe tried to talk to the internet or spawn a child process, your EDR would flag it immediately as malware. Today? That’s just Notepad logging into your Microsoft account for AI assistance.

---

*Originally published on [Medium](https://infosecwriteups.com/the-dumb-editor-that-got-too-smart-when-feature-bloat-leads-to-rce-0fd08d9c62cd). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
