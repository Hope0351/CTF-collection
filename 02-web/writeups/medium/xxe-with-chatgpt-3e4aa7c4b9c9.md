# :globe_with_meridians: XXE with ChatGPT

> **Original Source:** [XXE with ChatGPT](https://infosecwriteups.com/xxe-with-chatgpt-3e4aa7c4b9c9)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# XXE with ChatGPT


## Generate Custom XXE Payloads with AI


XXE (XML External Entity) is a type of vulnerability that allows attackers to inject malicious XML code into an application. The following [ChatGPT](https://chat.openai.com/) prompts can make it easy to generate payloads for bug bounty and penetration testing.

### 1. Basic XXE


To get started, let’s start with a basic XXE payload customized for the particular XML structure used by the target web app.


Prompt:

>

Provide an example of a safe XXE payload that you can use for testing purposes for a blind XXE PoC that uses `<burp collaborator>` for the domain for the following `.xml` file and maintain the structure of the XML content:


`<insert XML>`


How it works:


- The XML document declares a new entity called `xxe` that points to a resource on the Burp Collaborator server.

- The document then references this entity in a child element.

- When the application parses the document, it will attempt to fetch the resource, which can be used to detect XXE vulnerabilities.


### 2. SVG Image File XXE


SVG (Scalable Vector Graphics) files are XML-based vector image files that can also be vulnerable to XXE attacks, just like XML files.


## Get Mike Takahashi (TakSec)’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Prompt:

>

Provide an example of a safe XXE payload that you can use for testing purposes for a blind XXE PoC that uses `<burp collaborator>` for the domain for the following `.svg` file and maintain the structure of the XML content:


`<insert XML>`


### 3. Excel File XXE


The newer Microsoft Excel `.xlsx` files can still be vulnerable to XXE attacks because they contain embedded XML files.


To modify the embedded XML file:


- Extract the contents of the `.xlsx` file.

- Edit the XML file in a text editor using the ChatGPT prompt.

- Re-zip the contents.

- Rename the `.zip` file back to `.xlsx`.


Prompt:

>

Provide an example of a safe XXE payload that you can use for testing purposes for a blind XXE PoC that uses `<burp collaborator>` for the domain for the following `sharedStrings.xml` extracted from a `.xlsx` file and maintains the structure of the XML content:


`<insert XML>`


### More Resources for XXE:

---

*Originally published on [Medium](https://infosecwriteups.com/xxe-with-chatgpt-3e4aa7c4b9c9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
