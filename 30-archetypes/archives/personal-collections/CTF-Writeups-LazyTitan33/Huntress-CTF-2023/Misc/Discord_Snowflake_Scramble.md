# Discord Snowflake Scramble

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
This one required some googling but because of SEO, a lot of results were nothing I was interested in so I switch search engines and used duckduckgo:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The first 3 results show tools that parse the IDs in the link we were provided differently. Turns out these IDs are called Snowflakes and they can represent either a Message ID, or a Server ID, a channel ID etc. The tool that ultimately helped me further was [discordtools](https://discordtools.io). I was reticent at first because for it to give you detailed information, other than the timestamp of the snowflake, they require you to login with your Discord account. However, the good news is that it's an Open Source application with their code on Github so that was reassuring for me.

I inputted the first Snowflake from the link and sure enough, getting the detailed Discord info, we can see an Invite link:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Accessing that link gets us on this hidden server and we have the flag in the channel with the same name:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{bb1dcf163212c54317daa7d1d5d0ce35}
