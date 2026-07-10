# :globe_with_meridians: Easy XSSHunter Automation Setup Script | Adam J Sturge

> **Original Source:** [Easy XSSHunter Automation Setup Script | Adam J Sturge](https://infosecwriteups.com/easy-xsshunter-express-setup-script-d5a66039f7b6)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Easy XSSHunter Express Setup Script


Recently XSSHunter.com decided to stop signups and soon stopping its services. You’ll need to host your own version of XSSHunter. I wrote an [article](https://adamjsturge.medium.com/xss-hunter-slack-alerts-c2c778a1da3f?sk=ca03c42e5883340ffaf1f7dc9de7d3c1) about my fork of XSSHunter Express. Since making that article I wanted to make the process of setting up XSSHunter easier so I made a script for it. I’ll be referencing my repo [https://github.com/adamjsturge/easy-xsshunter-express](https://github.com/adamjsturge/easy-xsshunter-express) throughout this article.


Note: Discord Integration was recently added and is included in the new setup script. I wrote a more in-depth write up below


*Easy XSSHunter Express Running*


Before we get started, you’ll need a VPS. I recommend [VPSCheap](https://crm.vpscheap.net/aff.php?aff=27) and [Digital Ocean](https://m.do.co/c/a165a29be76c). You’ll also need a domain/subdomain that points to your VPS's IP.

### Installation


First step is to grab the script for Github.


```
curl -fsSL https://raw.githubusercontent.com/adamjsturge/easy-xsshunter-express/master/easy-xsshunter-express.sh -o easy-xsshunter-express.sh
```


Once we grab the script, we are going to run it with bash.


```
sudo bash easy-xsshunter-express.sh
```

---

*Originally published on [Medium](https://infosecwriteups.com/easy-xsshunter-express-setup-script-d5a66039f7b6). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
