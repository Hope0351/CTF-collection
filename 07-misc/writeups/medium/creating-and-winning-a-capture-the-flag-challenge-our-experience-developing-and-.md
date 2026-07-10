# :game_die: Creating and Winning a Capture the Flag Challenge: Our Experience Developing and Competing in an Attack & Defense CTF

> **Original Source:** [Creating and Winning a Capture the Flag Challenge: Our Experience Developing and Competing in an Attack & Defense CTF](https://infosecwriteups.com/creating-and-winning-a-capture-the-flag-challenge-our-experience-developing-and-competing-in-an-c2673317182)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Creating and Winning a Capture the Flag Challenge: Our Experience Developing and Competing in an Attack & Defense CTF


In December, my team and I took on a thrilling challenge as we participated in an Attack & Defense (A/D) Capture the Flag (CTF) competition. Despite being experienced players, none of us had ever developed a CTF challenge before, making it a challenging and risky endeavor. However, we were determined to put our skills to the test and deliver a fully-functional service that would stand out among the competition.


In this post, I’ll take you through the ups and downs of our journey to develop various vulnerabilities and exploits, including SQLi, Path Traversal, oAuth Login Bypass, and Server-side request forgery (SSRF). Despite the challenges we faced, it was all fun and enjoyable. We chose these specific vulnerabilities to focus on while being cautious to ensure that our app was not exploitable in any other way and protected against DOS attacks. Okay, let's dive into it.

## What is an A/D CTF?


More frequently organized Jeopardy CTFs (Capture the Flag) consist of challenges, while A/D (Attack-Defense) CTFs consist of services. A service is a simulated application that has security vulnerabilities that can be exploited to obtain flags, which serve as evidence of a successful hack. Service can have multiple components, called flag stores, where each contains a different set of flags. Flags can be assigned a specific flag ID to aid in identifying the target for exploitation.


For example, consider a service representing a Web forum where users can mark their threads as private. Users can also provide personal information in their profiles. This information is only used for analytics and is not publicly shown to other users on the platform. Assume that flags are stored in 2 specific locations, representing the 2 flag stores of the service:


- as part of a private thread,

- as a field of their profile data.


The flag ID for the 1st flag store could be the identifier of the private thread, while the user identifier could be used as a flag ID for the 2nd flag store.


This should give you a good head start on what this is all about. Let's now look at the service we designed.

## Our Service Overview


The service is split up into two semi-small services:


- The Webshop

- The FileServer


*Full architecture*


The first part of the service is a Webshop where users can create/view notes (private) and items (public). When entering the site one must create an account or log in (via `email` + `password` OR oAuth using a FileServer account) to proceed. In the Webshop, you can view your profile, create/view your own notes, create/view your own items, and view all items that exist in the store. Each store item has an individual page where one can see the image (if available). On the individual item page, one can check the stock of the item, reserve the item (reducing the available stock), view the image data of the item, and go to the previous item in the list.


If you don’t want me to spoil you with all the fun, go ahead and look at our repository on how to run the service locally and try to hack it:


In any case, in the next sections, I’ll provide a brief description of vulnerabilities and how one can exploit our service.

### Flag Store 1, Vuln 1 ~ SQLi


The service has user input that is not sanitized properly, and one of the many queries will contain a flaw in the usage of the untrusted input, therefore allowing SQLi to be possible. The SQLi is located in the search feature for the notes. Using this SQLi the user gets access to a table containing all the users and their personal notes. The notes displayed by the search query can then be modified to show the notes of all users or one specific user (e.g. the flag user). One specific user on the site will have the flag in their personal notes which can then be extracted and submitted.

### Flag Store 1, Vuln 2 ~ JWT Algorithm Confusion


JWT Algorithm Confusion occurs when an attacker is able to change the signing algorithm of JWT. Therefore it can be possible for the attacker to sign its own tokens without knowing the secret key from the server.

### Flag Store 1, Vuln 3 ~ oAuth Login Bypass


To implement this vulnerability we introduce a sub-service, which represents a file-upload service to upload pictures for the Webshop. This sub-service serves as an identity provider for the Webshop so that it is possible to login to the Webshop using oAuth. To create an account for the file upload server one needs to enter the following values:


- `username` (NOT unique)

- `email` (unique)

- `password`


When logging in using oAuth the Webshop checks if a user with the given email already exists in its database. If there is an entry, the user is logged in as that user, otherwise, a new account with the given parameters is created. The vulnerability allows for an attacker to be authenticated as an arbitrary Webshop user, by oAuthing with any email address and the username of the targeted account.

### Flag Store 2, Vuln 1 ~ Path Traversal


Shop items will be loaded by sending a GET request to the Webshop endpoint, which in turn retrieves a matching image (if existent) from the FileServer:


- GET *{webshop}/item/view?id={id of existing item}&file={image-name of item}* → returns the raw png data of the requested image

- GET *{webshop}/item/view?id={id of existing item}&file=../../../etc/passwd* → returns some form of error

- GET *example.com/images?name=….//….//….//etc/passwd* → returns the content of /etc/passwd


A malicious user is able to create a path to an arbitrary file and read the flag.

### Flag Store 2, Vuln 2 ~ SSRF with an open redirect


There are two vital parts to this vulnerability:


- The Web Server, serving users

- An internal API, checking and returning the availability of an item (the File Upload Server)


The store has a check stock feature, which returns the number of items available to the user. The Web Server checks the item stock by calling an endpoint on itself, giving `stockApi` it as a parameter. `stockApi` is a string containing an endpoint the Webshop should poll to get the available stock.


## Get TJ. Podobnik, @dorkamotorka’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


A malicious user is able to manipulate part of the URL the webserver sends requests to, by sending maliciously crafted parameters, containing arbitrary HTTP endpoints, to the web server when checking the stock.


However, since the domain of the stock checker is hardcoded, the attack has to be paired with an open redirect to be successfully exploited. Since the Webshop has valid credentials for the fileserver, an attacker can use this vulnerability to retrieve arbitrary images from any user on the fileserver.


That’s all there is to conquer our service and potentially win the competition. But on the other hand, there are a couple of more things you need to develop if you want to compete with your, own service.

## Other Components of the Service


If you look through the repository you will find there are three main sub-directories: `checkers`, `exploits`, and `patches` .

### Checkers


Service checkers are functions that verify the correct functioning of a service, e.g., whether the service is up and running, all functionalities are still in place, and if previously inserted flags are still accessible via the intended functionalities of the service. As for flag dispatchers, you are required to implement a checker for every flag store in your service.


It is extremely important that bots cannot be easily fingerprinted, e.g., because they always perform the same operations in the same order. Otherwise, teams could simply filter out incoming attacks by blocking all requests not following the same pattern used by the bot. For this reason, we require that bots randomly change their behavior among different executions by switching the order of some operations/requests and/or using different functionalities in different executions.


Not necessary, but useful to verify the service is exploitable as well as patchable for the competition – we also provide exploits and patch scripts one can run, respectively.


You can find more information under `checkers` directory.

### Exploits


Simple scripts that use the current flag ID to perform the exploit on our running service. They typically take the following parameters as command-line arguments:


- the IP of the target team to attack

- the flag ID (if used by your service/flag store)


You can find more information under `exploits` directory.

### Patches


Patches are lines of code committed to the main source code to patch the vulnerability during competition.


You can find more information under `patches` directory.

## Demo


*CottonRoad Service Demo*

## Conclusion


Throughout the journey, we encountered various obstacles, but we were able to overcome them and develop vulnerabilities and exploits such as SQLi, Path Traversal, oAuth Login Bypass, and Server-side request forgery (SSRF). In the end, we were able to create a service that was not exploitable in any other way and protected against DOS attacks, which was a great achievement. Overall, it was a valuable learning experience that allowed us to apply our skills and knowledge in a real-world scenario.

>

Thanks for reading! 😎 If you enjoyed this article, hit that clap button below 👏


Would mean a lot to me and it helps other people see the story. Say Hello on [Linkedin](https://www.linkedin.com/in/teodor-janez-podobnik/) | [Twitter](https://twitter.com/TeodorJanez)


Do you want to start reading exclusive stories on Medium? Use this

---

*Originally published on [Medium](https://infosecwriteups.com/creating-and-winning-a-capture-the-flag-challenge-our-experience-developing-and-competing-in-an-c2673317182). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
