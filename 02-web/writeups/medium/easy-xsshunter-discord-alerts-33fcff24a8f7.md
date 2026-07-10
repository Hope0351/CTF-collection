# :globe_with_meridians: Easy XSSHunter Discord Alerts

---

# Easy XSSHunter Discord Alerts

This will be a setup guide for XSSHunter and integrating it with Discord Alerts. This will be very similar to my other article but with more details

*XSSHunter Discord Alert*

## Installation

The first step is to download the Github script.

```
curl -fsSL https://raw.githubusercontent.com/adamjsturge/easy-xsshunter-express/master/easy-xsshunter-express.sh -o easy-xsshunter-express.sh
```

Once we grab the script, we are going to run it with bash.

```
sudo bash easy-xsshunter-express.sh
```

## Script Setup Tutorial

You will first be prompted if you want to install Docker or not with the script. It’s easy to abort the Docker install, so don’t be afraid to try anything.

*XSSHunter Discord Alerts Terminal Setup*

After Docker, pick the second option for my fork ([github repository](https://github.com/adamjsturge/xsshunter-express)). Since this is for my personal XSSHunter setup, I am going to say no to email and slack notifications but yes to discord notifications.

To get your webhook from Discord, you need to have your own Discord server and channel. By clicking Edit Channel, you can make the discord channel private. That webhook URL will be used…

---
