# :link: Account Takeover using Improper Authorization in “Check Availability” Feature

> **Original Source:** [Account Takeover using Improper Authorization in “Check Availability” Feature](https://infosecwriteups.com/account-takeover-using-improper-authorization-in-check-availability-feature-4f9f65098853)
> **Platform:** infosecwriteups.com | **Category:** `BLOCKCHAIN`

---

# Account Takeover using Improper Authorization in “Check Availability” Feature


Hello Guys!!!!


Hope you are doing Great.


This article is about recently resolved report, which was submitted to private program. which is application for hiring professionals for different kind of services like House cleaning , carpet cleaning , plumbers, Painters,Contractors.


*Victim Account*


As seen above anyone can sign up through email address in application and his account would be created. As seen in above image victim has not supplied his phone number.Account is registered using email only.


Application has profile of the professionals who provides services like plumber, contractors,electricians and more. There is functionality to check availability of such professional unauthenticated.


So any user without any kind of authentication go to any professional’s profile which contains his ratings and feedback,can start the flow to check availability of that professional as seen below

*Check Availability*


While go through this flow we can supply victim’s email which account already exist as below

---

*Originally published on [Medium](https://infosecwriteups.com/account-takeover-using-improper-authorization-in-check-availability-feature-4f9f65098853). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of blockchain CTF writeups.*
