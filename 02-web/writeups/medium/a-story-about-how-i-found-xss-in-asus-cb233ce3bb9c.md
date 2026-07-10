# :globe_with_meridians: A Story About How I Found Xss In Asus Cb233Ce3Bb9C

---

## The Discovery

While examining the target, I noticed that the Laravel Ignition debug mode was enabled on `adam.asus.com`, and the endpoint was vulnerable to XSS. The vulnerability was exposed through the following URL:

When accessing this URL, the embedded script was executed in the user’s browser, confirming the presence of an XSS vulnerability.

## Understanding the Vulnerability

## Impact

The impact of this XSS vulnerability depends on the application’s context and the privileges of the compromised user. For example:

- Minimal Impact: In applications with public information, the impact might be negligible.

- Serious Impact: In applications handling sensitive data, such as financial transactions or healthcare records, the impact could be severe, allowing unauthorized access to private information.

- Critical Impact: If a user with elevated privileges is compromised, the attacker could gain full control of the application, affecting all users and data.

## Steps to Reproduce

To confirm the vulnerability, follow these steps:

- Access the Vulnerable URL: Open the URL in your browser: `[http://adam.asus.com/_ignition/scripts/--%3E%3Csvg%20onload=alert('cappriciosec.com')%3E](http://adam.asus.com/_ignition/scripts/--%3E%3Csvg%20onload=alert('cappriciosec.com')%3E)`

- Observe the Script Execution: The script will execute in your browser, displaying an alert with the text `cappriciosec.com`.

## Automating the Hunt

To streamline the process, I built a Python tool specifically for detecting this vulnerability. You can install it using pip and automate your testing:

## Get Karthikeyan.V’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

ToolPOC:[laravel-ignition-rxss on github](https://pypi.org/project/laravel-ignition-rxss/)

```
pip install laravel-ignition-rxss
laravel-ignition-rxss --chatid <YourTelegramChatID>
```

```
laravel-ignition-rxss -u http://mytargetprogram.com
```

```
laravel-ignition-rxss -i urls.txt
```

## Remediation

To mitigate this vulnerability, it is essential to disable debug mode by setting `APP_DEBUG` to `false` in the environment configuration. This will prevent unauthorized script execution and protect users from potential XSS attacks.

POC by: [@karthithehacker](http://twitter.com/karthithehacker)
Mail: contact@karthithehacker.com
Website: [https://www.karthithehacker.com/](https://www.karthithehacker.com/)

If you’re interested in our VAPT service, contact us at ceo@cappriciosec.com or contact@cappriciosec.com.

For enrolling my cybersecurity and Bugbounty course,

WhatsApp +91 82709 13635.

## Connect with me:

Twitter: [https://twitter.com/karthithehacker](https://twitter.com/karthithehacker)

Instagram: [https://www.instagram.com/karthithehacker/](https://www.instagram.com/karthithehacker/)

LinkedIn: [https://www.linkedin.com/in/karthikeyan--v/](https://www.linkedin.com/in/karthikeyan--v/)

Website: [https://www.karthithehacker.com/](https://www.karthithehacker.com/)

Github : [https://github.com/karthi-the-hacker/](https://github.com/karthi-the-hacker/)

npmjs: [https://www.npmjs.com/~karthithehacker](https://www.npmjs.com/~karthithehacker)

Youtube: [https://www.youtube.com/@karthi_the_hacker](https://www.youtube.com/@karthi_the_hacker)

>

*Thank you*

Karthikeyan.V

---
