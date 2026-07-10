# :mag: Umdctf 2022 Write Ups C45Cdef017Bb

> **Original Source:** [Umdctf 2022 Write Ups C45Cdef017Bb](https://sutharnisarg.medium.com/umdctf-2022-write-ups-c45cdef017bb)
> **Platform:** sutharnisarg.medium.com | **Category:** `FORENSICS` | **Year:** 2022

---

## Forensics


### 1. Renzik’s Case


We’re given an image file `usb.img` which after loading in FTK shows the deleted files from the unallocated space. Simple one to begin with, nothing too complex.


*UMDCTF{Sn00p1N9_L1K3_4_SL317H!}*

### 2. How to Breakdance


For this one, we are given a `.pcap` file, which seems to include USB data.


Quickly going through the packets, you can notice the section of data that changes and one that stays the same. The interesting field here is `Leftover Capture Data` which includes the keystroke data sent from the keyboard to the host. Also notice that all packets have a field `usb.urb_type` which determines the direction of data transmission. `URB_COMPLETE` & `URB_SUBMIT` are the possible values for the same. We are looking for the direction keyboard to host, so let’s apply a filter for it: `usb.urb_type==URB_COMPLETE`


*The 8th byte will be set to a ‘C’ or an ‘S’ depending on the direction and the last 5 bytes (Byte 64–68) is what we want to extract which is the leftover capture data.*


To get all the leftover capture data we can use tshark to redirect the output. We apply the same filter to get all the packets from keyboard to host first and then export the `usb.capdata` field which is our ‘Leftover Capture Data’ in wireshark.


`tshark -r how_to_breakdance.pcapng -Y ‘usb.urb_type==URB_COMPLETE’ -T fields -e usb.capdata > keystrokes.txt`


Now all we need to do is map the HID usage codes in hex to the actual keys pressed. I wrote a python script to do the mapping and then removed all the newlines to get a big chunk of text to work with.


*UMDCTF{1_luv_70_f1nd_c7f_fl46s}*

### 3. Magic Plagueis the Wise


For this one, we’re given a large `.zip` file which had numerous `.png` files. Opening up the first image in HxD we can see a byte worth of data replacing the first byte of the default file signature for a `.png` which should be a `%` in ascii. Fixing the header results into a blank image for all files, which means the data that is being written is of interest.


*This pattern follows throughout the entirety of 4464 images.*


We can extract the first byte from all files like so: `head -c 1 * > firstchars.txt`and then simply process out the data from the additional noise.


*UMDCTF{d4r7h_pl46u315_w45_m461c}*

### 4. jdata


For this we have a `.zip` file that includes only an image inside at first glance, but I found a binary embedded inside it.


*Extract the elf binary so we can take a look in ghidra.*


`binwalk — dd=’.*’ jdata.zip` will search and extract every known file signature embedded.


*There is a function called hehe, which calls many other functions which only have a return statement. The function identifiers however, spell out something in reverse.*


`ghidraisforbinariesbroand` is the first half of the flag.


*Second half is in plaintext in the image, as aptly shown by the much useful red ellipse and arrow :) UMDCTF{ghidraisforbinariesbroandpubl1sh_s0m3_r3al_w0rk}*

### 5. Class Project


For this we’re given a VM image. In time crunch, instead of booting it up as a VM with provided password, I mounted it with Arsenal and used FTK to quickly look for interesting files in the filesystem.


*Right away, we have the flag base64 encoded.UMDCTF{f0rk_b0mb5_4r3_4_b4d_71m3}*

### 6. Kernel Infernal 1


This was the first time I came across a `.kdump` file. It stands for Kernel Dump, which is a mechanism in the Linux kernel to capture memory during a Kernel Panic. I used the crash utility to debug the memory dump.


*From the prompt we can see it hinting at pwd.*


The crash utility accepts 2 parameters, first is the Linux Kernel Object File that has the debugging switch set. You can get it from the corresponding OS index. Here we have a dump from `ubuntu20.04–5.4.0–99-generic` so find the equivalent debug symbol package and grab the object file from it.


The hint was ‘pwd’ which stands for present working directory, so I examined the backtrace first to determine which process caused the kernel panic. Then we can use the file command with the PID of that process.


*We can see a bash process with PID 5206 in backtrace.*


*Here we can see the current working directory for the same process.*


The challenge author wasn’t aware of the `files` command, and posted the intended solve on discord, which I wasn’t able to replicate but basically you have to traverse the `task_struct` structure to get the directory name, similar to how we would traverse an `_EPROCESS` structure to get ‘next process name’ and ‘previous process name’ from `ActiveProcessLinks` structure in a Windows memory dump.

*UMDCTF{T0ta11yCR45H!!}*

### 7. Still Crusin’


Again we have a VM image zipped and password protected, and an encrypted pdf. I started by cracking the pdf password using `john`.


*Use the same password to extract the VM image.*


Again, I just wanted to look at the filesystem so I didn’t boot up as it would take a lot of time. This time instead of FTK, I used R-studio as FTK wasn’t showing me some necessary deleted files. There were many deleted audio and image files to misdirect the players into deep steganography and spectral analysis rabbit holes. However I was able to find this hint so I quickly pivoted.


*I found this hint in this deleted file, to which my first thought was to do a keyword search.*


*UMDCTF{7h3r3'5_4_pl4c3_c4ll3d_k0k0m0}*

### 8. Kernel Infernal 2


For this one, we’re asked to find the address of the CR3 register.


CR3 enables the processor to translate logical addresses into physical addresses by locating the page directory and page tables for the current task.


CR3 contains the physical address of the page of the page directory table, so it is also called PDBR. This value is unique for each running process, since every process has it’s own page table.


So, we just need to walk the `task_struct` to get to the `pgd` pointer.


*UMDCTF{0xffff9b187a8e6000}*

---

*Originally published on [Medium](https://sutharnisarg.medium.com/umdctf-2022-write-ups-c45cdef017bb). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
