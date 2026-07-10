# :globe_with_meridians: Cyber Apocalypse CTF 2022 — Web — Amidst Us Write-up

---

# Cyber Apocalypse CTF 2022 — Web — Amidst Us Write-up

Prompt:

Amidst Us
The AmidstUs tribe is a notorious group of sleeper agents for hire. We have plausible reasons to believe they are working with Draeger, so we have to take action to uncover their identities. Ulysses and bonnie have infiltrated their HQ and came across this mysterious portal on one of the unlocked computers. Can you hack into it despite the low visibility and get them access?

Start:

It is a web challange and we have the source code of the application, so we are downloading it and building it to test it on our local before get the flag from the real website.

Firstly we are checking website and its functionality,

The website is like a darkroom and we have flashlight. I’m checking for any clickable thing there and I found if we click to the ufo, it gives opportunity to upload image. When I uploaded it, the image rendered on the same page..

And there is another interactive part, there we can change the color for something..

When I try to intercept them, I couldn’t.. In order to intercept them, you might need to tell it to proxy images and stuff, default is to hide css, images, and binary.

For burp suite, Follow the below path..

## Get zer0dac’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Proxy > Optiıns > Intercept Client Request >> Untick the File extension option.

Then we can intercept the request.

When I check the source code, I’m always checking the required things for application to see if there is any version vulnerability. And on this application, we are seeing Pillow 8.4.0. The question is why this version is especially required.

When we research it, we understand that the application uses Pillow to handle images, which is vulnerable to code execution if run through eval (which it is doing) [https://security-tracker.debian.org/tracker/CVE-2022-22817](https://security-tracker.debian.org/tracker/CVE-2022-22817)

Let’s turn back to the codes and see if any eval function.

Yeah there is eval function which is comes from ImageMath..

In the below of code, it is converting image from base64 etc..

And for the routing part, it is just checking if it is JSON or it includes image.. So, injecting our payload to one of background rgb color is best way.. From source code we know exactly the paths, so we can write flag to some path.(first you may try id,whoami, or ping methods if you don’t have the source code for RCE vulnerabilites)

As it is external website, I didn’t get a reverse shell for flag.. It requires ngrok or external ip, so this is the easy way.

---
