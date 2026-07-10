# :game_die: Extracting an Unsaved Memory-Content by Walking through Windows Heaps, but How?

---

# Extracting an Unsaved Memory-Content by Walking through Windows Heaps, but How?

>

Notes:
Greetings fellow readers! Before you read this content, I’d like to remind you that this is based on my research and findings, so if you encounter or happen to see a misleading information, I’d love to hear your opinion and I’m very open to any information that should be stated correctly.

First of all, I’d like to give a shoutout to my colleagues and IFEST CTF committee from FMIPA Padjajaran University to organize such an amazing CTF event and gives me and my team, [PETIR](https://petircysec.com/), an opportunity to host and become a part of CTF Problem Setters. This writings is based on one of a Memory Forensic challenges that I made.

Have you ever wondered how we can extract a valuable content inside our computer’s memory especially inside one process that has been run? Memory Forensics allows you to do that. Some famous forensic tools for investigating the memory consists of:

If you are not familiar with memory forensics, I’d recommend you to read a basic of it from [stuxnet](https://stuxnet999.github.io/volatility/2020/08/18/Basics-of-Memory-Forensics.html)blogs and also an amazing book `[The Art of Memory Forensics](https://www.amazon.com/Art-Memory-Forensics-Detecting-Malware/dp/1118825098)`.

We usually encounter a scenario of a challenge that was given a memory dump with a common extensions such as .vmem or .raw, and to identify the OS crash dump or a memory dump, a volatility plugin called `imageinfo` or `kdbgscan` will be responsible to do that. There are numerous blogs that discuss about the functionality of each `volatility` plugins, and I’d like to recommend it from [Andrea Fortuna](https://andreafortuna.org/2017/06/25/volatility-my-own-cheatsheet-part-1-image-identification/) blogs (part by part).

A. The Case Scenario

Let’s say that a DFIR Researcher is having a hypothesis that we’re able to parse and extract the content that we typed inside an application without retrieving its dumped file first so it shall be precisely located by ourself. To make it simpler, the researcher agrees to define a scope that will be used is a note-taking application.

In order to test out the hypothesis, the researcher creates an arbitrary `passwords` , separated by four newlines (\n) and consists of random alphanumeric characters and symbols. It’s also unreadable but the ASCII constraints still stays between 32 and 126.

*Reference: [https://id.wikipedia.org/wiki/Berkas:ASCII-Table.svg](https://id.wikipedia.org/wiki/Berkas:ASCII-Table.svg)*

In CTF, we commonly used an identified prefix of the CTF event name for a starting flag’s occurrence such as `COMPFEST{`, `HackToday{` , `CSCCTF{` , and then followed by a hash value or a readable combination of an alphanumeric characters like `CSCCTF{y3Y_i_am_r3ad1ng_th!s_mediUm}` . But for this case, it’ll be more ASCII unreadable. For example, the unsaved file might contains a format like these:

```
s)(&^a
r#@fdJk
at4$sg
^%$j4r
t%$r3e
```

The challenge is designed to be harder to be guessed from [strings](https://www.howtogeek.com/427805/how-to-use-the-strings-command-on-linux/)command. Now you might think that this is very guessy and it shall only be extracted by finding the passwords with [grep/findstr](https://www.cyberciti.biz/faq/howto-use-grep-command-in-linux-unix/)command and [regular expressions](https://en.wikipedia.org/wiki/Regular_expression)shall be worked but those are likely to be unintended solution. We’ll focus on more to the technical approach, locate precisely where does the content needs to be extracted in the memory. You may skip until the next part if you’re already familiar with a basic functionality of `volatility` .

B. The Background

Before we dive in deeper with the tools mentioned above, it’d be better if we have an idea on how to extract such contents by a fundamentals of the theory about how those contents are allocated inside the memory.

We begin to determine the OS Profile of the memory dump using `volatility` plugin, `kdbgscan`.

```
python vol.py -f /home/kali/Desktop/memory_gone.vmem kdbgscan Volatility Foundation Volatility Framework 2.6.1
Instantiating KDBG using: /home/kali/Desktop/memory_gone.vmem WinXPSP2x86 (5.1.0 32bit)
Offset (P) : 0x29f2120
KDBG owner tag check : True
Profile suggestion (KDBGHeader): Win7SP1x64
PsActiveProcessHead : 0x2a2b940
PsLoadedModuleList : 0x2a49c90
KernelBase : 0xfffff8000280f000
Instantiating KDBG using: /home/kali/Desktop/memory_gone.vmem WinXPSP2x86 (5.1.0 32bit)
Offset (P) : 0x29f2120
KDBG owner tag check : True
Profile suggestion (KDBGHeader): Win2008R2SP0x64
PsActiveProcessHead : 0x2a2b940
PsLoadedModuleList : 0x2a49c90
KernelBase : 0xfffff8000280f000[SNIP]
Instantiating KDBG using: /home/kali/Desktop/Windows 7 x64-b77cc556.vmem WinXPSP2x86 (5.1.0 32bit)
Offset (P) : 0x29f2120
KDBG owner tag check : True
Profile suggestion (KDBGHeader): Win2008R2SP1x64_24000
PsActiveProcessHead : 0x2a2b940
PsLoadedModuleList : 0x2a49c90
KernelBase : 0xfffff8000280f000
```

You’ll see a lot of profile suggestions from the `volatility` tool due to a false positive result from the KDBG header heuristics value because of the behavior from an offset-based traversal-search of `kdbgsearch` . I’ve also attached about those “magic” headers value from one distinct Windows OS in my [Github](https://github.com/as3ng/RTLCTF/tree/main/Forensics/Impostor)writeups. No wonder if Win7 and Win2008 popped out from the OS Profile suggestions. We’ll use the first profile suggestion, Win7SP1x64.

Next up, we’ll list out the live processes that has been run inside the OS at the current state. You may use the following plugins:

- `plist`

- `pstree`

- `psscan`

- `psxview`

Again, further explanations are better discussed in [here](https://andreafortuna.org/2017/07/03/volatility-my-own-cheatsheet-part-2-processes-and-dlls/). Since we don’t deal with any hidden processes, we’ll focus on what’s the built-in note-taking apps that was mentioned from the scenario.

```
python vol.py -f /home/kali/Desktop/memory_gone.vmem --profile=Win7SP1x64 pslist
Volatility Foundation Volatility Framework 2.6.1
Offset(V) Name PID PPID Thds Hnds Sess Wow64 Start Exit
------------------ -------------------- ------ ------ ------ -------- ------ ------ ------------------------------ ------------------------------
0xfffffa8018da5040 System 4 0 80 567 ------ 0 2022-06-26 05:28:51 UTC+0000
0xfffffa8019d1b540 smss.exe 228 4 2 29 ------ 0 2022-06-26 05:28:51 UTC+0000
0xfffffa801ab4e060 csrss.exe 308 296 9 503 0 0 2022-06-26 05:29:12 UTC+0000
0xfffffa801ac631c0 csrss.exe 348 340 8 209 1 0 2022-06-26 05:29:13 UTC+0000
0xfffffa801ac4c310 wininit.exe 356 296 3 76 0 0 2022-06-26 05:29:14 UTC+0000
0xfffffa801aca5060 winlogon.exe 384 340 5 134 1 0 2022-06-26 05:29:14 UTC+0000
0xfffffa801abdf060 services.exe 444 356 9 213 0 0 2022-06-26 05:29:16 UTC+0000
0xfffffa801abee060 lsass.exe 460 356 7 754 0 0 2022-06-26 05:29:17 UTC+0000
0xfffffa801ac8a330 lsm.exe 468 356 10 137 0 0 2022-06-26 05:29:17 UTC+0000
0xfffffa801b00db00 svchost.exe 560 444 10 355 0 0 2022-06-26 05:29:21 UTC+0000
0xfffffa801b056470 svchost.exe 632 444 8 270 0 0 2022-06-26 05:29:22 UTC+0000
0xfffffa801b0ba5a0 sppsvc.exe 788 444 5 151 0 0 2022-06-26 05:29:25 UTC+0000
0xfffffa801a3894a0 svchost.exe 828 444 29 631 0 0 2022-06-26 05:29:27 UTC+0000
0xfffffa801b0cf720 svchost.exe 852 444 55 1312 0 0 2022-06-26 05:29:27 UTC+0000
0xfffffa801b0ecb00 svchost.exe 900 444 22 634 0 0 2022-06-26 05:29:27 UTC+0000
0xfffffa801b119060 audiodg.exe 932 900 5 120 0 0 2022-06-26 05:29:29 UTC+0000
0xfffffa801b172b00 svchost.exe 304 444 34 580 0 0 2022-06-26 05:30:41 UTC+0000
0xfffffa801b17b830 svchost.exe 552 444 25 537 0 0 2022-06-26 05:30:41 UTC+0000
0xfffffa801b2751a0 spoolsv.exe 1152 444 15 285 0 0 2022-06-26 05:30:47 UTC+0000
0xfffffa801b2818b0 svchost.exe 1180 444 19 339 0 0 2022-06-26 05:30:47 UTC+0000
0xfffffa8019a99b00 svchost.exe 1272 444 10 149 0 0 2022-06-26 05:30:48 UTC+0000
0xfffffa801b0f7b00 svchost.exe 1568 444 6 96 0 0 2022-06-26 05:30:53 UTC+0000
0xfffffa801a540060 svchost.exe 1940 444 25 271 0 0 2022-06-26 05:31:49 UTC+0000
0xfffffa8018ef2b00 svchost.exe 1668 444 11 363 0 0 2022-06-26 05:32:02 UTC+0000
0xfffffa8018fd8060 SearchIndexer. 952 444 14 773 0 0 2022-06-26 05:32:20 UTC+0000
0xfffffa801903eb00 taskhost.exe 2412 444 10 260 1 0 2022-06-26 05:32:46 UTC+0000
0xfffffa80190a1b00 dwm.exe 2496 828 3 73 1 0 2022-06-26 05:32:46 UTC+0000
0xfffffa8018fe1240 explorer.exe 2548 2472 24 813 1 0 2022-06-26 05:32:47 UTC+0000
0xfffffa8019115b00 regsvr32.exe 2668 2548 0 -------- 1 0 2022-06-26 05:32:50 UTC+0000 2022-06-26 05:32:52 UTC+0000
0xfffffa801913bb00 mscorsvw.exe 2836 444 5 82 0 1 2022-06-26 05:32:59 UTC+0000
0xfffffa80191bab00 mscorsvw.exe 2872 444 5 75 0 0 2022-06-26 05:33:01 UTC+0000
0xfffffa80191816e0 svchost.exe 2900 444 12 344 0 0 2022-06-26 05:33:02 UTC+0000
0xfffffa801929f060 wmpnetwk.exe 2636 444 10 211 0 0 2022-06-26 05:33:29 UTC+0000
0xfffffa80195989b0 StikyNot.exe 2776 2548 10 173 1 0 2022-06-26 05:34:26 UTC+0000
0xfffffa80192ad060 WmiPrvSE.exe 2108 560 7 120 0 0 2022-06-26 05:34:52 UTC+0000
0xfffffa80191ed060 notepad.exe 588 2548 1 58 1 0 2022-06-26 05:35:06 UTC+0000
0xfffffa80195138e0 CompatTelRunne 1848 444 2 51 0 0 2022-06-26 05:35:45 UTC+0000
0xfffffa8019549b00 conhost.exe 764 308 2 33 0 0 2022-06-26 05:35:45 UTC+0000
0xfffffa8019559600 CompatTelRunne 2600 1848 12 420 0 0 2022-06-26 05:35:45 UTC+0000
```

We can see that there are only 2 built-in note-taking apps that were used, a notepad and a Sticky Notes, so our exploration’s scope limit field is only there. Another basic findings that we should take a look is a `screenshot` plugin in order to see if there’s any indication that one of the application popped out in the visible window Desktop because the OS saves a pseudo SS based on GDI. Why is this important? This might comes handy for us to find the offset of the raw image dump later.

```
python vol.py -f /home/kali/Desktop/memory_gone.vmem --profile=Win7SP1x64 screenshot -D /home/kali/Desktop/ssVolatility Foundation Volatility Framework 2.6.1
Wrote /home/kali/Desktop/ss/session_0.Service-0x0-3e4$.Default.png
Wrote /home/kali/Desktop/ss/session_0.Service-0x0-3e5$.Default.png
Wrote /home/kali/Desktop/ss/session_0.msswindowstation.mssrestricteddesk.png
Wrote /home/kali/Desktop/ss/session_0.WinSta0.Default.png
Wrote /home/kali/Desktop/ss/session_0.WinSta0.Disconnect.png
Wrote /home/kali/Desktop/ss/session_0.WinSta0.Winlogon.png
Wrote /home/kali/Desktop/ss/session_0.Service-0x0-3e7$.Default.png
Wrote /home/kali/Desktop/ss/session_1.WinSta0.Default.png
Wrote /home/kali/Desktop/ss/session_1.WinSta0.Disconnect.png
Wrote /home/kali/Desktop/ss/session_1.WinSta0.Winlogon.png
```

If we check WinSta0.Default.png, we’ll notice a little hint.

A “flying” box up there looks like a Sticky Notes and we may able to parse or see it with color through a tools called [GIMP](https://www.gimp.org/). Although GIMP is known as the image manipulation tools, but its functionality also allows it to read and render a raw data at a certain offset. This technique has already been used a lot in some CTFs like from [here](https://developpaper.com/ctf-realizing-windows-memory-forensics-with-volatility-and-gimp/) and you can try it out yourself. Are you able read the sticky notes content? I’ll leave it as a bonus challenge for you!

*Reference: [https://developpaper.com/ctf-realizing-windows-memory-forensics-with-volatility-and-gimp/](https://developpaper.com/ctf-realizing-windows-memory-forensics-with-volatility-and-gimp/)*C. Diving into the Memories

We’ll focus now on the second application, Notepad. In order to achieve our objective, we should know how a user-input works inside a process of the Notepad itself. Did you know that whenever we type something in our keyboard, those data are stored inside an allocated memory inside our OS, and since the data doesn’t remain static, which means even if I write this medium story, the length of this story is not declared at first, so it happens in “runtime”. We can think of it like an array of characters (some kind of data buffer). So how to handle a dynamically allocated buffer? The [Heaps](https://www.geeksforgeeks.org/heap-data-structure/)takes the lead. This happens to the application too where they may allocate a memory regions on the heap.

So how does this application work inside such a process? The application itself is an executable which lives inside a certain memory region. A process has its own [virtual memory space](https://docs.microsoft.com/en-us/windows/win32/memory/virtual-address-space). This is just like a mobile app which also isolated. In Windows OS, there are numerous of [Windows APIs](https://docs.microsoft.com/en-us/windows/win32/apiindex/windows-api-list) that will track each of those processes by enumerating them.

If we take a look at this diagram below,

*References: [https://icegrave0391.github.io/2020/03/09/memfor-7/](https://icegrave0391.github.io/2020/03/09/memfor-7/)*

This is how a process memory architecture looks like. It has a dynamic [DLLs](https://docs.microsoft.com/en-us/troubleshoot/windows-client/deployment/dynamic-link-library)which are pretty obvious, especially when it comes in Windows, there are some default DLLs like kernel32.dll and et cetera. Each process also has an environment variables like an executable paths, some default directory locations and more just like or environment variable that consists of a default paths. There’s also PEB (Process Environment Block), a data structure in Windows that contains the list of location mappings inside the memory. A process heaps is the component that we’d investigate further since it contains the inputs that the application receives. Another layer, called thread stack, contains a function-calls locations.

Our objective now is to locate the input that has been typed inside the heaps of the certain process, and in this case, Notepad. Although there are some helpful plugins from `volatility` called notepad and heaps, it still doesn’t support the version of our OS Profile (only supports in WinXP and 2003 ).

```
#notepad.py [SNIP]

class _HEAP(obj.CType):
""" A Heap on XP and 2003 """

def is_valid(self):
return obj.CType.is_valid(self) and self.Signature == 0xeeffeeff

def segments(self):
""" A list of the _HEAP_SEGMENTs.

This is an array of pointers so we have to deref
before returning or the caller will be calling
is_valid on the pointer and not the object.
"""
return [seg.dereference() for seg in self.Segments if seg != 0]

class _HEAP_SEGMENT(obj.CType):
""" A Heap Segment on XP and 2003 """

def is_valid(self):
return obj.CType.is_valid(self) and self.Signature == 0xffeeffee

def heap_entries(self):
"""Enumerate the heaps in this segment.

##FIXME:
* Raise ValueError if corruptions are detected.
* Should we start at FirstEntry or Entry?
"""

next = self.Entry #FirstEntry.dereference()
last = self.LastValidEntry.dereference()

chunk_size = self.obj_vm.profile.get_obj_size("_HEAP_ENTRY")

while (next and
next.obj_offset < last.obj_offset):

yield next

next = obj.Object("_HEAP_ENTRY",
offset = next.obj_offset + next.Size * chunk_size,
vm = next.obj_vm)[SNIP]
```

So we’ll try to manually approach something in a way to list out the `heaps` memory region of the Notepad itself. We can do this by using the `VAD` plugins in volatility, like `vadtree` , `vadwalk` , `vaddump` , and `vadinfo` (Refer to this [page](https://resources.infosecinstitute.com/topic/finding-enumerating-processes-within-memory-part-2/)to know about the VAD information). Luckily, volatility supports a module output like `dot` , `png` , `xlsx` and we’re going to use one of them to demonstrate how the memory regions are allocated by the WinAPI and also locate the heap locations and its range. I’ll use the `vadtree` plugin and also the specific PID of the Notepad (588).

```
python vol.py -f /home/kali/Desktop/memory_gone.vmem --profile=Win7SP1x64 vadtree -p 588 --output-file=/home/kali/Desktop/vadtree.dot --output=dot
Volatility Foundation Volatility Framework 2.6.1
Outputting to: /home/kali/Desktop/vadtree.dot#-- convert dot format to PNG
dot vadtree.dot -Tpng > vadtree.png
```

The output will be like this,

Note that there are some colors like yellow, white, grey and red. This is very interesting because volatility has recognized the characteristics of each memory regions precisely known as color codes although there are some other colors that are not shown. It’s explained moreover in its [documentation](https://github.com/volatilityfoundation/volatility/wiki/Command-Reference#vadtree).

## Get aseng’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

A) Yellow -> contains a mapped files

B) Green -> contains a thread stack

C) Red -> contains the process heapsD) Grey -> contains DLLs

We can conclude that there are 6 memory (nodes) that contains the process heaps and we’ll investigate further on them. The alternative method is to use a volshell plugin from volatility.

```
python vol.py -f /home/kali/Desktop/memory_gone.vmem --profile=Win7SP1x64 volshell -p 588
Volatility Foundation Volatility Framework 2.6.1
Current context: notepad.exe @ 0xfffffa80191ed060, pid=588, ppid=2548 DTB=0x2bf7f000Welcome to volshell! Current memory image is:
file:///home/kali/Desktop/memory_gone.vmem
To get help, type 'hh()'
>>> list_of_process_heaps_address = proc().Peb.ProcessHeaps.dereference()
>>> list_of_process_heaps_address
<Array 4325376,65536,1310720,1572864,30277632,33357824>
>>> for i in [4325376,65536,1310720,1572864,30277632,33357824]:
... print(hex(i))
...
0x420000
0x10000
0x140000
0x180000
0x1ce0000
0x1fd0000
```

These are the starting addresses of the process heaps which are the same as the starting nodes of the VAD before when we tried to list them using `vadtree` before. Now for the final step, we’ll locate the exact content in the specific address that might be located in one of those process heaps address.

In order to find the user-input that are located in the process heaps, we’ll deal with a heap chunk state (concluded from _HEAP_ENTRY flags chunk). There are currently known some flags state (FREE,BUSY,EXTRA) but if there are more, please let us all know!

*Reference: [https://illmatics.com/Understanding_the_LFH_Slides.pdf](https://illmatics.com/Understanding_the_LFH_Slides.pdf)*

The notable struct-variable that we need to know is that the user input exists in the application if the HEAP_ENTRY_EXTRA_PRESENT is set (the flag’s set, with the value of 0x02) in the _HEAP_ENTRY->Flags and the state’s name is extra.

We’ll use [WinDBG](http://www.windbg.org/)to analyze the heap memory region further. In order for the debugger to parse the memory dump, we need to create a valid [OS Crash Dump](https://docs.microsoft.com/en-us/windows/client-management/generate-kernel-or-complete-crash-dump) first and luckily, `volatility` has the plugin called `raw2dmp` already. We also use volshell for the little support of dumping the data by the offset address.

```
python vol.py -f /home/kali/Desktop/memory_gone.vmem --profile=Win7SP1x64 raw2dmp -O /home/kali/Desktop/memdump_ctf/windump.dmp
Volatility Foundation Volatility Framework 2.6.1
Writing data (5.00 MB chunks): |...........................................................................................................................................................................................................................................................................................................................................................................................................................|
```

We’ll pass the DMP file to the WinDBG and note that it will detect the crash dump as a 16-bit process architecture first. This is a known issue and you can read it [here](https://social.msdn.microsoft.com/Forums/vstudio/en-US/4b306267-1fd2-431a-96c5-83a4f1c6b323/dx-command-of-windbg-is-strange-when-a-dmp-of-windbg-from-volatility-raw2dmp-is-analyzed?forum=wdk). In order to declare it to 64-bit, we’ll use the .effmach.

Then, we’ll need to switch the current context to our process, Notepad. In order to find the context address, we can use either this command or using PID-specified volshell which was found earlier (0xfffffa80191ed060).

Now we’ll have to make sure that the heap memory regions from the VAD node before are the same as the output that will be prompted after we send `!heap` command inside the WinDBG.

We need to inspect them one by one in order to retrieve our content and as we all already jotted down before, the heap chunk state needs to contain an extra.

I’ll attach the snipped output that contains the `extra` state,

```
[SNIP]000000000044fc90 000000000044fca0 0000000000420000 0000000000420000 250 c30 10 busy
000000000044fee0 000000000044fef0 0000000000420000 0000000000420000 60 250 20 busy extra user_flag
000000000044ff40 000000000044ff50 0000000000420000 0000000000420000 180 60 10 busy
00000000004500c0 00000000004500d0 0000000000420000 0000000000420000 110 180 10 busy[SNIP]0000000000454a50 0000000000454a60 0000000000420000 0000000000420000 60 3e0 10 busy
0000000000454ab0 0000000000454ac0 0000000000420000 0000000000420000 1b0 60 20 busy extra user_flag
0000000000454c60 0000000000454c70 0000000000420000 0000000000420000 90 1b0 2c busy extra user_flag
0000000000454cf0 0000000000454d00 0000000000420000 0000000000420000 b0 90 20 busy extra user_flag
0000000000454da0 0000000000454db0 0000000000420000 0000000000420000 40 b0 24 busy extra user_flag
0000000000454de0 0000000000454df0 0000000000420000 0000000000420000 30 40 2c busy extra user_flag
0000000000454e10 0000000000454e20 0000000000420000 0000000000420000 30 30 2c busy extra user_flag
0000000000454e40 0000000000454e50 0000000000420000 0000000000420000 30 30 20 busy extra user_flag
0000000000454e70 0000000000454e80 0000000000420000 0000000000420000 570 30 8 busy
00000000004553e0 00000000004553f0 0000000000420000 0000000000420000 b0 570 8 busy
```

We got the address already and now we will proceed to dump the content from the specified address. I’ll demonstrate the first address that has the `extra` first, which derived from 0x44fee0 to 0x44fef0. Note that this means the starting point is from 0x44fef0 to (the new heap region inside the first process heaps address — the previous starting point of heap region) which means the allocated size is 0x44ff40–0x44fef0 = 80.

Using volshell, we can dump it like this,

There are some unique characteristics that the memory has a null-bytes delimiter so all those null bytes may be ignored and the newline comes to be in a format of standard line-termination (\r\n) so it’s converted to be %0d%0a but if it’s in memory, it’s 0d 00 0a 00. Yet sometimes it doesn’t have that “\r” so it’s just 0a 00.

Some findings that support the theory of the line-termination relies here:

*Image snippets are taken from [http://www.maxi-pedia.com/line+termination+line+feed+versus+carriage+return+0d0a](http://www.maxi-pedia.com/line+termination+line+feed+versus+carriage+return+0d0a)*

You may figure it out now from the previous captured image, that’s the content of the notepad! The scenario says that those content separated by four newlines so it’s five distinct words.

```
g0O@
$#,&
%f3st
h4v$@
j$@rt
```

Final step is just to concatenate those words into one string (g0O@$#,&%f3sth4v$@j$@rt) and calculate its MD5 hash which results 856e37dae6a6f35deb2ee34912fd2476.

Final Flag ~> IFEST22{856e37dae6a6f35deb2ee34912fd2476}

Feel free to experiment with the other heap regions that has an `extra` state but you need to know that the content shall has at least 4 0d 00 0a 00 or with a combination of 0a 00. You can try it out yourself by your own to make a specific scenario but with a readable content this time!

---
