# :game_die: My First Bug Bounty: SQL Injection!

---

# My First Bug Bounty: SQL Injection!

Hello there, I am Veshraj Ghimire all the way from Nepal. This is my first bounty write up. In this writeup, I will explain about my 1st critical finding on a site listed at [Bugv](http://bugv.io).

## Get Veshraj Ghimire’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So, Let Me Explain my short story about it.

*Let’s Get Started!*

>

Severity: Critical

The target was very fresh because it was listed on the platform just one day ago. Since I don’t have permission to disclose the program. Let me call it target.com. The next day, I planned to test on the program. I started my recon with enumerating subdomains and probing them with httpx and checking title, status code and content length at once by following command:

>

subfinder -d target.com -silent -o subs.txt | httpx -title -content-length -status-code -silent

While subfinder was enumerating subdomains for me. I noticed one intresting subdomain called adminsite.target.com. Then, I opened the site to check the contents on that site. The site was basically for searching some contents with some extra categories, where categories were taken as integer with parameter: “jbscategory”. When i searched for some category, url would look something like: [https://subdomain.target.com/search.php?jbscategory=](https://adminsite.rojgari.com/searchjbs.php?jbskeyword=a&jbscategory=.102)1

*Me often :V*

Wow, The content of the page changed! It did not gave sql error but the content of the page changed. To verify if it is vulnerable, I balanced it by using simple integer based balance: — -. And Boom, the previous content having category 1 was displayed. By this i was confirmed that it is vulnerable to sql injection. I was very happy and much excited because it was my first finding ever on bug bounty platform. Then i quickly checked numbers of columns by simple order by query and confirmed that there was 11 columns. After that I used following query to find out database name:

>

&jbscategory=1'union select 1,2,database(),3,4,5,6,7,8,9,10,11 — +-

And yeah, the database name got displayed.

*Dancing me :V*

After that I was very excited and nervous . I was fearing that it may be duplicate, so reported it very quickly by just showing the database name displayed with the payload.

*Excited and nervous :V*

After One hours, The Report got Triaged, Finally I got it!!, I was very happy.

*wew triaged :VHappy me :V*

Then after some weeks, it was changed to unresolved and I was awarded 100$ for my report. In this way, Finally, I got my 1st Bounty.

*1st Bounty :V*

>

Thankyou to all supporting people helping me to achieve it directly and indirectly. Mainly, I want to thank Avian Chhetri Dai for helping me to get into this and the awesome Nepali community [Pentester Nepal](https://www.facebook.com/groups/pentesternepal/).

Here’s what you get from this write-up:

- Keep on trying, Never give up (Wait For your time).

- Always follow the road which is less traveled.

- Keep learning.

I also recommend [this video](https://www.youtube.com/watch?v=kXwGsIz3xnU&t=950s) by Nittam Dai, if you want to understand SQL injection in depth in Nepali Language.

You can Follow me on [Twitter](https://twitter.com/GhimireVeshraj) if you wish.

So, That’s all for this writeup, Thankyou for making it till end.

*Cringe Alert :V*

---
