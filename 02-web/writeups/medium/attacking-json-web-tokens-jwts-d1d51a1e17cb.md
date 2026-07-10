# :globe_with_meridians: Attacking JSON Web Tokens (JWTs). Forge the token to gain unauthorized…

---

### Now the FUN part starts!

As discussed above to forge a token, one must have the correct keys (e.g. secret key for HS256, public and private keys for RS256) but if JWT’s configuration is not implemented correctly, then there are many ways to bypass the controls and modify the token to gain an unauthorized access.

## Basic Attacks

>

*To perform all of these attacks I will be using *[JWT_Tool](https://github.com/ticarpi/jwt_tool/)* and you can practice them using this *[Lab](https://github.com/h-a-c/jwt-lab)

### 1. None algorithm

If an application fails to verify thevalue of “alg” header, then we can change its value to “none” and this way it omits the need of a valid Signature for verification. For example:

```
// Modified Header of JWT after changing the "alg" parameter{
"alg": "none",
"typ": "JWT"
}
```

Command:

```
python3 jwt_tool.py <JWT> -X a
```

*None algorithm attack*

Here jwt_tool created different payloads to exploit this vulnerability and bypass all the restrictions by omitting the Signature section.

### 2. Change algorithm from RS256 to HS256

As I have explained above RS256 algorithm needs a private key in order to tamper the data and a corresponding public key to verify the authenticity of the Signature. But if we able to change the signing algorithm from RS256 to HS256, we would force the Application to use only one key to do the both tasks which is the normal behavior of the HMAC algorithm.

Hence, this way the workflow would convert from Asymmetric to Symmetric encryption and now we can sign the new tokens with the same public key.

Command:

```
python3 jwt_tool.py <JWT> -S hs256 -k public.pem
```

Here first I have downloaded the public key(public.pem) from the Application and then sign the token with HS256 algorithm using that key. This way we can produce new tokens and can inject payload in any existing claim.

### 3. Signature not being checked

Sometimes while fuzzing the data in the Header and Payload section, if the Application returned no error, then it means Signature is not being verified after it has been signed by the Authorization server. This way we can inject any payload in the claim and the token will always be valid.

## Get Neha Tariq’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Command:

```
python3 jwt_tool.py <JWT> -I -pc name -pv admin
```

Here as the Signature part is not being checked, therefore I can temper the “name” claim present in the Payload section and can become the “admin”

### 4. Crack the secret key

We can gain access to SECRET_KEY file via vulnerabilities like LFI, XXE, SSRF etc. but if that is not possible, then other attacks can still be made to check if the token is using any weak secret string for the encryption.

>

For this purpose, a BurpSuite’s extension called [JWT Heartbreaker](https://github.com/wallarm/jwt-heartbreaker) can be useful.

This exposure would compromise the whole security mechanism as now we can generate arbitrary tokens with the secret key.

But to ensure that the string which we got is the actual SECRET_KEY or not ? We can use the Crack feature of the jwt_tool.

Command:

```
python3 jwt_tool.py <JWT> -C -d secrets.txt
// Use -p flag for a string
```

*Cracking the valid secret key and signing a new token*

### 5. Use arbitrary files to verify

Key ID (kid) is an optional header having a string type which is used to indicate the specific key present in the filesystem or a database and then use its content for verifying the Signature. This parameter is helpful if the Application has multiple keys for signing the tokens, but can be dangerous if it is injectable because then an attacker can point to a specific file which content is predictable.

For example, “/dev/null” is called the null device file and will always return nothing, so it would work perfectly in Unix based systems.

Command:

```
python3 jwt_tool.py <JWT> -I -hc kid -hv "../../dev/null" -S hs256 -p ""
```

Alternatively, you can use any file present in the web root like CSS or JS and use its content to verify the Signature.

>

*Another solution for this challenge:*

Command:

```
python3 jwt_tool.py -I -hc kid -hv "path/of/the/file" -S hs256 -p "Content of the file"
```

---
