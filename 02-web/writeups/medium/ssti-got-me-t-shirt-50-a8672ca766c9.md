# :globe_with_meridians: SSTI gave me T-Shirt + € 50. Server side template injection

> **Original Source:** [SSTI gave me T-Shirt + € 50. Server side template injection](https://infosecwriteups.com/ssti-got-me-t-shirt-50-a8672ca766c9)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# SSTI gave me T-Shirt + € 50


>

Server side template injection


Many people 🤯 posted on Linkedin the photo of the T-Shirt they got after finding vulnerability on Achmea.


So I was 🎊 also excited to get the T-Shirt, but after some time I realized that focus on work instead of fruit🍍.


Why I say this because they accept only high severity issues. Even medium severity 😑 issues are not qualify for swag.


Even I reported one medium severity bug, I got only Hall of Fame🏆.


But I didn’t gave 🤕 up and manually tested approx 100+ domains, please check the responsible disclosure of Achmea because it contains many other domains acquired by Achmea👽.


One thing I got was a subdomain with a signup form, at first I entered <i>italic</i> in every field and when I submit. I got a email with values reflected as it is 😢.

>

Name- <i>italic</i>


Address- <i>italic</i>


Phone- <i>italic</i>


It was not 😓 vulnerable to HTML Injection(I haven’t tried any bypass, which should I because always check to bypass the filter).


## Get viperx9’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Again I checked for Hyperlink Injection, but that also not 💔worked.


Suddenly I remembered 😳 that someone in a video saying, people forget to try some 🐛 bugs. Now I entered {{7*7}} in every field and when I submitted. I got the email with details 😁👇

>

Name- 49


Address- 49


Phone- 49


I created a report and sent them. After some days I got this👇


Yes 👏 I got the T-Shirt, but I didn’t stop there. Now I know the signup form is vulnerable to SSTI, I thought 🤔 if there is any other form that will also be vulnerable, this was my guess as the developer will not write separate code for two signup forms for the same 🫡 company.


Yah 🙂 I was write, I got another subdomain with the signup form and both are same. I did the same thing as above and this time when I report it, I got Hall of Fame + T-Shirt + €50 💸


### Thank you for reading 🙏 😊

---

*Originally published on [Medium](https://infosecwriteups.com/ssti-got-me-t-shirt-50-a8672ca766c9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
