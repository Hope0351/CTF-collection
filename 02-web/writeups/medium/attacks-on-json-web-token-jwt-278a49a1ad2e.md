# :globe_with_meridians: Attacks On Json Web Token Jwt 278A49A1Ad2E

---

In this attack, we confuse the server to use one algorithm instead of another. So here we are going to change the algorithm from *RS256* to *HS256* …

As I had explained in my previous article the RS256 algorithm needs a private key in order to tamper with the data and a corresponding public key to verify the authenticity of the signature. But if we are able to change the signing algorithm from RS256 to HS256, we confuse the server to use one algorithm instead of another. We would force the Application to use only one key to do both tasks, which is the normal behaviour of the HMAC algorithm.

*This is an RS256 signed token given by the server*

So here we are going to change the algorithm from *RS256 to HS256*. Hence, this way the workflow would convert from Asymmetric to Symmetric encryption and we can sign the new tokens with the same public key.

As this is a public key, so this key has to remain public. So you can find it by yourself on the internet or another potential source is the server’s TLS certificate, which may be being re-used for JWT operations:

command:

```
openssl s_client -connect <hostname>:443
```

Copy the “Server certificate” output to a file (e.g. *cert.pem*) and extract the public key (to a file called *key.pem*) by running:

```
openssl x509 -in cert.pem -pubkey -noout > key.pem
```

This how you can get public.pem of any host…

As for this lab, the public key is provided to us.

*Save this public key in the file named public.pem*

To change the algorithm we are again going to use the same tool named [jwt_tool](https://github.com/ticarpi/jwt_tool).

First, we will see what is the behaviour of the application with the given RS256 signed token.

*Send JWT to validate the token*

*You can see token is validated by the server*

So let’s start changing the algorithm with the tool.

Command with an example :

- To just change the algorithm we can use this command

>

`python3 jwt_tool.py <JWT TOKEN> -S hs256 -k public.pem`

Example :

```
We got HS256 Signed token:eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJodHRwOi8vZGVtby5zam9lcmRsYW5na2VtcGVyLm5sLyIsImlhdCI6MTYyNzU2MTk4OCwiZXhwIjoxNjI3NTYzMTg4LCJkYXRhIjp7ImhlbGxvIjoid29ybGQifX0.OFYOhR0sW37RdC9XBbEVR2Tao0hymeCbYc0IpiTwvVg
```

Let’s see if this token is perfectly signed or not 🤔

*We are going to send this token to validate it.*

As you can see our HS256 Signed token got validated by the server. So you are thinking of what I will do then if it got validated by the server🤔???? What’s my benefit here??🙄

Well if you can create a token by yourself then you can also modify the token, I think you got the point😌(Samaj daar ki eshara kafhi hai). I will show you some scenarios so that you can understand them well.

Example:

```
Suppose in payloads there are fields which we are can modify."admin": "false" ======> "admin": "true"
"user": "normal" ======> "user": "administrator"
"name": "Anubhav Singh" ======> "name": "Vaibhav Singh"
"email": "hacker@gmail.com" ======> "email": "victim@gmail.com"This how we can modify the values...
```

So you got an idea of what things you can modify in the payload to get privilege escalation. But how you will modify this payload??? well there are various ways for it but for this article, I am just using the same tool([jwt_tool](https://github.com/ticarpi/jwt_tool)) to modify the payload and to create a token.

>

In this case, we have to tamper with the token ,modify the payload and also we have to change the algorithm.

command :

>

`python3 jwt_tool.py <JWT TOKEN> -S hs256 -k public.pem -T`

Steps:

I have made a video for you guys to demonstrate how you can modify JSON WEB TOKEN to get this attack done.

I hope you guys have understood how you can modify the token as you need means I have shown you the way to modify the value or to add any key-value pair in the payload part of the token and at last, the algorithm gets changed to HS256.

*Modified token*

So now we have got the modified token. Let’s see this gets validate by the server or not 🤔.

*Sending token to check*

>

*You can see our modified token gets validate by server*😌.

---
