# :game_die: PHST CTF 2021 - WRITE-UP. Capture the flag with PST

---

## Good Friday (Langfredag)

Today’s picture tells a story about an upgrade that was carried out by a consulting company, which caused the whole system to go down. The “Eggchange” server is not working, and all we possess is a [log file.](https://gist.github.com/suxSx/e83c687141e86c2b5845a820430ae468)

*Picture of the day , day 2— by [PST](https://p26e.dev/#langfredag)*

Looking throw the log file I notice that the update are loaded from github: git@paaschecomsulting/eggschange

```
[EGGSCHANGE] Set-DeliveryAddress id=0bea61679ac648bb9c5fac74fc57e46b
[EGGSCHANGE] Send-HealthStatus status=ok
[EGGSCHANGE] Update-EggContent id=f9c057294aae473cb0134868aefbf32c
[EGGNET] Set-UpdateStatus status=UpdateAvailabel
[EGGNET] Send-NewEggsChangeUpdate update=2.e66
[EGGSCHANGE] Set-DeliveryAddress id=0cd555bb4bb94466bbff809bc840a80a
[EGGSCHANGE] Set-DeliveryAddress id=ca84059bcf59417da14e05cf8eeff8e4
[EGGSCHANGE] Set-DeliveryAddress id=e58381696b44450b886b0cc958c7183d
[EGGNET] Set-EggsChangeHealth health=ok
[EGGSCHANGE] Update-EggContent id=bcff9cfa57de4fb1a76cc3b75a108b5d
[EGGNET] Get-EggsChangeHealth
[EGGSCHANGE] Update-EggContent id=5d6c3239d8b64ad78ca9749ac22a8b31
[EGGSCHANGE] Get-EggStatus id=63a50df11ce04b3992f4d83a980e4780
[EGGSCHANGE] Get-NewUpdate git@paaschecomsulting/eggschange
[EGGSCHANGE] Set-DeliveryAddress id=757929db9030410f95767cafbe492cac
```

I head over to [https://github.com/paaschecomsulting/eggschange/](https://github.com/paaschecomsulting/eggschange/) and find the update files. The update consists of a main script, a module and two binaries.

This is a very well-made script with a lot of humor. When you trigger it, it “loads” infective updates, creating nice ASCII images. And as a bonus, it puts in a task that makes your computer turn off at 6 p.m.

This was then the reason why the “eggchange” server went down. After a glance, I find this is the only code that is worth noting.

When you execute the script, it asks for a key. We do not possess this. On the other hand, it says that if you are doubtful. Maybe check help files.

I convert help files from base64 and see there are image files. Save them as png and get two nice pictures of Easter bunnies. This does not grant me much, I run them through various stegano-tools, but still nothing.

But at that moment, suddenly when I look through them in the notepad, I notice the authors of the picture. Those names seem extremely familiar.

*Screenshot of help file — by Author*

A quick google search for Marc Stevens and Ange Albertini brings me to this website [https://github.com/corkami/collisions](https://github.com/corkami/collisions).

It tells of an exploit that makes it possible to have the same MD5 checksum on two different images. Well why not do I think, what if the MD5 sum of the pictures is the key.

## Get Marcus Knoph’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I upload it into my favorite tool [cyberchef](https://gchq.github.io/CyberChef/#recipe=MD5()&input=NzY0OTJkMTExNjc0M2YwNDIzNDEzYjE2MDUwYTUzNDVNZ0I4QUhvQWRRQTJBQ3NBVUFCV0FEa0FiUUJ2QUdNQVlnQkRBR2dBU1FCNkFHVUFkZ0J4QUdnQVNRQlFBR2NBUFFBOUFId0FOd0F4QURrQU1BQTJBRElBTndBd0FESUFaZ0F6QUdNQVpnQTVBRGtBTWdBMUFHUUFaUUEzQURZQU9RQmpBREFBWVFBekFHUUFNZ0EyQUdFQU1BQXhBRGNBWVFCakFHSUFOQUJtQUdRQU53QTBBR1VBWVFCaEFEQUFNQUJsQURJQU1BQmpBRFFBTndCaUFHTUFaQUE0QURVQU9RQXdBR1FBTkFCaUFEUUFNUUEwQUdNQU13QTBBREFBTUFCaUFEY0FOd0E1QURrQVpRQTRBRGtBTWdBNUFHWUFZd0F3QURjQU1BQTVBRElBTXdCbUFEUUFOZ0JrQUdFQU13QmxBRGdBTkFBeEFEWUFPQUEwQURNQU1RQTRBRFlBTlFCbEFESUFaZ0ExQURjQU9BQTNBR01BWXdBMEFESUFOZ0JoQURNQVlRQmtBRE1BT0FBeEFHUUFNQUEyQURRQVl3QTNBREFBWVFCbUFHTUFNZ0JrQUdVQVpRQm1BRFFBTVFCbUFEY0FNQUF6QUdFQVl3QmhBRE1BWXdCakFHTUFPUUJsQURjQU5BQmlBRElBTUFBPQ). And get the MD5 hash: 4a981c87ef142f95d04424a29235dcfc. Run it in the script and yes, there is the flag for today.

```
PS eggschange-main\Update_2.e66> .\Påskenott.ps1
Velkommen til oppdateringsveiviseren for Paasche consults eggschange-server Vennligst vent mens vi laster inn nødvendige moduler cmdlet Test-EggschangeFlag at command pipeline position 1 Supply values for the following parameters:
Decryption_key: 4a981c87ef142f95d04424a29235dcfc PST{PaascheStemning_og_Kraftskall}
```

---
