# :globe_with_meridians: Reflected xss triggered in URL 🔎

---

# Reflected xss triggered in URL 🔎

Let’s dig in together…

Hello guys, here I am back again with a report on reflected xss which was again very easy bug to find but interesting. Took me a min to find the bug …😁

So, my last report was of Open redirection via google sign in (https://infosecwriteups.com/open-redirect-in-target-via-google-sign-in-d42b3cb633d). I mentioned in my last report, that it is a must to check for xss or sql injections where there is open redirection. There are always high chances to get it !!

Anyways, so I tested for reflected xss :

Firstly, I went forward to register in the website (for example : abc.com), by clicking join for free.

https://abc.com/join?continue_to=%2F (The original URL)

After then, I filled up the necessary details and crafted the xss payload as shown :

https://abc.com/join?continue_to=javascript:prompt(123) (The crafted URL)

Next step was obvious , i.e to click Join and the following page appeared then :

---
