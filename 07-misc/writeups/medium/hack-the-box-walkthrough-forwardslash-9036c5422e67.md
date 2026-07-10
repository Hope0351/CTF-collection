# :game_die: Hack the Box Walkthrough - Forwardslash

---

*Used cyberchef to sample times and formats and this came out*

Upon checking the binary owned by the user pain, we learned the following:

- It’s dubbed as *Pain’s Next-Gen Time Based Backup Viewer*

- Running it returns a jumbled string that we later found out to be an MD5 hash of the current time

So the `/usr/bin/backup` binary essentially gets the current system time, by the second, gets its md5 hash, and then tries to open a file with that filename. As you can see from the `access function`, in the `ltrace` screenshot, the filename is not using an absolute path, and so we can exploit it by creating a file with an md5 hash of a set time as its file name, and then running it at exactly that particular time.

What do we want to open though?

From the banner of the binary, it’s dubbed as a *Next-Gen Time Based Backup Viewer*, so a clue is that the author created it to view backups.

Let’s find all the files with the file extension `.bak` then.

```
$ find / -name '*.bak' 2>/dev/null
```

All files with `.bak` as a file extension is saved in `/var/backups`, so maybe we can check which one is useful / interesting.

*/var/backups*

One file is owned by pain, so instinctively, we go for that one first. How do we rename it to an md5 hash of the time though?

Since we cannot perform anything to edit or even read this file, we can create another file that is, quite literally, connected to this one through the use of symbolic links.

*Made a symbolic link named ‘md5’Renamed the symbolic link to the md5 hash of a particular timeRan the binary at that specific time*

I don’t remember why I did the above in 3 separate steps but my hunch is that I had minimal brain power during that time due to the complex enumerations that I did prior to that. hehe. A more elegant solution is presented below:

```
$ ln -s /var/backups/config.php.bak $(date | awk -F ' ' '{print $4}' | md5sum | awk -F ' ' '{print $1}') && backup
```

Running this will immediately print the contents of `/var/backups/config.php.bak` I can do bash scripting too you know. hahahaha. jk.

The credentials of the first user that we got are as follows:

- username: pain

- password: db1f73a72678e857d91e71d2963a1afa9efbabb32164cc1d94dbc704

### Encryptorinator

Since the output of the backup file contained DB credentials, instinctively, I tried dumping the database using the below command.

```
$ mysqldump --opt -u pain --password site > site.sql
```

For which I got an error. I then tried switching to the user pain using these recently dumped credentials and it worked.

Upon lateral movement to the user pain, I immediately checked the commands that pain is authorized to run as root without the system asking for any passwords. I usually do this to check whether I can hijack these binaries, or find an exploit for them so I can get root access.

However, upon checking the above, it wasn’t immediately clear to me what I can do with these commands to gain root, so I brushed it off for the moment and returned to pain’s home directory to get a closer look at the `encryptorinator` folder we saw earlier.

To make more sense of the situation, I figured that we need to go through with the decryption of the ciphertext present in the home directory of pain.

Since I am not that confident in reversing the given encryption algorithm, I instead wrote a simple pure bruteforce script.

The funny thing here, is that I was in the middle of debugging my script, when suddenly, upon running it, it worked. I didn’t expect that using a `key` of repeated characters will crack the cipher, but it did.⁴

---
