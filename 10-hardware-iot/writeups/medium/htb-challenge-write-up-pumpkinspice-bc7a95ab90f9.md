# :electric_plug: HTB Challenge Write-Up: PumpkinSpice

> **Original Source:** [HTB Challenge Write-Up: PumpkinSpice](https://infosecwriteups.com/htb-challenge-write-up-pumpkinspice-bc7a95ab90f9)
> **Platform:** infosecwriteups.com | **Category:** `HARDWARE / IoT`

---

# HTB Challenge Write-Up: PumpkinSpice


## Code Review


PumpkinSpice is a Flask application with routes specifically designed for local access. It replicates scenarios where administrative functions are limited to local networks or specific hosts. It also includes a bot functionality that simulates an administrator reviewing all the “addresses” submitted through the application.


In challenges like this, simulating a user action often indicates the presence of a *Stored XSS* vulnerability in the application. Now, let’s examine the `templates`.


```
<!-- addresses.html; codes omitted for brevity -->

<h1>Addresses:</h1>
{% for address in addresses %}
<p>{{ address|safe }}</p>
{% endfor %}
```


In `addresses.html`, the Jinja `safe` filter is applied to each address, allowing the data to be rendered as HTML and creating an XSS injection point. With this XSS vulnerability identified, let's now look for another vulnerability to chain with it.


```
# app.py

@app.route("/api/stats", methods=["GET"])
def stats():
# codes omitted for brevity

command = request.args.get("command")
if not command:
return render_template("index.html", message="No command provided")

results = subprocess.check_output(command, shell=True, universal_newlines=True)
return results
```


In `app.py`, the `/api/stats` route accepts a `command` parameter that is executed using the `subprocess` module. Without any filtering in place, this makes the application vulnerable to *Command Injection*.


## Get Pat Bautista’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We’ve identified two critical issues in the application. Let’s test the application locally to confirm the vulnerabilities and explore how they can be exploited together.

## Local Testing


After starting the application locally with the `build-docker.sh` script, let's submit the following payload in the address input. This will create a `proof.txt` file under the static folder, which we can access via HTTP to verify its successful creation.


```
<script>fetch("/api/stats?command=touch+/app/static/proof.txt");</script>
```


Now that we’ve confirmed we can execute system commands by exploiting the XSS vulnerability and the lack of filtering on the administrative routes, let’s spin up the Challenge instance and capture the flag.

## Exploitation


We will modify the payload used to create `proof.txt` in our local Docker instance to instead copy the flag from the root directory to the application's static folder.


```
<script>fetch("/api/stats?command=cp+/flag*+/app/static/flag.txt");</script>
```


We used a wildcard because the flag’s filename was renamed in the `entrypoint.sh` script when the application started. While we don't know the exact filename of the flag, we know it starts with "flag".


Now, let’s access the flag using the `curl` command.


We have successfully pwned PumpkinSpice!


## References

---

*Originally published on [Medium](https://infosecwriteups.com/htb-challenge-write-up-pumpkinspice-bc7a95ab90f9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of hardware / iot CTF writeups.*
