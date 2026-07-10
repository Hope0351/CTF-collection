# :globe_with_meridians: RCE on a Laravel Private Program. The recent Laravel CVE enables remote…

---

# RCE on a Laravel Private Program

The recent [Laravel CVE](https://nvd.nist.gov/vuln/detail/CVE-2021-3129) enables remote attackers to exploit a RCE flaw in websites using Laravel. I’ve read the [article](https://www.ambionics.io/blog/laravel-debug-rce) about the exploitation procedure using the Ignition library on Laravel. By the way this post is originally published [here](https://zdresearch.com/rce-on-a-laravel-private-program/) and I decided to put it in Medium site too.

To get started, I went through our recon database which contains the domains and subdomains of many web applications. We have built this system for bug bounty hunting:

*bug bounty database containing domains and assets*

here were roughly 526k live assets to filter for Laravel. The methodology is simple, sending out HTTP request to all assets, looking for the Laravel signature to match. [MEG](https://github.com/tomnomnom/meg) is a good tool for fetching lots of URLs. However, we run our tool which is similar to MEG:

I run the script using 20 threads, looking for status code 200 and “text/html” content type. The results are saved with the respective responses in separated directories

There are many ways to detect Laravel, I went through the following command which found several matches:

I then checked them one by one to see if they have Ignition running.

## Get Yasho’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

One interesting case was a private program we had discovered recently. Due to ethical concerns I can’t name the website/company, and as such will redact the names and URLs.

First thing I always do is check whether the web app is running on debug mode or not. There are many methods to do so. The one which is convenient for me on Laravel is sending permitted HTTP methods to endpoints ([need more information?](https://laravel.com/docs/8.x/routing)).

So I just changed the POST method to the PUT when sending credentials to the login endpoint and it returned Laravel’s debug error, confirming that the app has debug mode enabled:

You can also get Laravel’s version via the debug message, along with PHP and server OS and other extra information from displaying error messages.

Since the private program’s Laravel version was greater than 6 and it was also running Ignition, I decided to test the exploit and luckily the log file was on the default path and I could exploit it via [this exploit](https://github.com/ambionics/laravel-exploits):

However, if the log file path wasn’t on default location, I would have to brute force to guess the path or try the second method, i.e., talking to PHP-FPM using FTP.

---
