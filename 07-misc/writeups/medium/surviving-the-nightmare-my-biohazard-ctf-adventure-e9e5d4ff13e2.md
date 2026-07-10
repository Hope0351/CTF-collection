# :game_die: Surviving the Nightmare: My Biohazard CTF Adventure

---

2.5. What is the shield key flag

in our done list:

```
/diningRoom/ ----> input emblem flag!
/teaRoom/
/artRoom/
/barRoom/
```

Next, we head to /diningRoom2F/

### [ Dining room 2F ]

*/diningRoom2F/*

A Blue Gem is mentioned, but no link is present. Time to inspect /diningRoom2F/

*[ source ]*

Here, we can see a comment

```
<!-- Lbh trg gur oyhr trz ol chfuvat gur fgnghf gb gur ybjre sybbe. Gur trz vf ba gur qvavatEbbz svefg sybbe. Ivfvg fnccuver.ugzy -->
```

From my experience, it looks like an ROT13 cipher is used here though this is just a guess, as many ciphers can look similar. If you don’t know, ROT13 is a simple letter substitution cipher that replaces each letter with the 13th letter after it in the Latin alphabet.

Here’s a diagram to help understand how it works:

*[ ROT13 mapping ]*

Not sure what a cipher, ROT13, or “13th letter” means? No worries I’ve got some references you can check to understand the concept. You don’t need to read them all, just get the idea.

In CyberChef, we’ll drag and drop the ROT13 operation instead of using Magic.

*[ CyberChef ]*

Next, paste the cipher into the Input section, and the Output will show:

*[ CyberChef ]*

From the decoded text, we got a hint: the Blue Gem can be obtained by pushing the status to the lower floor. Since we’re currently in /diningRoom2F/ (second floor), let’s move to the first floor by modifying the path to /diningRoom/sapphire.html and visiting it.

*/diningRoom/sapphire.html*

Flag captured: blue_jewel!

Wait, this isn’t what we needed, we got the blue_jewel flag, but we actually need the shield_key flag! Note this down somewhere, as we’ll need it later. For now, /diningRoom2F/ is completed, so let’s keep moving.

In our done list:

```
/diningRoom/ ----> input emblem flag!
/teaRoom/
/artRoom/
/barRoom/
/diningRoom2F/
```

our next destination is /tigerStatusRoom/

### [ Tiger status room ]

*/tigerStatusRoom/*

An input box asks for a gem on the Tiger’s Eye.

We got it from /diningRoom/sapphire.html, so submit the blue_jewel flag! and see what happens.

*/tigerStatusRoom/gem.php*

An encoded string here gives a hint: it’s double-encoded and 14 letters long. It says to collect 4 crests, decode them, and combine them to reveal another path. Note this, as we need 3 more crests. /tigerStatusRoom/ is done, let’s continue.

In our done list:

```
/diningRoom/ ----> input emblem flag!
/teaRoom/
/artRoom/
/barRoom/
/diningRoom2F/
/tigerStatusRoom/
```

Our next destination is /galleryRoom/

### [ Gallerty ]

*/galleryRoom/*

Here, there’s a hyperlink called EXAMINE. Let’s visit it and see what’s inside.

*/galleryRoom/note.txt*

We got the second crest! Note it down this one is double-encoded, and the output length is 18 letters. With this, /galleryRoom/ is complete.

In our done list:

```
/diningRoom/ ----> input emblem flag!
/teaRoom/
/artRoom/
/barRoom/
/diningRoom2F/
/tigerStatusRoom/
/galleryRoom/
```

Our next destination is /studyRoom/

### [ Study room entrance ]

