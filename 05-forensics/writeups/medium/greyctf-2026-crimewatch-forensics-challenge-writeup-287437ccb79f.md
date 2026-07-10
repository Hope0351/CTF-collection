# :mag: Greyctf 2026 Crimewatch Forensics Challenge Writeup 287437Ccb79F

---

We are provided with 2 weird files named `"a"` and `"b"`, and a python file as shown:

the below screen shows the conclusion for `flag.py` file.

so, we are provided with weird files, we need to determine what are these format.

So with HxD and a little research, i could determine that this magic bytes are [qcow](https://en.wikipedia.org/wiki/Qcow)file format, which stands for “QEMU [Copy On Write](https://en.wikipedia.org/wiki/Copy-on-write)”.

So it’s a qemu disk images, but both files are just unallocated space on FTK

So, we need to convert them to a readable disk images to open properly.
After a little research i found this tool: [qemu-img](https://cloudbase.it/qemu-img-windows/)*, so let’s try this tool*

now we need to convert them

after conversion, we could open on FTK Imager

only the b disk image opened properly. after a long research and a very long chats with different AI models :), i was able to cofirm that `a`is Android FBE-encrypted userdata and `b`is the metadata partition needed to decrypt `a`.
finally i found an amazing tool: [fbe-decrypt](https://github.com/SlugFiller/fbe-decrypt)*, now let’s work to decrypt *`a`*.*

## Get Loay Salah’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

We just need to rename the files with the intended names based n the script to could run perfectly.

And now we can run and see the precious output here
*NOTE: First, you will need to install NodeJS*

Now we can investigate the disk image properly on FTK with no issues

Now, Let’s head back to the python script and start real investigation.

After walking around and deep searching, i found a very important note on the notifications file located in: `/system_ce/0/notification_history/notification_history.xml`

now i got 2 answers directly, and one glance for the third
first: telechat account is: `@vanta_supply
`second glance: plate numbers maybe starts or ends or contains:`..SG673..
`third: the buyer we suspect is: `jiawei`

After a long digging also, found this amazing picture located in:
`/media/0/Pictures/TeleChat/IMG_20260514_164900.png`

Now we got the full car plate number: `SG67301K`Now for the tricky part, the last question needs the coordinates to identify the pickup point.

There’s another image in the directory called `spot.jpg`, i guess it’s a clue

that’s a big clue and its called spot, so let’s get the exact coordinates.

wanna do a big shoutout to my friend for helping me get the exact coordinates

Found exactly the same view on different platforms such as: [alamy](https://www.alamy.com/singapore-circa-2018-lilly-pads-in-a-pond-bathed-in-evening-light-and-ripples-in-the-famous-botanic-gardens-singapore-as-nature-background-with-sp-image364466725.html?imageid=20FB8FFE-CD80-4AE7-BD8D-CB76B424D378&pn=1&searchId=9dfd5025a12e0c6d90aafd31c6a327f2&searchtype=9)and facebook post [here](https://www.facebook.com/taste.travel.tell/posts/pfbid02Y19yKHTmRgV9RAp565uadeY9ao7Lvkv2FcG2ZKf1qw3TB9egGbRvzky7icKSnfSul?rdid=EqrEte4tCNofUbYD#), and finally found a good person on [flickr](https://www.flickr.com/photos/dannyfoster/9511153795)posted the exact image with the exact location here: [https://www.flickr.com/map/?fLat=1.401333&fLon=103.794833&zl=13&everyone_nearby=1&photo=9511153795](https://www.flickr.com/map/?fLat=1.401333&fLon=103.794833&zl=13&everyone_nearby=1&photo=9511153795), so i got it from the url itself.
getting the exact coordinates on google maps [HERE](https://www.google.com/maps/place/1%C2%B024'04.8%22N+103%C2%B047'41.4%22E/@1.4013335,103.794792,3a,49.3y,143.02h,78.5t/data=!3m7!1e1!3m5!1s0_5Ju7VRToOB7wcSw5aNiA!2e0!6shttps:%2F%2Fstreetviewpixels-pa.googleapis.com%2Fv1%2Fthumbnail%3Fcb_client%3Dmaps_sv.tactile%26w%3D900%26h%3D600%26pitch%3D11.502224645524834%26panoid%3D0_5Ju7VRToOB7wcSw5aNiA%26yaw%3D143.01629719088223!7i13312!8i6656!4m4!3m3!8m2!3d1.401333!4d103.794833?entry=ttu&g_ep=EgoyMDI2MDUyNy4wIKXMDSoASAFQAw%3D%3D)

### So Let’s Get the FLAG

---
