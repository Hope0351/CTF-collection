# :arrows_counterclockwise: BlueHens UDCTF 2023 - Writeup Part 1 - Hardware Challenge

---

# BlueHens UDCTF 2023 — Writeup Part 1 — Hardware Challenge

*BlueHens UDCTF 2023*

So after the event ended I thought why not write some writeups of the challenges that were provided. So I will be writing the solutions for Hardware challenge in this part 1 and the Part 2 will be for reverse challenges.

## Hardware Challenge — Locked Circuit

*Locked Circuit Challenge*

Two files were provided called “k8_AntiSat_DTLAND0_c432.bench” and “c432.bench” respectively.

As it was categorized as a “Hardware” challenge and when I view the file contents using `cat file_name.bench``, at first I thought that I might need a logic gate simulator but turns out I didn’t need it. [I even tried some simulator with the given files but no luck on making them work.]

Then I noticed there was a hint given in the description where it says “trick hidden in the output”. So I started to analyze the contents of the files.

When I ran `diff file1.bench file2.bench`` I got some interesting output.

*running diff to view the differences*

*The interesting part*

“xorF_117”, “xorF_100” and so on , These(117,100, …) looked like some decimal values that can be converted to ascii. So I wrote a small python script to convert them and voila there’s the flag.

*solution*

The first thought crossed my mind when I solved this challenge was “why is this categorized as a hardware challenge I mean the intended solution points towards “crypto” category or “misc, crypto” as it is a very basic crypto problem”. This is just my opinion on this challenge. Overall it was an easy challenge.

Have a good day!

---
