# :game_die: HTB Starting Point: Mongod

> **Original Source:** [HTB Starting Point: Mongod](https://infosecwriteups.com/htb-starting-point-mongod-29281b2887ff)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Starting Point: Mongod


## Getting Familiar with MongoDB


Moving onto our next Starting Point machine we have this bad boy. A quick look at the tasks associated with guy shows that we’re going to need to be brushing up on our MongoDB knowledge. Truthfully, I don’t have a ton of experience with this so this will be good for all of us. After connecting to HTB’s environment through either their pwnbox or OpenVPN let’s go ahead and spawn our target and then get started with this first task.

## Task 1 and 2


We’re gonna knock out these first two tasks with an NMAP scan, we’re not wasting any time today.


Here you see me run


```
sudo nmap -sV -p- 10.129.16.91
```


which the -sV flag is for a service scan and -p- specifies I want to scan all ports, not just the top 10,000. So based off of the output here, we see that there are two TCP ports open and mongodb is the service running on port 27017 go figure. Let’s go ahead and plug all these answers in and then move right along.

## Task 3


You see here, sometimes HTB spoils its answer a tiny bit by giving us the character count. However, let’s not make this too easy, let’s actually understand the difference between a SQL vs NoSQL database. There’s a good article here from [IBM](https://www.ibm.com/think/topics/sql-vs-nosql) that goes into some detail, but long story short it has to deal with how the data is stored. It doesn’t mean NoSQL databases don’t use SQL or a kind of SQL to perform your queries. In SQL databases everything is stored in tables and rows, what is referred to as relational databases. NoSQL just allows us more flexibility in how we want our data stored and is considered better equipped to handle large amount of unstructured data. If you’re curious about the details, feel free to give that article a look, otherwise let’s just answer the question here ‘NoSQL’ and keep moving right along.

## Task 4


I actually don’t have the foggiest idea, like I said I’m kinda in the trenches with yall on this one. Let’s go to yee old googles and see what we get. [From GeeksforGeeks](https://www.geeksforgeeks.org/mongodb/how-to-use-the-mongodb-shell/)


Well here we see the command in question and also the syntax for connecting to a remote database, perfect we’ll need that in a second. Actually, before we submit our answer, let’s actually attempt to connect to the database. We aren’t given any credentials so let’s just specify the host and see what happens.


Huh, well that seems off. To keep this brief, this is some issue with the pwnbox’s nodejs version or something (per the HTB Forums) and the fix was actually only in the official writeup. Gasp, using the official writeup in a writeup? Yeah I know, sometimes you gotta do what you gotta do.


Alright let’s just run these command verbatim and connect to the database.


## Get KarmicDragoon92’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Bam connected. Just for ease of following along the necessary commands are provided below.


```
curl -O https://downloads.mongodb.com/compass/mongosh-2.3.2-linux-x64.tgz
```


```
tar xvf mongosh-2.3.2-linux-x64.tgz
```


```
cd mongosh-2.3.2-linux-x64/bin
```


```
./mongosh mongodb://[IP_Address]
```


Okay now after we’ve done all that, let’s go ahead and actually answer the question.

## Task 5


Well luckily I still have the GeeksforGeeks article up which actually provides us with most of what we need. The `show dbs` command will be what we need here.


So from our MongoDB shell here we run that command and see 5 databases here. For task 5 we have our answer, let’s move onto our next tasks.

## Task 6 and 7


Alright we’re gonna go for both of these at one. One nice feature in the MongoDB CLI is the `help` command.


This spits out a lot of useful information and you can also run it as `help <command>` in order to get more info on a specific command. Here though we can actually see the command we need to run. The `show collections` command will probably do it. We need to place ourselves into a database first with the `use` command.


From the list of DB’s here, sensitive_information sounds interesting. We can jump into that DB and run `show collections` to see a collection called flag. Well how about that? Now, this next part took me a little longer than I care to admin, but to answer task 7 we need to leverage the `db` command which is a massive tool when it comes to interacting with the CLI. After playing around though the command to run is


```
db.flag.find()
```


This command queries the flag collection for all documents, and in this case we only see one with a value called `flag:`. So if we submit that for our root flag...

## Root Flag and Conclusion


Being able to interact with DB’s of all kinds in an extremely necessary skill when it comes to enumerating our targets. Being able to pillage valid credentials or just sensitive information in general is kinda a big deal in red team operations. In also just good for us blue teamers to know because the more we know the better we can just do our jobs. Thank you for sticking around for this one and as always, see you in the next one!

---

*Originally published on [Medium](https://infosecwriteups.com/htb-starting-point-mongod-29281b2887ff). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
