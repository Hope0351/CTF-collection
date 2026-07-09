# Indirect Payload

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution

Accessing the generated link, we have a webpage where we can retrieve a payload:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We have Burpsuite intercepting in the background and we can see a lot of 302 Redirects as soon as we pressed the button:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Looking through each one, we can see that some have a body. One of them says that character 0 of the payload is `f`:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Then we have an `l`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And an `a`:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And a `g`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

These are not consecutive. There are some empty redirects in between so we can't simply click through and transcribe the flag. Or we could, but we can think of an easier way. Let's use `wget` to follow a lot of requests and get a detailed body into an output.txt file. The important part here is the `-debug` flag so that we can actually see the output of the redirects when there is one:

```bash
wget --debug --max-redirect=150 http://chal.ctf.games:31453/site/flag.php -o output.txt
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After a while, we can read the content of the output.txt file and parse it out to print the flag:  

```bash
cat output.txt|grep payload|awk '{print $12}' ORS=
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{448c05ab3e3a7d68e3509eb85e87206f} 
