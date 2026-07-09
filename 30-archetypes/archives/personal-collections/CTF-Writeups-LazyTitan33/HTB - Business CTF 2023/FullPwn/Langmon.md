### Challenge description
FullPwn challenges don't have a description. We just get an IP address and are supposed to get user and root flag.

A port scan shows only ports 22 and 80 open, we also see it resolved to `langmon.htb` so we add that to your hosts file.
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The mainpage reveals a good looking website:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Thankfully we are able to register a user on this website:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

From the nmap scan which shows `wp-admin` we know this is a Wordpress website so we use wpscan to scan it for users and vulnerable templates. We use the aggressive method and pass in our API token for more details:
```bash
wpscan --url http://langmon.htb/ -e vp,u --plugins-detection aggressive --api-token <redacted>
```

After a short while, the scanner finds that `php-everywhere` is a vulnerable plugin presently used on the website:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After a bit of research, we find this youtube video clearly showing the way to trigger code execution.

[![IMAGE ALT TEXT](http://img.youtube.com/vi/NJl64f9Ohp8/0.jpg)](http://www.youtube.com/watch?v=NJl64f9Ohp8 "PHP Everywhere RCE")

We just follow that video creating a post with a php block in it and get a reverse shell:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The first thing that needs to be done for a wordpress website is to read the `wp-config.php` file to read database credentials:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We find the password `SNJQvwWHCK` which turns out is being reused by the user `developer`:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we get the user flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)  

HTB{4lw4y5_upd473_y0ur_plu61n5}

## Privilege Escalation

Checking the sudo permissions we can see that user developer is allowed to run a specific python script:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```python
#!/usr/bin/python3
import sys
from langchain.prompts import load_prompt

def load(file):
        try:
                load_prompt(file)
        except:
                print("There is something wrong with the prompt file.")
if __name__ = "__main__":
        if len(sys.argv) != 2:
                print("Usage: prompt_loader.py <prompt_file_path>")
        else:
                file = sys.argv[1]
                load(file)
```

I wasn't familiar with the langchain library however quick google search for langchain exploits we find that it is vulnerable to code injection:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can copy the script from this github issue: angchain/issues/4849. Saved it to a file called getroot.py and we execute it to read the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

HTB{7h3_m4ch1n35_5p34k_w3_h34r}




