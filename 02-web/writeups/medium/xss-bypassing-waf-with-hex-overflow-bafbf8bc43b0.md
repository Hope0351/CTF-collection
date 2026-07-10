# :globe_with_meridians: Medium

---

# XSS — Bypassing WAF with Hex Overflow

Hello, I’m Syed Mushfik Hasan Tahsin aka [SMHTahsin33](https://x.com/SMHTahsin33). A 20 Y/O Cyber Security Enthusiast from Bangladesh. Passionately doing Bug Bounties in my free time solely out of curiosity. I am an eWPTXv2 as well.

Today I will be writing about how I bypassed BIG IP Local Traffic Manager (F5 Networks) Web Application Firewall using Hex Overflow.

The story will be going with a straight flow, but in reality the situation was a little bit backward. More likely Solving the problem first, then knowing what the actual problem was.

Before I start, A huge thanks to @[Gareth Heyes](https://x.com/garethheyes)for the invaluable help in gaining a deeper understanding of this!

Let’s get started!

## The XSS

Initially after observing that the input was unsanitized. I input a simple payload **<svg onload=alert()>** . This was immediately blocked.

So I started probing until the block was gone, and came to **<svg onload>**, meaning** onload=** (with the equal sign) was actually getting blocked. After seeing this, I tried all possible event handlers there, and nothing worked out. Dead end?

## Introducing — Hex Overflow

Hex or Hexadecimal is a 16-Base number system allowing **0-F(0123456789ABCDEF)** maxing out at FF. It is very much common to us that reserved or unsafe characters [[RFC 1738 2.2](https://datatracker.ietf.org/doc/html/rfc1738#section-2.2)] are encoded in the URL which is two Hex digits following a percent-sign ‘%’ like %23 is the hex representation of hash/fragment symbol ‘#’.

**Hex Overflow** occurs when a malformed URL decoder is used while handling of URL & allows character over the hex limit of 0-F exceeding to the usage of other alphabets including the symbols too [ ] { } ; : < > ! & more.

The decoder used in my target was a lot confusing & didn’t make sense at all to be honest. I can guess they also used more than one logic behind the decoder. The output was all in small letters adding up to the confusion more.

**What do you expect when you input %5% ?**
The output to is ‘e’ or 0x55. Wondering how? The decoder takes the first 5, then decoded the second ‘%’ symbol to %25 & ignores the first nibble ‘2’ and takes the 5 from there. Making it %55. And as it was a overflown character, it does a **-1** from the first nibble of the result making it %45 a capital ‘e’. So %7% resulted in %65 or capital ‘e’. And yes, %8% , %6% resulted in %75 or small ‘u’ & %55 or capital ‘u’ respectively.

## Get SMHTahsin33’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

**Now you might be wondering how was it handling the alphabet parts of the hex?
** The answer is — pretty weirdly! In first stage it was handling **abcdef** normally but when overflowing it was calling the alphabets with a index number which started from ‘g’ as 0.

Upon more observation, I found out that it can be used as 2 different sets. And When Mixed, it is something like this.

If the any of the characters from two sets are used together a +1 can be seen to the first nibble, if it is from the set green, meaning a input of %5g which is %50 according to this chart will output ‘%(5+1)0’ or %60 → ` (Backtick). Again if it’s %hz (h is from the 2nd set) which is %13 according to the chart, it will output ‘%(1+2)3’ or %33 → ‘3’

The worst part to all of these is that the pattern is not always constant and full workflow couldn’t be calculated. Sometimes it did +1, for some it did +2 or +3 and for some also a subtraction to the first nibble. But this understanding was enough for my bypass.

## The Bypass

As in the beginning we saw that there were no ways this could possibly be bypassed as each and every handlers were blocked, we needed some other way around.

Using Hex Overflow — we can generate a single ASCII character using a whole lot of different ways. If you already understand, you can actually represent the **“=”** equal sign (**%3d**) also by ‘**%3=’** which can be explained like **%3%3d** where the first nibble gets ignored making it again **%3d**. Also ‘**%zd’,** ‘**%z=’,** ‘**%jd’,** ‘**%it’** (-1 from the first nibble in this case). We can use all of these in place of equal sign like **<svg onload%jdonload=alert()>**

It again blocked our payload, reason? This time **alert()** was the blocked function. This was easily bypassed by **optional chaining** → **alert?.()** .

It doesn’t just limit here, it can be bypassed using a lot of other ways generating different parts of payload using hex overflow like **%0d (CR)** to **‘%0=’ **or **‘%w=’** making the payload **<svg onload%w==alert()>**.

## Conclusion

This kind of flawed decoders are very rare to encounter and all might not be flawed the same way. Playing with this was really fun for me.

Follow Me 🔗:
[https://twitter.com/SMHTahsin33](https://twitter.com/SMHTahsin33)
[https://www.youtube.com/@SMHTahsin33](https://www.youtube.com/@SMHTahsin33/)
[https://www.facebook.com/smhtahsin33/](https://www.facebook.com/smhtahsin33/)

Thanks for Reading, hope you all enjoyed. And don’t forget to share. Bye until next time 👋

---
