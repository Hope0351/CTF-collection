# :mag: Understanding Steganography for Capture The Flag(CTF) Challenges !

---

# Understanding Steganography for Capture The Flag(CTF) Challenges !

## what is Steganography? where it is used? Steganography in CTF’s

Hello everyone I hope you all are doing well. Today we gonna learn about Steganography and we will be doing some HackTheBox challenges. So without wasting any time let’s get started.

## What is Steganography?

>

*Steganography is a way of hiding a secret message inside something .For example hiding secret within a image or audio file.*

There are many tools that can help you to hide a secret message inside an image or another file type. One of The most famous tool is steghide . More on this later.

There are two types of steganography :

(i) Physical

(ii) Digital

In this article, we will be learning about Digitalsteganography

## Where is steganography used?

>

*Government agency’s like SVR uses steganography for certain communicationsSource :*[https://en.wikipedia.org/wiki/Steganography](https://en.wikipedia.org/wiki/Steganography)

*Malicious hackers use steganography for different types of attacks. Some of the most famous are embedding actual scripts within macro-enabled Word document, Or in songs or movies.If you want to learn more check this article*[https://portswigger.net/daily-swig/what-is-steganography-a-complete-guide-to-the-ancient-art-of-concealing-messages](https://portswigger.net/daily-swig/what-is-steganography-a-complete-guide-to-the-ancient-art-of-concealing-messages)

## How to Hide a text file to an Image

We need to install steghide. If you are using kali then *sudo apt install steghide .*

We will use command steghide embed -ef select file to be embedded <filename> -cf embed into the file <filename>

Now we will extract our data

## Get ZeusCybersec’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

we will use command steghide extract -sf write result to <filename> instead of cover-file <filename>

## Time to do Some CTF

1:- CTF Hackerman [https://app.hackthebox.com/challenges/17](https://app.hackthebox.com/challenges/17)

I will be telling you my method of how I do steg challenges in any CTF.

STEPS:-

1:- Download the challenge file

2:- After downloading the file I always run ExifTool against the file. (In CTF you can find passphrases or some other useful stuff.)

3:-Then I will run the strings command (print the sequences of printable characters in files). After that, I use other tools like steghide, foremost.

checking EXIF data

strings

Since I don’t know the passphrase, I tried to brute force it with stegcracker.

stegcracker

cracking password

We have got our passphrase ‘almost’.Now we can extract the hidden file with steghide

final output

Our output is base64 encoded we can simply base64 decode it.

>

Article Credits: Written by make sure to Follow Hac on Twitter-[https://twitter.com/Hac10101](https://twitter.com/Hac10101)

---
