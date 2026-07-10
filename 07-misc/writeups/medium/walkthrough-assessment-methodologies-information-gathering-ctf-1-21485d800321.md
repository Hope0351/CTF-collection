# :game_die: Walkthrough - Assessment Methodologies: Information Gathering CTF 1

---

# Walkthrough — Assessment Methodologies: Information Gathering CTF 1

Welcome, folks! Today, we will be discussing the EJPT CTF-1 walkthrough, how I solved it, and how I was able to collect all the flags. Keep in mind that I won’t be sharing the flags directly because I want you to learn, rather than just submit flags on the platform. However, I will share the commands I used and explain my methodology.

Let’s get started:

Flag 1: This tells search engines what to avoid and what not to crawl.

If you read the question carefully and remember from the videos, you’ll notice the answer is robots.txt. This file tells search engines which directories they can crawl and which they cannot. So, just go to the browser and append `/robots.txt` after your IP/URL, and you'll find the answer.

Flag 2: What website is running on the target, and what is its version?

In this we just need to do simple nmap scan and we get the flag and the command I used is:

```
nmap -sCV -A -O target.ine.local
```

Flag 3: Directory browsing might reveal where files are stored.

For flag 3 is fairly simple but takes time. You just need to do a basic directory busting using you favorite directory busting tool like dirb, fuff, dirbuster, etc., and check each files or directory.

If you go to the first URL, you’ll find an admin page, but you don’t have the credentials. Since this isn’t enumeration or exploitation, just abort it. Then, you go to the second URL, but it doesn’t show anything. You might waste time going down the rabbit hole with the third one and not find anything. But, if you examine the scan results carefully, you’ll see that dirb scans more than just directories; it can give you paths that you are unable to access, but it can still enumerate them.

## Get Mohammed Ali Mistry’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Look for something like this:

Now if you go to this path you will be able to find your third flag.

```
http://target.ine.local/wp-content/uploads/
```

Flag 4: An overlooked backup file in the webroot can be problematic if it reveals sensitive configuration details.

This one is tricky, and it took me some time to figure out, but the answer is hidden in the question itself. If you have even basic knowledge of WordPress sites, just Google the path for backup files for WordPress sites. You’ll find a URL, and if you enter that, a file with the `.bak` extension will be downloaded. Just cat the output, and you’ll get the flag.

Flag 5: Certain files may reveal something interesting when mirrored.

Mirrored?” does that ping something in your mind ……yes httrack the tool for mirroring websites. So basically use the default httrack command with URL and output into a directory:

```
httrack http://target.ine.local -O INE
```

Navigate to the path where you stored the output, and you’ll find many files and directories. This results in a long list, which we don’t want, so we’ll use grep to search for the flag in the entire directory. If you pay attention to the format of the previous flags, they are named as FLAG1{xvdwjvlkjw}, FLAG2{jcbjskvblk}, etc.

Since we need the fifth one, I grepped it out using this command:

```
grep -i "FLAG5" -R target.ine.local/
```

Hurray we got all the flags, congratulations.
Happy hacking!

---
