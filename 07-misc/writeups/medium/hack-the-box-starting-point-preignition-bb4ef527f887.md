# :game_die: Hack the Box Starting Point: Preignition

---

# Hack the Box Starting Point: Preignition

Looks like for this box we’re going to be using Gobuster to do some web directory brute forcing shenanigans. After starting our Pwnbox and letting our instance spawn in we’re going to address the first task.

## Task 1

Dir busting is the other name for directory brute forcing, so that’s that.

## Task 2

That’s going to be the -sV flag in order to tell Nmap to do version detection (as we’ll see later).

## Task 3

Well this one is just http, but let’s go ahead and fire up Nmap and put out money where our mouth is.

Here you see me run

```
sudo nmap -sV -p 80 10.129.29.48
```

which runs a service scan on the target, as mentioned earlier. Additionally I use the -p flag to specify port 80 as that’s the only one we are interested. And under service we see http so ta dah.

## Task 4

We can refer to our previous Nmap scan to see that the name and version number is `nginx 1.14.2`.

## Task 5

Now time to use some gobuster. I don’t actually remember the flag to specify that so…

I ran `gobuster -h` for help using the command (most command use either -h or -help for usage information). Looks like we need the dir switch to perform dir busting which, yeah checks out.

## Task 6

Mmm another good question. Well, when we ran`-h` on gobuster a second ago we also saw there was a help command that gives us more info on other commands.

## Get KarmicDragoon92’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So after running that at the bottom here we see we can specify a file extension with the -x flag. So our answer is`-x php`.

## Task 7

Time to finally fire it up, let’s point gobuster at the target.

Here you can see my in progress gobuster scan and below the command I ran.

```
gobuster dir -x php -w /usr/share/wordlists/dirbuster/directory-list-2.3-small.txt -u http://10.129.29.48
```

Just to break it down a little. The -x flag we’ve already covered, the -w flag is the wordlist we are using in order to try and brute force some of these web directories. We can already see at the bottom that admin.php has been found which, yeah sounds interesting. The -u flag specifies the target url, which in our case is just http:// and then the targets IP address.

After the scan completes we can see that it was just that admin page that was found making that the answer to this task.

## Task 8

From gobuster’s output we see it came back with an HTTP status code 200, which means OK or that it’s accessible. Just for fun let’s do this.

Here I use a command called curl

```
curl http://10.129.29.48/admin.php
```

which just rips down the html of the web page. Curl can do so much more than just this, but this is just to demonstrate we can in fact navigate to this page unrestricted through like a browser if we wanted to.

## Task 9

Huh, alright let’s go look for it. Maybe we’ll actually try going there in our browser next.

Yep, that’s a login page. Hang on, you don’t think that it would be admin:admin would you?

Oh come on now, that’s just too easy.

---
