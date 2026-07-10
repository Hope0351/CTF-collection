# :game_die: Beginners Ctf Guide Finding Hidden Data In Images E3Be9E34Ae0D

> **Original Source:** [Beginners Ctf Guide Finding Hidden Data In Images E3Be9E34Ae0D](https://infosecwriteups.com/beginners-ctf-guide-finding-hidden-data-in-images-e3be9e34ae0d)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

### Binwalk


Binwalk is a tool that allows you to search binary images for embedded files and executable code. We can use binwalk to search images for embedded files such as flags or files that may contain clues to the flag.


You may need to download binwalk on your system. Run the following command to install binwalk.


```
mrkmety@kali:~ $ sudo apt install binwalk -y
```


Example 1:
You are provided an image named [dog.jpg](https://github.com/mkmety/Medium-Steg-Image/blob/master/dog.jpg).
Run the following command to see if Binwalk finds any embedded files.


```
mrkmety@kali:~ $ binwalk dog.jpg
DECIMAL HEXADECIMAL DESCRIPTION

0 0x0 JPEG image data, JFIF standard 1.01
88221 0x1589D Zip archive ... name: hidden_text.txt
88384 0x15940 End of Zip archive, footer length: 22
```


Binwalk detects a zip file embedded within dog.jpg. The file within the zip file is named hidden_text.txt.


You can extract hidden files by running the following command.


```
mrkmety@kali:~ $ binwalk -e dog.jpgDECIMAL HEXADECIMAL DESCRIPTION

0 0x0 JPEG image data, JFIF standard 1.01
88221 0x1589D Zip archive data, ... hidden_text.txt
88384 0x15940 End of Zip archive, footer length: 22
```


A directory named ‘_dog.jpg.extracted’ has been created with the file automatically unzipped.


```
mrkmety@kali:~ $ cd _dog.jpg.extracted/
mrkmety@kali:~/_dog.jpg.extracted $ ls -l
total 8
-rw-r--r-- 1 pi pi 185 Jul 5 19:50 1589D.zip
-rw-r--r-- 1 pi pi 21 Jul 5 15:39 hidden_text.txt
mrkmety@kali:~/_dog.jpg.extracted $
mrkmety@kali~/_dog.jpg.extracted $ cat hidden_text.txt
THIS IS A HIDDEN FLAG
```


Running the cat command on the embedded text file reveals “THIS IS A HIDDEN FLAG.”

---

*Originally published on [Medium](https://infosecwriteups.com/beginners-ctf-guide-finding-hidden-data-in-images-e3be9e34ae0d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
