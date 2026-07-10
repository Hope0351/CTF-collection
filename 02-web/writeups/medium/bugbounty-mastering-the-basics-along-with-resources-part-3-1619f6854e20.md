# :globe_with_meridians: BugBounty — Mastering the Basics (along with Resources)[Part-3]

---

# BugBounty — Mastering the Basics (along with Resources)[Part-3]

Bug Bounty Hunting is a career that is known for the heavy use of security tools. These tools help to find vulnerabilities in software, web, and mobile applications and are an integral part of bounty hunting. Below is a list of security tools which should be leveraged by bug bounty hunters.

### Bug Bounty Tools & Scripts: Your Arsenal for Successful Hunting

Tools you should definitely know about:

- BurpSuite: Burp Suite is a software security application used for penetration testing of web applications.

- ZAP: OWASP ZAP is an open-source web application security scanner.

- Caido: A lightweight web security auditing toolkit.

Below is an awesome list to know more about the Bug Bounty Tools.

### Recon

### Subdomain Enumeration

Fast subdomains enumeration tool for penetration testers

In-depth Attack Surface Mapping and Asset Discovery

A high-performance DNS stub resolver for bulk lookups and reconnaissance (subdomain enumeration)

The fastest and cross-platform subdomain enumerator, do not waste your time.

Sudomy is a subdomain enumeration tool to collect subdomains and analyzing domains performing automated reconnaissance (recon) for bug hunting / pentesting.

Go client to communicate with Chaos DNS API.

Multi Tool Subdomain Enumeration

- Bugcrowd levelup subdomain enumeration

This repository contains all the material from the talk “Esoteric sub-domain enumeration techniques” given at Bugcrowd LevelUp 2017 virtual conference

shuffleDNS is a wrapper around massdns written in go that allows you to enumerate valid subdomains using active bruteforce as well as resolve subdomains with wildcard handling and easy input-output…

Perform subdomain enumeration using the certificate transparency logs from Censys.

Subdomain enumeration tool with analysis features for discovered domains

A script to extract subdomains/emails for a given domain using SSL/TLS certificate dataset on Censys

Fast subdomains enumeration tool for penetration testers.

Another Subdomain Enumeration Tool

A Web-UI for subdomain enumeration (subfinder)

Passive reconnaissance/enumeration of interesting targets by watching for SSL certificates being issued

enumall.py Setup script for Regon-ng

Generates permutations, alterations and mutations of subdomains and then resolves them

An automation framework for running multiple open-sourced subdomain bruteforcing tools (in parallel) using your own wordlists via Docker Compose

This is a parallelised domain name prober to find as many subdomains of a given domain as fast as possible.

Dnscan is a python wordlist-based DNS subdomain scanner.

Knockpy is a python tool designed to enumerate subdomains on a target domain through a wordlist.

Small, fast tool for performing reverse DNS lookups en masse.

Dnsx is a fast and multi-purpose DNS toolkit allow to run multiple DNS queries of your choice with a list of user-supplied resolvers.

Subfinder is a subdomain discovery tool that discovers valid subdomains for websites.

Find domains and subdomains related to a given domain

Yet another subdomain finder

A virtual host scanner that performs reverse lookups

Information Gathering tool — DNS / Subdomains / Ports / Directories enumeration

A research-grade suite of tools for subdomain enumeration, intelligence gathering and attack surface mapping.

Scrape domain names from SSL certificates of arbitrary hosts

### Port Scanning

TCP port scanner, spews SYN packets asynchronously, scanning entire Internet in under 5 minutes.

The Modern Port Scanner

A fast port scanner written in go with focus on reliability and simplicity.

The Network Mapper. Github mirror of official SVN repository.

Nmap on steroids. Simple CLI with the ability to run pure Nmap engine, 31 modules with 459 scan profiles.

Combines the speed of masscan with the reliability and detailed enumeration of nmap.

### Screenshots

EyeWitness is designed to take screenshots of websites, provide some server header info, and identify default credentials if possible.

Make website screenshots and mobile emulations from the command line.

