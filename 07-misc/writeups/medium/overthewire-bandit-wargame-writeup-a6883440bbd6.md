# :game_die: OverTheWire: Bandit wargame (Writeup -Part I)

---

# OverTheWire: Bandit wargame (Writeup -Part I)

Introduction: Overthewire is the community that can help you learn and practice security concepts through fun-filled games.

Bandit: It is a beginner-level challenge & I think it is good if you’re looking to harden your Linux OS Command line power & base hacking skills.

In this writeup, I’m going to cover levels 0–12

>

Level 0

Here we just have to SSH into a remote machine.

ssh -p 2220 <username>@<Domain/IP>

*In the Current dir, we’ve flag 0*

>

level 1

Here we’ve got a file that starts with a hyphen - & when we tried to execute it using cat or any tool it’ll going to display an error because a shell (bash,zsh etc) takes the meaning of it as a hyphen which we used with tool’s option/switches.

*Flag 1*

To tells the shell that it’s a normal hyphen we can use ./<filename>.

>

level 2

Here file has spaces so we get an error if we open it as we do normally. As Shell intercepts the space as EOF/Newline or in other words as a different file, not one.

*flag 2*

So we can use single/double quotation to tell the shell that it is one file

>

level 3

Files/dir begin from a full stop (.) are hidden means by listing the directory will not show them unless we explicitly mention them.

*flag 3*

So we can use -a switch that comes with ls so see those files/dir

>

level 4

Use ./ & wildcard (*) to automatically display all files at once.

*flag 4*

>

level 5

In inhere directory, we’ve got a lot of directories & sub-directory and so on but we’ve given the metadata of our flag file.

*flag 5*

- . (Searches from current dir recursively)

- type (Which type of file to search)

- size (Size of file 1033c means 1033 bytes

- perm (Permission -u means user ownership of file must be read & write).

- exec (System call used to execute OS command)

Find tool is best to find any file/dir in the system & with metadata, it makes it a lot easier for us.

>

level 6

For this level, we’ve to find a flag that’s somewhere in the server but we’ve given the metadata of our flag file.

*flag 6*

- / ( Means starts from the root of the filesystem or whole system search).

- user (used to represent the user ownership of a file).

- group (used to represent the group ownership of a file).

- 2 (2 means STDERR Data stream).

- >/dev/null ( Redirection of all errors into /null which is just a blackhole usually used to dump the data).

>

level 7

Here we’ve data.txt which has 98567 lines of data & we need to grab a given word for the file.

*flag 7*Grep is the best tool in these situations. As it searches throughout the file.

>

level 8

So here flag is stored in data.txt & it’s the only unique word.

*flag 8*

sort (Sorts all data by default Ascending)

## Get Ali AK’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

uniq -u (Output of sort is now input of uniq because of Pipe & return unique).

>

level 9

The flag is in data.txt it’s in human-readable form and preceded with “=”.

*flag 9*Strings (Grab all human-readable strings from binary or another file).

>

level 10

The flag is encoded with the base64 algorithm just needs to decode here.

*flag 10*Base64 (Used to encode & decode base64 )

>

level 11

The flag is encrypted using the rot13 algorithm. Can be decrypted easily as we know the key (13). So by using key value 13 we can decrypt it.

*flag 11*tr (here it take file input & return it into reversed rot13 format)

>

level 12

Here we’ve given a file which is hexdump of our flag.

To reverse the hexdump I’ve used xxd tool.

After reverse look like is also compressed (gzip) so rename it to gzip extension (.gz) and gunzip it.

After uncompression file of gzip look like file was compressed with bzip now so same step rename to (.bz2 or bz) extension & bunzip it.

After bunzip it’s now compressed with gzip so same step as above

After breaking 3 layers of compression our data file is now tar archived.

So extracted the tar archive using tar tool. After that we get data5.bin which was also tar archived so again extract it.

After archiving data5.bin we now have data6.bin which was (bzip) so rename file & bunzip it

After that file is (gzip) so do (gunzip) & finally we’ve ASCII text format means flag.

Check the next part II where I solved (levels 13–20)

---
