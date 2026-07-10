# :game_die: Nanothorpe challenge — CTF Write-up

---

# Nanothorpe challenge — CTF Write-up

Write-up for hxp 2020 CTF challenges

There are two parts to this post
1. Initial Setup
2. Challenge Solution

If you are looking for hands-on approach rather then just reading the solution then I would suggest you to go through the initial setup first. There are no spoilers about the challenge in the initial setup.

## Initial Setup

Firstly I would suggest you to download the CTF challenge’s source code. The CTF website doesn’t currently host the challenges but nevertheless the website provides links to download the source code for the challenge they hosted. The reason they provide the source code is that the challenge requires the players to find vulnerabilities by studying the source and develop and exploit for the target site provided by the CTF.

[Download link for Nanothorpe challenge’s source code](https://2020.ctf.link/assets/files/nanothorpe-d2095dcfeda4b08d.tar.xz)

Using the source code you can deploy a docker instance in your system which is similar to the original Target website provided in the CTF challenge.

*Fig. 1: Nanothorpe Source code*

The source code will look similar to what is shown in figure 1, apart from the server-secret and flag file. These are files are required for one to spin up the docker instance and they play a crucial role in the challenge. I have put some random text in the files for the purpose of depiction of the challenge.

*Fig. 2: Building the docker image*Generic command for building docker image:
$ *sudo docker build -t <tag> -f <file_location> .*

I have shown the command I used to start the process of building my docker image in figure 2. In short docker will check all dependencies and download few from the internet, if there is an issue you can easily resolve it using the error message and your friend google.
*In my view, if you have the server-secret and flag file you will be good to go.*

*Fig. 3: Running Docker image*Generic command for building docker image:
$* sudo docker run --privileged -p 80:80 -it <dockername>*

I have used the right command in the figure 3, use the generic command mentioned above to run the docker. The above command makes sure that the docker’s port 80 is connected with the host’s port 80.

This ensures that you can access the website hosted on docker using the home IP address(127.0.0.1)

*Fig. 4: Target website*

Finally when you open your web browser and visit 127.0.0.1, you will find the website shown in figure 4. This is the target website of the CTF challenge re-created on your system.

I will share few docker commands, they can come in handy:
$ *sudo docker inspect <dockername>*$ *sudo docker images -a*$ *sudo docker build -t <tag> -f <file_location> .*$* sudo docker ps -a*$ *sudo docker run — privileged <dockername>*$ *sudo docker run -p 80:80 -it <dockername>*$* sudo docker exec -it <Docker name/Docker ID> <Shell Cmds>*$ *sudo docker stop $(sudo docker ps -a -q)*$ *sudo docker rm $(sudo docker ps -a -q)*$ *sudo docker container run -it <Docker name>:latest /bin/bash/bin;*

## Challenge Solution

As the input box on the website was hinting that it would take ls as an input and also if one visits the CTF site on the challenge they describe the challenge as “Welcome back to `ls`-as-a-service, the most useful tool on the internet!”.

From these hints, intuitively first and foremost I have tried the ‘ls’ command on the website’s input box.

*Fig. 5: Network traffic for ‘ls’ as input*

After watching the result as shown in figure 5,
I understood that the website processes the user input and runs it on it’s server and returns the result to the users.
For this purpose it makes two http GET requests, one to “authorize” API and another to “run” API.

I tired to run other Linux shell commands and see how the website is processing it.

*Fig. 6: Network traffic for ‘echo’ as input*

As expected the website returns a message stated it Failed to run command. I have shown one such response I have got in figure 6.

After carefully examining the website, I was sure that there wasn’t any input validation done on the client side.
It’s evident that the “authorize” API first checks the command and then it redirects the request to “run” API.

The challenge is categorized cryptography in the CTF website. This only means one thing, I have to look into the source code acquired for the challenge and see if the back-end is using any vulnerable cryptographic algorithms or mechanisms.

I went through the the source code of the challenge, There were 3 python scripts and I went through the *service.py*
Soon I learnt that this is the python script uses the other two scripts, this script hosts a flask powered web-back-end.

*Fig. 7: Code block in Service.py*

Upon analyzing the code block shown in figure 7.
It can be easily inferred that the authorize API verifies is the user input, only proceeds further if the input is ‘ls’.

authorize API generates a time stamped signature, it stores the signature and decoded data in the cookie. Then the authorize API redirects to a GET request to run API end-point, it includes the input data sent by the user and it’s expiry time.

*Fig. 8: Code block in Service.py*

Studying the run API back-end code as shown in the figure 8. It is observed that only upon successful verification of the input data one cloud run the command on the server.

We also have the source code for octothorpe which is used as a Hash function in the CTF.

## Crucial Point

- Run API end-point is accessible to public internet (in our case the host system), this is inferred from the network data of figure 5 and also upon analyzing the authorize API source code.

- As run API end-point is available to public internet, anyone can send a maliciously crafted the request to run API end-point, provided they have a signature of the data, that authorize API generates.

- To generate a the signature of any data “server-secret” is required, from figure 5. The authorize API end-point prepends this secret to the time-stamp and user input, and then generates the signature by Hashing them.

- Hash function is defined in octothrope file.

### MAC = Hash ( Server-secret + Time-stamp + User-input)

## Vulnerability:

No matter how you look at it it all points to only one thing, Find a vulnerability in the Hashing mechanism.

If you look around in CTFs, the common methods to solve such problem is to try out if the Hash is vulnerable to[length extension attack](https://en.wikipedia.org/wiki/Length_extension_attack).

This is possible because of two reasons:

- The type of construction the octothorpe hashing function has used

- The secret information pertaining to the server is prepended to the data

*Fig. 9: Test code*

This code shown above confirms if the hash function in octothorpe is vulnerable to the length extension attack.

This simply sets the initial state of the octothorpe hash function to the legit hash value, from them on the hashing algorithm continues to hash with the appended data.

## How to use the vulnerability

If you could append ‘; ls -la’ or ‘; <shell command>’ then the provided shell command would run on the server. This input processes multiple shell commands provided in a single line, sequentially and displays the aggregated output.

## Exploit

We have the hash function with fixed IV in octothorpe, which is provided in the source code. We also have the hash for the legit data request. but we don’t know the length of the secret which the server appends.

- First get a legit hash (MAC), submit a query to authorize API with ‘ls’ command, use the signature and redirect provided in the response — signature will give the initial MAC, redirect will give the query string.

- Use brute force method to find the length of the secret for which the run API responds.

- Use the length of secret derived to generate a new valid request for run API, and appending “; pwd; whoami; cd /; ls -la; cat flag*” — It will provide all the basic information about the server instance and also get the flag file from root directory.

It would be impractical to show the attack pictorially. I would suggest you to follow the above steps and try it on your docker instance recreating the CTF challenge.

*I would really love your feedback on the content, please let me know it by sharing or commenting or clapping*

---
