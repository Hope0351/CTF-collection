# :sleuth_or_spy: OSINT - L’espion. This short article presents my solution…

---

## Challenge Questions

>

1. File -> Github.txt: What is the API key the insider added to his GitHub repositories?

Inside the *github.txt* challenge file, we are provided the following link:

```
[https://github.com/EMarseille99](https://github.com/EMarseille99)
```

Visiting this Github page, I can see that there are 14 repositories. I started by looking in the most up-to-date repository titled “[Project-Build-Custom-Login-Page](https://github.com/EMarseille99/Project-Build---Custom-Login-Page)”. Inside this repository, there are two JavaScript files called “*Login Page.js*” and “*fsociety.js*”. Looking at the contents of the “*Login Page.js*” file, I can see the API Key the insider added to his GitHub repositories.

*API Key.*

>

2. File -> Github.txt: What is the plaintext password the insider added to his GitHub repositories?

Still looking at the contents of the “*Login Page.js*” file, if I scroll down, I can see a base64 encoded password value.

*Base64 Encoded Password.*

Decoding this Base64 string provides the answer for this question.

>

3. File -> Github.txt: What cryptocurrency mining tool did the insider use?

If I look at the other available repositories, I can see a fork of the xmrig Github project. XMRIG is an open-source application that utilizes system CPUs to mine cryptocurrency.

*XMRIG cryptocurrency mining tool.*

>

4. What university did the insider go to?

On the insider’s Github page, I can see that they work as a backend programmer for Software Consultants Inc.

*Github Profile Details.*

I performed the following search in Google to find any references on other sites to the user “EMarseille99” and the company they work for.

```
"Software Consultants Inc" EMarseille99
```

Based on my search above, four results are returned.

*Search results.*

Visiting the LinkedIn page, I can see the university that the insider attended was Sorbonne.

*Insider’s LinkedIn Profile.*

>

## Get Hacktivities’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

5. What gaming website did the insider had an account on?

Looking at the about section on the insider’s LinkedIn account, I can see that they have a Steam account.

*Insider’s LinkedIn About Section.*

I can also use a tool called recon-ng, as seen below, which identifies a steam account with the username “EMarseille99”.

```
[recon-ng][default] > marketplace install profiler
[*] Module installed: recon/profiles-profiles/profiler
[*] Reloading modules...
[recon-ng][default] > modules load profiler
[recon-ng][default][profiler] > info
[recon-ng][default][profiler] > options set SOURCE EMarseille99
SOURCE => EMarseille99
[recon-ng][default][profiler] > run
.....
[recon-ng][default][profiler] > show profiles
```

*Recon-ng Identifies Steam Account.*

>

6. What is the link to the insider Instagram profile?

Reviewing the four search results seen earlier under question 4, we were also able to find the insider’s Instagram profile.

```
https://www.instagram.com/emarseille99/
```

>

7. Where did the insider go on the holiday? (Country only)

Looking at the insider’s Instagram account, I can see six pictures.

*Insider’s Instagram Photos.*

I used [ImgInn](https://imginn.org/)to view the Instagram photos and found a comment under the third image.

*Insider’s Instagram Holiday Photo.*

Using Google Image Lens, I performed a quick image lookup and identified the building as the Marina Bay Sands hotel in Singapore.

>

8. Where does the insider’s family live? (City only)

I started by reviewing the last two photos on the insider’s Instagram account. The first image looks to be somewhere with a warm desert climate and has a very large skyscraper in the background.

*Photo with very tall skyscraper.*

The second image shows the United Arab Emirates (UAE) flag and a comment about visiting friends and family.

*Photo with UAE flag.*

Based on this information, I believe the tall skyscraper in the first photo is the Burj Khalifa, which is located in the city of Dubai.

>

9. File -> office.jpg: You have been provided with a picture of the building in which the company has an office. Which city is the company located in?

We are provided the following office image seen below.

*Company Office Image.*

I can see a sign for the Hippodrome theater, which is located in Birmingham.

>

10. File -> Webcam.png: With the intel, you have provided, our ground surveillance unit is now overlooking the person of interest’s suspected address. They saw them leaving their apartment and followed them to the airport. Their plane took off and has landed in another country. Our intelligence team spotted the target with this IP camera. Which state is this camera in?

The webcam image provided can be seen below.

*Webcam Image.*

To answer this question, I performed a reverse image lookup using the website [TinEye](https://tineye.com/), which provided a single result.

*TinEye Reverse Image Search Results*

Selecting this result and navigating to the website, I found the matching image and was redirected to the EarthCam website. This revealed that the camera was located in the University of Notre Dame, Indiana.

*University of Notre Dame Camera.*

---
