# password-manager-is-a-must

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

Running strings on the provided dump, we can tell that it's a proc dump of the `keepass.exe` process.  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can clone the keepass-password-dumper locally and run it on the dump file to get the password from it:

```cmd
git clone eepass-password-dumper
dotnet run File.dmp
```

As usual with this method, the first 2 characters are not exact but can be deduced:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Password: `thesecretpass`

And we can now get the flag from the keepass file:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`CTF{c112b162e0567cbc5ae20558511ab3932446a708bc40a97e88e3faac7c242423}`
