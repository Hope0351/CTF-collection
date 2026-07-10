# :globe_with_meridians: How to Find XSS Vulnerabilities in 2 Minutes

> **Original Source:** [How to Find XSS Vulnerabilities in 2 Minutes](https://infosecwriteups.com/find-xss-vulnerabilities-in-just-2-minutes-d14b63d000b1)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How to Find XSS Vulnerabilities in 2 Minutes


## My simple yet powerful technique for spotting XSS vulnerabilities during bug hunting.


## Introduction


Hi everyone! Today, I’m going to show you a fast and efficient way to spot Cross-Site Scripting (XSS) vulnerabilities on any website. This method is designed to save you time and effort by using a powerful one-line command that runs several popular tools in sequence. By automating both the discovery and initial filtering steps, it helps you quickly pinpoint possible XSS points without manually checking every URL, making your testing workflow much faster and more streamlined.

## Phase 1: Initial URL Discovery and Filtering


The first step is to gather all URLs for the target domain and filter out reflected and unfiltered special characters parameters using a single one-liner command that combines multiple tools.


```
echo example.com | gau | gf xss | uro | Gxss | kxss | tee xss_output.txt
```


### But before we go any further let me explain these commands step by step:


- GAU: fetches old URLs from passive sources like WaybackURLs, AlienVault, Common Crawl and URLscan.

---

*Originally published on [Medium](https://infosecwriteups.com/find-xss-vulnerabilities-in-just-2-minutes-d14b63d000b1). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
