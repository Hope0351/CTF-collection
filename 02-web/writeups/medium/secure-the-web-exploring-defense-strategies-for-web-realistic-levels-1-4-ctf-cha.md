# :globe_with_meridians: Secure the Web: Exploring Defense Strategies for Web Realistic Levels 1–4 CTF Challenges

> **Original Source:** [Secure the Web: Exploring Defense Strategies for Web Realistic Levels 1–4 CTF Challenges](https://infosecwriteups.com/secure-the-web-exploring-defense-strategies-for-web-realistic-levels-1-4-ctf-challenges-993189e6600)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Secure the Web: Exploring Defense Strategies for Web Realistic Levels 1–4 CTF Challenges


*Created by Lexica*

## World of Peacecraft / Realistic


Accessing the Email Account:


Begin by logging into the target’s email account using the provided email address.


Exploring the Inbox:


Once logged in, navigate to the inbox to check for relevant emails. Look for any emails related to World of Peacecraft. Investigating the “World of Peacecraft: Activate Account” Email: Identify an email titled “`World of Peacecraft - Activate Account`" and open it. A message directing the user to a specific website in order to activate their account can be included inside the email. Keep a record of the given URL since you'll need it later to activate the account.


Checking the Trash Folder:


Navigate to the trash folder within the email account. Look for any discarded emails that may contain valuable information. Identify an email titled “`uStudio - Password Request`" and open it. Revealing the Password: Inside the "`uStudio - Password Request`" email, there will be a message indicating that the password has been requested. Take note of the revealed password, which is mentioned in the email. In this case, the password is "`iamgod`." Ensure to delete this email from the trash folder to minimize traces of the compromise.


Logging into the World of Peacecraft Account:


Return to the “`World of Peacecraft - Activate Account`" email. Click on the provided link, which will take you to a page prompting for the password. Enter the password obtained from the "`uStudio - Password Request`" email, which is "`iamgod`." Submit the password.


Account Access:


If the provided password is correct, you will successfully gain access to the target’s World of Peacecraft account. At this point, you can explore the account, gather information, or perform any necessary actions.

## Library Gateway / Realistic


Accessing the Library Gateway:


Upon accessing the provided link, we are presented with the Library Gateway page. It informs us that we are not currently logged in and provides a link to proceed with the login process.


Exploring the Login Page:


The login page is reached by clicking the “Login” link. In order to continue, we must enter the necessary information in the part that asks for our login and password.


Analyzing the Web Source Code:


We look through the web source code of the login page to find any possible hints or concealed data. By doing a right-click on the page and choosing “`View Page Source`" or a comparable option, depending on the online browser, we may accomplish this.


Searching for Clues:


Within the web source code, we perform a search for relevant keywords like “`password`" to identify any potential hints or variables associated with the login process.


Discovering a Relevant Code Snippet:


During the search, we come across a line of code that catches our attention: “`URL= "members/" + username + " " + password + ".htm";`". This code indicates that the login credentials might be used to form a URL that leads to a specific page.


Accessing the New Page:


By entering the modified URL, we open a new page associated with the provided login credentials. We carefully examine the content on this page, looking for any additional clues or information that might help us progress further. “`https://defendtheweb.net/extras/playground/real/2/members`”


Identifying the Correct Credentials:


After trying multiple combinations of usernames and passwords, we discover that the correct login credentials are “`librarian`" as the username and "`sweetlittlebooks`" as the password. By inputting these credentials, we gain access to the restricted sections of the Library Gateway.

## Princess slag / Realistic


Exploring the Initial Page


Upon loading the challenge, we encounter a message from “`Princess slag`" requesting assistance in obtaining the login details. We click the provided button labeled "Princess slag" and are taken to a new page with a link saying "`here it is`."


Investigating the Login Page


Upon clicking the “`here it is`" link, we are directed to a login page. Since we don't have any credentials yet, we need to explore alternative avenues to access the desired information. To do this, we go back to the previous page to examine it more closely.


Searching for Contact Information


## Get Ahmet Talha Şen’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


On the “`Princess slag`" page, we notice a line mentioning a contact email: "`Mail: princess@kingdom.far.away`". We decide to give it a try and use this email as the login credential, but unfortunately, it doesn't grant us access.


Analyzing the URL and Source Code


With no success from the previous attempt, we shift our focus to the URL and the source code of the page. Opening the web source, we search for any potential hints or vulnerabilities. At this point, we try modifying the URL in various ways to see if it leads us to new information.


Manipulating the URL


After several unsuccessful attempts, we decide to modify the URL by replacing a part of it. We try changing the URL to “`https://defendtheweb.net/extras/playground/princess-slag/?p=%00`". To our surprise, the page content changes, displaying the message "`Warning: file_get_contents() [function.file-get-contents]: failed to open stream: No such file or directory in pages on line 22`".


Exploiting the Vulnerability


The altered URL suggests that there might be a vulnerability related to file inclusion. With this newfound knowledge, we continue manipulating the URL to further exploit the vulnerability. We attempt the URL “`https://defendtheweb.net/extras/playground/princess-slag/?p=../admin.php%00`" to see if it leads us closer to our goal.


Accessing the Login Section


Success! The modified URL takes us to a page where the login section is revealed.


```
<?php
session_start();
if(isset($_GET['password'])){
if($_GET['password'] == 'f3bea12747'){
echo "Correct password";
} else {
echo "Incorrect password";
}
}
?>
```


Obtaining the Login Details


From the source code snippet, we can see that the login is validated based on a password parameter provided in the URL. The correct password to gain access is revealed to be “`f3bea12747`". Armed with this information, we can proceed to log in using the discovered password and gain access to the desired login details.

## Xmas ’08 / Realistic


Exploring the Website:


Upon accessing the website, we encounter three main sections: “`About Santa`", "`Write to Santa`", and "`Top Letters`". These sections provide crucial information and functionalities for our investigation.


Analyzing “About Santa”:


In the “`About Santa`" section, we find a letter supposedly written by Santa Claus. While this information may seem irrelevant at first, it's always essential to examine every element of a CTF challenge for potential clues or hidden messages.


Examining “Write to Santa”:


Moving on to the “`Write to Santa`" section, we discover a form that prompts us to provide our name, email, and message. Although this seems straightforward, we should remain vigilant and consider if there are any vulnerabilities or ways to exploit this input.


Investigating “Top Letters”:


Next, we explore the “`Top Letters`" section, where three names are displayed along with view URLs. Clicking on one of these URLs opens a new page containing some credentials. This finding suggests that we may need to utilize these credentials later on in the challenge.


Exploiting a Vulnerability:


During our exploration of the various pages and interactions, we stumble upon a potential vulnerability. By examining the URLs associated with form submissions, we discover a URL like “`https://defendtheweb.net/extras/playground/xmas08/mod.php?submit`". Intrigued, we manipulate the URL by removing the "submit" part, resulting in "`https://defendtheweb.net/extras/playground/xmas08/mod.php`".


The “Alternative Homepage”:


At this point, we encounter the “`Alternative Homepage`" option within the CTF challenge. However, when we click on it, we are presented with a simple note or message. While this may initially seem like a dead-end, it's important to thoroughly analyze the provided information, as even the smallest details can be significant in CTF challenges.


Gaining Unauthorized Access:


Attempting to access the modified URL, we encounter a login prompt that requires a username and password. Here, we can employ a technique called SQL injection (SQLi) to bypass authentication. By inputting “ `OR 1=1`" in both the username and password fields, we trick the system into granting us unauthorized access.


Modifying the Homepage:


Having successfully gained access to the protected area, we are presented with an option to “`Open file`" and "`Save`." To alter the homepage, we select "`Open file`" and provide the file name as "`index.php`". This opens the file in an editor where we can manipulate its content.


Injecting the Alternative Homepage:


To achieve our objective of replacing the original homepage, we delete the existing code within the editor. Next, we copy the source code from the “`Alternative Homepage`" provided in the CTF challenge and paste it into the editor. Finally, we save the changes.


Completing the Challenge:


With the modified homepage now in place, we have successfully completed the CTF challenge. The scam website that falsely claims to make children’s dreams come true is exposed, and our alteration ensures that visitors will be greeted with the alternative version of the homepage instead.

---

*Originally published on [Medium](https://infosecwriteups.com/secure-the-web-exploring-defense-strategies-for-web-realistic-levels-1-4-ctf-challenges-993189e6600). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
