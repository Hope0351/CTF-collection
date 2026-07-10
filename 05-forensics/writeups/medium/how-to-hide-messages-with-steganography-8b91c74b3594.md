# :mag: How to use Steganography for attacks or to hide messages

---

# How to use Steganography for attacks or to hide messages

## Overview

*Introduction from one of my previous article on Digital Forensics:*

Steganography is a technique used to hide data within a digital file. It is a powerful tool for concealing sensitive information from prying eyes. The data can be hidden in various types of media, such as images, audio files, or videos.

Steganography is used in a variety of applications, such as copyright protection, secure communication, and data storage. It is also used in digital forensics to uncover hidden evidence.

By distilling the concepts of steganography we can highlight the three key elements in: Secret, Carrier and Carrier’.

Secret: This is the element that needs to be hid in the *Carrier*. The *Secret* could be anything (string, image, audio, pdf, etc..), the only constrain is that must be shorter (in terms of bytes) than the *Carrier*.

Carrier: This element is the one in which our *Secret* will be stored. It could be an image or a file audio in the simplest scenario. The *Carrier* must be (in terms of bytes) longer than the *Secret.*Carrier’: The *Carrier’* is the *Carrier* with the *Secret* encoded inside.

---
