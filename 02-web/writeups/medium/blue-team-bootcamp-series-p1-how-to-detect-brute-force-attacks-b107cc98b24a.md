# :globe_with_meridians: Blue Team Bootcamp Series (P1): How to Detect Brute Force Attacks

> **Original Source:** [Blue Team Bootcamp Series (P1): How to Detect Brute Force Attacks](https://infosecwriteups.com/blue-team-bootcamp-series-p1-how-to-detect-brute-force-attacks-b107cc98b24a)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Blue Team Bootcamp Series (P1): How to Detect Brute Force Attacks


In this series — Blue Team Bootcamp, we’re going to learn about tactics, techniques and methodology that Blue Teamers in Cybersecurity Must know & also the scenarios they face in their career.


>

*Note: This series is not limited to Blue Teamers. Red Team can also benefit from this to understand the mindset that blue teamers use
As Sun Tzu said in the art of war that “If you know the enemy and know yourself, you need not fear the result of a hundred battles..”Now, Let’s begin with the first part of this series.*

## Introduction to Detecting Brute Force Attacks


Brute force attacks are a frequently preferred attack technique by attackers as they provide direct access to the system if successful. It is extremely important to be able to detect this attack technique and take the necessary precautions.

## Brute Force Attacks


A brute force attack is a name given to the activity performed to find any username, password, or directory on the web page or an encryption key by trial and error method.


We can explain brute-force attacks into two categories.


- Online Brute force attacks
In online brute force attacks, the attacker and the victim are online at the same time and contact each other directly for example attacker brute forces target SSH login credentials.

- Offline Brute force attacks
Offline brute-force attacks are used for previously captured encrypted or hashed data. In this type of attack, the attacker does not need to establish an active connection directly with the victim’s machine. An attacker can perform an offline attack on the password file that he/she somehow gained access to via sniffing, MiTM, dumping hashes from SAM, etc.

## Protocol/Services That Can Be Attacked by Brute Force


Brute force attacks are mostly encountered in the following areas.
Web application login pages
RDP services
SSH services
Database services
Web application home directories
DNS servers

## SSH Brute Force Attack Detection Example


In an example SSH brute force analysis, when we view a Linux machine log with the contents of the “/var/log/auth.log.1” file and failed login attempts, we can see who the failed login attempts belong to.


cat auth.log.1 | grep “Failed password” | cut -d “ ” -f10 | sort | uniq -c | sort
(Only display all the users that fail to authenticate)


A command such as the one below can be used to locate the IP addresses that made these attempts.
cat auth.log.1 | grep “Failed password” | cut -d “ ” -f12 | sort | uniq -c | sort


Users who successfully log in can also be detected with the following command.
cat auth.log.1 | grep “Accepted password”


As can be seen here, successful login attempts are seen with two different users from two different IP addresses.


When the previous failed login attempts are compared, it is seen that the “analyst” user did not have an unsuccessful login attempt before from the IP address he successfully logged in. However, it is seen that many unsuccessful attempts were made with the “lets defend” user at the IP address 188.58.65.203. This shows us that the attacker successfully logged in with the “lets defend” user during the brute force.


As seen above, successful and unsuccessful logged-in users can be easily found with basic Linux commands. When these two results are examined in detail, it is seen that there is a successful entry after many unsuccessful attempts by the “lets defend” user from the 188.58.65.203 IP address.

## HTTP Login Brute Force Attack Detection Example


In HTTP login brute force attacks, the attacker usually tries a password with a dictionary attack on a login page. To analyze this, the content of the relevant log file should be opened with a text editor and the logs should be examined.
The following screenshot shows an HTTP login brute force attack. It is seen that the user found the password by successfully entering the password after a certain number of unsuccessful login attempts. Here, the difference between the package sizes in the response returned to failed login attempts and the package sizes in the response returned to successful login attempts is seen.


## Windows Login Brute Force Detection Example


Windows Login Records
Considering the general situation, a login activity appears in all successful or unsuccessful cyberattacks. An attacker often wants to log into the server to take over the system. For this purpose, it can perform a brute force attack or directly log in with the password in hand. In both cases (successful login / unsuccessful login attempt) the log will be created.


## Get Ali AK’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Let’s consider an attacker logged into the server after a brute-force attack. To better analyze what the attacker did after entering the system, we need to find the login date. For this, we need “Event ID 4624 — An account was successfully logged on”.


Each event log has its ID value. Filtering, analyzing, and searching the log title is more difficult, so it is easy to use the ID value.
You can find the details of which Event ID value means from the URL address below.
[https://www.ultimatewindowssecurity.com/securitylog/encyclopedia/default.aspx](https://www.ultimatewindowssecurity.com/securitylog/encyclopedia/default.aspx)


To reach the result, we open the “Event Viewer” and select “Security” logs.


Then we create a filter for the “4624” Event ID.


And now we see that the number of logs has decreased significantly and we are only listing logs for successful login activities. Looking at the log details, we see that the user of “LetsDefendTest” first logged in on at 23/02/2021 10:17 PM.


When we look at the “Logon Type” field, we see the value 10. This indicates that you are logged in with “Remote Desktop Services” or “Remote Desktop Protocol”.


You can find the meaning of the logon type values on Microsoft’s page.


[https://docs.microsoft.com/en-us/windows/security/threat-protection/auditing/event-4624](https://docs.microsoft.com/en-us/windows/security/threat-protection/auditing/event-4624)


In the next section, we will detect the Brute force attack the attacker made before logging in.


- Windows RDP Brute Force Detection


In this section, we will catch an attacker who is in the lateral movement phase. The attacker is trying to jump to the other machine by brute force over RDP.


When an unsuccessful login operation is made on RDP, the “Event ID 4625 — An account failed to log on” log is generated. If we follow this log, we can track down the attacker.


After filtering, we see 4 logs with 4625 Event IDs.


When we look at the dates, we see that the logs are formed one after the other. When we look at the details, it is seen that all logs are created for the “LetsDefendTest” user.


As a result, we understand that the attacker has unsuccessfully attempted to log in 4 times. To understand whether the attack was successful or not, we can search for the 4624 logs we saw in the previous section.


As can be seen from the results, the attacker succeeded in connecting to the system

## How to Avoid Brute Force Attacks?


- Stong Password Policy: Enforces minimum complexity constraints on the passwords set by the user.
• Account Lockout: Locks the account after a certain number of failed attempts.
• Throttling Authentication Attempts: Delays the response to a login attempt. A couple of seconds of delay is tolerable for someone who knows the password, but they can severely hinder automated tools.
• Using CAPTCHA: Requires solving a question difficult for machines. It works well if the login page is via a graphical user interface (GUI).
• Two-Factor Authentication: Ask the user to provide a code available via other means, such as email, smartphone app, SMS or physical key, etc.

---

*Originally published on [Medium](https://infosecwriteups.com/blue-team-bootcamp-series-p1-how-to-detect-brute-force-attacks-b107cc98b24a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
