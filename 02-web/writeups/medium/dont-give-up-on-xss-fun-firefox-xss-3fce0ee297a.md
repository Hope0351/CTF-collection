# :globe_with_meridians: Don’t Give Up On XSS! | Fun Firefox XSS

---

# Don’t Give Up On XSS! | Fun Firefox XSS

## There’s always a way to exploit xss in different contexts

## Story

I got an invite from a private program on hackerone and started searching for some vulnerabilites. After a while of searching, i found an url that had some interesting parameters. One of my inputs were reflecting inside of an *hidden *inputtag.

```
<input type="hidden" name="SourceName" id="SourceName" value="hey">
```

So i tried to espace the value attribute by adding a quote, and i was able escape it succesfully. Now the catch is, after i escaped the attribute; i tried to close the input tag and open up another tag, but the app was giving error 500 when i entered < > characters. So i tried to execute xss inside of another attribute. I thought `" onfocus="alert(1)" autofocus="` would do the job, but i was wrong. Even if i was able to succesfully inject the attribute; it wasn’t firing.

```
<input type="hidden" name="SourceName" id="SourceName" value="hey" onfocus="alert(1)" autofocus="">
```

## Exploitation

So after i made a quick googling, i learned that because the input type is *hidden* it would never gain the focus and therefore the onfocus handler would never fire.

## Get Fırat’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So i started searching for an alternate solution, at this point; i was looking this as an xss challenge, i had to solve this. After searching for a while i came across an article published on [portswigger.net](https://portswigger.net/research/xss-in-hidden-input-fields)

So, to summarize the article: onclick events could be called on the hidden input when it activated via acces keys but only in firefox. So, after learning this my final payload was this:

```
<input type="hidden" accesskey="X" onclick="alert(1)">
```

With this payload, the user has to press ALT+SHIFT+X on his keyboard for this to fire. As i said earlier, this was like a challenge for me; as a result i learned a lot of new things. I would still be happy if this bug wasn’t accepted, since it needs a lot of user interaction.

---
