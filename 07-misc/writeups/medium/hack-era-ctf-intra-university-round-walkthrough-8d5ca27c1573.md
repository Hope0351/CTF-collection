# :game_die: HACK-ERA CTF — Intra University Round Walkthrough…

> **Original Source:** [HACK-ERA CTF — Intra University Round Walkthrough…](https://infosecwriteups.com/hack-era-ctf-intra-university-round-walkthrough-8d5ca27c1573)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HACK-ERA CTF — Intra University Round Walkthrough…


I recently organized a National Level Capture The Flag (CTF) Event titled *HACK-ERA CTF *under the banner of *Grafest* at *Graphic Era Deemed University.* The event brought together security enthusiasts and challenged them with real-world inspired scenarios ranging from web exploitation and OSINT to binary analysis. With participation from students across multiple departments, and states of the country. The event was both competitive and educational.


In this write-up, I’ll be walking through the solution to the Intra-University Round, breaking down the thought process behind it, and sharing insights into what made it both fun and tricky.

## Challenge 1: The Hidden Profile


Find a way to access other accounts.


*Challenge 1 : The Hidden Profile*

>

Mission Brief for Challenge 1: The Hidden Profile


You’ve recently joined a promising tech company, excited to dive into their internal dashboard. After logging in, you’re greeted by a sleek, modern interface, showcasing your profile information. The dashboard is impressive, and you can navigate through various sections with ease. One day, while checking your profile, you notice a profile icon at the top-right of the screen. Clicking it takes you to a page with your personal details — a short bio, recent projects, and more. It’s all looking good until you realize that below your information, there’s a bio that doesn’t seem to belong to you. Intrigued, you try clicking around and experimenting. Could it be possible that others’ profiles are exposed this way? Something seems off, but you’re not sure what.


NOTE: NO BRUTEFORCE ATTACK SHOULD PERFORM IF ANYONE FOUNDS TO BE DOING THAT THE INDIVIDUAL OR THE TEAM WILL BE DISQUALIFIED…


Username: vivek.kapoor
Password: vivekpass


In this CTF Challenge…you have provided with a Website named TaskMaster which contains a login page and track the activities of the employee.


First, let’s login to the portal using the username and password given in the Mission brief.


We got a dashboard where all the activities of Vivek Kapoor is monitored…This website is under developed because most of the buttons are not working properly…but after clicking on the profile icon (also mentioned in the mission brief). I got the profile of Vivek Kapoor which includes his username, email, bio, recent activities and much more….


So, Let’s fire-up the burpsuite to intercept and analyze this request. First, send the request of /profile to repeater.


And by looking at the request….You can see it is using a reg_id parameter which is used to tell the server which reg_id data I want to display….And that’s the vulnerability called IDOR (Insecure Direct Object Reference).


To confirm the vulnerability….Let’s update the value of reg_id to 1006 and click on Send.


And as you can see we got the information about user named *Meera Rathore.*


## Get Rajneesh Kumar Arya’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


And Similarly, by updating reg_id to 1004 we got our first Flag.


>

1. What is the email of Sneha Verma?


Ans: sneha.verma@infosec.org


For the second flag we need to find the reg_id of the admin user and after trying some random values we got the admin user reg_id which is 1000.


And we got our second flag….

>

2. Who is the admin user?


Answer: rajneesh_admin


And after just bit of scrolling in the response of the admin reg_id request, we got our final flag.


>

3. What is the flag? Format of the flag….FLAG{abcd}


Answer: FLAG{1d0r_vuln_3xp0s3d_admin_access}


## Challenge 2: The Last Transmission


Find a way to get the flag.


>

Mission Brief:


Late one night, you receive an encrypted email from an unknown source. The only attachment is a file named hidden_document.pdf. The message in the email header reads: “If you’re reading this, it’s already too late. Trust the layers.” — A. You open the file — it loads without error, displaying what seems to be an ordinary image inside a PDF. But something doesn’t feel right. Why would A. send just a picture? What’s the secret? Only one way to find out.


In this CTF Challenge you have provided with a PDF file which doesn’t seems like a PDF (as per mission brief)


So, to confirm its Identity let’s use file command.


And, you can see the file command reveal that this pdf is actually a JPEG file not a PDF file.


So, let’s rename this *hidden_document.pdf *to *hidden_image.jpeg.*


After renaming the image…let’s look at what this image contains using open command (which is used to open a file with a default application).


And we got the image of ELON MUSK.. which looks normal NO PIXEL DISTURBANCE…


Now, let’s see what’s the METADATA using exiftool command


And we got a password but we don’t know whose password is this?


Let’s check the FLAG inside the strings inside the image using strings command and filter out the FLAG using grep command.


Unfortunately, we got nothing inside the strings. Let’s move to the next step and check for hidden files inside the image ([Steganography](https://en.wikipedia.org/wiki/Steganography)) using steghide command. It’ll ask for the password and we already have one from METADATA.


And…..You can see we got the flag.txt file which contains the FLAG for this Challenge.


>

What is the Flag?


Answer: FLAG{n0t_4ll_pdfs_4re_wh4t_th3y_s33m}


I hope you all have enjoyed the HACK-ERA CTF Event and learn a lot of things….Stay tuned for the future CTF Events…


And if you want to practice CTF regularly join our WhatsApp Community where we do CTFs on weekly basis…[join us](https://chat.whatsapp.com/FpICNanCNH84Qkh5SUsIgH).


TILL THEN KEEP LEARNING….KEEP EXPLORING….AND MOST IMPORTANT DO HACKING….

---

*Originally published on [Medium](https://infosecwriteups.com/hack-era-ctf-intra-university-round-walkthrough-8d5ca27c1573). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
