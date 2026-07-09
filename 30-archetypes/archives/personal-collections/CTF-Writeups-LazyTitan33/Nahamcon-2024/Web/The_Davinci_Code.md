## The Davinci Code

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

The first page that loads seems very basic and in fact only has one endpoint:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, accessing that endpoint shows us a Flask Debug error.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

For a while we thought the challenge was broken, but the challenge description does mention that the website is broken, so it must be intentional. Taking a closer look at the debug error, we see it leaks that the root supports another HTTP request method other than GET.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

PROPFIND is used to retrieve properties, stored as XML, from a web resource, usually associated with WebDav servers. This explains the sneaky DAVinci from the challenge title so we must be on the correct path. We can use this HTTP request method to enumerate the web app directory and can see another directory.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In that directory, we can see the flag.txt file.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The question for the longest time was how can we read the flag, because it's in a folder that isn't defined as a route in Flask so we can't access it from the webpage directly. Looking around some more, we find a backup of the app in the /static directory:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can download files from the static directory because that's what it's there for.  To serve static files to the app.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Now that we have the source code, we can play around with it locally to better understand it. After we do more research on WebDav we find that there is another HTTP method we can abuse.  

https://learn.microsoft.com/en-us/previous-versions/office/developer/exchange-server-2003/aa142926(v=exchg.65)

## Solution

We can use the MOVE method to move the flag.txt from the endpoint into the static directory:  

```bash
curl -X MOVE --header 'Destination:static/flag.txt' 'http://challenge.nahamcon.com:31144/the_secret_dav_inci_code/flag.txt'
```

Now we can access it directly and score some points:  

```bash
curl http://challenge.nahamcon.com:31144/static/flag.txt
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`flag{2bc76964262b3a1bbd5bc610c6918438}`
