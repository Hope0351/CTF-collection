# :globe_with_meridians: How I found Reflected XSS on a WebGIS

---

# How I found Reflected XSS on a WebGIS

## Note: The vulnerability was reported and has been fixed.

Hi everyone,

In this write-up, I will share how I found a Reflected XSS vulnerability on a website that uses Geographic Information System (WebGIS).

While surfing the newsfeed on Facebook, I saw a new post from a fan page that introduced a new WebGIS that had just launched at:

`[https://mevietnamanhhung.hcmgis.vn](https://mevietnamanhhung.hcmgis.vn)`

*The post about a WebGIS that I saw on Facebook*

With a little curiosity, I decided to visit the website. The homepage looks like this:

*Homepage*

I didn’t gather much information there so I switched to the Artwork page:

*The Artwork page*

Here, the website displays several portraits belonging to brief stories of Vietnamese Heroic Mothers (VHM). Notice that on the top of this page, there is a search bar that allows searching by name of VHM.

I didn’t input anything and just clicked on the Search button. Now the URL appears many parameter—value pairs as follows:

```
[https://mevietnamanhhung.hcmgis.vn/cms/tac-pham?page=1&name=&province=&district=&from=01/01/2010&to=30/11/2020&storage=&on=&sort=lastest](https://mevietnamanhhung.hcmgis.vn/cms/tac-pham?page=1&name=&province=&district=&from=01%2F01%2F2010&to=30%2F11%2F2020&storage=&on=&sort=lastest)
```

After viewing the page source, I realized that there is a piece of javascript code that needs attention, including parameter — value pairs in a function, which are placed directly in the URL then sent the request to the server through the GET method:

From my experience, this could be a Reflected XSS vulnerability. Since this code is already in a `<script>` tag, I just need to escape from string -> object -> function to insert malicious code.

I used this payload to input in the search bar:

```
a'}}})});alert('Tri ân Mẹ Việt Nam Anh hùng');$(function(){var a = new Vue({b:{c:{d:'e
```

And the result was:

*Reflected XSS!*

I immediately reported this vulnerability to the web admin of the HCM Geographic Information System (HCMGIS). After 3 days, I received a thank you email from the Head of Technology Development Department, HCMGIS Center, Ho Chi Minh Department of Science and Technology, confirming that the bug has been fixed.

*The thank-you email confirmed that the bug has been fixed*

After a week, I went back to the website to check whether the XSS vulnerability I reported before had been fixed.

## Get KhanhCM’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

However, after taking a deeper look at the URL as well as the source code above, beside the `name` parameter, it is likely that the XSS vulnerability also occurs at the `page` parameter.

Since the admin has fixed the XSS vulnerability by filtering the `'` character, I will bypass this filter by using the following payload to set value for the `page` parameter:

```
5}}})});alert(String.fromCharCode(88,83,83));$(function(){var a = new Vue({b:{c:{d:5
```

Now the URL became:

```
[https://mevietnamanhhung.hcmgis.vn/cms/tac-pham?page=5}}})});alert(String.fromCharCode(88,83,83));$(function(){var%20a%20=%20new%20Vue({b:{c:{d:5name=&province=&district=&from=01/01/2010&to=30/11/2020&storage=&on=&sort=lastest](https://mevietnamanhhung.hcmgis.vn/cms/tac-pham?page=5%7D%7D%7D%29%7D%29%3Balert%28String.fromCharCode%2888%2C83%2C83%29%29%3B%24%28function%28%29%7Bvar+a+%3D+new+Vue%28%7Bb%3A%7Bc%3A%7Bd%3A5name%3D&province=&district=&from=01%2F01%2F2010&to=30%2F11%2F2020&storage=&on=&sort=lastest)
```

And the result was:

*Reflected XSS!*

It’s time to report this to HCMGIS. After two weeks, I received the second thank-you email, confirming that the bug has been fixed.

*The thank-you email confirmed that the bug has been fixed*

## Sharing time

About a month and a half after reporting the second XSS vulnerability to HCMGIS, I started to write this write-up. However, at that time, the website was no longer accessible, and only displayed the error as shown below:

*Error message when accessing the website at [https://mevietnamanhhung.hcmgis.vn](https://mevietnamanhhung.hcmgis.vn)*

To make the write-up more intuitive, I used the Wayback Machine to find the snapshot of this website. Fortunately, there is a snapshot saved at the following address:

```
[https://mevietnamanhhung.hcmgis.vn/cms/tac-pham](https://web.archive.org/web/20201031194708/https://mevietnamanhhung.hcmgis.vn/cms/tac-pham)
```

## Update on 28/12/2020:

The Vietnamese Heroic Mother website is now accessible at the new address: `[https://chandungme.vn](https://chandungme.vn)`

## Timeline

- 01/11/2020: first reported to HCMGIS Center.

- 03/11/2020: the web admin confirmed the vulnerability has been fixed.

- 10/11/2020: second reported to HCMGIS Center.

- 23/11/2020: the web admin confirmed the vulnerability has been fixed.

Thank you for taking the time to read this write-up! Give me a Clap if you like it! 👏

Cheers!

---