*/studyRoom/*

An input box appeared asking for a Helmet symbol / the Helmet flag to enter the Study Room. There are no hyperlinks, and I inspected the page no comments, hints, or clues. I tried all the flags we have, but none worked. Did we miss something? Nope. Let’s leave this page for now and come back later. Time to move to the next destination.

In our done list:

```
/diningRoom/ ----> input emblem flag!
/teaRoom/
/artRoom/
/barRoom/
/diningRoom2F/
/tigerStatusRoom/
/galleryRoom/
/studyRoom/ ----> input helemt flag!
```

Our next desination is /armorRoom/

### [ Armor room entrance ]

*/armorRoom/*

This page needs the Shield symbol / the Shield flag. Same situation as /studyRoom/: no hyperlinks, no comments, and trying all our flags was a waste of time. Let’s leave this page for now and come back later. Time to move to the next destination.

In our done list:

```
/diningRoom/ ----> input emblem flag!
/teaRoom/
/artRoom/
/barRoom/
/diningRoom2F/
/tigerStatusRoom/
/galleryRoom/
/studyRoom/ ----> input helemt flag!
/armorRoom/ ----> input shield flag!
```

Our next destination is /attic/

### [ Attic entrance ]

*/attic/*

This page needs the Shield symbol / the Shield flag. Just like /studyRoom/ and /armorRoom/, there are no hyperlinks or comments, and trying all our flags didn’t work. Leave this page for now; we’ll come back later. Let’s move to the next destination.

In our done list:

```
/diningRoom/ ----> input emblem flag!
/teaRoom/
/artRoom/
/barRoom/
/diningRoom2F/
/tigerStatusRoom/
/galleryRoom/
/studyRoom/ ----> input helemt flag!
/armorRoom/ ----> input shield flag!
/attic/ ----> input shield flag!
```

Our next destination is…..

*[ GIF sourced from tenor. Rights belong to the creator. ]*

>

………..THE END???

Are you ready?

Do you remember the /diningRoom/ path we left behind earlier? I told you we’d come back to it and now it’s time.

```
/diningRoom/ ----> input emblem flag!
```

### [ Dining room ]

*/diningRoom/*

Earlier, we tried using the emblem flag here, but it didn’t work. This time, we’ve obtained the gold_emblem flag from the Secret Bar Room (/barRoom3757162e3db…/).

Let’s input the flag here and see what happens!

### [ Dining room ]

*/diningRoom/*

then click submit.

*/diningRoom/emblem_slot.php*

It looks like ROT13, doesn’t it? Let’s try decoding the string using CyberChef. Drag and drop the *Magic* operation into the recipe, paste the string into the input field, and the result is:

*[ CyberChef]*

Nothing! As I mentioned earlier, many ciphers can look similar to ROT13. In this case, it only appears to be ROT13, but it’s not. So, how do we figure out which cipher it really is?

To solve this, let me introduce you to a handy website called Enigmator.

*[ Engimator ]*

here is the link:

This website can perform cryptanalysis but what does that mean? You can research it yourself. Essentially, it helps identify which cipher is being used. Keep in mind, though, Enigmator doesn’t support modern ciphers. There’s a reason I chose this website for identification, and you’ll understand why once you try analyzing different platforms. Now, let’s detect which cipher is in use:

*[ Engimator ]*

Paste the string into Enigmator, and make sure you select ‘Identify’ under the Cipher option. Then click Identify, and the results will be displayed as follows:

*[ Engimator ]*

Enigmator detects that it’s a Polyalphabetic Substitution cipher. Here are some references you can check out:

You don’t need to understand the entire theory just get a sense of how it works. In our output, the cipher is initially shown as a Vigenère cipher.

Let’s check if this cipher is available on CyberChef.

*[ CyberChef ]*

It’s available in CyberChef! Let’s drag and drop it into the recipe and see what happens:

*[ CyberChef ]*

In CyberChef, the Recipe section shows an input called Key, and the output says No key entered. That means we need a key to decode this cipher.

You might be thinking what if this isn’t actually a Vigenère cipher? If it turns out to be another cipher, we’d explore other options. For now, we’ll stick with Vigenère.

So now, do you remember the name we found in /barRoom/

*/barRoom3757162e3db…/emblem_slot.php*

Now, simply use this name as the key, and you’ll get the following result:

*[ CyberChef ]*

So, our shield key was hidden in /diningRoom/ , and there was an HTML page called the_great_shield_key The full path would look like this:

/diningRoom/the_great_shield_key.html

Don’t forget to add the html extension. Before we grab the shield_key, here are some shortcuts to decrypt the cipher more easily:

*[ boxentriq ]*

There’s a website called Boxentriq that can automatically solve ciphers. Here, you can see the cipher was decrypted without providing a key, but we can still extract the key from it. How cool is that? It’s a kind of automated cryptanalysis.

If you’re curious about cryptanalysis, there’s a lot more to explore research it yourself to learn the details. Another useful website for this is dcode, which also provides tools to analyze and decode ciphers.

*[ dcode ]*

here is the link:

Now, let’s grab the key:

*/diningRoom/the_great_shield_key.html*

Flag captured: shield_key!

---
