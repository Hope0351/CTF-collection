# :globe_with_meridians: Write-up: DOM XSS in innerHTML sink using source location.search @ PortSwigger Academy

> **Original Source:** [Write-up: DOM XSS in innerHTML sink using source location.search @ PortSwigger Academy](https://infosecwriteups.com/write-up-dom-xss-in-innerhtml-sink-using-source-location-search-portswigger-academy-94c6691f89b0)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Write-up: DOM XSS in innerHTML sink using source location.search @ PortSwigger Academy


This write-up for the lab *DOM XSS in innerHTML sink using source location.search* is part of my walkthrough series for [PortSwigger’s Web Security Academy](https://portswigger.net/web-security).


**Learning path**: Client-side topics → Cross-site scripting


Python script: [script.py](https://github.com/frank-leitner/portswigger-websecurity-academy/blob/main/11_cross_site_scripting_XSS/DOM_XSS_in_innerHTML_sink_using_source_location.search/script.py)

## Lab description


## Steps


The lab application is a blog website with search functionality. The search term is included on the result page.


## Get Frank Leitner’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


This is not performed on the server side, but by using client-side JavaScript:


If the `search` argument is provided, the `innerHTML` of a `span`-element is changed dynamically. Inserting JavaScript by using `foo<img src="xxx" onerror=alert(document.domain)>` as search parameter results in this HTML:


During the rendering of the page, the image fails to load. This in turn will raise the JavaScript `alert` box confirming the XSS vulnerability and updates the lab to

---

*Originally published on [Medium](https://infosecwriteups.com/write-up-dom-xss-in-innerhtml-sink-using-source-location-search-portswigger-academy-94c6691f89b0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