A golang, web screenshot utility using Chrome Headless

Web Inventory tool takes screenshots of webpages using Pyppeteer (headless Chrome/Chromium) and provides some extra bells & whistles to make life easier.

Convolutional neural network for analyzing pentest screenshots

A tool for collecting RDP, web and VNC screenshots all in one place

Recovers passwords from pixelized screenshots

HTTPScreenshot is a tool for grabbing screenshots and HTML of large numbers of websites.

### Technologies

Identify technology on websites.

Port of Wappalyzer (uncovers technologies used on websites) to automate mass scanning.

BuiltWith API client

Next-generation web scanner

Scanner detecting the use of JavaScript libraries with known vulnerabilities

Httpx is a fast and multi-purpose HTTP toolkit that allows to run multiple probers using a retryable http library, it is designed to maintain the result reliability with increased threads.

Fingerprintx is a standalone utility for service discovery on open ports that works well with other popular bug bounty command line tools.

### Content Discovery

Directory/File, DNS and VHost busting tool written in Go

Rapid content discovery tool for recursively querying webservers, handy in pentesting and web application assessments

A fast, simple, recursive content discovery tool written in Rust.

Web path scanner

A Go implementation of dirsearch.

An extremely fast and flexible web fuzzer

Modern alternative to dirbuster/dirb

Dirbuster-ng is C CLI implementation of the Java dirbuster tool

Gospider — Fast web spider written in Go

Simple, fast web crawler designed for easy, quick discovery of endpoints and assets within a web application

Fast, feature-rich unix-way web scraper/crawler written in Golang.

### Links

A python script that finds endpoints in JavaScript files

A js scanner, built in php designed to scrape urls and other info

Extract (links/possible endpoints) from responses & filter them via decoding/sorting

A fast and minimal JS endpoint extractor

Burp Extension for a passive scanning JS files for endpoint links.

A golang utility to spider through a website searching for additional links.

Fetch all the URLs that the Wayback Machine knows about for a domain

Fetch known URLs from AlienVault’s Open Threat Exchange, the Wayback Machine, and Common Crawl.

Reveals invisible links within JavaScript files

### Parameters

This tool can be used to brute discover GET and POST parameters.

This extension identifies hidden, unlinked parameters. It’s particularly useful for finding web cache poisoning vulnerabilities.

This tool for brute discover GET and POST parameters.

HTTP parameter discovery suite.

Mining parameters from dark corners of Web Archives.

Hidden parameters discovery suite written in Rust.

### Fuzzing

Web application fuzzer

Fast web fuzzer written in Go

Dictionary of attack patterns and primitives for black-box application fault injection and resource discovery.

A collection of Burpsuite Intruder payloads, BurpBounty payloads, fuzz lists, malicious file uploads, web pentesting methodologies, and checklists.

Potentially dangerous files

A JavaScript Engine Fuzzer

Fuzzapi is a tool used for REST API pentesting and uses API_Fuzzer gem

Qsfuzz (Query String Fuzz) allows you to build your own rules to fuzz query strings and easily identify vulnerabilities.

A very advanced (web) fuzzer written in Nim.

### Cloud Security Tools

- SkyArk — Privilege Escalation and Data Collection for AWS

- Pacu — AWS Exploitation Framework

- AWS Exploitation Framework — RhinoSecurityLabs

### Exploitation

List of tools that will be helpful during exploitation.

### Command Injection

Automated All-in-One OS command injection and exploitation tool.

### CORS Misconfiguration

CORS Misconfiguration Scanner

A simple CORS misconfiguration scanner

A multi-threaded scanner that helps identify CORS flaws/misconfigurations

Cross-Origin Resource Sharing MisConfiguration Scanner

### CRLF Injection

A fast tool specially designed to scan CRLF injection

A fast tool to scan CRLF vulnerability written in Go

Command line tool for testing CRLF injection on a list of domains.

CRLF and open redirect fuzzer.

### CSRF Injection

The Prime Cross-Site Request Forgery (CSRF) Audit and Exploitation Toolkit.

