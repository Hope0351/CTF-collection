# :game_die: Writeup Advent Of Cyber 2023 Day 3 Brute Forcing Hydra Is Coming To Town 1Bdcfa1

---

### Answer the questions below

Q1) Using `crunch` and `hydra`, find the PIN code to access the control system and unlock the door. What is the flag?

we have a simple pin login form at port 8000

key thing to note is The numeric keypad shows 16 characters, 0 to 9 and A to F, i.e., the hexadecimal digits. We need to prepare a list of all the PIN codes that match this criteria.

We will use Crunch, a tool that generates a list of all possible password combinations based on given criteria. We need to issue the following command:

`crunch 3 3 0123456789ABCDEF -o wordlist.txt`

- `3` the first number is the minimum length of the generated password

- `3` the second number is the maximum length of the generated password

- `0123456789ABCDEF` is the character set to use to generate the passwords

- `-o wordlist.txt` saves the output to the `wordlist.txt` file

Now we will use hydra to bruteforce.
Before that lets look at the page source

- The method is `post`

- The URL is `[http://MACHINE_IP:8000/login.php](http://MACHINE_IP:8000/login.php)`

- The PIN code value is sent with the name `pin`

And another thing is , incase of wrong attempt

It redirects to page with text `Access denied`

## Get dollarboysushil’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

With all this info lets start hydra

`hydra -l '' -P wordlist.txt -f -v -s 8000 MACHINE_IP http-post-form "/login.php:pin=^PASS^:Access denied"`

- `-l ''` indicates that the login name is blank as the security lock only requires a password

- `-P wordlist.txt` specifies the password file to use

- `-f` stops Hydra after finding a working password

- `-v` provides verbose output and is helpful for catching errors

- `-s 8000` indicates the port number on the target

- `MACHINE_IP` is the IP address of the target

- `http-post-form` specifies the HTTP method to use

- `"/login.php:pin=^PASS^:Access denied"` has three parts separated by `:`

- `/login.php` is the page where the PIN code is submitted

- `pin=^PASS^` will replace `^PASS^` with values from the password list

- `Access denied` indicates that invalid passwords will lead to a page that contains the text “Access denied”

And we got the password

Lets login

>

ANS: THM{pin-code-brute-force}

### Watch video walkthrough

---
