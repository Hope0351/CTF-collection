 Trivial - A Little Something to Get You Started (Web CTF Write-up)

 Challenge Overview
- Challenge Name: Trivial - A Little Something to Get You Started
- Category: Web
- Difficulty: Easy
- Objective: Find the hidden flag by analyzing the page source.

 Approach & Solution

 🔎 Step 1: Identifying an Unused Image File
While inspecting the page source, I noticed a reference to an image file:

```ini
src="background.png"
```
However, the page didn’t display any background image, which seemed suspicious.

 🔎 Step 2: Accessing the Hidden Image
I manually accessed the file by appending `background.png` to the URL:

```bash
https://example.com/background.png
```
💡 Boom! The flag was inside the image file.

 Lessons Learned
- Always check for hidden media files in the page source.
- Manually test file URLs to uncover hidden content.
- Developer tools are your best friend (`Ctrl + Shift + I` or `F12`).

Visiual : 



 Conclusion
This challenge was a great introduction to web-based CTF challenges, emphasizing the importance of understanding how web pages are structured and how developers may leave hints in the source code.

🚀 Happy Hacking!

