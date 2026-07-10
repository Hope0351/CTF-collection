# :game_die: Learning Cloud with HTB Business CTF 2025 - A Complete (cloud) Writeup: Part 1

> **Original Source:** [Learning Cloud with HTB Business CTF 2025 - A Complete (cloud) Writeup: Part 1](https://infosecwriteups.com/learning-cloud-with-htb-business-ctf-2025-a-complete-cloud-writeup-part-1-6188fa67219c)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2025

---

## [825 points] Dashboarded


>

TLDR:- SSRF in web application- Retrieve AWS EC2 Credentials- Use obtained credentials to access restricted endpoint


### Initial Look


At first, we are presented with a normal looking dashboard consist of several infrastructure status reports.


There’s a check status button which used to retrieve informations about the status of their infrastructure. On click, a request will be sent with cloud uri on the parameter URL. This is likely susceptible for AWS EC2 SSRF metadata leak.


### Quick IdeaAWS EC2


You see, in AWS, EC2 (Elastic Cloud Computing) refers to a web service that provides virtual servers in the Amazon Web Services. You can think of it as a virtual computer you can rent from AWS.


AWS EC2 and SSRF


Every EC2 instance has a special IP: `[http://169.254.169.254/latest/meta-data/](http://169.254.169.254/latest/meta-data/)` . If you hit this URL from inside the server, you can get: Instance info (instance ID, AWS region), IAM roles, even security credentials (temporary access keys) that you might able use for accessing other services based on its privilege. What to note is you cannot hit this IP from outside the corresponding EC2 instance.


Therefore, abusing an SSRF in this context means hacker tricks an application into making a request to the special IP, and retrieve the metadata.


*Basic concept of AWS SSRF*

### Exploit


Getting the creds


For sanity checking, we can change the url inside the request to the special IP `[http://169.254.169.254/latest/meta-data/](http://169.254.169.254/latest/meta-data/)`.


Sweet! the response showing some objects above shows that it does vulnerable. Now what we need to do is to retrieve temporary security credentials of the role attached to the instance profile by pointing the SSRF to `[http://169.254.169.254/latest/meta-data/iam/security-credentials/](http://169.254.169.254/latest/meta-data/)`.


And now we retrieve the credential owned by role APICallerRole credential by pointing the SSRF to `http://169.254.169.254/latest/meta-data/iam/security-credentials/APICallerRole`


Great! We compromised the APICallerRole credential where:

>

Access Key ID = ASIARHJ…6UUTD (starts with `AKIA` or `ASIA` for temporary creds, in this case this key is temporary creds)


Secret Access Key = F7zETSJ…bd5im (40 characters, random-looking string)


Session Token = IQoJb3JpZ…3m5AlcF1o= (long Base64-like string)


Configuring the creds


But how exactly do we gonna use the key? By configuring the keys to our machine like this:


- Install awscli ([https://docs.aws.amazon.com/cli/latest/userguide/getting-started-install.html](https://docs.aws.amazon.com/cli/latest/userguide/getting-started-install.html))

- Directly edit aws credentials configuration file


```
nano ~/.aws/credentials
```


3. Write this to the file


```
[your_profile_name]
aws_access_key_id = {obtained access key id}
aws_secret_access_key = {obtained secret access key}
aws_session_token = {obtained session token}
```


After configuring our new aws keys, we can check the validity by doing this command to check our key’s identity:


```
aws sts get-caller-identity --profile {your_profile_name}
```


Getting such response shows that our key is truly valid to the account.


Enumerating the privilege


We obtained the creds, but we don’t know this role’s permissions, and likely can’t query them directly. One way to discover them is by trial and error — several GitHub tools can help enumerate IAM permissions. My favorite tools for doing this is using [https://github.com/andresriancho/enumerate-iam](https://github.com/andresriancho/enumerate-iam).


After getting the repo cloned, I used this command


```
python3 enumerate-iam.py --access-key {your_access_key} \
--secret-key {your_secret_key} \
--session-token {your_session_token}
```


So far there are 2 privilege we can find:


- sts:get_caller_identity() which we already used before, used to tell who you are from AWS’s perspective when using a set of credentials.

- dynamodb:describe_endpoints() which used to return the DynamoDB endpoints for the current region. This privilege is rarely used in CTF cases, and usually not that much needed for normal DynamoDB operations like creating tables, inserting items, etc.


But for our knowledge, let’s find out what output the dynamodb:describe_endpoints() would gives.


```
aws dynamodb describe-endpoints --profile {your_profile_name}
```


It seems we have to specify the aws region. To find out the instance region, we can go back utilizing the SSRF by pointing it to `http://169.254.169.254/latest/dynamic/instance-identity/document`


Now we get that the region this instance is running is on `us-east-2` . Let’s specify that into our command


```
aws dynamodb describe-endpoints --profile {your_profile_name} \
--region {your_region}
```


There is no privilege or informations I can use to elevate my progress. Hence, I have to look at the other places.


The hidden API


Having a dead end, I decided to go back to the website to search for anything interesting. I saw the original url value sent by the application. `https://inyunqef0e.execute-api.us-east-2.amazonaws.com/api/status`


I visited the URL directly. It’s just a normal JSON.


Being curious, I removed the “status” part and visited `[https://inyunqef0e.execute-api.us-east-2.amazonaws.com/api/](https://inyunqef0e.execute-api.us-east-2.amazonaws.com/api/status)`


Turns out there are other endpoint “/private”. Let’s see what this endpoint can do.


At this point I’m thinking… what sort of “authentication” are we talking about? That’s where I realized, maybe it refers to [amazon signing request](https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-authenticating-requests.html#auth-methods-intro). Basically, our request will be sent with additional AWS authentication header or parameter which will be used to authenticate to the application.

*AWS signing request process (src: [https://docs.aws.amazon.com](https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-authenticating-requests.html))*


Now, who should I authenticate as when connecting to the API? Yes — with our previously obtained credentials.


*Well, to think that the credential is from a role called APICallerRole*


Searching for references, I found out that I can use [https://github.com/okigan/awscurl](https://github.com/okigan/awscurl) to support what I need to do.


After installing, here’s how I used the tool.


```
awscurl \
--service execute-api \
--region {your_region} \
--access_key {your_access_key} \
--secret_key {your_secret_key} \
--session_token {your_session_token} \
https://inyunqef0e.execute-api.us-east-2.amazonaws.com/api/private/
```


The result shows that the application successfully authenticated us, thus returning response with a complete list of data, including the flag. This is what the request looks like in burpsuite:


Hence, we completed our first chall. Yay!

### Flag


>

HTB{d4sh1nG_tHr0ugH_DaSHb04rDs}

---

*Originally published on [Medium](https://infosecwriteups.com/learning-cloud-with-htb-business-ctf-2025-a-complete-cloud-writeup-part-1-6188fa67219c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