### Directory Traversal

The Directory Traversal Fuzzer

File Inclusion & Directory Traversal fuzzing, enumeration & exploitation tool.

Burp extension to detect alias traversal via NGINX misconfiguration at scale.

Tired of manually adding dot-dot-slash to your possible path traversal? this short snippet will increment ../ on the URL.

### File Inclusion

Local file inclusion exploitation tool

Fuzzing for LFI using Burpsuite

Scripts to execute enumeration via LFI

Totally Automatic LFI Exploiter (+ Reverse Shell) and Scanner

Wordlist to bruteforce for LFI

### GraphQL Injection

InQL — A Burp Extension for GraphQL Security Testing

GraphQLmap is a scripting engine to interact with a GraphQL endpoint for pentesting purposes.

GraphQL security testing tool

Burp Suite extension to help make Graphql request more readable

Obtain GraphQL API schema despite disabled introspection!

### Header Injection

Customisable and automated HTTP header injection.

### Insecure Deserialization

A proof-of-concept tool for generating payloads that exploit unsafe Java object deserialization.

Probe endpoints consuming Java serialized objects to identify classes, libraries, and library versions on remote Java classpaths.

Deserialization payload generator for a variety of .NET formatters

PHPGGC is a library of PHP unserialize() payloads along with a tool to generate them, from command line or programmatically.

### Insecure Direct Object References

Automatic authorization enforcement detection extension for burp suite written in Jython developed by Barak Tawily

### Open Redirect

Open Redirection Analyzer

CRLF and open redirect fuzzer

Small script to check a list of domains against open redirect vulnerability

A Fuzzer for OpenRedirect issues

### Race Condition

A Kernel fuzzer focusing on race bugs

Race Condition framework

Small Python library that makes it easy to exploit race conditions in web apps with Requests.

Turbo Intruder is a Burp Suite extension for sending large numbers of HTTP requests and analyzing the results.

Tests for race conditions in web applications. Includes a RESTful API to integrate into a continuous integration pipeline.

### Request Smuggling

HTTP Request Smuggling Detection Tool

Smuggler — An HTTP Request Smuggling / Desync testing tool written in Python 3

HTTP Request Smuggling over HTTP/2 Cleartext (h2c)

These scripts I use to create Request Smuggling Desync payloads for CLTE and TECL style attacks.

### Server Side Request Forgery

Automatic SSRF fuzzer and exploitation tool

This tool generates gopher link for exploiting SSRF and gaining RCE in various servers

A collection of scripts that run on my web server. Mainly for debugging SSRF, blind XSS, and XXE vulnerabilities.

An automated SSRF finder. Just give the domain name and your server and chill! 😉 Also has options to find XSS and open redirects

Automatic tool for DNS rebinding-based SSRF attacks

A simple SSRF-testing sheriff written in Go

Toolkit to detect and keep track on Blind XSS, XXE & SSRF

Smart ssrf scanner using different methods like parameter brute forcing in post and get…

Fetch known URLs from AlienVault’s Open Threat Exchange, the Wayback Machine, and Common Crawl and Filter Urls With OpenRedirection or SSRF Parameters.

Server-side request forgery detector

Authenticated SSRF in Grafana

Tool to searching sentry config on page or in javascript files and check blind SSRF

Bruteforcing on Hidden parameters to find SSRF vulnerability using GET and POST Methods

A DNS rebinding attack framework.

A “malicious” DNS server for executing DNS Rebinding attacks on the fly (public instance running on rebind.network:53)

A front-end JavaScript toolkit for creating DNS rebinding attacks.

DNS Rebinding Exploitation Framework

Simple DNS Rebinding Service

Automatic tool for DNS rebinding-based SSRF attacks

DNS rebinding toolkit

### SQL Injection

Automatic SQL injection and database takeover tool

Automated NoSQL database enumeration and web application exploitation tool.

Automatic SQL injection with Charles and SQLmap API

Python3 Burp History parsing tool to discover potential SQL injection points. To be used in tandem with SQLmap.

