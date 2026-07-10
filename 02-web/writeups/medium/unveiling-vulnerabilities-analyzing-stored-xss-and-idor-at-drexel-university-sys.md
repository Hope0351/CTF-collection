# :globe_with_meridians: Unveiling Vulnerabilities: Analyzing Stored XSS and IDOR at Drexel University System.

---

# Unveiling Vulnerabilities: Analyzing Stored XSS and IDOR at Drexel University System.

Greetings Everyone. Hope you’re all doing well. In this new write up, I will be narrating two different vulnerabilities i.e Stored XSS and Insecure Direct Object Reference (IDOR) which I found on Drexel University System. Lets deep dive onto these vulnerabilities.

About Drexel Bug Bounty: The Drexel Bug Bounty Program is an initiative created with the purpose of encouraging any users to report bugs and cybersecurity vulnerabilities to our Information Security Team. All internet-facing assets on “*.drexel.edu” domain are in scope. So we have wild card scope here i.e domains ending with ‘.drexel.edu’ are eligible for Hall of Fame and Letter of Appreciation. So, started with the basic recon, collected some vaild working subdomains using tools like knockpy, subfinder, assetfinder, cert and amass. With the long list of valid subdomains, I manually started checking each subdomains with burp proxy running background.

## Get Jeewan Bhatta’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

One of the subdomain has login/register function. I created a new account using the temporary mail, entered the required parameters. Then started checking the profile page which has alot of input parameters. I inserted one XSS payoad (“><svg/onload=confirm(document.domain);>{{7*7}}) into the first, middle and last name. Nothing happened after I clicked on save profile. There was one endpoint to find the program of our interest. So when clicked on that button, XSS was triggered. This was a stored XSS. Then, I started searching other endpoints where XSS could be triggered. After some testing, I found one feature which was getting in touch with university members. So when clicked on that, again XSS would triggered.

*Drexel Stored XSS*

After submitting this to the security team, I started testing another subdomain. I created test account and started playing with the website features. When we navigate to our profile, the URL was like target.drexel.edu/user/numericvalue. So I started changing the numeric value up and down. Upon changing the values, the profile information of the user would disclosed. I automated this process in Burp Intruder. Here the response would contain first name, last name, membership time, nickname and email address of any user of the website. When the numeric value was changed to 1, the info of admin was disclosed. I submitted the report to the security team and they fixed the issue within the weeks.

*Info of Admin*

After submitting the issue, I was acknowledge in their [Hall of Fame](https://drexel.edu/it/security/services-processes/bug-bounty/) page and received a Letter of Appreciation from CISO (Chief Information Security Officer). If you find any valid vulnerabilities on Drexel assets, you can report your submission in this [form](https://drexel.qualtrics.com/jfe/form/SV_3pZr9TzRkYDcagK). Thanks for reading till the end. You can also connect with me on [LinkedIn](https://np.linkedin.com/in/jeewanbhatta) & [Twitter](https://x.com/__jeewan_).

---
