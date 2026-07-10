# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/azure-blob-container-to-initial-access-lab-walkthrough-pwned-labs-47ac29e5f5ee)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Azure Blob Container to Initial Access Lab Walkthrough : Pwned-Labs


*[https://labs.pwnedlabs.io/azure-blob-container-to-initial-access](https://labs.pwnedlabs.io/azure-blob-container-to-initial-access)*


H*ey there, Maverick here back again with another dive into the wild world of cloud pentesting. If you’re new to my corner of the cybersecurity scene, welcome aboard! Today, we’re tackling a beginner-friendly yet eye-opening lab from Pwned Labs: Azure Blob Container to Initial Access. This one’s all about spotting misconfigurations in Azure Blob Storage (think of it as Azure’s answer to AWS S3 buckets) and chaining them into a full foothold in an Entra ID (formerly Azure AD) environment.*


*By the end of this walkthrough, you’ll understand how a simple public blob exposure can lead to credential theft, Entra ID compromise, and even enumerating an entire organization’s users. We’ll simulate a real-world scenario for “Mega Big Tech,” a hybrid cloud setup with on-prem Active Directory syncing to Azure. Spoiler: It goes sideways fast if security’s lax.*


*This lab highlights why blob storage misconfigs have caused massive breaches remember those 38TB of exposed Microsoft AI data? Let’s get our hands dirty.*


*Attack Path (Source : [https://pwnedlabs.io](https://pwnedlabs.io/))*


*A single misconfigured Azure Blob container hosting a public website became the entry point for full Entra ID compromise: inspecting the site’s source revealed it was served from blob storage, versioning exposed a deleted ZIP file containing two PowerShell scripts with hardcoded admin credentials, and those credentials granted direct login to a privileged Entra ID account turning an overlooked storage misconfiguration into complete initial access in under 10 minutes. One blob, one flag, total pwn.***

### **Important prerequisite for the rest of this lab**


*The target environment is only reachable from within the provided corporate VPN. Before continuing with any Azure/Blob enumeration, connect to the lab VPN first:*


```
# Download the .ovpn file from the lab portal, then:
sudo openvpn azure.ovpn
```


*Target Website : [https://dev.megabigtech.com/$web/index.html](https://dev.megabigtech.com/$web/index.html)*


*Visiting the site reveals what appears to be a development or staging version of the main production website. No exposed functionality of immediate security interest is present on the surface. Proceeding to inspect the page source for hidden clues, comments, or references that might reveal additional attack surface.*

## Discovery of a Secondary Blob Container


*Closer inspection of the page source reveals a leftover development artifact an <hr> element containing a full URL to a CSS file hosted in a non-standard container:*


```
<hr="https://mbtwebsite.blob.core.windows.net/web/static/application-91620862a42825801f8afc0695b918649f56be0d297f9b0a77c5.css">
```


*This single line discloses the existence of a second container named web (distinct from the default $web container used for static website hosting).*


*Azure Blob Storage static websites are served from the special $web container by design, but many organizations also maintain a parallel web (or www, site, assets, etc.) container for builds, backups, or staging. These auxiliary containers are often forgotten and left with overly permissive anonymous access.*

## Quick PowerShell install on Kali


```
sudo apt update
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg
sudo mv microsoft.gpg /etc/apt/trusted.gpg.d/
sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/trusted.gpg.d/microsoft.gpg] https://packages.microsoft.com/repos/microsoft-debian-bookworm-prod bookworm main" > /etc/apt/sources.list.d/microsoft.list'
sudo apt update
sudo apt install -y powershell
```


```
pwsh
```


*Figure 1.1*


```
Invoke-WebRequest -Uri 'https://mbtwebsite.blob.core.windows.net/$web/index.html' -Method Head
```


- ***Invoke-WebRequest PowerShell’s built-in cmdlet for making HTTP/HTTPS requests (equivalent to curl in Kali).*

- ***-Uri Specifies the target URL (in this case the root index.html of the Azure static website).*

- ***-Method Head Sends only an HTTP HEAD request instead of GET. This retrieves headers without downloading the full file body perfect for quick verification and header inspection.*


*The presence of x-ms-blob-type: BlockBlob and the Server: Windows-Azure-Blobs header removes any remaining doubt this is 100% an Azure Blob Storage static website with anonymous read access enabled on the $web container.***

## Confirming the backend with headers


*Figure 2.1*


```
Invoke-WebRequest -Uri 'https://mbtwebsite.blob.core.windows.net/$web/index.html' -Method Head |
Select-Object -ExpandProperty Headers
```


**Linux equivalent (much simpler):**


```
curl -I https://mbtwebsite.blob.core.windows.net/$web/index.html
```


***This PowerShell one-liner sends a lightweight HEAD request to the site’s index.html and extracts all response headers in full. The key result: headers like Server: Windows-Azure-Blobs/1.0 and x-ms-blob-type: BlockBlob instantly confirm that the website is served directly from Azure Blob Storage with static website hosting enabled a single command that gives 100 % proof of the backend technology.*


*Figure 1.3*


*It’s worth exploring the $web container to see if we can find anything else there. We can do this using a browser as shown in Figure 1.3*


```
https://mbtwebsite.blob.core.windows.net/$web?restype=container&comp=list
```


*Figure 1.4*


*This returns all the blobs in a XML document! We could also return just the directories in the container by specifying the *`*/*`* delimiter as shown in Figure 1.4*


```
https://mbtwebsite.blob.core.windows.net/$web?restype=container&comp=list&delimiter=%2F
```


*Figure 1.5*


```
https://mbtwebsite.blob.core.windows.net/$web?restype=container&comp=list&include=versions
```


***The $web container only exposes the static directory we already observed in the source code nothing new there.***


*Next, we should determine whether blob versioning is enabled on the container. When versioning is active, Azure automatically retains previous versions of every blob, each tagged with a timestamp. This is particularly interesting because files that have been deleted (or replaced) from the current view can still exist as historical versions a common place where sensitive data lingers after attempted cleanup (temporary uploads, accidental commits containing secrets, etc.).*


*According to Microsoft documentation, the include=versions parameter is only supported when using API version 2019–12–12 or newer. By default, anonymous requests may use an older version, which silently ignores the parameter.*


## Get Maverick’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


*We can force the correct API version by adding the x-ms-version header:*


*Figure 1.6*


```
curl -H "x-ms-version: 2019-12-12" \
'https://mbtwebsite.blob.core.windows.net/$web?restype=container&comp=list&include=versions'
```


*This returns a large XML payload containing both current blobs and any previous versions.*


*For readability, install xmllint (if not already present) and pipe the output through it:*


*Figure 1.7*


```
sudo apt install -y libxml2-utils
```


```
curl -H "x-ms-version: 2019-12-12" \
'https://mbtwebsite.blob.core.windows.net/$web?restype=container&comp=list&include=versions' \
| xmllint --format - | less
```


*Figure 1.8*


*Figure 1.9*


After downloading the zip file you can extract and retrieve powershell scripts that contain credentials as shown in Figure 2.0


*Figure 2.0*


*Figure 2.1*


*After unzipping the archive we see two scripts. The contents of *`*stale_computer_accounts.ps1*`* is below. It identifies, disables and moves stale computer accounts to the "Review" OU. We see that it contains credentials for the Active Directory admin account *`*marcus_adm*`* as shown in Figure 2.1*


*We also see the *`*entra_users.ps1*`* script below that does an audit of all Entra AD users, and it has credentials included in the comments*


```
Import-Module MSAL.PS

# Username: marcus@megabigtech.com
# Password: TheEagles12345!

# Use Microsoft's public Azure PowerShell client ID
$ClientId = "04b07795-8ddb-461a-bbee-02f9e1bf7b46"
$TenantId = "common" # Or use your actual tenant ID
$Scopes = @("https://graph.microsoft.com/.default")

# Device code login (supports MFA)
$TokenResponse = Get-MsalToken -ClientId $ClientId -TenantId $TenantId -Scopes $Scopes -DeviceCode

# Use the access token in Graph API call
$AccessToken = $TokenResponse.AccessToken
$GraphApiUrl = "https://graph.microsoft.com/v1.0/users?`$select=displayName,userPrincipalName"

$headers = @{
"Authorization" = "Bearer $AccessToken"
"Content-Type" = "application/json"
}

$response = Invoke-RestMethod -Uri $GraphApiUrl -Headers $headers -Method Get

# Show formatted output
$response.value | Format-Table displayName, userPrincipalName
```


*Figure 2.2*


*Let’s run the script. First, open a PowerShell terminal and install the MSAL.PS PowerShell module if needed.*


```
Install-Module -Name MSAL.PS
```


*With that done, let’s see if the credentials for *`*marcus@megabigtech.com*`* are valid!*


```
./entra_users.ps1
```


*Figure 2.3*


After running this command copy the code and visit the url provided as shown in Figure 2.3

*Figure 2.4*


Add that code which is provided here and move forward and authenticate

*Figure 2.5*


Finally !! you have successfully authenticated now head back to the terminal and you will get entire list as shown in Figure 2.6


*Figure 2.6*


*We have achieved our assessment objectives, compromised an Entra AD user to get a foothold in the Mega Big Tech Azure account and can enumerate all users! PWNED!**To get the flag and complete the lab, we can run the command below, which is like the *`*whoami*`* command for Azure.*


```
Install-Module -Name Az
Import-Module -Name Az
Connect-AzAccount
Get-AzADUser -SignedIn | fl
```


*Figure 2.7*


We have finally completed the lab


*Source : [https://bootcamps.pwnedlabs.io/](https://bootcamps.pwnedlabs.io/)*


***Earn the Most Respected Cloud Pentesting/RT Certifications on the Planet***


*Complete a PWNED Labs 4-week Bootcamp and walk away with an official, hands-on certification that red teams and employers instantly recognize:*


- ***MCRTP — Microsoft Cloud Red Team Professional*

- ***GCRTP — Google Cloud Red Team Professional*

- ***ACRTP — AWS Cloud Red Team Professional*


*These aren’t theory exams. You breach real cloud tenants, escalate privileges, exfiltrate data, and defend against live attacks all under instructor guidance.*


*When you pass, you earn the badge that proves you can do it for real.*


***Discord: ***[https://discord.gg/pwnedlabs](https://discord.gg/pwnedlabs)*
LinkedIn: *[https://www.linkedin.com/company/pwned-labs](https://www.linkedin.com/company/pwned-labs)*
Twitter / X: ***[https://x.com/pwnedlabs](https://x.com/pwnedlabs)


*Follow for more offensive security related content !!* 😊😉

---

*Originally published on [Medium](https://infosecwriteups.com/azure-blob-container-to-initial-access-lab-walkthrough-pwned-labs-47ac29e5f5ee). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
