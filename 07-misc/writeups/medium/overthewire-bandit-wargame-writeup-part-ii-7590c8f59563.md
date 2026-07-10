# :game_die: OverTheWire: Bandit wargame (Writeup -Part II)

> **Original Source:** [OverTheWire: Bandit wargame (Writeup -Part II)](https://infosecwriteups.com/overthewire-bandit-wargame-writeup-part-ii-7590c8f59563)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# OverTheWire: Bandit wargame (Writeup -Part II)


Check part 1 of this series to understand & solve the next level easily.


[https://medium.com/@Ali_AK/overthewire-bandit-wargame-writeup-a6883440bbd6](https://medium.com/@Ali_AK/overthewire-bandit-wargame-writeup-a6883440bbd6)


In this writeup, I’m going to cover levels 13–20

>

*Level 13*


Here, we’ve given an SSH private key (RSA key) instead of a password for the next level (bandit14). For those, who don’t know SSH supports 2 authentication methods (password-based & Key-based).


Here it’s Key-based authentication so to get remote access to bandit14. we can use our (bandit13) SSH private key in the SSH login session.


Note: For key-based auth, your (bandit13 public key) must be stored in a server (bandit14) file named /.ssh/authorized_keys. For the client (bandit13) he’ll use his private key to log in.


Now we’re successfully login as bandit14 so we can read the bandit14 password file.

>

*Level 14*


Here, we just have to submit our last password (bandit14) into localhost (own machine) & port 30000 (Which is listening for connection).


so we use Netcat (nc) to transmit our data into a specific host & port.

>

*Level 15*


Here, we just have to do the same task as level 14 but using SSL encryption. we can’t use Netcat (nc) since it doesn’t have/support data transmission using SSL encryption.


So for transmission/communication using SSL encryption s_client which comes in the OpenSSL suite supports it.


>

*Level 16*


Here, we just have to do the same task as level 15 But we’ve given a range of ports so first, we need to find which ports are open (Any service is running).


## Get Ali AK’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


nmap -sV localhost -p 31000–32000 -vv

*Nmap (a port scanner) Scan Result*


So next we’ve to send to that port (service) which speaks/supports SSL.


*Port 31790 Speaks SSLRSA private key as next-level password*


Copy this Whole private key into your system & use it to log in to bandit17.

>

*Level 17*


Here we’ve two files & we just have to find only difference between 2 files.


diff tool is best to compare files & it returns indifference values.

>

*Level 18*


Here when we try to SSH it lets us in but after some banner display it logs us out every time. Look like someone is running a script in ~/.bashrc & it’s set to log us out when we try log into that user's home.


So by using the above command we can bypass/Ignore files such as bashrc, bash_profile, bash_login, and profile.


Note: Ignoring these files can cause shell basic functionality unstable & also result in the missing of basic features.

>

*Level 19*


Here, we’ve given a file that has a SUID permission set. SUID/Set Owner User ID is special permission set to executables. SUID allows an alternate user to run an executable with the same permissions as the owner of the file instead of the permissions of the alternate user.


So, this script is taking one argument & executing it with the privilege of the file owner (bandit20). so by this, we can read the password file which is owned by bandit20.

>

*Level 20*


Here we also have given SUID set executable & it is taking one argument


For this level, we’ve to use jobs command, and some knowledge of foregrounding & backgrounding processes.


jobs (return all the process states running, suspended, stopped etc)


bg (used to put the running process in the background just put & in any process which you want to bg)


fg (used to call the background process in the foreground).


./suconnect connects to localhost with our given port so on the other side to catch that connection I used Netcat (nc) to listen on that port after the connection is established just send the previous level password & script (suconnect) will return us our next level password.


Check the next part III where I solved (levels 21–27)


[https://medium.com/@Ali_AK/overthewire-bandit-wargame-writeup-part-iii-28e322d23d5d](https://medium.com/@Ali_AK/overthewire-bandit-wargame-writeup-part-iii-28e322d23d5d)

---

*Originally published on [Medium](https://infosecwriteups.com/overthewire-bandit-wargame-writeup-part-ii-7590c8f59563). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
