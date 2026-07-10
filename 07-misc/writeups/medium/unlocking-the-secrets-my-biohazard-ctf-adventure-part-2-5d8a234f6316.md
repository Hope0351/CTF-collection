# :game_die: Unlocking the Secrets: My Biohazard CTF Adventure Part 2

---

**3.2.** Password for the encrypted file

So here we are anyway, we need to decrypt the** helmet key**. Actually, we haven’t finished exploring the other files yet. Don’t worry about the **gpg.hash** we created earlier for cracking the helmet key just forget about it for now.

*[ files]*

There are three **.jpg** images. Let’s take a look and see if they contain any hints.

*[ .jpg ]*

I opened all three images, but there was nothing inside. However, do you notice a **pattern**? I’ll show you.

*[ key ]*

>

We’ve done something similar before when finding the FTP username and password. So what actually happened there? We needed to **collect four crests**, then **decode them and combine them into one string**. After decoding that string again, we finally got the result.

I think something similar is happening here, but this time with image files. Let’s inspect them. I’ll first determine the file type, just like we did before with the **.gpg** extension.

**command**:

```
file <input-file>
```

**example:**

```
file 001-key.jpg
```

**001-key.jpg**:

```
001-key.jpg: JPEG image data, JFIF standard 1.01, aspect ratio, density 1x1, segment length 16, baseline, precision 8, 400x320, components 3
```

This one’s just a regular image. Let’s check the next one.

**002-key.jpg:**

```
002-key.jpg: JPEG image data, JFIF standard 1.01, aspect ratio, density 1x1, segment length 16, comment: "5fYmVfZGVzdHJveV9", progressive, precision 8, 100x80, components 3
```

But here, we found something interesting a string hidden in the comment of** 002-key.jpg** . It looks like it could be **Base64** encoded.

```
comment: "5fYmVfZGVzdHJveV9",
```

I put this string into **CyberChef**, and after inspecting its properties, it turned out to be **Base85 **encoded.

*[ CyberChef ]*

Maybe it’s related to the key. Let’s note it down and move on to the next **.jpg** file.

**003-key.jpg:**

```
003-key.jpg: JPEG image data, JFIF standard 1.01, aspect ratio, density 1x1, segment length 16, comment: "Compressed by jpeg-recompress", progressive, precision 8, 100x80, components 3
```

So, in the comment section, it’s not an encrypted string. It shows:

```
comment: "Compressed by jpeg-recompress",
```

This isn’t just an ordinary image there’s something hidden behind it, possibly compressed within the file. What if we try to decompress it like a **zip** file?

**command:**

```
unzip 003-key.jpg
```

**out:**

*[ unzip ]*

Inside, we found a file named **key-003.txt**.

*[ extracted ]*

So, as you can see, a new file called **key-003.txt** has appeared. Let’s inspect it.

*[ key-003.txt ]*

as you can see, a new file called **key-003.txt** has appeared. Let’s inspect it.

```
001-key ?

002-key 5fYmVfZGVzdHJveV9

003-key 3aXRoX3Zqb2x0
```

By the way, notice this difference:

*[ file ]*

Actually, this is **my way** of finding those keys. There’s an exact, proper method to extract them but then why did I show you this?

*[ GIF sourced from tenor. Rights belong to the creator. ]*

Because it **might help in different situations**, I wanted to show you my approach. Let me make it clear, we are dealing with **steganography**.

If you want to learn more, here’s a reference you can check out:

**Steganography** is the practice of hiding data inside an image in various ways. There are many different types, and I won’t go into all of them here it would take too long but you can explore them through the link provided.

Sometimes, we find a **text file embedded inside an image**. Other times, different types of data are hidden, which means we need to use different tools to **reveal the hidden information**.

I’ll show you how to use these tools to extract hidden data:

- steghide

- stegseek

- exiftool

- binwalk

**[ steghide ]command:**

```
steghide --info 001-key.jpg
```

This command helps you **analyze an image** to check if it contains any hidden messages or files without actually extracting them.

*[ steghide ]*

After hitting **y**, it will ask for a passphrase just press **Enter**!

Once you run this command, it shows that a file called **key-001.txt** is embedded in **001-key.jpg**.

If you want to **extract that embedded text file** from the image, here’s how to do it:

**command:**

```
steghide --extract -sf 001-key.jpg
```

