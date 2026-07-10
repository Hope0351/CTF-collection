# :game_die: Ieee Mansb Ctf 2025 Dfir Writeup 3B49A1Afe7F6

---

```
14) The developer used a security feature to securely encrypt a secret file. Can you determine what he was trying to hide?
```

Now, for the last juicy part.

in question 13, we could answer it with PDF file located in `C:\Users\mhany\Desktop\Work\QR Tag\Docs\` directory.

So, while i was checking all other documents files, i found a file called `finance.xlsx`with a very strange magic bytes:

*finance.xlsx*

of course, it’s not the traditional hex values for an excel file. to be more clearer, there’s an another excel file called `user_accounts.xlsx`

*`user_accounts.xlsx`*

See the difference!!!! `finance.xlsx`is definitely not an excel sheet file.

So, the question now, what it is actually ?

and the question says “*The developer used a security feature to securely encrypt a secret file*”.

so this file is encrypted with a windows security feature i guess!!

if we did a quick research on the magic bytes on google `01 00 00 00 D0 8C`, we can definitely get to the point.

*DPAPI*

also i did a very weird research, i uploaded the excel file on VirusTotal [link](https://www.virustotal.com/gui/file/bfeddbd77a68f15e5489b851235c0c00e822f54446bf716309d35b6b44e30a33/details)(first one to upload this file) and by reading Details section, we can definitely make sure that this file contains DPAPI encrypted data (100%)

- we need to recover the DPAPI masterky to decrypt the file data.

2. and to do recover the DPAPI masterkey, we need to decrypt the masterkey file. location: `C\Users\<username>\AppData\Roaming\Microsoft\Protect\<SID>\<GUID>`

3. and to decrypt the masterkey file, we need to recover the logon password for the user “`mhany`”

4. and to recover the logon password for this user, we need to decrypt `SAM `registry hive that contains the local account password hashes.

5. and to decrypt the `SAM` registry hive, we will need also the`SYSTEM`hive
which both are located in : `C\Windows\System32\config\` directory

---
