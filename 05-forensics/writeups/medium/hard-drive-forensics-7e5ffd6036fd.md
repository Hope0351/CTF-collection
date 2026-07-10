# :mag: Uncovering Digital Evidence: A Guide to Investigating Physical Hard Drives for Criminal Investigations

> **Original Source:** [Uncovering Digital Evidence: A Guide to Investigating Physical Hard Drives for Criminal Investigations](https://infosecwriteups.com/hard-drive-forensics-7e5ffd6036fd)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS`

---

# Uncovering Digital Evidence: A Guide to Investigating Physical Hard Drives for Criminal Investigations


Imagine you are given a hard drive that you need to examine for a criminal investigation. As is for handling all evidence, you need to be extremely careful how you examine it and with the correct tools, since an improper approach can corrupt it, making it unuseful. This post is about how to handle digital evidence, specifically, the investigation of a physical hard drive while a similar approach is also applicable to other storage devices.


To summarize the following sections, I will show you how to:


- Make a copy of the disk

- Bind disk image to a block device

- Mount and examine it inside [libguestfs](https://libguestfs.org/)


I will be using a terminal on my Linux Ubuntu machine. If you are currently running Windows, set yourself a VM with any Linux OS distribution you like — Ubuntu, Xubuntu, and Debian should do fine, but there are lots of others that do the job too.

### Disk copy


Consider we are given a hard drive with digital evidence. The first and far most important thing we need to do is make a full copy of the hard drive into a disk image. Why? Well, we almost always want to perform an investigation on a copy, therefore if anything goes wrong…

---

*Originally published on [Medium](https://infosecwriteups.com/hard-drive-forensics-7e5ffd6036fd). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
