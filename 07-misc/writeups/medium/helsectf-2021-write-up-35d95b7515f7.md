# :game_die: HelseCTF 2021 Easter Edtion - WRITE-UP

> **Original Source:** [HelseCTF 2021 Easter Edtion - WRITE-UP](https://infosecwriteups.com/helsectf-2021-write-up-35d95b7515f7)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2021

---

## Osint


There was 12 challenges based on OSINT information gathering.

### Discord


```
Det kan være lurt å sjekke Discord: [https://discord.gg/b3zS2QrrU9](https://discord.gg/b3zS2QrrU9)
```


All you had to do here was to visit the dicord channel. Look at the news and yo find the flag in one of the posts.


```
HelseCTF — Yesterday at 10:08 AM
:chicken: :rabbit: :rabbit2: :hatching_chick: :baby_chick: :hatched_chick: :egg:
HelseCTF vil automagisk åpne nå om 2 timer hvis CTFd fungerer som tiltenkt.Alle oppgaver åpnes samtidig. Som en hovedregel vil det ikke bli lagt ut hint på noen av oppgavene, men det kan jo tenkes at vi har totalt bomma på vanskelighetsgrad eller hintlesing fra oppgaveteksten. Dette vil bli vurdert fortløpende. Eventuelle hint vil bli annonsert i god tid (discord/ctfd).God påske og EGG{lykke_til!}
:chicken: :rabbit: :rabbit2: :hatching_chick: :baby_chick: :hatched_chick: :egg:
```


### Twitter


```
Det kan være lurt å sjekke Twitter: [https://twitter.com/helsectf](https://twitter.com/helsectf)
```


Same as the last one, visit Twitter and in one of the latest post you find the flagg.


```
HelseCTF 2021 er åpen for registrering. 22. mars kl12 til 6. april. [http://helsectf.no](http://helsectf.no) #påskenøtter #ctf #EGG{helsectf_er_g0y}
```


### Oppdraget


```
Hva skal HelseCERT oppdage, forebygge og håndtere?Et hint kan være å lese finn.no annonsen: [https://www.finn.no/job/fulltime/ad.html?finnkode=209984069](https://www.finn.no/job/fulltime/ad.html?finnkode=209984069)Flagget er EGG{<et norsk ord>}
```


If you visit the add on Finn you can find the answer. They ask what are they suppose to idenify and manage. The answer is EGG{cyberangrep} (cyberattack)

### Nasjonale e-helseløsninger


```
Norsk Helsenett SF utvikler, forvalter og drifter mange nasjonale e-helseløsninger. Kan du nevne minst en av de?Flagget er EGG{<navn på en nasjonal e-helseløsning>}
```


What is the name of a natinal organization that use HelseCERT? The answer is EGG{helsenorge}.

### LinkedIn


```
Norsk Helsenett SF utvikler, forvalter og drifter mange nasjonale e-helseløsninger. Kan du nevne minst en av de?Flagget er EGG{<navn på en nasjonal e-helseløsning>}
```


If you visit LinkedIn you can find this post:


```
Tar du utfordringen? HelseCERT gjentar fjorårets suksess med påskectf. Individuell konkurranse. Åpent for alle. 22. mars til 6. april. Ingen premier. Norsk/engelsk. #påskenøtt #nhn #rekruttering #EGG_helsectf #helsecert
```


The egg is in the hashtag: EGG{helsectf}

### Prop. 1S (2020–2021)


```
Hvor stort var det samlede budsjettforslaget til helse- og omsorgsdepartementet for 2021?Flagget er EGG{<antall milliarder, avrundet nedover>}
```


A quick google search on Prop. 1S gives you the following result:


```
Prop. 1 S (2020–2021) — regjeringen.nowww.regjeringen.no › … › Prop. 1 S (2020–2021) Norge var et av de første landene i verden som utviklet en nasjonal demensplan. … Helse- og omsorgsdepartementets samlede budsjettforslag er om lag 239,7 mrd. … For å komme fram til hvor stor realvekst budsjettforslaget representerer, må …
```


The answer is therefore: EGG{239}

### Stats foretak


```
I hvilket år ble Norsk Helsenett SF stiftet av Helse- og omsorgsdepartementet?Flagget er EGG{<årstall>}
```


A quick google search gives you:


```
2009 — fra AS til statsforetak
Målsettingen var å satse på forebyggende og koordinerte helsetjenester med stor vekt på bruk av IKT. Etter initiativ fra Hanssen ble Norsk Helsenett SF stiftet av Helse- og omsorgsdepartementet i juli.
```


The egg is then: EGG{2009}

### Tildeling


```
Siden vår byråkratiske stat har blitt digitalisert ligger det mange offentlige dokumenter på nett. Her kan små og store påskekyllinger lese om hva de litt eldre og mer etablerte 🐔 har bestemt for allmennheten.Hvor stor var den totale tildelingen fra Helse- og omsorgsdepartementet til Norsk Helsenett SF for 2021?Flagget er EGG{<nærmeste millioner kroner, avrundet nedover>}
```


This was a little more tricky, I finnaly find [this document](https://www.nhn.no/media/3435/nhn-oppdragsbrev-2021.pdf) explaing who gets what:


```
Oppdragsbrev til Norsk helsenett SF for 2021
Helse- og omsorgsdepartementet har på bakgrunn av Prop. 1 S (2020–2021) og Innst. 11 S
(2020–2021) vedtatt å tildele følgende til Norsk helsenett SF:
(i 1000 kroner)
Kapittel Post Betegnelse Bevilgning
701 70 Norsk helsenett SF 151 633
701 72 Nasjonale e-helseløsninger 504 884
781 21 Spesielle driftsutgifter 1 000
```


Add them all up and you get the: EGG{657}

### Telling av meldinger


```
I Norsk Helsenett er det mange ivrige påskekyllinger som liker å telle meldinger. Faktisk er de så begeistret for meldingstelling at de har laget en egen tjeneste for dette, åpent tilgjengelig for alle.Totalt hvor mange eResept-meldinger (for hele landet) ble utvekslet mellom ulike aktører over helsenettet for hele 2020?Flagget er EGG{<antall millioner, avrundet nedover>}
```


They want you to find this [webpage](https://meldingsteller.nhn.no/) that gives you statistic about all the health related tech in Norway. You can tweek this to give you the result for the number of e-prescription given in 2020:


```
Antall meldinger fra 01.01.2020, 00:00 til og med 01.01.2021, 00:00
Filtrert på
Meldingskategorier:
eResept-meldinger
Meldingsformat: EbXml og Ikke EbXml
Rediger spørring
Last ned rapport
Totalt antall meldinger
Antall
102 654 980
```


The answer is then: EGG{102}

### Harer i mosen #1


```
En alarm i sensornettet har trigget på mistenksomme filoverføringer og en av påskekyllingene har fanget opp tilhørende nettverkstrafikk. Påskekyllingen ser at det er en ukjent enhet som har overført bildefiler, men sliter med å finne ut hvem som eier denne. Kan du hjelpe til med å finne ut hvem som står bak?
```


Open [the pcap](https://knoph.cc/ctf/write-up/helsectf-harer-imosen-mistenksom_trafikk.pcap) file that you get with the mission. Then follow the TCP stream for HTTP upload and you will find the flag in the author section.


*Sceenprint wireshark — by Author*


The egg is then: EGG{H4R4LD_H4R3PU5}

### Harer i mosen #2


```
Ved nærmere inspeksjon virker som innholdet i filoverføringen kan ha lokasjonsdata. Påskekyllingen ser trist ut og forteller at han var syk den dagen de hadde geografi på kyllingskolen. Klarer du å finne navnet på bygget som bildene ble tatt fra?Flagget er EGG{<navn på bygget>}
```


Start by exporting all the files in the HTTP stream:


*Export Files Wireshark — by Author*


Choose where to save them and open the folder. In the folder you can see if you open 3 of the files in notepad that it is images. Dont let the PDF marks fool you.


## Get Marcus Knoph’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Opening the images will show you the view of different places with a red square at it. Or mission if to find out where the pictures are taken. I use [https://www.metadata2go.com/](https://www.metadata2go.com/) to find the meta data for each image. And all of them contains some GPS cordinates:


```
Image 1: 63 deg 25' 16.11" N, 10 deg 15' 7.73" E
Image 2: 63 deg 24' 40.07" N, 10 deg 25' 51.23" E
Image 3: 63 deg 25' 36.81" N, 10 deg 23' 48.95" E
```


I then use [GeoJava](http://geo.javawa.nl/coordcalc/index_en.html) to triangualte the position:


*[Gps Triangulation](http://geo.javawa.nl/coordcalc/index_en.html) — by Author*


They all point to around the address at Abels Gate 9. A quick google search tells me that HelseCERT also have an office there, and the bulding is known as abels hus. This turns out to be the EGG: EGG{abels_hus}.

### Harer i mosen #3


```
En av påskekyllingene ser på bildene og reagerer plutselig. “Her er det noe muffens, men jeg klarer ikke helt å sette fingeren på det.” Han anbefaler at du analyserer bildene nærmere for å se om det er noe som skiller seg ut. En annen påskekylling nikker og legger til at vi enda ikke vet hvor bildene har blitt sendt. De lurer fælt på hva som egentlig har skjedd her. Kan du se om du finner noe som kan peke på hvor bildene har blitt lastet opp?
```


The task gives us all the information that we need. They say that one of the images have something extra to it, but they cant put the finger on what it is. The mostlikly image to have something to it is the biggest one.


I use the same files from Harer i mosen #2 and upload it to [https://futureboy.us/stegano/decinput.html](https://futureboy.us/stegano/decinput.html)


As I though the biggest picture are hiding something and it gives me a Key as a result:


```
The payload may be:
ASCII textTo display, I might suggest using a MIME type of:
text/plain“steganoin26771.jpg”:
format: jpeg
capacity: 111.7 KB
embedded file “ThisLooksSuspicios.key”:
size: 1.7 KB
encrypted: rijndael-128, cbc
compressed: yes — — -BEGIN PRIVATE KEY — — -
MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQCw29tWB+lxoO/p
AkuZsPr+70O04q79IKRiZrGPLrNzl4gCwrJ0sgaDGw3Iq2x9Lva24tuLrEsI27c6
6yVnQqey0dpPl4gtyqGsv2AVORUQHGtcvDqyp1UYA99W8Y/QDah7iLqRBjQW6Q5Q
/J98/pei/ki4ABsOuKTY81xclA3+65U5GHsN+jRIlUGqyqGTObX91lgwrgoT1yTr
sdJnYLi+f8mfNuDKQUEFffo7ZEo3gA68y0UgeyvnnQ517YmSu5E6gvEJtbMs+lnF
XnHyZ4MuWiMhTjuiq2pB94rxzk4WBci95KQHxKYlY/NEEtcZBx9futPdUUOkDjo5
BJB8taLbAgMBAAECggEBAKPOPkxkb5dK1GogMh1bil3tBezXt/PC8/4f130iaBs7
0kGcSuVCrj1oJVAjVgxsHx4s5+Np5OWDeyYa/T2ywtgg/e6SDxM6hpwVdMyzXgra
B6aQwF0QFwRzMby5Z9XvkIk6jnIcKMq/eP8RvDZtJ81Tb87cajMsWaKHZJhqmLvt
s4iOay3eRbpyl52WfYG9MKnpq4NJgohKrl9J1GUW6UnCXu+dOpTUjQ7J/Ex5nqej
5M8rcMuInhWg5s0T6bOlBU0rMpNHtFq3gBNAm41kh9UNzNTy0JLRlFNu57eUqQ1y
YvAfFe0l7K2n4Iy/buBXwrK0hEDb44NeUt3f2mc5D2ECgYEA5rrlNBkePt+kH9bR
h5ttygneSaPIfNUVCJcLcZ3AtrcZvlFNosV1yjep/coOreEqf1QFX4uoasVzavVh
36TLuY/OCkxfUhWfJgm52JKms0SBrDps26QO181woU2fdMfoWj4IMd1Bod/fvMMA
qdNSli2hvvzTQbr913ZGkb8it1cCgYEAxDqLQSs90oUhTcGga6JJ7ennmkvTSnd4
NaCL6R4Pwrr6yF+OZ904xdM/UOIABEixUDxR5lyXD+OqBDVppHcpYat7BZ4rT+QB
SnZBH2WFtj9rYESPZeARbuOm5sekT5rBz1JjabrrGJFYFsT0kmQgl2PEIR5ex6DR
zlsVE3o7Uh0CgYEAwNvf0hhcy7kr+uEY6vzkXEi7YVphrtZ9aly22BVAjHmoLwjO
mAvtVUYJ9XT7qCPZ3exhQWf/MqAwxWqukL2y/DxTwQ/tbTNdf/IJQhny9U2CBnAf
pcgQEBpM1seHTZn7gdLwDp4eyivTXHizCUD2e0lRNc8m1n5yx7K5cgIOBqkCgYEA
sWImvduEAEkeaPbOuF21LN9T4LQIpXlH7lpZ/3qQTrzNtNJEnflpt9KVmt0hnL3F
o71TX8V1PQTVjQZnoCej/cmQ5OwtRQPcct5hUito6u17eEOhyTr7J12dY2M3UkqY
Rny4pzw0BzpkAfk7CRaAK7og8rtMfHMRFdRaQggtlbUCgYBlaRtQxFRYc8ciJy6A
x8wg6mSgYx0c7Teg+dVIr/jA5ykP9EhYbSQIrJS2fv3Jz62+b/zmD7jyW5xX9RaO
lp7aeHsKb/vGOAodYUajI1os4qcDThvFrJ6DwnzT6wNYxJO7bW3W2jrFQ/xSx+I+
9qG+hQsfdaFCRM12P+X4unr/KA==
— — -END PRIVATE KEY — — -
```


I save the key and add it to wireshark:


*Adding RSA key to Wireshark — by Author*


I then filter out all the TLS packets: (http.request or tls.handshake.type eq 1) and !(ssdp)


All the data traffic that earlier was unreadable are now in ASCII plain text. A quick look tells you that there now are new files. One if very interesting bloggonnlegg.txt go ahed and export the new files and open it.


```
— — — — — — — — — — — — — dfa83fc40bbceed3
Content-Disposition: form-data; name=”text”; filename=”blogginnlegg.txt”
Content-Type: text/plainHeia bloggen! Jeg var en tur på kontoret i dag og tok noen bilder, se den flotte utsikten! Man kan se flere av de kjente byggene i Trondheim slik som Nidarosdomen og Gråkallen radarhode. Vi har til og med utsikt til Moholt studentby, hvor jeg bodde da jeg var student. Good times. I dag serverte de hjortegryte i kantina, nam nam! Vi får jo nærmest restaurantmat her på jobben. Men det var alt for denne gang. Husk å følge EGG{H4R3BL0GG3N} for å få med deg fremtidige blogginnlegg fra meg! Harald Harepus out!
— — — — — — — — — — — — — dfa83fc40bbceed3 —
```


And there you have it the egg is: EGG{H4R3BL0GG3N}

---

*Originally published on [Medium](https://infosecwriteups.com/helsectf-2021-write-up-35d95b7515f7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
