# :game_die: NPST CTF 2021- WRITE-UP

> **Original Source:** [NPST CTF 2021- WRITE-UP](https://infosecwriteups.com/npst-ctf-2021-write-up-96b58464151d)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2021

---

## Day 23 — Sabotage


Oh no, someone has changed the GPS for Santa’s sled. There have for some time been suspicions about a rough Elf, but now this have been confirmed. And they request us to look and see if we can discover the elf.


```
Alvene i sledegarasjen rapporterer om at noen har tuklet med julegaveruta som er lagt inn i slede-GPSen. Det er kritisk fordi det ikke er mulig å overstyre sledens GPS-kurs under flyturen. Det har visst blitt lagt til et stopp på Antarktis, rett utenfor SPST sitt hovedkvarter, og jeg (Julenissen) er redd for at SPST planlegger å rappe alle gavene fra sleden på selveste julaften.I slede-GPS-loggen er det lagt igjen en kort beskjed: “Ikke god jul, hilsen M”.Det er derfor høy prioritet å finne ut hvem “M” er, før “M” klarer å utrette mer ugagn. Mellomleder har skrytt av din innsats denne førjulstiden, så jeg vil derfor betro denne viktige oppgaven til nettopp deg. Jeg personlig har ikke tid, for jeg skal først på gløggsmaking og så skal jeg se Grevinnen og Hovmesteren. Du blir gitt tilgang til kontoret mitt i kveld for å lete gjennom papirer og se om du klarer å finne ut hvem rakkeren er. Navnet rapporteres tilbake til meg (du må selv pakke navnet inn i formatet pst{}).Dette oppdraget er gradert “Temmelig Hemmelig”, så ikke fortell om dine funn til noen andre enn meg personlig.[📎 Julenissens_kontor.png](https://wiarnvnpsjysgqbwigrn.supabase.co/storage/v1/object/public/files/u9On67xdLejo7yJlRlvgJ/Julenissens_kontor.png)Hoho, Julenissen
```


For this mission we gain access to [Santa’s office](https://wiarnvnpsjysgqbwigrn.supabase.co/storage/v1/object/public/files/u9On67xdLejo7yJlRlvgJ/Julenissens_kontor.png), and they invite us to look if we can find anything useful.


*Santas office — by [NPST](http://dass.p26e.dev)*


I start by downloading the image we got and running it through Binwalker. This produces a couple of files for us to look at. Some of the files will in addition be utilized for the challenge next day. But for this challenge is the note_to_elf.txt a nice place to start.


*Binwalk Jule nissen kontor — by Author*


This informs us that the elf needs to represent an employee of NPST, they have to be nice, and they most likely start at m. Along with all the files, we moreover possess the nice and bad list for personnel on M.


*Nice and bad list screen print — by Author*


This is way to long to look at by hand, so I develop a script.


After running the script sorting out nice personnel working at NPST, we can see there is one name that stands out: Maximilian.


```
> py .\cracker_sabotasje.py
[‘Madel’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Madina’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Maggi’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Magnor’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Malfred’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Manuela’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Marenius’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Margun’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Marinius’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Mario’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Marte’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Marylyn’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Maud’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Maximilian’, ‘Ja’, ‘Nei’, ‘Ja’]
[‘Merete’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Milliam’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Mohammad’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Moritz’, ‘Ja’, ‘Ja’, ‘Ja’]
[‘Målfrid’, ‘Ja’, ‘Ja’, ‘Ja’]
```


He is the only one that haven’t received a gift this year. I forward it in as a flag PST{Maximilian} and yes that’s the flag for today.

---

*Originally published on [Medium](https://infosecwriteups.com/npst-ctf-2021-write-up-96b58464151d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
