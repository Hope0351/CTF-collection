# :globe_with_meridians: eLFI already solved it, better get going #BUGCROWD Challenge Walkthrough

---

# eLFI already solved it, better get going #BUGCROWD Challenge Walkthrough

In this Write-Up, I am going to walk you through the [bugcrowd’s open challenge](https://twitter.com/Bugcrowd/status/1606016814831570989?s=20&t=aam_TPp8kFfqYfJ67bR8KQ) to hackers.

- Note: In case you’re reading this Write-Up without trying out the [challenge](https://bugcrowd-advent-challenge.herokuapp.com/login.php). I request you to first give it a try and check this blog if you’re stuck.

- Hint given: “i am eLFI”

- So, I went to this link [https://bugcrowd-advent-challenge.herokuapp.com/login.php](https://bugcrowd-advent-challenge.herokuapp.com/login.php)

3. Tried user1 and Randompassword123 as credentials that was present on the login page itself and it gave me an internal server error as shown below.

4. I tried to play around with the login.php but no luck.

5. I jumped right away to the view page source of the login.php application, went through the source code and few lines caught my attention which I highlighted below.

6. Then I remembered the Hint and tried to sync that with the above lines of code.

7. That’s how I found a vulnerable endpoint which is /style.php?css_file=custom.css8. Here, when I tried to inject a random LFI payload, it showed Hacker detected, which confirmed that style.php is the vulnerable parameter.

[https://bugcrowd-advent-challenge.herokuapp.com/](https://bugcrowd-advent-challenge.herokuapp.com/login.php)style.php?css_file=//..//..//..//etc/passwd

9. Here I guessed it is filtering out etc/passwd so I tried URL, BASE64 encoding, and double encoding, but no luck.

10. Then, I played around with the application for a while. Finally, while fuzzing the application, I observed there’s another file as index.php

11. But when I opened it, it redirected me to the login.php. But when you open the network tab you can see the index.php and the status code as 302.

12. I felt a bit suspicious about this index.php and I wanted to see what is there in it. So, I googled about it.

13. I came across this piece of code `php://filter/convert.base64-encode/resource=<filename>`

## Get Prasanth Bodepu’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

which helped me in bypassing the restriction and allowed me to view the source code of index.php

14. Finally, index.php gave me some encoded string like this.

*index.php*15. I decoded it using the below command. You can also use [cyberchef](https://gchq.github.io/CyberChef/)(You can also use burpsuite’s decoder)

echo “PD9waHAKCnNlc3Npb25fc3RhcnQoKTsKc2Vzc2lvbl9yZWdlbmVyYXRlX2lkKHRydWUpOwoKaWYgKGlzc2V0KCRfU0VTU0lPTlsidXNlciJdKSl7CiAgICBoZWFkZXIoIkxvY2F0aW9uOiBkYXNoYm9hcmQucGhwIik7CiAgICBleGl0KCk7Cn1lbHNlewogICAgaGVhZGVyKCJMb2NhdGlvbjogbG9naW4ucGhwIik7CiAgICBleGl0KCk7Cn0KCj8+” | base64 — decode

*index.php -> decoded*16. It showed me two Php files named dashboard.php and login.php

Now, I replaced the index.php with dashboard.php and it gave me the below encoded string.

*dashboard.php*17. This time I used cyberchef to decode, I found another file named sober.php in the source code.

*dashboard.php -> decoded*18. Now, I replaced the dashboard.php with sober.php and I found another encoded string

19. After decoding the string I got the below below code. Here, I found another encoded string in the multi-line comments, but this time it is small compared to the earlier encoded strings.

20. Finally, after decoding the string, I found this.

*flag*

I don’t know why, but somehow I was attracted to this challenge and took off the first half of the day from work. Thanks to you [bugcrowd](https://twitter.com/Bugcrowd) : )

The challenge seems to be very simple after reading the walkthrough, but believe me, it took me a lot of brains to think and execute it.

I thank my friend [Paweł Wąsik](https://www.linkedin.com/in/pawe%C5%82-w%C4%85sik-b526bb1ba/) for his constant support.

References:Feel free to Connect with me at-

*Photo by [Madeleine Kohler](https://unsplash.com/@mdln_khlr?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

---
