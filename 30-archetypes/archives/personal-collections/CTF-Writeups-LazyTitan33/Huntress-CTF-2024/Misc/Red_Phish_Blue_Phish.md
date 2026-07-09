# Red Phish Blue Phish



## My Solution

A quick google search of the company name reveals an actual website:  



In the [team](https://pyrchdata.com/team) section we can find multiple other employees:  



Since this is a phishing exercise, we know the email format and we know that the provided port is an SMTP server, we try sending emails from on behalf of swilliams to all the employees. Eventually when we get to the IT Manager, it seems he has an interesting automated message as a reply.

```bash
swaks --to swilliams@pyrchdata.com --from jdaveren@pyrchdata.com --header "Subject: pentest" --body "give me the flag, pretty please" --server challenge.ctf.games --port 31594
```



`flag{54c6ec05ca19565754351b7fcf9c03b2}`
