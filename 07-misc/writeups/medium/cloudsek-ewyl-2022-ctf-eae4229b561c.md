# :game_die: CloudSek EWYL 2022 CTF. Solving a Harry Potter Themed CTF

---

# CloudSek EWYL 2022 CTF

## Solving a Harry Potter Themed CTF

This was a “Harry Potter” themed CTF containing challenges from Multiple areas of Web security like Template Injection and Code Review. This Challenge was hosted by CloudSEK as a part of the EWYL-2022 Program.

In this report, I have explained in detail how I solved the CTF.

## Initial Recon

I started the Challenge by Scanning the Target IP which was [http://13.235.95.179](http://13.235.95.179).

The Scan showed three Opened ports, but as Per the Rules of the CTF, we were not allowed to attack the underlying Infrastructure of the CTF. So port 22 was not touched. We will only focus on ports 80 and 5000.

After the NMAP scan, I performed a Directory Brute Force to look for Interesting Directories and Files, But that scan didn’t return anything special, not even a *“robots.txt”* file.

## Decoding & Deobfuscation

Accessing the main Webpage on Port 80 showed the theme of the challenge along with a login page on the “*/gateway.php”* endpoint

This was a basic Login Page with not many functionalities. This page has an interesting line *“You also need to explore more about the content of Wizardry before coming to Hogwarts”. *This can be an indication of the missing “robots.txt” which we were unable to find in the Initial Scan.

After a Hit-and-Trial round, a page was found at “*/wizardry.txt” *which contained an Obfuscated Text along with a message from Dobby the ELF.

The text present here was doubly Encoded first with Base64 and then with JSFuck Language.

Gibberish Text -> Base64 -> JSFuck Decoded -> alert(“id3nt1ty_card.php”);

After Decoding the text at *“/wizardry.txt” *we got a new page which was id3nt1ty_card.php

## Inspecting the ID CARD

*Vulnerability: Hidden Parameter Discovery*

Visiting the page on id3nt1ty_card.php gave us a Picture of an ID card with some random numbers. Performing a GET parameter brute force on the endpoint gave the parameter “?id”.

Using *?id=1* on the page shows us the following image

This shows we are on the right track, we use brute force again to get a valid value for the id parameter.

Brute forcing gave us that the parameter is accepting the value of “?id=212.”

The following response was received from the server.

This page gave us very Useful Information which would help us to get Login into gateway

It has 2 variables present, the combination of these variables would give us the Password to login.

=======> x = 436c3075445f53654b5f=======> y = ControlC — password protected page

We need to crack the password for the “ControlC” page in order to get the 2nd part of the password.

On the same page, we find a few other Images, but they are all a rabbit hole.

But one particular Image was present in the Source Code of the Page

Here we find a PHP code for the combination of different passwords that can be used on the “ControlC” Website.

## Juggling With PHP

*Vulnerability: PHP Type Juggling Attack*

The piece of code we received in the earlier step will allow us to get the 2nd part of the password from ControlC.

Let’s analyze the code now.

*-> if(array_key_exists(“passphrase”,$ REQUEST))*: This line checks if the parameter “passphrase” is defined in the “REQUEST” body or not, the request can be of any type (GET or POST).

-> *if(strstr($ REQUEST[“passphrase”],”carbonblack”):* This line uses the strstr function to check if the given string is present in the original string or not. It returns True if the string is present.

*-> ($_REQUEST[”passphrase”] > 22) && ($ REQUEST[”passphrase”] >55)*

This is the line where we can exploit PHP type Juggling Vulnerability, this line does a loose comparison between a string and an Integer, so only the first integer characters are checked.

So, a Few possibilities of passwords are: From 23carbonblack till 54carbonblack.

Upon trying these passwords the correct one was: 33carbonblack.

This gave us the 2nd part of the password :

alert(“The second part of the password: W0rK_iS_FuN”);

## Unlocking the Gateway

*Steganography Challenge*

We now have values for both the variables *x and y* to unlock the gateway

*=====> x = 436c3075445f53654b5f=====> y = W0rK_iS_FuN*

## Get Mayank Pandey’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

The value of *x* doesn’t seem to be quite right, upon more inspection I found that it is Hex Encoded

*436c3075445f53654b5f -> Hex Decode -> Cl0uD_SeK_*

I made a list of a few possible usernames from the Challenge and Found the Correct credentials

*-> Username: Cloudster-> Password: Cl0uD_SeK_W0rK_iS_FuN*

Using this we can now get into the Gateway. After logging in We are Greeted by a Chocolate Frogs Collectible Card Page on /we1c0mE_start.php

Here we find a cfcard image. I used Exiftool to extract any possible hidden metadata inside the image. There was an Interesting Comment in the Image.

>

*Krasy8 unicode key 7 → Sl}lsf8fJs7|KfzLrf^pUMsHn (Move to next key with domain:5000 port)*

I had no idea what was Krasy8. Searching on Google gave a GitHub Repo, a tool to perform Encoding and Decoding Using a Key.

After decoding the text present in the Comment we get our Final Flag for Level 1

>

Level 1 Flag: Level_1_Cl0uD_sEk_WiNFlAg

## Injecting the Template

*Vulnerability: Server-Side Template Injection {SSTI}*

We now move to a different port (5000) to solve the Next level.

The image is self-explanatory (for the “?search” parameter). Anyways we do a Heuristic Test and find that the page accepts a parameter ?search.

Fuzzing the search parameter gives us an Interesting result.

The result confirmed that the server is Vulnerable to SSTI, the Backend was using Jinja2 Template. I tried to run system Commands using the OS module but it failed *[Because they don’t want us to run commands on the server]*

So now the only path left here was to check for a few predefined objects in the app like “Config”. I used the {{Config }} object and Voilla!!! I received a Response…

- What is Config object?

The config object is a Flask template global that represents “The current configuration object (flask.config).”

It is a dictionary-like object that contains all of the configuration values for the application.

In most cases, this includes sensitive values such as database connection strings, credentials to third-party services, the SECRET_KEY, etc. Viewing these configuration items is as easy as injecting a payload of {{ config.items() }} or {{config}}

The response had an interesting text {Nothing to hide on /adieu}.

So as a Hacker what do we do when someone tells us not to visit something? Exactly, We Visit it!!

## “adieu”

Moving to the next Page we get a simple page

Viewing the Source of this page gives us something Interesting.

From here we get a link for GitHub Repo: [https://github.com/aayush-vish/cloudSEK-CTF](https://github.com/aayush-vish/cloudSEK-CTF)

Manually Visiting the Repo Give us a 404 error which means this Repo is Private. We need to work more to get to this Private repo.

## GitHub Quest

Doing More Passive Recon we find a Few Indexed Commits from the Owner of the Private Repo.

In this file we find the Token to Clone the Repo

The token was Base64 Encoded: REDACTED_BASE64_TOKEN

Decoding it gives us: REDACTED_GITHUB_TOKEN

## Tracking the Commits

Cloning the Repo doesn’t give us anything Interesting, so it was time for Looking through the Commit History.

Initial Search gives us this, although it’s Interesting but we don’t need this.

After Undoing the Commits we find Something Very Interesting, It’s the Flag

Finally, We Found the Level 2 Flag

>

Level 2 Flag: CTF{Congratulations_Level02_Completed}.html

## Concluding the Hunt

This CTF threw some amazing challenges, a few being From Real World and Others from the imaginary world just like Harry Potter.

---
