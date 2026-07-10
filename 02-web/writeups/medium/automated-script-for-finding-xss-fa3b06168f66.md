# :globe_with_meridians: AUTOMATED SCRIPT FOR FINDING XSS

---

# AUTOMATED SCRIPT FOR FINDING XSS

An example of a web security vulnerability is cross-site scripting (XSS), which enables attackers to insert malicious executable scripts into the code of a website or application that is trusted. An XSS attack is frequently started by an attacker tempting a user to click on a malicious link that they deliver to them. Through cross-site scripting (XSS) assaults, attackers can get around access restrictions like the same-origin policy, which separates websites from one another.Zero When the victim accesses the website or application that runs the malicious code, the attack really takes place.1. Malicious scripts are injected into websites that are otherwise trustworthy and benign in an exploit known as cross-site scripting (XSS).

HERE IS THE SCRIPT THAT AUTOMATES XSS DETECTION

caturls.txt|egrep -iv “.(jpg|jpeg|js|cs|gif|tiff|png|woff|woff2|ico|pdf|svg|txt)” |qsreplace ‘ “><()’|tee combinedfuzz.json && cat combinedfuzz.json|while read host do; do curl — silent — path-as-is — insecure “$host” |grep -qs “\”><()” && echo -e “$host \033[91m Vulnerable \e[0m \n” || echo -e “$host \033[92m Not Vulnerable \e[0m \n”; done |tee saveitas.txt

## STEP 1

type nano xxsautomation.txt and copy paste the above script in it and save it

this is for future reference ,its your wish to save it like this

## STEP 2

the screenshot is little different so don’t be confuse yourself use the above syntax

## STEP 3

create a nano urls.txt and store the links you wanna check ,like mentioned below

## STEP 4

finally run this on terminal

*Originally published at *[https://readitgainit.blogspot.com](https://readitgainit.blogspot.com/2023/10/automated-script-for-finding-xss.html)* on October 25, 2023.*

---
