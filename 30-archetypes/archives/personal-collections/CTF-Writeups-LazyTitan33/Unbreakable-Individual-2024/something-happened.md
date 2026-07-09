# something-happened

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

This challenge generates a Kibana instance for us where we can sift through some logs. We can start to discover by clicking on the menu button in the top left and then `Discover`:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Now, from the right side, we change the time filter to go as far back as we can:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We need to change the index pattern to the one we are interested in and luckily this one bears the name of the challenge so it is easy to identify:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can now see the logs including over 80.000 hits:

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Looking through the filters on the left side, we can soon see something that catches our eye in the `user_agent`:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A `log4j` payload on destination_ip: `198.71.247.91` so we have our answers to the first 2 questions. 

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The answer to the last question was horrible. I've lost a lot of my time and accuracy percentage here. It was a really bad choice from the creator to make the answer a lowercase word: `mozilla`.

This made the challenge a huge time waster and very unsatisfying to complete. Again, we had to guess the last answer because it's not logical to actually enter "mozilla". What is more logical is to apply common sense, and put in the log4j payload that we can actually see in the `user_agent` field, or at the very least, the full Mozilla user agent that is found most often after filtering based on the victim IP:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In any forensics/DFIR investigation, a report will be made with complete and detailed information. Questions will be asked in full. If these CTF challenges are supposed to emulate that, then it is unacceptable to abbreviate something that neededn't be abbreviated.

Also, the way the question was formulated didn't help either. All in all, a bad challenge in my book. On the bright side, it does give an opportunity to learn to parse Elastic/Kibana logs if you haven't before.
