# Flag 1

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After we unzip the archive, we find a .OVA file we can open in VirtualBox and the password for the IEUser to login is found in the Description of the VM:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We first notice that the desktop files are encrypted. We go to the file explorer and enable the "show hidden files and folders" option and can find a hidden folder in the Documents that contains a ransome note.

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we get our first flag:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{053692b87622817f361d8ef27482cc5c}

# Flag 2

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We saw that Outlook was pinned to the taskbar in the previous picture of the desktop so we open that and read his emails. We see he got an `update.ps1` via email:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{75f086f265fff161f81874c6e97dee0c}

# Flag 3

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This is the part I spent the most time on as I am not very experienced in this type of powershell obfuscation reversing. At a certain point, I had the idea to search the file on https://VirusTotal.com and found it was scanned recently. Probably by someone else participating in the CTF.

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I followed the link for the report: https://www.filescan.io/reports/e71d061653a077209474360cb8be2c36d3b1d000ac31078c98d42aed192697ac/d771db5a-8b31-4324-ad0f-de7807f19d63/emulation_data#8c22ae3c323b46c996a0145a0063d58d

It would seem that that the powershell script contains a base64 encoded blob at some point that it executes:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I parsed it out in Cyberchef for a bit until I got 4 layers deeper:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can now see another blob that is reversed and base64 encoded. The variable names were random, I cleaned it up a bit to better understand it. Learned that from [John Hammond's](https://www.youtube.com/@_JohnHammond) videos.

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We reverse and decode it in Cyberchef and get the encryption function:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And our third flag is found:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{892a8921517dcecf90685d478aedf5e2}

# Flag 4

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This was in the VirusTotal details as well so I got this before flag 3:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We just needed to generate the MD5 sum. We use `-n` with echo to remove the newline otherwise we get an incorrect hash.

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{32c53185c3448169bae4dc894688d564}

# Flag 5

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I put this together after some trial and error together with ChatGPT:

```powershell
$ErrorActionPreference = "silentlycontinue"

function decryptFiles {
    Param(
        [Parameter(Mandatory=$true, Position=0)]
        [string] $baseDirectory
    )
    foreach ($File in (Get-ChildItem $baseDirectory -Recurse -File)) {
        if ($File.extension -eq ".enc") {
            $DestinationFile = $File.FullName -replace "\.enc$"
            $FileStreamReader = New-Object System.IO.FileStream($File.FullName, [System.IO.FileMode]::Open)
            $FileStreamWriter = New-Object System.IO.FileStream($DestinationFile, [System.IO.FileMode]::Create)
            $cipher = [System.Security.Cryptography.SymmetricAlgorithm]::Create("AES")
            $cipher.key = [System.Text.Encoding]::UTF8.GetBytes("7h3_k3y_70_unl0ck_4ll_7h3_f1l35!")
            $cipher.Padding = [System.Security.Cryptography.PaddingMode]::PKCS7

            $ivLengthBytes = New-Object byte[](4)
            $FileStreamReader.Read($ivLengthBytes, 0, 4)
            $ivLength = [System.BitConverter]::ToInt32($ivLengthBytes, 0)

            $ivBytes = New-Object byte[]($ivLength)
            $FileStreamReader.Read($ivBytes, 0, $ivLength)

            $cipher.IV = $ivBytes

            $Transform = $cipher.CreateDecryptor()
            $CryptoStream = New-Object System.Security.Cryptography.CryptoStream($FileStreamReader, $Transform, [System.Security.Cryptography.CryptoStreamMode]::Read)
            $CryptoStream.CopyTo($FileStreamWriter)

            $CryptoStream.Close()
            $FileStreamReader.Close()
            $FileStreamWriter.Close()
            Remove-Item -LiteralPath $File.FullName
        }
    }
}

decryptFiles -baseDirectory "C:\Users\IEUser\Desktop"
```

The only encrypted files were the ones on the desktop and after fiddling around a bit with all the files, I was able to see a peek of some very small text in the lower left corner of the second page of the `NextGenInnovation.pdf` file.

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It turns out it was the flag after zooming in a lot:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{593f1527d6b3b9e7da9bdc431772d32f}

PS: I normally do strictly offensive stuff in my day-to-day, but doing some Incident Response this way was fun and interesting. As a pentester, I haven't had the need to obfuscate my payloads to this extent, but it doesn't hurt to know it's doable.









