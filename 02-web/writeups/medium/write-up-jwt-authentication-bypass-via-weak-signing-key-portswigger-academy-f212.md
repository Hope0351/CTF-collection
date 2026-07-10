# :globe_with_meridians: Write Up Jwt Authentication Bypass Via Weak Signing Key Portswigger Academy F212

---

## The malicious payload

With the signature key known, I can create my own arbitrary tokens. I store the key in the key store of the `JWT Editor`. It needs to be base64-encoded which can be done in Burp decoder or on the command line with `echo -n 'secret1' | base64`:

*Storing the secret key for further use*

I request the `/admin` page with my normal user account and receive the expected `Admin interface only available if logged in as an administrator` message. This request I send to Burp Repeater.

## Get Frank Leitner’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

The payload only contains the username and no privileges or roles. So as a first attempt I try to use `administrator` as my username. In the payload, I change the `sub` value to `administrator` and re-sign the token with the signing key that I stored above.

The result looks promising as it references me as `administrator`:

*Manipulation of JWT in the request*

Now that I know that the JWT is correct for `administrator`, I replace my session cookie with this manipulated token. That way, I do not need to modify the requests but can work directly in the browser:

I reload the `/admin` page in the browser. Instead of the error message I received earlier, I am greeted with the user management:

After clicking on the `Delete` link for user `carlos`, the lab updates to

---
