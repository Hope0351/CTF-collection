# Plantopia



## My Solution

We login on the webpage using the provided credentials and notice that the cookie is just a base64 string.



It consists of the user, 0 and an epoch time.

As you might imagine, just changing the 0 to a 1 gives us access to the admin panel:  



The app also allows us to see the API endpoints so we know there's a an option to see the logs, to send mail and to update the settings.  



We start by updating the settings of the alert to test for command injection:  



Then we trigger the sendmail function:  



And then check the logs to get our flag:  



`flag{c29c4d53fc432f7caeb573a9f6eae6c6}`
