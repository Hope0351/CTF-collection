# :globe_with_meridians: Art of onscrollend | Demonstrating XSS through scroll events with write-up

---

# Art of onscrollend | Demonstrating XSS through scroll events with write-up

*From Acunetix*

Hey, Its rAmpancist and I’m thrilled to have you join me for this post.

Through development of Web Application Firewalls recently, both internals and externals(CDN), its growing harder and harder to deliver a successful payload. However, its never impossible to find developers miss a sanitization or a pattern filter, leading to XSS. One of these misses can be underestimating the power of a certain tag, or a certain event, thus missing single or more patterns to filter.

This mostly happens with animation, audio and scroll events. Fortunately or not, a firm knowledge of HTML/CSS is essential to craft payloads properly around these events. This post however focuses on scroll events, as all events above deserve their own post, respectively…

## Enumeration phase

The subdomain I encountered was not really a sneaky, undercover one, but actually easily findable through Subfinder. The trick however lied in the fact that it required a really deep directory fuzzing, which led me to find a hidden directory with 200 response, which attempted to redirect me to SSO login page through manual form submission.

After attempting to get a reflection on each of those form values, I successfully reached reflection on parameter “page”.

Through the simplest attempt to break the context, I got the following reflection:

```
<input type="hidden" name="RelayState" value="[REDACTED]?page=">"/>
```

Our job however is not even close to over.

## Narrow fuzzing phase

The occurrence above leaves us with 2 possibilities:

- Do I want to perform my payload inside the INPUT tag?

- Or do I want to break the tag, and seek possibilities through other tags?

Of course the lazier approach is to try injecting attributes into INPUT.

Now before I demonstrate the first fuzzing phase, I want to draw your attention to the fact that `type=”hidden”` is set.

### What is type=”hidden”?

Unlike what it might look like, Inputs have a huge variety of types, some which you might not expect of.

Some interesting types include:

`type="button"`Can cause Inputs to transform into buttons with values.

`type="color"` Causes a color picker to pop up.

`type="image"` Turns Input to an image entirely, letting you load images with `src` attribute.

Now, `type="hidden"` hides the Input, something similar to CSS style `display: none;` .

But why does it matter? The point is that HTML attributes are non-override-able. Many XSS vectors for in-attribute Inputs rely heavily on settingour own type.

For instance, this is a sample vector around `onload` or `onerror`:

`<input type=image src=1 onerror=alert(1)>`

`<input type=image src="validSource" onload=alert(1)>`

Notice how we need to set type=image before attempting to load from a `src`, and then triggering an `onload `or `onerror`. That’s because we need to turn our input into an image before being able to load from sources.

### What does non-override-able mean?

It precisely means that for instance if the developers define type before your injection point, their type takes priority over yours.

```
<input type="hidden" value="INJECTIONPOINT" type="image">"
```

In the example above `type=hidden` takes priority over `type=image`, disabling us to use the functionalities of an image. This also applies to all attributes in HTML, such as style and etc.

Now getting back to the main part, I fuzzed all the available events for Input.

*fuzzing result for events inside input*

The results were quite boring. I already lost access to `src` based events. Additionally, all other events are either unusable for Input, or they rely on animations which I’m unable to use for the following reason:

- Both `<style>` and `<script>` tags were strictly blocked, disabling us to perform absolutely any CSS or JS outside of tags.

2. Animations rely on a separate `<style>` tag. Example:

```
<style>@keyframes x{}</style><input style=”animation-name:x” onwebkitanimationend=”alert(1)”></input>
```

### Moving onto the next option, invoking a separate tag

Problems above leaves me with the single option of trying for other tags. Aiming to fuzz all combinations of tags and events, BurpSuite’s intruder comes extremely in hand.

When we have to iterate through tags and events, Cluster Bomb is the ideal option to perform this.

Our positions section is going to look like this:

```
/login.jsp?page=%22%3e§§%20§§%3d

">§§ §§=
```

*Cluster Bomb intruder mode with tags and events*

The results are quite interesting, there is a single vector not blocked in 7910 requests.

Keep in mind that the application is behind both Akamai + an internal WAF which manually dropped some vectors.

Understanding our probable path, we can proceed to Exploitation Phase.

## Exploitation Phase

Before we proceed, lets understand the nature of `<slot>`

### What is `<slot>` ?

From w3schools:

>

The <slot> tag is a placeholder …..

Content inside the tag will not be rendered.

The content can be made visible and rendered later by using JavaScript.

In other words, slot can contain anything, but has its `display` defaulted to `none`. Note that unlike what the piece of documentation said above, its also possible to make its content visible through CSS.

## Get rAmpancist’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Now understanding the tag, lets examine what `onscrollend` actually does.

### Onscrollend

The name might actually suggest that you have to scroll to the end of the document, but actually this event is similar to `onkeyup`. It triggers when any amount of scrolling finishes. `onscroll` listens for the initiation of event and `onscrollend` listens for its termination.

From Mozilla:

>

Scroll position updates include smooth or instant mouse wheel scrolling, keyboard scrolling, scroll-snap events, or other APIs and gestures which cause the scroll position to update.

To create payloads around onscrollend, Portswigger has some suggestions:

>

<xss onscrollend=alert(1) style=”display:block;overflow:auto;border:1px dashed;width:500px;height:100px;”><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><span id=x>test</span></xss>

This would’ve easily met my needs, but we have a little complicated situation here. We don’t have <br>. We don’t have <span>.

I believed the documentation is extremely poor from Portswigger. Since this payload doesn't directly work, and opening their demo page reveals whole new tips with slightly different payload.

