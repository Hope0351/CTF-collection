# :globe_with_meridians: When XML Turns Dangerous: Protecting Your Systems from Direct XXE Attacks

---

# When XML Turns Dangerous: Protecting Your Systems from Direct XXE Attacks

## Understanding Direct XXE: What’s Happening?

Direct XXE attacks exploit the way XML parsers handle external entities. When an XML document includes an external entity declaration, the parser fetches the referenced resource — a file, a web address, or even another service. If the parser doesn’t explicitly block this behaviour, attackers can access sensitive files, steal data, or perform unauthorized actions.

## How Direct XXE Works: A Step-by-Step Breakdown

### Scenario: MegaBank’s Screenshot Feature

MegaBank offers a feature allowing users to send a screenshot of their current account page to customer support. The feature involves the following steps:

User Interaction:

- The user clicks the “Send Screenshot” button on the MegaBank web page.

- The browser fetches the visible HTML content of the page.

Serialization:

- The browser serializes the HTML content into XML format using JavaScript. The content of the `#content` div is serialized into a string representation of XML using `XMLSerializer`.

Sending the XML:

- The serialized XML content is sent via an HTTP POST request to the server. This request is used `XMLHttpRequest` to send the serialized content to the endpoint `/screenshot`.

Server-Side Processing:

- On the server side, the XML is parsed and processed (e.g., converting it into a JPG image to send to customer support).

However, this process is vulnerable to Direct XML External Entity (XXE) injection, which can allow attackers to manipulate the XML content sent by the client to exploit the server’s XML parser.

## How Direct XXE Works

### 1. Client-Side (Attacker’s Input)

- The attacker injects an XML payload into the page content (`#content`) before sending it to the server.

- This is done by manipulating the client-side code using JavaScript, which sends the malicious XML to the server.

### 2. Sending Malicious XML Data

- The attacker sends the malicious XML to the server via an HTTP POST request. This is done by invoking the `screenshot()` function, which sends the serialized XML as form data to the server.

### 3. Server-Side (Vulnerable XML Parsing)

- The server receives the XML data via the `/screenshot` endpoint and parses it.

- If the server’s XML parser does not have protection mechanisms in place (e.g., disabling external entities), it will attempt to resolve the `xxe` entity.

- In this case, the parser will read the contents of the `/etc/passwd` file, which may contain sensitive information.

### 4. Exploiting the Vulnerability

- If the server does not disable external entity resolution or validate the XML input properly, it may access the contents of the `/etc/passwd` file or other sensitive files on the server.

- The attacker can exploit this to read the contents of critical system files or even initiate further attacks.

### 5. Potential Consequences

- Sensitive Data Exposure: The attacker could access sensitive system files, such as `/etc/passwd` (which may contain system user information).

- Server Compromise: If the attacker gains access to internal files, they may further exploit the system, potentially leading to remote code execution or privilege escalation.

- Information Disclosure: The attacker could use XXE to make internal network requests, potentially disclosing information about the internal infrastructure or services.

Direct XXE attacks are a significant security risk, especially when XML parsers are not configured properly. In the case of MegaBank, an attacker could exploit a vulnerability in the screenshot feature by injecting a malicious XML payload. By understanding the full flow of the attack — from the client-side injection to the server-side exploitation — developers can take steps to secure their applications and prevent these types of attacks. Disabling external entity processing on the server side and sanitizing inputs are critical steps to mitigate the risks associated with XXE.

## Direct XXE Vulnerabilities

This guide delves into the technical, code-centric understanding of XXE vulnerabilities, the logic behind each attack, mitigations, and their effectiveness across platforms such as Linux, Windows, Android, and websites. Each section provides practical examples and explains why specific approaches work.

## Sensitive Data Exposure via XML Parsing

Sensitive data exposure occurs when an attacker is able to access and extract confidential information from a system, often through insecure processing of data formats like XML. In the case of XML, improper handling of external entity references can lead to unintended disclosure of sensitive system files or data.

## How Sensitive Data Exposure Happens

XML parsers read and process XML files, but some parsers allow the inclusion of external entities. These entities act as references within the XML document, instructing the parser to fetch data from an external source (such as local system files or remote URLs). If the parser is not properly secured, it will follow these references without validating their legitimacy. This can result in security vulnerabilities, particularly in the case of XML External Entity (XXE) attacks, where attackers can exploit this behavior to access sensitive files, execute arbitrary code, or leak private information.

### Example of Sensitive Data Exposure

Consider the following scenario:

- On Linux, system files like `/etc/passwd` contain sensitive information such as usernames and passwords.

- On Windows, files such as `C:\Windows\System32\config\SAM` store crucial system and user information.

An attacker could craft an XML payload that instructs the parser to retrieve these sensitive files and send them to an external server controlled by the attacker.

### Why This Happens

- External Entity References: Many XML parsers support the use of external entities, which can point to files or resources outside the XML document itself. For instance, an entity could reference the file path `/etc/passwd` on a Unix-based system.