When it asks for a passphrase, just hit **Enter**, and the file will be extracted!

*[ steghide ]*

Let’s take a look at the extracted text:

*[ key-001.txt ]*

Now we have the **first key**!

You might be wondering about the parameters I used with **steghide**:

```
--info -> display information about a cover- or stego-file
--extract -> extract data
-sf -> select stego file
```

There are more parameters available just type **steghide** to see all the options.

**[ stegseek ]**

Now, let’s move on to s**tegseek**. We didn’t use this earlier, but it can be really helpful.

Do you remember when we tried to get information from the image using **steghide**?

*[ steghide ]*

Here, I told you to just hit **Enter** when prompted for a passphrase. In our case, it wasn’t needed, but this **won’t always be the case**.

If the creator embeds a passphrase, you’ll need to find it because that’s the only way to extract the hidden data or file.

Let me show you a **scenario**:

Here, you can see an image in my **demo** directory.

*[ cat.jpg ]*

I created a file called **secret.txt** and embedded it inside **cat.jpg** using **steghide**.

*[ steghide ]*

Here, you can see that it’s asking for a passphrase. So, I set a passphrase for it.

*[ steghide ]*

Notice here that to extract the embedded text file, you **must provide the correct passphrase**.

>

The old trick hitting **Enter** with a blank password like we did for **001-key.jpg** won’t work this time.

What would you do in this scenario?

*[ GIF sourced from tenor. Rights belong to the creator. ]*

In this situation, we can use **stegseek** to **brute-force the passphrase** using a wordlist.

**command:**

```
stegseek cat.jpg -wl /usr/share/wordlists/rockyou.txt
```

**result:**

*[ stegseek ]*

It detected the passphrase, which was **silver**. The original file we embedded, **secret.txt**, was extracted as **cat.jpg.out**.

## Get Adwaith S’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Let’s see how it works by checking the extracted file:

*[ cat.jpg.out ]*

We successfully extracted the embedded file. Sometimes, a **.jpg** is protected by a passphrase, so this method can be very helpful it’s a common way to find the passphrase.

Now, if we look at the other **.jpg** files (excluding **001-key.jpg**):

*[ steghide ]*

This means we need a **passphrase**. It’s asking for one as well so can we brute-force it?

This is exactly why I suggested **manually inspecting **the** .jpg **files and checking their formats first.

*[ file ]*

When you examine the files carefully, the approach becomes clearer. **001-key.jpg **has no comments or hidden content, so there’s no need for **stegseek** or additional tools. In contrast, the second image contains a comment, and the next key was compressed this gives clues about which method to use and helps avoid confusion. I hope this method is useful.

**[ exiftool ]**

This tool helps you gather more information about an image. You can **extract comments** and other metadata as well.

**command:**

```
exiftool 002-key.jpg
```

**002-key.jpg:**

*[ exiftool ]*

**003-key.jpg:**

*[ exiftool ]*

When you look closely, you’ll notice **comments in both images** along with other information. There’s even more you can do with **ExifTool **just type **exiftool** in your terminal to explore its features.

**[ binwalk ]**

*[ binwalk ]*

Here, you can see that when we run this single command, it shows that a **zip file exists** in the image, including the name of the text file inside.

**command:**

```
binwalk -e 003-key.jpg
```

After extracting the **.jpg** , a new directory appeared called **_003-key.jpg.extracted**.

*[ extracted ]*

Let’s see what’s inside that directory. Here we have **key-003.txt**.

*[ key-003.txt ]*

Let’s cat that file. And here it is our **key**!

*[ key-003.txt ]*

Of course, these aren’t the only tools or methods for steganography, there’s a lot more to explore. I’ll cover a deeper dive in a future post.

For now, we’ve successfully obtained our **keys**:

```
001-key -> cGxhbnQ0Ml9jYW
002-key -> 5fYmVfZGVzdHJveV9
003-key -> 3aXRoX3Zqb2x0
```

What we need to do now is **combine all the strings into one**:

```
cGxhbnQ0Ml9jYW5fYmVfZGVzdHJveV93aXRoX3Zqb2x0
```

At last, take the combined string, drop it into **CyberChef**, and apply the **“Magic” recipe**. This will give you the **passphrase** for the **.gpg** file.

*[ CyberChef ]*

Now we have the **password** for the encrypted file.

---
