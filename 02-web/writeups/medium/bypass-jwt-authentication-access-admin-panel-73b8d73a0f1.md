# :globe_with_meridians: Bypass JWT Authentication | Access Admin Panel

---

# Bypass JWT Authentication | Access Admin Panel

Servers typically do not store the information contained in JSON web token. They simply verify and decode the token and then authenticate the user according to the data. But if the server is not properly verifying the token, then it is possible for an attacker to bypass authentication and gain unauthorized access to sensitive resources. And that’s what we are going to look in this blog.

## What is JWT?

Jason Web tokens or JWT for short are a popular way to authenticate users and authorize access to resources. JWT are made up of three parts, a header, a payload, and a signature. The header tells us what algorithm was used to create the signature. The payload contains information about the user or session, and the signature is used to check that the token has not been modified.

## What is Signature Verification?

When we use the jwt token, we need to verify the signature to make sure that the message has not been modified since it was created. This is important because we need to be sure that the user or system that send the message is who they claim to be. But the problem is some developers use a non algorithm for signature verification, which means that no signature is applied to the token. This can be a serious problem because attackers can modify the token and then resign it using the non algorithm. This can allow an attacker to bypass the authentication process and gain unauthorized access.

## Goal: Unauthorized Access to Admin Panel

Let’s see how we can bypass a JWT authentication via a flawed signature. I’m using this amazing lab from portswigger for demonstration [here](https://portswigger.net/web-security/jwt/lab-jwt-authentication-bypass-via-flawed-signature-verification). I need to create an account.

Now, I will open Burp to analyze the request. Here, you can observe the endpoint that logged me in using the username “wiener.” In the response, we are provided with a JWT token, also known as a session token. This token is subsequently used in the following requests to communicate with the server.

What I am going to do is send this request to the repeater first, and then modify the path to “/admin” and send the request again. The response clearly indicates “401 Unauthorized,” which is obvious since we are not the administrator. Additionally, the response states that the admin interface is only accessible when logged in as an administrator. Therefore, the username should be set as “administrator”.

You can also observe this tab labeled “JSON Web Token” here. I have installed the JWT Editor extension, which allows me to access this feature. I suggest downloading it too because it makes it easy to experiment with JWT tokens. By clicking on the “JSON Web Token” tab, we can view the decoded header and payload sections. Within these sections, we can identify the algorithm and the “sub” value. Currently, the algorithm is set to “RS256.” Our objective is to modify it to “none,” indicating that the token is not signed. Furthermore, we will change the “sub” value to “administrator.” As a result, the original token will be changed according to the values we modified.

Before we proceed with sending this request, let’s take a moment to understand something important. I will open a JWT decoder in my browser here. Next, I will paste the token that I copied into the decoder. Take a look: this token consists of three parts. The highlighted part in red is called the header, the pink string represents the payload, and the remaining blue string is the signature. Now, before we send this request, it’s necessary to remove the signature because the algorithm is already set to none(modified earlier).

### Why are we doing this?

Basically, it is considered good practice to remove the signature to avoid confusion, as keeping the signature as it is sometimes leads to issues and the exploitation might not work. Now, let’s return to the repeater. This time, I will send the request without removing the signature portion. As you can see, it results in a “401 Unauthorized” response, indicating that it is not functioning properly. Let’s proceed by removing the signature section from the token. Remember to retain the dot (.) as it is to prevent any JSON parsing errors.

From the above screenshot, we can see that the response is 200 instead of 401. Left Click and select show response in browser, copy link and paste it in the browser.

As evident, the authentication can be easily bypassed when the server fails to adequately verify the JWT token’s signature. If you’re interested in a practical demonstration, feel free to check out my YouTube video on this topic.

## Get Medusa’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Thank You for Reading.

Twitter: [https://twitter.com/medusa_0xf](https://twitter.com/medusa_0xf)

[AI-Powered Cyber Threat Detection and Response](https://links.swapstack.co/wk5y): SIEM and Compliance solution powered by AI, real-time correlation, and threat intelligence. Built for simplicity, reduced noise and affordability. [Learn More](https://links.swapstack.co/wk5y)

---
