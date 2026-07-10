# :globe_with_meridians: Story of a really cool SSRF bug.. Hello all! My name is Vedant, also…

> **Original Source:** [Story of a really cool SSRF bug.. Hello all! My name is Vedant, also…](https://infosecwriteups.com/story-of-a-really-cool-ssrf-bug-cf88a3800efc)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Story of a really cool SSRF bug.


Hello all! My name is Vedant, also known as Vegeta(on [twitter](https://twitter.com/_justYnot)). I’m a cybersecurity enthusiast and a bug bounty hunter. This is my first write-up of 2021. This write-up is about a [SSRF](https://portswigger.net/web-security/ssrf) vulnerability that allowed me to access the AWS metadata of the target company. So let’s get started,


### Little bit about the target:-


The target web app was like a social media platform with lots of functionalities. Let’s assume it as www.target.com

### The discovery:-


As the target had lots of functionalities I decided to test the main web app first rather than doing any recon. So I fired up burp suite and added the target to scope and started to spider the web app. While the spider was running I began to test different functionalities of the web app. I tried to find different vulnerabilities such as XSS, IDORs, SQLi, rate limit attacks, business logic errors etc. for about 2 hours but no luck :(


I was just about to give up on that target and then suddenly remembered that I started to spider the web app so I went to the target tab in burp, there were a lot of pages crawled and lots of new parameters. Then I started to search for interesting parameters and after about 5 minutes I got the following request:-


*GET /proxy/proxy.php?url=some_URL*


After seeing that request I immediately fired up the burp collaborator, generated a payload and entered it in the url= parameter and sent the request. And I got the callback request in the burp collaborator with both DNS and HTTP request. I was really happy at this point.


## Get Vedant Tekale’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Then I tried to access the localhost(127.0.0.1) and /etc/passwd file but this time I got nothing in response. So I copied the IP which I got from the burp collaborator and used Whois and dig commands on it and got to know that the IP belonged to the target company’s AWS instance. So this time I tried to access the IP 169.254.169.254 which is used in Amazon EC2 and other cloud computing platforms to distribute metadata to cloud instances. So I made following request:-


GET /proxy/proxy.php?url=`*http://169.254.169.254/latest/meta-data*`


And got the following response:-


After that I tried to access the AWS secret access key to show the impact of this SSRF and made the following request:-


GET /proxy/proxy.php?url=`*http://169.254.169.254/latest/meta-data/identity-credentials/ec2/security-credentials/ec2-instance/*`


And got the AWS secret access key in the response! And I was extremely happy with this finding!


*SSRF to AWS-metadata access.*


Then I quickly wrote a good report and sent it to the company and they fixed this vulnerability within 2 days. Unfortunately I didn’t get any bounty for this as the target company had a responsible disclosure program, but anyways I learned a lot of new things from this vulnerability and I hope you learned some new things as well :)


If you have any doubts regarding this write-up , you can contact me [here](https://twitter.com/_justYnot) .


I hope you all enjoyed reading this write-up. Until next time, good bye and happy hacking!

---

*Originally published on [Medium](https://infosecwriteups.com/story-of-a-really-cool-ssrf-bug-cf88a3800efc). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
