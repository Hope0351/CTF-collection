# :globe_with_meridians: India’s Aadhar card source code disclosure via exposed .svn/wc.db

> **Original Source:** [India’s Aadhar card source code disclosure via exposed .svn/wc.db](https://infosecwriteups.com/indias-aadhar-card-source-code-disclosure-via-exposed-svn-wc-db-c05519ea7761)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# India’s Aadhar card source code disclosure via exposed .svn/wc.db


Hi Guys, I recently found a .svn/wc.db folder exposed on a [resident.uidai.gov.in](https://resident.uidai.gov.in), and used it to reconstruct the Web app’s source code. I cannot find any article about svn, So this will be very useful for those who find svn on a website.

>

what is .svn/wc.db?


The .svn/wc.db file is a database file used by Subversion, a version control system and it contains information about the state of the working copy, including the revision numbers of the files, the dates and times when they were last updated, and any local modifications that have been made. It is used by Subversion to track changes to the files in the working copy and to manage the process of merging changes from the repository into the working copy.

>

what is the Difference between .svn/wc.db and .git ?


.svn/wc.db is a database file used by Subversion, a centralized VCS


.git, on the other hand, is a database file used by Git, a distributed VCS


Note: I haven’t used any directory or file brute-forcing. I used a chrome extension called [DotGit](https://chrome.google.com/webstore/detail/dotgit/pampamgoihgcedonnphgehgondkhikel?hl=en) which automatically finds .git and .svn in a website while surfing.


Let's Look at How I downloaded all the source codes of an Aadhar website


I just appended .svn/wc.db to [https://resident.uidai.gov.in](https://resident.uidai.gov.in) and downloaded the database file


```
wget https://resident.uidai.gov.in/.svn/wc.db
```


when I opened the database file with SQLite browser. I came occurs a lot of tables.


```
sqlitebrowser wc.db
```


The nodes table contains many columns but 2 important columns are “local_relpath” and “checksum”


local_relpath →It contains the path of a web app


checksum → It contains a checksum value of the path


For Example:


local_relpath = /Bio-Lock-Enable.php


## Get 0xLittleSpidy’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


checksum = $sha1$c7fb9f76455733203cb734de0c6016366d729458


I know that SVN keeps a backup copy of all files in a one location


```
.svn/pristine/<XX>/<CHECKSUM>.svn-base
```


- CHECKSUM is Sha1 sum of the file (remove $sha1$)

- XX is the first two characters of CHECKSUM.


```
https://resident.uidai.gov.in/.svn/pristine/c7/c7fb9f76455732203cb734de0c6016366d729428.svn-base
```


It is easy to download a single file with wget command. but I have more than 500 paths.so I wrote a simple script to download all the source code.


link to the below code ↓


[https://gist.github.com/0xLittleSpidy/d57446737071f119f452d5bc95721864](https://gist.github.com/0xLittleSpidy/d57446737071f119f452d5bc95721864)

*script to download all the source code*


*Downloaded source code*


Finally, I got the complete source code of the Aadhar website.


The Indian government has fixed the issue and I encourage ethical hacking practices.


Here are some more good resources:


Special thanks to [Dinesh Kumar](https://www.linkedin.com/in/dhina016/)for guiding me.


Thanks for taking the time to read my write-up.

### Want to Connect? Please consider following me on [Medium](https://0xlittlespidy.medium.com/), and [Twitter](https://twitter.com/0xLittleSpidy), connecting with me on [LinkedIn](https://www.linkedin.com/in/pradeep21801/), or [buying me a coffee](https://www.buymeacoffee.com/0xLittleSpidy)!

---

*Originally published on [Medium](https://infosecwriteups.com/indias-aadhar-card-source-code-disclosure-via-exposed-svn-wc-db-c05519ea7761). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
