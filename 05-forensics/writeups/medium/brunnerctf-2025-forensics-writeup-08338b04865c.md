# 🔍 BrunnerCTF 2025 Forensics writeup

> **Original Source:** [BrunnerCTF 2025 Forensics writeup](https://medium.com/@manageesh11/brunnerctf-2025-forensics-writeup-08338b04865c)
> **Platform:** medium.com | **Category:** `FORENSICS` | **Year:** 2025

---

## 📝 Full Writeup

BrunnerCTF 2025 Forensics writeup[![Mohammad Alzamil](https://miro.medium.com/v2/resize:fill:64:64/1*nTKh0qgDpJ82WB5CqTfpOw.jpeg)

](/web/20250915013441/https://medium.com/@manageesh11?source=post_page---byline--08338b04865c---------------------------------------)

[Mohammad Alzamil](/web/20250915013441/https://medium.com/@manageesh11?source=post_page---byline--08338b04865c---------------------------------------)

·
Aug 24, 2025

[

](/web/20250915013441/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2F08338b04865c&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40manageesh11%2Fbrunnerctf-2025-forensics-writeup-08338b04865c&user=Mohammad+Alzamil&userId=a7a265bc8e43&source=---header_actions--08338b04865c---------------------clap_footer------------------)

--


During this CTF, I had the chance to dive into a Hard-categorized forensics challenge, and it turned out to be one of the most fun and memorable challenges I’ve worked on.

ENJOY.

1 — VeryCheap

In this challenge we have a disk image, and as the description hints, our task was to analyze it thoroughly and uncover what VeryCheap was really hiding.

We can use FTK Imager or Autopsy to open the disk file, and I will use FTK imager and Autopsy for potential deleted files.

First thing that came to my mind was to check the browser history to see if I could get any useful hints about the user activity, so I thought about checking the Edge history, which is located at:
 C:\Users<username>\AppData\Local\Microsoft\Edge\User Data\Default\History

As we can see in the Edge history, the user is searching for “literally any other browser than edge,” and shortly after he searches for and downloads Google Chrome.

This was a big clue — it meant that instead of continuing to focus on Edge, the real activity was most likely happening inside Google Chrome.

So the next step was to move on to Google Chrome history, which is located at:
 C:\Users<username>\AppData\Local\Google\Chrome\User Data\Default\History

As we can see, the Chrome history reveals some suspicious searches. The user was clearly interested in hiding files and later moved on to downloading and researching VeraCrypt, which hints that he might be using it to conceal sensitive data.

After confirming from the browser history that VeraCrypt was being searched and most likely used, I continued my investigation by searching through the disk. Inside the Documents folder, I discovered a suspicious file named test.hc, which is a VeraCrypt container. This clearly indicates that the user had created an encrypted volume to hide sensitive data.

After a bit of digging, I found a deleted text note on the Desktop. I opened it in Autopsy to recover its contents, and as we can see, the file contained the password for the VeraCrypt container: “brunsviger”.

The next move was to download VeraCrypt and try opening the container we found earlier (test.hc) using the recovered password. With the password “brunsviger”, I was able to successfully mount the volume and access its contents. Inside, I found a text file, but unfortunately, it turned out to be just a decoy file rather than the real secret.

After the decoy, I kept digging and remembered seeing VeraCrypt command-line. That led me to check the PowerShell history for any useful commands.

When I checked the PowerShell history at C:\Users<user>\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadline\ConsoleHost_history.txt, I came across an interesting command related to VeraCrypt.

## Explanation:
- `**& 'C:\Program Files\VeraCrypt\VeraCrypt.exe'**` → Runs VeraCrypt executable.

- `**/v 'C:\Program Files\7-Zip\7z.dll'**` → Specifies the **volume to mount**, here disguised as a `7z.dll` file.

- `**/p "VeryCheapAndDeliciousBrunnerForAll"**` → Provides the **password** for the encrypted container.

- `**/k ".\Pictures\VeryCheapBrunner.png"**` → Uses a **keyfile**, in this case an image file, as additional authentication.

- In short: this command shows the **real VeraCrypt container location, password, and keyfile** that the suspect used.

After extracting the needed files from the disk, I went back to VeraCrypt and used the recovered password and keyfile to mount the hidden container. Once inside, I found four files. But the one that really attracted me — and turned out to be useful — was VeryCheapVerySecretRecipe.txt.

From the text file, we got two important hints. First, the mention of “that’s why I keep so many sticky notes around” pointed us toward checking Sticky Notes artifacts on the disk. Second, the line “some castles might have a back entrance with a different key” suggested that the same VeraCrypt container could be unlocked again, but this time with a different password hidden somewhere else.

Next, I went to the Sticky Notes storage path at C:\Users<User>\AppData\Local\Packages\Microsoft.MicrosoftStickyNotes_8wekyb3d8bbwe\LocalState\plum.sqlite.

When I opened it, I found another useful hint hidden inside the notes that could lead us to more information about the encrypted container.

From the Sticky Notes, we noticed the line saying “Never save anything sensitive as a file on disk, just keep it in an unsaved Notepad window.” This gave us a direct hint that the next artifact to investigate was Notepad’s unsaved files/recovery data, since Notepad stores unsaved content automatically for recovery when reopened.

When I moved on to the Notepad artifact path:
 C:\Users\Joe\AppData\Local\Packages\Microsoft.WindowsNotepad_8wekyb3d8bbwe

While going through the Notepad artifact, I came across a clue mentioning VeraCrypt’s Hidden Volume feature. For context: a hidden volume is like a secret container inside the normal VeraCrypt container. The trick is that both containers are stored in the same file — when you enter the first password, it opens the normal (decoy) volume, but if you enter the hidden password, it unlocks the secret inner volume. This is used for plausible deniability, so even if someone forces you to reveal a password, you can give them the outer one while keeping the real data hidden.

At the end of the Notepad file, I found the line:
 WhaaaatItCanHaveAnExtraHiddenVolume?!?

This was clearly the password for the hidden volume.

Finally, with the hidden volume password in hand, I was able to unlock the real container. Inside, I found an Excel file — and that’s where the real flag was hidden.

---