- Lack of Input Validation: If the XML parser does not properly validate or restrict external entity references, it can inadvertently access sensitive local files or execute system-level commands, exposing confidential data.

### Mitigation Strategies

To prevent sensitive data exposure, XML parsers should be securely configured to disable external entity processing. Additionally, input validation and access control measures should be enforced to prevent unauthorized access to sensitive resources.

## Get Scaibu’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

By following best practices, such as disabling external entities and ensuring strict validation, applications can protect against sensitive data exposure through XML-based attacks.

- DOCTYPE Declaration: The `<!DOCTYPE>` declaration defines the structure and rules for the XML document. Inside this declaration, the attacker defines an external entity called `xxe`.

- Entity Definition: The entity `xxe` is defined using the `SYSTEM` keyword, which tells the XML parser to fetch the content of the file located at `file:///etc/passwd`. This is a commonly used file on Unix-based systems that contains user account information.

- Entity Reference: In the `<data>` element, the `&xxe;` reference is included. The parser, upon processing the XML, will replace `&xxe;` with the content fetched from the `/etc/passwd` file.

- Result: When the XML parser processes this document, it retrieves the contents of `/etc/passwd` and inserts it into the XML output, effectively exposing sensitive system data.

### How to Prevent This

In Java, you can configure the XML parser not to follow external entities.Why This Works:

- Disabling Entity Features: This stops the parser from fetching anything outside the XML file itself.

- Secure Defaults: The parser only processes what’s explicitly allowed.

## Denial of Service (DoS) Attack in XML Parsing

A Denial of Service (DoS) attack occurs when an adversary intentionally overwhelms a system’s resources, such as memory or processing power, causing the system to crash or become unresponsive.

### XML Entity-based DoS Exploits

In the context of XML processing, DoS attacks can be executed by exploiting XML entities. Malicious actors can craft entities that lead to uncontrolled expansions or recursive loops, which consume excessive system resources. A prominent example of this type of attack is the Billion Laughs Attack.

### XML Entities Overview

An XML entity is a symbolic name that represents data or a value. It is typically defined within an XML document and referenced throughout the document. For example, an entity like `&lol3;` would be expanded to a large block of text during XML parsing.

### Attack Execution

- Entity Expansion: During XML parsing, the parser resolves an entity reference (e.g., `&lol3;`) by substituting it with a large predefined block of text. If the entity expansion is large enough, it can result in significant memory consumption.

- Recursive Entity References: The risk escalates when entities reference each other circularly or recursively. In such cases, the parser repeatedly resolves the entities, leading to exponential growth in memory consumption. This recursive expansion continues indefinitely, eventually exhausting system resources and leading to a crash or freeze.

Such behaviour poses a significant security risk, particularly when processing untrusted or malformed XML data. It is critical to implement safeguards, such as entity expansion limits and depth controls, to mitigate the potential for such attacks.

### How to Prevent This

In Python, you can use the `defusedxml` library to stop dangerous entity expansions.

Why This Works:

- defusedxml automatically blocks entity expansions and DTD processing.

- It ensures the parser processes only the actual XML data.

## Remote Code Execution (RCE) via XML Parsing

Remote Code Execution (RCE) is a critical security vulnerability where an attacker exploits a system’s XML parser to execute arbitrary system commands. This can lead to severe consequences, such as unauthorized access, data theft, or even system compromise.

### How RCE Vulnerabilities Manifest in XML Parsers

Attackers can exploit vulnerabilities in XML parsers by injecting malicious payloads that trigger the execution of harmful system commands during XML document parsing. These commands could include actions like deleting files, stealing sensitive data, or executing arbitrary code.

### Mechanism Behind RCE Attacks

- Special Protocols in XML Parsers: Some XML parsers support special protocols or schemes that allow the execution of external system commands during parsing. One such example is the expect:// protocol, which enables the parser to execute commands and return their output.

- Command Injection: If an attacker can inject a payload that leverages such protocols, they can exploit the parser to run system-level commands. This is particularly dangerous when the XML parser has access to privileged system resources.

