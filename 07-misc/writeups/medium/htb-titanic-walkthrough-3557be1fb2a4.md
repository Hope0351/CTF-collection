# :game_die: Htb Titanic Walkthrough 3557Be1Fb2A4

> **Original Source:** [Htb Titanic Walkthrough 3557Be1Fb2A4](https://infosecwriteups.com/htb-titanic-walkthrough-3557be1fb2a4)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## 5. POST ROOT BONUS 😉


### 5.1 How was the LFI introduced ?


```
from flask import Flask, request, jsonify, send_file, render_template, redirect, url_for, Response
import os
import json
from uuid import uuid4

app = Flask(__name__)

TICKETS_DIR = "tickets"

if not os.path.exists(TICKETS_DIR):
os.makedirs(TICKETS_DIR)

@app.route('/')
def index():
return render_template('index.html')

@app.route('/book', methods=['POST'])
def book_ticket():
data = {
"name": request.form['name'],
"email": request.form['email'],
"phone": request.form['phone'],
"date": request.form['date'],
"cabin": request.form['cabin']
}

ticket_id = str(uuid4())
json_filename = f"{ticket_id}.json"
json_filepath = os.path.join(TICKETS_DIR, json_filename)

with open(json_filepath, 'w') as json_file:
json.dump(data, json_file)

return redirect(url_for('download_ticket', ticket=json_filename))

@app.route('/download', methods=['GET'])
def download_ticket():
ticket = request.args.get('ticket')
if not ticket:
return jsonify({"error": "Ticket parameter is required"}), 400

json_filepath = os.path.join(TICKETS_DIR, ticket)

if os.path.exists(json_filepath):
return send_file(json_filepath, as_attachment=True, download_name=ticket)
else:
return jsonify({"error": "Ticket not found"}), 404

if __name__ == '__main__':
app.run(host='127.0.0.1', port=5000)
```


The issue arises in the `/download` API which takes in the ticket parameter and does no input sanitization on it. Next, the value in ticket is appended to the string value `tickets`.


```
TICKETS_DIR = "tickets"
ticket = request.args.get('ticket')
json_filepath = os.path.join(TICKETS_DIR, ticket)
```


If the user input is `../../../../etc/passwd`, the `json_file` output becomes `tickets/../../../../etc/passwd` -> `/etc/passwd` . This is how we exploited the LFI in this box.

### 5.2 Why did the $PATH based binaries not work ?


We created a fake `truncate` command which would give us a shell in the `/home/developer/.local/bin`and setup a listener on our machine.


We waited for some time but did not receive a shell. Tried different payloads but it did not work so was kinda scratching my head. Found the reason once I became root.


As you know, the script `identify_images.sh`is being run as root but it is not necessary for the root user’s `$PATH` to be the same as the developer’s `$PATH`. The root user’s `$PATH` did not have the `/home/developer/.local/bin` entry as shown below. Hence, the script when run did not pick up the `truncate` command which we had created.


*PATH variable for root*


The reason the developer user had that entry in his path is because of the `/home/developer/.profile` which set this specifically for this user.


*developer .profile*

### 5.3 How is the cron running for the `identify_images.sh` script ?


Once we become root, we can run `crontab -l` for the root user to see if there are any cronjobs.


*root crontab*


*cleanup.sh*


We see that `identify_images.sh` is being run every minute and a cleanup of the shared library also takes place using `cleanup.sh`.


Every 10 minutes, the `/opt/app/static/assets/images` directory is being reset to a predefined directory using the `revert.sh` script.


*revert.sh*

---

*Originally published on [Medium](https://infosecwriteups.com/htb-titanic-walkthrough-3557be1fb2a4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
