# :globe_with_meridians: From image Upload to Workspace Takeover: Deconstructing a Critical Stored XSS Attack

> **Original Source:** [From image Upload to Workspace Takeover: Deconstructing a Critical Stored XSS Attack](https://infosecwriteups.com/from-image-upload-to-workspace-takeover-deconstructing-a-critical-stored-xss-attack-55d821c73b72)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# From image Upload to Workspace Takeover: Deconstructing a Critical Stored XSS Attack


*This “Image” Hacked a Company Workspace*


A seemingly harmless feature — file uploading — became the entry point for a complete workspace takeover in a recent vulnerability found in the Dust platform. This case serves as a critical reminder of how a classic Stored Cross-Site Scripting (XSS) flaw, when combined with architectural oversights, can lead to devastating consequences, including privilege escalation and full administrative control.

## The Attack Chain Unraveled ⛓️


The attack’s brilliance lay in its simplicity and ability to chain together several seemingly minor flaws into a high-impact exploit. It didn’t require complex code or password theft; it only needed one user to click one link.


*The Attack Chain: From One Click to Total Compromise*


Here’s a step-by-step breakdown of how it worked:


- Disguised Malicious File Upload: The attacker, logged in as a low-privilege member, uploaded a file named something innocuous like `xss_poc.png`. However, they manipulated the request to set the file's

- `Content-Type` to `text/html`. The system's validation checks failed to catch this mismatch, prioritizing the declared content type over the file extension.

- Same-Origin Hosting: The uploaded HTML file was hosted on the main application domain (`dust.tt`). This was the pivotal mistake. By serving user-generated content from the same origin as the core application, the platform allowed any script within that file to operate within the application's trusted security context.

- The Bait: The attacker shared the direct URL to the uploaded file with a workspace administrator. To the admin, it appeared to be just another link to an image file shared by a colleague.

- Silent Execution: When the administrator visited the link, their browser didn’t render an image. Instead, it correctly interpreted the

- `text/html` content type and executed the JavaScript embedded in the file. Because this script ran on the

- `dust.tt` domain, it automatically inherited the administrator's authenticated session.

- API-driven Takeover: The JavaScript payload was designed to silently make API calls on the administrator’s behalf. It first fetched the workspace ID and then sent a

- `POST` request to the API endpoint responsible for managing members. This request promoted the attacker's own account to an "admin" role. The action was performed seamlessly in the background, using the victim's active session, with no indication that a compromise had occurred.

## The Widespread Impact 💥


Once the attacker gained admin privileges, it was game over for the workspace’s security. They could:

*Your Browser, Their Commands*


- Escalate Privileges: Promote their own account to the highest level.

- Revoke Access: Downgrade or remove the legitimate administrators, locking them out of their own workspace.

- Access Sensitive Data: View and delete private secrets and internal data accessible only to administrators.

- Achieve Full Compromise: Take complete control over the workspace, its members, and all its data.


The attack didn’t require stealing the victim’s session cookie; it leveraged the active session directly, making it highly efficient and difficult to detect through traditional means.

## Key Security Lessons and Mitigation Strategies


This incident underscores several fundamental principles for securing modern web applications, especially those handling user-generated content.

### 1. Sandbox User Content on a Separate Domain


The most effective countermeasure is to serve all user-uploaded files from a separate, cookie-less domain. For example, if your application runs on `app.com`, user content should be served from a sandboxed domain like `app-usercontent.com`. This isolates the content, ensuring that even if a malicious script executes, it cannot access the main application's cookies or make authenticated API calls.

### 2. Enforce `Content-Disposition: attachment`


To prevent browsers from rendering files inline, always send the `Content-Disposition: attachment; filename="..."` header. This forces the browser to trigger a download prompt instead of trying to display the content, neutralizing XSS vectors embedded in files like HTML or SVG.

### 3. Validate Files by Content, Not Metadata


Never trust user-provided metadata like filenames or `Content-Type` headers. Implement server-side validation that inspects a file's actual contents (e.g., using magic bytes) to determine its true type. A file ending in `.png` should contain a valid PNG data structure, not HTML tags.

### 4. Implement a Strict Content-Security-Policy (CSP)


A well-configured CSP acts as a vital layer of defense. It can be used to block inline scripts (`script-src 'self'`) and restrict where resources can be loaded from, significantly reducing the attack surface for XSS even if a malicious file is uploaded and rendered.


## Get Abhishek meena’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


This case is a powerful illustration of why security must be approached in layers. A single point of failure — in this case, trusting and rendering a user-uploaded file in the same security context as the application — can unravel an entire system’s defenses.

---

*Originally published on [Medium](https://infosecwriteups.com/from-image-upload-to-workspace-takeover-deconstructing-a-critical-stored-xss-attack-55d821c73b72). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