To prevent RCE attacks, it is crucial to disable or restrict the use of insecure protocols (e.g., expect://) in XML parsers and ensure that input is validated to prevent unauthorized command execution. Proper security controls, such as input sanitization and the principle of least privilege, should be enforced in environments that process XML data.

### How to Prevent This

In JavaScript, you can configure the parser to ignore all entities.

Why This Works:

- Ignoring Entities: The parser treats entities like plain text, not commands or references.

- Safe Parsing: This ensures no harmful code is executed.

## Data Exfiltration via XML Parsing

Data exfiltration refers to the unauthorized transfer of sensitive data from a target system to an external server controlled by an attacker. In the context of XML parsing, this attack occurs when an attacker manipulates the parser to extract and send sensitive data to a malicious destination.

### How Data Exfiltration Happens

Attackers exploit external entities in XML documents to retrieve remote URLs, which can be crafted to exfiltrate sensitive data. By injecting malicious payloads, attackers trick the XML parser into appending sensitive data (e.g., files from the system) to external requests, thereby redirecting the data to a server they control.

- Entity Definition: The entity `exfil` instructs the XML parser to fetch the remote URL (`http://attacker.com/steal`).

- Query Parameter: The URL includes a query parameter that appends the contents of the `/etc/passwd` file as part of the request, which contains sensitive information about system users.

- Data Theft: The attacker’s server receives the stolen file data from the compromised system.

### How to Prevent Data Exfiltration

To mitigate the risk of data exfiltration, XML parsers must be configured to block external entity processing. Below is an example of how to disable external entities in an Android application using the `XmlPullParser` library.

### Why This Works

- Disabling DTD Processing: By disabling Document Type Declaration (DTD) processing, external entities are prevented from being fetched or processed. This ensures that the parser cannot make requests to external servers or access sensitive system files.

- Controlled Parsing: The parser processes only safe, local XML content, mitigating the risk of malicious exfiltration attempts through remote entities.

This approach helps secure applications from data exfiltration by eliminating the ability for the XML parser to access remote resources during processing.

## XXE Attack in Content Management Systems

- In 2017, a widely-used Content Management System (CMS) faced a significant XML External Entity (XXE) vulnerability that allowed attackers to exploit the system through malicious XML file uploads. This vulnerability had severe consequences for the company involved, exposing sensitive data and leading to reputational and financial damage.

## How the XXE Attack Was Executed

- File Upload Mechanism: The CMS allowed users to upload XML files for document processing. These files were parsed and processed by the CMS server to extract and display information or to generate documents. However, the parser used by the CMS lacked proper configuration to restrict external entity references, a common security misconfiguration in XML parsers.

- Exploiting the Vulnerability: Attackers crafted malicious XML files that included external entities. These entities instructed the XML parser to fetch sensitive local files, such as `/etc/passwd` on Unix-based systems, which contain critical user information.

- Malicious Upload: The attacker uploaded the malicious XML document through the CMS’s file upload functionality. Since the XML parser in the CMS didn’t have protection against external entities, it processed the malicious XML and attempted to retrieve sensitive files from the system.

- Data Exposure: Once the parser processed the entity reference, it fetched the content of the `/etc/passwd` file and included it in the XML output. This allowed the attacker to extract sensitive system files, leading to the exposure of user data and other confidential information.

## Consequences of the XXE Attack

- Reputational Damage: The CMS vendor suffered a significant loss of trust. Customers expect such platforms to provide strong protection for their sensitive data. The breach led to negative publicity and a damaged reputation.

- Legal and Financial Consequences: The exposed user data potentially included personally identifiable information (PII), leading to lawsuits from affected customers and regulatory bodies. The company faced legal actions related to data privacy violations, resulting in substantial financial penalties and legal costs.

- Operational Disruption: The vulnerability caused operational disruption, forcing the company to temporarily halt services to patch the system and secure the XML parser. This downtime led to lost business opportunities and customer dissatisfaction.

## Why This Happened

- The primary cause of this vulnerability was the lack of proper input validation and the failure to disable external entity processing in the XML parser. Many XML parsers, by default, support external entities, which can be exploited to access local files or external resources. In this case, the CMS failed to configure the parser securely, leaving the system vulnerable to XXE attacks.

## XXE Attacks in Other Systems

XXE vulnerabilities have been a recurring issue across different systems over the years. A few notable historical examples include:

- 2005 — Apache Xalan: Apache Xalan, a popular XML parser, suffered from an XXE vulnerability that allowed attackers to exploit external entities and gain access to local files. This vulnerability was part of the larger issue of insecure XML parsing in many early web applications.

- 2012 — Drupal: Drupal, a widely-used content management framework, was found to have an XXE vulnerability in its handling of XML files. Attackers exploited this to retrieve sensitive information from the server, such as database credentials and configuration files.

- 2014 — eBay: eBay, the global e-commerce giant, was reported to have been affected by an XXE vulnerability in its search engine component, which could allow attackers to access private user data by manipulating XML-based requests.

These historical examples highlight the ongoing risks associated with improper XML parsing, particularly in systems that allow external entities. They demonstrate how XXE vulnerabilities have been exploited to access sensitive data, often leading to significant financial and reputational damage.

## Final Thoughts

In the world of cybersecurity, there are no silver bullets. Every application, feature, and component must be carefully designed with security in mind. By understanding the nuances of XXE attacks, implementing protective measures, and maintaining a proactive approach, we can ensure that our systems stay safe from potential exploits. As technology evolves, so too must our commitment to safeguarding the digital landscape, one secure line of code at a time.

In conclusion, the fight against XXE attacks is not just about fixing vulnerabilities — it’s about fostering a culture of security-first development, where the potential risks of every feature are weighed, and defense mechanisms are seamlessly integrated into every phase of the project. By taking the necessary steps now, we can protect our applications, our data, and ultimately, our users from the quiet dangers lurking within XML processing.

---
