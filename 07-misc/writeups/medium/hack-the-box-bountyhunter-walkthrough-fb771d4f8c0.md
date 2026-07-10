# :game_die: Hack The Box - BountyHunter Walkthrough

---

After, inserting this payload, We will get the db.php file content.

*`source: base64decode.org`*

Here, we can get the password. Now, we will try to login with the SSH for admin user and we failed and then we see that there is a user called development. Now, we will try to login with development

*SSH login*

Yes, we got the user flag now and now we will try to get the root flag.

## Get Sudhakar Muthumani’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

By trying `*sudo -l*` we get the following error,

*sudo -l*

Here, the `*/usr/bin/python3.8 /opt/skytrain_inc/ticketValidator.py*` have root privilege. So, we are doing privilege escalation now. By reading the code we understood there is a ticket generated for every failed attempts. We will try to get root with the following file called root.md

The root.md file looks like,

```
# Skytrain Inc
## Ticket to root
__Ticket Code:__
102 + 10 == 112 and __import__(‘os’).system(‘/bin/bash’) == False
```

*File: root.md*

Now, try to run the root.md file in the `*ticketvalidator.py*` .

*root*

Now, we got root access and we will go to root directory to get the root flag.

Follow me on:

>

Instagram: [https://www.instagram.com/sudhakar_._m/](https://www.instagram.com/sudhakar_._m/)

Facebook: [https://www.facebook.com/sudhakarmuthumani00](https://www.facebook.com/sudhakarmuthumani00)

Twitter: [https://twitter.com/Sudhakarmuthu04](https://twitter.com/Sudhakarmuthu04)

Linkedin: [https://www.linkedin.com/in/sudhakarmuthumani/](https://www.linkedin.com/in/sudhakarmuthumani/)

---