*Demo page from [Portswiggerlabs](https://portswigger-labs.net)*

First thing is they are using Bootstrap, which automatically provides tags like `<h1>` and `<span>` with predefined styles. That becomes extremely confusing when you want to craft your own payload, and that’s when you have to recreate all the predefined Bootstrap styles for your tags specifically.

Other thing is that their demo pages has its link supplied with tricky `#x` which is the whole point of payload and had me confused for hours, since I couldn’t find it on the main page.

This is the final payload in their demo page:

```
https://portswigger-labs.net/xss/xss.php?context=html&x=%3Cxss%20onscrollend%3Dalert(1)%20style%3D%22display%3Ablock%3Boverflow%3Aauto%3Bborder%3A1px%20dashed%3Bwidth%3A500px%3Bheight%3A100px%3B%22%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cbr%3E%3Cspan%20id%3Dx%3Etest%3C%2Fspan%3E%3C%2Fxss%3E#x
```

Now lets focus on our goal and recreate the payload for `<slot>`.

### What do we aim for?

In simple words, we want to create a scroll-able element, and trigger the scroll completely through HTML and with no JS involved.

First we have our parent tag, which is `<slot>`. We realized that slot is a placeholder tag and hidden by default. So we supply it with `display: block;` . PS style attribute is allowed for slot tag. My assumption is that the whole slot pattern was missed.

### What is display?

The `display` property specifies the display behavior of an element. Most important values are `inline`, `none`, `block`. All tags are defaulted to `inline` .

Supplying with the style above, we got a normal behaving tag on our hands. Now we want to make our element scroll-able.

### What is overflow?

The `overflow` is a CSS property which specifies whether to clip the content or to add scrollbars when the content of an element is too big to fit in the specified area.

Most important values are `visible`, `scroll` and `auto`.

The default value for most tags is `visible`. `visible` prevents an element from getting scroll-able and causes the contents to fall out of context.

*visible, From [W3Schools](https://www.w3schools.com/css/css_overflow.asp)*

What we need is `auto` or `scroll`. scroll makes the element scroll-able whether or not its needed. `auto` makes it scroll-able only when needed. Designing tip: You can limit this property to x-axis or y-axis with `overflow-x` and `overflow-y.`

*auto, From [W3Schools](https://www.w3schools.com/css/css_overflow.asp)*

Now with my `<slot>` being scroll-able, we have to add appropriate contents to be able to scroll. There is many options to create contents too big for y-axis so it falls out of context. One is creating texts with huge font size or too many characters, or using `<br>` which creates lines breaks. The other option is making our element’s height lesser to create more convenient payloads.

This is a schematic of what we ultimately need:

*Final goal*

The `<br>` tag is blocked, and too many characters is bad idea for a payload for many reasons. We’ll proceed with big font size.

This is how our payload look like until now:

```
<slot style="display: block;overflow: auto;box-sizing: border-box;text-align: left;line-height: 1.2;font-weight: 500;font-size: 1rem;border: 1px dashed;width: 500px;height: 100px;"><slot style="font-size: 10rem;display:block">FIRST CONTENT</slot><slot style="font-size: 10rem;display:block">SECOND CONTENT</slot></slot>
```

We created 2 texts in `<slot>` with a font size too big for the element size.

Let’s get to the tricky part.

### Anchoring

When the page loads, we are at the top of the box seeing FIRST CONTENT. We want to traverse to the second part without user’s interaction and that’s when we need anchoring.

As many of you might already know, the part after `#` is called the hash fragment part which helps users traverse to a certain section of a crowded page and ignore the frustrating scrolling part.

The receiver of that call is the `id` attribute.

```
<slot style="display:block;" id=comehere>SECOND CONTENT</slot>
```

If you put this in your page and add `#comehere` to the end of URL, you’ll be guided directly to SECOND CONTENT. That’s when the scrolling event is called without your knowledge.

*How page looks after #comehere*

How our payload looks after making the `id`:

```
<slot style="display: block;overflow: auto;box-sizing: border-box;text-align: left;line-height: 1.2;font-weight: 500;font-size: 1rem;border: 1px dashed;width: 500px;height: 100px;"><slot style="font-size: 10rem;display:block">FIRST CONTENT</slot><slot style="font-size: 10rem;display:block" id=comehere>SECOND CONTENT</slot></slot>
```

### Final touch

All that remains is assigning the `onscrollend` with a proper PoC. Fuzzing all the possible options, we face the fact that all critical methods are banned. However, `setInterval` is always a convenient way to bypass all of that.

```
setInterval('ale'+'rt(docum'+'ent.c'+'ookie)')
```

Final payload:

```
"><slot style="display: block;overflow: auto;box-sizing: border-box;text-align: left;line-height: 1.2;font-weight: 500;font-size: 1rem;border: 1px dashed;width: 500px;height: 100px;" onscrollend="setInterval('ale'+'rt(docum'+'ent.c'+'ookie)')"><slot style="font-size: 10rem;display:block">FIRST CONTENT</slot><slot style="font-size: 10rem;display:block" id=comehere>SECOND CONTENT</slot></slot>#comehere
```

*Report status*

It’s always necessary to have an understanding around the payload, so we can easily customize and tweak to our own liking. Since I found that the documentation is not great for this situation, I decided to make my own post.

While thanking you for sticking with me to the end of this article, I’d appreciate if you like and share it.

My twitter: [https://twitter.com/rampancist](https://twitter.com/rampancist)

---
