# :game_die: The Core Value Proposition of SOAR

> **Original Source:** [The Core Value Proposition of SOAR](https://infosecwriteups.com/the-core-value-proposition-of-soar-25c3d5c786b3)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# The Core Value Proposition of SOAR


Security alerts are generated in siloes. Each category (email, network, endpoint, cloud and identity) have a set of tools designed to monitor logs and produce security alerts when a suspicious pattern is seen. However, activities between these different categories are often related. But the detection platforms can’t connect the dots because the systems don’t talk to each other. So, incident responders have the responsibility of searching across tools and databases in order to find related information; then make a decision.


However, the process of finding this relevant information is time-consuming, monotonous, and error-prone. Every incident responder faces this issue. With an overwhelming amount of alerts generated everyday, it’s easy to get overwhelmed. However the risk of not doing this work is to miss a related activity and misclassifying something as a false positive or contained.


Across use cases, users gain the most consistent value when SOAR playbooks are used to automatically consolidate relevant, contextual information and display it in a way that helps analysts make better decisions.


## Get Alexander Pierre Noujeim’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


For example, here is an alert created by CrowdStrike when a task was executed that may indicate malware on a device.


This alert tells us the event time, the hostname, the parent process, and the username. However, what it doesn’t tell us is where that file came from that triggered the process if the user’s account has been compromised, and if the machine is communicating with any suspicious devices outside of the network.


This is where SOAR playbooks come in. When an incident is raised a series of automated, API-based tasks trigger. These tasks query the various tools in an environment and consolidate relevant information.


Here, under **Data Correlations**, you can see the recipients of the original file as well as their login activity over the past 14 days. This information was collected from Office 365 and Azure Active Directory.


Then, the playbook uses CrowdStrike to list all of the outbound connections established between the user’s machine and devices outside of the network. Then it uses Recorded Future to collect the risk of each IP address.


Finally, we can see the established sessions and executables inevitably creating the original alert.


Without this contextualization, users would either miss the big picture or spend time searching through each database in order to connect the dots. Doing this one time is okay, but considering the number of alerts security teams are dealing with every day, this is just inefficient. And this is the core value proposition of SOAR: **It takes time away from monotonous, repetitive tasks, and puts them in a position to make better decisions.**

---

*Originally published on [Medium](https://infosecwriteups.com/the-core-value-proposition-of-soar-25c3d5c786b3). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
