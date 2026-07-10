# :sleuth_or_spy: OSINTorg Revealed

> **Original Source:** [OSINTorg Revealed](https://infosecwriteups.com/osintorg-revealed-vulnmachines-osint-writeup-cb2cb976c1b9)
> **Platform:** infosecwriteups.com | **Category:** `OSINT`

---

# OSINTorg Revealed


## Vulnmachines OSINT writeup


### TLDR


*We will resolve VulnMachine’s OSINT challenges that involve searching social networks, gist, and Jenkins servers for information to find flags and complete challenges.*


In this post, you will find the write-ups for VulnMachines OSINT challenges 1, 2, 3, and 4.


These challenges are part of a series of OSINT (open-source intelligence) challenges, in which we’re asked to evaluate open-source intelligence on an organization’s external assets.


- The first challenge is to find the organization’s social media accounts and its employees’ profiles.

- For the second challenge, you should look for additional information in git repositories belonging to the organization and its employees.

- In the third challenge, the goal is to find and analyze Jenkins’ production server.

- Finally, in the fourth challenge, you will have to identify cloud-based assets related to the organization.

### OSINT 1


- We’re told to focus on social networks first; so let’s see if there is a social media account called OSINTOrg. Although we could do this manually, it would be better to use a name checker tool for automation purposes. We will use namechecker’s online service, but you could use the Sherlock tool or a similar tool.


*Namechecker output*


2. We get an account on Twitter related to the organization.


3. Reviewing the profile, we see that 3 of its followers include a reference to this account in their bio.

*Followers*


4. By analyzing the interactions between profiles, we can obtain our first flag, on a tweet response.


### OSINT 2


- From the tweet of the previous challenge we can see a link pointing to a repo of a GitHub organization, although the link does not appear to be public it opens the door to investigate the organization’s repository.


2. Reviewing the organization, we can find 2 users linked to it, they seem to correspond to the Twitter accounts that interacted in the previous tweet.


3. Looking for the organization and users in the different GitHub platforms (GitHub, gist, and GitLab), we found some gist users.


4. Reviewing the gists, we can find a flag in the comments.


### OSINT 3


- Starting from the end of the previous challenge, it will be easy to find the domain that points to the Jenkins “*osintorg-emilyosintorg-prod.osintorg.com*”.


2. We can see that, although when accessing from the browser directly, we can’t see anything, there is an associated DNS.


3. Now we have two options, either we can look for the standard Jenkins port or we can scan the server with nmap looking for an open port. In both cases, we will reach the Jenkins service on port 8080.


*Nmap result*


4. We can easily access the credentials stored on the server since we do not need credentials to access the server.


*Jenkins credentials*

### OSINT 4


- For the last flag, we will focus on information related to deployments.


2. Within the deployment logs, we can see the address of an AWS S3 bucket.


3. If we list the bucket, we see a file called FLAG.txt, and we can access it using the CLI.


## Get Cybertrinchera’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The whole process is explained here:


```
aws s3 ls s3-osint-jenkins --no-sign-request
```


This command is used to list the files and directories within an S3 bucket named “s3-osint-jenkins”. When executed, the `ls` option indicates that you want to list the contents of the bucket. The `--no-sign-request` flag is used to bypass the request signing process, this works only in situations where public access is enabled.


```
aws s3 cp s3://s3-osint-jenkins/FLAG.txt . --no-sign-request
```


You can use the following command to copy a file from the S3 bucket named “s3-osint-jenkins” to the current directory on your local machine.


The path `s3://s3-osint-jenkins/FLAG.txt` specifies the location of the file you want to copy. The dot (`.`) indicates the current directory as the destination for the copy.Similarly to the previous command, the `--no-sign-request` option is used to skip the request signing process.

---

*Originally published on [Medium](https://infosecwriteups.com/osintorg-revealed-vulnmachines-osint-writeup-cb2cb976c1b9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
