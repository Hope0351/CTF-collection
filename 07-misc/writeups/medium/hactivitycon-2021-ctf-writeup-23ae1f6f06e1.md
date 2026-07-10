# :game_die: HactivityCon 2021 CTF Writeup. OPA Secrets challenge (category: web…

> **Original Source:** [HactivityCon 2021 CTF Writeup. OPA Secrets challenge (category: web…](https://infosecwriteups.com/hactivitycon-2021-ctf-writeup-23ae1f6f06e1)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2021

---

# HactivityCon 2021 CTF Writeup


OPA Secrets challenge (category: web, level: hard)


*OPA Secrets Challenge*Step 1: On opening the challenge, a login screen would come up.


*Login Screen*Step 2: We first need to set up an account in order to access the OPA Secrets portal. So, signup with any random username and password.


*Sign Up Screen*Step 3: Now login using the credentials with which new account was created.


Step 4: On logging in, OPA Secrets dashboard will come up.


*OPA Secrets Dashboard*Step 5: There are 2 tabs on the dashboard, in the secrets tab, it gives the functionality to create and save our secrets. On visiting the Security tab, it gives us info about the algorithm that is used in keeping this secrets secure. Also a Github link is mentioned where we can see the source code of this open source OPA Secrets algorithm.


Step 6: Open the github link ([congon4tor/opa_secrets: Secret manager using Open Policy Agent (github.com](https://github.com/congon4tor/opa_secrets)) and open the *app.py *script (opa_secrets/app/app.py).


*app.py Script*Step 7: Now carefully observe the script. We can see that 3 different users have been created (congon4tor, jellytalk, pinkykoala). Each one is having thier unique id and roles assigned.


*Created users*


We can see that user with username *congon4tor *is admin while rest of 2 users are normal users. We can also see the passwords of all three users (qwerty123, test, test). But it won’t be needed to solve this challenge.


## Get hackerdevil’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Step 8: On further observing the code, we can see that 3 different secrets are also been added to respective user’s account. Each secret is having unique id.


*Secrets with unique secret ids*


We can notice that the name of first secret is Flag, which indicates that it has something to do with our target *i.e. *flag{}. Also to note that first secret’s value is not directly mentioned in clear text unlike the other 2 secrets.


Step 9: Now let’s go to the dashboard of the account that we created and create one secret and save it.


*Secret Creation*Step 10: Once the secret is created, it will show up in our dashboard. Also remember our secret would have been assingined a unique id just like other secrets were assingined (refer step 8)


*After successfull secret creation*Step 11: It can be seen that the value of our secret is masked and in order to see the secret in clear text we need to click on that *eye *button. On clicking it, it will send the request including our secret’s unique id and as a response it will receive the value of our secret.


Step 12: We need to fire up Burpsuite in order to intercept that request. Once burp is set-up, click on the *eye *button and intercept that request. In the intercepted request we can see that unique id of our secret is sent.


*Intercepted request with our secret’s unique id*Step 13: Now simply replace the id value with the id of the secret with the name Flag that we found in the *app.py *script (the one we saw in the step 8) *i.e. afce78a8–23d6–4f07–81f2–47c96ddb10cf *and forward that modified request


*Edited request with the id replaced*Step 14: In the response we will get the flag on our dashboard.


*FLAG*


flag{589882d62d1c899d8b85db1af2076b39}


This was my approach for finding the flag. Hope you find it usefull.


Thank You for reading. Knowledge is power, so keep gaining!😈


Follow me on [GitHub](https://github.com/gandhidevansh)!

---

*Originally published on [Medium](https://infosecwriteups.com/hactivitycon-2021-ctf-writeup-23ae1f6f06e1). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
