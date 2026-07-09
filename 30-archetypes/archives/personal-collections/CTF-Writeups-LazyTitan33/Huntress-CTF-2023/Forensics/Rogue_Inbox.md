# Rogue Inbox

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution

We get a .csv file with lots of data in it. We can open it in Excel and filter based on UserId because we already know from the challenge description that Debra was compromised. Taking a long time to look through this data, I was trying to see if I can spot any anomalies. Then it hit me... there were a lot of `New-InboxRule` set up which is out of the ordinary. People do set up inbox rules but rarely that many in a quick succession so I applied a filter to show only the New-InboxRules as well and focused on these.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Then I saw it.. a letter peaking out at me:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Then I saw another one:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And another:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

You see where I'm going with this:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Let's use some bash onliner magic to carve this out:  

```bash
cat purview.csv|awk -F "520c2525d932" '{print $2}'|awk -F '"' '{print $1}' ORS=|sed 's/\\//g'
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{24c4230fa7d50eef392b2c850f74b0f6}
