# :globe_with_meridians: Medium

---

# Write-up: DOM XSS in document.write sink using source location.search @ PortSwigger Academy

This write-up for the lab *DOM XSS in document.write sink using source location.search* is part of my walkthrough series for [PortSwigger’s Web Security Academy](https://portswigger.net/web-security).

**Learning path**: Client-side topics → Cross-site scripting

Python script: [script.py](https://github.com/frank-leitner/portswigger-websecurity-academy/blob/main/11_cross_site_scripting_XSS/DOM_XSS_in_document.write_sink_using_source_location.search/script.py)

## Lab description

## Steps

The lab application is a blog website with search functionality. After performing a search, the search term is included on the result page.

## Get Frank Leitner’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

A simple XSS attempt fails:

Looking at the page source, the search term displayed is properly encoded. However, it also shows that a javascript takes the search term out of the URL and writes it into an img-tag for some type of tracking:

Using the browser tools, I can inspect the resulting HTML. It is visible that my search term is embedded without any apparent safeguards:

Of course, the script tags are within a string here, so they are harmless. However, if I can terminate the string by injecting double quotes, then I can manipulate the resulting HTML freely.

---
