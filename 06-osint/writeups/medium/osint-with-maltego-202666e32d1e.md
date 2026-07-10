# :sleuth_or_spy: Osint With Maltego 202666E32D1E

> **Original Source:** [Osint With Maltego 202666E32D1E](https://infosecwriteups.com/osint-with-maltego-202666e32d1e)
> **Platform:** infosecwriteups.com | **Category:** `OSINT` | **Year:** 2026

---

*OSINT with Maltego*

## What is Maltego?


Maltego is an application for data mining that mines open-source data sources and generates graphs for relationship analysis. The graphs simplify the linking of data such as a person’s name, email organizational structure, domains, documents, etc. Maltego is available for Windows, Mac, and Linux, and is bundled with Buscador and Kali, among other OSINT Linux distributions.


Essentially, it’ll scan a large amount of data and search many open-source websites for you before providing a visually pleasing graph to help you put the jigsaw puzzle together. Furthermore, Maltego is often used as a resource at any point in the investigation, but if your goal is to find a domain, it is best to start mapping the network with Maltego from the beginning.

## What exactly does Maltego do?


As a tool, Maltego is a program that can be used for investigative purposes by journalists, government agencies, and cybercrime units. Moreover, it shows connections and relationships between pieces of information that might not seem related at first glance.


This is carried out by mapping entities in the real-world connections between:


- People
- Name
- Email addresses
- Aliases

- Groups of people (social networks)

- Companies

- Organizations

- Websites

- Internet infrastructure such as:
- Domains
- DNS names
- Netblocks
- IP addresses

- Affiliations

- Documents and files


Open-source intelligence (OSINT) methods are used to find connections between different pieces of information by searching sources like DNS Enumeration, search engines, social networks, User Enumeration, whois Lookup, various web APIs, and extracting metadata.

## Installing Maltego


Kali: Maltego is already installed on Kali. You must first create an account on the website. After you set up your account, you will be issued a key granting you access to the Community Edition.


Buscador: If you obtained Maltego through Buscador, it will, in the first instance, appear as a Casefile version. You must first create an account on the website. After you create your account, you will receive a key that will convert your casefile to CE.


New Installation: If you are doing a fresh installation on Windows, Mac, or Linux, Paterva has provided a [step-by-step guide](https://docs.maltego.com/support/solutions/articles/15000008704-installing-maltego).

## Getting Started


Scroll through the Entity Palette on the left until you select a Domain, then drag it into your blank graph plane.


Double-click the domain icon and enter the name of the domain you want to investigate.


Right-click on the domain icon to bring up the Run Transforms box. We’ll choose Run All Transforms by clicking the tiny fast-forward arrows next to it, but you could capsulize your search by scrolling through the palette and fine-tuning it.


Right-click and select “Run Transform” and you will notice the graph network structure.


## Get Redfox Security’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Note: On the left side of the graph panel, there are different options available to pick from according to one’s choice.


As you can see in the image below, a plethora of information gets displayed, such as DNS servers, related sites, related emails, email servers, and even more detailed connections such as names associated with emails and phone numbers.


Let’s take a closer look at the profile of the employee, “John Doe." Right-click on John’s icon and run "All Transforms."


When the transforms are finished, it generates a new graph with all of John‘s associated links.


We can find his Flickr account as well as some other accounts, which may uncover more OSINT possibilities for further investigation.


## How to Use Maltego to Run Email Addresses?


Create a new graph.


From the Entity palette look for Email Address and drag and drop it into an empty page.


Double-click the icon and change the email address that we found in the graph 1 result, to verify that the email is valid we can run IPQS Tag Transform.


We will check if an email has ever been breached by using havibeenpwned Transform and by getting all paste featuring email address.


Now, let’s run both the transforms.


## Discover Email Addresses from an Organization


Either add the company domain to our blank canvas or utilize the “Company Stalker” machine, which offers an easy way to scrape a large amount of data to begin capturing an organization’s email addresses.


To start a machine, click on the Machines tab at the top of the Maltego window. Then click the Run Machine icon and select the machine you want to run.


Select the company Stalker and click “Next”.


Enter the Domain name you want to find the email addresses for. Click Finish.


Select all the mail addresses and run haveibeenpwned Transform.


The result has given the output for breached email addresses and Pastebin URLs.


*Pastebin URLs*


So, that’s how you conduct basic OSINT research using Maltego. It is a powerful and intuitive platform for information gathering, which parses through open-source information. You can also add manual links to the tree graph and create an execution strategy.


We will cover more OSINT frameworks in the upcoming blogs. Also, refer to our blog post titled, [Introduction to OSINT](https://redfoxsec.com/blog/introduction-to-osint/).[Redfox Security](https://redfoxsec.com/) is a diverse network of expert security consultants with a global mindset and a collaborative culture. We proudly deliver robust security solutions with data-driven, research-based, and manual testing methodologies.


“Join us on our journey of growth and development by signing up for our comprehensive [courses](https://training.redfoxsec.com/).””

---

*Originally published on [Medium](https://infosecwriteups.com/osint-with-maltego-202666e32d1e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
