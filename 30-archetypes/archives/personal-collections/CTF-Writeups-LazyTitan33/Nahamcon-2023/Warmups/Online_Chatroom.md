# Online Chatroom

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

For this challenge, we get the source code of a Go binary. We notice some chat messages going on and the flag is within the chat history of user 5.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Sending a simple message in the web application:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And intercepting it with Burpsuite, we notice it is using websockets:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In the source code, we notice another command other than `!write`. We notice we can query the chat history using `!history`. After sending the request to Repeater, we see we need to provide an index from 1 to 7.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Well, what happens if we query outside of that range?

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We get the flag: flag{c398112ed498fa2cacc41433a3e3190b}
