# :mag: Forensics - Memory Analysis with Volatility

---

## Task 1: Volatility Forensics

>

1. What is the Operating System of this Dump file? (OS name)

Volatility needs profiles to work. When we have the memory image file we want to analyze, we first need to use the command see below:

```
$ volatility -f victim.raw imageinfoVolatility Foundation Volatility Framework 2.6
INFO : volatility.debug : Determining profile based on KDBG search...
Suggested Profile(s) : Win7SP1x64, Win7SP0x64, Win2008R2SP0x64, Win2008R2SP1x64_24000, Win2008R2SP1x64_23418, Win2008R2SP1x64, Win7SP1x64_24000, Win7SP1x64_23418
AS Layer1 : WindowsAMD64PagedMemory (Kernel AS)
AS Layer2 : FileAddressSpace (/home/kali/Downloads/Capture-The-Flag/Forensics/victim.raw)
PAE type : No PAE
DTB : 0x187000L
KDBG : 0xf800028420a0L
Number of Processors : 1
Image Type (Service Pack) : 1
KPCR for CPU 0 : 0xfffff80002843d00L
KUSER_SHARED_DATA : 0xfffff78000000000L
Image date and time : 2019-05-02 18:11:45 UTC+0000
Image local date and time : 2019-05-02 11:11:45 -0700
```

Once this command is run, Volatility will identify the system the memory image was taken from, including the operating system, version, and architecture. Volatility will suggest the recommended profile and when running any other command on this memory image we need to provide the profile as well. The suggested profile is Win7SP1x64 and we can therefore say that the OS of this dump file is Windows.

>

2. What is the PID of SearchIndexer?

We can identify the process ID (PID) of the SearchIndexer process, by using the pslist plugin provided by volatility. We will use the profile Win7SP1x64 identified earlier and specify the pslist plugin, as seen in the command below:

```
volatility -f victim.raw --profile=Win7SP1x64 pslist
```

Looking through the output, we can see the SearchIndexer process and it’s PID:

*Volatility “pslist” plugin output.*

>

3. What is the last directory accessed by the user? (The last folder name as it is?)

For this question, we are provided a hint which states:

>

Why don’t you search a bag full of shells in your backyard?

This hint refers to the Shellbags plugin for Volatility. This plugin parses and prints [Shellbag (pdf)](http://www.dfrws.org/2009/proceedings/p69-zhu.pdf) information obtained from the registry. More information can be found about this plugin using the link below:

Using this plugin, we can identify files, folders, zip files and installers that existed at one point on the system (even if deleted), as well as there Metadata (timestamps and absolute paths).

```
volatility -f victim.raw --profile=Win7SP1x64 shellbags
```

We can look down through the output, and based on the Access Date field, identify the last directory accessed by the user. After some searching, I found the following directory:

*Volatility “shellbags” plugin output.*

---