MS SQL proxy is a toolkit aimed to perform lateral movement in restricted environments through a compromised Microsoft SQL Server via socket reuse

SQLI Hunter is a simple HTTP / HTTPS proxy server and a SQLMAP API wrapper that makes digging SQLi easy.

Gather urls from wayback machine then test each GET parameter for sql injection.

Evil SQL Client (ESC) is an interactive .NET SQL console client with enhanced SQL Server discovery, access, and data exfiltration features.

SQL injection script for MSSQL that extracts domain users from an Active Directory environment based on RID bruteforcing

Messy BurpSuite plugin for SQL Truncation vulnerabilities.

Blind SQL Injection Tool with Golang

A python library to automate time-based blind SQL injection

Massive SQL injection vulnerability scanner

NoSql Injection CLI tool, for finding vulnerable websites using MongoDB.

### XSS Injection

Most advanced XSS scanner.

XSS’OR — Hack with JavaScript.

XSS spider — 66/66 wavsep XSS detected

Sleepy Puppy XSS Payload Management Framework

ezXSS is an easy way for penetration testers and bug bounty hunters to test (blind) Cross Site Scripting.

The XSS Hunter service — a portable version of XSSHunter.com

DalFox(Finder Of XSS) / Parameter Analysis and XSS Scanning tool based on golang

Cross Site “Scripter” (aka XSSer) is an automatic -framework- to detect, exploit and report XSS vulnerabilities in web-based applications.

Powerfull XSS Scanning and Parameter analysis tool&gem

XSS payloads designed to turn alert(1) into P1

A tool designed to assist with finding all sinks and sources of a web application and display these results in a digestible manner.

A collection of scripts that run on my web server. Mainly for debugging SSRF, blind XSS, and XXE vulnerabilities.

This burp intruder extender is designed for automation and validation of XSS vulnerabilities.

An interactive multi-user web JS shell

bXSS is a utility which can be used by bug hunters and organizations to identify Blind Cross-Site Scripting.

Utility to embed XXE and XSS payloads in docx,odt,pptx,etc (OXML_XEE on steroids)

XSS Radar is a tool that detects parameters and fuzzes them for cross-site scripting vulnerabilities.

BruteXSS is a tool written in python simply to find XSS vulnerabilities in web application.

A fast DOM based XSS vulnerability scanner with simplicity.

DOM XSS scanner for Single Page Applications

Automated blind-xss search for Burp Suite

Toolkit to detect and keep track on Blind XSS, XXE & SSRF

DOMXSS Scanner is an online tool to scan source code for DOM based XSS vulnerabilities

Correlated injection proxy tool for XSS Hunter

A better version of my xssfinder tool — scans for different types of XSS on a list of URLs.

XSSCon: Simple XSS Scanner tool

Maintaining account persistence via XSS and Oauth

Shadow Workers is a free and open source C2 and proxy designed for penetration testers to help in the exploitation of XSS and malicious Service Workers (SW)

This is a burp plugin that extracts keywords from response using regexes and test for reflected XSS on the target scope.

Detect, manage and exploit Blind Cross-site scripting (XSS) vulnerabilities.

Chrome extension that finds DOM based XSS vulnerabilities

PNG IDAT chunks XSS payload generator

A simple Swagger-ui scanner that can detect old versions vulnerable to various XSS attacks

### XXE Injection

A collection of scripts that run on my web server. Mainly for debugging SSRF, blind XSS, and XXE vulnerabilities.

List DTDs and generate XXE payloads using those local DTDs.

Uility to embed XXE and XSS payloads in docx,odt,pptx,etc (OXML_XEE on steroids)

A mini webserver with FTP support for XXE payloads

Tool to help exploit XXE vulnerabilities

Toolkit to detect and keep track on Blind XSS, XXE & SSRF

Tool for automatic exploitation of XXE vulnerability using direct and different out of band methods.

A tool for embedding XXE/XML exploits into different filetypes

A bash script that automates the scanning of a target network for HTTP resources through XXE

---
