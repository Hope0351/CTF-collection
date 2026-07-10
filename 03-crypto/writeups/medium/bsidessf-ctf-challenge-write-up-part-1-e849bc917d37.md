# :locked_with_key: BsidesSF CTF - Challenge Write-up Part 1

---

# BsidesSF CTF — Challenge Write-up Part 1

I was part of the Bsides San Francisco CTF crew for the third year in the row, this year I contributed four challenges and helped out with slack / scoreboard support. The other organizers include -

The team is always a pleasure to work with and a delight to learn from. We scrambled frantically before d-day but pulled through without major hiccups, like they say “The ultimate inspiration is the deadline”. *Matir *has a great write-up on the BSides SF [site](https://bsidessf.org/news/2019/03/running-the-bsides-sf-2019-ctf), that I highly recommend reading, especially if you ever plan to run one in the future. As always, our challenges have been published to [github](https://github.com/BSidesSF/ctf-2019-release) and are available to all.

## Mobile challenges

I enjoy writing mobile CTF challenges, they are a bit under-represented but a lot of fun to put together. A [list](https://github.com/xtiankisutsa/awesome-mobile-CTF) curated by Christian Kisutsa ([@xtian_kisutsa](https://twitter.com/xtian_kisutsa)) is comprehensive and captures the variety of mobile challenges that are currently out there. Coming up with ideas and implementing mobile challenges is time consuming, every year it is a bit of a roller coaster as I stare at the scoreboard and the daunting 0 solves that lingers for the first few hours. Wondering if the challenge is broken or just not being attempted, watching the first solve roll in is almost always accompanied with a heavy wave of relief washing over me.

This year I had three mobile challenges — a 101 challenge (*Blink*), a puzzle (*YayOrNay*) and a real world issue inspired (*Weather Companion*). Two of the three were hits, I am very proud of *Weather Companion* and how it was received. *YayOrNay* was a miss, it was a puzzle and unintentionally became a — you either get it or you don’t — making it a bad challenge, it was a valuable lesson and will factor into my future challenges. With that let’s jump into the challenges!

## Blink — 50 points, 239 solves — Mobile, 101

>

“Get past the Jedi mind trick to find the flag you are looking for.”

The motivation behind *Blink*, was to show people Android APKs are easy to take apart. There are many ways to reverse an Android application — APKTool + dex2jar + jdgui or Android Studio. The latter is something I stumbled upon while testing my challenges this year. Coupled with the other tools available in the Android Studio suite, it makes debugging / walking through APKs fairly easy. To get things started, choose the “Profile or debug APK” option and select the challenge APK.

Once loaded try running the APK, the first and only activity that will be shown is the one below -

It is clear that the flag is not visible on the activity (as hinted by the Jedi mind trick reference), let’s try decompiling the app and digging a bit further. Android Studio decompiles the APK and gives you a convenient UI that allows you to click through and view its contents. Expanding classes.dex will show the packages / classes in the APK, skip over the standard android / java packages and focus on the application’s code in the package — com.example.blink.

Right clicking on a class and selecting “Show Bytecode” will open up a window with the corresponding smali code. MainActivity loads the layout and nothing more, let’s move onto the r2d2 class(more not so subtle star wars references). It appears to have a base64 encoded hardcoded image -

>

.line 22

.local v0, “image”:Landroid/widget/ImageView;

const-string v1, “ data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD/2wBDAAMCAgICAgMCAgIDAwMDBAYEBAQEBAgGBgUGCQgK….snip….

Copying and pasting this into an online image viewer will the following image which contains the flag.

Yes, I mixed two geek movie references — Star Wars and Scott Pilgrim, I will aim for better consistency next time.

## YayOrNay — 200 points, 7 solves — Mobile, Forensics

>

“Keep track of places you would love / hate to *see*, by dropping markers with a simple click. Try YayorNay v1.2 today!

:::: Updated README :::: v 1.0 — Added short press, Yay support — Fix stability issues

v 1.1 — Added long press, Nay support — Add labels

v 1.2 — Populate from DB — Save to DB

To-do — Fix stability issues — Bug fixes — Implement feature to view by day

(Not the standard flag format, case matters!)”

Note: The initial README’s phrasing did not convey the meaning I was going for, so I had to update the challenge description with a new README to address it.

Repeating the same steps as Blink, running the APK shows a landing page and a map which a user can interact with to keep track of places they like / dislike.

A couple of things stand out — there are files in the assets folder and there is no network traffic. The assets folder contains two files — README and Location.db.

The updated README from the challenge description, captures the changes made in each of the versions and unresolved to-dos. The to-dos are stability fixes and implementing a view by day feature.

Let’s follow the view by day lead, first we need to pull the location.db file you can do this by unpacking the APK with apktool or through Android Studio’s device file explorer. The file explorer window allows you to view all the files currently present on the emulator, if you look through the /data/data/ folder corresponding to the application — com.example.yayornay — it displays the files it creates on the device. The subfolder databases contains the Location.db file, you can right click the file and choose “Save As”, which pulls the file off the device and saves it on the computer. Opening it using [SQLite Browser](https://sqlitebrowser.org/) shows two tables -

- Android_metadata (standard table, shows the language)

- Locations (Locations by latitude, longitude — the date they were added and the color of the marker)

The locations table has *199 entries* added across *11 days*. Some players plotted the points by day using the Google Maps API, another option is to make 11 versions of the database each with a single day’s entries pushing it to the emulator and restarting the application. The database can be pushed to the folder by right clicking and using the “Upload” option. The day- 02/09/2019 has an interesting pattern.

This was braille, each character represented by a 3 x 2 cell. In this case, the green represents a dot and the red a blank. Using a [braille guide](https://brailleworks.com/reading-and-writing-braille/), you can decipher it as “Z3Lda”. People had a hard time spotting that his was braille and realizing the first cell indicates that the following cell is a capitalized letter.

The goal of the challenge was to teach people to look at the databases created by the application / in the APK. Unfortunately, the use of braille made this needlessly complicated and something I will try to avoid doing in the future.

Stay tuned for part 2 which will dive into Weather Companion and Table Tennis challenges.

---
