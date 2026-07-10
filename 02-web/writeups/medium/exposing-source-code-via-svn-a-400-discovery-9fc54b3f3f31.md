# :globe_with_meridians: Exposing Database Creds via SVN: A $400 Discovery

> **Original Source:** [Exposing Database Creds via SVN: A $400 Discovery](https://infosecwriteups.com/exposing-source-code-via-svn-a-400-discovery-9fc54b3f3f31)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Exposing Database Creds via SVN: A $400 Discovery


*Photo by [Markus Spiske](https://unsplash.com/@markusspiske?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*


In this write-up, I will share how I uncovered a source code disclosure vulnerability through an exposed SVN (Subversion) repository. This subtle yet impactful issue led to significant risks, including the exposure of database credentials.

## How I Found the Vulnerability


Here are some simple ways to find this vulnerability:


Method 1: Using Nuclei Templates

>

nuclei -t nuclei-templates/http/exposures/files/svn-wc-db.yaml -l <subdomain_list>


Method 2: Wordlist Brute Force

>

Adding .svn/wc.db to the wordlist and using dirsearch/ffuf


Method 3: Custom Dot Git Extension [The Method I Used]

>

Using Dot Git extension, need to change the configuration as it does not come with .svn detection.


This approach involves tweaking the Dot Git extension to detect `.svn` directories since it doesn’t do this by default.

## Exploiting the Vulnerability


After spotting the exposed SVN directory, I followed these steps to dig deeper and uncover the source code and the database credentials:


Step 1: Downloading the `wc.db` File


First, I checked if the `wc.db` file was publicly accessible. I used a simple command to download it:

>

wget [https://redacted.com/.svn/wc.db](https://redacted.com/.svn/wc.db)


This showed that the file was indeed exposed and could be downloaded by anyone.


## Get Vipul Sahu’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Step 2: Extracting Source Code Paths


With the `wc.db` file in hand, I ran an SQLite query to pull out the paths to the source code files stored in the repository:

>

sqlite3 wc.db ‘select local_relpath, “.svn/pristine/” || substr(checksum,7,2) || “/” || substr(checksum,7) || “.svn-base” as alpha from NODES;’ | tee Snv_Database


This query listed all the paths of the source code files in the repository, making it easier to find and access them.


Step 3: Creating URLs for the Source Code Files


Next, I generated URLs that pointed directly to these source code files:

>

cat Snv_database.txt | cut -d”|” -f2 | sort -u | sed “s/^/https:\/\/redacted.com\//” | tee Urls_generated.txt


This gave me a list of URLs that I could use to access and download the source code files.


Step 4: Downloading the Source Code and Credentials


Finally, using the URLs I generated, I could download the source code files:

>

wget — input-file=Urls_generated.txt -P Source_code


I found database credentials among these files, which could have been exploited to gain unauthorized access to the application’s database.

## Impact of the Vulnerability


The exposure of source code and database credentials can lead to serious consequences. With the database credentials in hand, attackers could gain unauthorized access to sensitive data, potentially leading to significant security breaches. Additionally, the exposed source code could be stolen, allowing competitors or malicious actors to exploit the company’s intellectual property, which could result in a loss of competitive advantage.

## Conclusion


This experience shows how important it is to secure version control systems like SVN. Even a minor oversight, like leaving a `wc.db` file exposed, can lead to significant risks. Through responsible disclosure, I was able to help the company fix the issue quickly and was rewarded with a $400 bounty.

---

*Originally published on [Medium](https://infosecwriteups.com/exposing-source-code-via-svn-a-400-discovery-9fc54b3f3f31). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
