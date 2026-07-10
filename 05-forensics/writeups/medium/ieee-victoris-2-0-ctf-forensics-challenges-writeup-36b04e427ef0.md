# :mag: IEEE Victoris 2.0 CTF Forensics Challenges Writeup

---

# IEEE Victoris 2.0 CTF Forensics Challenges Writeup

Hello and welcome,
I’m Mohamed Adel and this is my writeup for forensics challenges at IEEE Victoris 2.0 CTF organized by [IEEE ManSB](https://www.facebook.com/IEEEManSB) and powered by EGCERT.

Let’s start with the first one.

## VulnPass:

>

Category: Memory ForensicsDownload the challenge from [here](https://mega.nz/file/fxVUUbwT#AukwW87Agzxx-q0TZGomyWkpcgaOMFmx8BwhxWlWNsg)and try to solve it.

It’s a *memory dump*, so I will use my lovely tool [Volatility3](https://github.com/volatilityfoundation/volatility3).

At first, we need to know the *processes* that were run, so will use the *Pslist *plugin, and then we will see the last program the user opened *KeePass*.

```
python3 vol.py MEMDUMP.mem windows.pslist.PsList
```

Okay, now when using the *cmdline *plugin will see this file.

```
python3 vol.py MEMDUMP.mem windows.cmdline.CmdLine
```

Need to *dump *the file, so, use the *Filescan *plugin and *grep *for it to get the *Virtaddr.*

```
python3 vol.py MEMDUMP.mem windows.filescan.FileScan
```

Now, *dump *the second file with the *dumpfiles *plugin and the *Virtaddr *is *0xc60007b1b820, *and rename the file.

```
python3 vol.py -f MEMDUMP.mem windows.dumpfiles.DumpFiles --virtaddr 0xc60007b1b820
```

Move the file on windows and try to open it, it needs a password.

>

Note:
You need to download and install the [KeePass](https://keepass.info/download.html)program to open the Database file.

Return to the memory dump to search for the password but nothing.

After more searching, I found [this](https://www.forensicxlab.com/posts/keepass/)great blog talk about the *KeePass *Plugin in Volatility3, So I downloaded the Plugin from [here](https://github.com/forensicxlab/volatility3_plugins/blob/main/keepass.py)and moved it to the path *volatility3/plugins/windows/*

Now, need to use it with the *pid *of the *KeePass *process *8528, *and yes, we got the password.

```
python3 vol.py -f MEMDUMP.mem windows.keepass --pid 8528
```

When tried to open the Database file the password was wrong.

Ok, keep calm and read the password, you will find it is “ecretpass123”, at first look it seems like “secretpass123”, so the password is missing the letter “s”, but we don’t know whether it is a capital or a small letter, Tried the 2 possibilities and the correct password was in a capital litter which in final is “S3cr3tP4ss123”, then open the Database.

*Right-click* on the *password *of *C2* and *copy *it, then *paste *it into any *text editor*, and you will get the *flag*.

```
Flag: EGCERT{10_P0ints_t0_Gryff1nd0r}
```

### Another Method:

You can solve this challenge with *strings*.

```
strings MEMDUMP.mem | grep -i -A 1 egcert
```

Just remove 0 from the end of the first line.

>

I hate the challenges that the flag stored in it, I prefer the challenges with questions.

---
