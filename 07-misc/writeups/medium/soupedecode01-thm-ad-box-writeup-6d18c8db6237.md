# :game_die: SoupeDecode01 - THM AD Box Writeup

---

# SoupeDecode01 — THM AD Box Writeup

By : Vedant Bhalgama (@ActiveXSploit)

- A new TryHackMe machine, SoupeDecode01, was recently released. It’s a beginner-friendly Active Directory box that covers several AD attack techniques, including Password Spraying, Pass-the-Hash, and Kerberoasting.

- In this write-up, I’ll walk you through my approach and methodology for compromising the box. With that being said, let’s get started!

- Room Link : [https://tryhackme.com/room/soupedecode01](https://tryhackme.com/room/soupedecode01)

## - 0x01 — Initial Recon :

- As usual, I began with a `nmap` scan to enumerate the open ports and identify the services running on the target machine. Looking at the scan results, it was pretty evident that our target is a Domain Controller.

- On a high level, the following services were identified :
- Kerberos (88)
- LDAP (389)
- RDP (3389)
- SMB (445)
- RPC (135)
- DNS (53)

*Initial Nmap Scan against the DC*

```
nmap -p 53,88,135,139,389,445,593,636,3268,3269,3389,9389,49667,49675,49709,49804 -sC -sV -oN nmap/aggressive-all-ports.tcp -Pn 10.201.45.53
```

- My approach when dealing with a Domain Controller is to begin by enumerating SMB. I first check whether guest authentication is permitted, and if it is, I look for any accessible shares that might contain valuable information. With this in mind, I started my enumeration by focusing on SMB on the target.

- While checking for guest authentication with `nxc`I found that it was indeed enabled. However, access was limited to READ permissions on the `IPC$` share, with no additional rights. During the enumeration, I also discovered an interesting share named`backup`, which seemed like it could be useful later. I made a note of this and moved forward.

*SMB Share Enumeration reveals an interesting share named “backup”*

```
nxc smb 10.201.45.53 -u ' ' -p '' --shares
```

- Next, I attempted LDAP enumeration, but with anonymous binds disabled, I couldn’t progress without valid credentials. Revisiting the SMB results, I realized that since I had `READ` access to the `IPC$` share, I could perform a RID brute force attack using `impacket-lookupsid` to enumerate all valid domain users. These accounts could later be leveraged for attacks such as AS-REP Roasting or password spraying.

*RID BruteForce via impacket-lookupsid*

```
impacket-lookupsid ' ':''@10.201.45.53
```

## - 0x02 — Gaining initial access to ybob317’s account :

- The RID brute force attack returned a total of 1,069 accounts, several of which were computer accounts. My next step was to check if any of these accounts had the `DO_NOT_REQUIRE_PREAUTH` flag enabled. If present, such accounts would be vulnerable to AS-REP Roasting, allowing me to request their TGT and attempt offline password cracking on the attacker machine.

- However, none of the accounts in the domain had the `DO_NOT_REQUIRE_PREAUTH` flag set, which ruled out the possibility of AS-REP Roasting. I then shifted my focus to password spraying. Instead of using a large wordlist like `rockyou.txt` — which would have been inefficient given the high number of usernames — I opted for a more targeted approach: spraying with each username as its own password. This is a common misconfiguration in real-world environments, where users often set their username as their password.

*Tried an ASREP-Roast attack but failed ;(*

```
impacket-GetNPUsers soupedecode.local/ -usersfile domain_users.txt -request -dc-ip 10.201.45.53 -no-pass -outputfile hashes_asrep
```

- While running the password spray attack with `nxc`, I quickly discovered a valid credential set — the user `ybob317` had their username set as their password. A lucky find!

- Credentials Discovered :
- `ybob317 : ybob317`

*Password spray attack reveals a successful login for ybob317*

```
nxc smb 10.201.45.53 -u domain_users.txt -p domain_users.txt --ignore-pw-decoding --no-bruteforce --continue-on-success
```

- With valid credentials in hand, I revisited the SMB shares to check if `ybob317` had access to the `backup` share. Unfortunately, the attempt revealed that access was still restricted.

*Re-Enumerated SMB Shares as ybob317 to validate access to backup share*

```
nxc smb 10.201.45.53 -u ybob317 -p ybob317 --shares
```

- This wasn’t the end of the road. Revisiting the list of users obtained from RID brute forcing, I noticed a few service accounts. Since I already had valid credentials for *ybob317*, I decided to perform Kerberoasting via `impacket-GetUserSPNs` to request TGS tickets for these service accounts. I then attempted to crack the extracted hashes locally, hoping to successfully recover at least one password.

## Get Avyukt Security’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

## - 0x03— Lateral Movement via Kerberoasting :

*Performed kerberoasting to request TGS tickets for service accounts*

```
impacket-GetUserSPNs soupedecode.local/'ybob317':'ybob317' -request -dc-ip 10.201.45.53 -outputfile kerberoasting_hashes
```

- From the output, I was able to retrieve TGS hashes for five service accounts in the domain, namely:
- `file_svc`
- `firewall_svc`
- `web_svc`
- `monitoring_svc`

- Next, I attempted to crack the retrieved TGS hashes using John, hoping for at least one successful result. Within a few seconds, I managed to crack the hash of one account, revealing the password `Password123!!`. A solid find!

*Using John-The-Ripper to crack TGS hashes*

```
john --wordlist=/usr/share/wordlists/rockyou.txt kerberoasting_hashes
```

- I then sprayed this password against the five service accounts to determine which one we had successfully compromised. This revealed that the cracked password was valid for the *file_svc* service account, confirming successful access.

*Successful login as file_svc service account*

```
nxc smb 10.201.45.53 -u service_accounts.txt -p 'Password123!!'
```

- With the new credentials, I re-enumerated SMB as the `file_svc` account to verify access to the `backup` share. This time, the account indeed had `READ` permissions on the share! I then proceeded to enumerate the share to check if it contained any valuable information.

*READ access to backup share as file_svc service account*

```
nxc smb 10.201.45.53 -u file_svc -p 'Password123!!' --shares
```

- Using `smbclient`I accessed the `backup` share with the `file_svc` account to enumerate its contents. Among the files, I found a text file named`backup_extract.txt`, which seemed promising. I quickly downloaded it to my local machine and examined its contents.

*Discovery of backup_extract.txt from the backup share*

```
smbclient -U='file_svc' \\\\10.201.45.53\\backup
```

- Upon reviewing the backup file, I found that it contained NTLM hashes for several computer accounts in the domain. To make use of this, I wrote a quick Bash one-liner to extract the computer account names along with their corresponding NTLM hashes, saving them into separate files for spraying later on :)

*Computer accounts and their respective NTLM hashes recovered from backup_extract.txt*

*One-Liner for extracting computer account names*

```
cat backup_extract.txt | cut -d ":" -f 1 >> backup_users.txt
```

*One-Liner for extracting NTLM hashes of computer accounts*

```
cat backup_extract.txt | cut -d ":" -f 4 >> backup_hashes.txt
```

## - 0x04 — Gaining Domain Admin on `soupedecode.local `:

- After separating the computer account names from their corresponding NTLM hashes, I proceeded to spray these hashes against the Domain Controller to check if they were still valid and active.

- To my surprise, one of the computer accounts `FileServer$,` still had its password hash in use. Even more interesting was the output showing a `Pwn3d!` message, indicating that we had successfully compromised the domain. This suggested that the `FileServer$` account was likely a member of the Administrators group on the Domain Controller, which granted us elevated privileges.

- I later confirmed this by executing a simple `whoami /groups` command on the Domain Controller, which verified that the `FileServer$` computer account was indeed part of the Administrators group. This ultimately resulted in a full domain compromise!

*Successful authentication to the DC as FileServer$ computer account*

```
nxc smb 10.201.45.53 -u backup_users.txt -H backup_hashes.txt --continue-on-success --no-bruteforce
```

*FileServer$ computer account being a part of the Administrators group*

```
nxc smb 10.201.45.53 -u 'FileServer$' -H e41da7e79a4c76dbd9cf79d1cb325559 -x 'whoami /groups'
```

*Gaining root flag ;)*

```
nxc smb 10.201.45.53 -u 'FileServer$' -H e41da7e79a4c76dbd9cf79d1cb325559 -x 'type C:\\Users\\Administrator\\Desktop\\root.txt'
```

- With that, I had successfully rooted the box! I hope you found this write-up interesting. Don’t forget to subscribe to Avyukt Security for more articles and walkthroughs on cybersecurity!

Happy Hacking!

---
