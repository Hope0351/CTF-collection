# :game_die: HTB Remote [Writeup]. NFS Check, CMS exploitation, UsoSvc…

---

# HTB Remote [Writeup]

## NFS Check, CMS exploitation, UsoSvc service permission exploit

### Summary

Looking at the nmap result, there were too many ports that is overwhelming to look at, for the beginners. After some enumeration and checks, NFS share was found to be publicly available to anyone on the network. Further digging into this revealed the credentials and an exploit was easily found from checking the web application version which the site was running. Using that exploit the user machine was pwned. For the Root, again a quick check using the powershell’s program, we find the service vulnerability and abusing which led to becoming the ROOT!

Platform: Windows

Tools Used:

- `nmap`

- `showmount -e 10.10.10.180`to show NFS shares since port 2049 was open

- `mount 10.10.10.180:/site_backups site_backups/` to mount the available share directory onto the host machine.

- `john` to crack the hash file.

- `powershell.exe` and its programs

- Exploit: [Umbraco CMS 7.12.4](https://www.exploit-db.com/exploits/46153)

- `sc.exe qc UsoSvc` to get more info about the service 'UsoSvc'CVE(s): n/a

### Enumeration

---
